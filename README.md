Rendera
====
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![Windows](https://github.com/wermos/Rendera/actions/workflows/windows.yml/badge.svg)](https://github.com/wermos/Rendera/actions/workflows/windows.yml) [![Linux](https://github.com/wermos/Rendera/actions/workflows/linux.yml/badge.svg)](https://github.com/wermos/Rendera/actions/workflows/linux.yml)

A raytracing engine written in C++17.

This project was made as a part of the Seasons of Code (SoC) initiative by the WnCC Club at IITB.

> **Note**
> The project uses some libraries which are added as submodules, to clone this project use

```bash
    git clone --recurse-submodules https://github.com/wermos/Rendera.git
```

To build the project and run locally,

```bash
    cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ./build/Rendera/Rendera
```

```bash
-DCMAKE_CXX_COMPILER=gcc-11  //use this flag if gcc is not default
```bash
