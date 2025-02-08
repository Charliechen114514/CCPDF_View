# README

![(Language)](https://img.shields.io/badge/language-c++>=17-brightgreen)![Language](https://img.shields.io/badge/Tools-Qt>=6.6-brightgreen)![STILL_IN_MAINTAINS](https://img.shields.io/badge/Maintains-YES-red)![License](https://img.shields.io/badge/license-GNUv3-yellow)  ![Documentation](https://img.shields.io/badge/documentation-yes-brightgreen)



![GUI](https://img.shields.io/badge/Introduction-What_is_CCPDF__View-blue)

CCPDFView_Seta is a concise lightweight PDF reader program that is currently in the testing phase.

![GUI](https://img.shields.io/badge/GUI_-Example-blue)

![image-20240715210652898](./assets/README_FirstPage.png)

![GUI](https://img.shields.io/badge/Details-What_can_CCPDF__View_Do-yellow)

## Functionalities Current

### Currently supported features:

> :book: Reading:
>
> > :arrow_lower_right: Basic PDF page redirection, reading navigation
> >
> > :notebook: Memory Functionalities supported by logging automatically locates the last browsing location for documents that the user has not closed next time they open them
>
> :mag_right: Basic Zooming
>
> > :mag_right: Support Zoom in and Zoom Out 
> >
> > :computer_mouse: Support Mouse Dragging when PDF is zooming in a relavent large case
>
> :link:PDF Service
>
> > :link:Parse native PDF bookmarks and support jumping by double-clicking for quick browsing of chapters
> >
> > :tanzania: native text information extraction for Non image rendering based PDF supports!
> >
> > :link:Support internal PDF retrieval and model redirection
> >
> 
>:books:PDF Library
> 
>>:books:Support library browsing, easily navigate through all PDF programs in one folder within the program
> >
> >:heavy_check_mark: Support searching for PDF titles in a given directory
> 
>:electric_plug: Plugin operation:
> 
>>:electric_plug: Support the use of Tesseract OCR plugin and TesseractWrapper.dll associated with the project as compatibility support for DLL plugin
> >
> >:electric_plug: Supporting user side free translation program compatibility, users only need to provide a translation EXE file and meet the file name specification to use the translation plugin inside the program
> >
> >:electric_plug: Support Auto Run For Translations,When you browse the PDF up and down, the software will automatically trigger the call to the plugin program according to the page changes! no matter if is MultiPage or SinglePage
> 
>:monorail: Qt Theme Free Registration:
> 
>>:monorail: Support the use of all Qt themes with QSS format. Users only need to specify the QSS file of the theme to load it and remember it until it is deleted by the user.
> 
>:closed_book: MultiPage Supports:
> 
>> :closed_book: Users now can browse PDF In MutiPage
