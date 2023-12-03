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
    1. 固定宽高
        > setFixdSize(width,height);
    2. 设置水平标题头自动缩进
        > horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    3. 设置垂直标题头自动缩进
        > verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        >horizontalHeader() verticalHeader() 这两个方法得到的是QHeaderView 类型的对象,调用这个对象的 setSectionResizeMode() 方法
    4. 隐藏垂直标题头
        > verticalHeader()->hide() 实际上调用的是QHeaderView 的 hide() 方法
    5. 设置不可编辑
        > setEditTriggers(QAbstractItemView::NoEditTriggers);
    6. QTableWidget 继承自 QAbstractItemView
        > QAbstractItemView 的 setEditTriggers 方法可以设置是否可以编辑,只要继承自 QAbstractItemView 的其他控件都可以设置为是否可编辑,而且方法一致
    7. 设置每个单元格的文字居中显示
        > 通过 item(row,column) 得到单元格 QTableWidgetItem 的对象 再使用 QTableWidget 的 setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter) 方法
- QTableView
    设置行和列只能在 Model 中设置,我的理解是因为 QTableView 是个显示数据的 View,只有有数据才能生成行和列

- QPushbutton
    设置背景色,设置选中状态,划过状态的字体颜色

    ```cpp
    pushbutton->setStyleSheet("QPushButton{background-color:green}"
                              "QPushButton:checked{background-color:red}"
                              "QPushButton:hover{background-color:blue}");
    ```

## QDialog

- 窗口的模态和非模态
  - 使用 `exec()` 显示一个模式对话框,锁住程序直到用户关闭这个对话框为止,函数返回一个 DialogCode 结果,在对话框弹出期间，用户不可以切换同程序下的其它窗口，直到该对话框被关闭
  - 使用 `show()` 显示一个非模式对话框。控制权即刻返回给调用函数。弹出窗口是否模式对话框，取决于modal属性的值

## QWidget

- widget window 窗体主窗口关闭后,子窗口还存在
  先说结论 对子窗体设置一个属性 `setAttribute(Qt::WA_QuitOnClose,false);`
  每个 `Qt::Window` 类型的 widget 都有,默认都为 `true`

## QListWidget

- listwidget 中的项目是 listwidgetitem 
  想要删除项目的话,需要使用 `QListWidgetItem * takeItem(int row)` 这个方法返回一个 QlistWidgetItem* 想要彻底删除它需要手动释放这个内存使用 delete
  需要注意的是这个方法传入的是个行号
- listwidget 有排序功能,默认是关闭的
  使用 `void setSortingEnable(bool)` 开启,开启后还可以使用 `void sortItems(Qt::SortOrder order = Qt::AscendingOrder)` 方法进行排序
- listwidget 有查找指定的 listwidgetitem 功能 使用 `QList<QListWidgetItem *> findItems(const QString &text, Qt::MatchFlags flags) const` 查找指定的 item,可以有多种匹配模式,

## QFileInfo 和 QDir

- QFileInfo 是文件相关的类,存储的有文件的相关信息,后缀,文件名,文件路径等信息
  `bool exists() const` 方法返回文件是否存在
  `QString baseName() const` 方法返回文件名不带后缀
  `qint64 size() const` 返回文件大小
  `QString QFileInfo::fileName() const` 返回不包括路径的文件名
  `QString QFileInfo::filePath() const` 返回文件的路径,可以使相对路径也可以是绝对路径
  `QString QFileInfo::suffix() const` 返回文件的后缀名,返回最后一个 `.` 之后 (但不包括) 的所有字符
- QDir 能得到指定路径的文件信息
  `void setPath(QString path)` 设置路径信息
  `void setNameFilters(const QStringList &nameFilters)` 设置文件筛选器
  `QFileInfoList entryInfoList(QDir::Filters filters = NoFilter, QDir::SortFlags sort = NoSort) const` 得到所设置的指定路径和指定文件筛选器后的 QFileInfoList
