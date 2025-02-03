# Jaguar SDK 25/Development Tools

Jaguar SDK 25 is an updated version of the Jaguar development tools released by Cubanismo, which was already itself a custom version of the original jaguar SDK released by Belboz in 2009. Both SDKs can be found here:
https://github.com/cubanismo/jaguar-sdk
https://www.hillsoftware.com/files/atari/jaguar/

All changes and improvements made by Cubanismo have been preserved (check README.md in the legacy/docs folder for a better view of these changes) as the design goal behind this 2025 version is to propose a simpler development environment based on Sublime Text and WSL for Windows. The SDK still works with regular Linux version though.

To fully embrace this philosophy, I have simplified the structure of the repository and rework the 3d engine example. The current goal is to apply this to the working examples provided in the SDK and finally to offer a lightweight game engine based on those examples, with the hope of getting some more 3d games out.


## Tools

This part only focus on tools specific to the Jaguar SDK 25.

* Sublime Text build environment configuration: Those scripts are available in "tools/sublime" and help you setup Sublime Text to work together with WSL. 
* build.sh: this script is intended to be called from outside linux by the Sublime Text build environment. It will setup the Jaguar environment and then select the project to build or clean.

## Build/Installation

If you intend to work from Linux, you can skip this part as the original SDK workflow still works fine.

* Install WSL: To be able to work from Windows, WSL (Windows Subsystem for Linux) is used as a proxy to use the SDK and build the different Jaguar projects. To install WSL, please refer to the widely available documentation online, or simply search the Windows Store to install one of the Linux distribution running on WSL in just a few clicks.We recommand Ubuntu 18.04 as several tools from the SDK are DOS only and required Dosemu that only run on this version of Ubuntu (not later ones).
* Install Sublime Text build environment configuration: Please read the README in the "tools/sublime" folder for more information.

## Usage/Examples

build.sh script is intended to be called from Sublime Text but you can of course call it from shell. The first parameter is the relative folder to the project. The second parameter is the target name for the binary and is optional. Make sure it matches the name in the makefile. It is used to copy the binary your dev roms folder.

````sh
$ build.sh examples/3d demo
````

## Credits/Thanks

* Cubanismo: https://github.com/cubanismo/jaguar-sdk - Custom development tools package
