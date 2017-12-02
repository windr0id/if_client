#include "QFileDialog"
#include "QMessageBox"
#include "filewindow.h"
#include "ui_filewindow.h"
#include "mainwindow.h"
#include "p2p.h"

FileWindow::FileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    MainWindow *qm = (MainWindow*)this->parent();
    this->setWindowTitle("Send file to: "+qm->get_username_by_id(qm->get_selected_id()));

}

FileWindow::~FileWindow()
{
    delete ui;
}


void FileWindow::on_pushButton_select_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select File"), ".", tr("Any Files(*.*)"));
    if(path.length() == 0){
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }else{
        this->ui->textEdit_path->setText(path);
    }
}

void FileWindow::on_pushButton_send_clicked()
{
    QString path = this->ui->textEdit_path->document()->toRawText();
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(NULL, tr("Error"), tr("Can't read the file."));
        return;
    }
    QDataStream qs(&file);
    int destid = ((MainWindow*)this->parent())->get_selected_id();
    p_c = new p2p(destid, path, file.size());
    int ret = p_c->request();
    qDebug()<<ret;
    return;

    if(p_c->isRunning() == false){
        p_c->start();
    }

    char buff[BUFF_LEN];
    int rdlen = qs.readRawData(buff, 1000);
    buff[rdlen] = '\0';
    qDebug()<<buff;

}
