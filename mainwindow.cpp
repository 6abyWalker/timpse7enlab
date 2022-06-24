#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //подписи осей x и y
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    //начальная установка отображаемых значений осей x и y
    ui->widget->xAxis->setRange(-5, 5);
    ui->widget->yAxis->setRange(-5, 5);

    //включение возможности приближать и отдалять график, перемащаться по нему
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->setInteraction(QCP::iRangeZoom, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //очистка строки состояния
    ui->statusbar->clearMessage();
    //удаление предыдущего графика
    ui->widget->clearGraphs();
    //удаление всех элементов из векторов x и y
    x.clear();
    y.clear();
    //перенос значений из виджетов в переменные (граница рендера)
    x1 = ui->x1spin->value();
    x2 = ui->x2spin->value();
    y1 = ui->y1spin->value();
    y2 = ui->y2spin->value();
    //проверка введных значений границ
    if(x1>x2 || y1>y2 || x1==x2){
        isDraw = false;
    }else{isDraw = true;}
    //получение коэффициентов a, b, c, шаг из виджетов
    a = ui->aSpin->value();
    b = ui->bSpin->value();
    c = ui->cSpin->value();
    step = ui->stepSpin->value();

    ui->widget->yAxis->setRange(y1, y2);
    ui->widget->xAxis->setRange(x1, x2);

    //вычисление значений функции
    if(ui->sinxBtn->isChecked()){
        for(temp=x1; temp  <= x2; temp += step){
            x.push_back(temp);
            y.push_back(a+sin(temp));
        }
        if(isDraw){
            ui->statusbar->showMessage("Был построен график функции y(x)=sin(x)+a");
        }else{ ui->statusbar->showMessage("Неправильно указаны границы рендера");}

    }else if(ui->cosBtn->isChecked()){
        for(temp=x1; temp  <= x2; temp += step){
            x.push_back(temp);
            y.push_back(cos(temp)*b);
        }
        if(isDraw){
            ui->statusbar->showMessage("Был построен график функции y(x)=cos(x)*b");
        }else{ ui->statusbar->showMessage("Неправильно указаны границы рендера");}

    }else if(ui->mainBtn->isChecked()){
        for(temp=x1; temp  <= x2; temp += step){
            x.push_back(temp);
            y.push_back(a*sin(pow(temp,4))+b*cos(pow(temp,3))+c);
        }
        if(isDraw){
            ui->statusbar->showMessage("Был построен график функции y(x)=a*sin(x^4)+b*cos(x^3)+c");
        }else{ ui->statusbar->showMessage("Неправильно указаны границы рендера");}

    }else{
        ui->statusbar->showMessage("Функция для построения не выбрана");
    }


    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);

    ui->widget->replot();
}


void MainWindow::on_sinxBtn_clicked()
{
    ui->aSpin->setEnabled(true);
    ui->bSpin->setDisabled(true);
    ui->cSpin->setDisabled(true);
}


void MainWindow::on_cosBtn_clicked()
{
    ui->aSpin->setDisabled(true);
    ui->bSpin->setEnabled(true);
    ui->cSpin->setDisabled(true);
}


void MainWindow::on_mainBtn_clicked()
{
    ui->aSpin->setEnabled(true);
    ui->bSpin->setEnabled(true);
    ui->cSpin->setEnabled(true);
}

