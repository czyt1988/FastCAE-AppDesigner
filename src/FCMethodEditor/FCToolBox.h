#ifndef FCTOOLBOX_H
#define FCTOOLBOX_H
#include <QToolBox>
#include "FCNodeMetaData.h"
#include <QMap>
class FCToolBox : public QToolBox
{
    Q_OBJECT
public:
    FCToolBox() = default;
    void addItems(const QMap<QString, QList<FCNodeMetaData> >& datas);
};

#endif // FCTOOLBOX_H
