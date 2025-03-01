# cadance
A CAD / CAM initiative based on Immutable data model, ELM architecture and key-input based effective non window based UX

'Cadance' - From 'CAD', 'Dance' and 'Cadence'. The name is chosen to elude to the user experience being that of 'dancing' with the tool. And also, promote a user interface that propmets working in a 'cadence' as in a steady rythm back and forth.

# Initial version 0.0

An empty repository to create a C++ CMake and Conan package manager consuming software development environment.

## How this project has been setup

This project is setup as a conan package combined with cmake support for tool chain build and application.

For conan command references see https://docs.conan.io/2/reference/commands.html 

### conan new cmake_exe -d name=cadance -d version=0.0

For conan command reference see https://docs.conan.io/2/reference/commands/new.html 

```sh
kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub/cadance % conan new cmake_exe -d name=cadance -d version=0.0
File saved: CMakeLists.txt
File saved: conanfile.py
File saved: src/cadance.cpp
File saved: src/cadance.h
File saved: src/main.cpp
File saved: test_package/conanfile.py
kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub/cadance % 
```

### conan install . --build=missing

For conan command reference see https://docs.conan.io/2/reference/commands/install.html 

```sh
kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub/cadance % conan install . --build=missing


======== Input profiles ========
Profile host:
[settings]
arch=armv8
build_type=Release
compiler=apple-clang
compiler.cppstd=gnu17
compiler.libcxx=libc++
compiler.version=16
os=Macos

Profile build:
[settings]
arch=armv8
build_type=Release
compiler=apple-clang
compiler.cppstd=gnu17
compiler.libcxx=libc++
compiler.version=16
os=Macos


======== Computing dependency graph ========
Graph root
    conanfile.py (cadance/0.0): /Users/kjell-olovhogdahl/Documents/GitHub/cadance/conanfile.py

======== Computing necessary packages ========

======== Installing packages ========

======== Finalizing install (deploy, generators) ========
conanfile.py (cadance/0.0): Calling generate()
conanfile.py (cadance/0.0): Generators folder: /Users/kjell-olovhogdahl/Documents/GitHub/cadance/build/Release/generators
conanfile.py (cadance/0.0): CMakeToolchain generated: conan_toolchain.cmake
conanfile.py (cadance/0.0): CMakeToolchain: Preset 'conan-release' added to CMakePresets.json.
    (cmake>=3.23) cmake --preset conan-release
    (cmake<3.23) cmake <path> -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake  -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Release
conanfile.py (cadance/0.0): CMakeToolchain generated: /Users/kjell-olovhogdahl/Documents/GitHub/cadance/build/Release/generators/CMakePresets.json
conanfile.py (cadance/0.0): CMakeToolchain generated: /Users/kjell-olovhogdahl/Documents/GitHub/cadance/CMakeUserPresets.json
conanfile.py (cadance/0.0): Generating aggregated env files
conanfile.py (cadance/0.0): Generated aggregated env files: ['conanbuild.sh', 'conanrun.sh']
Install finished successfully
kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub/cadance % 
```

At this stage a find and a diff reveals the following overall changes to the candance file structure.

```sh
kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub/cadance % find . > after.txt
kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub/cadance % diff before.txt after.txt 
1a2
> ./CMakeLists.txt
2a4
> ./CMakeUserPresets.json
3a6,7
> ./conanfile.py
> ./after.txt
5a10,24
> ./test_package
> ./test_package/conanfile.py
> ./build
> ./build/Release
> ./build/Release/generators
> ./build/Release/generators/deactivate_conanrun.sh
> ./build/Release/generators/conanrun.sh
> ./build/Release/generators/conanbuild.sh
> ./build/Release/generators/conanbuildenv-release-armv8.sh
> ./build/Release/generators/conandeps_legacy.cmake
> ./build/Release/generators/CMakePresets.json
> ./build/Release/generators/deactivate_conanbuild.sh
> ./build/Release/generators/cmakedeps_macros.cmake
> ./build/Release/generators/conan_toolchain.cmake
> ./build/Release/generators/conanrunenv-release-armv8.sh
58a78,81
> ./src
> ./src/cadance.cpp
> ./src/cadance.h
> ./src/main.cpp
kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub/cadance % 
```
Note that 'conan install' reports what settings has to (and could go) into cmake processing files.

```conan
conanfile.py (cadance/0.0): CMakeDeps necessary find_package() and targets for your CMakeLists.txt
    find_package(OpenCASCADE)
    target_link_libraries(... opencascade::opencascade)
conanfile.py (cadance/0.0): CMakeToolchain generated: conan_toolchain.cmake
conanfile.py (cadance/0.0): CMakeToolchain: Preset 'conan-release' added to CMakePresets.json.
    (cmake>=3.23) cmake --preset conan-release
    (cmake<3.23) cmake <path> -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake  -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Release
conanfile.py (cadance/0.0): CMakeToolchain generated: /Users/kjell-olovhogdahl/Documents/GitHub/cadance/build/Release/generators/CMakePresets.json
conanfile.py (cadance/0.0): CMakeToolchain generated: /Users/kjell-olovhogdahl/Documents/GitHub/cadance/CMakeUserPresets.json
conanfile.py (cadance/0.0): Generating aggregated env files
conanfile.py (cadance/0.0): Generated aggregated env files: ['conanbuild.sh', 'conanrun.sh']
Install finished successfully
```

This means that to have cmake know about the dependancy on opencascade we need to put the sugested 'find_package' and 'target_link_libraries' into CmakeLists.txt (which we have done).