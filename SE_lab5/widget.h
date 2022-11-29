#ifndef WIDGET_H
#define WIDGET_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    bool setContent(QList<QStringList> filenames,int i);
    void writeToFile(QString file,QList<QStringList> filenames,int i,QString state);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
