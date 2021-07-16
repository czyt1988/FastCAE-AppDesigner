#include "FCNodesLoader.h"
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDomDocument>
#include <QDomElement>
#include <QLocale>


FCNodesManager::LanguageDict load_languageMap(QDomElement stringsEle);

/**
 * @brief load_FCNode
 * @param rootNodeEle 根节点
 * @param langMap 语言字典
 * @param nodexmlPath node xml所在路径
 * @param node node节点指针
 * @return
 */
bool load_FCNode(QDomElement rootNodeEle,
    const QString& nodexmlPath,
    FCNode *node);
QRectF load_QRectF(QDomElement rectEle);
QRect load_QRect(QDomElement rectEle);

FCNodesManager::LanguageDict load_languageMap(QDomElement stringsEle)
{
    FCNodesManager::LanguageDict res;
    QDomNodeList strnode = stringsEle.elementsByTagName("str");
    const int c = strnode.count();

    for (int i = 0; i < c; ++i)
    {
        QDomElement ele = strnode.at(i).toElement();
        QString id = ele.attribute("id");
        QDomNodeList langnodes = ele.childNodes();
        const int cc = langnodes.count();
        for (int j = 0; j < cc; ++j)
        {
            QDomElement langEle = langnodes.at(j).toElement();
            if (langEle.isNull()) {
                continue;
            }
            res[langEle.tagName()][id] = langEle.text();
        }
    }
    return (res);
}


bool load_FCNode(QDomElement rootNodeEle,
    const QString& nodexmlPath,
    FCNode *node)
{
    QDomElement e;
    QString prototype = rootNodeEle.attribute("prototype");

    if (prototype.isEmpty()) {
        qDebug() << "invalid prototype";
        return (false);
    }
    node->setNodePrototype(prototype);
    e = rootNodeEle.firstChildElement("name");
    if (!e.isNull()) {
        node->setNodeName(e.text());
    }
    e = rootNodeEle.firstChildElement("describe");
    if (!e.isNull()) {
        node->setDescribe(e.text());
    }
    e = rootNodeEle.firstChildElement("boundingRect");
    if (!e.isNull()) {
        node->setBoundingRect(load_QRectF(e));
    }
    e = rootNodeEle.firstChildElement("pixmapRect");
    if (!e.isNull()) {
        node->setPixmapRect(load_QRect(e));
    }
    e = rootNodeEle.firstChildElement("pixmap");
    if (!e.isNull()) {
        QString pixmapFileName = e.text();
        QPixmap pixmap(nodexmlPath + QDir::separator() + pixmapFileName);
        pixmap = pixmap.scaled(node->getPixmapRect().size(), Qt::KeepAspectRatio);
        node->setPixmap(pixmap);
    }
    e = rootNodeEle.firstChildElement("rotation");
    if (!e.isNull()) {
        node->setRotation(e.text().toDouble());
    }

    return (true);
}


QRectF load_QRectF(QDomElement rectEle)
{
    QRectF rect;

    rect.setX(rectEle.firstChildElement("x").text().toDouble());
    rect.setY(rectEle.firstChildElement("y").text().toDouble());
    rect.setWidth(rectEle.firstChildElement("w").text().toDouble());
    rect.setHeight(rectEle.firstChildElement("h").text().toDouble());
    return (rect);
}


QRect load_QRect(QDomElement rectEle)
{
    QRect rect;

    rect.setX(rectEle.firstChildElement("x").text().toInt());
    rect.setY(rectEle.firstChildElement("y").text().toInt());
    rect.setWidth(rectEle.firstChildElement("w").text().toInt());
    rect.setHeight(rectEle.firstChildElement("h").text().toInt());
    return (rect);
}


//////////////////////////////////////////////


class FCNodesLoaderPrivate {
public:
    FC_IMPL_PUBLIC(FCNodesLoader)
    FCNodesLoaderPrivate(FCNodesLoader *p);
    ~FCNodesLoaderPrivate();
    FCNodesManager *_manager;
};

FCNodesLoaderPrivate::FCNodesLoaderPrivate(FCNodesLoader *p)
    : q_ptr(p)
{
}


FCNodesLoaderPrivate::~FCNodesLoaderPrivate()
{
}


/////////////////////////////////////////////

FCNodesLoader::FCNodesLoader(FCNodesManager *mgr)
    : d_ptr(new FCNodesLoaderPrivate(this))
{
    d_ptr->_manager = mgr;
}


FCNodesLoader::~FCNodesLoader()
{
}


FCNode *FCNodesLoader::load(const QString& filepath)
{
    QFile fd(filepath);

    if (!fd.open(QIODevice::ReadOnly|QIODevice::Text)) {
        qDebug() << "can not load file:" <<filepath;
        return (nullptr);
    }
    QDomDocument doc;
    QString err;

    if (!doc.setContent(&fd, false, &err)) {
        qDebug()	<< "can not load xml file:" << filepath
                << " error string is:"<<err
        ;
    }
    FCNode *nodeptr = d_ptr->_manager->createNode();
    QDomElement root = doc.documentElement();
    QDomElement stringsEle = root.firstChildElement("strings");
    //加载语言
    FCNodesManager::LanguageDict langStrMap = load_languageMap(stringsEle);

    //加载节点
    QFileInfo fi(filepath);

    if (!load_FCNode(root, fi.path(), nodeptr)) {
        d_ptr->_manager->deleteNode(nodeptr);
        return (nullptr);
    }
    d_ptr->_manager->setupLanguageDict(nodeptr, langStrMap);
    d_ptr->_manager->translate(nodeptr);
    return (nodeptr);
}
