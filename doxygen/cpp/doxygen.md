# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`DefragmentDialog`](#classDefragmentDialog) | The [DefragmentDialog](#classDefragmentDialog) class represents a dialog for defragmentation settings.
`class `[`FormatFileSystemDialog`](#classFormatFileSystemDialog) | Dialog for mounting a filesystem from a specific path.
`class `[`FragmentationDiagram`](#classFragmentationDiagram) | 
`class `[`FragmentationDialog`](#classFragmentationDialog) | 
`class `[`FragmentTile`](#classFragmentTile) | 
`class `[`MainWindow`](#classMainWindow) | The [MainWindow](#classMainWindow) class is the main GUI window for the application.
`class `[`MountFromPathDialog`](#classMountFromPathDialog) | Dialog for mounting a filesystem from a specific path.
`class `[`PreviewGraphicsView`](#classPreviewGraphicsView) | The [PreviewGraphicsView](#classPreviewGraphicsView) class provides a custom QGraphicsView for previewing graphics.
`class `[`ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog) | 
`class `[`SteganoFsAdapter`](#classSteganoFsAdapter) | Adapter class for interacting with the SteganoFS filesystem.
`class `[`Worker`](#classWorker) | The [Worker](#classWorker) class represents a worker object that performs tasks asynchronously.

# class `DefragmentDialog` 

```
class DefragmentDialog
  : public QDialog
```  

The [DefragmentDialog](#classDefragmentDialog) class represents a dialog for defragmentation settings.

This class provides a dialog window to configure defragmentation settings for the application.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`DefragmentDialog`](#classDefragmentDialog_1a36555d7df2bd9665e0e23ff33f318b1a)`(QWidget * parent)` | Constructs a [DefragmentDialog](#classDefragmentDialog) object.
`public  `[`~DefragmentDialog`](#classDefragmentDialog_1ad9228d774583b1de71e35ea6c89975a8)`()` | Destroys the [DefragmentDialog](#classDefragmentDialog) object.
`public void `[`setLightmodeOn`](#classDefragmentDialog_1a35d90d7a9065c8b5bdbf07c52469048e)`(bool newLightmodeOn)` | Sets the light mode on/off.
`public bool `[`lightmodeOn`](#classDefragmentDialog_1ad4aff2a176ddc99ac526395e63bac6e6)`() const` | Checks if light mode is on.
`public void `[`setFragmentation`](#classDefragmentDialog_1ab2bb749a237464fed7a328be447c83a4)`(float f)` | Sets the fragmentation level.
`public void `[`setAdapter`](#classDefragmentDialog_1afcab0648f64b6f802d6ea226864365a3)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` | Sets the adapter for the defragmentation dialog.

## Members

#### `public  explicit `[`DefragmentDialog`](#classDefragmentDialog_1a36555d7df2bd9665e0e23ff33f318b1a)`(QWidget * parent)` 

Constructs a [DefragmentDialog](#classDefragmentDialog) object.

#### Parameters
* `parent` The parent widget.

#### `public  `[`~DefragmentDialog`](#classDefragmentDialog_1ad9228d774583b1de71e35ea6c89975a8)`()` 

Destroys the [DefragmentDialog](#classDefragmentDialog) object.

#### `public void `[`setLightmodeOn`](#classDefragmentDialog_1a35d90d7a9065c8b5bdbf07c52469048e)`(bool newLightmodeOn)` 

Sets the light mode on/off.

#### Parameters
* `newLightmodeOn` Whether light mode should be turned on.

#### `public bool `[`lightmodeOn`](#classDefragmentDialog_1ad4aff2a176ddc99ac526395e63bac6e6)`() const` 

Checks if light mode is on.

#### Returns
True if light mode is on, otherwise false.

#### `public void `[`setFragmentation`](#classDefragmentDialog_1ab2bb749a237464fed7a328be447c83a4)`(float f)` 

Sets the fragmentation level.

#### Parameters
* `f` The new fragmentation level.

#### `public void `[`setAdapter`](#classDefragmentDialog_1afcab0648f64b6f802d6ea226864365a3)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` 

Sets the adapter for the defragmentation dialog.

#### Parameters
* `newAdapter` The adapter to be set.

# class `FormatFileSystemDialog` 

```
class FormatFileSystemDialog
  : public QDialog
```  

Dialog for mounting a filesystem from a specific path.

This class provides a dialog for selecting a mounting path and filesystem path, along with additional settings like light mode. It also allows connecting a [SteganoFsAdapter](#classSteganoFsAdapter) to handle the mounting process.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FormatFileSystemDialog`](#classFormatFileSystemDialog_1aaba29f0e2d89c8822c1a53fbcec16a3c)`(QWidget * parent)` | 
`public  `[`~FormatFileSystemDialog`](#classFormatFileSystemDialog_1abbfaf02cde260941c5b03f5ba17b1a90)`()` | Destructs the [FormatFileSystemDialog](#classFormatFileSystemDialog).
`public bool `[`lightmodeOn`](#classFormatFileSystemDialog_1afecfd82a5095388be528f89a2eb37c99)`() const` | Checks if light mode is enabled.
`public void `[`setLightmodeOn`](#classFormatFileSystemDialog_1a20822de12d768b26a74311d156bc4349)`(bool newLightmodeOn)` | Sets the light mode.
`public QString `[`filesystemPath`](#classFormatFileSystemDialog_1af22d96618f70f44242656405a580370b)`() const` | Returns the selected filesystem path.
`public void `[`setFilesystemPath`](#classFormatFileSystemDialog_1a95011a39226ae36584ffc95fd276080a)`(const QString & newFilesystemPath)` | Sets the filesystem path.
`public `[`SteganoFsAdapter`](#classSteganoFsAdapter)` * `[`adapter`](#classFormatFileSystemDialog_1a5a1a3f337eeb4998e6182ef1ad348b51)`() const` | Returns the associated [SteganoFsAdapter](#classSteganoFsAdapter).
`public void `[`setAdapter`](#classFormatFileSystemDialog_1addcb99c6141a0e15df6565dc5f8b806b)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` | Sets the [SteganoFsAdapter](#classSteganoFsAdapter).

## Members

#### `public  explicit `[`FormatFileSystemDialog`](#classFormatFileSystemDialog_1aaba29f0e2d89c8822c1a53fbcec16a3c)`(QWidget * parent)` 

#### `public  `[`~FormatFileSystemDialog`](#classFormatFileSystemDialog_1abbfaf02cde260941c5b03f5ba17b1a90)`()` 

Destructs the [FormatFileSystemDialog](#classFormatFileSystemDialog).

#### `public bool `[`lightmodeOn`](#classFormatFileSystemDialog_1afecfd82a5095388be528f89a2eb37c99)`() const` 

Checks if light mode is enabled.

#### Returns
True if light mode is enabled, false otherwise.

#### `public void `[`setLightmodeOn`](#classFormatFileSystemDialog_1a20822de12d768b26a74311d156bc4349)`(bool newLightmodeOn)` 

Sets the light mode.

#### Parameters
* `newLightmodeOn` True to enable light mode, false to disable.

#### `public QString `[`filesystemPath`](#classFormatFileSystemDialog_1af22d96618f70f44242656405a580370b)`() const` 

Returns the selected filesystem path.

#### Returns
The selected filesystem path.

#### `public void `[`setFilesystemPath`](#classFormatFileSystemDialog_1a95011a39226ae36584ffc95fd276080a)`(const QString & newFilesystemPath)` 

Sets the filesystem path.

#### Parameters
* `newFilesystemPath` The new filesystem path.

#### `public `[`SteganoFsAdapter`](#classSteganoFsAdapter)` * `[`adapter`](#classFormatFileSystemDialog_1a5a1a3f337eeb4998e6182ef1ad348b51)`() const` 

Returns the associated [SteganoFsAdapter](#classSteganoFsAdapter).

#### Returns
The associated [SteganoFsAdapter](#classSteganoFsAdapter).

#### `public void `[`setAdapter`](#classFormatFileSystemDialog_1addcb99c6141a0e15df6565dc5f8b806b)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` 

Sets the [SteganoFsAdapter](#classSteganoFsAdapter).

#### Parameters
* `newAdapter` The new [SteganoFsAdapter](#classSteganoFsAdapter).

# class `FragmentationDiagram` 

```
class FragmentationDiagram
  : public QWidget
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FragmentationDiagram`](#classFragmentationDiagram_1aae4ee9ece57258ffb064fc0d7e1f2f24)`(QWidget * parent)` | 
`public  `[`~FragmentationDiagram`](#classFragmentationDiagram_1acdffba03285bc7e7eaea907d561a097b)`()` | 

## Members

#### `public  explicit `[`FragmentationDiagram`](#classFragmentationDiagram_1aae4ee9ece57258ffb064fc0d7e1f2f24)`(QWidget * parent)` 

#### `public  `[`~FragmentationDiagram`](#classFragmentationDiagram_1acdffba03285bc7e7eaea907d561a097b)`()` 

# class `FragmentationDialog` 

```
class FragmentationDialog
  : public QDialog
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FragmentationDialog`](#classFragmentationDialog_1ac7cce577cee2b686bafcd1e32cfa6e34)`(QWidget * parent)` | 
`public  `[`~FragmentationDialog`](#classFragmentationDialog_1a70760f655d540eb0ace1a951de0e8311)`()` | 

## Members

#### `public  explicit `[`FragmentationDialog`](#classFragmentationDialog_1ac7cce577cee2b686bafcd1e32cfa6e34)`(QWidget * parent)` 

#### `public  `[`~FragmentationDialog`](#classFragmentationDialog_1a70760f655d540eb0ace1a951de0e8311)`()` 

# class `FragmentTile` 

```
class FragmentTile
  : public QWidget
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FragmentTile`](#classFragmentTile_1ae2e01b74ff0ac19c82aeef4c19d68edd)`(QWidget * parent,const QColor & color)` | 
`public void `[`setColor`](#classFragmentTile_1a20ec9f6c163c9f5f2c5b054776cfbf6a)`(const QColor & color)` | 
`public  `[`~FragmentTile`](#classFragmentTile_1a2ad9a8b38100a34f066f65fea6124782)`()` | 

## Members

#### `public  explicit `[`FragmentTile`](#classFragmentTile_1ae2e01b74ff0ac19c82aeef4c19d68edd)`(QWidget * parent,const QColor & color)` 

#### `public void `[`setColor`](#classFragmentTile_1a20ec9f6c163c9f5f2c5b054776cfbf6a)`(const QColor & color)` 

#### `public  `[`~FragmentTile`](#classFragmentTile_1a2ad9a8b38100a34f066f65fea6124782)`()` 

# class `MainWindow` 

```
class MainWindow
  : public QMainWindow
```  

The [MainWindow](#classMainWindow) class is the main GUI window for the application.

This class handles various UI interactions, signals, and slots.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`MainWindow`](#classMainWindow_1a996c5a2b6f77944776856f08ec30858d)`(QWidget * parent)` | Constructor for the [MainWindow](#classMainWindow) class.
`public  `[`~MainWindow`](#classMainWindow_1a1f7d2c56410fc1bfa135bb907d43313f)`()` | Destructor for the [MainWindow](#classMainWindow) class.
`{signal} public void `[`pathChanged`](#classMainWindow_1ace748f1515a0654d9f2325d7bca9a02b)`()` | Signal emitted when the path is changed.

## Members

#### `public  explicit `[`MainWindow`](#classMainWindow_1a996c5a2b6f77944776856f08ec30858d)`(QWidget * parent)` 

Constructor for the [MainWindow](#classMainWindow) class.

#### Parameters
* `parent` The parent widget.

#### `public  `[`~MainWindow`](#classMainWindow_1a1f7d2c56410fc1bfa135bb907d43313f)`()` 

Destructor for the [MainWindow](#classMainWindow) class.

#### `{signal} public void `[`pathChanged`](#classMainWindow_1ace748f1515a0654d9f2325d7bca9a02b)`()` 

Signal emitted when the path is changed.

# class `MountFromPathDialog` 

```
class MountFromPathDialog
  : public QDialog
```  

Dialog for mounting a filesystem from a specific path.

This class provides a dialog for selecting a mounting path and filesystem path, along with additional settings like light mode. It also allows connecting a [SteganoFsAdapter](#classSteganoFsAdapter) to handle the mounting process.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`MountFromPathDialog`](#classMountFromPathDialog_1ac0ffa4a61c9a0d1598cff9b0a925b755)`(QWidget * parent)` | Constructs a [MountFromPathDialog](#classMountFromPathDialog).
`public  `[`~MountFromPathDialog`](#classMountFromPathDialog_1ad0c342390443b00e9887a0d51bd5c190)`()` | Destructs the [MountFromPathDialog](#classMountFromPathDialog).
`public void `[`setMountingPath`](#classMountFromPathDialog_1ad44022ed4523176f59bd94e7b07fe763)`(const QString & newMountingPath)` | Sets the mounting path.
`public QString `[`mountingPath`](#classMountFromPathDialog_1a00e9bca483eb6268bce54510722050ab)`() const` | Returns the selected mounting path.
`public bool `[`lightmodeOn`](#classMountFromPathDialog_1ac67393a1ccbb1ea0e2bd8647e11a7fc4)`() const` | Checks if light mode is enabled.
`public void `[`setLightmodeOn`](#classMountFromPathDialog_1a3e4e30fae568277d4ade30ff744da027)`(bool newLightmodeOn)` | Sets the light mode.
`public QString `[`filesystemPath`](#classMountFromPathDialog_1a0d39744eee257c6e1664cf9b8b724c8e)`() const` | Returns the selected filesystem path.
`public void `[`setFilesystemPath`](#classMountFromPathDialog_1ad1dee511ad5ab72a032ad1e651bf567e)`(const QString & newFilesystemPath)` | Sets the filesystem path.
`public `[`SteganoFsAdapter`](#classSteganoFsAdapter)` * `[`adapter`](#classMountFromPathDialog_1ac6cbcc62f1d2113a475348ba715f16c1)`() const` | Returns the associated [SteganoFsAdapter](#classSteganoFsAdapter).
`public void `[`setAdapter`](#classMountFromPathDialog_1aeaf4590f25a8bf5c44e77f70c6858e3b)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` | Sets the [SteganoFsAdapter](#classSteganoFsAdapter).
`{signal} public void `[`finishedMounting`](#classMountFromPathDialog_1a02fabdeb1840a462564166b95fdf5722)`()` | Signal emitted when the mounting process is finished.

## Members

#### `public  explicit `[`MountFromPathDialog`](#classMountFromPathDialog_1ac0ffa4a61c9a0d1598cff9b0a925b755)`(QWidget * parent)` 

Constructs a [MountFromPathDialog](#classMountFromPathDialog).

#### Parameters
* `parent` The parent widget.

#### `public  `[`~MountFromPathDialog`](#classMountFromPathDialog_1ad0c342390443b00e9887a0d51bd5c190)`()` 

Destructs the [MountFromPathDialog](#classMountFromPathDialog).

#### `public void `[`setMountingPath`](#classMountFromPathDialog_1ad44022ed4523176f59bd94e7b07fe763)`(const QString & newMountingPath)` 

Sets the mounting path.

#### Parameters
* `newMountingPath` The new mounting path.

#### `public QString `[`mountingPath`](#classMountFromPathDialog_1a00e9bca483eb6268bce54510722050ab)`() const` 

Returns the selected mounting path.

#### Returns
The selected mounting path.

#### `public bool `[`lightmodeOn`](#classMountFromPathDialog_1ac67393a1ccbb1ea0e2bd8647e11a7fc4)`() const` 

Checks if light mode is enabled.

#### Returns
True if light mode is enabled, false otherwise.

#### `public void `[`setLightmodeOn`](#classMountFromPathDialog_1a3e4e30fae568277d4ade30ff744da027)`(bool newLightmodeOn)` 

Sets the light mode.

#### Parameters
* `newLightmodeOn` True to enable light mode, false to disable.

#### `public QString `[`filesystemPath`](#classMountFromPathDialog_1a0d39744eee257c6e1664cf9b8b724c8e)`() const` 

Returns the selected filesystem path.

#### Returns
The selected filesystem path.

#### `public void `[`setFilesystemPath`](#classMountFromPathDialog_1ad1dee511ad5ab72a032ad1e651bf567e)`(const QString & newFilesystemPath)` 

Sets the filesystem path.

#### Parameters
* `newFilesystemPath` The new filesystem path.

#### `public `[`SteganoFsAdapter`](#classSteganoFsAdapter)` * `[`adapter`](#classMountFromPathDialog_1ac6cbcc62f1d2113a475348ba715f16c1)`() const` 

Returns the associated [SteganoFsAdapter](#classSteganoFsAdapter).

#### Returns
The associated [SteganoFsAdapter](#classSteganoFsAdapter).

#### `public void `[`setAdapter`](#classMountFromPathDialog_1aeaf4590f25a8bf5c44e77f70c6858e3b)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` 

Sets the [SteganoFsAdapter](#classSteganoFsAdapter).

#### Parameters
* `newAdapter` The new [SteganoFsAdapter](#classSteganoFsAdapter).

#### `{signal} public void `[`finishedMounting`](#classMountFromPathDialog_1a02fabdeb1840a462564166b95fdf5722)`()` 

Signal emitted when the mounting process is finished.

# class `PreviewGraphicsView` 

```
class PreviewGraphicsView
  : public QGraphicsView
```  

The [PreviewGraphicsView](#classPreviewGraphicsView) class provides a custom QGraphicsView for previewing graphics.

This class extends QGraphicsView and adds functionality for handling resize events and emitting a signal to request a scene refresh.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`PreviewGraphicsView`](#classPreviewGraphicsView_1a45c98cad2a7523214a55490496da6d44)`(QWidget * parent)` | Constructs a [PreviewGraphicsView](#classPreviewGraphicsView).
`public void `[`resizeEvent`](#classPreviewGraphicsView_1afa9e61b3319db87c1d9abc57bad6b539)`(QResizeEvent * event)` | Handles resize events for the view.
`{signal} public void `[`refreshScene`](#classPreviewGraphicsView_1a35941b72b1cf7893aa7f9e3e36bf2836)`()` | Signal emitted when the scene needs to be refreshed.

## Members

#### `public  explicit `[`PreviewGraphicsView`](#classPreviewGraphicsView_1a45c98cad2a7523214a55490496da6d44)`(QWidget * parent)` 

Constructs a [PreviewGraphicsView](#classPreviewGraphicsView).

#### Parameters
* `parent` The parent QWidget of this view.

#### `public void `[`resizeEvent`](#classPreviewGraphicsView_1afa9e61b3319db87c1d9abc57bad6b539)`(QResizeEvent * event)` 

Handles resize events for the view.

#### Parameters
* `event` A pointer to the QResizeEvent object containing event details.

#### `{signal} public void `[`refreshScene`](#classPreviewGraphicsView_1a35941b72b1cf7893aa7f9e3e36bf2836)`()` 

Signal emitted when the scene needs to be refreshed.

# class `ShowFileSystemInfoDialog` 

```
class ShowFileSystemInfoDialog
  : public QDialog
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog_1a6dbcf3f3fb4799581ea35d8c13d2a320)`(QWidget * parent)` | Constructs a [ShowFileSystemInfoDialog](#classShowFileSystemInfoDialog).
`public  `[`~ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog_1a15669c5dfeeb0d78c07d52868cd63142)`()` | Destructor for [ShowFileSystemInfoDialog](#classShowFileSystemInfoDialog).
`public void `[`setLightmodeOn`](#classShowFileSystemInfoDialog_1a6aa47a76fc6b885456ada85780966c00)`(bool newLightmodeOn)` | Sets the light mode state.
`public void `[`showFilesystemInfo`](#classShowFileSystemInfoDialog_1a0510202431ad37d11d18c0e72216eb89)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` & sfa)` | Displays filesystem information.

## Members

#### `public  explicit `[`ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog_1a6dbcf3f3fb4799581ea35d8c13d2a320)`(QWidget * parent)` 

Constructs a [ShowFileSystemInfoDialog](#classShowFileSystemInfoDialog).

#### Parameters
* `parent` The parent widget.

#### `public  `[`~ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog_1a15669c5dfeeb0d78c07d52868cd63142)`()` 

Destructor for [ShowFileSystemInfoDialog](#classShowFileSystemInfoDialog).

#### `public void `[`setLightmodeOn`](#classShowFileSystemInfoDialog_1a6aa47a76fc6b885456ada85780966c00)`(bool newLightmodeOn)` 

Sets the light mode state.

#### Parameters
* `newLightmodeOn` The new light mode state.

#### `public void `[`showFilesystemInfo`](#classShowFileSystemInfoDialog_1a0510202431ad37d11d18c0e72216eb89)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` & sfa)` 

Displays filesystem information.

#### Parameters
* `sfa` The [SteganoFsAdapter](#classSteganoFsAdapter) for filesystem access.

# class `SteganoFsAdapter` 

Adapter class for interacting with the SteganoFS filesystem.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`SteganoFsAdapter`](#classSteganoFsAdapter_1a8b16a46ebc14456614ec45e33b31d651)`(std::string steganoImageFolder)` | Constructor for [SteganoFsAdapter](#classSteganoFsAdapter).
`public  `[`~SteganoFsAdapter`](#classSteganoFsAdapter_1abe270fd7364b981e11ca8b95629d4d57)`()` | Destructor for [SteganoFsAdapter](#classSteganoFsAdapter).
`public size_t `[`formatNewFilesystem`](#classSteganoFsAdapter_1ab90da955cdb155d8c7ffdca00983ba38)`()` | Creates a new filesystem the specified path of steganographic files.
`public bool `[`createNewFilesystem`](#classSteganoFsAdapter_1ad1064d64fa6aafa0561e4a83e044c7b2)`(size_t diskSize)` | Creates a new filesystem with the given disk size.
`public bool `[`loadFilesytemFromSteganoProvider`](#classSteganoFsAdapter_1ad7a36c1a7ac2f3be193e20c706c40f7a)`()` | Load the hidden filesystem from the steganographic image provider.
`public bool `[`mount`](#classSteganoFsAdapter_1ad79d549ad56dd0b3a1c9a85ed3a941f3)`(const std::string & mntPoint)` | Mount the hidden filesystem to the given mount point.
`public bool `[`writeFilesystemToSteganoProvider`](#classSteganoFsAdapter_1a8d668990c752bf8e3386ee1f80a59fa8)`()` | Write the hidden filesystem back to the steganographic image provider.
`public bool `[`umount`](#classSteganoFsAdapter_1aa1e0bd5984e477759b299c354f682ab5)`(std::string mntPoint)` | Unmount the hidden filesystem.
`public float `[`getFragmentationInPercent`](#classSteganoFsAdapter_1afd4cb6d986578c8ae3818fbe04d593e1)`()` | Get the fragmentation of the hidden filesystem in percentage.
`public std::vector< size_t > `[`getFilesystemVector`](#classSteganoFsAdapter_1a44ebcbf79df3e7aaf3c8bb126c980fc6)`()` | Get a vector containing fragmentation information of the filesystem.
`public bool `[`checkFilesystemIntegrity`](#classSteganoFsAdapter_1a1899628c9e7216a10172d8fde47b6f23)`()` | Check the integrity of the hidden filesystem.
`public bool `[`defragmentateFilesystem`](#classSteganoFsAdapter_1a0a59bee7c6dd614233441e77d18648b9)`()` | Defragment the hidden filesystem.
`public struct statvfs `[`getFilesystemInfo`](#classSteganoFsAdapter_1abb2a12ee096914a0b6983596ce93c1e1)`()` | Get information about the hidden filesystem.
`public std::string `[`steganoImageFolder`](#classSteganoFsAdapter_1acd82f4904fdb30b50cf05416388cf395)`() const` | Get the steganographic image folder path.
`public bool `[`isMounted`](#classSteganoFsAdapter_1a9dc809dc804b9c51ec834ae27c2f8c0d)`() const` | Check if the filesystem is mounted.
`public bool `[`isLoaded`](#classSteganoFsAdapter_1a8cff00edd53804553a0c47f3cd54b3b1)`() const` | Check if the filesystem is loaded.
`public std::string `[`mountPath`](#classSteganoFsAdapter_1ac30e2ac223e1f7f4a650ff411ce10594)`() const` | Get the mount path of the filesystem.

## Members

#### `public  explicit `[`SteganoFsAdapter`](#classSteganoFsAdapter_1a8b16a46ebc14456614ec45e33b31d651)`(std::string steganoImageFolder)` 

Constructor for [SteganoFsAdapter](#classSteganoFsAdapter).

#### Parameters
* `steganoImageFolder` Path to the stegano image folder.

#### `public  `[`~SteganoFsAdapter`](#classSteganoFsAdapter_1abe270fd7364b981e11ca8b95629d4d57)`()` 

Destructor for [SteganoFsAdapter](#classSteganoFsAdapter).

#### `public size_t `[`formatNewFilesystem`](#classSteganoFsAdapter_1ab90da955cdb155d8c7ffdca00983ba38)`()` 

Creates a new filesystem the specified path of steganographic files.

#### Returns
The size of the new filesystem. 0 if fails.

#### `public bool `[`createNewFilesystem`](#classSteganoFsAdapter_1ad1064d64fa6aafa0561e4a83e044c7b2)`(size_t diskSize)` 

Creates a new filesystem with the given disk size.

#### Parameters
* `diskSize` Size of the disk in bytes. 

#### Returns
True if successful, false otherwise.

#### `public bool `[`loadFilesytemFromSteganoProvider`](#classSteganoFsAdapter_1ad7a36c1a7ac2f3be193e20c706c40f7a)`()` 

Load the hidden filesystem from the steganographic image provider.

#### Returns
True if the filesystem was loaded successfully, false otherwise.

#### `public bool `[`mount`](#classSteganoFsAdapter_1ad79d549ad56dd0b3a1c9a85ed3a941f3)`(const std::string & mntPoint)` 

Mount the hidden filesystem to the given mount point.

#### Parameters
* `mntPoint` Mount point for the filesystem. 

#### Returns
True if the filesystem was mounted successfully, false otherwise.

#### `public bool `[`writeFilesystemToSteganoProvider`](#classSteganoFsAdapter_1a8d668990c752bf8e3386ee1f80a59fa8)`()` 

Write the hidden filesystem back to the steganographic image provider.

#### Returns
True if the filesystem was written successfully, false otherwise.

#### `public bool `[`umount`](#classSteganoFsAdapter_1aa1e0bd5984e477759b299c354f682ab5)`(std::string mntPoint)` 

Unmount the hidden filesystem.

#### Parameters
* `mntPoint` Mount point for the filesystem. Can be omitted if set as member 

#### Returns
True if the filesystem was unmounted successfully, false otherwise.

#### `public float `[`getFragmentationInPercent`](#classSteganoFsAdapter_1afd4cb6d986578c8ae3818fbe04d593e1)`()` 

Get the fragmentation of the hidden filesystem in percentage.

#### Returns
Fragmentation percentage if the filesystem is loaded, otherwise -1.

#### `public std::vector< size_t > `[`getFilesystemVector`](#classSteganoFsAdapter_1a44ebcbf79df3e7aaf3c8bb126c980fc6)`()` 

Get a vector containing fragmentation information of the filesystem.

#### Returns
Vector of fragmentation data if the filesystem is loaded, otherwise an empty vector.

#### `public bool `[`checkFilesystemIntegrity`](#classSteganoFsAdapter_1a1899628c9e7216a10172d8fde47b6f23)`()` 

Check the integrity of the hidden filesystem.

#### Returns
True if the filesystem is intact, false if integrity check fails.

#### `public bool `[`defragmentateFilesystem`](#classSteganoFsAdapter_1a0a59bee7c6dd614233441e77d18648b9)`()` 

Defragment the hidden filesystem.

#### Returns
True if defragmentation was successful, false otherwise.

#### `public struct statvfs `[`getFilesystemInfo`](#classSteganoFsAdapter_1abb2a12ee096914a0b6983596ce93c1e1)`()` 

Get information about the hidden filesystem.

#### Returns
Structure containing filesystem information.

#### `public std::string `[`steganoImageFolder`](#classSteganoFsAdapter_1acd82f4904fdb30b50cf05416388cf395)`() const` 

Get the steganographic image folder path.

#### Returns
Steganographic image folder path.

#### `public bool `[`isMounted`](#classSteganoFsAdapter_1a9dc809dc804b9c51ec834ae27c2f8c0d)`() const` 

Check if the filesystem is mounted.

#### Returns
True if the filesystem is mounted, false otherwise.

#### `public bool `[`isLoaded`](#classSteganoFsAdapter_1a8cff00edd53804553a0c47f3cd54b3b1)`() const` 

Check if the filesystem is loaded.

#### Returns
True if the filesystem is loaded, false otherwise.

#### `public std::string `[`mountPath`](#classSteganoFsAdapter_1ac30e2ac223e1f7f4a650ff411ce10594)`() const` 

Get the mount path of the filesystem.

#### Returns
Mount path of the filesystem.

# class `Worker` 

```
class Worker
  : public QObject
```  

The [Worker](#classWorker) class represents a worker object that performs tasks asynchronously.

This class inherits from QObject and provides slots for performing various tasks.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Worker`](#classWorker_1a013acfa37bedf294ece993aa4fcfb59f)`(QObject * parent)` | Constructor for the [Worker](#classWorker) class.
`{slot} public void `[`mountFolder`](#classWorker_1a9de036625c9508479d832b6b20a30f76)`(const QVariant & qAdapt,const QString & s)` | Mounts a folder using the provided adapter and path.

## Members

#### `public  explicit `[`Worker`](#classWorker_1a013acfa37bedf294ece993aa4fcfb59f)`(QObject * parent)` 

Constructor for the [Worker](#classWorker) class.

#### Parameters
* `parent` The parent QObject for this worker.

#### `{slot} public void `[`mountFolder`](#classWorker_1a9de036625c9508479d832b6b20a30f76)`(const QVariant & qAdapt,const QString & s)` 

Mounts a folder using the provided adapter and path.

#### Parameters
* `qAdapt` The QVariant containing a pointer to the [SteganoFsAdapter](#classSteganoFsAdapter). 

* `s` The path to the folder to be mounted.

Generated by [Moxygen](https://sourcey.com/moxygen)