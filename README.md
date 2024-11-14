# Vex-SDK

## What is this?

This is a modified version of the vex SDK to support newer standards of the C/CPP language.  

> [!WARNING]
> This is unofficial and in no way affiliated, endorsed, supported, or created by VEX Robotics.

## Things updated

- make.exe | 4.2 -> 4.4.1
- GNU ARM.exe's | 2013 -> 13.3.rel1/2024
  - GCC Arm includes | 4.9.3 -> 13.3.1

- clang.exe | 8.0.0 -> 19.1.3
  - clang includes | 8.0.0 -> 19.1.3

- mkenv.mk | C=gnu99, C++=gnu++11 -> C=gnu23, C++=gnu++23

## How can I apply this "update"?

Method 1: (1.3.0b or later, auto update script 1.4 or later)  
Use my new powershell script to do this!  
1: Open it with ISE to view the code, or run as powershell when ready, and follow the prompts!  
(You don't need admin privileges to run this.)

> [!IMPORTANT]
> **VERY IMPORTANT**  
> 2: In your project, make sure you update your makefiles and json files with your platfrom;  from the examples folder. (It will be on your desktop)   

Method 2:  
Vscode insiders -> "C:\Users\%USERNAME%\AppData\Roaming\Code - Insiders\User\globalStorage\vexrobotics.vexcode"  
Vscode stable -> "C:\Users\%USERNAME%\AppData\Roaming\Code\User\globalStorage\vexrobotics.vexcode"  

1. Where you vex install location is (see paths above), delete the folders `sdk`, and `tools`.  
2. Then copy the folders `sdk` and `tools` from this repo, and paste it in the folder where you deleted it.  
3. Load/Reload VsCode

> [!IMPORTANT]
> **VERY IMPORTANT**  
> 4: In the folder `example` from my sdk, find your platform, and move the files/folders from there into your project.  

Vex code hardcodes the location of the sdk into the makefiles, and if you don't replace it, the sdk will redownload and you will have to do steps 1-3 again!
(I am making a script to do this, but it only works in powershell ise right now.)

## Known problem

- VsCode will replace the c_cpp_properties.json every time you relaunch the window.  I can't fix this, you will need to manually fix it... (Sorry!)  
