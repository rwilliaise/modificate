# Modificate

A Minecraft clone made for me and my friends. Uses Lua for implementing game mechanics such as blocks, items, and (hopefully) rendering for some blocks/items.

## Modding


## Building

I use a full CMake buildsystem since I deploy across platforms (primarily Linux and macOS).

Make sure that submodules were downloaded:
```
git submodule update --init
```

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
cmake .. -GXcode
open modificate.xcodeproj
```

