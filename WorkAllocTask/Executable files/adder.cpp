#include "adder.h"
#include "ui_adder.h"
#include "Students.h"
#include <QMessageBox>

Student *Arr = new Student[20];

Adder::Adder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Adder)
{
    ui->setupUi(this);
}

Adder::~Adder()
{
    delete ui;
}

void Adder::on_pushButton_clicked()
{
    QMessageBox msg;
    Arr[Arr->Number_of_students].Set_Name(ui->lineEdit->text().toLocal8Bit().constData());
    Arr[Arr->Number_of_students].Set_Surname(ui->lineEdit_2->text().toLocal8Bit().constData());
    Arr[Arr->Number_of_students].Set_Patronymic(ui->lineEdit_3->text().toLocal8Bit().constData());
    Arr[Arr->Number_of_students].Set_City(ui->lineEdit_4->text().toLocal8Bit().constData());
    if (ui->lineEdit_5->text() == "Yes" || ui->lineEdit_5->text() == "yes" || ui->lineEdit_5->text() == "YES" || ui->lineEdit_5->text() == "1") {
        Arr[Arr->Number_of_students].Set_Marital_Status(true);
    }
    if (ui->lineEdit_5->text() == "No" || ui->lineEdit_5->text() == "no" || ui->lineEdit_5->text() == "NO" || ui->lineEdit_5->text() == "0") {
        Arr[Arr->Number_of_students].Set_Marital_Status(false);
    }
    if (ui->lineEdit_6->text() == "Yes" || ui->lineEdit_6->text() == "yes" || ui->lineEdit_6->text() == "YES" || ui->lineEdit_6->text() == "1") {
        Arr[Arr->Number_of_students].Set_Kids(true);
    }
    if (ui->lineEdit_6->text() == "No" || ui->lineEdit_6->text() == "no" || ui->lineEdit_6->text() == "NO" || ui->lineEdit_6->text() == "0") {
        Arr[Arr->Number_of_students].Set_Kids(false);
    }
    msg.setText("Student number " + QString::number(Arr->Number_of_students + 1) + " is added to a DataBase.");
    msg.exec();
    close();
    Arr->Number_of_students++;
}
