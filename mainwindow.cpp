#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->statusBar();

    // Adition of menu bar
    QMenuBar * menuBar = this->menuBar();
    std::cout << "Menubar widget position: " << menuBar->pos().x() << "," << menuBar->pos().y() << std::endl;

    // Adition of submenu options
    QMenu * openMenu = menuBar->addMenu( tr ("&Open") );
    QMenu * saveMenu = menuBar->addMenu( tr ("&Save") );
    QMenu * quitMenu = menuBar->addMenu( tr ("&Quit") );
    QMenu * penMenu = menuBar->addMenu( tr ("&Pen Settings") );
    QMenu * colorMenu = menuBar->addMenu( tr ("&Color Settings") );
    QMenu * styleMenu = menuBar->addMenu( tr ("&Style Settings") );
    QMenu * formMenu = menuBar->addMenu( tr ("&Form Settings") );

    // Adition of textbox at center
    text = new QTextEdit(this);
    setCentralWidget(text);
    std::cout << "Text widget position: " << text->pos().x() << "," << text->pos().y() << std::endl;

    // Adition of DrawZone
    mydrawzone = new DrawZone(this);
    setCentralWidget(mydrawzone);
    std::cout << "Drawzone widget position: " << mydrawzone->pos().x() << "," << mydrawzone->pos().y() << std::endl;

    // Declaration of Actions
    QAction * openAction = new QAction( QIcon(":/icons/open.png"), tr("&Open"), this);
    QAction * saveAction = new QAction( QIcon(":/icons/save.png"), tr("&Save"), this);
    QAction * quitAction = new QAction( QIcon(":/icons/quit.png"), tr("&Quit"), this);
    QAction * paintAction = new QAction( QIcon(":/icons/paint.png"), tr("&Paint"), this);
    QAction * editAction = new QAction( QIcon(":/icons/edit.png"), tr("&Edit"), this);
    QAction * moveAction = new QAction( QIcon(":/icons/move.png"), tr("&Edit"), this);

    QActionGroup *group_color = new QActionGroup(this);
    connect(group_color, SIGNAL(triggered(QAction *)), this, SLOT(doIt(QAction *)));
    color0 = group_color->addAction(tr("Black Pen"));
    color1 = group_color->addAction(tr("White Pen"));
    color2 = group_color->addAction(tr("Dark Gray Pen"));
    color3 = group_color->addAction(tr("Gray Pen"));
    color4 = group_color->addAction(tr("Light Gray Pen"));
    color5 = group_color->addAction(tr("Red Pen"));
    color6 = group_color->addAction(tr("Green Pen"));
    color7 = group_color->addAction(tr("Blue Pen"));
    color8 = group_color->addAction(tr("Cyan Pen"));
    color9 = group_color->addAction(tr("Magenta Pen"));
    color10 = group_color->addAction(tr("Yellow Pen"));
    color11 = group_color->addAction(tr("Dark Red Pen"));
    color12 = group_color->addAction(tr("Dark Green Pen"));
    color13 = group_color->addAction(tr("Dark Blue Pen"));
    color14 = group_color->addAction(tr("Dark Cyan Pen"));
    color15 = group_color->addAction(tr("Dark Magenta Pen"));
    color16 = group_color->addAction(tr("Dark Yellow Pen"));
    color17 = group_color->addAction(tr("Transparent"));

    QActionGroup *group_style = new QActionGroup(this);
    connect(group_style, SIGNAL(triggered(QAction *)), this, SLOT(doIt2(QAction *)));
    style0 = group_style->addAction(tr("Solid Pen"));
    style1 = group_style->addAction(tr("Dash Line Pen"));
    style2 = group_style->addAction(tr("Dot Line Pen"));
    style3 = group_style->addAction(tr("Dash dot Line Pen"));
    style4 = group_style->addAction(tr("Dash Dot Dot Line Pen"));
    style5 = group_style->addAction(tr("Custom Dash Line Pen"));

    QActionGroup *group_form = new QActionGroup(this);
    connect(group_form, SIGNAL(triggered(QAction *)), this, SLOT(doIt3(QAction *)));
    form0 = group_form->addAction(tr("Line Form"));
    form1 = group_form->addAction(tr("Rectangle Form"));
    form2 = group_form->addAction(tr("Elipse Form"));

    QAction *set_pen_color =new QAction(tr("Alternate Color Pen"), this);
    QAction *set_pen_width_larger =new QAction(tr("&Pen Width +"), this);
    QAction *set_pen_width_shorter =new QAction(tr("&Pen Width -"), this);
    QAction *set_pen_style =new QAction(tr("&Alternate Style Pen"), this);
    QAction *set_figure_form =new QAction(tr("&Alternate Figure Form"), this);
    QAction *undo =new QAction(tr("&Undo"), this);

    openAction->setShortcut( tr("Ctrl+O"));
    saveAction->setShortcut( tr("Ctrl+S"));
    quitAction->setShortcut( tr("Ctrl+Q"));
    paintAction->setShortcut( tr("Ctrl+P"));
    editAction->setShortcut( tr("Ctrl+E"));
    moveAction->setShortcut( tr("Ctrl+M"));

    set_pen_color->setShortcut( tr("Ctrl+C"));
    set_pen_style->setShortcut( tr("Ctrl+Space"));
    set_pen_width_larger->setShortcut( tr("Ctrl++"));
    set_pen_width_shorter->setShortcut( tr("Ctrl+-"));
    set_figure_form->setShortcut( tr("Ctrl+F"));
    undo->setShortcut(tr ("Ctrl+Z"));


    openAction->setToolTip( tr("Open file"));
    saveAction->setToolTip( tr("Save file"));
    quitAction->setToolTip( tr("Quit file"));

    openAction->setStatusTip( tr("Open file"));
    saveAction->setStatusTip( tr("Save file"));
    quitAction->setStatusTip( tr("Quit file"));

    //Link Actions to Menus
    openMenu->addAction(openAction);
    saveMenu->addAction(saveAction);
    quitMenu->addAction(quitAction);

    penMenu->addAction(set_pen_width_larger);
    penMenu->addAction(set_pen_width_shorter);
    penMenu->addAction(undo);

    colorMenu->addAction(set_pen_color);
    colorMenu->addActions(group_color->actions());

    styleMenu->addAction(set_pen_style);
    styleMenu->addActions(group_style->actions());

    formMenu->addAction(set_figure_form);
    formMenu->addActions(group_form->actions());


    QToolBar * toolbar = this->addToolBar(tr("ToolBar"));
    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(quitAction);
    toolbar->addAction(paintAction);
    toolbar->addAction(editAction);
    toolbar->addAction(moveAction);

    //Link Actions to Slots
    connect(openAction, SIGNAL(triggered( )), this, SLOT(openFile()));
    connect(saveAction, SIGNAL(triggered( )), this, SLOT(saveFile()));
    connect(quitAction, SIGNAL(triggered( )), this, SLOT(quitApp()));
    connect(paintAction, SIGNAL(triggered( )), mydrawzone, SLOT(set_draw_mode_paint()));
    connect(editAction, SIGNAL(triggered( )), mydrawzone, SLOT(set_draw_mode_edit()));
    connect(moveAction, SIGNAL(triggered( )), mydrawzone, SLOT(set_draw_mode_move()));

    connect(set_pen_color, SIGNAL(triggered( )), mydrawzone, SLOT(set_pen_color()));
    connect(set_pen_width_larger, SIGNAL(triggered( )), mydrawzone, SLOT(set_pen_width_larger()));
    connect(set_pen_width_shorter, SIGNAL(triggered( )), mydrawzone, SLOT(set_pen_width_shorter()));
    connect(set_pen_style, SIGNAL(triggered( )), mydrawzone, SLOT(set_pen_style()));
    connect(set_figure_form, SIGNAL(triggered( )), mydrawzone, SLOT(set_figure_form()));
    connect(undo, SIGNAL(triggered( )), mydrawzone, SLOT(undo()));

}

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
//        stream >> path;
        new_figure.usedpen = pen;
        new_figure.usedpath = path;
        new_figure.being_edited = 0;
        std::cout << "Read one line" << std::endl;
        content.append(new_figure);
        std::cout << "Successfull append" << std::endl;
    }
    mydrawzone->load_figures(content);
    update();
    std::cout << "Open File Request for path: " << qPrintable(fileName) << std::endl;
}

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
    std::cout << "Save File Request for path: " << qPrintable(fileName) << std::endl;
}

void MainWindow::quitApp(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Application Exit", "Quit?", QMessageBox::Yes|QMessageBox::No);
    std::cout << "Quit App Request!" << std::endl;

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Application Exit", "Quit?", QMessageBox::Yes|QMessageBox::No);
    std::cout << "Quit App Request!" << std::endl;

    if (reply == QMessageBox::Yes) {
        event->accept();
    }
    else{
        event->ignore();
    }
}

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
