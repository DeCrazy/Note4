#include "memo.h"
#include "ui_memo.h"
#include "setting.h"
#include "function.h"

TextData MyData;
FTPData FTP(MyData);
bool isMouseDown = false;

Memo::Memo(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::Memo)
{
    ui->setupUi(this);
    setCentralWidget(ui->MainText);

    // Counter Compere
    SettingData myCount;
    UserData sqlCount(NULL,NULL,NULL);

    //-------------------------------------------------------------------------------------------------//
    QFile *file = new QFile("UserData.txt");
    int LoginState = 0;
    if(myCount.Program_Count == sqlCount.sqlCount)
    {
        if(sqlCount.sqlCount == 1)
        {
            LoginState = 1;
        }
        else if(sqlCount.sqlCount!=1)
        {
            if(file->open(QIODevice::ReadOnly | QIODevice::Text))
            {
                LoginState = 2;
            }
            else if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
            {
                LoginState = 3;
            }
        }
    }
    else if(myCount.Program_Count != sqlCount.sqlCount)
    {
        if(sqlCount.sqlCount == 1)
        {
            LoginState = 1;
        }
        else if(sqlCount.sqlCount != 1)
        {
            LoginState = 3;
        }
    }

    switch (LoginState) {
    case 1:
        MyData.SAVE();
        ui->MainText->appendPlainText("Welcome Thank's for using this program. Start your first 'MEMO'");
        break;
    case 2:
        MyData.LOAD();
        ui->MainText->appendPlainText(MyData.Text_Data);
        file->close();
        break;
    case 3:
        QMessageBox::StandardButton myreply;
        myreply = QMessageBox::question(this,"Notice",
                              "Your Data File Download Form FTP Server?",
                              QMessageBox::Yes | QMessageBox::No);
        if(myreply==QMessageBox::Yes)
        {
            FTP.Download();
            QMessageBox box;
            box.setText("Loading File...");
            box.exec();
            ui->MainText->appendPlainText(MyData.Text_Data);
        }
        else
        {
            MyData.SAVE();
        }
        break;
    }

    // Visual Data Management & Counter Same Set
    SettingData UserSetData;
    Visual_Load(UserSetData.Color,UserSetData.Opcity,UserSetData.Font_Size);
    UserSetData.Program_Count = sqlCount.sqlCount;
    UserSetData.SAVE();
}

void Memo::Visual_Load(int x, int y,int z)
{
    QPalette qpalette; // Color Changer Var
    int RED,GREEN,BLUE; // Color Value
    switch (x) {
    case 1:
        RED = 255, GREEN = 255, BLUE = 255;
        break;
    case 2:
        RED = 255, GREEN = 239, BLUE = 133;
        break;
    case 3:
        RED = 255, GREEN = 178, BLUE = 245;
        break;
    case 4:
        RED = 178, GREEN = 204, BLUE = 255;
        break;
    case 5:
        RED = 228, GREEN = 247, BLUE = 186;
        break;
    }
    qpalette.setColor(QPalette::Base,QColor(RED,GREEN,BLUE,255));
    ui->MainText->setPalette(qpalette);

    qpalette.setColor(QPalette::Window,QColor(RED,GREEN,BLUE,230));
    setPalette(qpalette);

    setWindowOpacity((float)y/100);

    QFont font;
    font.setPixelSize(z);
    ui->MainText->setFont(font);
}

Memo::~Memo()
{
    delete ui;
}

void Memo::on_actionExit_triggered()
{
    // Text Local Save
    MyData.Text_Data = ui->MainText->toPlainText();
    MyData.SAVE();

    close();
}

void Memo::on_actionSetting_triggered()
{
    Setting UserSet(*this);
    UserSet.setModal(true);
    UserSet.exec();
    UserSet.show();
}

void Memo::on_MainText_textChanged()
{
    MyData.Text_Data = ui->MainText->toPlainText();
    MyData.SAVE();
    FTP.timer1->start(3000);
}

void Memo::on_actionSync_triggered()
{
    FTP.Upload();
}

void Memo::mousePressEvent(QMouseEvent *event) {
   if (event->button() == Qt::LeftButton) {
      isMouseDown = true;
   }
}

void Memo::mouseReleaseEvent(QMouseEvent *event) {
   isMouseDown = false;
}

void Memo::mouseMoveEvent(QMouseEvent *event) {
   if (isMouseDown == true) {
      mousePoint = event->globalPos();
      move(mousePoint.x()-100,mousePoint.y()-200);
   }
}
