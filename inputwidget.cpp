#include "inputwidget.h"
#include "ui_inputwidget.h"
#include<QMessageBox>
InputWidget::InputWidget(char classCh,QWidget *parent,Commodity* com) :
    QWidget(parent),
    ui(new Ui::InputWidget),rm(),_classCh(classCh),_com(com)
{
    ui->setupUi(this);
    QStringList kList ;
    switch(_classCh)
    {
    case'F':
        kList = {tr("熟食"), tr("生食"),tr("袋装食品")};
        break;
    case'C':
        kList={tr("美容"),tr("清洁"),tr("护肤")};
        break;
    case 'B':
        kList={tr("普通饮料"),tr("酒"),tr("碳酸饮料")};
        ui->weiOrCapaLab->setText(tr("商品容量"));
        break;
    case 'D':
        kList={tr("床上用品"),tr("厨房用品"),tr("电器"),tr("常用品")};
    }
    ui->kindBox->clear();
    ui->kindBox->addItems(kList); //设置下拉选择框内容
    if(com)
    {
        ui->kindBox->setCurrentIndex(com->getKind());
        ui->nameEdit->setText(tr(com->getName().c_str()));
        ui->brandEdit->setText(tr(com->getBrand().c_str()));
        ui->manuEdit->setText(tr(com->getManufacturer().c_str()));
        ui->priceBox->setValue(com->getPrice());
        ui->costBox->setValue(com->getCost());
        ui->weightOrCapaBox->setValue((com->getWeiOrCapa()));
        ui->amountBox->setValue(com->getAmount());
    }
}

InputWidget::~InputWidget()
{
    delete ui;
}


void InputWidget::on_okBtn_released()  //录入信息
{
    int kind = ui->kindBox->currentIndex();
    auto name = ui->nameEdit->text().toStdString();
    auto brand = ui->brandEdit->text().toStdString();
    auto manufacturer=ui->manuEdit->text().toStdString();
    double price = ui->priceBox->value();
    double cost = ui->costBox->value();
    double weiOrCapa=ui->weightOrCapaBox->value();
    int amount = ui->amountBox->value();
    if(brand==""||manufacturer==""||brand==""||cost<=0||
            price<=0||weiOrCapa<=0||amount<=0)
    {
        QMessageBox::critical(this,tr("错误"),tr("输入信息有误，请重新输入！"));
        return ;
    }
    if(_com) //修改
    {
        std::string no = _com->getNo();
        rm.setPricre(no,price);
        rm.setAmount(no,amount);
        _com->setName(name);
        _com->setCost(cost);
        _com->setManufacturer(manufacturer);
        _com->setBrand(brand);
        _com->setWeiOrCapa(weiOrCapa);
        _com->setKind(kind);
    }
    else //新增
    {
        if(rm.comExist(name,brand))  //查重 品牌+商品名 相同为重复
        {
            QMessageBox::information(this,tr("提示"),tr("该商品已存在！"));
            this->close();
            return;
        }
        switch (_classCh)
        {

        case 'F': //food

            rm.addFood(std::move(name),std::move(brand),std::move(manufacturer),
                       price,cost,amount,weiOrCapa,(Food::FoodKind)kind);
            break;
        case 'C':

            rm.addCosmetic(std::move(name),std::move(brand),std::move(manufacturer),
                           price,cost,amount,weiOrCapa,(Cosmetic::CosmeticKind)kind);
            break;
        case 'B':
            rm.addBeverage(std::move(name),std::move(brand),std::move(manufacturer),
                           price,cost,amount,weiOrCapa,(Beverage::BeverageKind)kind);
            break;
        case 'D':
            rm.addDaily(std::move(name),std::move(brand),std::move(manufacturer),
                           price,cost,amount,weiOrCapa,(Daily::DailyKind)kind);
            break;
        }
    }
    QMessageBox::information(this,tr("提示"),tr("成功！"));
    this->close();
}


void InputWidget::on_cancelBtn_released()
{
    this->close();
}

