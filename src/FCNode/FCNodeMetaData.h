#ifndef FCNODEMETADATA_H
#define FCNODEMETADATA_H
#include "FCNodeGlobal.h"
#include <QtCore/qglobal.h>
#include <QIcon>

/**
 * @brief 保存节点元数据
 * 节点元数据由工厂进行管理
 */
class FCNODE_API FCNodeMetaData
{
public:
    FCNodeMetaData();
    FCNodeMetaData(const QString& prototype);
    FCNodeMetaData(const QString& prototype, const QString& name, const QIcon& icon, const QString& group);
    //ptototype
    QString getNodePrototype() const;
    void setNodePrototype(const QString& prototype);

    //节点名
    QString getNodeName() const;
    void setNodeName(const QString& name);

    //图标
    QIcon getIcon() const;
    void setIcon(const QIcon& icon);

    //所属分组
    QString getGroup() const;
    void setGroup(const QString& group);

private:
    QString m_prototype;
    QString m_nodeName;
    QIcon m_nodeIcon;
    QString m_group;
};

FCNODE_API uint qHash(const FCNodeMetaData& key, uint seed = 0);
FCNODE_API bool operator <(const FCNodeMetaData& a, const FCNodeMetaData& b);

Q_DECLARE_METATYPE(FCNodeMetaData)

#endif // FCNODEMETADATA_H
