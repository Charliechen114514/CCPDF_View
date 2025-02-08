# README

![(Language)](https://img.shields.io/badge/language-c++>=17-brightgreen)![Language](https://img.shields.io/badge/Tools-Qt>=6.6-brightgreen)![STILL_IN_MAINTAINS](https://img.shields.io/badge/Maintains-YES-red)![License](https://img.shields.io/badge/license-GNUv3-yellow)  ![Documentation](https://img.shields.io/badge/documentation-yes-brightgreen)



![GUI](https://img.shields.io/badge/Introduction-What_is_CCPDF__View-blue)

​	CCPDFView_Beta是一个简洁轻量的PDF阅读器程序，目前仍然处于开发阶段！



![GUI](https://img.shields.io/badge/GUI_-Example-blue)

​	这是一个打开了一本FreeRTOS示例文件的GUI全貌图像

![image-20240715210652898](./assets/README_FirstPage.png)



![GUI](https://img.shields.io/badge/Details-What_can_CCPDF__View_Do-yellow)

## 功能简单浏览

目前支持的功能：

> :book: 支持常规的阅读
>
> > :arrow_lower_right: 基本的pdf页码跳转，阅读导航
> >
> > :notebook: 日志支持的PDF记忆功能，对于用户没有关闭的文档下次打开自动定位到上一次浏览所在位置
>
> :mag_right: PDF浏览放大：
>
> > :mag_right: 支持PDF放大和缩小
> >
> > :computer_mouse: 当PDF放的相对较大，鼠标可以右键进行拖拽移动
>
> :link: PDF服务
>
> > :link: 解析原生的PDF书签且双击支持跳转，以便快速浏览章节
> >
> > :tanzania: 非图像渲染支持原生的文本信息提取
> >
> > :link:支持PDF内部的检索与项目跳转
> >
> 
>:books: PDF书库
> 
>> :books: 支持书库浏览，方便的在程序内部遨游一个文件夹下的所有PDF程序
> >
> > :heavy_check_mark: 支持在给定目录下检索PDF的Title
> 
>:electric_plug: ​插件操作：
> 
>> :electric_plug: 支持使用Tesseract OCR插件，使用关联项目的TesseractWrapper.dll作为DLL插件的兼容支持
> >
> > :electric_plug: 支持用户侧自由的翻译程序兼容，只需要用户提供翻译EXE文件且满足文件名称规范即可在程序内部使用翻译插件
> >
> > :electric_plug: 翻译模块支持自动翻译了，当您上下浏览PDF的时候，软件将会依照页面变化自动触发对插件程序的调用！无论单双页
> 
>:monorail: Qt主题自由注册：
> 
>> :monorail: 支持使用所有带有QSS格式的Qt主题，用户只需指定主题的QSS文件，便可以加载主题并记忆保留，直到用户删除为止。
> 
>:closed_book: 多页阅读模式：
> 
>> :closed_book: 现在我们的PDF运行程序支持多页阅读，用户可以自由的使用鼠标浏览PDF

