/**
 * @author 作者信息
 * @date 日期
 * @version 版本
 * @brief 简明描述
 * @attention 注意
 */

#include <iostream>

namespace rededa
{

/**
 * @brief 这里描述类的功能和用法
 *  
 * 下面写一个例子example 使用方法
 */

class doxygen
{
private:
    int data;
    /* data */
public:
    doxygen(/* args */);
    ~doxygen();
/**
 * @brief 描述函数的功能
 * @param 参数
 * @return 该函数的返回值
 */
    int getattribute(int a);

};

doxygen::doxygen(/* args */)
{
}

doxygen::~doxygen()
{
}
 
} // namespace rededa  这里命名空间结束后注释加上命名空间的名字
