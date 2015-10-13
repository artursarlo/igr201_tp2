#ifndef DRAWZONE_H
#define DRAWZONE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <iostream>

class DrawZone : public QWidget
{
    Q_OBJECT
public:
    explicit DrawZone(QWidget *parent = 0);
    QPen copy_pen;

    typedef struct{
        QPen usedpen;
        QPainterPath usedpath;
    }figuredraw;

    void get_save_cord(QList<figuredraw> **adress, int *n_figures);
    void load_figures(QList<figuredraw> adress);

private:
    int xi,yi,xf,yf, ismoving, figure_form, draw_mode;
    QList<figuredraw> *figures;
    QRectF select_area;

protected:
    virtual void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

signals:

public slots:
    void set_pen_color();
    void set_pen_width_larger();
    void set_pen_width_shorter();
    void set_pen_style();
    void set_figure_form();
    void undo();
    void set_pen_color(int new_color);
    void set_pen_style(int new_style);
    void set_figure_form(int new_form);
    void set_draw_mode_paint();
    void set_draw_mode_edit();
};

#endif // DRAWZONE_H
