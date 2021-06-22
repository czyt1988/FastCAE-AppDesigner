#ifndef FCD3VIEWER_H
#define FCD3VIEWER_H
#include <QVTKOpenGLNativeWidget.h>
#include "FCD3ViewerAPI.h"
#include "FCGlobals.h"
class TopoDS_Shape;
class QResizeEvent;
FC_IMPL_FORWARD_DECL(FCD3Viewer)

/**
 * @brief 3D视图的封装
 * 参考FASTCAE GeometryViewProvider 类进行封装
 */
class FCD3VIEWER_API FCD3Viewer : public QVTKOpenGLNativeWidget
{
    Q_OBJECT
    Q_PROPERTY(bool autoRender READ isAutoRender WRITE setAutoRender)
    Q_PROPERTY(bool isGradientBackgroundEnable READ isGradientBackgroundEnable WRITE setGradientBackgroundEnable)
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor background2 READ getBackground2 WRITE setBackground2)
    Q_PROPERTY(double backgroundAlpha READ getBackgroundAlpha WRITE setBackgroundAlpha)
    Q_PROPERTY(QColor geometryPointColor READ getGeometryPointColor WRITE setGeometryPointColor)
    Q_PROPERTY(QColor geometryCurveColor READ getGeometryCurveColor WRITE setGeometryCurveColor)
    Q_PROPERTY(QColor geometrySurfaceColor READ getGeometrySurfaceColor WRITE setGeometrySurfaceColor)
    Q_PROPERTY(GeometryDisplayTypes geometryDisplayType READ getGeometryDisplayType WRITE setGeometryDisplayType)
    Q_PROPERTY(bool toolBarVisible READ isToolBarVisible WRITE setToolBarVisible)
    Q_PROPERTY(ToolBarArea toolBarArea READ getToolBarArea WRITE setToolBarArea)
    Q_PROPERTY(ToolBarActionFlag toolBarActionFlag READ getToolBarActionFlags WRITE setToolBarActionFlags)
    FC_IMPL(FCD3Viewer)
public:
    FCD3Viewer(QWidget *parent = nullptr);
    ~FCD3Viewer();
public:

    /**
     * @brief 定义视图类型，用于@sa view 槽函数
     */
    enum ViewType {
        UnknowView,     ///< 未知的位置
        ViewXPlus,      ///< XPlus
        ViewXMiuns,     ///< XMiuns
        ViewYPlus,      ///< YPlus
        ViewYMiuns,     ///< YMiuns
        ViewZPlus,      ///< ZPlus
        ViewZMiuns,     ///< ZMiuns
        ViewFit         ///< 最佳视角
    };
    Q_ENUM(ViewType)

    /**
     * @brief 几何显示样式设置
     */
    enum GeometryDisplayType {
        DisplayPoint	= 0x01, ///< 显示点
        DisplayCurve	= 0x02, ///< 显示线
        DisplaySurface	= 0x04  ///< 显示面
    };
    Q_DECLARE_FLAGS(GeometryDisplayTypes, GeometryDisplayType)
    Q_FLAG(GeometryDisplayTypes)

    /**
     * @brief 定义工具栏的位置
     */
    enum ToolBarArea {
        ToolBarOnTop,           ///< 工具栏在顶端
        ToolBarOnLeft,          ///< 工具栏在左边
        ToolBarOnBottom,        ///< 工具栏在底部
        ToolBarOnRight          ///< 工栏在右侧
    };
    Q_ENUM(ToolBarArea)

    /**
     * @brief 记录了所有的动作
     */
    enum ToolBarActions {
        ActionViewXPlus		= 0x01,         ///< XPlus
        ActionViewXMiuns	= 0x02,         ///< XMiuns
        ActionViewYPlus		= 0x04,         ///< YPlus
        ActionViewYMiuns	= 0x08,         ///< YMiuns
        ActionViewZPlus		= 0x10,         ///< ZPlus
        ActionViewZMiuns	= 0x20,         ///< ZMiuns
        ActionViewFit		= 0x40,         ///< 最佳视角
        ActionAll		= 0xFFFFFFFF    ///< 所有
    };
    Q_DECLARE_FLAGS(ToolBarActionFlag, ToolBarActions)
    Q_FLAG(ToolBarActionFlag)
public slots:
    //设置渐变背景
    void setGradientBackgroundEnable(bool en = true);

    //设置背景颜色
    void setBackground(const QColor& clr);

    //设置背景颜色2
    void setBackground2(const QColor& clr);

    //设备背景透明度
    void setBackgroundAlpha(double a);

    //设置是否进行自动绘制
    void setAutoRender(bool isenable = true);

    //渲染
    void render();

    //设定视图
    void view(double lookX, double lookY, double lookZ,
        double upX, double upY, double upZ,
        double posX = 0.0, double posY = 0.0, double posZ = 0.0);

    //重载视角函数
    void view(ViewType type);

    //清空所有的已经高亮显示对象
    void clearGeometryHighLight();

    //设置几何体的显示效果
    void setGeometryDisplayType(GeometryDisplayTypes f);

    //导入几何
    void importGeometry(const QString& filename);

    //设置工具栏位置
    void setToolBarArea(ToolBarArea area);

    //设置允许显示工具栏
    void setToolBarVisible(bool enable = true);

    //设置哪些action可见
    void setToolBarActionFlags(ToolBarActionFlag flag);

public:
    //最佳视图
	void fitView();

    //判断是否允许渐变背景
    bool isGradientBackgroundEnable() const;

    //获取背景颜色
    QColor getBackground() const;

    //获取背景颜色2
    QColor getBackground2() const;

    //获取背景透明度
    double getBackgroundAlpha() const;

    //是否进行自动绘制
    bool isAutoRender() const;

    //还原所有对象颜色并清空高亮显示
    void restoreGeoColor();

    //设置几何点颜色
    void setGeometryPointColor(const QColor& c);
    QColor getGeometryPointColor() const;

    //设置几何线颜色
    void setGeometryCurveColor(const QColor& c);
    QColor getGeometryCurveColor() const;

    //设置几何面颜色
    void setGeometrySurfaceColor(const QColor& c);
    QColor getGeometrySurfaceColor() const;

    //几何体的显示效果
    GeometryDisplayTypes getGeometryDisplayType() const;

    //获取工具栏所在位置
    ToolBarArea getToolBarArea() const;

    //是否允许使用工具栏
    bool isToolBarVisible() const;

    //获取哪些action需要显示
    ToolBarActionFlag getToolBarActionFlags() const;

protected:
    //重载resize函数用于调整工具栏位置
    virtual void resizeEvent(QResizeEvent *e);

public:
    //添加几何
    void addShape(TopoDS_Shape *shape);
    void addBox(double *loc, double *para);
};

#endif
