#ifndef SYSINFOWIDGET_H
#define SYSINFOWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLCDNumber>

class SysInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SysInfoWidget(QWidget *parent = 0,
                           int startDelayMs = 500,
                           int updateSeriesDelayMs = 500);

protected:
    QLCDNumber mDisplayer;

protected slots:
    virtual void updateSeries() = 0;

private:
    QTimer mRefreshTimer;
};

#endif // SYSINFOWIDGET_H
