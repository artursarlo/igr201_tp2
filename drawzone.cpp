#include "drawzone.h"

DrawZone::DrawZone(QWidget *parent) :
    QWidget(parent)
{
    // Effective creation of the figure list
    // This is the main list used for storing the figures already drawn
    // It uses a defined structure type that stores the used path an pen for each figure drawn
    // This defined structure type ("figuredraw") stores the information about if the
    // figure was selected or not at the selection mode
    figures = new QList<figuredraw>();
    // Set the initial drawmode at painting mode
    draw_mode = 1;
    // Set the initial figure form to be drawn at a line
    figure_form = 0;
}

// The paint event that is refreshed many times
// The variable 'ismoving' is necessary to indicate to the paint event
// whenever it was caled by a mouse operation or an action by shortcut for exemple
void DrawZone::paintEvent(QPaintEvent* e) {
    QWidget::paintEvent(e);
    QPainter painter(this);
    // Draw everything that is stored at the list if it isn't empty
    if (!figures->isEmpty()){
        for (int i=0; i<figures->length(); i++){
            painter.setPen(figures->at(i).usedpen);
            painter.drawPath(figures->at(i).usedpath);
        }
    }
    // Depending on the draw_mode and figure_form, draw the correspondent shape of the form selected
    // if the draw_mode is for painting, or a dashed rectangle if the draw mode is for selection.
    // It gives a more responsive impression (since the figure will be added to the
    // list just at the mouse release).
    switch (draw_mode){
    case 1:
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
    break;
    case 0:
        QPen edit_pen;
        edit_pen.setStyle(Qt::DashLine);
        painter.setPen(edit_pen);
        if(ismoving)
            painter.drawRect(xi, yi, xf-xi, yf-yi);
        break;
    }
}

// If in the painting mode, add a new figure to the list.
// If in the selection mode, change the selection attribute for each
// figure intersecting the selection rectangle at the list.
void DrawZone::mouseReleaseEvent(QMouseEvent* e){
    if (e->button() == Qt::LeftButton){
        if(draw_mode == 1){
            QPainterPath path;
            figuredraw newline;
            switch(figure_form){
            case 0:
                path.moveTo(xi, yi);
                path.lineTo(xf, yf);
                newline.usedpath = path;
                newline.usedpen = copy_pen;
                newline.being_edited = 0;
                figures->append(newline);
                break;
            case 1:
                path.addRect(xi,yi, xf-xi, yf-yi);
                newline.usedpath = path;
                newline.usedpen = copy_pen;
                newline.being_edited = 0;
                figures->append(newline);
                break;
            case 2:
                path.addEllipse(xi,yi, xf-xi, yf-yi);
                newline.usedpath = path;
                newline.usedpen = copy_pen;
                newline.being_edited = 0;
                figures->append(newline);
                break;
            }
        }
        else if (draw_mode == 0){
            select_area.setRect(xi,yi, xf-xi, yf-yi);
            if (!figures->isEmpty()){
                            for (int i=0; i<figures->length(); i++){
                                int *changing_being_edited = (int *) &figures->at(i).being_edited;
                                if (figures->at(i).usedpath.intersects(select_area)){
                                    *changing_being_edited = 1;
                                }
                                else{
                                    *changing_being_edited = 0;
                                }
                            }
            }
        }
        ismoving = 0;
        update();
    }
}

// Update the initial position of the operation and change the
// class variable responsable for indicating if we are doing a mouse operation
void DrawZone::mousePressEvent(QMouseEvent* e){
    if (e->button() == Qt::LeftButton){
        xi = e->pos().x();
        yi = e->pos().y();
        ismoving = 1;
    }
}

// Update the final position of the operation.
// If the draw_mode indicates movementation mode, then it
// moves each figure inside the list to the direction of movement
void DrawZone::mouseMoveEvent(QMouseEvent* e){
    if (ismoving){
        xf = e->pos().x();
        yf = e->pos().y();
        if (draw_mode == 2){
            if (!figures->isEmpty()){
                for (int i=0; i<figures->length(); i++){
                    if (figures->at(i).being_edited){
                        QPainterPath *changing_path = (QPainterPath *) &figures->at(i).usedpath;
                        changing_path->translate(xf-xi, yf-yi);

                    }
                }
                xi = xf;
                yi = yf;
            }

        }
        update();
    }
}

// Method to alternate color of the drawing pen or selected figures each time its called
void DrawZone::set_pen_color(){
    static int color_index = 0;
    QColor color_list[] = {Qt::black,	Qt::white,
                           Qt::darkGray,	Qt::gray,	Qt::lightGray,	Qt::red,
                           Qt::green,	Qt::blue,	Qt::cyan,	Qt::magenta,
                           Qt::yellow,	Qt::darkRed,	Qt::darkGreen,	Qt::darkBlue,
                           Qt::darkCyan,	Qt::darkMagenta, Qt::darkYellow, Qt::transparent};
    if(draw_mode == 1)
        copy_pen.setColor(color_list[color_index]);
    else if (draw_mode == 0){
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).being_edited){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setColor(color_list[color_index]);
                }
            }
        }
    }
    update();
    color_index = (color_index +1)%(sizeof(color_list)/sizeof(QColor));
}

// Overcharged method to set color of the drawing pen or selected figures
void DrawZone::set_pen_color(int new_color){
    QColor color_list[] = {Qt::black,	Qt::white,
                           Qt::darkGray,	Qt::gray,	Qt::lightGray,	Qt::red,
                           Qt::green,	Qt::blue,	Qt::cyan,	Qt::magenta,
                           Qt::yellow,	Qt::darkRed,	Qt::darkGreen,	Qt::darkBlue,
                           Qt::darkCyan,	Qt::darkMagenta, Qt::darkYellow, Qt::transparent};

    if(draw_mode == 1)
        copy_pen.setColor(color_list[new_color]);
    else if (draw_mode == 0){
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).being_edited){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setColor(color_list[new_color]);
                }
            }
        }
    }
    update();
}

// Method to increment width of the drawing pen or selected figures each time its called
void DrawZone::set_pen_width_larger(){
    if(draw_mode == 1)
        copy_pen.setWidth(copy_pen.width() +1);
    else if (draw_mode == 0){
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).being_edited){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setWidth(changing_pen->width() +1);
                }
            }
        }
    }
    update();
}

// Method to decrement width of the drawing pen or selected figures each time its called
void DrawZone::set_pen_width_shorter(){
    if(draw_mode == 1)
        if(copy_pen.width() > 1){
            copy_pen.setWidth(copy_pen.width() -1);
        }
        else{}
    else if (draw_mode == 0){
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).being_edited){
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

// Method to alternate style of the drawing pen  or selected figures each time its called
void DrawZone::set_pen_style(){
    static int style_index = 0;
    Qt::PenStyle style_list[] = {Qt::SolidLine,	Qt::DashLine,	Qt::DotLine,
                                 Qt::DashDotLine,	Qt::DashDotDotLine,	Qt::CustomDashLine};
    if(draw_mode == 1)
        copy_pen.setStyle(style_list[style_index]);
    else if (draw_mode == 0){
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).being_edited){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setStyle(style_list[style_index]);
                }
            }
        }
    }
    update();
    style_index = (style_index +1)%(sizeof(style_list)/sizeof(Qt::PenStyle));
}

// Overcharged method to set style of the drawing pen or selected figures
void DrawZone::set_pen_style(int new_style){
    Qt::PenStyle style_list[] = {Qt::SolidLine,	Qt::DashLine,	Qt::DotLine,
                                 Qt::DashDotLine,	Qt::DashDotDotLine,	Qt::CustomDashLine};
    if(draw_mode == 1)
        copy_pen.setStyle(style_list[new_style]);
    else if (draw_mode == 0){
        if (!figures->isEmpty()){
            for (int i=0; i<figures->length(); i++){
                if (figures->at(i).being_edited){
                    QPen *changing_pen = (QPen *) &figures->at(i).usedpen;
                    changing_pen->setStyle(style_list[new_style]);
                }
            }
        }
    }
    update();
}

// Method to alternate form of the drawing figure
void DrawZone::set_figure_form(){
    static int current_form = 0;
    current_form = (current_form +1)%3;
    figure_form = current_form;
}

// Overcharged method to set form of the drawing figure
void DrawZone::set_figure_form(int new_form){
    figure_form = new_form;
}

// Slots to set the draw_mode
void DrawZone::set_draw_mode_move(){
    draw_mode = 2;
}

void DrawZone::set_draw_mode_paint(){
    draw_mode = 1;
}

void DrawZone::set_draw_mode_edit(){
    std::cout << "Selection mode!!";
    draw_mode = 0;
}

// Method used for saving the current state of the drawzone
void DrawZone::get_save_cord(QList<figuredraw> **adress, int *n_figures){
    *adress = figures;
    *n_figures = figures->count();
}

// Method used for loading a list of figures
void DrawZone::load_figures(QList<figuredraw> adress){
    *figures = adress;
}

// Method used to erase the last element of the figure list
void DrawZone::undo(){
    if (!figures->isEmpty()){
        figures->pop_back();
        update();
    }
}
