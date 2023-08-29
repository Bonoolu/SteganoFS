### Pluto Explorer: Graphical User Interface (GUI)

The Pluto Explorer serves as the Graphical User Interface (GUI) for SteganoFS, providing an intuitive and familiar environment for interacting with concealed filesystems within steganographic image files. Built using C++ and the Qt framework, the Pluto Explorer closely resembles the widely recognized Windows File Explorer, ensuring ease of use for users. This section provides an overview of the Pluto Explorer's key features and functionalities.



#### Navigation and Exploration

Pluto Explorer offers multiple ways to navigate and explore concealed filesystems:

- **Tree View:** Located on the left side of the GUI, the Tree View displays the hierarchical structure of the concealed filesystem. Users can expand folders, view subdirectories, and select items for further interaction.

- **Path Input Field:** Users can directly type in paths in the line edit at the top of the GUI, enabling quick navigation to specific locations within the concealed filesystem.

- **Back and Forward Buttons:** Positioned to the left of the path-field, these buttons allow users to navigate back and forth through previously visited locations, enhancing the browsing experience.



#### Functionality Buttons

The group box at the top of the GUI chosts several functional buttons, each designed to facilitate various actions:

- **Preview:** The preview button activates the visibility of a preview section, enabling users to preview selected files or folders before performing actions on them.c

- **Light Mode:** The light mode button allows users to switch between themes, enhancing visual comfort during extended usage.c

- **Paste, Delete, Cut, Copy, New Folder, New File:** While these buttons are currently placeholders and not fully implemented, they provide a glimpse of upcoming features for the GUI, enhancing its functionality over time.



#### Mounting and Filesystem Management

Accessible from the menu bar option "File" the GUI provides essential filesystem management features:

- **Mount and Load:** Users can initiate the process of mounting a concealed filesystem by choosing a steganographic image file and a destination folder. Once mounted, the GUI unlocks additional options for interacting with the concealed filesystem.

- **Filesystem Information:** Users can view detailed information about the mounted concealed filesystem, gaining insights into its properties and usage.

- **Fragmentation and Defragmentation:** The GUI allows users to assess the fragmentation status of the filesystem and perform defragmentation operations to optimize its structure.

- **Format**: By choosing this option, the User can select a filesystem to format.  

- **Unmount:** Users have the ability to format the concealed filesystem or unmount a mounted folder, ensuring controlled access to the filesystem and its contents.

