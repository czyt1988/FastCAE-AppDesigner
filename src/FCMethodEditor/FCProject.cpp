#include "FCProject.h"
#include <QScopedPointer>
class FCProjectPrivate {
public:
    FC_IMPL_PUBLIC(FCProject)
    FCProjectPrivate(FCProject *p);
public:
    QString _projectName;
};

FCProjectPrivate::FCProjectPrivate(FCProject *p) : q_ptr(p)
{
}


////////////////////////////////////////////////////


FCProject::FCProject(QObject *p) : QObject(p)
    , d_ptr(new FCProjectPrivate(this))
{
}


FCProject::~FCProject()
{
}


/**
 * @brief 获取工程名
 * @return
 */
QString FCProject::getProjectName() const
{
    return (d_ptr->_projectName);
}


/**
 * @brief 设置工程名
 * @param projectName
 */
void FCProject::setProjectName(const QString& projectName)
{
    d_ptr->_projectName = projectName;
}
