# GDB

gdb 调试

- 命令

    1. gdb 可执行程序
   
       开始调试

       或者程序已经开始运行了需要先查到程序的进程 id
       以 linux 为例子
       使用 ps - A | grep main 
       查询 main 函数的进程 id
       或者使用 pidof main 
       查询 main 函数的进程信息
       找到之后需要使用 sudo 管理员命令来运行 gdb 命令
       因为 进入 gdb 命令之后需要使用 attach 来访问得到的这个进程 id 号
       如果不使用 sudo 管理员权限来运行 gdb 的话会出现权限错误的提示
       之后使用 attach xxx 
       开始调试已经运行的进程，他会把该进程已经加载的一些动态库和符号重新加载，之后就能正常的进行调试了。

       进入 gdb 后进行交互界面

    2. r 
       
       运行程序
       
       r 还会自动执行上个 gdb 后面的命令 
       如 gdb ls
       r -l
       会出现 ls -l 的效果

    3. bt 
       
       栈回溯，可以看到调用的堆栈信息

    4. l 
       
       查看上下文

       > l name

       name 可以是函数名等
       可以查看 name 前后的上下文

    5. b 
       
       > b main:3

       b 后可以跟文件的行数，格式为 文件名：行数
       可以跟函数名等，表示在此函数处添加一个断点
       b 可以用来添加条件断点
       b name if a!=0
       表示 如果 a 的值不等于 0 时才会在 name 处添加断点

    6. tb 
       
       tb 表示添加一个临时的断点
       只在第一次进入这个断点时会生效

    7. p
       
       > p cmd

       p 后可以执行命令并进行打印
       p 可以执行函数 可以用来在调试模式下该程序中变量的值
       p 也可以直接跟上变量的名字，打印该变量的值
       p 后跟表达式可以执行表达式

    8. watch
       
       > watch variable
       
       varibale 表示变量
       可以观察该变量值的变化，每次 varibale 变化时都会暂停
       与这个命令有关的几个变种为
       awatch,rwatch
       awatch a 表示 access 表示每次访问这个变量时都会暂停，可以观察这个变量变化前后的值
       rwatch r 表示 read 每次访问这个变量时程序都会暂停

    9. n
      
       next 的缩写

       n 表示继续进行下一行

    10. s
       
        s 表示进入步入该函数，变量内部查看

    11. c
       
        c 表示 continue 继续进行下去（可能是到下一个断点处）

    12. gdb xxx -ex "cmd"

        进行调试时会加上后面的参数执行


- 三方支持库

    https://github.com/bombela/backward-cpp

    能在程序崩溃时打印出堆栈信息

- 保存断点信息

    保存断点信息可以再次加载使用
    保存一个文件为 name.gdb 的文件
    内容大概为
    b main
    watch varibale
    这些，然后在 gdb 中使用
    sourch name.gdb 
    gdb 回加载文件中的一些调试断点信息进行调试