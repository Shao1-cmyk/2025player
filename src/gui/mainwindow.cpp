#include "mainwindow.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<DPushButton>
#include<DLabel>
#include<DScrollBar>
#include<DTitlebar>
#include<DWidgetUtil>
#include<DPaletteHelper>
#include<DScrollArea>
#include<QStackedWidget>
MainWindow::~MainWindow() {
    delete cw;
    delete Navw;
    delete MainVLayout;
    delete UpHLayout;
    delete DownHLayout;
    delete RightHLayout;
}
MainWindow::MainWindow()

{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    this->titlebar()->setSeparatorVisible(false);
    this->titlebar()->setAutoHideOnFullscreen(true);
    this->titlebar()->setIcon(QIcon(":asset/image/logo.png"));
    this->titlebar()->setTitle("Muiltimedia Player");
    this->titlebar()->setFixedHeight(60);
    this->setWindowRadius (10);
    this->setMinimumSize(QSize(900, 600));
    Navw->setAutoFillBackground(true);
    cbar->setAutoFillBackground(true);

    moveToCenter(this); //把窗口移动到屏幕中间
    //把主窗口分为上下两个垂直布局

    MusicTable *music_table = new MusicTable();
    DPushButton *ts2=new DPushButton(this);
    ts2->setText("视频");

    page = new QStackedWidget(this);
    page->addWidget(music_table);
    page->addWidget(ts2);
      RightHLayout->addWidget(page);
    cw->setLayout(MainVLayout);
    cw->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,Qt::transparent);
    cw->setPalette(palette);

    cbar->setStyleSheet("background-color:white");
    MainVLayout->setContentsMargins(0, 0, 0, 0);
    MainVLayout->addSpacing(5);
    MainVLayout->addLayout(UpHLayout);
    MainVLayout->addLayout(DownHLayout);
    UpHLayout->addWidget(Navw);

    UpHLayout->addLayout(RightHLayout);
    MainVLayout->setSpacing(0);
    MainVLayout->setContentsMargins(0,0,0,0);
    UpHLayout->setContentsMargins(0,0,0,0);
    DownHLayout->setContentsMargins(0,0,0,0);
    DownHLayout->addWidget(cbar);

    UpHLayout->setStretch(0, 6);
    UpHLayout->setStretch(1, 22);

    MainVLayout->setStretch(0, 9);
    MainVLayout->setStretch(1, 1);
    this->setCentralWidget(cw);
    //切换主题
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,this,&MainWindow::setTheme);
    //对应左侧导航栏
    connect(Navw->ListView1->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::currentchange);
    Navw->ListView1->setCurrentIndex(Navw->ListView1->model()->index(0, 0));

}

 ///深色浅色两套主题的颜色/图标设置
void MainWindow::setTheme(DGuiApplicationHelper::ColorType theme)
{

    if(theme==DGuiApplicationHelper::LightType){
        QPalette palette = this->palette();
        cbar->setPalette(palette);
    }else {
        QPalette palette = this->palette();
        cbar->setPalette(palette);
    }
}


void MainWindow::currentchange(const QModelIndex &current,const QModelIndex &previous)
{
    int row=current.row();

//    if(rowp!=-1){
//        while (QLayoutItem *item = RightHLayout->takeAt(0)){
//            QWidget *widget = item->widget();
//                   if (widget) {
//                       widget->deleteLater();
//                   }
//        }
//    }
    if (row==0)
    {
        page->setCurrentIndex(0);
//        if(cbar->mediaPlayer!=nullptr){
//            cbar->mediaPlayer->stop();
//        }
        cbar->mediaPlayer=&MusicPlayer::instance();
        cbar->readVolume("");
    }
    else if(row==1){
        page->setCurrentIndex(1);

    }
}

