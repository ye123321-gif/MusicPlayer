/********************************************************************************
** Form generated from reading UI file 'mymain.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAIN_H
#define UI_MYMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyMain
{
public:
    QWidget *title_widget;
    QLineEdit *lineEdit;
    QPushButton *pushButton_cloth;
    QPushButton *pushButton_search;
    QPushButton *pushButton_close;
    QPushButton *pushButton_min;
    QTableWidget *tableWidget;
    QListWidget *listWidget_musiclist;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPushButton *pushButton_album2;
    QPushButton *pushButton_album3;
    QPushButton *pushButton_album4;
    QPushButton *pushButton_album1;
    QWidget *page_2;
    QListWidget *listWidget_lyrics;
    QWidget *widget_bottom;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider_music;
    QLabel *label_starttime;
    QLabel *label_endtime;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_prev;
    QPushButton *pushButton_next;
    QPushButton *pushButton_like;
    QPushButton *pushButton_lyrics;
    QListWidget *listWidget;
    QPushButton *pushButton_volume;
    QLabel *label;

    void setupUi(QWidget *MyMain)
    {
        if (MyMain->objectName().isEmpty())
            MyMain->setObjectName(QStringLiteral("MyMain"));
        MyMain->resize(830, 550);
        MyMain->setLayoutDirection(Qt::LeftToRight);
        title_widget = new QWidget(MyMain);
        title_widget->setObjectName(QStringLiteral("title_widget"));
        title_widget->setGeometry(QRect(0, 0, 831, 61));
        lineEdit = new QLineEdit(title_widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(270, 10, 151, 41));
        pushButton_cloth = new QPushButton(title_widget);
        pushButton_cloth->setObjectName(QStringLiteral("pushButton_cloth"));
        pushButton_cloth->setGeometry(QRect(620, 10, 31, 31));
        pushButton_search = new QPushButton(title_widget);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(280, 20, 21, 21));
        pushButton_close = new QPushButton(title_widget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(780, 10, 31, 31));
        pushButton_min = new QPushButton(title_widget);
        pushButton_min->setObjectName(QStringLiteral("pushButton_min"));
        pushButton_min->setGeometry(QRect(730, 10, 31, 31));
        tableWidget = new QTableWidget(MyMain);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 70, 261, 31));
        listWidget_musiclist = new QListWidget(MyMain);
        listWidget_musiclist->setObjectName(QStringLiteral("listWidget_musiclist"));
        listWidget_musiclist->setGeometry(QRect(10, 130, 261, 321));
        stackedWidget = new QStackedWidget(MyMain);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(320, 80, 491, 371));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayoutWidget_2 = new QWidget(page);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 491, 191));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 210, 121, 17));
        pushButton_album2 = new QPushButton(page);
        pushButton_album2->setObjectName(QStringLiteral("pushButton_album2"));
        pushButton_album2->setGeometry(QRect(120, 240, 111, 101));
        pushButton_album2->setFocusPolicy(Qt::NoFocus);
        pushButton_album3 = new QPushButton(page);
        pushButton_album3->setObjectName(QStringLiteral("pushButton_album3"));
        pushButton_album3->setGeometry(QRect(240, 240, 111, 101));
        pushButton_album3->setFocusPolicy(Qt::NoFocus);
        pushButton_album4 = new QPushButton(page);
        pushButton_album4->setObjectName(QStringLiteral("pushButton_album4"));
        pushButton_album4->setGeometry(QRect(360, 240, 111, 101));
        pushButton_album4->setFocusPolicy(Qt::NoFocus);
        pushButton_album1 = new QPushButton(page);
        pushButton_album1->setObjectName(QStringLiteral("pushButton_album1"));
        pushButton_album1->setGeometry(QRect(0, 240, 111, 101));
        pushButton_album1->setFocusPolicy(Qt::NoFocus);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        listWidget_lyrics = new QListWidget(page_2);
        listWidget_lyrics->setObjectName(QStringLiteral("listWidget_lyrics"));
        listWidget_lyrics->setGeometry(QRect(0, 0, 491, 371));
        stackedWidget->addWidget(page_2);
        widget_bottom = new QWidget(MyMain);
        widget_bottom->setObjectName(QStringLiteral("widget_bottom"));
        widget_bottom->setGeometry(QRect(0, 450, 831, 101));
        verticalLayoutWidget = new QWidget(widget_bottom);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 241, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_music = new QSlider(widget_bottom);
        horizontalSlider_music->setObjectName(QStringLiteral("horizontalSlider_music"));
        horizontalSlider_music->setGeometry(QRect(320, 60, 261, 29));
        horizontalSlider_music->setOrientation(Qt::Horizontal);
        label_starttime = new QLabel(widget_bottom);
        label_starttime->setObjectName(QStringLiteral("label_starttime"));
        label_starttime->setGeometry(QRect(270, 70, 51, 17));
        label_endtime = new QLabel(widget_bottom);
        label_endtime->setObjectName(QStringLiteral("label_endtime"));
        label_endtime->setGeometry(QRect(590, 70, 67, 17));
        pushButton_pause = new QPushButton(widget_bottom);
        pushButton_pause->setObjectName(QStringLiteral("pushButton_pause"));
        pushButton_pause->setGeometry(QRect(430, 30, 31, 31));
        pushButton_prev = new QPushButton(widget_bottom);
        pushButton_prev->setObjectName(QStringLiteral("pushButton_prev"));
        pushButton_prev->setGeometry(QRect(390, 40, 21, 21));
        pushButton_next = new QPushButton(widget_bottom);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(480, 40, 21, 21));
        pushButton_like = new QPushButton(widget_bottom);
        pushButton_like->setObjectName(QStringLiteral("pushButton_like"));
        pushButton_like->setEnabled(true);
        pushButton_like->setGeometry(QRect(640, 40, 21, 21));
        pushButton_lyrics = new QPushButton(widget_bottom);
        pushButton_lyrics->setObjectName(QStringLiteral("pushButton_lyrics"));
        pushButton_lyrics->setGeometry(QRect(740, 40, 21, 21));
        listWidget = new QListWidget(widget_bottom);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(680, -120, 50, 110));
        pushButton_volume = new QPushButton(widget_bottom);
        pushButton_volume->setObjectName(QStringLiteral("pushButton_volume"));
        pushButton_volume->setGeometry(QRect(690, 40, 21, 21));
        label = new QLabel(MyMain);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 110, 67, 17));
        stackedWidget->raise();
        widget_bottom->raise();
        title_widget->raise();
        tableWidget->raise();
        listWidget_musiclist->raise();
        label->raise();

        retranslateUi(MyMain);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MyMain);
    } // setupUi

    void retranslateUi(QWidget *MyMain)
    {
        MyMain->setWindowTitle(QApplication::translate("MyMain", "MyMain", 0));
        label_2->setText(QApplication::translate("MyMain", "Recommendation", 0));
        pushButton_album2->setText(QString());
        pushButton_album3->setText(QString());
        pushButton_album4->setText(QString());
        pushButton_album1->setText(QString());
        label_starttime->setText(QApplication::translate("MyMain", "00:00", 0));
        label_endtime->setText(QApplication::translate("MyMain", "00:00", 0));
        pushButton_pause->setText(QString());
        pushButton_prev->setText(QString());
        pushButton_like->setText(QString());
        pushButton_lyrics->setText(QString());
        pushButton_volume->setText(QString());
        label->setText(QApplication::translate("MyMain", "Music", 0));
    } // retranslateUi

};

namespace Ui {
    class MyMain: public Ui_MyMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAIN_H
