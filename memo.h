#ifndef MEMO_H
#define MEMO_H

#include <QMainWindow>

namespace Ui {
class Memo;
}

class Memo : public QMainWindow
{
    Q_OBJECT
private:

public:
    explicit Memo(QWidget *parent = 0);
    ~Memo();
    Ui::Memo *ui;
    void Visual_Load(int x,int y,int z);

private slots:
    void on_actionExit_triggered();
    void on_actionSetting_triggered();
    void on_MainText_textChanged();
    void on_actionSync_triggered();

protected:
   void mousePressEvent(QMouseEvent * event);
   void mouseReleaseEvent(QMouseEvent * event);
   void mouseMoveEvent(QMouseEvent * event);
   QPoint mousePoint;
};

#endif // MEMO_H
