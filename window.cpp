//
// Created by Mac on 2022/11/30.
//

#include "window.h"
#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>

Window::Window(QWidget *parent) :
 QWidget(parent) {
    setFixedSize(800,600);
    QVBoxLayout *qvBoxLayout = new QVBoxLayout();
    l_button = new QPushButton("lint check",this);
    l_button->setGeometry(10,10,80,30);
    l_button->setCheckable(true);
    m_button = new QPushButton("async.list",this);
    m_button->setGeometry(10,10,80,30);
    m_button->setCheckable(true);
    qvBoxLayout->addWidget(l_button);
    qvBoxLayout->addWidget(m_button);
    this->setLayout(qvBoxLayout);
    m_counter = 0;
    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(slotButtonClicked(bool)));
    connect(this, SIGNAL (counterReached()), QApplication::instance(), SLOT (quit()));
}

void Window::slotButtonClicked(bool checked) {
   if(checked) {
       m_button->setText("Checked");
       m_progress_widget = new ProgressWidget();
       m_progress_widget->show();
   } else {
       m_button->setText("Hello World");
   }
   m_counter ++;
   if (m_counter == 10) {
       emit counterReached();
   }
}

