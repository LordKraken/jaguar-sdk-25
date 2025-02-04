# Jaguar SDK 25/Development Tools

The **Jaguar SDK 25** is an updated version of the Jaguar development tools released by **Cubanismo**, which was already itself a custom version of the original jaguar SDK released by **Belboz** in 2009. Both SDKs can be found here:

https://github.com/cubanismo/jaguar-sdk
https://www.hillsoftware.com/files/atari/jaguar/

All changes and improvements made by Cubanismo have been preserved (check README.md in the legacy/docs folder for a better view of these changes) as the design goal behind the 2025 version is to propose a simpler development environment based on Sublime Text and WSL for Windows. The SDK still works with regular Linux version though.

To fully embrace this philosophy, I have also simplified the structure of the repository and reworked the 3d engine example entirely, with the hope of getting people with a C-language background onboard and more 3D games out.

## New Tools

This part only focus on tools specific to the Jaguar SDK 25.

* **Sublime Text build Build Environment**: Those scripts are available in "tools/sublime" and help you setup Sublime Text to work together with WSL. 
* **build.sh**: this script is intended to be called from outside Linux by Sublime Text. It will setup the Jaguar environment and then select the project to build or clean.

## Build/Installation

If you intend to work from Linux, you can skip this part as the original SDK workflow still works fine.

* **maketools.sh** (optional): Binaries are provided (for Ubuntu) but if you want or need to rebuild everything, call this script. Refer to Cubanismo's README for the complete installation procedure.
* Install **WSL**: To be able to work from Windows, WSL (Windows Subsystem for Linux) is used as a proxy to use the SDK and build the different Jaguar projects. To install WSL, documenation is widely available online, or simply search the Windows Store to install one of the WSL Linux distribution. We recommend to use **Ubuntu 18.04** as several tools from the SDK required Dosemu that only run with this version (or prior) of Ubuntu.
* Install **Sublime Text Build Environment**: Please read the README in the "tools/sublime" folder for more information.

## Usage

the **build.sh** script is intended to be called from Sublime Text but you can of course call it from shell. The first parameter is the relative folder to the project. The second parameter is the target name for the binary and is optional. Make sure it matches the binary name in the makefile as it is used to copy the binary file into your roms folder.

````sh
$ build.sh examples/3d demo
````

## Examples

The main idea behind this version is to promote the creation of games, especially 3D games, within the Jaguar community. This is why we will provide and develop an example game based upon the minimalistic 3D engine provided in the SDK. A 2D example game might follow, even though you might want to look at JagStudio instead for 2D games.

## Folders

A big effort has been made to simplify the folders structure. There is still some work left but the guideline here is to separate the SDK, the working examples and the deprecated ones into different folders. Here is the current structure:

* dev (new): Folder containing templated games, that can be reused or extend to your need.
* examples (new): Folder containing working examples from the original SDK.
* jaguar: Original (messy) folder of the SDK. It contains everything except tools. Will be deprecated once all working examples have been moved out.
* legacy (new): old files, like readme, docker files, etc.
* sdk (new): the actual SDK, source and libraries.
* tools: all the original tools, along with binaries, as well as Sublime Text configuration files.

## Credits/Thanks

* Cubanismo: https://github.com/cubanismo/jaguar-sdk - Custom development tools package
* Cobra: https://stormplay.scot/games/followthrough/jaguar/ - Devlog of Operation Follow Through
