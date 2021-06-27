#ifndef FCCOORDINATESWIDGET_H
#define FCCOORDINATESWIDGET_H

#include "ctkCoordinatesWidget.h"
#include "FCCommonWidgetsAPI.h"

/**
 * @brief 封装ctkCoordinatesWidget，实现坐标的设置
 */
class FCCOMMONWIDGETS_API FCCoordinatesWidget : public ctkCoordinatesWidget
{
    Q_OBJECT
public:
    FCCoordinatesWidget(QWidget *p = nullptr);
};

#endif // FCCOORDINATESWIDGET_H
