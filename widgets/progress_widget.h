//
// Created by Mac on 2022/11/30.
//

#ifndef CPP_QT_WFH_PROGRESS_WIDGET_H
#define CPP_QT_WFH_PROGRESS_WIDGET_H
#include <QWidget>
#include <QProgressBar>
#include <QThreadPool>
#include <QPushButton>
#include <QSemaphore>
#include "../runner/my_runnable.h"

class ProgressWidget: public QWidget{
    Q_OBJECT
public:
    ProgressWidget(QWidget *parent=0);
private slots:
    void handleLargeFile();
private slots:
    void onReceiveValue(bool is_exist);
private:
    std::vector<std::string> splitString(const std::string& str);
private:
    QProgressBar *m_progress_bar;
    QPushButton *m_button;
    QString *filename;
    QThreadPool *pool;
};


#endif //CPP_QT_WFH_PROGRESS_WIDGET_H
