#ifndef GETTER_H
#define GETTER_H

#include <QWidget>

namespace Ui {
class getter;
}

class getter : public QWidget
{
    Q_OBJECT

public:
    explicit getter(QWidget *parent = nullptr);
    ~getter();

private slots:
    void on_city_find_button_clicked();

    void on_marital_find_button_clicked();

    void on_childrens_find_button_clicked();

private:
    Ui::getter *ui;
};

#endif // GETTER_H
