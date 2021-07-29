#ifndef FCABSTRACTPLUGIN_H
#define FCABSTRACTPLUGIN_H
#include <QtPlugin>
#include "FCPluginGlobal.h"

/**
 * @brief 所有插件的基类
 *
 * 所有支持插件的库都需要实现以下导出函数
 * QString plugin_get_iid();
 * QString plugin_get_name();
 * QString plugin_get_version();
 * QString plugin_get_description();
 * FCAbstractPlugin* plugin_create();
 * void plugin_destory(FCAbstractPlugin* p);
 */
class FCPLUGIN_API FCAbstractPlugin {
public:
    FCAbstractPlugin() {}
    virtual ~FCAbstractPlugin() {}

    //插件id
    virtual QString getIID() const = 0;

    /**
     * @brief 插件名
     * @return
     */
    virtual QString getName() const = 0;

    /**
     * @brief 插件版本
     * @return
     */
    virtual QString getVersion() const = 0;

    /**
     * @brief 插件描述
     * @return
     */
    virtual QString getDescription() const = 0;
};

//下面是插件导出的函数指针
typedef QString (*FP_PluginGetIID)();
typedef QString (*FP_PluginGetName)();
typedef QString (*FP_PluginGetVersion)();
typedef QString (*FP_PluginGetDescription)();
typedef FCAbstractPlugin * (*FP_PluginCreate)();
typedef void (*FP_PluginDestory)(FCAbstractPlugin *);



#endif // FCABSTRACTPLUGIN_H
