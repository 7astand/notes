# doxygen

[doxygen 下载]:(https://www.doxygen.nl/download.html)
[doxygen 配置使用]:(https://my.oschina.net/hava/blog/110874)
[doxygen 配置选项官网]:(https://www.doxygen.nl/manual/config.html)
[doxygen 配置选项]:(https://my.oschina.net/learnbo/blog/801966)
[doxygen 注释风格]:(https://my.oschina.net/zhfish/blog/35422)

## 用法

[doxygen 下载]
[doxygen 配置使用]
[doxygen 配置选项官网]
[doxygen 配置选项]

## 给代码添注释

[doxygen 注释风格]

```markdown
并不是所有的注释都会被收入文档，Doxygen 支持的常用的注释风格有：

在全局作用域，类前或函数前注释
/**     注释的内容       */
/*!     注释的内容       */
文件成员，类成员，结构体成员，共同体成员，枚举成员或函数参数后注释
int a; /**<      注释的内容        */
int a; /*!<      注释的内容        */
其它注释风格见：http://doxygen.nl/manual/docblocks.html

Doxygen 常用的注释标记（标记以 / 或 @ 开头表示）：

添加简单描述
\brief 简要描述
添加详细描述
@details 详细描述
添加类信息
@class 类名 类所在的文件 类所在的文件（可包括路径） 
添加结构体信息
@struct 结构体名 结构体所在的文件 结构体所在的文件（可包括路径）
添加参数说明
@param [in]  输入参数名 说明
@param [out] 输出参数名 说明
添加返回说明
@return 返回说明
添加返回特定值说明
@retval 特定值 特定返回值说明
添加异常说明
@exception 异常类型 异常说明
添加代码
@code
...代码...
@encode
添加计划做的事儿
@todo 计划做的事
添加参考
@see 参考其它
添加过时说明
@deprecated 过时说明
添加 bug 说明
@bug "bug 说明"
添加例子
@example 例子文件名
添加警告信息
@warning 警告信息
添加开始使用的版本
@since 版本
添加注意事项
@note 注意事项
```
## c++ 注释风格

////
/// 下面是一个含有两个参数的函数的注释说明（简述）   
///    
///     这里写该函数的详述信息    
///     @param a 被测试的变量（param描述参数）    
///     @param s 指向描述测试信息的字符串    
///     @return    测试结果 （return描述返回值）   
///     @see    Test()    （本函数参考其它的相关的函数，这里作一个链接）  
///     @note    (note描述需要注意的问题)    
int testMe(int a,const char *s);  
5.4.8       枚举变量的注释示例