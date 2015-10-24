#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Setup this MainWindow with the parameters mainwindow.ui:
    // Definition of size, creation of widgets inside etc..
    ui->setupUi(this);

    // Retrieve pointers of widgets already created by the up operation
    // Those who will be used again outside the creator are saved at class variables
    QMenuBar * menuBar = ui->menuBar;
    QSlider *slider_color = ui->verticalSlider;
    QSlider *slider_style = ui->verticalSlider_2;
    QToolBar * toolbar = ui->toolBar;
    mydrawzone = ui->widget;

    // Declaration of menus and adition inside menubar
    QMenu * openMenu = menuBar->addMenu( tr("&Open"));
    QMenu * saveMenu = menuBar->addMenu( tr("&Save"));
    QMenu * quitMenu = menuBar->addMenu( tr("&Quit"));
    QMenu * penMenu = menuBar->addMenu( tr("&Pen Settings"));
    QMenu * colorMenu = menuBar->addMenu( tr("&Color Settings"));
    QMenu * styleMenu = menuBar->addMenu( tr("&Style Settings"));
    QMenu * formMenu = menuBar->addMenu( tr("&Form Settings"));

    // Declaration of principal actions
    // Those that will be shown at the toolbar
    QAction * openAction = new QAction( QIcon(":/icons/open.png"), tr("&Open"), this);
    QAction * saveAction = new QAction( QIcon(":/icons/save.png"), tr("&Save"), this);
    QAction * quitAction = new QAction( QIcon(":/icons/quit.png"), tr("&Quit"), this);
    QAction * paintAction = new QAction( QIcon(":/icons/paint.png"), tr("&Paint"), this);
    QAction * editAction = new QAction( QIcon(":/icons/edit.png"), tr("&Edit"), this);
    QAction * moveAction = new QAction( QIcon(":/icons/move.png"), tr("&Edit"), this);

    // Declaration of some other actions
    // Those that will have shortcuts as well but wont be shown in the toolbar
    QAction *set_pen_color =new QAction(tr("Alternate Color Pen"), this);
    QAction *set_pen_width_larger =new QAction(tr("&Pen Width +"), this);
    QAction *set_pen_width_shorter =new QAction(tr("&Pen Width -"), this);
    QAction *set_pen_style =new QAction(tr("&Alternate Style Pen"), this);
    QAction *set_figure_form =new QAction(tr("&Alternate Figure Form"), this);
    QAction *undo =new QAction(tr("&Undo"), this);

    // Declaration of action groups
    // The pointers for the actions are saved inside class variables
    // to be used outside the class creator
    QActionGroup *action_group_color = new QActionGroup(this);
    color0 = action_group_color->addAction(tr("Black Pen"));
    color1 = action_group_color->addAction(tr("White Pen"));
    color2 = action_group_color->addAction(tr("Dark Gray Pen"));
    color3 = action_group_color->addAction(tr("Gray Pen"));
    color4 = action_group_color->addAction(tr("Light Gray Pen"));
    color5 = action_group_color->addAction(tr("Red Pen"));
    color6 = action_group_color->addAction(tr("Green Pen"));
    color7 = action_group_color->addAction(tr("Blue Pen"));
    color8 = action_group_color->addAction(tr("Cyan Pen"));
    color9 = action_group_color->addAction(tr("Magenta Pen"));
    color10 = action_group_color->addAction(tr("Yellow Pen"));
    color11 = action_group_color->addAction(tr("Dark Red Pen"));
    color12 = action_group_color->addAction(tr("Dark Green Pen"));
    color13 = action_group_color->addAction(tr("Dark Blue Pen"));
    color14 = action_group_color->addAction(tr("Dark Cyan Pen"));
    color15 = action_group_color->addAction(tr("Dark Magenta Pen"));
    color16 = action_group_color->addAction(tr("Dark Yellow Pen"));
    color17 = action_group_color->addAction(tr("Transparent"));

    QActionGroup *action_group_style = new QActionGroup(this);
    style0 = action_group_style->addAction(tr("Solid Pen"));
    style1 = action_group_style->addAction(tr("Dash Line Pen"));
    style2 = action_group_style->addAction(tr("Dot Line Pen"));
    style3 = action_group_style->addAction(tr("Dash dot Line Pen"));
    style4 = action_group_style->addAction(tr("Dash Dot Dot Line Pen"));
    style5 = action_group_style->addAction(tr("Custom Dash Line Pen"));

    QActionGroup *action_group_form = new QActionGroup(this);
    form0 = action_group_form->addAction(tr("Line Form"));
    form1 = action_group_form->addAction(tr("Rectangle Form"));
    form2 = action_group_form->addAction(tr("Elipse Form"));

    // Adition of shortcuts for principal actions
    openAction->setShortcut( tr("Ctrl+O"));
    saveAction->setShortcut( tr("Ctrl+S"));
    quitAction->setShortcut( tr("Ctrl+Q"));
    paintAction->setShortcut( tr("Ctrl+P"));
    editAction->setShortcut( tr("Ctrl+E"));
    moveAction->setShortcut( tr("Ctrl+M"));

    // Adition of shortcuts for those other actions
    set_pen_color->setShortcut( tr("Ctrl+C"));
    set_pen_style->setShortcut( tr("Ctrl+Space"));
    set_pen_width_larger->setShortcut( tr("Ctrl++"));
    set_pen_width_shorter->setShortcut( tr("Ctrl+-"));
    set_figure_form->setShortcut( tr("Ctrl+F"));
    undo->setShortcut(tr ("Ctrl+Z"));

    // Adition of tool tips for principal actions
    openAction->setToolTip( tr("Open file"));
    saveAction->setToolTip( tr("Save file"));
    quitAction->setToolTip( tr("Quit file"));

    // Adition of status tips for principal actions
    openAction->setStatusTip( tr("Open file"));
    saveAction->setStatusTip( tr("Save file"));
    quitAction->setStatusTip( tr("Quit file"));

    // Adition of actions to menus
    openMenu->addAction(openAction);
    saveMenu->addAction(saveAction);
    quitMenu->addAction(quitAction);

    penMenu->addAction(set_pen_width_larger);
    penMenu->addAction(set_pen_width_shorter);
    penMenu->addAction(undo);

    colorMenu->addAction(set_pen_color);
    colorMenu->addActions(action_group_color->actions());

    styleMenu->addAction(set_pen_style);
    styleMenu->addActions(action_group_style->actions());

    formMenu->addAction(set_figure_form);
    formMenu->addActions(action_group_form->actions());

    // Adition of principal actions to toolbar
    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(quitAction);
    toolbar->addAction(paintAction);
    toolbar->addAction(editAction);
    toolbar->addAction(moveAction);

    // Set some parameters to the sliders
    slider_color->setTickPosition(QSlider::TicksBothSides);
    slider_color->setMinimum(0);
    slider_color->setMaximum(17);
    slider_color->setSingleStep(1);

    slider_style->setTickPosition(QSlider::TicksBothSides);
    slider_style->setMinimum(0);
    slider_style->setMaximum(5);
    slider_style->setSingleStep(1);

    // Link actions and signals to slots
    connect(openAction, SIGNAL(triggered( )), this, SLOT(openFile()));
    connect(saveAction, SIGNAL(triggered( )), this, SLOT(saveFile()));
    connect(quitAction, SIGNAL(triggered( )), this, SLOT(quitApp()));

    connect(paintAction, SIGNAL(triggered( )), mydrawzone, SLOT(set_draw_mode_paint()));
    connect(editAction, SIGNAL(triggered( )), mydrawzone, SLOT(set_draw_mode_edit()));
    connect(moveAction, SIGNAL(triggered( )), mydrawzone, SLOT(set_draw_mode_move()));
    connect(set_pen_width_larger, SIGNAL(triggered( )), mydrawzone, SLOT(set_pen_width_larger()));
    connect(set_pen_width_shorter, SIGNAL(triggered( )), mydrawzone, SLOT(set_pen_width_shorter()));
    connect(undo, SIGNAL(triggered( )), mydrawzone, SLOT(undo()));

    connect(set_pen_color, SIGNAL(triggered( )), mydrawzone, SLOT(set_pen_color()));
    connect(action_group_color, SIGNAL(triggered(QAction *)), this, SLOT(doIt(QAction *)));
    connect(this, SIGNAL(color_pen_changed(int)), mydrawzone, SLOT(set_pen_color(int)));

    connect(set_pen_style, SIGNAL(triggered( )), mydrawzone, SLOT(set_pen_style()));
    connect(action_group_style, SIGNAL(triggered(QAction *)), this, SLOT(doIt2(QAction *)));
    connect(this, SIGNAL(style_pen_changed(int)), mydrawzone, SLOT(set_pen_style(int)));

    connect(set_figure_form, SIGNAL(triggered( )), mydrawzone, SLOT(set_figure_form()));
    connect(action_group_form, SIGNAL(triggered(QAction *)), this, SLOT(doIt3(QAction *)));
    connect(this, SIGNAL(form_painter_changed(int)), mydrawzone, SLOT(set_figure_form(int)));

    connect(slider_color, SIGNAL(valueChanged(int)), this, SLOT(slide_color_pen_changed(int)));
    connect(slider_style, SIGNAL(valueChanged(int)), this, SLOT(slide_style_pen_changed(int)));
}

// Class method to open .txt files with saved draws
void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName( this, tr("Open File"), "/cal/homes/aandrade/Downloads/IGR201/tp2_qt/tp2_qt/icons/images", tr("Text Files (*.txt)"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    QList<figuredraw> content;
    int k;
    stream >> k;
    for(int i= 0; i<k; i++){
        figuredraw new_figure;
        QPen pen;
        QPainterPath path;
        stream >> pen >> path;
        new_figure.usedpen = pen;
        new_figure.usedpath = path;
        new_figure.being_edited = 0;
        content.append(new_figure);
    }
    mydrawzone->load_figures(content);
    update();
}

// Class method to save .txt with current drawzone 'state'
void MainWindow::saveFile(){
    QString filter = tr("Text Files (*.txt)");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/cal/homes/aandrade/Downloads/IGR201/tp2_qt/tp2_qt/icons/images", filter, &filter);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    QList<figuredraw> *save_adress;
    int save_size;
    mydrawzone->get_save_cord(&save_adress, &save_size);
    stream << save_size;
    for (int k = 0; k< save_size; k++){
        figuredraw new_figure = save_adress->at(k);
        stream << new_figure.usedpen;
        stream << new_figure.usedpath;
    }
}

// Method to invoke program close screen  when hiting the close button at the toolbar
void MainWindow::quitApp(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Application Exit", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

// Method to invoke program close screen when hiting the 'x' button at up right corner
void MainWindow::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Application Exit", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        event->accept();
    }
    else{
        event->ignore();
    }
}

// Slot to invoke the change at pen color at the drawzone widget from the slider
void MainWindow::slide_color_pen_changed(int color){
 emit color_pen_changed(color);
}

// Slot to invoke the change at pen color at the drawzone widget from different actions
void MainWindow::doIt(QAction *sender){
    if (sender == color0)
        emit color_pen_changed(0);
    if (sender == color1)
        emit color_pen_changed(1);
    if (sender == color2)
        emit color_pen_changed(2);
    if (sender == color3)
        emit color_pen_changed(3);
    if (sender == color4)
        emit color_pen_changed(4);
    if (sender == color5)
        emit color_pen_changed(5);
    if (sender == color6)
        emit color_pen_changed(6);
    if (sender == color7)
        emit color_pen_changed(7);
    if (sender == color8)
        emit color_pen_changed(8);
    if (sender == color9)
        emit color_pen_changed(9);
    if (sender == color10)
        emit color_pen_changed(10);
    if (sender == color11)
        emit color_pen_changed(11);
    if (sender == color12)
        emit color_pen_changed(12);
    if (sender == color13)
        emit color_pen_changed(13);
    if (sender == color14)
        emit color_pen_changed(14);
    if (sender == color15)
        emit color_pen_changed(15);
    if (sender == color16)
        emit color_pen_changed(16);
    if (sender == color17)
        emit color_pen_changed(17);
}

// Slot to invoke the change at pen style at the drawzone widget from the slider
void MainWindow::slide_style_pen_changed(int style){
 emit style_pen_changed(style);
}

// Slot to invoke the change at pen style at the drawzone widget from the different actions
void MainWindow::doIt2(QAction *sender){
    if (sender == style0)
        emit style_pen_changed(0);
    if (sender == style1)
        emit style_pen_changed(1);
    if (sender == style2)
        emit style_pen_changed(2);
    if (sender == style3)
        emit style_pen_changed(3);
    if (sender == style4)
        emit style_pen_changed(4);
    if (sender == style5)
        emit style_pen_changed(5);
}

// Slot to invoke the change at pen form at the drawzone widget from the different actions
void MainWindow::doIt3(QAction *sender){
    if (sender == form0)
        emit form_painter_changed(0);
    if (sender == form1)
        emit form_painter_changed(1);
    if (sender == form2)
        emit form_painter_changed(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
