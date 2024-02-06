# JgsuSchoolNetwork
Applicable to Jinggangshan University campus network login.

适用于井冈山大学校园网登录

Supports Windows/Linux platforms and needs to be built with cmake

支持 Windows/Linux 平台，需使用 cmake 构建

```bash
​git clone --recursive https://github.com/azh-1415926/JgsuSchoolNetwork.git
# or
​git clone https://github.com/azh-1415926/JgsuSchoolNetwork.git
cd JgsuSchoolNetwork
git submodule update --init  --recursive
```

Create a folder,and switch to it.

创建一个文件夹，并切换到该目录

```bash
cd JgsuSchoolNetwork
mkdir build
cd build
```

We can compile with the following command.

使用如下命令编译

```bash
cmake ..
make
```

Execute it.

执行

```bash
./src/login_C
# or
./src/login_CXX

# sample for Windows
./sample/Windows/login
# sample for Linux
./sample/Linux/login
```