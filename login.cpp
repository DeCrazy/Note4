#include "login.h"
#include "ui_login.h"
#include "function.h"

Login::Login(QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    UserData temp0(NULL,NULL,NULL);
    ui->idFill->setText(temp0.UserIDfile);
    ui->pwFill->setText(temp0.UserPSfile);
    temp0.FILE_DELETE();
}

void Login::Next_Form()
{
    this->close();
    MainNote = new Memo(this);
    MainNote->show();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    OpenSQL();
    QString UserID, UserPW;		//id, pw 텍스트 받아오기
    UserID = ui->idFill->text();
    UserPW = ui->pwFill->text();

    QSqlQuery qry;		//쿼리 생성

    if (qry.exec("SELECT UserID, UserPW FROM MemberINFO WHERE UserID='" + UserID + "\' AND UserPW='" + UserPW + "\'"));
        {
            if (qry.next())
            {
                ui->testlabel->setText("9ood");
                QMessageBox::information(this, "LoginInfo", "Logined");
                hide();
                qry.exec("UPDATE MemberSTATUS SET UserIP = 'IPADDR', UserIS_ON = 1 WHERE UserID_S = '"+UserID+"';");
                qry.exec("UPDATE MemberSTATUS SET UserCOUNT = UserCOUNT + 1 WHERE UserID_S='"+UserID+"';");

                // SQL Program Counter ++
                QSqlQuery qry2("SELECT userCount FROM MemberSTATUS WHERE userid_s='"+UserID+"';");
                int test = qry2.record().indexOf("userCount");
                int sqrCount;
                while(qry2.next())
                {
                    sqrCount = qry2.value(test).toInt();
                }

                // Local Program Counter ++
                ID_BACK BACKID;
                TextData mTextData;
                SettingData UserSet;
                if(QString::compare(UserID, BACKID.ID_Bak, Qt::CaseInsensitive) == 0 || UserSet.Program_Count == 0)
                {
                    UserSet.Program_Count++;
                    UserSet.SAVE();
                }
                else
                {
                    UserSet.FILE_DELETE();
                    mTextData.FILE_DELETE();
                    SettingData newUserSet;
                    newUserSet.SAVE();
                }

                UserData temp0(UserID,UserPW,sqrCount);
                temp0.SAVE();

                BACKID.ID_LOAD();
                BACKID.SAVE();
                Next_Form();
            }
            else
            {
                ui->testlabel->setText("Worng ID or Password");
                QMessageBox::information(this, "LoginInfo", "Worng ID or Password");
            }
        }
}

void Login::OpenSQL()
{
    QString servername = "decrazy.iptime.org,8989";					//SQL 서버 주소
    QString dbname = "TEST";												//SQL DB 이름
    QString dbid = "Testing";												//SQL ID
    QString dbpw = "gksfk2014";											//SQL 비밀번호
    db = QSqlDatabase::addDatabase("QODBC3");						//ODBC 드라이버
    db.setConnectOptions();

    QString dsn = QString("DRIVER={SQL Server};"
        "SERVER=%1;DATABASE=%2;UID=%3;PWD=%4;").arg(servername).arg(dbname).arg(dbid).arg(dbpw);
    //DRIVER = {SQL 드라이버}; SERVER = servername //SQL 서버이름; DATABASE = dbname //DB이름; UID = dbid;
    //DB 아이디 PWD = dbpw; //DB 비번 Trusted_Connection = ; //보안연결 ").arg(servername).arg(dbname).arg(dbid).arg(dbpw); 위에따로빼준거
    db.setDatabaseName(dsn);

    if (db.open()) //서버상태
    {
    }
    else
    {
        QMessageBox::information(this, "ServerINFO", "Offline");
    }
} //SQL 여는 함수

void Login::on_pushButton_3_clicked()
{
    close();
}

void Login::on_pushButton_2_clicked()
{
    reg reg_window(this);
    reg_window.setModal(true);
    reg_window.exec();
    reg_window.show();
}
