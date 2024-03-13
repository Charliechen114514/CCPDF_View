# CCPDF_View
  Access the binaries for Windows by Releasing Part
## Intro's

​	This is the repo for CCPDF_View, a PDF Reader contains Tesseract OCR. Incluings are the releases that is at least portable in Windows 10 and Window 11(Sadly, Linux Version is required to compile by yourself :( )

​	CCPDF_View is free toaccess by anyone who want's to use it. The base sources are

>  OCR：Tesseract5：
>
> [tesseract-ocr/tesseract: Tesseract Open Source OCR Engine (main repository) (github.com)](https://github.com/tesseract-ocr/tesseract)
>
> Styles：
>
> `[QDarkStyle]:`https://github.com/ColinDuquesnoy/QDarkStyleSheet
>
> `[QSS]:` https://github.com/GTRONICK/QSS.git
>
> PDF Reading Core:
>
> QPDF[Qt PDF](https://doc.qt.io/qt-6/qtpdf-index.html)

​	click these links for learning more about them!

## Compiles

> In Windows, what you need is to use Mingw73_64 Or MSVC19 to Compile the Project. The Execution requires the Private Sources libOCRPack, the source is a lib given in the ./sources/OCRPack/, what you are supposed to do at first is to modify according to your need, compile it to the DEBUG/Releasing lib, put it in the ./source/CCPDF_View/ocr/libs, the linking step accuires the lib in such a path.

## Release 2.0

​	A New Published and a more user friendly releases are published here in March 13th 2024.

![image-20240303190652420](./doc/2024-03-13 211303.png)

​	In this releases, we:

> Add:
>
> > 1. Add History Menu to check the history reading PDF much more convinient!
> > 2. Allowed Searching in PDF, accepted quick jump to the target findings
> > 3. Allowed Searching target PDF in the libraries sections
> > 4. Allowed loading BookMarks in PDF, which allowed better jumps.
> > 5. Allowed Direct Fetching Texts instead of OCR, OCR Now has been an extra-sources in current Version, Download the extra-sources in the Releases for tags
>
> Fixed:
>
> > 1. Better Fixing in Notes binding
> > 2. Avoid Duplicated Error MessageBox
> > 3. Better Fixing in related updating when dragging PDF into the Applications
> > 4. Depatched the OCR Sources as optional when downloading Releases
