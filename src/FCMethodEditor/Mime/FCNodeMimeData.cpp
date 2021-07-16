#include "FCNodeMimeData.h"
#include "FCMimeTypeFormatDefine.h"
FCNodeMimeData::FCNodeMimeData() : FCMimeData()
{
}


QStringList FCNodeMimeData::formats() const
{
    return (QStringList() << MIME_STANDARD_NODE);
}


bool FCNodeMimeData::hasFormat(const QString& mimeType) const
{
    return (mimeType == MIME_STANDARD_NODE);
}


QString FCNodeMimeData::getNodePrototype() const
{
    return (m_nodePrototype);
}


void FCNodeMimeData::setNodePrototype(const QString& name)
{
    m_nodePrototype = name;
}
