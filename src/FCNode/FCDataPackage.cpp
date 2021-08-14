#include "FCDataPackage.h"
#include <QSharedPointer>
#include <QHash>
class FCDataPackagePrivate
{
    FC_IMPL_PUBLIC(FCDataPackage)
public:
    FCDataPackagePrivate(FCDataPackage *p);

    QSharedPointer<QHash<QString, FCDataItem> > _datas;///< 数据区，有可能是空
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
