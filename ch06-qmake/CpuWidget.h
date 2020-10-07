#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include "SysInfoWidget.h"

class CpuWidget : public SysInfoWidget
{
    Q_OBJECT
public:
    explicit CpuWidget(QWidget* parent = 0);

protected slots:
    void updateSeries() override;
};

#endif // CPUWIDGET_H
