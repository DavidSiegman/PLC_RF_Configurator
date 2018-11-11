#ifndef STYLE_H
#define STYLE_H

#include <QString>
/*
    const static QString MainWindow_StyleSheet;
    const static QString Widget1_StyleSheet;
    const static QString Widget2_StyleSheet;
    const static QString ToolTip_StyleSheet;
    const static QString Background_Green;
    const static QString Background_Grey;
    const static QString Background_Red;
*/

const QString MainWindow_StyleSheet = QString(
                                                      "QMainWindow::separator {"
                                                      "background: yellow;"
                                                      "width: 10px;" /* when vertical */
                                                      "height: 10px;" /* when horizontal */
                                                      "}"

                                                      "QMainWindow::separator:hover {"
                                                      "background: red;"
                                                      "}"
                                                    );

const QString Widget1_StyleSheet = QString (
                                                    "QWidget{"
                                                    "background-color: rgb(229, 202, 186);"
                                                    "border-style: none;"
                                                    "}"
                                                  );
const QString Widget2_StyleSheet = QString (
                                                    "QWidget{"
                                                    "color: rgb(255, 255, 220);"
                                                    "background: rgba(100,50,00,0);"
                                                    "border-style: none;"
                                                    "}"
                                                  );
const QString ToolTip_StyleSheet = QString (
                                                    "QToolTip{"
                                                    "color: rgb(255,255,220);"
                                                    "border-style: none;"
                                                    "border-width: 1px;"
                                                    "border-color: rgba(255,220,180,255);"
                                                    "background: rgba(100,50,00,255);"
                                                    "}"
                                                  );

const QString Background_Green                    (
                                                   "QWidget{"
                                                   "background-color: rgb(186, 229, 202);"
                                                   "}"
                                                  );
const QString Background_Grey                     (
                                                   "QWidget{"
                                                   "background: rgba(100,50,00,0);"
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
                                                  );

#endif // STYLE_H
