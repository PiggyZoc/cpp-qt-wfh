//
// Created by Mac on 2022/11/30.
//
#include <QProgressBar>
#include <iostream>
#include "progress_widget.h"



ProgressWidget::ProgressWidget
(QWidget *parent) {
    setFixedSize(400,300);
    m_progress_bar = new QProgressBar(this);
    m_progress_bar->setRange(0,100);
    m_progress_bar->setValue(0);
    m_progress_bar->setGeometry(10, 10, 280, 30);
    progress_num = 0;
    m_button = new QPushButton("TRIGGER",this);
    m_button->setGeometry(10,30,80,30);
    m_button->setCheckable(true);
    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(handleLargeFile()),Qt::QueuedConnection);
    filename = new QString("/Users/mac/Desktop/pyqt-wfh/large.log");
    // pool = new QThreadPool(this);
   //  pool->setMaxThreadCount(4);
   // handleLargeFile();
//    QString *m = new QString("aasasa");
//    MyRunnable *task = new MyRunnable(m);
//    task->setAutoDelete(true);
//    QString *e = new QString("dddd");
//    MyRunnable *task1 = new MyRunnable(e);
//    task->setAutoDelete(true);
//
//    pool->start(task);
//    pool->start(task1);
}

void ProgressWidget::handleLargeFile() {
//    int SIZE = 1024*1024*2;
//    char buffer[1024*1024*3];
    auto start = std::chrono::system_clock::now();
    m_progress_bar->setMaximum(countLineNum(filename->toStdString().c_str()));
    int offsets[16000][3];
    FILE *fp;
    fp = fopen(filename->toStdString().c_str(),"r");
    if(!fp)
    {
        qDebug("Unable to Open File %s", qUtf8Printable(*filename));
        return;
    }
    fseek(fp,0,SEEK_END);
    int file_size = ftell(fp);
    int SIZE = file_size / 8 ;
    char* buffer = new char[SIZE+1024];
    printf("%d \n", file_size);
    fseek(fp,0,SEEK_SET);
    int seek = 0;
    int j = 0;

    while (true) {
        if (seek+SIZE >= file_size) {
            SIZE = file_size - seek;
            if(SIZE == 0) {
                break;
            }
        }
        fread(buffer, sizeof(char), SIZE, fp);
        char in = '0';
        int idx = SIZE;
        while (buffer[SIZE-1] != '\n' && in != '\n' && in != EOF) {
            fscanf(fp, "%c", &in);
            buffer[idx] = in;
            idx++;
        }
        buffer[idx-1] = '\0';
        QString* buf = new QString(buffer);
        QThread* m_thread = new QThread();
        Worker* worker = new Worker(buf);
        worker->moveToThread(m_thread);
        connect(worker, SIGNAL(onOnePathCheckFinish(bool)), this, SLOT(onReceiveValue(bool)));
        connect(m_thread, SIGNAL(started()), worker, SLOT(doWork()));

        m_thread->start();
        //        std::vector<std::string> tokens = splitString(buffer);
//        for (auto const &token: tokens) {
//            const char *cstr = token.c_str();
//            QString *filepath = new QString(cstr);
//            MyRunnable *task = new MyRunnable(filepath);
//            Worker *worker = new Worker(filepath);
//            connect(worker, &Worker::onCheckFinish,  this, &ProgressWidget::onReceiveValue,Qt::BlockingQueuedConnection);
//            this->pool->enqueue(path_check,worker);
//            //std::this_thread::sleep_for(std::chrono::seconds(8));
//        }
        offsets[j][0] = seek;
        offsets[j][1] = idx;
        seek = seek + idx;
        j++;
        if(seek >= file_size) {
            printf("END \n");
            break;
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: "<< elapsed_seconds.count() << "s" << std::endl;

}


void ProgressWidget::onReceiveValue(bool is_exist) {
    progress_num ++;
    m_progress_bar->setValue(progress_num);
  //  qDebug("Received!");
//    if (is_exist) {
//        qDebug("Exist!");
//    } else {
//        qDebug("Error");
//    }
}

unsigned int ProgressWidget::countLineNum(const char *filename) {
    unsigned int num = 0;
    int offsets[16000][3];
    FILE *fp;
    fp = fopen(filename,"r");
    if(!fp)
    {
        fprintf(stderr,"Unable to open %s\n", filename);
        return (1);
    }
    fseek(fp,0,SEEK_END);
    int file_size = ftell(fp);
    int SIZE = file_size / 18 ;
    char* buffer = new char[SIZE+1024];
    printf("%d \n", file_size);
    fseek(fp,0,SEEK_SET);
    int seek = 0;
    int j = 0;
//    std::ofstream out;
//    out.open("out.log",std::ios::app);
    while (true) {
        if (seek+SIZE >= file_size) {
            SIZE = file_size - seek;
            if(SIZE == 0) {
                break;
            }
        }
        fread(buffer, sizeof(char), SIZE, fp);
        char in = '0';
        int idx = SIZE;
        while (buffer[SIZE-1] != '\n' && in != '\n' && in != EOF) {
            fscanf(fp, "%c", &in);
            buffer[idx] = in;
            idx++;
        }
        buffer[idx-1] = '\0';
        //process(buffer);
        std::vector<std::string> tokens = splitString(buffer);
        num = num + tokens.size();
//        for (auto const &token: tokens) {
//
//            const char *cstr = token.c_str();
//            //out << (char *)cstr << '\n';
//            results.emplace_back(pool.enqueue(path_exist,(char *)cstr));
//        }
        offsets[j][0] = seek;
        offsets[j][1] = idx;
        seek = seek + idx;
        j++;
        if(seek >= file_size) {
            printf("END \n");
            break;
        }
    }
    return num;
}

std::vector<std::string> ProgressWidget::splitString(const std::string &str) {
    std::vector<std::string> tokens;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find('\n', prev)) != std::string::npos) {
        tokens.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    tokens.push_back(str.substr(prev));

    return tokens;
}
