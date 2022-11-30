//
// Created by Mac on 2022/11/30.
//
#include <QProgressBar>
#include "progress_widget.h"

ProgressWidget::ProgressWidget
(QWidget *parent) {
    setFixedSize(400,300);
    m_progress_bar = new QProgressBar(this);
    m_progress_bar->setRange(0,100);
    m_progress_bar->setValue(0);
    m_progress_bar->setGeometry(10, 10, 280, 30);

    m_button = new QPushButton("TRIGGER",this);
    m_button->setGeometry(10,30,80,30);
    m_button->setCheckable(true);
    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(handleLargeFile()),Qt::QueuedConnection);
    filename = new QString("/Users/mac/Desktop/pyqt-wfh/large.log");
    pool = new QThreadPool(this);
    pool->setMaxThreadCount(4);
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
    int SIZE = 1024*1024*2;
    char buffer[1024*1024*3];
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
    printf("%d \n", file_size);
    fseek(fp,0,SEEK_SET);
    int seek = 0;
    int j = 0;

    while (true) {
        if (seek+SIZE >= file_size) {
            break;
        }
        fread(buffer, sizeof(char), SIZE, fp);
        char in = '0';
        int idx = SIZE;
        while (buffer[SIZE-1] != '\n' && in != '\n' && in != EOF) {
            fscanf(fp, "%c", &in);
            buffer[idx] = in;
            idx++;
        }
        buffer[idx] = '\0';

        std::vector<std::string> tokens = splitString(buffer);
        for (auto const &token: tokens) {
            const char *cstr = token.c_str();
            QString *filepath = new QString(cstr);
            MyRunnable *task = new MyRunnable(filepath);
            //connect(task, SIGNAL(sendSignal(bool)),  this, SLOT(onReceiveValue(bool)));
            this->pool->start(task);
            //std::this_thread::sleep_for(std::chrono::seconds(8));
        }
        offsets[j][0] = seek;
        offsets[j][1] = idx;
        seek = seek + idx;
        j++;
        if(seek >= file_size) {
            printf("END \n");
            break;
        }
    }

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

void ProgressWidget::onReceiveValue(bool is_exist) {
    qDebug("Received!");
    if (is_exist) {
        qDebug("Exist!");
    } else {
        qDebug("Error");
    }
}
