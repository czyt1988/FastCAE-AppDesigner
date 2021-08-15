#ifndef FCDATAPACKAGE_H
#define FCDATAPACKAGE_H
#include <QtCore/qglobal.h>
#include "FCNodeGlobal.h"
#include <QDebug>
#include "FCDataItem.h"
FC_IMPL_FORWARD_DECL(FCDataPackage)

/**
 * @brief DataPackage实现键值对数据的传递，其赋值操作都是引用操作，数据区并不发生拷贝
 *
 * 若要实现拷贝，需要显示调用@sa copy 函数
 */
class FCDataPackage
{
    FC_IMPL(FCDataPackage)
public:
    FCDataPackage();

    //拷贝构造重载，实现弱拷贝
    FCDataPackage(const FCDataPackage& d);

    //移动构造
    FCDataPackage(FCDataPackage&& d);

    //等号操作符重载
    FCDataPackage& operator =(const FCDataPackage& a);

    //判断是否为空
    bool isNull() const;

    //拷贝
    FCDataPackage copy() const;

    //获取这个变量的id，可以看出是否共同引用一个变量
    qint64 id() const;

    //等于判断 只要id相等就认为相等
    bool operator ==(const FCDataPackage& other) const;

    //获取值
    QVariant getValue(const QString& key) const;

    //获取值对应的名字
    QString getValueName(const QString& key) const;

    //获取item
    FCDataItem getValueItem(const QString& key) const;

    //设置值
    void setValue(const QString& key, const QVariant& v, const QString& name);

    //获取所有的值
    QList<QVariant> getValues() const;

    //获取所有的变量名
    QList<QString> getValueNames() const;

    //获取所有的key
    QList<QString> getKeys() const;
};

#endif // FCDATAPACKAGE_H
