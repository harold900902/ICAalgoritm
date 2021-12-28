#ifndef PARAMETROSICA_H
#define PARAMETROSICA_H
#include "icalgorithm.h"
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class parametrosICA;
}

class parametrosICA : public QWidget
{
    Q_OBJECT

public:
    explicit parametrosICA(QWidget *parent = 0);
    ~parametrosICA();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_limpiar_clicked();

    void on_cancelar_clicked();

    void on_aceptar_clicked();

    void on_numpaises_editingFinished();

private:
    Ui::parametrosICA *ui;
};

#endif // PARAMETROSICA_H
