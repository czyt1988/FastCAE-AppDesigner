#ifndef FCPATHLINEEDIT_H
#define FCPATHLINEEDIT_H
#include "ctkPathLineEdit.h"
#include "FCCommonWidgetsAPI.h"

/**
 * @brief 封装ctkPathLineEdit，便于进行文件选择
 */
class FCCOMMONWIDGETS_API FCPathLineEdit : public ctkPathLineEdit
{
    Q_OBJECT
public:
    FCPathLineEdit(QWidget *p = nullptr);
    FCPathLineEdit(const QString& label,
        const QStringList& nameFilters,
        Filters filters = ctkPathLineEdit::AllEntries,
        QWidget *p = 0);
};

#endif // FCPATHLINEEDIT_H
