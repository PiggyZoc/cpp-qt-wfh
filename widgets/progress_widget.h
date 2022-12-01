//
// Created by Mac on 2022/11/30.
//

#ifndef CPP_QT_WFH_PROGRESS_WIDGET_H
#define CPP_QT_WFH_PROGRESS_WIDGET_H
#include <QWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QThread>
#include "../ThreadPool.h"
#include "../worker/worker.h"
#include "../utilities.h"

class ProgressWidget: public QWidget{
    Q_OBJECT
public:
    ProgressWidget(QWidget *parent=0);
private slots:
    void handleLargeFile();
private slots:
    void onReceiveValue(bool is_exist);
private:
    unsigned int countLineNum(const char* filename);
private:
    QProgressBar *m_progress_bar;
    QPushButton *m_button;
    QString *filename;
    int progress_num;
};


#endif //CPP_QT_WFH_PROGRESS_WIDGET_H
