#ifndef FCPLUGINMANAGER_H
#define FCPLUGINMANAGER_H
#include <QObject>
#include "FCPluginGlobal.h"
#include "FCAbstractPlugin.h"
#include "FCPluginOption.h"
#include <QDebug>
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

    //设置忽略列表
    void setIgnoreList(const QStringList ignorePluginsName);

    //加载所有插件
    void load();

    //是否已经加载
    bool isLoaded() const;

    //设置插件路径
    void setPluginPath(const QString& path);

    //插件数
    int getPluginCount() const;

    //获取加载的插件名
    QList<QString> getPluginNames() const;

    //获取所有插件信息
    QList<FCPluginOption> getPluginOptions() const;
};

//格式化输出
FCPLUGIN_API QDebug operator <<(QDebug debug, const FCPluginManager& fmg);

#endif // FCPLUGINMANAGER_H
