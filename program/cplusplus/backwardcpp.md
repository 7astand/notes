# backward

cpp 中的栈回溯库

github 仓库地址
[backward](https://github.com/bombela/backward-cpp)

- 使用方式

    将库目录放在项目同级根目录

    在项目的入口 cmake 中添加

    ```cmake
    `add_subdirectory(backward-cpp)
    ```
    
    主程序添加完可执行程序后

    ```cmake
    add_executable(main main.cpp)
    target_sources( main PUBLIC ${BACKWARD_ENABLE})
    add_backward(main)
    ```

    运行主程序 main 当出现崩溃时就会自动打印出崩溃时堆栈的相关信息