#ifndef FCPLUGINOPTION_H
#define FCPLUGINOPTION_H
#include "FCPluginGlobal.h"
#include "FCAbstractPlugin.h"
#include <QDebug>
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
    //判断是否是有效的
    bool isValid() const;

    // 加载插件
    bool load(const QString& pluginPath);

    // 错误信息
    QString getErrorString() const;

    //文件名
    QString getFileName() const;

    //获取iid
    QString getIid() const;

    //获取版本信息
    FCAbstractPlugin *plugin() const;
};
//格式化输出
FCPLUGIN_API QDebug operator <<(QDebug debug, const FCPluginOption& po);

#endif // FCPLUGINOPTION_H
