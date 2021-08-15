#ifndef FCDATAITEM_H
#define FCDATAITEM_H
#include <QVariant>
#include <QDebug>
#include "FCNodeGlobal.h"

/**
 * @brief 基础数据
 *
 * 节点的传递过程就是基础数据包的传递过程，基础数据条码管理的单个数据信息
 */
class FCNODE_API FCDataItem
{
public:
    FCDataItem();
    FCDataItem(const QVariant& v, const QString& n);
    //变量值
    QVariant getValue() const;
    void setValue(const QVariant& v);
    QVariant& value();
    const QVariant& value() const;

    //变量的注释
    QString getName() const;
    void setName(const QString& n);
    QString& name();
    const QString& name() const;

    //设置值和名字
    void set(const QVariant& v, const QString& n);

private:
    QVariant m_variant;
    QString m_name;
};
Q_DECLARE_METATYPE(FCDataItem)

//等操作，对比value和comment
FCNODE_API bool operator ==(const FCDataItem& a, const FCDataItem& b);
FCNODE_API bool operator <(const FCDataItem& a, const FCDataItem& b);
FCNODE_API QDebug operator <<(QDebug dbg, const FCDataItem& a);

#endif // FCDATAITEM_H
