#include "CpuWidget.h"
#include "SysInfo.h"

#include <QString>

CpuWidget::CpuWidget(QWidget* parent) :
    SysInfoWidget(parent)
{
    mDisplayer.display(0.0);
}

void CpuWidget::updateSeries()
{
    double cpuLoadAverage = SysInfo::instance().cpuLoadAverage();
    mDisplayer.display(QString("%1").arg(cpuLoadAverage, 0, 'f', 2));
}
