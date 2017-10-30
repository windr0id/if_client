#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
        void on_Button_send_clicked();
        void on_Button_login_clicked();
        void on_mesin(int, int, QString);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
