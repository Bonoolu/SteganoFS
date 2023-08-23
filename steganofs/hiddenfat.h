#ifndef _HIDDENFAT_H_
#define _HIDDENFAT_H_

#include "hiddencluster.h"
#include "steganofs.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct HiddenCluster HiddenCluster;
typedef struct HiddenFile HiddenFile;
typedef struct HiddenFat HiddenFat;

struct HiddenFat {
    size_t block_size;
    size_t amount_blocks;
    unsigned char *disk;
    HiddenCluster *clusters;
    HiddenFile *files[STEGANOFS_AMOUNT_ROOT_FILES];
};

// HiddenFat
HiddenFat *create_hidden_fat (size_t disk_size, size_t block_size);

void free_hidden_fat (HiddenFat *hidden_fat);

size_t get_amount_entries (HiddenFat *hidden_fat, const char *path);

size_t get_free_disk_space (HiddenFat *hidden_fat);

void show_hidden_fat (HiddenFat *hidden_fat, char *output_message);

bool check_integrity (HiddenFat *hidden_fat);

float check_for_fragmentation (HiddenFat *hidden_fat);

void defragmentate (HiddenFat *hidden_fat);

int write_block (HiddenFat *hidden_fat, size_t b_index, const char *buffer, size_t offset, size_t length);

int read_block (HiddenFat *hidden_fat, size_t b_index, const char *buffer, size_t offset, size_t length);

size_t get_fragmentation_array (HiddenFat *hidden_fat, size_t **array);

#endif //_HIDDENFAT_H_
