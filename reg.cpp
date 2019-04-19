#include "reg.h"
#include "ui_reg.h"
#include "login.h"
#include "ui_login.h"

reg::reg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reg)
{
    ui->setupUi(this);
}

reg::~reg()
{
    delete ui;
}

void reg::on_pushButton_clicked()
{
   Login regs;
   QString UserID, UserPW, UserMAIL;
   regs.OpenSQL();
   ui->loglabel->setText("Server Online");
   UserID = ui->idFill->text();
   UserPW = ui->pwFill->text();
   UserMAIL = ui->mailFill->text();
   QSqlQuery qry;
   if (UserID == "" || UserPW == "" || UserMAIL == "" )
   {
      QMessageBox::information(this, "info", "ID or PW or MAIL EMPTY!");
      ui->loglabel->setText("ID or PW or MAIL EMPTY!");
   }
   else
   {
      if (qry.exec("SELECT UserID FROM MemberINFO WHERE UserID='" + UserID + "\'")) {
         if (qry.next())
         {
            QMessageBox::information(this, "info", "Exist ID");
            ui->loglabel->setText("Exist!");
         }
         else
         {
            ui->loglabel->setText("Created");
            qry.exec("INSERT INTO MemberINFO VALUES ('" + UserID + "','" + UserPW + "','" + UserMAIL + "');");
            qry.exec("INSERT INTO MemberSTATUS VALUES('" + UserID + "','0.0.0.0',0,0);");
            qry.exec("update MemberINFO set UserID = rtrim(replace(UserID, ' ', ''));");
            qry.exec("update MemberINFO set UserPW = rtrim(replace(UserPW, ' ', ''));");
            qry.exec("update MemberINFO set UserMAIL = rtrim(replace(UserMAIL, ' ', ''));");
            QMessageBox::information(this, "info", "Done!");
            close();
         }
      }
   }
}

void reg::on_pushButton_2_clicked() // EXIT BUTTON
{
    close();
}
