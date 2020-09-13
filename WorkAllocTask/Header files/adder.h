#ifndef ADDER_H
#define ADDER_H

#include <QWidget>

namespace Ui {
class Adder;
}

class Adder : public QWidget
{
    Q_OBJECT

public:
    explicit Adder(QWidget *parent = nullptr);
    ~Adder();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Adder *ui;
};

#endif // ADDER_H
