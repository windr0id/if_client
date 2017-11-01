#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "message.h"
#include "sign.h"
#include "online.h"

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
        void on_mesin(int, int, QString);
        void on_onluserin(int, QString);
        void on_listWidget_itemClicked(QListWidgetItem *item);
        void on_Button_refresh_clicked();

private:
    Ui::MainWindow *ui;
    void refresh_online();
    QString get_username_by_id(int id);
    int selected_id;
    MessageClass *m_c;

};

#endif // MAINWINDOW_H
