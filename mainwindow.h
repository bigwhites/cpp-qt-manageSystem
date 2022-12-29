#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"head/commodities.h"
#include"head/Manager.h"
#include"head/RepManager.h"
#include"head/Saler.h"
#include"head/Food.h"
#include"head/Sorter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buyBtn_released();

    void on_endBuyBtn_released();

    void on_sureAddBtn_released();

    void on_backBtn_released();

    void on_exitBtn_released();

    void on_showBtn_released();

    void on_backBtn_2_released();

    void on_displayBtn_released();

    void on_saleStatBtn_released();

    void on_backBtn_3_released();

    void on_searchBtn_released();

    void on_changeBtn_released();

    void on_returnBtn_2_released();

    void on_addBtn_released();


    void on_backBtn_5_released();

    void on_comManagerBtn_released();

    void on_startSeachBtn_released();

    void on_comsManTab_itemDoubleClicked(QTableWidgetItem *item);

    void on_comsTab_itemDoubleClicked(QTableWidgetItem *item);

    void on_deleteBtn_released();

    void on_lastBtn_released();

    void on_nextBtn_released();

private:
    Ui::MainWindow *ui;
    RepManager rm;
    Saler saler;
};
#endif // MAINWINDOW_H
