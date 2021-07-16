#ifndef FCNODEMIMEDATA_H
#define FCNODEMIMEDATA_H

#include <QtCore/qglobal.h>
#include "FCMimeData.h"

/**
 * @brief 节点移动的mime data
 */
class FCNodeMimeData : public FCMimeData
{
    Q_OBJECT
public:
    FCNodeMimeData();
    //节点格式 - MIME_STANDARD_NODE
    virtual QStringList formats() const;
    virtual bool hasFormat(const QString& mimeType) const;

    //设置/获取节点名
    QString getNodePrototype() const;
    void setNodePrototype(const QString& prototype);

private:
    QString m_nodePrototype;
};

#endif // GNODEMIMEDATA_H
