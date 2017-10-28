#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoglogin.h"
#include <QDebug>
#include <string>

#include "message.h"
#include "sign.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_init();
    ui->setupUi(this);
    DialogSignup *dsu = new DialogSignup;
    dsu->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_close();
}

void MainWindow::on_Button_send_clicked()
{
    QString qs_text = this->ui->textEdit->document()->toPlainText();
    QByteArray qb_text = qs_text.toLatin1();
    char* c_text = qb_text.data();
    int meslen = qb_text.length();
    send_message(976284396, c_text, meslen);
    std::cout<<c_text<<"end";
    this->ui->textEdit->clear();
}

void MainWindow::on_Button_login_clicked()
{
    m_close();
    m_init();
    char* u = "user3";
    char* p = "123123";
    signup(u, strlen(u)+1, p, strlen(p)+1);
}
