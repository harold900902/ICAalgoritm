#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fitnessfunction.h"
#include "icalgorithm.h"
#include "parametrosica.h"
#include <array>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->yAxis->setRange(0, 30);
    ui->plot->xAxis->setRange(0, 50);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*void MainWindow::llenarValores(int numOfCountries, int numOfInitialImperialists,
                               int numOfDecades,double revolutionRate,double assimilationCoefficient,
                               double assimilationAngleCoefficient,double zeta,double dampRatio,
                               double searchPercent){

    this->numPaises= numOfCountries;
    this->numImpe = numOfInitialImperialists;
    this->decada = numOfDecades;
    this->revolutionrate = revolutionRate;
    this->asimil = assimilationCoefficient;
    this->asimilAngle=assimilationAngleCoefficient;
    this->zeta = zeta;
    this->ratio=dampRatio;
    this->busqueda= searchPercent;
}*/

void MainWindow::on_pushButton_clicked()
{

    // Set the fitness function and problem parameters
      FitnessFunction *fitnessFunc = new FitnessFunction();

      // Create the algorithm object
      ICAlgorithm *ica = new ICAlgorithm();

      ica->numOfCountries=ui->numpaises->text().toInt();
      ica->numOfInitialImperialists=ui->imperialistas->text().toInt();
      ica->numOfAllColonies=ui->numpaises->text().toInt()-ui->imperialistas->text().toInt();
      ica->numOfDecades=ui->decadas->text().toInt();
      ica->revolutionRate=ui->revolutiorate->text().toDouble();
      ica->assimilationCoefficient=ui->asimilacion->text().toDouble();
      ica->assimilationAngleCoefficient=ui->angulo->text().toDouble();
      ica->zeta=ui->zeta->text().toDouble();
      ica->dampRatio=ui->dampratio->text().toDouble();
      ica->unitingThreshold=ui->busqueda->text().toDouble();
      ica->Actualizar(fitnessFunc);

      // Run the simulation
      int nbRuns = 1;
      int maxEvals = 200000;
      double bestFitness=0;
      for (int i = 0;i < nbRuns;i++)
      {
          // Run the algorithm and get the results
          std::vector<double> results = ica->runICA(maxEvals);
          std::vector<double> minimoCosto = ica->minimumCost;

          bestFitness = fitnessFunc->getFitnessValue(results);
          ica->reset();
          ui->fitesresult->setText(QString::number(bestFitness));
         // cout<<"Best fitness:\t"<< bestFitness;
          // Display the results
         // std::wcout << bestFitness << std::endl;

          QVector<double> q_x,q_y;

          for (int k = 0; k < minimoCosto.size(); ++k) {
              std::wcout << minimoCosto[k] << std::endl;
              q_x.append(k);
              q_y.append(minimoCosto[k]);
              ui->plot->graph(0)->setData(q_x,q_y);
              if (k>50) {
               ui->plot->xAxis->setRange(0, k+3);
              }
              Sleep(50);
              ui->plot->replot();
              ui->plot->update();
            }


          //System.out.println("ICA run results:");
          cout<<"Best solution:\t";
          for (int i = 0; i < results.size(); ++i) {

               cout<< results.at(i)<<" ";
          }

      }

}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

void MainWindow::on_limpiar_clicked()
{
    ui->numpaises->clear();
    ui->imperialistas->clear();
    ui->asimilacion->clear();
    ui->angulo->clear();
    ui->dampratio->clear();
    ui->busqueda->clear();
    ui->decadas->clear();
    ui->zeta->clear();
    ui->revolutiorate->clear();
}

