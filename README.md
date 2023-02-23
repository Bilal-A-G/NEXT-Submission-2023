# Ubisoft NEXT Programming Submission 2023

My submission to the Ubisoft NEXT Programming category, it consists of 2 parts:

- The Game (name pending)
- The Engine (Ga_U_SS)

## Engine Features

- **Software 3D Graphics**
- **Entity Component System**
- **Physics**
- **Particles**
- **Screenshake**
- **Scene Graph / Transform Hierarchy**
- **Scene Management**


## Running

### Via an IDE (Visual Studio or Rider preferred)

This project uses Premake 5 as its build system

To build, first download this repository, unzip it, and double click the "GenerateProjectFiles.bat" file to 
generate the .sln, which will be for Visual Studio 2019 by default

The contents of the .bat file are:
```
call external\premake\premake5.exe vs2019
PAUSE
```

Feel free to change the ```vs2019``` part of the call to whatever version of Visual 
Studio you are using

Lastly, open the .sln and build the .exe (Ctrl B) and then run it (Ctrl F5)

### Via the release

Download the release .zip, then unzip it and double click the .exe