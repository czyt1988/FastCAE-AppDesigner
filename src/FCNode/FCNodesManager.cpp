#include "FCNodesManager.h"
class FCNodesManagerPrivate {
public:
    FC_IMPL_PUBLIC(FCNodesManager)
    FCNodesManagerPrivate(FCNodesManager *p);
    void destory();

    QList<FCNode *> _nodes;
    QList<FCNodeLink *> _links;
    QMap<FCNode *, FCNodesManager::LanguageDict> _nodeToLanguage;   ///< 保存了所有节点对应的翻译字典
    QHash<QString, FCNode *> _prototypeToNode;                           ///< 记录类型对应的节点，这个节点会创建一份
};


FCNodesManagerPrivate::FCNodesManagerPrivate(FCNodesManager *p) : q_ptr(p)
{
}


void FCNodesManagerPrivate::destory()
{
    for (FCNode *n : _nodes)
    {
        delete n;
    }
    for (FCNodeLink *n : _links)
    {
        delete n;
    }
    for (auto v : _prototypeToNode)
    {
        delete v;
    }
    _nodes.clear();
    _links.clear();
    _nodeToLanguage.clear();
    _prototypeToNode.clear();
}


////////////////////////////////////////////////////

FCNodesManager::FCNodesManager() : d_ptr(new FCNodesManagerPrivate(this))
{
}


FCNodesManager::~FCNodesManager()
{
    d_ptr->destory();
}


void FCNodesManager::recordNode(FCNode *node)
{
    d_ptr->_nodes.append(node);
    if(!d_ptr->_prototypeToNode.contains(node->getNodePrototype())){
        registeNodePrototype(node);
    }
}


void FCNodesManager::recordNodeLink(FCNodeLink *link)
{
    d_ptr->_links.append(link);
}


/**
 * @brief 创建一个节点,并管理
 * @note 节点的内存由FCNodesManager来管理
 * @return
 */
FCNode *FCNodesManager::createNode()
{
    FCNode *n = new FCNode();

    recordNode(n);
    return (n);
}


/**
 * @brief 通过类型创建一个节点，
 * 此节点必须通过setNodeType操作过manager才会记住这个类型对应的节点
 * @param type
 * @return
 * @sa setNodeType
 */
FCNode *FCNodesManager::createNodeFromPrototype(const QString& prototype)
{
    FCNode *base = d_ptr->_prototypeToNode.value(prototype, nullptr);

    if (base) {
        FCNode *real = base->copy();
        recordNode(real);
        return (real);
    }
    return (nullptr);
}


/**
 * @brief 创建节点连接,并管理
 * @note 节点连接的内存由FCNodesManager来管理
 * @return
 */
FCNodeLink *FCNodesManager::createNodeLink()
{
    FCNodeLink *n = new FCNodeLink();

    recordNodeLink(n);
    return (n);
}


/**
 * @brief 销毁一个节点
 * @param node
 */
void FCNodesManager::deleteNode(FCNode *node)
{
    d_ptr->_nodes.removeOne(node);
    delete node;
}


/**
 * @brief 销毁一个链接
 * @param link
 */
void FCNodesManager::deleteNodeLink(FCNodeLink *link)
{
    d_ptr->_links.removeOne(link);
    delete link;
}


/**
 * @brief 获取所有节点
 * @return
 */
QList<FCNode *> FCNodesManager::allNodes() const
{
    return (d_ptr->_nodes);
}


/**
 * @brief 获取所有连接
 * @return
 */
QList<FCNodeLink *> FCNodesManager::allNodeLinks() const
{
    return (d_ptr->_links);
}


/**
 * @brief 根据节点复制出一个节点，并进行管理
 * @note other节点可以并非FCNodesManager管理的节点
 * @param other 其他节点实例
 * @return 返回复制出来的节点，此时节点的内存归FCNodesManager管理
 */
FCNode *FCNodesManager::copyNode(FCNode *other)
{
    FCNode *n = new FCNode(*other);

    d_ptr->_nodes.append(n);
    return (n);
}


void FCNodesManager::translate(FCNode *node)
{
    translate(node, QLocale().language());
}


void FCNodesManager::translate(FCNode *node, QLocale::Language lng)
{
    FCNode::StringMap dict = d_ptr->_nodeToLanguage[node][QLocale::languageToString(lng)];

    node->setupStringMap(dict);
}


void FCNodesManager::translate()
{
    for (auto i = d_ptr->_nodeToLanguage.begin(); i != d_ptr->_nodeToLanguage.end(); ++i)
    {
        translate(i.key());
    }
}


/**
 * @brief 设置语言字典
 * @param node 设置节点
 * @param dict 语言字典
 */
void FCNodesManager::setupLanguageDict(FCNode *node, const FCNodesManager::LanguageDict& dict)
{
    d_ptr->_nodeToLanguage[node] = dict;
}


/**
 * @brief 设置某个node的类型，
 * manager会记住类型对应的node，
 * 通过createNodeFromType函数可以创建设置过类型的node
 * @note 记录的节点是经过复制的，节点设置完类型后删除节点对记忆的节点不影响
 * @param type
 * @param node
 */
void FCNodesManager::registeNodePrototype(FCNode *node)
{
    d_ptr->_prototypeToNode[node->getNodePrototype()] = node->copy();
}
