#ifndef FCGEOMETRYDATAIOWORKER_H
#define FCGEOMETRYDATAIOWORKER_H
#include <QObject>
#include "FCD3ViewerAPI.h"
#include "FCGlobals.h"
#include "FCGeometryDataIOResult.h"
FC_IMPL_FORWARD_DECL(FCGeometryDataIOWorker)

/**
 * @brief 几何体读写的工作者（多线程读写）
 */
class FCD3VIEWER_API FCGeometryDataIOWorker : public QObject
{
    Q_OBJECT
    FC_IMPL(FCGeometryDataIOWorker)
public:
    FCGeometryDataIOWorker(QObject *p = nullptr);
    ~FCGeometryDataIOWorker();

    //判断是否正在读取
    bool isWorking() const;

public slots:
    //读取
    void read(const QString& filename);

signals:

    /**
     * @brief 开始读取发射的信号
     */
    void startRead();

    /**
     * @brief 读取完成信号，携带几何信息
     * @param result 读取的结果和是否成功通过此参数获取
     * @sa FCGeometryDataIOResult
     */
    void readed(FCGeometryDataIOResult result);

    /**
     * @brief 写入完成信号，返回
     * @param isSucc 标记是否写入成功，如果失败，可调用@sa errorString 获取错误信息
     */
    void writed(bool isSucc);
};

#endif // FCGEOMETRYDATAIOWORKER_H
