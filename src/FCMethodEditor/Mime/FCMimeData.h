#ifndef FCMIMEDATA_H
#define FCMIMEDATA_H

#include <QtCore/qglobal.h>
#include <QMimeData>

/**
 * @brief mime的基类
 */
class FCMimeData : public QMimeData
{
    Q_OBJECT
public:
    FCMimeData();
};

#endif // FCMIMEDATA_H
