#ifndef FCGEOMETRYDATAIORESULT_H
#define FCGEOMETRYDATAIORESULT_H
#include <QObject>
#include "FCD3ViewerAPI.h"
#include "FCGlobals.h"
FC_IMPL_FORWARD_DECL(FCGeometryDataIOResult)
class TopoDS_Shape;

/**
 * @brief 用于保存几何io打开的结果，便于把TopoDS_Shape通过信号槽进行传递
 * @note result里保存的shape是指针，在result销毁时不会自动销毁，
 * 需要手动调用@sa destory 函数
 */
class FCD3VIEWER_API FCGeometryDataIOResult {
    FC_IMPL(FCGeometryDataIOResult)
    friend class FCAbstractGeometryDataIO;
public:
    FCGeometryDataIOResult();
    FCGeometryDataIOResult(const FCGeometryDataIOResult& rhs);
    //移动语义
    FCGeometryDataIOResult(FCGeometryDataIOResult&& rhs);

    FCGeometryDataIOResult& operator=(FCGeometryDataIOResult&& rhs);
    FCGeometryDataIOResult& operator=(FCGeometryDataIOResult& rhs);

    virtual ~FCGeometryDataIOResult();

    //判断是否有效
    bool isValid() const;

    //获取io的结果的拓扑形状
    TopoDS_Shape *shape();
    const TopoDS_Shape *shape() const;
    void setShape(TopoDS_Shape *s);

    //设置为空，会清空TopoDS_Shaped的内存
    void destory();

    //获取错信息
    void setErrorString(const QString& err);
    QString getErrorString() const;

    //获取错信息
    void setFileName(const QString& fileName);
    QString getFileName() const;
};
Q_DECLARE_METATYPE(FCGeometryDataIOResult)
#endif // FCGEOMETRYDATAIORESULT_H
