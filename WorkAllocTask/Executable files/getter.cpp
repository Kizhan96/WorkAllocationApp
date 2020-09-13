#include "getter.h"
#include "ui_getter.h"
#include <qstringlistmodel.h>
#include "Students.h"

QString Name;
QString Surname;
QString Patronymic;
QString City;
QString Marital_Status;
QString Kids;

getter::getter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getter)
{
    ui->setupUi(this);
}

getter::~getter()
{
    delete ui;
}

void getter::on_city_find_button_clicked()
{
    QStringListModel *city_find = new QStringListModel(this);
    QStringList list;

    for (int i = 0; i <= 20; i++) {
         if (Arr[i].Get_City() == ui->city_line->text().toLocal8Bit().constData()) {
             Name = QString::fromStdString(Arr[i].Get_Name());
             Surname = QString::fromStdString(Arr[i].Get_Surname());
             Patronymic = QString::fromStdString(Arr[i].Get_Patronymic());
             City = QString::fromStdString(Arr[i].Get_City());
             if (Arr[i].Get_Marital_Status() == true)
                Marital_Status = "Yes";
             if (Arr[i].Get_Kids() == true)
                 Kids = "Yes";
             list << "Name: " + Name + ";  Surname: "+ Surname + ";   Patronymic: " + Patronymic + ";   City: " + City + ";   Marital status: " + Marital_Status + ";   Kids: " + Kids;
         }
    }

    city_find -> setStringList(list);
    ui->city_list->setModel(city_find);
}

void getter::on_marital_find_button_clicked()
{
    QStringListModel *find_marital = new QStringListModel(this);
    QStringList list1;

    for (int i = 0; i <= 20; i++) {
        if (ui->Married_Radio->isChecked() == true) {
            if (Arr[i].Get_Marital_Status() == true) {
                Name = QString::fromStdString(Arr[i].Get_Name());
                Surname = QString::fromStdString(Arr[i].Get_Surname());
                Patronymic = QString::fromStdString(Arr[i].Get_Patronymic());
                City = QString::fromStdString(Arr[i].Get_City());
                    Marital_Status = "Yes";
                if (Arr[i].Get_Kids() == true)
                    Kids = "Yes";
                else if (Arr[i].Get_Kids() == false) Kids = "No";
                    list1 << "Name: " + Name + ";  Surname: "+ Surname + ";   Patronymic: " + Patronymic + ";   City: " + City + ";   Marital status: " + Marital_Status + ";   Kids: " + Kids;
            }
        }
        if (ui->Married_Radio->isChecked() == false) {
            if (ui->Single_Radio->isChecked() == true) {
                if (Arr[i].Get_Marital_Status() == false) {
                    Name = QString::fromStdString(Arr[i].Get_Name());
                    Surname = QString::fromStdString(Arr[i].Get_Surname());
                    Patronymic = QString::fromStdString(Arr[i].Get_Patronymic());
                    City = QString::fromStdString(Arr[i].Get_City());
                        Marital_Status = "No";
                    if (Arr[i].Get_Kids() == true)
                        Kids = "Yes";
                    else if (Arr[i].Get_Kids() == false) Kids = "No";
                    list1 << "Name: " + Name + ";  Surname: "+ Surname + ";   Patronymic: " + Patronymic + ";   City: " + City + ";   Marital status: " + Marital_Status + ";   Kids: " + Kids;
                }
            }
        }
    }

    find_marital -> setStringList(list1);
    ui->marital_list->setModel(find_marital);
}

void getter::on_childrens_find_button_clicked()
{
    QStringListModel *find_childrens = new QStringListModel(this);
    QStringList list2;

    for (int i = 0; i <= 20; i++) {
        if (ui->YesKids_Radio->isChecked() == true) {
            if (Arr[i].Get_Kids() == true) {
                Name = QString::fromStdString(Arr[i].Get_Name());
                Surname = QString::fromStdString(Arr[i].Get_Surname());
                Patronymic = QString::fromStdString(Arr[i].Get_Patronymic());
                City = QString::fromStdString(Arr[i].Get_City());
                    Kids = "Yes";
                if (Arr[i].Get_Marital_Status() == true)
                    Marital_Status = "Yes";
                else if (Arr[i].Get_Marital_Status() == false) Marital_Status = "No";
                    list2 << "Name: " + Name + ";  Surname: "+ Surname + ";   Patronymic: " + Patronymic + ";   City: " + City + ";   Marital status: " + Marital_Status + ";   Kids: " + Kids;
            }
        }
        if (ui->YesKids_Radio->isChecked() == false) {
            if (ui->NoKids_Radio->isChecked() == true) {
                if (Arr[i].Get_Kids() == false) {
                    Name = QString::fromStdString(Arr[i].Get_Name());
                    Surname = QString::fromStdString(Arr[i].Get_Surname());
                    Patronymic = QString::fromStdString(Arr[i].Get_Patronymic());
                    City = QString::fromStdString(Arr[i].Get_City());
                        Kids = "No";
                        if (Arr[i].Get_Marital_Status() == true)
                            Marital_Status = "Yes";
                        else if (Arr[i].Get_Marital_Status() == false) Marital_Status = "No";
                    list2 << "Name: " + Name + ";  Surname: "+ Surname + ";   Patronymic: " + Patronymic + ";   City: " + City + ";   Marital status: " + Marital_Status + ";   Kids: " + Kids;
                }
            }
        }
    }

    find_childrens -> setStringList(list2);
    ui->childrens_list->setModel(find_childrens);
}
