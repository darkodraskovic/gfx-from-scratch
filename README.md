# Scratch Renderer

[Reylib](https://www.raylib.com/) implementation of raytracer and a rasterizer described in [Computer Graphics from Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/).

# Installation

## Dirs

```
mkdir build
mkdir bin
```

## Configure

```
cd build/ && cmake ..
```

## Build and run

```
cd build/ && make && cd ../bin && ./main
```

## clangd

Install [clangd](https://clangd.llvm.org/installation.html).

`compile_commands.json` will be created in `build` directory. Symlink it (or simply copy it) to the root directory. To symlink it, `cd` to the root and

```
ln -s build/compile_commands.json .
```

# Resources

- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
