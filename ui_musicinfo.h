/********************************************************************************
** Form generated from reading UI file 'musicinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICINFO_H
#define UI_MUSICINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicInfo
{
public:
    QPushButton *pushButton_SongCD;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_SongName;
    QLabel *label_SongAuthor;

    void setupUi(QWidget *MusicInfo)
    {
        if (MusicInfo->objectName().isEmpty())
            MusicInfo->setObjectName(QStringLiteral("MusicInfo"));
        MusicInfo->resize(217, 71);
        pushButton_SongCD = new QPushButton(MusicInfo);
        pushButton_SongCD->setObjectName(QStringLiteral("pushButton_SongCD"));
        pushButton_SongCD->setGeometry(QRect(3, 5, 71, 61));
        widget = new QWidget(MusicInfo);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(92, 12, 110, 42));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_SongName = new QLabel(widget);
        label_SongName->setObjectName(QStringLiteral("label_SongName"));

        gridLayout->addWidget(label_SongName, 0, 0, 1, 1);

        label_SongAuthor = new QLabel(widget);
        label_SongAuthor->setObjectName(QStringLiteral("label_SongAuthor"));

        gridLayout->addWidget(label_SongAuthor, 1, 0, 1, 1);


        retranslateUi(MusicInfo);

        QMetaObject::connectSlotsByName(MusicInfo);
    } // setupUi

    void retranslateUi(QWidget *MusicInfo)
    {
        MusicInfo->setWindowTitle(QApplication::translate("MusicInfo", "Form", 0));
        pushButton_SongCD->setText(QString());
        label_SongName->setText(QString());
        label_SongAuthor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MusicInfo: public Ui_MusicInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICINFO_H
