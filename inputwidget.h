#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include"head/RepManager.h"

namespace Ui {
class InputWidget;
}

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InputWidget(char claasCh,QWidget *parent = nullptr,Commodity* com=nullptr);
    ~InputWidget();

private slots:

    void on_okBtn_released();
    void on_cancelBtn_released();

private:
    Ui::InputWidget *ui;
    RepManager rm;
    char _classCh;
    Commodity* _com;
};

#endif // INPUTWIDGET_H
