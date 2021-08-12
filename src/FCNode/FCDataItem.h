#ifndef FCDATAITEM_H
#define FCDATAITEM_H
#include <QVariant>
#include "FCNodeGlobal.h"

/**
 * @brief 基础数据
 */
class FCNODE_API FCDataItem
{
public:
    FCDataItem();
    //变量值
    QVariant getValue() const;
    void setValue(const QVariant& v);
    QVariant& value();
    const QVariant& value() const;

    //变量的注释

private:
    QVariant m_variant;
    QString m_comment;
};

#endif // FCDATAITEM_H
