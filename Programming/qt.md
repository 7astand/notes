# QT

## delegate

- comboxdelegate

 Qt 中视图与模型绑定时,模型必须用 new 来创建, 否则初始化时候,视图没有数据显示,或者后期视图不能随着模型的改变而改变.
 原因分析: 可能是局部变量的生命周期问题, new 创建的变量在堆空间中,不手动释放的话,会一直存在. 如果不 new 一个 model , 把 model 放在类的成员变量中, 视图也可以正常显示数据.(最后一条未验证)

 ```cpp
    
 ```

## QTableWidget 和 QTableView

- 区别
    QTableWidget 继承自 QTableView

- QTablewidget
    可以在ui文件中设置行和列
    固定宽高 setFixdSize(width,height);
    设置水平标题头自动缩进 horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    设置垂直标题头自动缩进 verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader() verticalHeader() 这两个方法得到的是QHeaderView 类型的对象,调用这个对象的 setSectionResizeMode() 方法
    隐藏垂直标题头 verticalHeader()->hide() 实际上调用的是QHeaderView 的 hide() 方法
    设置不可编辑 setEditTriggers(QAbstractItemView::NoEditTriggers);
    QTableWidget 继承自 QAbstractItemView ,QAbstractItemView 的 setEditTriggers 方法可以设置是否可以编辑,只要继承自 QAbstractItemView 的其他控件都可以设置为是否可编辑,而且方法一致
    设置每个单元格的文字居中显示 通过 item(row,column) 得到单元格 QTableWidgetItem 的对象 再使用 QTableWidget 的 setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter) 方法
- QTableView
    设置行和列只能在 Model 中设置,我的理解是因为 QTableView 是个显示数据的 View,只有有数据才能生成行和列
