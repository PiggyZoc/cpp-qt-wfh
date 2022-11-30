//
// Created by Mac on 2022/11/30.
//

#ifndef CPP_QT_WFH_MY_RUNNABLE_H
#define CPP_QT_WFH_MY_RUNNABLE_H

#include <QRunnable>

class MyRunnable :  public QRunnable{
public:
explicit MyRunnable(QString *path);

protected:
    void run();


private:
    QString *path;
};


#endif //CPP_QT_WFH_MY_RUNNABLE_H
