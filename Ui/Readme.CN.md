# README

​	Ui文件夹是核心组件的Ui交互和GUI界面所在的地方

```
D: 
│   Readme.CN.md
│   Readme.md
│
├───ActionMonitor#包括事件句柄函数
│   ├───KeyboardMonitor  #窗口键盘监视器
│   └───MouseMonitor #窗口鼠标事件监视器
├───CCPDF_BookLibraryManager #图书馆阅读小工具管理器
│   └───FileSystemModel #当前使用的文件系统视图
├───CCPDF_BookLibrary小部件#库小部件定义
├───CCPDF_BookMark #书签经理
├───CCPDF_BookMarkWidget#书签小部件
├───CCPDF_HistoryAction#历史菜单动作定义
├───CCPDF_HistoryActionHelper#HistoryMenu动作助手，帮助确保
├───CCPDF_HistoryTableWidgetController#历史表管理器
├───CCPDF_LinkListWidgetManager#PDF链接小部件管理器
├───CCPDF_LinkWidget#PDF链接小部件在此处定义
├───CCPDF_MdiArea#自定义MdiArea的过载中间区域
├───CCPDF_MdiSubWindow#自定义MdiSubWindow的MdiSubWindow过载
├───CCPDF_SearchDelegate #PDF 搜索小部件视图代理
├───CCPDF_earchManager   #PDF搜索小部件管理器
├───CCPDF_SearchWidget #PDF搜索小部件在此处定义
├───CCPDF_ThemeAction #主题行动定义
├───CCPDF_ThemeActionHelper #像CCPDF_HistoryActionHelper一样执行：）
├───MainWindow #主窗口，应用程序显示页面
├───Plugins	 #为插件支持而编译
│   ├───OCR#OCR小部件和管理器支架，但现在仅支持谷歌Tesseract！
|   │
│   └───Translations #翻译支持，目前支持可执行程序的插件。
├───ThemeController#主题控制器，用户可以通过提供QSS来选择主题
├───WindowBuild #窗口配置
└───WindowEventHelper #帮助编写前面提到的组件
```

