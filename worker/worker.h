//
// Created by Mac on 2022/11/30.
//

#ifndef CPP_QT_WFH_WORKER_H
#define CPP_QT_WFH_WORKER_H


#include <QObject>

class Worker: public QObject {
    Q_OBJECT
public:
    Worker(QString *path);
public slots:
    void doWork();
private:
    std::vector<std::string> splitString(const std::string& str);
    bool pathCheck(const std::string& path);
signals:
    void onOnePathCheckFinish(bool);
private:
    QString *buffer;
};


#endif //CPP_QT_WFH_WORKER_H
