# Modificate

A Minecraft clone made for me and my friends. Uses Lua for implementing game mechanics such as blocks, items, and (hopefully) rendering for some blocks/items.

## Building

I use a full CMake buildsystem since I develop on both a Windows and Arch Linux machine.

First install the required packages:

```
pacman -S glm glfw boost
```

```
vcpkg install glfw3:x64-windows-static glm:x64-windows-static boost-json:x64-windows-static
```

All other required packages are in `thirdparty/`

Then, do a clean CMake build.

```
mkdir build
cd build
cmake ..
cmake --build .
```


## Modding
