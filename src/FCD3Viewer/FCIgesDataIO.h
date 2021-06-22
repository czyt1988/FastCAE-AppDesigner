#ifndef FCIGESDATAIO_H
#define FCIGESDATAIO_H
#include "FCD3ViewerAPI.h"
#include "FCGlobals.h"
#include "FCAbstractGeometryDataIO.h"
#include <QObject>

/**
 * @brief 针对iges数据的io
 */
class FCD3VIEWER_API FCIgesDataIO : public FCAbstractGeometryDataIO
{
    Q_OBJECT
public:
    FCIgesDataIO(QObject *par = nullptr);
    ~FCIgesDataIO();
    //读取
    virtual void read();

    //写入
    virtual void write();

    //错误信息
    virtual QString errorString() const;

private:
    QString m_errString;
};

#endif // FCIGESDATAIO_H
