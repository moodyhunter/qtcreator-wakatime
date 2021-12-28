# QT Creator Wakatime plugin

# Information:

This repo is a fork of https://github.com/BlurryLight/qtcreator-wakatime which is a fork of https://github.com/nonametr/qtcreator-wakatime. The original repo provides binary plugin up to Qtc4.9, which is too old to work with the latest Qtc, and this is a fork from https://github.com/BlurryLight/qtcreator-wakatime.

# Aim:
QtCreator plugin for automatic time tracking and metrics generated from your programming activity by using [wakatime](https://wakatime.com).

# Build From Source:

Build instructions for Ubuntu(should be same for other distributions):

### Requirements:

- A C++ compiler,  eg: GCC, Clang, MSVC. Make sure it supports C++17
- CMake
- Qt 5.15 (the one currently used) or above
- QtCreator source from  https://github.com/qt-creator/qt-creator.git

### Steps:

1. git clone https://github.com/qt-creator/qt-creator.git

2. cd qt-creator

3. If you are building plugin for QtCreator 4.14.0 run 'git checkout origin/v4.14.0' or list all branches with 'git branch -a' and pick required version.

4. Build 'qt-creator' details here https://doc-snapshots.qt.io/qtcreator-extending/getting-and-building.html (also you can run build from other Qt Creator).

5. Run:

   ```
   cd qtcreator-wakatime/
   mkdir build && cd build
   cmake ../ -DCMAKE_BUILD_TYPE=Release -DQTC_BUILD_PATH=/path/to/where/you/built/qtcreator
   cmake --build . --config Release
   ```

   

6. Afterwards you should see a shared library libWakatime.so or Wakatme.dll or whatever your platform shows for shared libraries, zip it, then add it via plugin menu in Qtcreator

   ```
   Help > About Plugins > Install Plugin... > point to where the zip was created 
   ```

7. Plugin should now be ready for use, just restart qtcreator.

# Usage

![preview](./preview.gif)
