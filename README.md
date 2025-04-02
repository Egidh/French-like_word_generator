# Graph project

## Building

### Building for Visual Studio (Windows)

This project was developed for Windows under Visual Studio.
To compile this project, make sure you have correctly installed the following tools:
- [Visual Studio](https://visualstudio.microsoft.com/) with "Desktop Development in C++" option,
- [CMake](https://cmake.org/download/).

Rename the ``build_vs.txt`` file to ``build_vs.bat`` and double-click on this file to run the script.
The Visual Studio solution is created in the ``_build_vs`` folder.

If you wish to compile the project manually, you can run the following commands:
```
mkdir _build_vs
cd _build_vs
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

### Building for linux

Use the following commands to install project dependencies:
```
sudo apt install cmake
```
Then run the following commands:
```
mkdir _build_linux
cd _build_linux
cmake ..
cmake --build .
../_bin/application
```

## License & Mention

Special mention to M. Bodin and M. Bannier who created the basecode of this project. This project was realized during their class.
All code produced for this project is licensed under the [MIT license](/LICENSE.md).
