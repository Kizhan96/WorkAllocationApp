#ifndef LAB1_H
#define LAB1_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Lab1; }
QT_END_NAMESPACE

class Lab1 : public QMainWindow
{
    Q_OBJECT

public:
    Lab1(QWidget *parent = nullptr);
    ~Lab1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Lab1 *ui;
};
#endif // LAB1_H
