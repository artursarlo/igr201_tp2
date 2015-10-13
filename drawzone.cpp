#include "drawzone.h"

DrawZone::DrawZone(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(parent->size());
    figures = new QList<figuredraw>();
    connect(parent, SIGNAL(color_pen_changed(int)), this, SLOT(set_pen_color(int)));
    connect(parent, SIGNAL(style_pen_changed(int)), this, SLOT(set_pen_style(int)));
    connect(parent, SIGNAL(form_painter_changed(int)), this, SLOT(set_figure_form(int)));
}

void DrawZone::paintEvent(QPaintEvent* e) {
    QWidget::paintEvent(e);
    QPainter painter(this);

    if (!figures->isEmpty()){
        for (int i=0; i<figures->length(); i++){
            painter.setPen(figures->at(i).usedpen);
            painter.drawPath(figures->at(i).usedpath);
        }
    }

    if (draw_mode){
        painter.setPen(copy_pen);
        if(ismoving){
            switch(figure_form){
            case 0:
                painter.drawLine(xi, yi, xf, yf);
                break;
            case 1:
                painter.drawRect(xi, yi, xf-xi, yf-yi);
                break;
            case 2:
                painter.drawEllipse(xi, yi, xf-xi, yf-yi);
            }
        }
    }
    else{
        QPen edit_pen;
        edit_pen.setStyle(Qt::DashLine);
        painter.setPen(edit_pen);
        if(ismoving)
            painter.drawRect(xi, yi, xf-xi, yf-yi);
    }
}

void DrawZone::mouseReleaseEvent(QMouseEvent* e){
    if (e->button() == Qt::LeftButton){
        std::cout << "LeftButtonReleased!" << std::endl;
        if(draw_mode){
            QPainterPath path;
            figuredraw newline;
            switch(figure_form){
            case 0:
                path.moveTo(xi, yi);
                path.lineTo(xf, yf);
                path.closeSubpath();
                newline.usedpath = path;
                newline.usedpen = copy_pen;
                figures->append(newline);
                break;
            case 1:
                path.addRect(xi,yi, xf-xi, yf-yi);
                path.closeSubpath();
                newline.usedpath = path;
                newline.usedpen = copy_pen;
                figures->append(newline);
                break;
            case 2:
                path.addEllipse(xi,yi, xf-xi, yf-yi);
                path.closeSubpath();
                newline.usedpath = path;
                newline.usedpen = copy_pen;
                figures->append(newline);
                break;
            }
        }
        else{
            select_area.setRect(xi,yi, xf-xi, yf-yi);
        }
        ismoving = 0;
        update();
    }
}

void DrawZone::mousePressEvent(QMouseEvent* e){
    if (e->button() == Qt::LeftButton){
        std::cout << "LeftButtonClicked!" << std::endl;
        xi = e->pos().x();
        yi = e->pos().y();
        ismoving = 1;
    }
}

void DrawZone::mouseMoveEvent(QMouseEvent* e){
    if (ismoving){
        xf = e->pos().x();
        yf = e->pos().y();
        update();
    }
}

void DrawZone::set_pen_color(){
    static int color_index = 0;
    QColor color_list[] = {Qt::black,	Qt::white,
                           Qt::darkGray,	Qt::gray,	Qt::lightGray,	Qt::red,
                           Qt::green,	Qt::blue,	Qt::cyan,	Qt::magenta,
                           Qt::yellow,	Qt::darkRed,	Qt::darkGreen,	Qt::darkBlue,
                           Qt::darkCyan,	Qt::darkMagenta, Qt::darkYellow, Qt::transparent};
    if(draw_mode)
        copy_pen.setColor(color_list[color_index]);
    else{
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).usedpath.intersects(select_area)){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setColor(color_list[color_index]);
                }
            }
        }
    }
    update();
    color_index = (color_index +1)%(sizeof(color_list)/sizeof(QColor));
}

void DrawZone::set_pen_color(int new_color){
    std::cout << "Cheguei aqui" << std::endl;
    QColor color_list[] = {Qt::black,	Qt::white,
                           Qt::darkGray,	Qt::gray,	Qt::lightGray,	Qt::red,
                           Qt::green,	Qt::blue,	Qt::cyan,	Qt::magenta,
                           Qt::yellow,	Qt::darkRed,	Qt::darkGreen,	Qt::darkBlue,
                           Qt::darkCyan,	Qt::darkMagenta, Qt::darkYellow, Qt::transparent};

    if(draw_mode)
        copy_pen.setColor(color_list[new_color]);
    else{
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).usedpath.intersects(select_area)){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setColor(color_list[new_color]);
                }
            }
        }
    }
    update();
}

void DrawZone::set_pen_width_larger(){
    if(draw_mode)
        copy_pen.setWidth(copy_pen.width() +1);
    else{
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).usedpath.intersects(select_area)){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setWidth(changing_pen->width() +1);
                }
            }
        }
    }
    update();
}

void DrawZone::set_pen_width_shorter(){
    if(draw_mode)
        if(copy_pen.width() > 1){
            copy_pen.setWidth(copy_pen.width() -1);
        }
        else{}
    else{
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).usedpath.intersects(select_area)){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    if(changing_pen->width() > 1){
                        changing_pen->setWidth(changing_pen->width() -1);
                    }
                }
            }
        }
    }
    update();
}

void DrawZone::set_pen_style(){
    static int style_index = 0;
    Qt::PenStyle style_list[] = {Qt::SolidLine,	Qt::DashLine,	Qt::DotLine,
                                 Qt::DashDotLine,	Qt::DashDotDotLine,	Qt::CustomDashLine};
    if(draw_mode)
        copy_pen.setStyle(style_list[style_index]);
    else{
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).usedpath.intersects(select_area)){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setStyle(style_list[style_index]);
                }
            }
        }
    }
    update();
    style_index = (style_index +1)%(sizeof(style_list)/sizeof(Qt::PenStyle));
}

void DrawZone::set_pen_style(int new_style){
    Qt::PenStyle style_list[] = {Qt::SolidLine,	Qt::DashLine,	Qt::DotLine,
                                 Qt::DashDotLine,	Qt::DashDotDotLine,	Qt::CustomDashLine};
    if(draw_mode)
        copy_pen.setStyle(style_list[new_style]);
    else{
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).usedpath.intersects(select_area)){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setStyle(style_list[new_style]);
                }
            }
        }
    }
    update();
}

void DrawZone::set_figure_form(){
    static int current_form = 0;
    current_form = (current_form +1)%3;
    figure_form = current_form;
}

void DrawZone::set_figure_form(int new_form){
    figure_form = new_form;
}

void DrawZone::set_draw_mode_paint(){
    draw_mode = 1;
}

void DrawZone::set_draw_mode_edit(){
    draw_mode = 0;
}

void DrawZone::get_save_cord(QList<figuredraw> **adress, int *n_figures){
    *adress = figures;
    *n_figures = figures->count();
}

void DrawZone::load_figures(QList<figuredraw> adress){
    *figures = adress;
}

void DrawZone::undo(){
    std::cout << "UNDO!" << std::endl;
    if (!figures->isEmpty()){
        figures->pop_back();
        update();
    }
}

