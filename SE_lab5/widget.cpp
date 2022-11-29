#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QPlainTextEdit>
#include <QStringList>
#include <QString>
#include <QList>
#include <QTextEdit>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QFile temp("result.csv");
    temp.open(QIODeviceBase::WriteOnly);
    QTextStream aStream(&temp);
    aStream << "file1,file2,result" << Qt::endl;
    temp.close();
    QFile file("equal.csv");
    file.open(QIODeviceBase::ReadOnly);
    static QList<QStringList> filenames;
    while(!file.atEnd())
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList filename = line.split(',');
            if(filename[0] == "file1")
                continue;
            filenames.push_back(filename);
        }
    }
    file.close();
    static int i = 0;
    setContent(filenames,i);i++;
    connect(ui->pushButton,&QPushButton::clicked,this,[&](){
        bool judge = setContent(filenames,i);i++;
        if(judge==false)
            return;
        writeToFile("result.csv",filenames,i,"equal");
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[&](){
        setContent(filenames,i);i++;
        if(i > filenames.size())
            return;
        writeToFile("result.csv",filenames,i,"inequal");
    });
    connect(ui->pushButton_3,&QPushButton::clicked,this,[&](){
        setContent(filenames,i);i++;
        if(i > filenames.size())
            return;
        writeToFile("result.csv",filenames,i,"doubt");
    });

}

Widget::~Widget()
{
    delete ui;
}

bool Widget::setContent(QList<QStringList> filenames,int i)
{
    if(i >= filenames.size())
    {
        QMessageBox::information(this,"提示","已经全部判断结束，可以退出程序！");
        return false;
    }
    QFile file1(filenames[i][0]);
    file1.open(QIODeviceBase::ReadOnly);
    QString content1;
    while(!file1.atEnd())
    {
        QTextStream in(&file1);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            content1 += line + '\n';
        }
    }
    file1.close();
    ui->textEdit->setText(content1);
    QFile file2(filenames[i][1]);
    file2.open(QIODeviceBase::ReadOnly);
    QString content2;
    while(!file2.atEnd())
    {
        QTextStream in(&file2);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            content2 += line + '\n';
        }
    }
    file2.close();
    ui->textEdit_2->setText(content2);
    return true;
}

void Widget::writeToFile(QString file,QList<QStringList> filenames,int i,QString state)
{
    if(i >= filenames.size())
    {
        QMessageBox::information(this,"提示","已经全部判断结束，可以退出程序！");
        return;
    }
    QFile f(file);
    f.open(QIODeviceBase::Append);
    QTextStream aStream(&f);
    qDebug()<<filenames[i][0] << "," << filenames[i][1] << "," << state ;
    QString result = filenames[i][0] + "," + filenames[i][1] + "," + state + '\n';
    result = result.toUtf8();
    aStream << result << Qt::endl;

    f.close();
    return;
}

