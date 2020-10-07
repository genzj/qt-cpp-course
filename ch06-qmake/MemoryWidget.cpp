#include "MemoryWidget.h"

#include "SysInfo.h"


MemoryWidget::MemoryWidget(QWidget *parent) :
    SysInfoWidget(parent)
{
    mDisplayer.display(0.0);
}

void MemoryWidget::updateSeries()
{
    double memoryUsed = SysInfo::instance().memoryUsed();
    mDisplayer.display(QString("%1").arg(memoryUsed, 0, 'f', 2));
}
