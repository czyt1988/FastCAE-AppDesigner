#ifndef FCNODEMIMEDATA_H
#define FCNODEMIMEDATA_H

#include <QtCore/qglobal.h>
#include "FCMimeData.h"
#include "FCNodeMetaData.h"

/**
 * @brief 节点移动的mime data
 */
class FCNodeMimeData : public FCMimeData
{
    Q_OBJECT
public:
    FCNodeMimeData(const FCNodeMetaData& md);
    //节点格式 - MIME_STANDARD_NODE
    virtual QStringList formats() const;
    virtual bool hasFormat(const QString& mimeType) const;

    //设置/获取节点名
    FCNodeMetaData getNodeMetaData() const;
    void setNodeMetaData(const FCNodeMetaData& md);

private:
    FCNodeMetaData m_nodeMetaData;
};

#endif // GNODEMIMEDATA_H
