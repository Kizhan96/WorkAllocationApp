#include "lab1.h"
#include "ui_lab1.h"
#include "adder.h"
#include "getter.h"

Lab1::Lab1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lab1)
{
    ui->setupUi(this);
}

Lab1::~Lab1()
{
    delete ui;
}


void Lab1::on_pushButton_clicked()
{
    Adder *w_adder = new Adder;
    w_adder->show();
}

void Lab1::on_pushButton_2_clicked()
{
    getter *w_getter = new getter;
    w_getter->show();
}
