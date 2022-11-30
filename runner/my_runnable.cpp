//
// Created by Mac on 2022/11/30.
//
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "my_runnable.h"
#include <QDebug>

void MyRunnable::run() {
    FILE *file;
    file = fopen(path->toStdString().c_str(), "r");
    bool is_exist = true;
    if (file) {
        fclose(file);
        qDebug("Path %s Exists", qUtf8Printable(*path));
    } else {
        is_exist = false;
        qDebug("Path %s Invalid",qUtf8Printable(*path));
    }
    std::this_thread::sleep_for(std::chrono::seconds(8));
    //QMetaObject::invokeMethod(this->obj,"onReceiveValue",Qt::DirectConnection, Q_ARG(bool,is_exist));
    //emit sendSignal(is_exist);
}

MyRunnable::MyRunnable(QString *path) {
    this->path = path;
}

