#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Timer for UI responsivness
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(UpdateGUI()));
    tmrTimer->start(20);

    // Set initial sliders postion (for selecting ROI)
    ui->SldLower->setSliderPosition(0);
    ui->SldUpper->setSliderPosition(480);
    ui->SldLeft->setSliderPosition(0);
    ui->SldRight->setSliderPosition(640);

    //connections to video processor thread

    const bool c = connect(&processor,SIGNAL(outFPS(float)),ui->FPS,SLOT(setNum(float)));
    connect(&processor,SIGNAL(inDisplay(QPixmap)),ui->inVideo,SLOT(setPixmap(QPixmap)));
    connect(&processor,SIGNAL(outDisplay(QPixmap)),ui->outVideo,SLOT(setPixmap(QPixmap)));


    qDebug() << "connected" << c;
}

MainWindow::~MainWindow()
{
    processor.requestInterruption();
    processor.wait();
    delete ui;
}

void MainWindow::UpdateGUI()
{
  //Append Resize values
  ui->SldLeftValue->clear();
  ui->SldLeftValue->appendPlainText(QString::number(ui->SldLeft->value()));

  ui->SldUpperValue->clear();
  ui->SldUpperValue->appendPlainText(QString::number(ui->SldUpper->value()));

  ui->SldRightValue->clear();
  ui->SldRightValue->appendPlainText(QString::number(ui->SldRight->value()));

  ui->SldLowerValue->clear();
  ui->SldLowerValue->appendPlainText(QString::number(ui->SldLower->value()));


  if(ui->SldRight->value()-ui->SldLeft->value() >= 0 && ui->SldUpper->value()-ui->SldLower->value() >=0)
  {
    roi.setRect(ui->SldLeft->value(),ui->SldLower->value(),(ui->SldRight->value()-ui->SldLeft->value()),(ui->SldUpper->value()-ui->SldLower->value()));
  }
  else
  {
    qDebug() << "ROI out of bounds";
  }

  processor.update(roi, 0.5, 1.5);


}

void MainWindow::on_pushButton_toggled(bool checked)
{
    if(checked)
    {
        processor.requestInterruption();
        processor.quit();
        ui->pushButton->setText("INITIATE");
    }
    else
    {
        processor.update(roi, 0.5, 1.5);
        processor.start();
        ui->pushButton->setText("INTERRUPT");
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event){
//    if(((object == ui->txtparam1) ||
//       (object == ui->txtparam2) ||
//       (object == ui->txtminRadius) ||
//       (object == ui->txtmaxRadius))&&
//        event->type() == QEvent::KeyPress){
//        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//        if(keyEvent->key() == Qt::Key_Return  || keyEvent->key() == Qt::Key_Enter){
//            // Read the values
//            param1 = ui->txtparam1->toPlainText().toDouble();
//            param2 = ui->txtparam2->toPlainText().toDouble();
//            minRadius = ui->txtminRadius->toPlainText().toInt();
//            maxRadius = ui->txtmaxRadius->toPlainText().toInt();
//        }
//    }
    return QMainWindow::eventFilter(object, event);
}
