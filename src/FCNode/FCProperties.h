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

/**
 * @brief 属性组
 *
 */
class FCNODE_API FCPropertiesGroup : public QHash<QString, FCProperties>
{
public:
    FCPropertiesGroup() = default;
    //获取属性
    QVariant getProperty(const QString& group, const QString& key) const;
    QVariant getProperty(const QString& group, const QString& key, const QVariant& defaultProperty) const;

    //获取一组属性，必须先确保有这个分组
    const FCProperties& constProperties(const QString& group) const;

    //获取一组属性的引用，如果没有，会插入一个默认属性,但对于常量操作不会插入，而是触发断言
    FCProperties& properties(const QString& group);
    const FCProperties& properties(const QString& group) const;

    //获取一组属性
    FCProperties getProperties(const QString& group);

    //设置一组属性
    void setProperties(const QString& group, const FCProperties& propertys);

    //设置属性
    void setProperty(const QString& group, const QString& key, const QVariant& value);

    //判断是否存在分组
    bool hasGroup(const QString& group);
};
Q_DECLARE_METATYPE(FCPropertiesGroup)

#endif // SAPROPERTIES_H
