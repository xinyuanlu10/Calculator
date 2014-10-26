#include "tabwidget.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QToolBar>
#include <QtWidgets>
#include <QFileDialog>
#include <QColorDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QString>
#include <string>
#include "solvex.h"
#include "Calculus.h"
#include "stdlib.h"
#include <vector>
#include <qscrollarea.h>
#include "Matrix.h"
#include <qradiobutton.h>
#include <algorithm>
#include "expr.h"

QString s2q(std::string s){
    return QString(QString::fromLocal8Bit(s.c_str()));
}

string q2s(const QString &s)
{
    return string((const char *)s.toLocal8Bit());
}

void tabwidget::mat_open(){
//    int refocus = 0;
    if(tab->count() == 5){
        tab->removeTab(0);
        delete m_text_m;
        delete m_text_n;
        delete m_text_x;
        delete m_text_l;
        first_mat.clear();
        second_mat.clear();
//        refocus = 1;
    }
    QWidget *mat_open = new QWidget();
    QLabel *mat_welcome = new QLabel(tr("<h3>Please enter the size of matrices:</h3>"));
    QLabel *mat_m = new QLabel(tr("row number of the first matrix:"));
    QLabel *mat_n = new QLabel(tr("column number of the first matrix:"));
    QLabel *mat_x = new QLabel(tr("row number of the second matrix:"));
    QLabel *mat_l = new QLabel(tr("column number of the second matrix:"));
    QLabel *mat_op = new QLabel(tr("please choose the operation type:"));
    m_text_m = new QLineEdit;
//    m_text_m->setClearButtonEnabled(true);
    m_text_n = new QLineEdit;
    m_text_x = new QLineEdit;
    m_text_l = new QLineEdit;
    mat_add = new QRadioButton("ADD operation");
    mat_sub = new QRadioButton("SUB operation");
    mat_mul = new QRadioButton("MUL operation");
    mat_add->setChecked(1);
    QHBoxLayout *mat_add_lay = new QHBoxLayout;
    QHBoxLayout *mat_sub_lay = new QHBoxLayout;
    QHBoxLayout *mat_mul_lay = new QHBoxLayout;
    mat_add_lay->addWidget(mat_add);
    mat_sub_lay->addWidget(mat_sub);
    mat_mul_lay->addWidget(mat_mul);
    mat_button = new QPushButton(tr("&Submit"));
    mat_button->setDefault(1);
    mat_button->setEnabled(false);
    //connect
    QVBoxLayout *m_toplay = new QVBoxLayout;
    QHBoxLayout *m_m_lay = new QHBoxLayout;
    QHBoxLayout *m_n_lay = new QHBoxLayout;
    QHBoxLayout *m_x_lay = new QHBoxLayout;
    QHBoxLayout *m_l_lay = new QHBoxLayout;
    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(mat_button);
    button_layout->setAlignment(Qt::AlignRight);
    m_m_lay->addWidget(mat_m);
    m_m_lay->addWidget(m_text_m);
//    m_m_lay->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    m_n_lay->addWidget(mat_n);
    m_n_lay->addWidget(m_text_n);
//    m_n_lay->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    m_x_lay->addWidget(mat_x);
    m_x_lay->addWidget(m_text_x);
    m_l_lay->addWidget(mat_l);
    m_l_lay->addWidget(m_text_l);
//    m_l_lay->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    m_toplay->addWidget(mat_welcome);
    m_toplay->addLayout(m_m_lay);
    m_toplay->addLayout(m_n_lay);
    m_toplay->addLayout(m_x_lay);
    m_toplay->addLayout(m_l_lay);
    m_toplay->addWidget(mat_op);
    m_toplay->addLayout(mat_add_lay);
    m_toplay->addLayout(mat_sub_lay);
    m_toplay->addLayout(mat_mul_lay);
    m_toplay->addLayout(button_layout);
    m_toplay->addStretch();
    mat_open->setLayout(m_toplay);
    tab->insertTab(0, mat_open, "Matrix");
    tab->setCurrentIndex(0);

    mat_operation = 0;
//    if(refocus) m_text_m->setFocus();
    connect(mat_button, SIGNAL(clicked()), this, SLOT(mat_input_first()));
    connect(mat_add, SIGNAL(clicked()), this, SLOT(mat_op_add()));
    connect(mat_sub, SIGNAL(clicked()), this, SLOT(mat_op_sub()));
    connect(mat_mul, SIGNAL(clicked()), this, SLOT(mat_op_mul()));
    connect(m_text_m, SIGNAL(textChanged(QString)), this, SLOT(mat_enable()));
    connect(m_text_n, SIGNAL(textChanged(QString)), this, SLOT(mat_enable()));
    connect(m_text_l, SIGNAL(textChanged(QString)), this, SLOT(mat_enable()));
    connect(m_text_x, SIGNAL(textChanged(QString)), this, SLOT(mat_enable()));
}

void tabwidget::mat_enable(){
    bool temp = (m_text_m->text()).isEmpty()||(m_text_n->text()).isEmpty()||(m_text_l->text()).isEmpty()||(m_text_x->text()).isEmpty();
//    bool temp2 =
    mat_button->setEnabled(!temp);
}

void tabwidget::mat_op_add(){
    mat_operation = 0;
}

void tabwidget::mat_op_sub(){
    mat_operation = 1;
}

void tabwidget::mat_op_mul(){
    mat_operation = 2;
}

void tabwidget::sort_open(){
    if(tab->count() == 5){
        tab->removeTab(1);
        sort_elements.clear();
        delete s_open_button;
    }

    QWidget *sort_open = new QWidget;
    sort_open->setMaximumSize(10000, 480);
    QLabel *sort_welcome = new QLabel(tr("Please enter the number of elments to be sorted:"));
    sort_n = new QLineEdit;
    sort_n->setFocus();
    QVBoxLayout *s_open_lay = new QVBoxLayout;
    QHBoxLayout *s_open_button_lay = new QHBoxLayout;
    s_open_button = new QPushButton(tr("&Submit"));
    s_open_button->setDefault(1);
    s_open_button->setDisabled(1);
    s_open_lay->addWidget(sort_welcome);
    s_open_lay->addWidget(sort_n);
    s_open_button_lay->addWidget(s_open_button);
    s_open_button_lay->setAlignment(Qt::AlignRight);
    s_open_lay->addLayout(s_open_button_lay);
    s_open_lay->addStretch();
    sort_open->setLayout(s_open_lay);
    tab->insertTab(1, sort_open, "Sort");
    tab->setCurrentIndex(1);

    connect(s_open_button, SIGNAL(clicked()), this, SLOT(sort_input()));
    connect(sort_n, SIGNAL(textChanged(QString)), this, SLOT(sort_enable()));
}

void tabwidget::sort_enable(){
    s_open_button->setEnabled(!sort_n->text().isEmpty());
}

void tabwidget::equation_open(){
    if(tab->count() == 5){
        tab->removeTab(2);
        delete eq;
        delete eq_left;
        delete eq_right;
        delete eq_button;
    }
    QWidget *equation = new QWidget;
    QLabel *equation_welcome = new QLabel(tr("Please enter the equation you want to solve:"));
    eq = new QLineEdit;
    QLabel *eq_left_welcome = new QLabel(tr("Please enter left point of the interval:"));
    QLabel *eq_right_welcome = new QLabel(tr("Please enter right point of the interval:"));
    eq_left = new QLineEdit;
    eq_right = new QLineEdit;
    eq_button = new QPushButton(tr("&Solve"));
    eq_button->setDefault(1);
    eq_button->setDisabled(1);
    QVBoxLayout *e_lay = new QVBoxLayout;
    QHBoxLayout *e_lay_left = new QHBoxLayout;
    QHBoxLayout *e_lay_right = new QHBoxLayout;
    QHBoxLayout *e_lay_button = new QHBoxLayout;
    e_lay_left->addWidget(eq_left_welcome);
    e_lay_left->addWidget(eq_left);
    e_lay_right->addWidget(eq_right_welcome);
    e_lay_right->addWidget(eq_right);
    e_lay_button->addWidget(eq_button);
    e_lay_button->setAlignment(Qt::AlignRight);
    e_lay->addWidget(equation_welcome);
    e_lay->addWidget(eq);
    e_lay->addLayout(e_lay_left);
    e_lay->addLayout(e_lay_right);
    e_lay->addLayout(e_lay_button);
    e_lay->addStretch();
    equation->setLayout(e_lay);
    tab->insertTab(2, equation, "Equation");
    tab->setCurrentIndex(2);

    connect(eq_button, SIGNAL(clicked()), this, SLOT(eq_output()));
    connect(eq, SIGNAL(textChanged(QString)), this, SLOT(eq_enable()));
    connect(eq_right, SIGNAL(textChanged(QString)), this, SLOT(eq_enable()));
    connect(eq_left, SIGNAL(textChanged(QString)), this, SLOT(eq_enable()));
}

void tabwidget::eq_enable(){
    bool temp = (eq->text().isEmpty())||(eq_left->text().isEmpty())||(eq_right->text().isEmpty());
    eq_button->setEnabled(!temp);
}

void tabwidget::integration_open(){
    if(tab->count() == 5){
        tab->removeTab(3);
        delete itg_button;
    }

    QWidget *integration = new QWidget;
    QLabel *integration_welcome = new QLabel(tr("Please enter the integration you want to solve:"));
    QLabel *itg_left_welcome = new QLabel(tr("Please enter left point of the interval:"));
    QLabel *itg_right_welcome = new QLabel(tr("Please enter right point of the interval:"));
    itg = new QLineEdit;
    itg_left = new QLineEdit;
    itg_right = new QLineEdit;
    itg_button = new QPushButton(tr("&Solve"));
    itg_button->setDefault(1);
    itg_button->setDisabled(1);
    QVBoxLayout *itg_lay = new QVBoxLayout;
    QHBoxLayout *itg_lay_left = new QHBoxLayout;
    QHBoxLayout *itg_lay_right = new QHBoxLayout;
    QHBoxLayout *itg_lay_button = new QHBoxLayout;
    itg_lay_left->addWidget(itg_left_welcome);
    itg_lay_left->addWidget(itg_left);
    itg_lay_right->addWidget(itg_right_welcome);
    itg_lay_right->addWidget(itg_right);
    itg_lay_button->addWidget(itg_button);
    itg_lay_button->setAlignment(Qt::AlignRight);
    itg_lay->addWidget(integration_welcome);
    itg_lay->addWidget(itg);
    itg_lay->addLayout(itg_lay_left);
    itg_lay->addLayout(itg_lay_right);
    itg_lay->addLayout(itg_lay_button);
    itg_lay->addStretch();
    integration->setLayout(itg_lay);
    tab->insertTab(3, integration, "Integration");
    tab->setCurrentIndex(3);

    connect(itg_button, SIGNAL(clicked()), this, SLOT(integration_output()));
    connect(itg, SIGNAL(textChanged(QString)), this, SLOT(itg_enable()));
    connect(itg_right, SIGNAL(textChanged(QString)), this, SLOT(itg_enable()));
    connect(itg_left, SIGNAL(textChanged(QString)), this, SLOT(itg_enable()));
}

void tabwidget::cal_open(){
    if(tab->count() == 5){
        tab->removeTab(4);
        delete cal_button;
    }

    QWidget *calculate = new QWidget;
    QLabel *cal_welcome = new QLabel(tr("Please enter the expression you want to calculate:"));
    cal = new QLineEdit;
    cal_button = new QPushButton(tr("&Calculate"));
    cal_button->setDefault(1);
    cal_button->setDisabled(1);
    QVBoxLayout *cal_lay = new QVBoxLayout;
    QHBoxLayout *cal_lay_button = new QHBoxLayout;
    cal_lay_button->addWidget(cal_button);
    cal_lay_button->setAlignment(Qt::AlignRight);
    cal_lay->addWidget(cal_welcome);
    cal_lay->addWidget(cal);
    cal_lay->addLayout(cal_lay_button);
    cal_lay->addStretch();
    calculate->setLayout(cal_lay);
    tab->insertTab(4, calculate, "Calculator");
    tab->setCurrentIndex(4);

    connect(cal_button, SIGNAL(clicked()), this, SLOT(cal_output()));
    connect(cal, SIGNAL(textChanged(QString)), this, SLOT(cal_enable()));
}

void tabwidget::cal_enable(){
    cal_button->setEnabled(!(cal->text()).isEmpty());
}

void tabwidget::itg_enable(){
    bool temp = (itg->text().isEmpty())||(itg_left->text().isEmpty())||(itg_right->text().isEmpty());
    itg_button->setEnabled(!temp);
}

void tabwidget::mat_input_first(){
    QString m_string = m_text_m->text();
    int m_int;
    m_int = m_string.toInt();
    if(m_int == 0){
        QMessageBox::critical(NULL, "input error!", "You have input a wrong m!", QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
        m_text_m->clear();
        m_text_n->clear();
        m_text_l->clear();
        m_text_x->clear();
        return;
    }
    QString n_string = m_text_n->text();
    int n_int;
    n_int = n_string.toInt();
    if(n_int == 0){
        QMessageBox::critical(NULL, "input error!", "You have input a wrong n!", QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
        m_text_m->clear();
        m_text_n->clear();
        m_text_l->clear();
        m_text_x->clear();
        return;
    }
    int x_int;
    QString x_string = m_text_x->text();
    x_int = x_string.toInt();
    if(x_int == 0){
        QMessageBox::critical(NULL, "input error!", "You have input a wrong x!", QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
        m_text_m->clear();
        m_text_n->clear();
        m_text_l->clear();
        m_text_x->clear();
        return;
    }
    int l_int;
    QString l_string = m_text_l->text();
    l_int = l_string.toInt();
    if(l_int == 0){
        QMessageBox::critical(NULL, "input error!", "You have input a wrong l!", QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
        m_text_m->clear();
        m_text_n->clear();
        m_text_l->clear();
        m_text_x->clear();
        return;
    }
    if(mat_add->isChecked() || mat_sub->isChecked()){
        if((m_int != x_int) || (n_int != l_int)){
            QMessageBox::critical(NULL, "input error!", "You have input wrong sizes!", QMessageBox::Yes|QMessageBox::No,
                                  QMessageBox::Yes);
            m_text_m->clear();
            m_text_n->clear();
            m_text_l->clear();
            m_text_x->clear();
            return;
        }
    }
    if(mat_mul->isChecked()){
        if(n_int != x_int){
            QMessageBox::critical(NULL, "input error!", "You have input wrong sizes!", QMessageBox::Yes|QMessageBox::No,
                                  QMessageBox::Yes);
            m_text_m->clear();
            m_text_n->clear();
            m_text_l->clear();
            m_text_x->clear();
            return;
        }
    }

    tab->removeTab(0);
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *welcome = new QLabel(tr("please enter each element of the first matrix:"));
    layout->addWidget(welcome);
    QVector<QHBoxLayout *> hlayout;
    for(int i = 0; i < m_int; i++){
        hlayout.push_back(new QHBoxLayout);
        for(int j = 0; j < n_int; j++){
            first_mat.push_back(new QLineEdit);
//            if(i == 0 && j == 0) first_mat[0]->setFocus();
            hlayout.at(i)->addWidget(first_mat.at(i*n_int+j));
        }
        layout->addLayout(hlayout.at(i));
    }
    QHBoxLayout *button_layout = new QHBoxLayout;
    QPushButton *submit = new QPushButton(tr("&submit"));
    submit->setDefault(1);
    QPushButton *clear = new QPushButton(tr("&clear"));
    button_layout->addWidget(submit);
    button_layout->addWidget(clear);
    button_layout->setAlignment(Qt::AlignRight);
    layout->addLayout(button_layout);
    layout->addStretch();

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(widget);
    scroll->setGeometry(0, 0, 320, 240);
    tab->insertTab(0, scroll, tr("Matrix"));
    tab->setCurrentIndex(0);
    first_mat[0]->setFocus();

    connect(submit, SIGNAL(clicked()), this, SLOT(mat_input_second()));
    connect(clear, SIGNAL(clicked()), this, SLOT(clear_first_mat()));
}

void tabwidget::clear_first_mat(){
    for(int i = 0; i < first_mat.size(); i++)
        first_mat[i]->setText("");
}

void tabwidget::mat_input_second(){
    QString l_string = m_text_l->text();
    int l_int;
    l_int = l_string.toInt();
    if(l_int == 0){
        QMessageBox::critical(NULL, "input error!", "You have input a wrong l!", QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
        m_text_m->clear();
        m_text_n->clear();
        m_text_l->clear();
        m_text_x->clear();
        return;
    }
    QString x_string = m_text_x->text();
    int x_int;
    x_int = x_string.toInt();
    if(x_int == 0){
        QMessageBox::critical(NULL, "input error!", "You have input a wrong x!", QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
        m_text_m->clear();
        m_text_n->clear();
        m_text_l->clear();
        m_text_x->clear();
        return;
    }

    tab->removeTab(0);
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *welcome = new QLabel(tr("please enter each element of the second matrix:"));
    layout->addWidget(welcome);
    QVector<QHBoxLayout *> hlayout;
    for(int i = 0; i < x_int; i++){
        hlayout.push_back(new QHBoxLayout);
        for(int j = 0; j < l_int; j++){
            second_mat.push_back(new QLineEdit);
//            if(i == 0 && j == 0) second_mat[0]->setFocus();
            hlayout.at(i)->addWidget(second_mat.at(i*l_int+j));
        }
        layout->addLayout(hlayout.at(i));
    }
    QHBoxLayout *button_layout = new QHBoxLayout;
    QPushButton *submit = new QPushButton(tr("&submit"));
    submit->setDefault(1);
    QPushButton *clear = new QPushButton(tr("&clear"));
    button_layout->addWidget(submit);
    button_layout->addWidget(clear);
    button_layout->setAlignment(Qt::AlignRight);
    layout->addLayout(button_layout);
    layout->addStretch();

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(widget);
    scroll->setGeometry(0, 0, 320, 240);
    tab->insertTab(0, scroll, tr("Matrix"));
    tab->setCurrentIndex(0);
    second_mat[0]->setFocus();

    connect(submit, SIGNAL(clicked()), this, SLOT(mat_output()));
    connect(clear, SIGNAL(clicked()), this, SLOT(clear_first_mat()));
}

void tabwidget::clear_second_mat(){
    for(int i = 0; i < second_mat.size(); i++)
        second_mat[i]->setText("");
}

void tabwidget::mat_output(){
    tab->removeTab(0);
    Matrix<double> m1;
    Matrix<double> m2;
    Matrix<double> m;
    QString text;
    int m_int;
    m_int = (m_text_m->text()).toInt();
    int n_int;
    n_int = (m_text_n->text()).toInt();
    int x_int;
    x_int = (m_text_x->text()).toInt();
    int l_int;
    l_int = (m_text_l->text()).toInt();

    m1.t.resize(m_int);
//    for(int i = 0; i < m_int; i++){
//        (m1.t[i]).resize(n_int);
//    }
    m2.t.resize(x_int);
//    for(int i = 0; i < n_int; i++){
//        (m2.t[i]).resize(l_int);
//    }
    m.t.resize(m_int);
    for(int i = 0; i < m_int; i++){
        (m.t[i]).resize(l_int);
    }
    for(int i = 0; i < m_int; i++){
        for(int j = 0; j < n_int; j++){
            text = (first_mat.at(i*n_int + j))->text();
            m1.t[i].push_back(text.toDouble());
        }
    }
    for(int i = 0; i < x_int; i++){
        for(int j = 0; j < l_int; j++){
            text = (second_mat.at(i*l_int + j))->text();
            (m2.t.at(i)).push_back(text.toDouble());
        }
    }

    if(mat_operation == 0) m = m1 + m2;
    if(mat_operation == 1) m = m1 - m2;
    if(mat_operation == 2) m = m1 * m2;

    QVector<QHBoxLayout *> h_lay;
    QVector<QLabel *> l_lay;
    QVBoxLayout *layout = new QVBoxLayout;
    QString s;
    for(int i = 0; i < m_int; i++){
        h_lay.push_back(new QHBoxLayout);
        for(int j = 0; j < l_int; j++){
            s = QString::number(m.t[i][j]);
            l_lay.push_back(new QLabel(s));
            h_lay.at(i)->addWidget(l_lay.at(i*l_int + j));
        }
        layout->addLayout(h_lay.at(i));
    }
    QPushButton *Return = new QPushButton(tr("return"));
    Return->setDefault(1);
    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(Return);
    button_layout->setAlignment(Qt::AlignRight);
    layout->addLayout(button_layout);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(widget);
    scroll->setGeometry(0, 0, 320, 240);
    tab->insertTab(0, scroll, tr("Matrix"));
    tab->setCurrentIndex(0);

    connect(Return, SIGNAL(clicked()), this, SLOT(mat_open()));
}

void tabwidget::sort_input(){
    QString n_string = sort_n->text();
    int n_int;
    bool ok;
    n_int = n_string.toInt(&ok, 10);
    if(n_int == 0){
        QMessageBox::critical(NULL, "input error!", "You have input a wrong number!", QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
        sort_n->clear();
        return;
    }

    QVBoxLayout *sort_input = new QVBoxLayout;
    QVector<QHBoxLayout *> label_text;
    QVector<QLabel *> label_vector;
    char label_name[50];
    for(int i = 0; i < n_int; i++){
        if(i == 0)
            sprintf(label_name, "Please input the 1st element:");
        else if(i == 1)
            sprintf(label_name, "Please input the 2nd element:");
        else
            sprintf(label_name, "Please input the %dth element:", i + 1);
        label_vector.push_back(new QLabel(tr(label_name)));
        sort_elements.push_back(new QLineEdit);
        label_text.push_back(new QHBoxLayout);
        label_text.at(i)->addWidget(label_vector.at(i));
        label_text.at(i)->addWidget(sort_elements.at(i));
        sort_input->addLayout(label_text.at(i));
    }
    QHBoxLayout *button_layout = new QHBoxLayout;
    QPushButton *submit = new QPushButton(tr("&submit"));
    QPushButton *clear = new QPushButton(tr("&clear"));
    submit->setDefault(true);
    button_layout->addWidget(submit);
    button_layout->addWidget(clear);
    button_layout->setAlignment(Qt::AlignRight);
    sort_input->addLayout(button_layout);

    QWidget *sort_input_widget = new QWidget;
//    sort_input_widget->setMaximumSize();
    sort_input_widget->setLayout(sort_input);
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(sort_input_widget);
    scroll->setGeometry(0, 0, 320, 240);
    tab->removeTab(1);
    tab->insertTab(1, scroll, tr("Sort"));
    tab->setCurrentIndex(1);
    sort_elements[0]->setFocus();

    connect(submit, SIGNAL(clicked()), this, SLOT(sort_output()));
    connect(clear, SIGNAL(clicked()), this, SLOT(sort_clear()));
}

void tabwidget::sort_clear(){
    for(int i = 0; i < sort_elements.size(); i++){
        sort_elements[i]->setText("");
    }
    return;
}

//int cmp(const void *a,const void *b){
//    return *(int *)a - *(int *)b;
//}

void tabwidget::sort_output(){
    int n = sort_elements.size();
    double* array = new double[n];
    for(int i = 0; i < n; i++){
        array[i] = (sort_elements.at(i)->text()).toDouble();
    }
    sort(array, array + n);

    vector<QString> str_vec;
    vector<QLabel*> lab_vec;
    for(int i = 0; i < n; i++){
        str_vec.push_back(QString::number(array[i]));
        lab_vec.push_back(new QLabel(str_vec.at(i)));
    }
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *welcome = new QLabel(tr("Here is the result:"));
    QVBoxLayout *number_layout = new QVBoxLayout;
    QPushButton *Return = new QPushButton(tr("return"));
    Return->setDefault(1);
    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(Return);
    button_layout->setAlignment(Qt::AlignRight);
    for(int i = 0; i < n; i++)
        number_layout->addWidget(lab_vec[i]);
    layout->addWidget(welcome);
    layout->addLayout(number_layout);
    layout->addLayout(button_layout);
//    layout->addStretch();
    tab->removeTab(1);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(widget);
    scroll->setGeometry(0, 0, 320, 240);
    tab->insertTab(1, scroll, "Sort");
    tab->setCurrentIndex(1);

    connect(Return, SIGNAL(clicked()), this, SLOT(sort_open()));
}

void tabwidget::eq_output(){
    QString eq_string = eq->text();
    QString eq_left_string = eq_left->text();
    QString eq_right_string = eq_right->text();
    QString eq_return = QString("initial");
    QString eq_compare = eq_return;
    double eq_solution;

    std::string equation = eq_string.toStdString();
    double left = eq_left_string.toDouble();
    double right = eq_right_string.toDouble();

    try{
        solvex equ(equation.c_str());
        eq_solution = equ.solve_secant_method(left, right);
        //equ.print_postfix();
    }
    catch (string exc)
    {
        eq_return = s2q(exc);
    }
    catch (...)
    {
        eq_return = s2q("未知错误!");
    }

    tab->removeTab(2);

    QVBoxLayout *layout = new QVBoxLayout;
    QLineEdit *output = new QLineEdit;
    QPushButton *Return = new QPushButton(tr("return"));
    Return->setDefault(1);
    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(Return);
    button_layout->setAlignment(Qt::AlignRight);
    char* value_string;
    sprintf(value_string, "x = %6f; ", eq_solution);
    int test = QString::compare(eq_return, eq_compare);
    if(test==0){
        QString value_test = QString(value_string);
        output->setText(value_test);
    }
    else {
        output->setText(eq_return);
    }
    output->setReadOnly(1);
    layout->addWidget(output);
    layout->addLayout(button_layout);
    layout->addStretch();

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    tab->insertTab(2, widget, "Equation");
    tab->setCurrentIndex(2);

    connect(Return, SIGNAL(clicked()), this, SLOT(equation_open()));
}

void tabwidget::integration_output(){
    QString itg_string = itg->text();
    QString itg_left_string = itg_left->text();
    QString itg_right_string = itg_right->text();
    QString itg_return = QString("initial");
    QString itg_compare = itg_return;
    double itg_solution;

    std::string integration = itg_string.toStdString();
    double left = itg_left_string.toDouble();
    double right = itg_right_string.toDouble();

    try{
        calculus itg(integration.c_str());
        itg_solution = itg.getcalculus(left, right);
    }
    catch (string exc)
    {
        itg_return = s2q(exc);
    }
    catch (...)
    {
        itg_return = s2q("未知错误!");
    }

    tab->removeTab(3);

    QVBoxLayout *layout = new QVBoxLayout;
    QLineEdit *output = new QLineEdit;
    QPushButton *Return = new QPushButton(tr("return"));
    Return->setDefault(1);
    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(Return);
    button_layout->setAlignment(Qt::AlignRight);
    char* value_string;
    sprintf(value_string, "Consequence = %lf; ", itg_solution);
    int test = QString::compare(itg_return, itg_compare);
    if(test==0){
        QString value_test = QString(value_string);
        output->setText(value_test);
    }
    else {
        output->setText(itg_return);
    }
    layout->addWidget(output);
    layout->addLayout(button_layout);
    layout->addStretch();

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    tab->insertTab(3, widget, "Integration");
    tab->setCurrentIndex(3);

    connect(Return, SIGNAL(clicked()), this, SLOT(integration_open()));
}

void tabwidget::cal_output(){
    QString cal_string = cal->text();
    QString cal_return = QString("initial");
    QString cal_compare = cal_return;
    double cal_solution;

    std::string calculator = cal_string.toStdString();

    try{
        expr e(calculator.c_str());
        cal_solution = e.result();
        //equ.print_postfix();
    }
    catch (string exc)
    {
        cal_return = s2q(exc);
    }
    catch (...)
    {
        cal_return = s2q("未知错误!");
    }

    tab->removeTab(4);

    QVBoxLayout *layout = new QVBoxLayout;
    QLineEdit *output = new QLineEdit;
    QPushButton *Return = new QPushButton(tr("return"));
    Return->setDefault(1);
    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(Return);
    button_layout->setAlignment(Qt::AlignRight);
//    char* value_string;
//    sprintf(value_string, "the result is = %6f; ", cal_solution);
    int test = QString::compare(cal_return, cal_compare);
    if(test==0){
        QString value_test = QString::number(cal_solution);
        output->setText(value_test);
    }
    else {
        output->setText(cal_return);
    }
    output->setReadOnly(1);
    layout->addWidget(output);
    layout->addLayout(button_layout);
    layout->addStretch();

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    tab->insertTab(4, widget, "Calculator");
    tab->setCurrentIndex(4);

    connect(Return, SIGNAL(clicked()), this, SLOT(cal_open()));
}

tabwidget::tabwidget(QWidget *parent)
    : QDialog(parent)
{
    tab = new QTabWidget();
//    this->setMinimumSize(640, 480);
    this->setWindowTitle("Welcome to MatShow!");

    mat_open();
    tab->setTabToolTip(0, "add, sub and multiply for matrix");
    sort_open();
    tab->setTabToolTip(1, "sort in the increasing order");
    equation_open();
    tab->setTabToolTip(2, "solve a equation in natural language");
    integration_open();
    tab->setTabToolTip(3, "solve a integration in natural language");
    cal_open();
    tab->setTabToolTip(4, "calculate an expression in natural language");
    tab->setCurrentIndex(0);

    eq->setClearButtonEnabled(true);
    itg->setClearButtonEnabled(true);

    QHBoxLayout *toplayout = new QHBoxLayout;
    toplayout->addWidget(tab);
    this->setLayout(toplayout);
}

tabwidget::~tabwidget()
{

}
