# 插件：OCR

​	提示：Windows Only！当然这里给出TesseractWrapper的项目地址：

>[Charliechen114514/TesseractWrapper (github.com)](https://github.com/Charliechen114514/TesseractWrapper)

​	任何Linux user需要自己尝试编译配齐Tesseract和Leptopia的依赖，并确保自己的Tesseract Wrapper可以正常的解析到自己的数据。如果您不想使用OCR功能，需要自行下载源码禁用CCPDFView_Beta.pro下的宏定义：SUPPORT_TRANSLATION

> 提示：在Linux下符号解析错误将会导致软件直接崩溃，请在调试状态下完成对Tesseract Wrapper的依赖配置

​	只有当定位到动态执行文件且正确解析了所有TesseractWrapper内部的符号才有可能正常的进行运行！
