#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QDialog>
#include <QTabWidget>
#include <QtWidgets>
#include <QVector>
#include <qradiobutton.h>

class tabwidget : public QDialog
{
    Q_OBJECT

public:
    tabwidget(QWidget *parent = 0);
    ~tabwidget();
signals:

public slots:
    void mat_input_first();
    void mat_input_second();
    void mat_output();
    void mat_op_add();
    void mat_op_sub();
    void mat_op_mul();
    void sort_input();
    void eq_output();
    void mat_open();
    void sort_open();
    void sort_output();
    void equation_open();
    void integration_open();
    void integration_output();
    void clear_first_mat();
    void clear_second_mat();
    void sort_clear();
    void mat_enable();
    void sort_enable();
    void eq_enable();
    void itg_enable();
    void cal_open();
    void cal_enable();
    void cal_output();

private:
    QTabWidget *tab;
    QLineEdit *m_text_m;
    QLineEdit *m_text_n;
    QLineEdit *m_text_x;
    QLineEdit *m_text_l;
    QRadioButton *mat_add;
    QRadioButton *mat_sub;
    QRadioButton *mat_mul;
    int mat_operation;
    QLineEdit *sort_n;
    QLineEdit *eq;
    QLineEdit *eq_left;
    QLineEdit *eq_right;
    QLineEdit *itg;
    QLineEdit *itg_left;
    QLineEdit *itg_right;
    QVector<QLineEdit *> sort_elements;
    QVector<QLineEdit *> first_mat;
    QVector<QLineEdit *> second_mat;
    QPushButton *mat_button;
    QPushButton *s_open_button;
    QPushButton *eq_button;
    QPushButton *itg_button;
    QLineEdit *cal;
    QPushButton *cal_button;
};

#endif // TABWIDGET_H
