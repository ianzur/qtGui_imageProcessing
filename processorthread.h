#ifndef PROCESSORTHREAD_H
#define PROCESSORTHREAD_H

#include <QThread>
#include <QImage>
#include <QPixmap>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ProcessorThread : public QThread
{
      Q_OBJECT


  public:
      explicit ProcessorThread(QObject *parent = 0);
      void update(QRect r, float low, float high);
      int CLOCK();
      float avgfps();

  signals:
      void inDisplay(QPixmap pixmap);
      void outDisplay(QPixmap pixmap);
      void outFPS(float fps);

  protected:
      void run() override;

  private:
      cv::VideoCapture capture;

      //Region of interest
      cv::Rect myROI;

      float lowHz;
      float highHz;
      //float fps;
      int _fpsstart=0;
      float _avgfps=0;
      float _fps1sec=0;

};

#endif // PROCESSORTHREAD_H
