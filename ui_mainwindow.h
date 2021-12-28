/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QCustomPlot *plot;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *paises_9;
    QLineEdit *busqueda;
    QLabel *paises;
    QLabel *paises_7;
    QLabel *paises_2;
    QDoubleSpinBox *revolutiorate;
    QLabel *paises_6;
    QLabel *paises_3;
    QLabel *paises_4;
    QLabel *paises_5;
    QLabel *paises_8;
    QLineEdit *asimilacion;
    QLineEdit *numpaises;
    QLineEdit *zeta;
    QLineEdit *decadas;
    QLineEdit *imperialistas;
    QLineEdit *dampratio;
    QLineEdit *angulo;
    QLabel *label_4;
    QLabel *fitness;
    QLabel *fitesresult;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1186, 475);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1010, 430, 75, 23));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setGeometry(QRect(360, 20, 811, 401));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1100, 430, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(370, 0, 171, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 370, 31, 41));
        label_2->setWordWrap(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(380, 430, 47, 13));
        paises_9 = new QLabel(centralWidget);
        paises_9->setObjectName(QStringLiteral("paises_9"));
        paises_9->setGeometry(QRect(20, 290, 121, 16));
        busqueda = new QLineEdit(centralWidget);
        busqueda->setObjectName(QStringLiteral("busqueda"));
        busqueda->setGeometry(QRect(210, 320, 113, 20));
        paises = new QLabel(centralWidget);
        paises->setObjectName(QStringLiteral("paises"));
        paises->setGeometry(QRect(20, 80, 121, 16));
        paises_7 = new QLabel(centralWidget);
        paises_7->setObjectName(QStringLiteral("paises_7"));
        paises_7->setGeometry(QRect(20, 260, 121, 16));
        paises_2 = new QLabel(centralWidget);
        paises_2->setObjectName(QStringLiteral("paises_2"));
        paises_2->setGeometry(QRect(20, 110, 161, 16));
        revolutiorate = new QDoubleSpinBox(centralWidget);
        revolutiorate->setObjectName(QStringLiteral("revolutiorate"));
        revolutiorate->setGeometry(QRect(210, 170, 62, 22));
        revolutiorate->setDecimals(1);
        revolutiorate->setValue(0.1);
        paises_6 = new QLabel(centralWidget);
        paises_6->setObjectName(QStringLiteral("paises_6"));
        paises_6->setGeometry(QRect(20, 230, 191, 16));
        paises_3 = new QLabel(centralWidget);
        paises_3->setObjectName(QStringLiteral("paises_3"));
        paises_3->setGeometry(QRect(20, 140, 121, 16));
        paises_4 = new QLabel(centralWidget);
        paises_4->setObjectName(QStringLiteral("paises_4"));
        paises_4->setGeometry(QRect(20, 170, 121, 16));
        paises_5 = new QLabel(centralWidget);
        paises_5->setObjectName(QStringLiteral("paises_5"));
        paises_5->setGeometry(QRect(20, 200, 141, 16));
        paises_8 = new QLabel(centralWidget);
        paises_8->setObjectName(QStringLiteral("paises_8"));
        paises_8->setGeometry(QRect(20, 320, 171, 16));
        asimilacion = new QLineEdit(centralWidget);
        asimilacion->setObjectName(QStringLiteral("asimilacion"));
        asimilacion->setGeometry(QRect(210, 200, 113, 20));
        numpaises = new QLineEdit(centralWidget);
        numpaises->setObjectName(QStringLiteral("numpaises"));
        numpaises->setGeometry(QRect(210, 80, 113, 20));
        zeta = new QLineEdit(centralWidget);
        zeta->setObjectName(QStringLiteral("zeta"));
        zeta->setGeometry(QRect(210, 260, 113, 20));
        decadas = new QLineEdit(centralWidget);
        decadas->setObjectName(QStringLiteral("decadas"));
        decadas->setGeometry(QRect(210, 140, 113, 20));
        imperialistas = new QLineEdit(centralWidget);
        imperialistas->setObjectName(QStringLiteral("imperialistas"));
        imperialistas->setGeometry(QRect(210, 110, 113, 20));
        dampratio = new QLineEdit(centralWidget);
        dampratio->setObjectName(QStringLiteral("dampratio"));
        dampratio->setGeometry(QRect(210, 290, 113, 20));
        angulo = new QLineEdit(centralWidget);
        angulo->setObjectName(QStringLiteral("angulo"));
        angulo->setGeometry(QRect(210, 230, 113, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 20, 151, 16));
        label_4->setFont(font);
        fitness = new QLabel(centralWidget);
        fitness->setObjectName(QStringLiteral("fitness"));
        fitness->setGeometry(QRect(30, 400, 47, 13));
        fitesresult = new QLabel(centralWidget);
        fitesresult->setObjectName(QStringLiteral("fitesresult"));
        fitesresult->setGeometry(QRect(80, 400, 47, 13));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Algoritmo Competitivo Imperialista", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Ejecutar", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Cerrar", 0));
        label->setText(QApplication::translate("MainWindow", "Convergencia del algoritmo", 0));
        label_2->setText(QApplication::translate("MainWindow", "Costo", 0));
        label_3->setText(QApplication::translate("MainWindow", "D\303\251cadas", 0));
        paises_9->setText(QApplication::translate("MainWindow", "DampRatio:", 0));
        busqueda->setText(QApplication::translate("MainWindow", "0.02", 0));
        paises->setText(QApplication::translate("MainWindow", "N\303\272mero inicial de pa\303\255ses:", 0));
        paises_7->setText(QApplication::translate("MainWindow", "Zeta:", 0));
        paises_2->setText(QApplication::translate("MainWindow", "N\303\272mero inicial de imperialistas:", 0));
        paises_6->setText(QApplication::translate("MainWindow", "Coeficiente de asimilaci\303\263n de \303\241ngulo:", 0));
        paises_3->setText(QApplication::translate("MainWindow", "N\303\272mero de d\303\251cadas:", 0));
        paises_4->setText(QApplication::translate("MainWindow", "Revolution rate:", 0));
        paises_5->setText(QApplication::translate("MainWindow", "Coeficiente de asimilaci\303\263n:", 0));
        paises_8->setText(QApplication::translate("MainWindow", "Porcentaje espacio de b\303\272squeda:", 0));
        asimilacion->setText(QApplication::translate("MainWindow", "2", 0));
        numpaises->setText(QApplication::translate("MainWindow", "20", 0));
        zeta->setText(QApplication::translate("MainWindow", "0.02", 0));
        decadas->setText(QApplication::translate("MainWindow", "600", 0));
        imperialistas->setText(QApplication::translate("MainWindow", "2", 0));
        dampratio->setText(QApplication::translate("MainWindow", "0.99", 0));
        angulo->setText(QApplication::translate("MainWindow", "0.5", 0));
        label_4->setText(QApplication::translate("MainWindow", "Par\303\241metros del algoritmo", 0));
        fitness->setText(QApplication::translate("MainWindow", "Fitness:", 0));
        fitesresult->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
