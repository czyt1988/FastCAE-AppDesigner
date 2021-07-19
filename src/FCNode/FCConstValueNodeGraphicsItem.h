#ifndef FCCONSTVALUENODEGRAPHICSITEM_H
#define FCCONSTVALUENODEGRAPHICSITEM_H
#include "FCNodeGlobal.h"
#include "FCAbstractNodeGraphicsItem.h"

/**
 * @brief 变量及常数节点，此节点存放常数
 */
class FCNODE_API FCConstValueNodeGraphicsItem : public FCAbstractNodeGraphicsItem
{
public:
    enum { Type = FastCAE::GraphicsNodeItemConst };
    int type() const
    {
        return (Type);
    }


    FCConstValueNodeGraphicsItem();
    ~FCConstValueNodeGraphicsItem();

    //获取node的类型，这个类型可以表征同一类型的node 这个不会进行翻译
    virtual QString getNodePrototype() const;

    //外部参数
    //设置参数，如果无法设置成功返回false
    bool setValue(const QVariant& v);

    //获取数据
    QVariant getValue() const;

    //判断数据是否为空
    bool isNull() const;

public:
    //绘图相关
    QRectF boundingRect() const;

protected:
    bool checkType() const;

private:
    QVariant m_value;
};

#endif // FCCONSTVALUENODEGRAPHICSITEM_H
