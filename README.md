# Modificate

A Minecraft clone made for me and my friends. Uses Lua for implementing game mechanics such as blocks, items, and (hopefully) rendering for some blocks/items.

## Building

I use a full CMake buildsystem since I deploy across platforms (primarily Linux and macOS).

First install the required packages:

```
pacman -S glm boost
```

```
brew install glm
brew install boost
```

```
./vcpkg install glm:x64-windows-static boost-json:x64-windows-static
```

All other required packages are in `thirdparty/`

Then, do a clean CMake build.

```
mkdir build
cd build
cmake ..
cmake --build .
```

On macOS this build is a little different:
```
mkdir build
cd build
cmake -DCMAKE_CXX_FLAGS="-std=c++17 -stdlib=libc++" ..
cmake --build .
```

For clangd, ccls, or the obsoleted cquery on Windows using MSYS2:
```
cmake -DCMAKE_CXX_COMPILER="clang++" -DCMAKE_C_COMPILER="clang" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
```

## Modding
