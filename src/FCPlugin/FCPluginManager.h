#ifndef FCPLUGINMANAGER_H
#define FCPLUGINMANAGER_H
#include <QObject>
#include "FCPluginGlobal.h"
#include "FCAbstractPlugin.h"
FC_IMPL_FORWARD_DECL(FCPluginManager)

/**
 * @brief 此类为插件管理类，作为单例，管理整个程序的插件加载和释放
 */
class FCPLUGIN_API FCPluginManager : public QObject
{
    FC_IMPL(FCPluginManager)
    FCPluginManager(QObject *p = nullptr);
public:
    //调用实例函数
    static FCPluginManager& instance();

    //加载所有插件
    void load();

    //设置插件路径
    void setPluginPath(const QString& path);

    //插件数
    int getPluginCount() const;
};



#endif // FCPLUGINMANAGER_H
