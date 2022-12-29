#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_backBtn_released()
{
     ui->stackedWidget->setCurrentWidget(ui->mainPg);
}

void MainWindow::on_backBtn_2_released()
{
     ui->stackedWidget->setCurrentWidget(ui->mainPg);
}

void MainWindow::on_backBtn_3_released()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPg);
}


void MainWindow::on_backBtn_5_released()
{
   ui->stackedWidget->setCurrentWidget(ui->mainPg);
}
void MainWindow::on_showBtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->showPg);
}

void MainWindow::on_buyBtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->buyPg);
}

void MainWindow::on_saleStatBtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->saleStatPg);
    //更新总成本和总收入
    ui->sumRevenLcd->display(rm.getSumRevenue());
    ui->sumCostLcd->display(rm.getSumCost());
}


void MainWindow::on_comManagerBtn_released()
{
      ui->stackedWidget->setCurrentWidget(ui->managerPg);
}

void MainWindow::on_exitBtn_released()
{
    this->close();
}
