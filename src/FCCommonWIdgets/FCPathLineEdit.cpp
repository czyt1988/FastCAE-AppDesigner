#include "FCPathLineEdit.h"

FCPathLineEdit::FCPathLineEdit(QWidget *p) : ctkPathLineEdit(p)
{
}


FCPathLineEdit::FCPathLineEdit(const QString& label, const QStringList& nameFilters, ctkPathLineEdit::Filters filters, QWidget *p)
    : ctkPathLineEdit(label, nameFilters, filters, p)
{
}
