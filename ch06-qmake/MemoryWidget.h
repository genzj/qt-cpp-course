#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include "SysInfoWidget.h"

class MemoryWidget : public SysInfoWidget
{
    Q_OBJECT
public:
    explicit MemoryWidget(QWidget *parent = 0);

protected slots:
    void updateSeries() override;
};

#endif // MEMORYWIDGET_H
