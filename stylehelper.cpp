#include "stylehelper.h"


QString StyleHelper::getStartButtonsStyle()
{
    return "QPushButton{"
            "color:#0f0;"
            "}";

}

QString StyleHelper::getMainWidgetStyle()
{
    return "background-color:"
           "rgb(255, 255, 255);";
}

QString StyleHelper::getXStyle()
{
    return "QPushButton{"
           "    background-color: #8C8C8C;"
//           "    background-image: url(:/res/stocks/X_small.png);"
           "    background-repeat: no-repeat;"
           "    background-position: center center;"
           "    border:1px solid #8C8C8C;"
           "    border-top-left-radius:5px;"
           "    border-bottom-left-radius:5px;"
           "}";
}

QString StyleHelper::getOStyle()
{
    return "QPushButton{"
           "    background-color: #8C8C8C;"
//           "    background-image: url(:/res/stocks/О_small.png);"
           "    background-repeat: no-repeat;"
           "    background-position: center center;"
           "    border:1px solid #8C8C8C;"
           "    border-left:none;"
           "    border-top-right-radius:5px;"
           "    border-bottom-right-radius:5px;"
           "}";
}

QString StyleHelper::getXActiveStyle()
{
    return "QPushButton{"
           "    background-color: #D1D1D1;"
//           "    background-image: url(:/res/stocks/X_small.png);"
           "    background-repeat: no-repeat;"
           "    background-position: center center;"
           "    border:1px solid #D1D1D1;"
           "    border-top-left-radius:5px;"
           "    border-bottom-left-radius:5px;"
           "}";
}

QString StyleHelper::getOActiveStyle()
{
    return "QPushButton{"
           "    background-color: #D1D1D1;"
//         "    background-image: url(:/res/stocks/О_small.png);"
           "    background-repeat: no-repeat;"
           "    background-position: center center;"
           "    border:1px solid #D1D1D1;"
           "    border-left: none;"
           "    border-top-right-radius:5px;"
           "    border-bottom-right-radius:5px;"
           "}";
}


QString StyleHelper::getBlankButtonStyle()
{
   return
    "QPushButton {"
        "   background-color: white;"
        "   border-style: outset;"
        "   border-width: 0px;"
        "   border-radius: 5px;"
        "   border-color: beige;"
    "}"

    "QPushButton:pressed {"
        "   background-color: rgb(176, 176, 176);"
        "   border-style: inset;"
    "}"

    "QPushButton:hover:!pressed {"
        "   background-color: rgb(232, 232, 232);"
        "   border-style: inset;"
    "}";

}

QString StyleHelper::getGiveUpButtonStyle()
{
    return
     "QPushButton {"
         "  background-color: rgb(244, 144, 143);"
         "   border-style: outset;"
         "   border-width: 0px;"
         "   border-radius: 5px;"
         "   border-color: beige;"
     "}"

     "QPushButton:pressed {"
         "  background-color: rgb(210, 128, 127);"
         "   border-style: inset;"
     "}"

     "QPushButton:hover:!pressed {"
         "  background-color: rgb(210, 128, 127);"
         "   border-style: inset;"
     "}";
}

QString StyleHelper::getTieButtonStyle()
{
    return
     "QPushButton {"
         "  background-color: rgb(100, 125, 161);"
         "   border-style: outset;"
         "   border-width: 0px;"
         "   border-radius: 5px;"
         "   border-color: beige;"
     "}"

     "QPushButton:pressed {"
         "  background-color: rgb(86, 101, 120);"
         "   border-style: inset;"
     "}"

     "QPushButton:hover:!pressed {"
         "  background-color: rgb(86, 101, 120);"
         "   border-style: inset;"
     "}";
}

QString StyleHelper::getXFieldStyle()
{
    return
     "QPushButton {"
         "  background-color: white;"
         "  border-image:url(:/res/stocks/X.png);"
         "  background-position: center center;"
         "  background-repeat: no-repeat;"
         "  border-style: outset;"
         "  border-width: 0px;"
         "  border-radius: 5px;"
         "  border-color: beige;"
     "}"

     "QPushButton:pressed {"
         "  background-color: rgb(176, 176, 176);"
         "  border-style: inset;"
     "}"

     "QPushButton:hover:!pressed {"
         "  background-color: rgb(232, 232, 232);"
         "  border-style: inset;"
     "}";
}

QString StyleHelper::getOFieldStyle()
{
    return
     "QPushButton {"
         "  background-color: white;"
         "  border-image:url(:/res/stocks/O.png);"
         "  background-position: center center;"
         "  background-repeat: no-repeat;"
         "  border-style: outset;"
         "  border-width: 0px;"
         "  border-radius: 5px;"
         "  border-color: beige;"
     "}"

     "QPushButton:pressed {"
         "  background-color: rgb(176, 176, 176);"
         "  border-style: inset;"
     "}"

     "QPushButton:hover:!pressed {"
         "  background-color: rgb(232, 232, 232);"
         "  border-style: inset;"
     "}";
}

QString StyleHelper::getXWinFieldStyle()
{
    return
     "QPushButton {"
         "  background-color: rgb(92, 200, 92);"
         "  border-image:url(:/res/stocks/X.png);"
         "  background-position: center center;"
         "  background-repeat: no-repeat;"
         "  border-style: outset;"
         "  border-width: 0px;"
         "  border-radius: 5px;"
         "  border-color: beige;"
     "}"

     "QPushButton:pressed {"
         "  background-color: rgb(67, 148, 67);"
         "  border-style: inset;"
     "}"

     "QPushButton:hover:!pressed {"
         "  background-color: rgb(67, 148, 67);"
         "  border-style: inset;"
     "}";
}

QString StyleHelper::getOWinFieldStyle()
{
    return
     "QPushButton {"
         "  background-color: rgb(92, 200, 92);"
         "  border-image:url(:/res/stocks/O.png);"
         "  background-position: center center;"
         "  background-repeat: no-repeat;"
         "  border-style: outset;"
         "  border-width: 0px;"
         "  border-radius: 5px;"
         "  border-color: beige;"
     "}"

     "QPushButton:pressed {"
         "  background-color: rgb(67, 148, 67);"
         "  border-style: inset;"
     "}"

     "QPushButton:hover:!pressed {"
         "  background-color: rgb(67, 148, 67);"
         "  border-style: inset;"
     "}";
}

QString StyleHelper::getXLoseFieldStyle()
{
    return
     "QPushButton {"
         "  background-color: rgb(244, 144, 143);"
         "  border-image:url(:/res/stocks/X.png);"
         "  background-position: center center;"
         "  background-repeat: no-repeat;"
         "  border-style: outset;"
         "  border-width: 0px;"
         "  border-radius: 5px;"
         "  border-color: beige;"
     "}"

     "QPushButton:pressed {"
         "  background-color: rgb(210, 128, 127);"
         "  border-style: inset;"
     "}"

     "QPushButton:hover:!pressed {"
         "  background-color: rgb(210, 128, 127);"
         "  border-style: inset;"
     "}";
}

QString StyleHelper::getOLoseFieldStyle()
{
    return
     "QPushButton {"
         "  background-color: rgb(244, 144, 143);"
         "  border-image:url(:/res/stocks/O.png);"
         "  background-position: center center;"
         "  background-repeat: no-repeat;"
         "  border-style: outset;"
         "  border-width: 0px;"
         "  border-radius: 5px;"
         "  border-color: beige;"
     "}"

     "QPushButton:pressed {"
         "  background-color: rgb(210, 128, 127);"
         "  border-style: inset;"
     "}"

     "QPushButton:hover:!pressed {"
         "  background-color: rgb(210, 128, 127);"
         "  border-style: inset;"
     "}";
}
