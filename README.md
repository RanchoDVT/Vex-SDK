# Vex-SDK

## What is this?

This is a modified version of the vex SDK to support newer standards of the C/CPP language.  

Things updated:

- make.exe | 4.2 -> 4.4.1
- GNU ARM.exe's | 2021 -> 13.2.rel1/2023
  - GCC Arm includes | 4.9.3 -> 13.2.1

- clang.exe | 8.0.0 -> 18
  - clang includes | 8.0.0 -> 18

- mkenv.mk | C=gnu99, C++=gnu++11 -> C=gnu23, C++=gnu++26
  
*I am aware that gnu 13.2.1 has very little c++26 support, but I added it anyways.*  
*THIS IS ONLY FOR V5, I DON'T HAVE HARDWARE TO TEST IQ2, OR EXP. PLEASE DON'T ASK ME TO MAKE IT FOR THOSE PLATFORMS!*  

## How can I apply this "update"?

Vscode insiders -> "C:\Users\%USERNAME%\AppData\Roaming\Code - Insiders\User\globalStorage\vexrobotics.vexcode"  
Vscode stable -> "C:\Users\%USERNAME%\AppData\Roaming\Code\User\globalStorage\vexrobotics.vexcode"  

- In here, delete the folders `sdk`, and `tools`.  
- Then copy the folders `sdk` and `tools` from this repo, and paste it in the folder where you deleted it.  
- *Vex will auto download IQ2 and EXP*, as I don't include them to save space :)  

**VERY IMPORTANT**  
Then in your project, in the `example` folder, paste it into your workspace and replace the files!  
The technical detail is that vex hardcodes some of the folders that we replace, so we have to change where the makefile looks for it!  
If you DON'T do this step, and you try to build, vex will auto redownload the sdk, and you will have to do 1-3 AGAIN!  

## Known problem

- VsCode will replace the c_cpp_properties.json every time you relaunch the window.  I can't fix this, you will need to manually fix it... (Sorry!)  
