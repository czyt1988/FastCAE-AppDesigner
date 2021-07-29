#ifndef FCPLUGINOPTION_H
#define FCPLUGINOPTION_H
#include "FCPluginGlobal.h"
#include "FCAbstractPlugin.h"
FC_IMPL_FORWARD_DECL(FCPluginOption)

/**
 * @brief 用于插件的加载操作
 */
class FCPLUGIN_API FCPluginOption
{
    FC_IMPL(FCPluginOption)
public:
    FCPluginOption();
    FCPluginOption(const FCPluginOption& other);
    FCPluginOption(FCPluginOption&& other);
    FCPluginOption& operator =(const FCPluginOption& other);

    ~FCPluginOption();
public:
    // 加载插件
    bool load(const QString& pluginPath);

    // 错误信息
    QString errorString() const;

    //文件名
    QString fileName() const;

    //获取iid
    QString iid() const;

    //获取版本信息
    FCAbstractPlugin *plugin() const;
};

#endif // FCPLUGINOPTION_H
