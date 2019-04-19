#ifndef FUNCTION_H
#define FUNCTION_H

// Local File Stream
#include <qtextstream.h>
#include <qfile.h>

// ETC
#include <QtCore>
#include <QtGui>
#include <qstring.h>
#include <qmessagebox.h>
#include <QObject>

// FTP Management
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

// Reference
#include "memo.h"
#include "ui_memo.h"

class TextData
{
public:
    QString Text_Data;
    void SAVE()
    {
        QFile *file = new QFile;
        file->setFileName("UserData.txt");
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out.setCodec("UTF-8");
        out << Text_Data;
        file->close();
    }
    void LOAD()
    {
        QFile *file = new QFile;
        file->setFileName("UserData.txt");
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        in.setCodec("UTF-8");
        Text_Data = in.readAll();
        file->close();
    }
    void FILE_DELETE()
    {
        QFile *file = new QFile;
        file->setFileName("UserData.txt");
        file->remove();
        file->close();
    }
};

class UserData
{
public:
    QString UserIDfile;
    QString UserPSfile;
    int sqlCount;
    UserData(QString data1, QString data2, int data3)
    {
        file = new QFile;
        file->setFileName("CoreLib32.dll");
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            UserIDfile = data1;
            UserPSfile = data2;
            sqlCount = data3;
            file->close();
        }
        else
        {
            LOAD();
        }
        file->close();
    }

    void LOAD()
    {
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        UserIDfile = in.readLine();
        UserPSfile = in.readLine();
        sqlCount = in.readLine().toInt();
        file->close();
    }

    void SAVE()
    {
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out << UserIDfile << "\n" << UserPSfile << "\n" << sqlCount;
        file->close();
    }

    void FILE_DELETE()
    {
        file->remove();
    }
private:
    QFile *file;
};

class ID_BACK
{
public:
    QFile *file;
    QString ID_Bak;
    ID_BACK()
    {
        file = new QFile;
        file->setFileName("CoreLib64.dll");
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {

        }
        else
        {
            LOAD();
        }
    }
    void SAVE()
    {
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out << ID_Bak;
        file->close();
    }
    void LOAD()
    {
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        ID_Bak = in.readLine();
        file->close();
    }
    void ID_LOAD()
    {
        QFile *file = new QFile;
        file->setFileName("CoreLib32.dll");
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        ID_Bak = in.readLine();
        file->close();
    }
};

class SettingData
{
public:
    int Color;
    int Opcity;
    int Font_Size;
    int Size_Width;
    int Size_Height;
    int Program_Count;

    SettingData()
    {
        QFile *file = new QFile;
        file->setFileName("Setting.txt");
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            Color = 1;
            Opcity = 100;
            Font_Size = 10;
            Size_Width = 274;
            Size_Height = 383;
            Program_Count = 0;
        }
        else
        {
            LOAD();
        }
        file->close();
    }

    void SAVE()
    {
        QFile *file = new QFile;
        file->setFileName("Setting.txt");
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out << Color << "\n" << Opcity << "\n" << Font_Size
            << "\n" << Size_Width << "\n" << Size_Height
            << "\n" << Program_Count;
        file->close();
    }

    void LOAD()
    {
        QFile *file = new QFile;
        file->setFileName("Setting.txt");
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        Color = in.readLine().toInt();
        Opcity = in.readLine().toInt();
        Font_Size = in.readLine().toInt();
        Size_Width = in.readLine().toInt();
        Size_Height = in.readLine().toInt();
        Program_Count = in.readLine().toInt();
        file->close();
    }

    void FILE_DELETE()
    {
        QFile *file = new QFile;
        file->setFileName("Setting.txt");
        file->remove();
        file->close();
    }
};

class FTPData : public QObject
{
    Q_OBJECT
public slots:
    void downloadFinished(QNetworkReply *reply)
    {
        file = new QFile("UserData.txt");
        if(file->open(QIODevice::Append))
        {
            file->write(reply->readAll());
            file->flush();
            file->close();
        }
        localData.LOAD();
    }
    void uploadFinished(QNetworkReply *reply)
    {
        if(!reply->error())
        {
            file->close();
            file->deleteLater();
            reply->deleteLater();
        }
    }
    void Upload_SUB()
    {
        UserData temp0(NULL,NULL,NULL);
        url.setUrl("ftp://baealex.iptime.org/TextServer/"+temp0.UserIDfile+".txt");
        url.setUserName("TextAdmin");
        url.setPassword("password486");
        url.port(21);
        file = new QFile("UserData.txt");
        if (file->open(QIODevice::ReadOnly))
        {
            m_manager->put(QNetworkRequest(url), file);
        }
        timer1->stop();
    }

public:
    QTimer *timer1;
    FTPData(TextData &ref) :
        localData(ref)
    {
        m_manager = new QNetworkAccessManager(this);
        timer1 = new QTimer;
        QObject::connect(m_manager,SIGNAL(finished(QNetworkReply*)),
                this,SLOT(downloadFinished(QNetworkReply*)));
        QObject::connect(m_manager,SIGNAL(finished(QNetworkReply*)),
                this,SLOT(uploadFinished(QNetworkReply*)));
        QObject::connect(timer1,SIGNAL(timeout()),
                         this,SLOT(Upload_SUB()));
    }

    void Upload()
    {
        UserData temp0(NULL,NULL,NULL);
        url.setUrl("ftp://baealex.iptime.org/TextServer/"+temp0.UserIDfile+".txt");
        url.setUserName("TextAdmin");
        url.setPassword("password486");
        url.port(21);
        file = new QFile("UserData.txt");
        if (file->open(QIODevice::ReadOnly))
        {
            m_manager->put(QNetworkRequest(url), file);
        }
    }

    void Download()
    {
        UserData temp0(NULL,NULL,NULL);
        url.setUrl("ftp://baealex.iptime.org/TextServer/"+temp0.UserIDfile+".txt");
        url.setUserName("TextAdmin");
        url.setPassword("password486");
        url.port(21);
        m_manager->get(QNetworkRequest(url));
    }
private:
    QNetworkAccessManager *m_manager;
    QFile *file;
    QUrl url;
    TextData &localData;
};

#endif // FUNCTION_H
