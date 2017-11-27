#ifndef READER_H
#define READER_H
#include <QObject>
#include <QDebug>
class Reader:public QObject
{
    Q_OBJECT
public:
    Reader();
    void recevieNewsPaper(const QString & name)
    {
        qDebug()<<"recevie newspaper:"<<name;
    }
};

#endif // READER_H
