# pybind11
[pybind11参考官方文档](https://pybind11.readthedocs.io/en/stable/basics.html)

- 将c++的类和方法等包装成python的moudle 等 使用

- c++项目设置

    添加 pybind11 library

    cmake中添加

    project(pname)
    add_subdirectory(pybind11)
    pybind11_addmoudle(pname test.cpp)

    test.cpp 
    中需要绑定代码
    将c++中函数和类等绑定到moudle中

    test.cpp

    ```cpp
        #include <pybind11/pybind11.h>
        using namespace py = pybind11

        int add(int a,int b){
            return a+b;
        }

        PYBIND11_MOUDLE(pname ,m){
            m.doc()="pybind11 test doc";
            m.def("add",&add,"a add function");
        }

- pybind11 语法

    绑定class

    ```cpp
        using namespace py =pybind11;

        struct Pet{
            Pet(const string& name):name(name){}
            string getName(){return name}
            void setName(string name){name=name}
            const string name;
        }

      PYBIND11_MOUDLE(Pet,m){
        m.doc()="Pet doc";
        py::class_<Pet>(m,"Pet")
            .def(py::init<const string&>())
            .def("setName",&Pet::setName)
            .def("getName",&Pet::getName);
      }

    ```



    ```