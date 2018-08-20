#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <stdint.h>
#include <QObject>
#include <QDebug>
#include "image_type.h"

#if (__GNUC__ > 4) || (__APPLE__ && __MACH__)
    #include <atomic>
#else
    #include <cstdatomic>
#endif

class CameraModel : public QObject
{
    Q_OBJECT

public:
    CameraModel(QObject *parent = nullptr) : QObject(parent) { running.store(false); }
    virtual ~CameraModel() { running.store(false); }


    virtual bool start() = 0;
    virtual uint16_t *getFrame() = 0;

    virtual void setDir(const char *filename) { Q_UNUSED(filename); }

    virtual bool isRunning() { return running.load(); }

    unsigned int getFrameWidth() const { return frame_width; }
    unsigned int getFrameHeight() const { return frame_height; }
    unsigned int getDataHeight() const { return data_height; }
    camera_t getCameraType() const { return camera_type; }

signals:
    void timeout();

protected:
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int data_height;
    camera_t camera_type;

    std::atomic<bool> running;
};

#endif // CAMERAMODEL_H
