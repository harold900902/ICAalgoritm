#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    double revolutionrate;
    int numPaises;
    int numImpe;
    double asimil;
    double asimilAngle;
    double ratio;
    double busqueda;
    int decada;
    double zeta;
    explicit MainWindow(QWidget *parent = 0);
    void llenarValores(int numOfCountries, int numOfInitialImperialists,
                                   int numOfDecades,double revolutionRate,double assimilationCoefficient,
                                   double assimilationAngleCoefficient,double zeta,double dampRatio,
                                   double searchPercent);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_limpiar_clicked();

    void on_numpaises_cursorPositionChanged(int arg1, int arg2);

    void on_fitesresult_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
