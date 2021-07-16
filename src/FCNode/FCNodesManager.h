#ifndef FCNODESMANAGER_H
#define FCNODESMANAGER_H
#include "FCNodeGlobal.h"
#include "FCNode.h"
#include "FCNodeLink.h"
FC_IMPL_FORWARD_DECL(FCNodesManager)

/**
 * @brief 实现对FCNode\FCNodeLink的管理
 *
 * 节点的回收和创建，都通过FCNodesManager来进行操作
 *
 * 通过@sa FCNodesManager 创建的节点和连接都会自动回收
 *
 * @sa createNode @sa createNodeLink 函数用来创建节点和连接
 *
 * @sa deleteNode @sa deleteNodeLink 函数用来销毁节点和连接
 */
class FCNODE_API FCNodesManager
{
    FC_IMPL(FCNodesManager)
public:
    typedef QHash<QString, FCNode::StringMap> LanguageDict;
    FCNodesManager();
    virtual ~FCNodesManager();

    //记录node，此时node的所有权归属于FCNodesManager
    void recordNode(FCNode *node);

    //记录nodelink，此时nodelink的所有权归属于FCNodesManager
    void recordNodeLink(FCNodeLink *link);

    //创建一个节点
    FCNode *createNode();

    //通过类型创建一个节点，此节点必须通过setNodeType操作过manager才会记住这个类型对应的节点
    FCNode *createNodeFromPrototype(const QString& prototype);

    //创建连接
    FCNodeLink *createNodeLink();

    //销毁节点
    void deleteNode(FCNode *node);

    //销毁连接
    void deleteNodeLink(FCNodeLink *link);

    //获取所有节点
    QList<FCNode *> allNodes() const;

    //获取所有连接
    QList<FCNodeLink *> allNodeLinks() const;

    //复制一个节点
    FCNode *copyNode(FCNode *other);

    //通过当前的QLacal翻译某一个node
    void translate(FCNode *node);

    //通过语言翻译node里的内容
    void translate(FCNode *node, QLocale::Language lng);

    //翻译所有的node,根据Qlocale
    void translate();

    //建立语言字典
    void setupLanguageDict(FCNode *node, const LanguageDict& dict);

    //设置某个node的类型，manager会记住类型对应的node，通过createNodeFromPrototype函数可以创建设置过类型的node
    void registeNodePrototype(FCNode *node);
};

#endif // FCNODESMANAGER_H
