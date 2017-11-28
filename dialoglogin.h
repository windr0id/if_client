#ifndef DIALOGSIGNUP_H
#define DIALOGSIGNUP_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class DialogSignup;
}

class DialogSignup : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSignup(QWidget *parent = 0);
    ~DialogSignup();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();



    void on_signupButton_clicked();


protected:
     void closeEvent(QCloseEvent *event);

private:
    Ui::DialogSignup *ui;
};

#endif // DIALOGSIGNUP_H
