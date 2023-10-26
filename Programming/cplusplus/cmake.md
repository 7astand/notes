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

- GLOB 和 GLOBAL_RECURSE

    src/test/*.cpp

    GLOB src/*.cpp 不能匹配到
    GLOB_RECURSE src/*.cpp 可以匹配到

    

    file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
    CONFIGURE_DEPENDS 参数可以在添加新文件是时不用重新config
    cmake -B build 是config 操作
    有文件变动时如果有 CONFIGURE_DEPENDS 时会自动执行config操作的

    findxxx.cmake
    xxxconfig.cmake

    fin_package(xxx MODULE REQUIRED)
    只搜索 findxxx.cmake

    find_package(xxx CONFIG REQUIRED)
    只搜索 xxxconfig.cmake 形式

    CMAKE_MOUDLE_PATH 这个路径是搜索 findxx.cmake 的路径

    cmake -B build -DQT5_DIR="/opt/lib/qt/"
    