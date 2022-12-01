//
// Created by Mac on 2022/11/30.
//

#ifndef CPP_QT_WFH_WORKER_H
#define CPP_QT_WFH_WORKER_H


#include <QObject>
#include "../utilities.h"

class Worker: public QObject {
    Q_OBJECT
public:
    Worker(QString *path);
    ~Worker();
public slots:
    void doWork();
private:
    bool pathCheck(const std::string& path);
signals:
    void onOnePathCheckFinish(bool);
signals:
    void workFinished();
private:
    QString *buffer;
};


#endif //CPP_QT_WFH_WORKER_H
