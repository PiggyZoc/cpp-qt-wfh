//
// Created by Mac on 2022/11/30.
//

#ifndef CPP_QT_WFH_WINDOW_H
#define CPP_QT_WFH_WINDOW_H


#include <QWidget>
#include "widgets/progress_widget.h"

class QPushButton;
class Window : public QWidget
{
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

signals:
    void counterReached();

private slots:
    void slotButtonClicked(bool checked);
private:
    int m_counter;
    QPushButton *m_button;
    ProgressWidget *m_progress_widget;
};
#endif //CPP_QT_WFH_WINDOW_H
