# CCPDF_View

## Intro's

​	这是CCPDF_View的存储仓库！CCPDF_View是一个集成了谷歌的Tesseract OCR PDF阅读器。本仓库包含了该PDF阅读器当前的所有测试版本和正式版本的源代码，以及正式版本的发行可执行文件下载包

1. 软件的发行版，其软件至少可以运行在Windows 10和Windows 11上，遗憾的是Linux版本的发行版需要自行编译
2. 软件的源码，CC PDF wheel对任何人都是开放的各位可以自行拿取源码并使用

​	这里运用到了基本的开源库如下:

>  OCR：Tesseract5：
>
>  [tesseract-ocr/tesseract: Tesseract Open Source OCR Engine (main repository) (github.com)](https://github.com/tesseract-ocr/tesseract)
>
>  Styles：
>
>  `[QDarkStyle]:`https://github.com/ColinDuquesnoy/QDarkStyleSheet
>
>  `[QSS]:` https://github.com/GTRONICK/QSS.git
>
>  PDF Reading Core: [Qt PDF](https://doc.qt.io/qt-6/qtpdf-index.html)
>

​	

## Compiles

> 在Windows下：你所需要做的就是使用MINGW或者是MSVC编译本项目，由于这个应用程序需要本人自己开发封装的库libOCRPack， 这个库的源码在路径中给出./sources/OCRPack/，你所需要做的就是根据自己的需求编译这个库，然后把它放置到路径./source/CCPDF_View/ocr/libs之下。这是因为在编译链接的时候是需要这个库在这个路径下的

## 补丁发行：Release 2.1.0

> 修复了焦点错位需要手动刷新的错误，这里现在支持点击主窗口进行刷新！
>
> 优化使用体验与修复了自Release2.0发行版来引入的加载EditWindow的潜在崩溃错误

## Release 2.0

​	这里发布一个全新的CCPDF_Viewer

![image-20240303190652420](./doc/image2024-03-13211303.png)

​	本版本中：

> 添加了：
>
> > 1. 添加了历史菜单从而更加便捷的阅读PDF
> > 2. 支持在PDF阅读器中搜索PDF，并且可以点击搜索结果实现快速的跳转
> > 3. 支持在书库中搜索PDF标题定位PDF
> > 4. 支持PDF书签，实现章节跳转
> > 5. 支持直接从PDF本身获取文本而不需要OCR, 在发布下的额外资源标签下下载额外的资源
>
> 修复：
>
> > 1. 更好的笔记绑定
> > 2. 移除冗余的错误消息框
> > 3. 修复了PDF拖入时不更新相关信息的bug
> > 4. 剥离PDF的OCR使之成为可选的部分
