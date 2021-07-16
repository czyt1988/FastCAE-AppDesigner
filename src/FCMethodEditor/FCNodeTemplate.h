#ifndef FCNODETEMPLATE_H
#define FCNODETEMPLATE_H
#include "FCNode.h"
#include <QObject>
#include <QHash>
#include <QSharedPointer>
#include "FCNodesManager.h"

/**
 * @brief 加载文件，把node模板加载上来,并对此部分node进行管理
 * 此类仅对模板文件的node进行管理，因此
 */
class FCNodeTemplate : public QObject
{
    Q_OBJECT
public:
    FCNodeTemplate();
    ~FCNodeTemplate();
    //获取模板路径
    static QString templateFolder();

    //加载所有节点信息
    void load();

    //获取所有分组名
    QList<QString> groupsName() const;

    //获取节点列表
    QList<FCNode *>& nodeList(const QString& group);

    //获取内部管理的manager
    FCNodesManager *manager() const;

private:
    FCNode *loadNode(const QString& filepath);

private:
    QHash<QString, QList<FCNode *> > m_templateNodes; ///< 保存了所有节点的分组
    QScopedPointer<FCNodesManager> m_mgr;
};

#endif // FCNODETEMPLATELOADER_H
