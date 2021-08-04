#ifndef FCCONSTVALUENODEGRAPHICSITEM_H
#define FCCONSTVALUENODEGRAPHICSITEM_H
#include "FCUtilNodePluginGlobal.h"
#include "FCAbstractNodeGraphicsItem.h"

/**
 * @brief 变量及常数节点，此节点存放常数
 */
class FCUTILNODEPLUGIN_API FCConstValueNodeGraphicsItem : public FCAbstractNodeGraphicsItem
{
public:
    enum { Type = FastCAE::GraphicsNodeItemConst };
    int type() const override
    {
        return (Type);
    }


    FCConstValueNodeGraphicsItem(QGraphicsItem *p = nullptr);
    ~FCConstValueNodeGraphicsItem();

    //外部参数
    //设置参数，如果无法设置成功返回false
    bool setValue(const QVariant& v);

    //获取数据
    QVariant getValue() const;

    //判断数据是否为空
    bool isNull() const;

    //返回连接点信息
    virtual QList<FCNodeLinkPoint> getLinkPoints() const;

public:
    //绘图
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    //绘图相关
    QRectF boundingRect() const override;

protected:
    bool checkType() const;

//    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
//    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
//    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QVariant m_value;
    QList<FCNodeLinkPoint> m_linkPoints;
//    QColor m_hoverEdgeColor;        ///< 鼠标hover时的颜色
//    QPen m_edge;                    ///< 边框画笔
};

#endif // FCCONSTVALUENODEGRAPHICSITEM_H
