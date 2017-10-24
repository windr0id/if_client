#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "msocket.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    m_close();
}

void MainWindow::on_Button_signal_clicked()
{
    m_init();
    m_test();
}
