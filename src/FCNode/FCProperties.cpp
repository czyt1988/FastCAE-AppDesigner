#include "FCProperties.h"

/**
 * @brief 获取属性
 * @param key 键值
 * @return 如果不存在键值返回QVariant(),如果存在返回对应属性
 */
QVariant FCProperties::getProperty(const QString& key) const
{
    return (value(key, QVariant()));
}


/**
 * @brief 获取属性
 * @param key 键值
 * @param defaultProperty 默认值
 * @return 如果不存在键值返回defaultProperty,如果存在返回对应属性
 */
QVariant FCProperties::getProperty(const QString& key, const QVariant& defaultProperty) const
{
    return (value(key, defaultProperty));
}


/**
 * @brief 设置属性
 * @param key 键值
 * @param value 值
 */
void FCProperties::setProperty(const QString& key, const QVariant& value)
{
    insert(key, value);
}
