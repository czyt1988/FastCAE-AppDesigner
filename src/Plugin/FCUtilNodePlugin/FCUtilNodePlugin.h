#ifndef FCUTILNODEPLUGIN_H
#define FCUTILNODEPLUGIN_H
#include <QtCore/qglobal.h>
#include "FCAbstractPlugin.h"
#include "FCUtilNodePluginGlobal.h"
#include "FCAbstractNodePlugin.h"
//这是插件要求的6个标准导出函数
extern "C" FCUTILNODEPLUGIN_API QString plugin_get_iid();

extern "C" FCUTILNODEPLUGIN_API QString plugin_get_name();

extern "C" FCUTILNODEPLUGIN_API QString plugin_get_version();

extern "C" FCUTILNODEPLUGIN_API QString plugin_get_description();

extern "C" FCUTILNODEPLUGIN_API FCAbstractPlugin *plugin_create();

extern "C" FCUTILNODEPLUGIN_API void plugin_destory(FCAbstractPlugin *p);

class FCUtilNodePlugin : public FCAbstractNodePlugin
{
public:
    FCUtilNodePlugin();
    ~FCUtilNodePlugin();
    //插件id
    virtual QString getIID() const;

    /**
     * @brief 插件名
     * @return
     */
    virtual QString getName() const;

    /**
     * @brief 插件版本
     * @return
     */
    virtual QString getVersion() const;

    /**
     * @brief 插件描述
     * @return
     */
    virtual QString getDescription() const;

    /**
     * @brief 创建一个节点工厂
     * @return
     */
    virtual FCAbstractNodeGraphicsFactory *createNodeFactory();

    /**
     * @brief 删除一个节点工厂(谁创建谁删除原则)
     * @param p
     */
    virtual void destoryNodeFactory(FCAbstractNodeGraphicsFactory *p);
};

#endif // FCUTILNODEPLUGIN_H
