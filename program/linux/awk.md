# awk

    处理格式化过的文本，类似脚本语言
    有一些预定一变量
    NF 最后一个字段输

BEGIN{}{

}END{
    
}

awk -F , {print $NF} filename

    F 表示分隔符是 ,
    $NF 表示最后一个字段
    filename 要处理的文件名

分为模式和处理行
