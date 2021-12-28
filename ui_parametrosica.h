/********************************************************************************
** Form generated from reading UI file 'parametrosica.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETROSICA_H
#define UI_PARAMETROSICA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_parametrosICA
{
public:
    QLabel *paises;
    QLabel *paises_2;
    QLabel *paises_3;
    QLabel *paises_4;
    QLabel *paises_5;
    QLabel *paises_6;
    QLabel *paises_7;
    QLabel *paises_8;
    QLabel *paises_9;
    QDoubleSpinBox *revolutiorate;
    QLineEdit *numpaises;
    QLineEdit *imperialistas;
    QLineEdit *decadas;
    QLineEdit *asimilacion;
    QLineEdit *angulo;
    QLineEdit *zeta;
    QLineEdit *busqueda;
    QLineEdit *dampratio;
    QPushButton *aceptar;
    QPushButton *limpiar;
    QPushButton *cancelar;

    void setupUi(QWidget *parametrosICA)
    {
        if (parametrosICA->objectName().isEmpty())
            parametrosICA->setObjectName(QStringLiteral("parametrosICA"));
        parametrosICA->resize(402, 337);
        paises = new QLabel(parametrosICA);
        paises->setObjectName(QStringLiteral("paises"));
        paises->setGeometry(QRect(30, 10, 121, 16));
        paises_2 = new QLabel(parametrosICA);
        paises_2->setObjectName(QStringLiteral("paises_2"));
        paises_2->setGeometry(QRect(30, 40, 161, 16));
        paises_3 = new QLabel(parametrosICA);
        paises_3->setObjectName(QStringLiteral("paises_3"));
        paises_3->setGeometry(QRect(30, 70, 121, 16));
        paises_4 = new QLabel(parametrosICA);
        paises_4->setObjectName(QStringLiteral("paises_4"));
        paises_4->setGeometry(QRect(30, 100, 121, 16));
        paises_5 = new QLabel(parametrosICA);
        paises_5->setObjectName(QStringLiteral("paises_5"));
        paises_5->setGeometry(QRect(30, 130, 141, 16));
        paises_6 = new QLabel(parametrosICA);
        paises_6->setObjectName(QStringLiteral("paises_6"));
        paises_6->setGeometry(QRect(30, 160, 191, 16));
        paises_7 = new QLabel(parametrosICA);
        paises_7->setObjectName(QStringLiteral("paises_7"));
        paises_7->setGeometry(QRect(30, 190, 121, 16));
        paises_8 = new QLabel(parametrosICA);
        paises_8->setObjectName(QStringLiteral("paises_8"));
        paises_8->setGeometry(QRect(30, 220, 171, 16));
        paises_9 = new QLabel(parametrosICA);
        paises_9->setObjectName(QStringLiteral("paises_9"));
        paises_9->setGeometry(QRect(30, 250, 121, 16));
        revolutiorate = new QDoubleSpinBox(parametrosICA);
        revolutiorate->setObjectName(QStringLiteral("revolutiorate"));
        revolutiorate->setGeometry(QRect(250, 100, 62, 22));
        revolutiorate->setDecimals(1);
        revolutiorate->setValue(0.1);
        numpaises = new QLineEdit(parametrosICA);
        numpaises->setObjectName(QStringLiteral("numpaises"));
        numpaises->setGeometry(QRect(250, 10, 113, 20));
        imperialistas = new QLineEdit(parametrosICA);
        imperialistas->setObjectName(QStringLiteral("imperialistas"));
        imperialistas->setGeometry(QRect(250, 40, 113, 20));
        decadas = new QLineEdit(parametrosICA);
        decadas->setObjectName(QStringLiteral("decadas"));
        decadas->setGeometry(QRect(250, 70, 113, 20));
        asimilacion = new QLineEdit(parametrosICA);
        asimilacion->setObjectName(QStringLiteral("asimilacion"));
        asimilacion->setGeometry(QRect(250, 130, 113, 20));
        angulo = new QLineEdit(parametrosICA);
        angulo->setObjectName(QStringLiteral("angulo"));
        angulo->setGeometry(QRect(250, 160, 113, 20));
        zeta = new QLineEdit(parametrosICA);
        zeta->setObjectName(QStringLiteral("zeta"));
        zeta->setGeometry(QRect(250, 190, 113, 20));
        busqueda = new QLineEdit(parametrosICA);
        busqueda->setObjectName(QStringLiteral("busqueda"));
        busqueda->setGeometry(QRect(250, 220, 113, 20));
        dampratio = new QLineEdit(parametrosICA);
        dampratio->setObjectName(QStringLiteral("dampratio"));
        dampratio->setGeometry(QRect(250, 250, 113, 20));
        aceptar = new QPushButton(parametrosICA);
        aceptar->setObjectName(QStringLiteral("aceptar"));
        aceptar->setGeometry(QRect(120, 300, 75, 23));
        limpiar = new QPushButton(parametrosICA);
        limpiar->setObjectName(QStringLiteral("limpiar"));
        limpiar->setGeometry(QRect(210, 300, 75, 23));
        cancelar = new QPushButton(parametrosICA);
        cancelar->setObjectName(QStringLiteral("cancelar"));
        cancelar->setGeometry(QRect(300, 300, 75, 23));

        retranslateUi(parametrosICA);

        QMetaObject::connectSlotsByName(parametrosICA);
    } // setupUi

    void retranslateUi(QWidget *parametrosICA)
    {
        parametrosICA->setWindowTitle(QApplication::translate("parametrosICA", "Par\303\241metros ICA", 0));
        paises->setText(QApplication::translate("parametrosICA", "N\303\272mero inicial de pa\303\255ses:", 0));
        paises_2->setText(QApplication::translate("parametrosICA", "N\303\272mero inicial de imperialistas:", 0));
        paises_3->setText(QApplication::translate("parametrosICA", "N\303\272mero de d\303\251cadas:", 0));
        paises_4->setText(QApplication::translate("parametrosICA", "Revolution rate:", 0));
        paises_5->setText(QApplication::translate("parametrosICA", "Coeficiente de asimilaci\303\263n:", 0));
        paises_6->setText(QApplication::translate("parametrosICA", "Coeficiente de asimilaci\303\263n de \303\241ngulo:", 0));
        paises_7->setText(QApplication::translate("parametrosICA", "Zeta:", 0));
        paises_8->setText(QApplication::translate("parametrosICA", "Porcentaje espacio de b\303\272squeda:", 0));
        paises_9->setText(QApplication::translate("parametrosICA", "DampRatio:", 0));
        aceptar->setText(QApplication::translate("parametrosICA", "Aceptar", 0));
        limpiar->setText(QApplication::translate("parametrosICA", "Limpiar", 0));
        cancelar->setText(QApplication::translate("parametrosICA", "Cancelar", 0));
    } // retranslateUi

};

namespace Ui {
    class parametrosICA: public Ui_parametrosICA {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETROSICA_H
