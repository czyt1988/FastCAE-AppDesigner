#include "FCNodeMimeData.h"
#include "FCMimeTypeFormatDefine.h"
FCNodeMimeData::FCNodeMimeData(const FCNodeMetaData& md) : FCMimeData()
{
    setNodeMetaData(md);
}


QStringList FCNodeMimeData::formats() const
{
    return (QStringList() << MIME_NODE_META_DATA);
}


bool FCNodeMimeData::hasFormat(const QString& mimeType) const
{
    return (mimeType == MIME_NODE_META_DATA);
}


FCNodeMetaData FCNodeMimeData::getNodeMetaData() const
{
    return (m_nodeMetaData);
}


void FCNodeMimeData::setNodeMetaData(const FCNodeMetaData& md)
{
    m_nodeMetaData = md;
}
