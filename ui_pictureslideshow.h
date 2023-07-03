/********************************************************************************
** Form generated from reading UI file 'pictureslideshow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTURESLIDESHOW_H
#define UI_PICTURESLIDESHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "picturebutton.h"

QT_BEGIN_NAMESPACE

class Ui_PictureSlideShow
{
public:
    QGraphicsView *graphicsView;
    QPushButton *pushButton_leftview;
    QPushButton *pushButton_rightview;
    pictureButton *picButton1;
    pictureButton *picButton2;
    pictureButton *picButton3;
    pictureButton *picButton4;

    void setupUi(QWidget *PictureSlideShow)
    {
        if (PictureSlideShow->objectName().isEmpty())
            PictureSlideShow->setObjectName(QStringLiteral("PictureSlideShow"));
        PictureSlideShow->resize(491, 191);
        graphicsView = new QGraphicsView(PictureSlideShow);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 471, 171));
        pushButton_leftview = new QPushButton(PictureSlideShow);
        pushButton_leftview->setObjectName(QStringLiteral("pushButton_leftview"));
        pushButton_leftview->setGeometry(QRect(30, 90, 21, 21));
        pushButton_rightview = new QPushButton(PictureSlideShow);
        pushButton_rightview->setObjectName(QStringLiteral("pushButton_rightview"));
        pushButton_rightview->setGeometry(QRect(440, 90, 21, 21));
        picButton1 = new pictureButton(PictureSlideShow);
        picButton1->setObjectName(QStringLiteral("picButton1"));
        picButton1->setGeometry(QRect(230, 182, 0, 20));
        picButton2 = new pictureButton(PictureSlideShow);
        picButton2->setObjectName(QStringLiteral("picButton2"));
        picButton2->setGeometry(QRect(240, 182, 0, 20));
        picButton3 = new pictureButton(PictureSlideShow);
        picButton3->setObjectName(QStringLiteral("picButton3"));
        picButton3->setGeometry(QRect(250, 182, 0, 20));
        picButton4 = new pictureButton(PictureSlideShow);
        picButton4->setObjectName(QStringLiteral("picButton4"));
        picButton4->setGeometry(QRect(260, 182, 0, 20));

        retranslateUi(PictureSlideShow);

        QMetaObject::connectSlotsByName(PictureSlideShow);
    } // setupUi

    void retranslateUi(QWidget *PictureSlideShow)
    {
        PictureSlideShow->setWindowTitle(QApplication::translate("PictureSlideShow", "Form", 0));
        pushButton_leftview->setText(QString());
        pushButton_rightview->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PictureSlideShow: public Ui_PictureSlideShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTURESLIDESHOW_H
