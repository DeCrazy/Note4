#include "setting.h"
#include "ui_setting.h"
#include "memo.h"
#include "ui_memo.h"
#include "function.h"

Setting::Setting(Memo &ref,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting),
    Noteref(ref)
{
    ui->setupUi(this);
    SettingData SetData;
    ui->horizontalSlider->setValue(SetData.Opcity);
    ui->spinBox->setValue(SetData.Font_Size);
}

Setting::~Setting()
{
    delete ui;
}

QPalette qpalette; // Color Changer Var
int RED,GREEN,BLUE; // Color Value

void Setting::on_theme_white_clicked()
{
    SettingData SetData;
    RED = 255, GREEN = 255, BLUE = 255;
    qpalette.setColor(QPalette::Base,QColor(RED,GREEN,BLUE,255));
    Noteref.ui->MainText->setPalette(qpalette);

    qpalette.setColor(QPalette::Window,QColor(RED,GREEN,BLUE,230));
    Noteref.setPalette(qpalette);
    SetData.Color = 1;
    SetData.SAVE();
}

void Setting::on_theme_yellow_clicked()
{
    SettingData SetData;
    RED = 255, GREEN = 239, BLUE = 133;
    qpalette.setColor(QPalette::Base,QColor(RED,GREEN,BLUE,255));
    Noteref.ui->MainText->setPalette(qpalette);

    qpalette.setColor(QPalette::Window,QColor(RED,GREEN,BLUE,230));
    Noteref.setPalette(qpalette);
    SetData.Color = 2;
    SetData.SAVE();
}

void Setting::on_theme_pink_clicked()
{
    SettingData SetData;
    RED = 255, GREEN = 178, BLUE = 245;
    qpalette.setColor(QPalette::Base,QColor(RED,GREEN,BLUE,255));
    Noteref.ui->MainText->setPalette(qpalette);

    qpalette.setColor(QPalette::Window,QColor(RED,GREEN,BLUE,230));
    Noteref.setPalette(qpalette);
    SetData.Color = 3;
    SetData.SAVE();
}

void Setting::on_theme_blue_clicked()
{
    SettingData SetData;
    RED = 178, GREEN = 204, BLUE = 255;
    qpalette.setColor(QPalette::Base,QColor(RED,GREEN,BLUE,255));
    Noteref.ui->MainText->setPalette(qpalette);

    qpalette.setColor(QPalette::Window,QColor(RED,GREEN,BLUE,230));
    Noteref.setPalette(qpalette);
    SetData.Color = 4;
    SetData.SAVE();
}

void Setting::on_theme_green_clicked()
{
    SettingData SetData;
    RED = 228, GREEN = 247, BLUE = 186;
    qpalette.setColor(QPalette::Base,QColor(RED,GREEN,BLUE,255));
    Noteref.ui->MainText->setPalette(qpalette);

    qpalette.setColor(QPalette::Window,QColor(RED,GREEN,BLUE,230));
    Noteref.setPalette(qpalette);
    SetData.Color = 5;
    SetData.SAVE();
}

void Setting::on_horizontalSlider_sliderMoved(int position)
{
    SettingData SetData;
    float Opcity = ((float)position/100);
    if(position > 30)
    {
        Noteref.setWindowOpacity(Opcity);
        SetData.Opcity = position;
        SetData.SAVE();
    }
}

void Setting::on_spinBox_valueChanged(int arg1)
{
    SettingData SetData;
    QFont font;
    font.setPixelSize(arg1);
    Noteref.ui->MainText->setFont(font);
    SetData.Font_Size = arg1;
    SetData.SAVE();
}
