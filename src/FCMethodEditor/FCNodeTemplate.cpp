#include "FCNodeTemplate.h"
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QLocale>
#include "FCNodesLoader.h"


const QString c_template_node_folder_name = "template-node";


FCNodeTemplate::FCNodeTemplate()
{
    m_mgr.reset(new FCNodesManager());
}


FCNodeTemplate::~FCNodeTemplate()
{
}


/**
 * @brief 获取节点目录
 * @return
 */
QString FCNodeTemplate::templateFolder()
{
    return (qApp->applicationDirPath() + QDir::separator() + c_template_node_folder_name);
}


/**
 * @brief 加载所有节点信息
 */
void FCNodeTemplate::load()
{
    const QString folder = templateFolder();
    QDir dir(folder);
    QStringList paths = dir.entryList(QDir::NoDotAndDotDot|QDir::Dirs);

    for (const QString& flodername : paths)
    {
        QList<FCNode *> nodes;
        qInfo() << QObject::tr("scan node type:") << flodername;
        QDir dirnode(folder+QDir::separator()+flodername);
        QFileInfoList fileinfos = dirnode.entryInfoList(QDir::NoDotAndDotDot|QDir::Files);
        for (const QFileInfo& fi : fileinfos)
        {
            if (fi.suffix() == "xml") {
                FCNode *node = loadNode(fi.filePath());
                if (node) {
                    nodes.append(node);
                }
                m_mgr->recordNode(node);//把这个node的类型注册到manager中，这样可以通过type创建node
                qDebug() << *node;
            }
        }
        m_templateNodes[flodername] = nodes;
    }
}


/**
 * @brief 获取所有分组名
 * @return
 */
QList<QString> FCNodeTemplate::groupsName() const
{
    return (m_templateNodes.keys());
}


/**
 * @brief 获取节点列表
 * @param group
 * @return
 */
QList<FCNode *>& FCNodeTemplate::nodeList(const QString& group)
{
    return (m_templateNodes[group]);
}


/**
 * @brief 获取内部管理的manager
 * @return
 */
FCNodesManager *FCNodeTemplate::manager() const
{
    return (m_mgr.get());
}


/**
 * @brief 加载一个节点
 * @param filepath
 * @return 如果加载失败返回nullptr
 */
FCNode *FCNodeTemplate::loadNode(const QString& filepath)
{
    FCNodesLoader loader(m_mgr.get());

    return (loader.load(filepath));
}
