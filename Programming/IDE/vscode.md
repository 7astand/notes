# vscode

## 配置环境

- windows

使用 Msys2 来配置环境

在 `msys64\etc\pacman.d` 中找到 `mirrorlist.mingw32` `mirrorlist.mingw64` `mirrorlist.msys` 三个文件
把一些国内源放在最上边,比如 清华源-tinghua,中国科技大学源-ustc,上海交通大学源-sjtu.

安装依赖

```shell
pacman -S git
pacman -S boost
pacman -S  mingw-w64-x86_64-cmake
pacman -S  mingw-w64-x86_64-gcc
pacman -S  mingw-w64-x86_64-toolchain
pacman -S  mingw-w64-x86_64-qt5
```

vscode 配置环境
配置文件 `.vscode/c_cpp_properties.json`

```jason
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "D:/Programs/Programming/MSYS2/mingw64/include/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "D:/Programs/Programming/MSYS2/mingw64/bin/gcc.exe",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64",
            "configurationProvider": "vector-of-bool.cmake-tools",
            // "compileCommands": "${workspaceFolder}/build/compile_commands.json"
        }
    ],
    "version": 4
}
```

- Linux

vscode 配置 c++ 开发环境
配置文件 `.vscode/c_cpp_properties.json`

```json

```
