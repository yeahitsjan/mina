<p align="center">
  <a href="https://github.com/yeahitsjan/mina">
    <img height="128" width="128" src="https://raw.githubusercontent.com/yeahitsjan/mina/develop/resources/icons/app/logo_default_512px.png">
  </a>
  <p align="center"><b>Mina : 3D material authoring tool</b></>
</p>

Mina is a 3D material authoring tool like [Substance Designer](https://www.adobe.com/products/substance3d-designer.html) or [Material Maker](https://www.materialmaker.org/). 

**This project is in active development**, more information will be available in a while...

## Setup a build environment

**This is subject to change! A full build guide will be available when the application grows. Current dev environment is Debian based. If you want to hack on the application yourself, it is recommended that you use atleast OpenGL or OpenGL ES 3.1.** Using a dedicated graphics card will improve the performance.

What you need:
- [Qt 5.14.x + QtCreator](https://download.qt.io/archive/qt/5.14/)
- [Git](https://git-scm.com)
- ``sudo apt install libgl-dev mesa-common-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev libgl1-mesa-dev libxi-dev build-essential libdbus-1-dev libfontconfig1-dev libfreetype6-dev libx11-dev``

```
$ git clone --recursive https://github.com/yeahitsjan/mina.git
$ cd mina
```

It is recommended to use the Qt project file `mina.pro` together with QtCreator to build Mina.

## License

GNU GPLv3. See [LICENSE](https://github.com/yeahitsjan/mina/blob/develop/LICENSE).