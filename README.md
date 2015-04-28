# uGL
An OpenGL model viewer created for a school project in C++/Qt with native OpenGL bindings

Created by
 - Isabelle Chum-Chhin
 - David Arel
 - Alexandre Rivest
 - Vincent Aubé

## Technologies
  - OpenGL 3.30
  - GLSL 3.30.6 (version #330 core)
  - Qt 5.4 x64
  - glm 0.9.6.3
  - FreeImage / FreeImagePlus 3.17.0
  - Compiled under MSVC++ 12.0 x64
  - ISO-compatible C++11

### How to compile
  - Visual Studio 2013
  - Qt 5.4 libraries in your PATH (Windows)
  - MSVC++ Redist Packages x64 for VS2013 (msvcp12.dll)
  - You can easily export the .pri files out from VS and create a standard QMake file. I was able to build the project under Fedora 21 x64 with fairly minor changes (coming soon in another branch!).
    - You need to install FreeImagePlus with your favorite package manager
  
### Tested under
  - Windows 8.1 x64, Windows 8.0 x64
  - Intel HD 2xxx (with OpenGL 3.3-compatible drivers), Intel HD 3xxx, Intel HD 4xxx, NVIDIA GTX 9xx, NVIDIA GTX 7xx, AMD Radeon HD 7xxx, AMD Radeon R9 2xx

## Architecture (namespace sorted using VS filters) ![architecture](https://raw.githubusercontent.com/Vaub/uGL/master/FinalArchitecture.png)
