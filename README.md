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
目前仅支持 Linux 平台

编译
------------------
* 下载 PowerVR SDK 并编译
* 安装 libglm-dev
* 修改 Makefile.include 指定 SDK 的位置
* 进入到程序目录执行 make
