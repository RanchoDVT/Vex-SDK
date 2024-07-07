# Vex-SDK

## What is this?

This is a modified version of the vex SDK to support newer standards of the C/CPP language.  

"Things" updated:

- make.exe | 4.2 -> 4.4.1
- GNU ARM.exe's | 2013 -> 13.3.rel1/2024
  - GCC Arm includes | 4.9.3 -> 13.3.1

- clang.exe | 8.0.0 -> 18.1.8
  - clang includes | 8.0.0 -> 18.1.8

- mkenv.mk | C=gnu99, C++=gnu++11 -> C=gnu23, C++=gnu++23

## How can I apply this "update"?

Vscode insiders -> "C:\Users\%USERNAME%\AppData\Roaming\Code - Insiders\User\globalStorage\vexrobotics.vexcode"  
Vscode stable -> "C:\Users\%USERNAME%\AppData\Roaming\Code\User\globalStorage\vexrobotics.vexcode"  

1. In here, delete the folders `sdk`, and `tools`.  
2. Then copy the folders `sdk` and `tools` from this repo, and paste it in the folder where you deleted it.  
3. Load/Reload VsCode
**VERY IMPORTANT**  
4. Then in your project, in the `example` folder, there are folders for a platform, paste it into your workspace and replace the files!  

The technical detail is that vex hardcodes some of the folders that we replace, so we have to change where the makefile looks for it!  
If you DON'T do this step, and you try to build, vex will auto redownload the sdk, and you will have to do 1-3 AGAIN!  

## Known problem

- VsCode will replace the c_cpp_properties.json every time you relaunch the window.  I can't fix this, you will need to manually fix it... (Sorry!)  
