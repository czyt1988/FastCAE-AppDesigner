#ifndef FCCOLORPICKERBUTTON_H
#define FCCOLORPICKERBUTTON_H
#include "ctkColorPickerButton.h"

/**
 * @brief 颜色拾取按钮封装
 */
class FCColorPickerButton : public ctkColorPickerButton
{
    Q_OBJECT
public:
    FCColorPickerButton(QWidget *parent = nullptr);
};

#endif // FCCOLORPICKERBUTTON_H
