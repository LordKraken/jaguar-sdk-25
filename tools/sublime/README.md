# Jaguar SDK 25/Sublime Text

Sublime text configuration file to create a minimum dev environment for Jaguar SDK 25, based on wsl.

## Installation

* Copy this file to you sublime folder, generally under "C:\Users\username\AppData\Roaming\Sublime Text\Packages\User"
* In the same sublime folder, copy or edit the file "Default (Windows).sublime-keymap" in order to add shortcuts for Build/Clean/Run
* Update the "working_dir" folder with the dev roms folder
* Update the jaguar SDK 25 folder for both build and clean command (use the linux path as it is passed as an argument to wsl)
* Update BigPEmu (or another emulator) folder

## Usage

If you are using the provided "Default (Windows).sublime-keymap", and according that paths are valid

* F5 starts the built roms (if suceeded) with the emulator
* F7 builds the project using make
* F12 cleans the project