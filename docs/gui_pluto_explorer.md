# Pluto Explorer: Graphical User Interface (GUI)

The Pluto Explorer serves as the Graphical User Interface (GUI) for SteganoFS, providing a familiar environment for interacting with concealed filesystems within steganographic image files. Built using C++ and the Qt framework, the Pluto Explorer was built to resemble the widely recognized Windows File Explorer, ensuring ease of use for users. The key features and functionalities are:



#### Navigation and Exploration

Pluto Explorer offers multiple ways to navigate and explore concealed filesystems:

- **Tree View:** Located on the left side of the GUI, the Tree View displays the hierarchical structure of the system's directories. Users can expand folders, view subdirectories, and select items for further interaction.

- **Path Input Field:** Users can directly type in paths in the input field at the top of the GUI, enabling quick navigation to specific locations within the filesystem.

- **Back and Forward Buttons:** Positioned to the left of the path-field, these buttons allow users to navigate back and forth through previously visited locations.



#### Functionality Buttons

The group box at the top of the GUI hosts several functional buttons, each designed to facilitate various actions:

- **Preview:** The preview button activates the visibility of a preview section, enabling users to preview selected image files. Files of different type will be represented with their assigned icon.

- **Light Mode:** The light mode button allows users to switch between themes. Pluto Explorer offers a light and a dark theme.

- **Paste, Delete, Cut, Copy, New Folder, New File:** While these buttons are currently placeholders and not fully implemented, they provide a glimpse of upcoming features for the GUI.



#### Mounting and Filesystem Management

Accessible from the menu bar option "File" the GUI provides essential filesystem management features:

- **Mount and Load:** Users can initiate the process of mounting a directory by choosing steganographic image files and a destination folder. Once mounted, the GUI unlocks additional options for interacting with the loaded filesystem.

- **Filesystem Information:** Users can view detailed information about the loaded filesystem, gaining insights into its properties and stats.

- **Fragmentation and Defragmentation:** The GUI allows users to assess the fragmentation status of the filesystem and perform defragmentation operations to optimize its structure.

- **Format**: By choosing this option, the User can select a filesystem to format.  

- **Unmount:** Users have the ability unmount a mounted folder, ensuring controlled access to the filesystem and its contents.

