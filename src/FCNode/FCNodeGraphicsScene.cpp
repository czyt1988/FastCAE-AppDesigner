#include "FCNodeGraphicsScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QScopedPointer>
#include "FCNodeStandardLinkGraphicsItem.h"
class FCNodeGraphicsScenePrivate {
    FC_IMPL_PUBLIC(FCNodeGraphicsScene)
public:
    FCNodeGraphicsScenePrivate(FCNodeGraphicsScene *p);
    bool _isStartLink;
    QScopedPointer<FCNodeStandardLinkGraphicsItem> _linkingItem;
};

FCNodeGraphicsScenePrivate::FCNodeGraphicsScenePrivate(FCNodeGraphicsScene *p) : q_ptr(p)
    , _isStartLink(false)
{
}


FCNodeGraphicsScene::FCNodeGraphicsScene(QObject *p)
    : QGraphicsScene(p)
    , d_ptr(new FCNodeGraphicsScenePrivate(this))
{
    initConnect();
}


FCNodeGraphicsScene::FCNodeGraphicsScene(const QRectF& sceneRect, QObject *p)
    : QGraphicsScene(sceneRect, p)
    , d_ptr(new FCNodeGraphicsScenePrivate(this))
{
    initConnect();
}


FCNodeGraphicsScene::FCNodeGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *p)
    : QGraphicsScene(x, y, width, height, p)
    , d_ptr(new FCNodeGraphicsScenePrivate(this))
{
    initConnect();
}


bool FCNodeGraphicsScene::isStartLink() const
{
    return (d_ptr->_isStartLink);
}


void FCNodeGraphicsScene::callNodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp, QGraphicsSceneMouseEvent *event)
{
    emit nodeItemLinkPointSelected(item, lp, event);
}


void FCNodeGraphicsScene::initConnect()
{
    qRegisterMetaType<FCNodeLinkPoint>("FCNodeLinkPoint");
    connect(this, &FCNodeGraphicsScene::nodeItemLinkPointSelected, this, &FCNodeGraphicsScene::onNodeItemLinkPointSelected);
}


void FCNodeGraphicsScene::onNodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp, QGraphicsSceneMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton)) {
        if (isStartLink()) {
            //说明此时处于开始连接状态，接收到点击需要判断是否接受
            if (lp.isOutput() && d_ptr->_linkingItem.isNull()) {
                //连接的结束从in结束，out就退出
                event->ignore();
                return;
            }
            //此时连接到to点
            if (d_ptr->_linkingItem->attachTo(item, pl)) {
                //连接成功，把item脱离管理
                d_ptr->_linkingItem.take();
                d_ptr->_isStartLink = false;
            }
        }else{
            //说明此时处于正常状态，判断是否开始连线
            if (lp.isInput()) {
                //连接的开始从out开始，in就退出
                event->ignore();
                return;
            }
            //此时说明开始进行连线
            d_ptr->_isStartLink = true;
            d_ptr->_linkingItem.reset(new FCNodeStandardLinkGraphicsItem());
            if (!d_ptr->_linkingItem->attachFrom(item, lp)) {
                //连接不成功
                d_ptr->_linkingItem.reset();
                d_ptr->_isStartLink = false;
                return;
            }
            //把item加入
            addItem(d_ptr->_isStartLink.get());
        }
    }else{
        //除开左键的所有按键都是取消
        if (isStartLink()) {
            removeItem(d_ptr->_isStartLink.get());
            d_ptr->_isStartLink.reset();
            d_ptr->_isStartLink = false;
        }
    }
}
