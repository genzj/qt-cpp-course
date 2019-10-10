#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "databasemanager.h"
#include "trackmodel.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    auto tracks = DatabaseManager::instance().trackDao.tracks();

//    for (auto it = tracks->begin(), end = tracks->end(); it != end; it ++)
//    {
//        qDebug() << (*it)->id() << "|" << (*it)->name() << "|" << (*it)->album() << "|" << (*it)->artist();
//    }
    ui->tableView->setModel(new TrackModel());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


MainWindow::~MainWindow()
{
    delete ui;
}

