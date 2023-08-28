#include "steganofs.h"

int stgfs_getattr (const char *path, struct stat *stbuf, __attribute__((unused)) struct fuse_file_info *fi)
{
  HiddenFat *hidden_fat = (HiddenFat *) fuse_get_context ()->private_data;

  // Check if the path corresponds to the root directory
  if (strcmp (path, "/") == 0)
    {
      // Set default values for the root directory
      stbuf->st_mode = S_IFDIR | 0777; // Directory with 755 permissions
      stbuf->st_nlink = 2; // Number of hard links (including . and ..)
      stbuf->st_nlink += get_amount_entries (hidden_fat, path);
      return 0; // Return success
    }
  else
    {
      HiddenFile *hidden_file = find_file_by_path (hidden_fat, path);
      if (hidden_file != NULL)
        {
          stbuf->st_mode = S_IFREG | 0666; // Regular file with 666 permissions
          stbuf->st_nlink = 1; // Number of hard links (including . and ..)
          stbuf->st_size = (__off_t) hidden_file->real_filesize;
          stbuf->st_uid = 1000;
          stbuf->st_gid = 1000;


          // Set access time and modification time based on the Unix timestamp
          time_t timestamp = hidden_file->timestamp;

          // Set access time (st_atim)
          stbuf->st_atim.tv_sec = timestamp;
          stbuf->st_atim.tv_nsec = 0;

          // Set modification time (st_mtim)
          stbuf->st_mtim.tv_sec = timestamp;
          stbuf->st_mtim.tv_nsec = 0;

          return 0;
        }
      return -ENOENT; // ENOENT indicates "No such file or directory"
    }
}

int stgfs_readdir (const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi,
                   enum fuse_readdir_flags flags)
{
  // Add entries for the root directory
  if (strcmp (path, "/") == 0)
    {
      filler (buf, "..", NULL, 0, 0);
      filler (buf, ".", NULL, 0, 0);
      HiddenFat *hidden_fat = (HiddenFat *) fuse_get_context ()->private_data;
      for (HiddenFile **p_file = hidden_fat->files; p_file < hidden_fat->files + STEGANOFS_AMOUNT_ROOT_FILES; p_file++)
        {
          if (*p_file != NULL)
            {
              filler (buf, (*p_file)->filename, NULL, 0, 0);
            }
        }
      return 0;
    }
  return -ENOENT;
}

int stgfs_create (const char *path, mode_t mode, struct fuse_file_info *fi)
{
  HiddenFat *hidden_fat = (HiddenFat *) fuse_get_context ()->private_data;

  mode = S_IFREG | 0666;
  if (count_path_components (path) == 1)
    {
      const char *filename = path + 1;
      HiddenFile **p_file = create_hidden_file (hidden_fat, filename, time (NULL));
      if (p_file != NULL)
        {
          return 0;
        }
      return -ENOMEM;
    }
  return -ENOENT;
}

int stgfs_write (const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
  if (count_path_components (path) != 1)
    {
      return -ENOENT;
    }
  struct fuse_context *private = fuse_get_context ();
  HiddenFat *hidden_fat;
  if (private != NULL)
    {
      hidden_fat = (HiddenFat *) (private->private_data);
    }
  else
    {
#ifdef STEGANOFS_DEBUG
      hidden_fat = (HiddenFat *) fi;
#else
      fprintf(stderr, "Couldn't get fuse context, is null!!\n");
      return -1;
#endif
    }
  HiddenFile *p_file = find_file_by_path (hidden_fat, path);
  if (p_file == NULL)
    {
      return -ENOENT;
    }

  // Check if file is already large enough, if no, allocate
  while (offset + size > p_file->filesize)
    {
      if (!extend_hidden_cluster (hidden_fat, p_file))
        {
          return -ENOMEM;
        }
    }
  p_file->real_filesize = offset + size;
  size_t bytes_written = 0;

  // Find correct clusterblock to write to
  HiddenCluster *hidden_cluster = p_file->hiddenCluster;
  size_t file_offset = 0;
  int size_signed = (int) size;
  while (size_signed > 0)
    {
      if (hidden_cluster == NULL)
        {
          fprintf (stderr,
                   "Tried to write at an offset for a file which is not large enough, did you forget to allocate?");
          return -errno;
        }
      // First we search for the block where the offset is in
      if (file_offset >= offset)
        {
          // Next we get the amount of blocks to write
          size_t amount_bytes_to_write;
          size_t offset_inside_block = offset % hidden_fat->block_size;
          if (offset + size_signed < file_offset + hidden_fat->block_size)
            {
              amount_bytes_to_write = size_signed;
            }
          else
            {
              amount_bytes_to_write = hidden_fat->block_size - offset_inside_block;
            }
          int written = write_block (hidden_fat, hidden_cluster
              ->b_index, buf, offset_inside_block, amount_bytes_to_write);
          if (written < 0)
            {
              return -errno;
            }
          bytes_written += written;
          if (written != amount_bytes_to_write)
            {
              fprintf (stderr, "Meant to write %zu bytes in Block %zu at block offset %zu (which is disk offset %zu),"
                               " but %d bytes were written!\n", amount_bytes_to_write, hidden_cluster->b_index,
                       offset_inside_block, offset, written);
              return -errno;
            }
          offset += (off_t) written;
          buf += written;
          size_signed -= (int) written;
        }
      hidden_cluster = hidden_cluster->next;
      file_offset += hidden_fat->block_size;
    }
  return (int) bytes_written;
}

int stgfs_read (const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
  if (count_path_components (path) != 1)
    {
      return -ENOENT;
    }
  struct fuse_context *private = fuse_get_context ();
  HiddenFat *hidden_fat;
  if (private != NULL)
    {
      hidden_fat = (HiddenFat *) (private->private_data);
    }
  else
    {
#ifdef STEGANOFS_DEBUG
      hidden_fat = (HiddenFat *) fi;
#else
      fprintf(stderr, "Couldn't get fuse context, is null!!\n");
      return -1;
#endif
    }
  HiddenFile *p_file = find_file_by_path (hidden_fat, path);
  if (p_file == NULL)
    {
      return -ENOENT;
    }

  // Check if we read outside file, if yes try to truncate size var to filesize
  if (offset + size > p_file->filesize)
    {
      int delta = (int) (p_file->filesize) - (int) (offset);
      if (delta >= 0)
        {
          size = delta;
        }
      else
        { // if even the offset is higher then the filesize, we simply return 0 bytes read
          return 0;
        }
    }
  size_t bytes_read = 0;

  // Find correct clusterblock to write to
  HiddenCluster *hidden_cluster = p_file->hiddenCluster;
  size_t file_offset = 0;
  int size_signed = (int) size;
  while (size_signed > 0)
    {
      if (hidden_cluster == NULL)
        {
          fprintf (stderr,
                   "Tried to write at an offset for a file which is not large enough, did you forget to allocate?");
          return -errno;
        }
      // First we search for the block where the offset is in
      if (file_offset >= offset)
        {
          // Next we get the amount of bytes to write
          size_t amount_bytes_to_read;
          size_t offset_inside_block = offset % hidden_fat->block_size;
          if (offset + size_signed < file_offset + hidden_fat->block_size)
            {
              amount_bytes_to_read = size_signed;
            }
          else
            {
              amount_bytes_to_read = hidden_fat->block_size - offset_inside_block;
            }
          int amount_read = read_block (hidden_fat, hidden_cluster
              ->b_index, buf, offset_inside_block, amount_bytes_to_read);
          if (amount_read < 0)
            {
              return -errno;
            }
          bytes_read += amount_read;
          if (amount_read != amount_bytes_to_read)
            {
              fprintf (stderr, "Meant to read %zu bytes from Block %zu at block offset %zu (which is disk offset %zu),"
                               " but %d bytes were read!\n", amount_bytes_to_read, hidden_cluster->b_index,
                       offset_inside_block, offset, amount_read);
              return -errno;
            }
          offset += (off_t) amount_read;
          buf += amount_read;
          size_signed -= (int) amount_read;
        }
      hidden_cluster = hidden_cluster->next;
      file_offset += hidden_fat->block_size;
    }
  return (int) bytes_read;
}

int stgfs_unlink (const char *path)
{
  if (count_path_components (path) != 1)
    {
      return -ENOENT;
    }
  struct fuse_context *private = fuse_get_context ();
  HiddenFat *hidden_fat;
  if (private != NULL)
    {
      hidden_fat = (HiddenFat *) (private->private_data);
    }
  else
    {
      fprintf (stderr, "Couldn't get fuse context, is null!!\n");
      return -1;
    }
  HiddenFile *p_file = find_file_by_path (hidden_fat, path);
  if (p_file == NULL)
    {
      return -ENOENT;
    }
  const char *filename = path + 1;
  return delete_hidden_file (hidden_fat, filename);
}

int stgfs_statfs (__attribute__((unused)) const char *path, struct statvfs *stbuf)
{

  if (!stbuf)
    {
      return -EINVAL;  // Invalid argument
    }

  struct fuse_context *private = fuse_get_context ();
  HiddenFat *hidden_fat;
  if (private != NULL)
    {
      hidden_fat = (HiddenFat *) (private->private_data);
    }
  else
    {
      fprintf (stderr, "Couldn't get fuse context, is null!!\n");
      return -1;
    }

  stbuf->f_bsize = hidden_fat->block_size;    // Filesystem block size
  stbuf->f_frsize = hidden_fat->block_size;   // Fundamental filesystem block size
  stbuf->f_blocks = hidden_fat->amount_blocks; // Total data blocks in filesystem
  stbuf->f_bfree = get_free_disk_space (hidden_fat) / hidden_fat->block_size;   // Free blocks
  stbuf->f_bavail =
      get_free_disk_space (hidden_fat) / hidden_fat->block_size;  // Free blocks available to non-superuser
  stbuf->f_namemax = STEGANOFS_MAX_FILENAME_LENGTH;

  return 0; // Success
}

struct fuse_operations fuse_operations = {
    .getattr = stgfs_getattr,
    .readdir = stgfs_readdir,
    .create = stgfs_create,
    .write = stgfs_write,
    .read = stgfs_read,
    .unlink = stgfs_unlink,
    .statfs = stgfs_statfs
};

struct HiddenFat *steganofs_create_new_ramdisk (size_t disk_size)
{
  size_t amount_blocks = disk_size / STEGANOFS_BLOCK_SIZE;
  return create_hidden_fat (amount_blocks * STEGANOFS_BLOCK_SIZE, STEGANOFS_BLOCK_SIZE);
}

size_t steganofs_format (const char *stegano_image_folder)
{
  struct SerializedFilesystem serialized_filesystem = stegano_provider_read (stegano_image_folder);
  if (serialized_filesystem.size == 0)
    return 0;
  size_t amount_blocks = calculate_amount_blocks (serialized_filesystem);
  free (serialized_filesystem.buf);
  HiddenFat *hidden_fat = steganofs_create_new_ramdisk (amount_blocks * STEGANOFS_BLOCK_SIZE);
  if (hidden_fat == NULL)
    {
      return 0;
    }
  serialized_filesystem = serialize_filesystem (hidden_fat);
  if (serialized_filesystem.size == 0)
    return 0;
  bool ret = stegano_provider_write (serialized_filesystem, stegano_image_folder);
  free (serialized_filesystem.buf);
  if (ret)
    {
      return amount_blocks * STEGANOFS_BLOCK_SIZE;
    }
  else
    {
      return 0;
    }
}

struct HiddenFat *steganofs_load_ramdisk (const char *stegano_image_folder)
{
  struct SerializedFilesystem serialized_filesystem = stegano_provider_read (stegano_image_folder);
  if (serialized_filesystem.size == 0)
    return NULL;
  HiddenFat *p_hidden_fat = load_ramdisk (serialized_filesystem);
  free (serialized_filesystem.buf);
  return p_hidden_fat;
}

bool steganofs_unload_ramdisk (struct HiddenFat *hidden_fat, const char *stegano_folder)
{
  struct SerializedFilesystem serialized_filesystem = serialize_filesystem (hidden_fat);
  if (serialized_filesystem.size == 0)
    return false;
  bool ret = stegano_provider_write (serialized_filesystem, stegano_folder);
  free (serialized_filesystem.buf);
  return ret;
}

bool steganofs_mount (struct HiddenFat *hidden_fat, const char *mnt_point)
{
  int argc = 1;
  const char *argv[] = {mnt_point};

  struct fuse_args args = FUSE_ARGS_INIT(argc, (char **) argv);
  struct fuse *fuse_struct = fuse_new (&args, &fuse_operations, sizeof (fuse_operations), hidden_fat);
  if (fuse_struct == NULL)
    {
      return false;
    }
  int status = fuse_mount (fuse_struct, mnt_point);
  if (status != 0)
    {
      return false;
    }
  status = fuse_loop (fuse_struct);
  return status == 0;
}

bool steganofs_umount (const char *mnt_point)
{
  char command[256];
  snprintf (command, sizeof (command), "umount %s", mnt_point);
  int res = system (command);
  return res == 0;

}

void steganofs_show_fragmentation (HiddenFat *hidden_fat, char *output_message)
{
  show_hidden_fat (hidden_fat, output_message);
}

size_t steganofs_fragmentation_array (HiddenFat *hidden_fat, size_t **array)
{
  return get_fragmentation_array (hidden_fat, array);
}

bool steganofs_check_integrity (HiddenFat *hidden_fat)
{
  return check_integrity (hidden_fat);
}

float steganofs_defragmentation_percent (HiddenFat *hidden_fat)
{
  return check_for_fragmentation (hidden_fat);
}

void steganofs_defragmentate_filesystem (HiddenFat *hidden_fat)
{
  defragmentate (hidden_fat);
}
