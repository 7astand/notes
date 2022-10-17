# Cmake

- 链接库或者文件夹活着文件时的选项

    target_include_categories
    target_include_source
    target_include_directory
    target_link_library

    这些命令时 会用到权限控制修饰

    command destination public source

    PUBLIC 
    INTERFACE 依赖于destination目标的目标需要source
    PRIVATE


- 使用