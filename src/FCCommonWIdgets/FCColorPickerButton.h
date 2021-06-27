#ifndef FCCOLORPICKERBUTTON_H
#define FCCOLORPICKERBUTTON_H
#include "ctkColorPickerButton.h"
#include "FCCommonWidgetsAPI.h"

/**
 * @brief 颜色拾取按钮封装
 */
class FCCOMMONWIDGETS_API FCColorPickerButton : public ctkColorPickerButton
{
    Q_OBJECT
public:
    FCColorPickerButton(QWidget *parent = nullptr);
};

#endif // FCCOLORPICKERBUTTON_H
