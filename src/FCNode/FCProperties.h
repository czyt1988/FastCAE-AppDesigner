#ifndef FCPROPERTIES_H
#define FCPROPERTIES_H
#include <QHash>
#include <QVariant>
#include "FCNodeGlobal.h"

/**
 * @brief 参考Java Properties 类封装的属性类，负责SA的属性传递
 *
 *
 */
class FCNODE_API FCProperties : public QVariantHash
{
public:
    FCProperties() = default;

    //获取属性
    QVariant getProperty(const QString& key) const;
    QVariant getProperty(const QString& key, const QVariant& defaultProperty) const;

    //设置属性
    void setProperty(const QString& key, const QVariant& value);
};
Q_DECLARE_METATYPE(FCProperties)


#endif // SAPROPERTIES_H
