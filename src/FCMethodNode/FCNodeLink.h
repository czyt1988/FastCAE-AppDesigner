#ifndef FCNODELINK_H
#define FCNODELINK_H
#include "FCNodeGlobal.h"
#include "FCGlobals.h"
FC_IMPL_FORWARD_DECL(FCNodeLink)
class FCNode;

/**
 * @brief 定义连接，from和to是不允许相同的
 */
class FCNODE_API FCNodeLink
{
    FC_IMPL(FCNodeLink)
    friend class FCNode;
public:
    FCNodeLink();
    virtual ~FCNodeLink();
    //连接的绑定
    bool attachFrom(FCNode *node, const QString& connectPointName);
    bool attachTo(FCNode *node, const QString& connectPointName);

    //连接的起始
    FCNode *from();
    const FCNode *from() const;

    //连接的结束
    FCNode *to();
    const FCNode *to() const;

    //判断是否存在节点
    bool isHaveFromNode() const;
    bool isHaveToNode() const;
};

#endif // FCNODELINK_H
