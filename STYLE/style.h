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
                                                    "color: rgb(255, 255, 255);"
                                                    "border-top-right-radius: 10px;"
                                                    "border-top-left-radius: 10px;"
                                                    "border-bottom-right-radius: 0px;"
                                                    "border-bottom-left-radius: 0px;"
                                                    "border: solid;"
                                                    "border-top-width: 3px;"
                                                    "border-bottom-width: 1px;"
                                                    "border-right-width: 3px;"
                                                    "border-left-width: 3px;"
                                                    "border-bottom-color: rgba(255,100,100,0%);"
                                                    "border-top-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                    "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                    "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                    "background:"
                                                    "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                    "stop:0 rgba(147,29,18,127),"
                                                    "stop:0.05 rgba(200, 200, 200, 10),"
                                                    "stop:0.5 rgba(200, 200, 200, 130),"
                                                    "stop:0.95 rgba(200, 200, 200, 10),"
                                                    "stop:1 rgba(147,29,18,127));"
                                                   "}"
                                                  );
const QString DownPanel_Widget_Style              (
                                                   "QWidget{"
                                                   "border: solid;"
                                                   "border-bottom-right-radius: 10px;"
                                                   "border-bottom-left-radius: 10px;"
                                                   "border-top-right-radius: 0px;"
                                                   "border-top-left-radius: 0px;"
                                                   "border-bottom-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "background-color: qlineargradient(spread:reflect, x1:0.501391, y1:0.755, x2:0.493423, y2:0, stop:0 rgba(195, 93, 0, 238), stop:1 rgba(255, 255, 255, 0));"
                                                   "}"
                                                  );
const QString Work_Area_Style                     (
                                                   "QWidget{"
                                                    "background-color: rgba(255, 255, 255, 240);"
                                                    "color: rgb(150, 80, 0);"
                                                   "}"
                                                  );
const QString Basic_Text_Style                    (
                                                   "QWidget{"
                                                    "color: rgb(90, 60, 60);"
                                                   "}"
                                                   "QWidget:disabled{"
                                                    "color: rgb(100, 100, 100);"
                                                   "}"
                                                   "QWidget:enabled{"
                                                    "color: rgb(90, 60, 60);"
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
const QString Text_Green_Disabled                          (
                                                   "QWidget{"
                                                   "color: rgb(0, 115, 10);"
                                                   "}"
                                                   "QWidget:disabled{"
                                                    "color: rgb(0, 115, 10);"
                                                   "}"
                                                   "QWidget:enabled{"
                                                    "color: rgb(0, 115, 10);"
                                                   "}"
                                                  );
const QString Text_Red                          (
                                                   "QWidget{"
                                                   "color: rgb(250,60,50);"
                                                   "}"
                                                   "QWidget:disabled{"
                                                    "color: rgb(100, 100, 100);"
                                                   "}"
                                                   "QWidget:enabled{"
                                                    "color: rgb(250,60,50);"
                                                   "}"
                                                  );
const QString Text_Red_Disabled                          (
                                                   "QWidget{"
                                                   "color: rgb(250,60,50);"
                                                   "}"
                                                   "QWidget:disabled{"
                                                    "color: rgb(250,60,50);"
                                                   "}"
                                                   "QWidget:enabled{"
                                                    "color: rgb(250,60,50);"
                                                   "}"
                                                  );
const QString ScrollBar_Style                     (
                                                   "QScrollBar:vertical {"
                                                    "width: 10px;"
                                                    "height: 10px;"
                                                    "background: rgb(255,255,255);"
                                                   "}"
                                                   "QScrollBar:horizontal {"
                                                    "width: 10px;"
                                                    "height: 10px;"
                                                    "background: rgb(255,255,255);"
                                                   "}"
                                                  );
const QString Basic_PushButtons_Style                 (
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
                                                    "background: qradialgradient(spread:pad, cx:0.503114, cy:0.168, radius:0.824, fx:0.497929, fy:0.99116, stop:0.153257 rgba(255, 65, 0, 59), stop:1 rgba(0, 0, 0, 0));"
                                                   "}"
                                                   "QPushButton:pressed {"
                                                    "border: none;"
                                                    "color: rgb(50, 20, 20);"
                                                   "}"
                                                  );
const QString Basic_ToolButtons_Style             (
                                                   "QToolButton{"
                                                    "border: none;"
                                                   "}"
                                                   "QToolButton:disabled {"
                                                    "border: none;"
                                                    "color: rgb(100, 100, 100);"
                                                   "}"
                                                   "QToolButton:enabled {"
                                                    "border: none;"
                                                    "color: rgb(250,60,50);"
                                                   "}"
                                                   "QToolButton:checked {"
                                                    "border: none;"
                                                    "color: rgb(0, 115, 10);"
                                                   "}"
                                                   "QToolButton:hover {"
                                                    "border: none;"
                                                    "text-decoration: underline;"
                                                    "background: qradialgradient(spread:pad, cx:0.503114, cy:0.168, radius:0.824, fx:0.497929, fy:0.99116, stop:0.153257 rgba(255, 65, 0, 59), stop:1 rgba(0, 0, 0, 0));"
                                                   "}"
                                                   "QToolButton:pressed {"
                                                    "border: none;"
                                                    "color: rgb(100, 100, 100);"
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

const QString ToolButtons_Style                  ( "QToolButton{"
                                                   "border-style: solid;"
                                                   "border-top-width: 6px;"
                                                   "border-bottom-width: 1px;"
                                                   "border-right-width: 6px;"
                                                   "border-left-width: 6px;"
                                                   "border-color: rgba(255,100,100,0%);"
                                                   "background: rgba(147,29,18,0%);"
                                                   "color: rgba(255,255,255,100%);"
                                                   "border-top-right-radius: 10px;"
                                                   "border-top-left-radius: 10px;"
                                                   "border-bottom-right-radius: 0px;"
                                                   "border-bottom-left-radius: 0px;"
                                                   "}"

                                                   "QToolButton:disabled{"
                                                   "border-style: solid;"
                                                   "border-top-width: 3px;"
                                                   "border-bottom-width: 1px;"
                                                   "border-right-width: 3px;"
                                                   "border-left-width: 3px;"
                                                   "border-top-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "color: rgba(0,0,0,100%);"
                                                   "background: "
                                                   "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                   "stop:0 rgba(255,255,255,100), "
                                                   "stop: 0.05 rgba(255,255,255,120),"
                                                   "stop:0.5 rgba(255,250,250,200),"
                                                   "stop:0.95 rgba(255,255,255,120),"
                                                   "stop:1 rgba(255,255,255,100));}"

                                                   "QToolButton:enabled {"
                                                   "border-style: solid;"
                                                   "color: rgba(255,255,255,100%);"
                                                   "border-top-width: 3px;"
                                                   "border-bottom-width: 1px;"
                                                   "border-right-width: 3px;"
                                                   "border-left-width: 3px;"
                                                   "border-top-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "background: "
                                                   "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                   "stop:0 rgba(255,255,255,50), "
                                                   "stop: 0.05 rgba(200,200,200,70),"
                                                   "stop:0.5 rgba(200,200,200,170),"
                                                   "stop:0.95 rgba(200,200,200,70),"
                                                   "stop:1 rgba(255,255,255,100));}"

                                                   "QToolButton:hover {"
                                                   "border-style: solid;"
                                                   "color: rgba(255,255,255,100%);"
                                                   "border-top-width: 3px;"
                                                   "border-bottom-width: 1px;"
                                                   "border-right-width: 3px;"
                                                   "border-left-width: 3px;"
                                                   "border-top-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "background: "
                                                   "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                   "stop:0 rgba(147,29,18,127), "
                                                   "stop: 0.05 rgba(200, 200, 200, 10),"
                                                   "stop:0.5 rgba(200, 200, 200, 130),"
                                                   "stop:0.95 rgba(200, 200, 200, 10),"
                                                   "stop:1 rgba(147,29,18,127));}"

                                                   "QToolButton::pressed{"
                                                   "border-style: solid;"
                                                   "color: rgba(255,255,255,100%);"
                                                   "border-top-width: 3px;"
                                                   "border-bottom-width: 1px;"
                                                   "border-right-width: 3px;"
                                                   "border-left-width: 3px;"
                                                   "border-top-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "background: "
                                                   "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                   "stop:0 rgba(255,255,255,50), "
                                                   "stop: 0.05 rgba(200,200,200,70),"
                                                   "stop:0.5 rgba(200,200,200,170),"
                                                   "stop:0.95 rgba(200,200,200,70),"
                                                   "stop:1 rgba(255,255,255,100));}"
                                                  );

const QString PushButtons_Style                  ( "QPushButton{"
                                                   "border-style: solid;"
                                                   "border-top-width: 1px;"
                                                   "border-bottom-width: 6px;"
                                                   "border-right-width: 6px;"
                                                   "border-left-width: 6px;"
                                                   "border-color: rgba(255,100,100,0%);"
                                                   "background: rgba(147,29,18,0%);"
                                                   "color: rgba(255,255,255,100%);"
                                                   "border-bottom-right-radius: 10px;"
                                                   "border-bottom-left-radius: 10px;"
                                                   "border-top-right-radius: 0px;"
                                                   "border-top-left-radius: 0px;"
                                                   "}"
                                                   "QPushButton:disabled{"
                                                   "border-style: solid;"
                                                   "border-bottom-width: 3px;"
                                                   "border-top-width: 1px;"
                                                   "border-right-width: 3px;"
                                                   "border-left-width: 3px;"
                                                   "border-bottom-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "color: rgba(0,0,0,100%);"
                                                   "background: "
                                                   "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                   "stop:0 rgba(255,255,255,100), "
                                                   "stop: 0.05 rgba(255,255,255,120),"
                                                   "stop:0.5 rgba(255,250,250,200),"
                                                   "stop:0.95 rgba(255,255,255,120),"
                                                   "stop:1 rgba(255,255,255,100));}"

                                                   "QPushButton:enabled {"
                                                   "border-style: solid;"
                                                   "color: rgba(255,255,255,100%);"
                                                   "border-bottom-width: 3px;"
                                                   "border-top-width: 1px;"
                                                   "border-right-width: 3px;"
                                                   "border-left-width: 3px;"
                                                   "border-bottom-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "background: "
                                                   "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                   "stop:0 rgba(255,255,255,50), "
                                                   "stop: 0.05 rgba(200,200,200,70),"
                                                   "stop:0.5 rgba(200,200,200,170),"
                                                   "stop:0.95 rgba(200,200,200,70),"
                                                   "stop:1 rgba(255,255,255,100));}"

                                                   "QPushButton:hover {"
                                                   "border-style: solid;"
                                                   "color: rgba(255,255,255,100%);"
                                                   "border-bottom-width: 3px;"
                                                   "border-top-width: 1px;"
                                                   "border-right-width: 3px;"
                                                   "border-left-width: 3px;"
                                                   "border-bottom-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "background: "
                                                   "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                   "stop:0 rgba(147,29,18,127), "
                                                   "stop:0.05 rgba(200, 200, 200, 10),"
                                                   "stop:0.5 rgba(200, 200, 200, 130),"
                                                   "stop:0.95 rgba(200, 200, 200, 10),"
                                                   "stop:1 rgba(147,29,18,127));}"

                                                   "QPushButton::pressed{"
                                                   "border-style: solid;"
                                                   "color: rgba(255,255,255,100%);"
                                                   "border-bottom-width: 3px;"
                                                   "border-top-width: 1px;"
                                                   "border-right-width: 3px;"
                                                   "border-left-width: 3px;"
                                                   "border-bottom-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-right-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "border-left-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"
                                                   "background: "
                                                   "qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                   "stop:0 rgba(255,255,255,50), "
                                                   "stop: 0.05 rgba(200,200,200,30),"
                                                   "stop:0.5 rgba(200,200,200,140),"
                                                   "stop:0.95 rgba(200,200,200,30),"
                                                   "stop:1 rgba(147,29,18,127));}"
                                                  );
#endif // STYLE_H
