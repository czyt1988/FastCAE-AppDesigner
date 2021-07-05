#include "FCNode_p.h"
#include "FCNode.h"
#include "FCNodeLink.h"
FCNodePrivate::FCNodePrivate(FCNode *p) : q_ptr(p)
    , _rotation(0.0)
{
}


FCNodePrivate::~FCNodePrivate()
{
}


/**
 * @brief 除了q_ptr和_linkMap,其余都复制
 * @param other
 */
void FCNodePrivate::copy(const FCNodePrivate *other)
{
    _name = other->_name;
    _describe = other->_describe;
    _boundingRect = other->_boundingRect;
    _pixmapRect = other->_pixmapRect;
    _pixmap = other->_pixmap;
    _connectPoints = other->_connectPoints;
    _pos = other->_pos;
    _rotation = other->_rotation;
    _dataMap = other->_dataMap;
}


/**
 * @brief 移除连接
 * @param link
 */
void FCNodePrivate::removeLink(FCNodeLink *link)
{
    for (auto i = _linkMap.begin(); i != _linkMap.end(); ++i)
    {
        if (_linkMap.values(i.key()).contains(link)) {
            _linkMap.remove(i.key(), link);
            return;
        }
    }
}


/**
 * @brief 把所有连接进行解绑操作
 *
 * 此函数仅仅在析构时调用
 */
void FCNodePrivate::detachAll()
{
    for (auto i = _linkMap.begin(); i != _linkMap.end(); ++i)
    {
        QList<FCNodeLink *> vs = _linkMap.values(i.key());
        for (FCNodeLink *v : vs)
        {
            //先把link断开node的连接
            if (v->to() == q_ptr) {
                v->_disattachTo();
            }else if (v->from() == q_ptr) {
                v->_disattachFrom();
            }
        }
    }
}


//////////////////////////////////////////////////////////


FCNodeLinkPrivate::FCNodeLinkPrivate(FCNodeLink *p) : q_ptr(p)
    , _fromNode(nullptr)
    , _toNode(nullptr)
{
}
