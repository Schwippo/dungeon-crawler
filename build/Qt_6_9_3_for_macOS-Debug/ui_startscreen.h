/********************************************************************************
** Form generated from reading UI file 'startscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTSCREEN_H
#define UI_STARTSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_startscreen
{
public:

    void setupUi(QDialog *startscreen)
    {
        if (startscreen->objectName().isEmpty())
            startscreen->setObjectName("startscreen");
        startscreen->resize(400, 300);

        retranslateUi(startscreen);

        QMetaObject::connectSlotsByName(startscreen);
    } // setupUi

    void retranslateUi(QDialog *startscreen)
    {
        startscreen->setWindowTitle(QCoreApplication::translate("startscreen", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startscreen: public Ui_startscreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSCREEN_H
