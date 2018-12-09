#ifndef STYLE_H
#define STYLE_H

#include <QString>

const QString Main_Widget_Style                   (
                                                   "QWidget{"
                                                    "background-color: qlineargradient(spread:reflect, x1:1, y1:0.1, x2:1, y2:0.9,stop:0.223242 rgba(220, 120, 65, 255),"
                                                    "stop:0.902141 rgba(255, 255, 255, 255));"
                                                   "}"
                                                  );
const QString Titel_Widget_Style                  (
                                                   "QWidget{"
                                                    "background-color: rgba(220, 120, 65, 255);"
                                                    "color: rgb(255, 255, 255);"
                                                   "}"
                                                  );
const QString Work_Area_Style                     (
                                                   "QWidget{"
                                                    "background-color: rgb(255, 255, 245);"
                                                    "color: rgb(150, 80, 0);"
                                                   "}"
                                                  );
const QString Basic_Text_Style                    (
                                                   "QWidget{"
                                                    "color: rgb(50, 20, 20);"
                                                   "}"
                                                   "QWidget:disabled{"
                                                    "color: rgb(100, 100, 100);"
                                                   "}"
                                                   "QWidget:enabled{"
                                                    "color: rgb(50, 20, 20);"
                                                   "}"
                                                  );
const QString Background_Green                    (
                                                   "QWidget{"
                                                   "background-color: rgb(186, 229, 202);"
                                                   "}"
                                                  );
const QString Background_Grey                     (
                                                   "QWidget{"
                                                    "background: rgba(0,0,0,0);"
                                                   "}"
                                                  );
const QString Background_Red                      (
                                                   "QWidget{"
                                                    "background: rgb(253,184,179);"
                                                   "}"
                                                  );
const QString Background_White                    (
                                                   "QWidget{"
                                                    "background: rgb(255,255,255);"
                                                   "}"
                                                   "QWidget:disabled{"
                                                    "background: rgba(0,0,0,0);"
                                                   "}"
                                                   "QWidget:enabled{"
                                                    "background: rgb(255,255,255);"
                                                   "}"
                                                  );
const QString Text_Green                          (
                                                   "QWidget{"
                                                   "color: rgb(0, 115, 10);"
                                                   "}"
                                                   "QWidget:disabled{"
                                                    "color: rgb(100, 100, 100);"
                                                   "}"
                                                   "QWidget:enabled{"
                                                    "color: rgb(0, 115, 10);"
                                                   "}"
                                                  );
const QString ScrollBar_Style                     (
                                                   "QScrollBar:vertical {"
                                                    "width: 10px;"
                                                    "height: 10px;"
                                                   "}"
                                                   "QScrollBar:horizontal {"
                                                    "width: 10px;"
                                                    "height: 10px;"
                                                   "}"
                                                  );
const QString Basic_Buttons_Style                 (
                                                   "QPushButton{"
                                                    "border: none;"
                                                   "}"
                                                   "QPushButton:disabled {"
                                                    "border: none;"
                                                    "color: rgb(100, 100, 100);"
                                                   "}"
                                                   "QPushButton:enabled {"
                                                    "border: none;"
                                                    "color: rgb(150, 80, 0);"
                                                   "}"
                                                   "QPushButton:hover {"
                                                    "border: none;"
                                                    "color: rgb(220, 119, 64);"
                                                    "text-decoration: underline;"
                                                   "}"
                                                   "QPushButton:pressed {"
                                                    "border: none;"
                                                    "color: rgb(50, 20, 20);"
                                                   "}"
                                                  );

const QString Buttons_Style                       (
                                                   "QPushButton{"
                                                    "border: none;"
                                                   "}"
                                                   "QPushButton:disabled {"
                                                    "border: none;"
                                                    "background: rgb(243,211,194);"
                                                   "}"
                                                   "QPushButton:enabled {"
                                                    "border: none;"
                                                    "background: rgb(240, 196, 172);"
                                                   "}"
                                                   "QPushButton:hover {"
                                                    "border: none;"
                                                    "background: rgb(235, 179, 148);"
                                                   "}"
                                                   "QPushButton:pressed {"
                                                    "border: none;"
                                                    "background: rgb(240, 196, 172);"
                                                   "}"
                                                  );
#endif // STYLE_H
