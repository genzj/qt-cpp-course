#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include "SysInfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCpuWidget(this),
    mMemoryWidget(this)
{
    ui->setupUi(this);
    SysInfo::instance().init();
    ui->cpuBox->layout()->addWidget(&mCpuWidget);
    ui->ramBox->layout()->addWidget(&mMemoryWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
