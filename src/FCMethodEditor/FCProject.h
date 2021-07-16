#ifndef FCPROJECT_H
#define FCPROJECT_H
#include <QObject>
#include "FCGlobals.h"
class FCNodesManager;
FC_IMPL_FORWARD_DECL(FCProject)

/**
 * @brief 负责整个节点的工程管理
 */
class FCProject : public QObject
{
    Q_OBJECT
    FC_IMPL(FCProject)
public:
    FCProject(QObject *p = nullptr);
    ~FCProject();
    //获取项目名
    QString getProjectName() const;
    void setProjectName(const QString& projectName);

    //获取节点管理类
    FCNodesManager *manager() const;
};

#endif // FCPROJECT_H
