# sed

    处理文本

sed 's/find/replace/g'

sed默认全部输出
-n 之输出匹配的行
-p 输出
-f 指定（输出）文件

sed '1,$s/my/your/g' a.txt
替换 1行到最后一行 的my 为 your 全部替换