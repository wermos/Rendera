Rendera
====
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A raytracing engine written in C++17.

This project was made as a part of the Seasons of Code (SoC) initiative by the WnCC Club at IITB.

>Note: The project uses some libraries which are added as submodules. To clone this project and build locally,


```bash
    git clone --recurse-submodules https://github.com/wermos/Rendera.git
```

To build the project and run locally,

```bash
    cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ./build/Rendera/Rendera
```
