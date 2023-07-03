/********************************************************************************
** Form generated from reading UI file 'soundvolume.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDVOLUME_H
#define UI_SOUNDVOLUME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SoundVolume
{
public:
    QSlider *verticalSlider_volume;

    void setupUi(QWidget *SoundVolume)
    {
        if (SoundVolume->objectName().isEmpty())
            SoundVolume->setObjectName(QStringLiteral("SoundVolume"));
        SoundVolume->resize(50, 110);
        verticalSlider_volume = new QSlider(SoundVolume);
        verticalSlider_volume->setObjectName(QStringLiteral("verticalSlider_volume"));
        verticalSlider_volume->setGeometry(QRect(10, 10, 31, 91));
        verticalSlider_volume->setOrientation(Qt::Vertical);

        retranslateUi(SoundVolume);

        QMetaObject::connectSlotsByName(SoundVolume);
    } // setupUi

    void retranslateUi(QWidget *SoundVolume)
    {
        SoundVolume->setWindowTitle(QApplication::translate("SoundVolume", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SoundVolume: public Ui_SoundVolume {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDVOLUME_H
