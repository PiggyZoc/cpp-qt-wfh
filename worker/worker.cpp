//
// Created by Mac on 2022/11/30.
//

#include <thread>
#include <iostream>
#include "worker.h"

Worker::Worker(QString *buffer) {
    this->buffer = buffer;
}

void Worker::doWork() {
    auto start = std::chrono::system_clock::now();
    std::vector<std::string> tokens = splitString( this->buffer->toStdString());
    for (auto const &token: tokens) {

       bool is_exist =  pathCheck(token);
       emit onOnePathCheckFinish(is_exist);
        //printf("%s \n",cstr );
        //out << (char *)cstr << '\n';
        // results.emplace_back(pool.enqueue(path_exist,(char *)cstr));
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: "<< elapsed_seconds.count() << "s" << std::endl;
    emit workFinished();
}


bool Worker::pathCheck(const std::string &path) {
    FILE *file;
    file = fopen(path.c_str(), "r");
    bool is_exist = true;
    if (file) {
        fclose(file);
        //qDebug("Path %s Exists", path.c_str());
    } else {
        is_exist = false;
        //qDebug("Path %s Invalid",path.c_str());
    }
    return is_exist;
}

Worker::~Worker() {
    qDebug("I am gone!");
}


