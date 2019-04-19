#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

#include "memo.h"
#include "reg.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void Next_Form();
    void OpenSQL();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::Login *ui;
    Memo *MainNote;
    QSqlDatabase db;
};

#endif // LOGIN_H
