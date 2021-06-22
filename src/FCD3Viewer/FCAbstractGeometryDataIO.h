#ifndef FCABSTRACTGEOMETRYDATAIO_H
#define FCABSTRACTGEOMETRYDATAIO_H

#include <QObject>
#include "FCD3ViewerAPI.h"
#include "FCGlobals.h"
#include "FCGeometryDataIOResult.h"
FC_IMPL_FORWARD_DECL(FCAbstractGeometryDataIO)



/**
 * @brief 几何体文件io基类
 * 负责几种三维文件的读写操作
 *
 * @sa FCIgesDataIO
 */
class FCD3VIEWER_API FCAbstractGeometryDataIO : public QObject
{
    Q_OBJECT
    FC_IMPL(FCAbstractGeometryDataIO)
public:
    FCAbstractGeometryDataIO(QObject *par = nullptr);
    virtual ~FCAbstractGeometryDataIO();
    //文件名设置
    void setFileName(const QString& filename);
    QString getFileName() const;

    //读取
    virtual void read() = 0;

    //写入
    virtual void write() = 0;

    //获取错误信息
    virtual QString errorString() const = 0;

signals:

    /**
     * @brief 读取完成信号，携带几何信息
     * @param result 读取的结果和是否成功通过此参数获取,就算是读取错误，也通过此信号返回
     * @sa FCGeometryDataIOResult
     */
    void readed(FCGeometryDataIOResult result);

    /**
     * @brief 写入完成信号，返回
     * @param isSucc 标记是否写入成功，如果失败，可调用@sa errorString 获取错误信息
     */
    void writed(bool isSucc);
};

#endif // FCABSTRACTGEOMETRYDATAIO_H
