#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include "p2p.h"

namespace Ui {
class FileWindow;
}

class FileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = 0);
    ~FileWindow();

private slots:
    void on_pushButton_select_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::FileWindow *ui;
    p2p *p_c;
};

#endif // FILEWINDOW_H
