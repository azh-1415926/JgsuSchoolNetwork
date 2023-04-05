# JgsuSchoolNetwork
Applicable to Jinggangshan University campus network login.

适用于井冈山大学校园网登录

Recommended use AllPlatforms.

推荐使用 AllPlatforms，为最新版本

**Windows**

1. gcc

    Library file `ws2_32.lib` is required for compilation.

    依赖库文件 `ws2_32.lib`

    We can compile with the following command.

    编译命令如下

    `gcc client.c myhttp.c mysocket.c -lws2_32 -o login`

    or

    `gcc *.c -l ws2_32 -o login`

**Linux**

1. gcc

    编译命令如下

    `gcc client.c myhttp.c mysocket.c -o login`

    or

    `gcc *.c -o login`