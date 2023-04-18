# JgsuSchoolNetwork
Applicable to Jinggangshan University campus network login.

适用于井冈山大学校园网登录

Recommended use AllPlatforms.

推荐使用 AllPlatforms，为最新版本

**Windows**

Switch to the directory,you can choose  `AllPlatform` or `Windows`

切换到目录 `AllPlatform` or `Windows` 下

1. gcc

    Library file `ws2_32.lib` is required for compilation.

    依赖库文件 `ws2_32.lib`

    We can compile with the following command.

    编译命令如下

    `gcc client.c myhttp.c mysocket.c -lws2_32 -o login`

    or

    `gcc *.c -l ws2_32 -o login`
2. cmake

    Create a folder,and switch to it.

    创建一个文件夹，并切换到该目录

    `mkdir build`

    `cd build`

    We can compile with the following command.

    使用如下命令编译

    `cmake ..`

    `make`

    Execute it.

    执行

    `./login.exe`

**Linux**

Switch to the directory,you can choose  `AllPlatform` or `Linux`

切换到目录 `AllPlatform` or `Linux` 下

1. gcc

    编译命令如下

    `gcc client.c myhttp.c mysocket.c -o login`

    or

    `gcc *.c -o login`

2. cmake

    Create a folder,and switch to it.

    创建一个文件夹，并切换到该目录

    `mkdir build`

    `cd build`

    We can compile with the following command.

    使用如下命令编译

    `cmake ..`

    `make`

    Execute it.

    执行

    `./login`