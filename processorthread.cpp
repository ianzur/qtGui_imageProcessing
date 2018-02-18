#include "processorthread.h"
#include <QDebug>
#include <sys/timeb.h>

using namespace cv;

ProcessorThread::ProcessorThread(QObject *parent) : QThread(parent)
{

}

int ProcessorThread::CLOCK()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC,  &t);
    return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

float ProcessorThread::avgfps()
{
    if(CLOCK()-_fpsstart>1000)
    {
        _fpsstart=CLOCK();
        _avgfps=0.8*_avgfps+0.2*_fps1sec;
        _fps1sec=0;
    }

    _fps1sec++;
    return _avgfps;
}

void ProcessorThread::run()
{
    VideoCapture camera(0);

    cv::Mat inFrame, outFrame, cropped, bit;

    while(camera.isOpened() && !isInterruptionRequested())
    {
        camera >> inFrame;

        if(inFrame.empty())
            continue;

        outFrame = inFrame.clone();

        cropped = inFrame(myROI);

        bitwise_not(cropped, bit);

        bit.copyTo(outFrame(myROI));

        float i = avgfps();

        qDebug() << i;

        emit outFPS(i);

        emit inDisplay(QPixmap::fromImage(QImage(inFrame.data,inFrame.cols,inFrame.rows,inFrame.step,QImage::Format_RGB888).rgbSwapped()));

        emit outDisplay(QPixmap::fromImage(QImage(outFrame.data,outFrame.cols,outFrame.rows,outFrame.step,QImage::Format_RGB888).rgbSwapped()));


    }
}

void ProcessorThread::update(QRect r, float low, float high)
{
    this->myROI = cv::Rect(r.x(),r.y(),r.width(),r.height());

    this->lowHz = low;
    this->highHz = high;
}
