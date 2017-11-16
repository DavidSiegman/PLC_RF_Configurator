#include "style.h"


const QString Style::MainWindow_StyleSheet = QString(
                                                      "QMainWindow::separator {"
                                                      "background: yellow;"
                                                      "width: 10px;" /* when vertical */
                                                      "height: 10px;" /* when horizontal */
                                                      "}"

                                                      "QMainWindow::separator:hover {"
                                                      "background: red;"
                                                      "}"
                                                    );
const QString Style::Widget1_StyleSheet = QString (
                                                    "QWidget{"
                                                    "background-color: rgb(229, 202, 186);"
                                                    "border-style: none;"
                                                    "}"
                                                  );
const QString Style::Widget2_StyleSheet = QString (
                                                    "QWidget{"
                                                    "color: rgb(255, 255, 220);"
                                                    "background: rgba(100,50,00,0);"
                                                    "border-style: none;"
                                                    "}"
                                                  );
const QString Style::ToolTip_StyleSheet = QString (
                                                    "QToolTip{"
                                                    "color: rgb(255,255,220);"
                                                    "border-style: none;"
                                                    "border-width: 1px;"
                                                    "border-color: rgba(255,220,180,255);"
                                                    "background: rgba(100,50,00,255);"
                                                    "}"
                                                  );

Style::Style()
{

}
