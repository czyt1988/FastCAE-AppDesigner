#include "FCDataPackage.h"
#include <QSharedPointer>
#include <QHash>
class FCDataPackagePrivate
{
    FC_IMPL_PUBLIC(FCDataPackage)
public:
    FCDataPackagePrivate(FCDataPackage *p);
    typedef QHash<QString, FCDataItem>	DataMapType;
    typedef QHash<QString, FCDataItem> *	DataMapTypePtr;
    QSharedPointer<DataMapType> _datas;///< 数据区，有可能是空
};

FCDataPackagePrivate::FCDataPackagePrivate(FCDataPackage *p) : q_ptr(p)
{
}


FCDataPackage::FCDataPackage() : d_ptr(new FCDataPackagePrivate(this))
{
}


FCDataPackage::FCDataPackage(const FCDataPackage& d) : d_ptr(new FCDataPackagePrivate(this))
{
    //数据直接转移
    d_ptr->_datas = d.d_ptr->_datas;
}


FCDataPackage::FCDataPackage(FCDataPackage&& d)
{
    //内存直接转移
    d_ptr.reset(d.d_ptr.take());
}


/**
 * @brief 等号操作实现弱拷贝，数据区共享
 * @param a
 * @return
 */
FCDataPackage& FCDataPackage::operator =(const FCDataPackage& a)
{
    d_ptr->_datas = a.d_ptr->_datas;
    return (*this);
}


/**
 * @brief 判断数据区是否有内容
 * @return
 */
bool FCDataPackage::isNull() const
{
    return (d_ptr->_datas.isNull());
}


/**
 * @brief 拷贝操作
 * @return
 */
FCDataPackage FCDataPackage::copy() const
{
    FCDataPackage d;

    //数据拷贝
    *(d.d_ptr->_datas) = *(d_ptr->_datas);
    //编译器会优化实现移动语意，不需要std::move
    return (d);
}


/**
 * @brief 获取这个变量的id，可以看出是否共同引用一个变量
 * @return
 */
qint64 FCDataPackage::id() const
{
    if (isNull()) {
        return (0);
    }
    return (qint64(d_ptr->_datas.get()));
}


/**
 * @brief 等于判断 只要id相等就认为相等
 * @param other
 * @return
 */
bool FCDataPackage::operator ==(const FCDataPackage& other) const
{
    return (id() == other.id());
}


/**
 * @brief 通过id获取变量
 * @param id
 * @return
 */
QVariant FCDataPackage::getValue(const QString& key) const
{
    if (isNull()) {
        return (QVariant());
    }
    return (d_ptr->_datas->value(key).getValue());
}


/**
 * @brief 获取值对应的名字
 * @param id
 * @return
 */
QString FCDataPackage::getValueName(const QString& key) const
{
    if (isNull()) {
        return (QString());
    }
    return (d_ptr->_datas->value(key).getName());
}


/**
 * @brief 获取item
 * @param key
 * @return
 */
FCDataItem FCDataPackage::getValueItem(const QString& key) const
{
    if (isNull()) {
        return (FCDataItem());
    }
    return (d_ptr->_datas->value(key));
}


/**
 * @brief 设置值
 * @param id
 * @param v
 */
void FCDataPackage::setValue(const QString& key, const QVariant& v, const QString& name)
{
    if (isNull()) {
        d_ptr->_datas.reset(new QHash<QString, FCDataItem>());
    }
    d_ptr->_datas->operator [](key).set(v, name);
}


/**
 * @brief 获取所有的值
 * @return
 */
QList<QVariant> FCDataPackage::getValues() const
{
    QList<QVariant> res;

    if (isNull()) {
        return (res);
    }
    FCDataPackagePrivate::DataMapTypePtr dp = d_ptr->_datas.get();

    for (auto i = dp->begin(); i != dp->end(); ++i)
    {
        res.append(i.value().getValue());
    }
    return (res);
}


/**
 * @brief 获取所有的变量名
 * @return
 */
QList<QString> FCDataPackage::getValueNames() const
{
    QList<QString> res;

    if (isNull()) {
        return (res);
    }
    FCDataPackagePrivate::DataMapTypePtr dp = d_ptr->_datas.get();

    for (auto i = dp->begin(); i != dp->end(); ++i)
    {
        res.append(i.value().getName());
    }
    return (res);
}


/**
 * @brief 获取所有key
 * @return
 */
QList<QString> FCDataPackage::getKeys() const
{
    QList<QString> res;

    if (isNull()) {
        return (res);
    }
    return (d_ptr->_datas->keys());
}
