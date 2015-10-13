#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "drawzone.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTextEdit * text;
    DrawZone * mydrawzone;
    QAction *color0, *color1, *color2, *color3, *color4, *color5, *color6, *color7, *color8, *color9, *color10, *color11, *color12,
    *color13, *color14, *color15, *color16, *color17;
    QAction *style0, *style1, *style2, *style3, *style4, *style5;
    QAction *form0, *form1, *form2;

signals:
    void color_pen_changed(int new_color);
    void style_pen_changed(int new_style);
    void form_painter_changed(int new_form);

public slots:
    void openFile();
    void saveFile();
    void quitApp();
    void doIt(QAction *sender);
    void doIt2(QAction *sender);
    void doIt3(QAction *sender);
};

#endif // MAINWINDOW_H
