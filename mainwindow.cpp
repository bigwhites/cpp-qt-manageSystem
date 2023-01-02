#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<map>
#include<array>
#include<stdexcept>
#include<qdebug.h>
#include<QMessageBox>
#include<QInputDialog>
#include"inputwidget.h"
#include<QTimer>
#include<QDateTime>
#include<QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),rm(),saler()
{
    rm.loadRepository();
    saler.loadTradeRecord();

    ui->setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/new/prefix1/rc/n133f35jvek.jpg"));

    auto setImg = [](QString imgStr,QLabel *& label)  //设置图片
    {
        QImage* img=new QImage(imgStr);
        label->setScaledContents(true); //完整显示
        label->setPixmap(QPixmap::fromImage(*img));

    };
    auto setGif= [](QString gifStr,QLabel *&label,MainWindow *parent,QSize size)
    {
        QMovie *gif = new QMovie(gifStr);
        gif->setParent(parent);
        gif->setScaledSize(size);
        label->setMovie(gif);
        gif->start();
    };
    setImg(":/new/prefix1/rc/money.png",ui->moneyImgLab);
    setImg(":/new/prefix1/rc/buyCar.png",ui->buyCarLab);
    setGif(":/new/prefix1/rc/9954a5f7dfd64e7bafc23eda4e8b9487.gif",ui->gifLab,this,QSize(311,121));
    setGif(":/new/prefix1/rc/show.gif",ui->gifShowLab,this,QSize(171,171));
    setGif(":/new/prefix1/rc/manage.gif",ui->gifManLab,this,QSize(151,151));
    //设置定时器
    ui->timeLcd->setSegmentStyle(QLCDNumber::Filled);
    ui->timeLcd->setDigitCount(20); //数字位数
    QTimer* timer = new QTimer(this);
    timer->start(1000);
    connect(timer,&QTimer::timeout,[&]()
    {
        ui->timeLcd->display(QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss"));
    });

    //背景透明 设置字体色
    ui->timeLcd->setStyleSheet("background:transparent;color:#00ccff;");
    ui->totalMoneyLcd->setStyleSheet("background:transparent;color:#00ccff;");
    ui->totalLcd->setStyleSheet("background:transparent;color:#00ccff;");
    ui->sumCostLcd->setStyleSheet("background:transparent;color:#00ccff;");
    ui->sumRevenLcd->setStyleSheet("background:transparent;color:#00ccff;");
    //表格禁止编辑
    ui->saledComsTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->comsTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->comTabRec->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->comsManTab->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //表头大小自适应
    ui->comTabRec->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->saledComsTab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->comsTab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->comsManTab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    rm.saveRepository();
    saler.saveTradeRecord();
    delete ui;
}





void MainWindow::on_endBuyBtn_released()  //结算
{
    if(ui->saledComsTab->rowCount()==0)
    {
        QMessageBox::critical(this,tr("错误"),tr("还没有商品!"));
        return ;
    }
    auto [trid,money] = saler.endBuy();
    QMessageBox::information(this,tr("结算"),
                             QString("订单号：%1\n\n总金额：%2").arg(trid.c_str()).arg(money));
    ui->countBox->setValue(1);
    ui->totalLcd->display(0);
    ui->saledComsTab->clearContents();
    while(ui->saledComsTab->rowCount()>=1)
    {
        ui->saledComsTab->removeRow(ui->saledComsTab->rowCount()-1);
    }
}



void MainWindow::on_sureAddBtn_released()  //购买商品
{
    try
    {
        auto qNo = ui->noEdit->text();
        int amount = ui->countBox->value();
        auto com = rm.searchNo(qNo.toStdString());
        saler.buy(com,amount);
        ui->totalLcd->display(saler.locIncome());
        Manager::displaySaledCom(com,ui->saledComsTab,amount);
    }
    catch(runtime_error& re)
    {
        QMessageBox::critical(this,tr("错误"),re.what());
    }
}


void MainWindow::on_displayBtn_released()   //排序
{
    Sorter sorter;
    int toKey[]={0,2,4,6};
    int selKey = ui->sortKeyBox->currentIndex();  //排序项
    int selDir = ui->sortdirBox->currentIndex();  //升降序
    selDir==1?toKey[selKey]++:0;
    sorter((Sorter::SortKey)toKey[selKey],ui->comsTab);
}


void MainWindow::on_searchBtn_released()  //查找交易记录
{
    ui->sumRevenLcd->display(rm.getSumRevenue());
    ui->sumCostLcd->display(rm.getSumCost());
    auto trid = ui->trIdEdit->text().toStdString();
    try
    {
        if(trid=="")
        {
            trid=saler.getFirstId();
            ui->trIdEdit->setText(trid.c_str());
        }
        saler.showRecord(trid,ui->comTabRec);
        ui->totalMoneyLcd->display(saler.getTradeIncome(trid));
    }
    catch(std::exception &e)
    {
        QMessageBox::critical(this,tr("错误"),QString(e.what()));
    }
}


void MainWindow::on_changeBtn_released()  //修改购买商品的数量
{
    auto trid = ui->trIdEdit->text().toStdString();
    try  //检查交易号合法性
    {
        saler.getPosition(trid);
    }
    catch(std::exception& e)
    {
        QMessageBox::critical(this,tr("错误"),QString(e.what()));
        return;
    }
    ui->searchBtn->released();  //先查询再修改
    QStringList noList = saler.getNoList(trid);
    QString no = QInputDialog::getItem(this,tr("输入"),tr("选择商品"),noList);
    auto com = rm.searchNo(no.toStdString());
    bool ok;  //是否点击确认
    int newAmount = QInputDialog::getInt(this,tr("输入"),tr("输入新购买数量") ,0,0,com->getAmount(),1,&ok);
    if(ok)
    {
        saler.reSetTrRecord(trid,com,newAmount);
        QMessageBox::information(this,tr("提示"),tr("商品数量修改成功"));
        ui->searchBtn->released();
    }
}



void MainWindow::on_returnBtn_2_released()   //退货
{
    auto trid = ui->trIdEdit->text().toStdString();
    try  //检查交易号合法性
    {
        saler.getPosition(trid);
    }
    catch(std::exception& e)
    {
        QMessageBox::critical(this,tr("错误"),QString(e.what()));
        return;
    }
    ui->searchBtn->released();  //先查询再退货
    saler.reSetTrRecord(trid);
    QMessageBox::information(this,tr("提示"),tr("退货成功"));
}


void MainWindow::on_startSeachBtn_released()   //查询商品
{
    int searchKey = ui->searchKeyBox->currentIndex();
    QString qKey;
    int index;
    char keyCh[4] = {'F','C','B','D'};
    if(searchKey==3)
    {
        QStringList kindList={"食品","化妆品","饮料","日用品"};
        qKey = QInputDialog::getItem(this,tr("选择"),tr("选择商品类型"), kindList);
        index=kindList.indexOf(qKey);
    }
    else if(searchKey!=4)
    {
        bool ok;
        qKey = QInputDialog::getText(this,tr("输入"),QString("输入%1").arg(ui->searchKeyBox->currentText())
                                     ,QLineEdit::Normal,"",&ok);  //格式化字符串
        if(!ok) return;
    }
    std::string key  = qKey.toStdString();

    std::list<Commodity*> res;

    if(searchKey==0)  //商品号搜索
    {
        try
        {
            res.push_back(rm.searchNo(key)); //唯一结果
        }
        catch(runtime_error& re)
        {
            QMessageBox::critical(this,tr("错误"),tr(re.what()));
            return;
        }
    }
    else if(searchKey==1) //商品名搜索
    {
        res=std::move(rm.searchName(key));
    }
    else if(searchKey==2) //品牌搜索
    {
        res=std::move(rm.searchBrand(key));
    }
    else if(searchKey==3) //商品类型搜索
    {
        res=std::move(rm.searchClass(keyCh[index]));
    }
    if(searchKey==4)//默认全查询
    {
        res=std::move(rm.searchName(""));
    }
    while(ui->comsManTab->rowCount()>=1) //清除原有数据
    {
        ui->comsManTab->removeRow(ui->comsManTab->rowCount()-1);
    }
    for(auto& com:res)
    {
        Manager::displayRepCom(com,ui->comsManTab);
    }
}



void MainWindow::on_comsManTab_itemDoubleClicked(QTableWidgetItem *item)  //修改商品
{
    if(item->column()==0)
    {
        std::string no = item->text().toStdString();
        Commodity* com=rm.searchNo(no); //要修改的商品
        InputWidget* iWid=new InputWidget(no[0],this,com);  //用于输入的子窗口
        iWid->setWindowFlags(iWid->windowFlags() |Qt::Dialog);
        iWid->setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
        iWid->show();
    }
    else //展示详细信息
    {
        QMessageBox::information(this,tr("信息"),item->text());
    }
}

void MainWindow::on_addBtn_released()  //新增商品
{
    QStringList classList={"食品","化妆品","饮料","日用品"};
    bool ok=false;
    QString qKey = QInputDialog::getItem(this,tr("选择"),tr("选择商品类型"), classList,0,true,&ok);
    if(ok)
    {
        int index=classList.indexOf(qKey);
        char keyCh[4] = {'F','C','B','D'};
        InputWidget* iWid = new InputWidget(keyCh[index],this); //新增商品
        iWid->setWindowFlags(iWid->windowFlags() |Qt::Dialog);
        iWid->setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
        iWid->show();
    }
}


void MainWindow::on_comsTab_itemDoubleClicked(QTableWidgetItem *item)
{
    QMessageBox::information(this,tr("信息"),item->text());
}


void MainWindow::on_deleteBtn_released()    //商品删除
{
    bool ok;
    auto no = QInputDialog::getText(this,tr("删除商品"),tr("输入商品号"),QLineEdit::Normal,"",&ok).toStdString();
    if(ok)
    {
        try
        {
            rm.deleteCommodity(no);
        }
        catch(std::exception& e)
        {
            QMessageBox::critical(this,tr("错误"),e.what());
            return;
        }
        QMessageBox::information(this,tr("提示"),tr("删除成功！"));
        ui->searchKeyBox->setCurrentIndex(4);
        ui->startSeachBtn->released(); //更新表单
    }

}


void MainWindow::on_lastBtn_released()  //查看上一条记录
{
    auto trid = ui->trIdEdit->text().toStdString();
    try
    {
        auto lastTrid = saler.getLastTrid(trid);  //找到上一条
        ui->trIdEdit->setText(tr(lastTrid.c_str()));   //更新输入框
        saler.showRecord(lastTrid,ui->comTabRec);  //更新表格
        ui->totalMoneyLcd->display(saler.getTradeIncome(lastTrid));//更新总金额
    }
    catch(std::exception &e)
    {
        QMessageBox::critical(this,tr("错误"),tr(e.what()));
    }
}


void MainWindow::on_nextBtn_released() //查看下一条记录
{
    auto trid = ui->trIdEdit->text().toStdString();
    try
    {
        auto nextTrid = saler.getNextTrid(trid);
        ui->trIdEdit->setText(tr(nextTrid.c_str()));
        saler.showRecord(nextTrid,ui->comTabRec);
        ui->totalMoneyLcd->display(saler.getTradeIncome(nextTrid));
    }
    catch(std::exception &e)
    {
        QMessageBox::critical(this,tr("错误"),tr(e.what()));
    }
}

