PowerVR Tutorial
======================

程序依赖关系
------------------
    ├── 00_HelloPVR
    ├── 01_Uniform
    ├── 02_UiRenderer
    │   └── 20_Chinese
    ├── 03_TriangleClass
    ├── 04_Colors
    ├── 05_Textures
    ├── 06_Perspective
    ├── 07_Transform
    ├── 08_Rotation
    ├── 09_View
    ├── 10_lookAt
    ├── 11_CubeClass
    ├── 12_SimpleLighting
    ├── 13_DepthTest
    ├── 14_PointLighting
    │   ├── 17_LoadModel
    │   │   └── 19_Control
    │   ├── 21_FrameBuffer
    │   ├── 22_MSAA
    │   └── 23_Shadow
    ├── 15_CubeMap
    ├── 16_Reflection
    └── 18_IBL

平台
------------------
目前支持 Linux 平台和 Windows 平台

Linux 平台编译
------------------
* 下载 PowerVR SDK 并编译
* 安装 libglm-dev
* 修改 Makefile.include 指定 SDK 的位置
* 进入到程序目录执行 make

Windows 平台编译
------------------
* 下载 PowerVR SDK 并编译
* 修改 base.cmake 指定 SDK 的位置
* 打开 Visual Studio 的命令行界面
* cd 到程序目录，执行
```console
    mkdir build
    cd build
    cmake ..
    msbuild HelloPVR.sln
* 可以在 Debug 目录找到目标程序
