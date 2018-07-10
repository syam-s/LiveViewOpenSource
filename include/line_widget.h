#ifndef LINE_WIDGET_H
#define LINE_WIDGET_H

#include "lvtabapplication.h"
#include "image_type.h"

class line_widget : public LVTabApplication
{
    Q_OBJECT
public:
    explicit line_widget(FrameWorker *fw, image_t image_t, QWidget *parent = 0);
    virtual ~line_widget();

    image_t image_type;

public slots:
    void handleNewFrame();
    void lineScrolledY(const QCPRange &newRange);
    void rescaleRange();
    void updatePlotTitle(const QPointF &coord);
    void setTracer(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);
    void moveCallout(QMouseEvent *e);
    void hideCallout(bool toggled);
    void useDSF(bool toggled);

private:
    QVector<double> (line_widget::*p_getLine)(QPointF);
    float* (FrameWorker::*p_getFrame)();
    QVector<double> getSpectralLine(QPointF coord);
    QVector<double> getSpatialLine(QPointF coord);
    QVector<double> getSpectralMean(QPointF coord);
    QVector<double> getSpatialMean(QPointF coord);
    QVector<double> x, y;

    QCPTextElement *plotTitle;

    QCheckBox *hideTracer;

    QCPItemTracer *tracer;
    QCPItemText *callout;
    QCPItemLine *arrow;

    int xAxisMax;
};

#endif // LINE_WIDGET_H