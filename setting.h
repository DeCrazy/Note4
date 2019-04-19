#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "memo.h"

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(Memo &ref,QWidget *parent = 0);
    ~Setting();

private slots:
    void on_theme_white_clicked();
    void on_theme_yellow_clicked();
    void on_theme_pink_clicked();
    void on_theme_blue_clicked();
    void on_theme_green_clicked();
    void on_horizontalSlider_sliderMoved(int position);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::Setting *ui;
    Memo &Noteref;
};

#endif // SETTING_H
