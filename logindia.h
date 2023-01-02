#ifndef LOGINDIA_H
#define LOGINDIA_H

#include <QDialog>

namespace Ui {
class LoginDia;
}

class LoginDia : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDia(QWidget *parent = nullptr);
    ~LoginDia();
    bool canLog();
private slots:


    void on_okBtn_released();

    void on_cancelBtn_released();

    void on_chPwdEdit_released();

    void on_aboutBtn_released();

private:
    Ui::LoginDia *ui;
    QString _passWord;
    bool _canLog;
};

#endif // LOGINDIA_H
