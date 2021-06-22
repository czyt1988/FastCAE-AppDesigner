#include "FCD3Viewer.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS.hxx>
#include <IVtkOCC_Shape.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>
#include <vtkDataSetMapper.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <QMultiHash>
#include "FCGeometryDataIOWorker.h"
#include "FCGeometryDataIOResult.h"
#include <QResizeEvent>
#include <QToolBar>
#include <QMap>
class FCD3ViewerPrivate {
public:
    FC_IMPL_PUBLIC(FCD3Viewer)
    FCD3ViewerPrivate(FCD3Viewer *p);

    ~FCD3ViewerPrivate();

    //尝试刷新，如果符合条件将自动刷新，通过_isAutoRender可以控制刷新
    void checkRender();

    //构建ui
    void setupUI();

    //更新工具栏
    void updateToolBarPosition();

    FCD3Viewer::ToolBarArea _toolBarArea;
    QToolBar *_toolBar;
    QMap<FCD3Viewer::ToolBarActions, QAction *> _toolBarActionsMap;
    FCD3Viewer::ToolBarActionFlag _toolActionFlags;
    vtkSmartPointer<vtkRenderer> _render;
    vtkSmartPointer<vtkRenderWindow> _renderWindow;
    QList<vtkActor *> _vertexActors;
    QList<vtkActor *> _edgeActors;
    QList<vtkActor *> _faceActors;
    vtkOrientationMarkerWidget *_axesWidget;
    bool _isAutoRender;
    FCD3Viewer::GeometryDisplayTypes _geometryDisplayTypes;         ///< 几何体显示效果
    QColor _geometryPointColor;                                     ///< 几何点颜色
    QColor _geometryCurveColor;                                     ///< 几何线颜色
    QColor _geometrySurfaceColor;                                   ///< 几何面颜色
    int _geometrySurfaceTransparency;                               ///< 几何面的透明度[0-100]
    QHash<vtkPolyData *, vtkActor *> _selectPolydataActorHash;      //选中的actord的集合
//    QMultiHash<Geometry::GeometrySet*, int> _selectItems;
    //
    FCGeometryDataIOWorker _geoIOWorker;///< 导入模型的io
};

FCD3ViewerPrivate::FCD3ViewerPrivate(FCD3Viewer *p) : q_ptr(p)
    , _toolBarArea(FCD3Viewer::ToolBarOnTop)
    , _toolActionFlags(FCD3Viewer::ActionAll)
    , _axesWidget(nullptr)
    , _isAutoRender(false)
    , _geometryDisplayTypes(FCD3Viewer::DisplayCurve|FCD3Viewer::DisplaySurface)
    , _geometryPointColor(Qt::black)
    , _geometryCurveColor(Qt::black)
    , _geometrySurfaceColor(Qt::gray)
    , _geometrySurfaceTransparency(100)
{
}


FCD3ViewerPrivate::~FCD3ViewerPrivate()
{
    int c = _vertexActors.size();

    for (int i = 0; i < c; ++i)
    {
        vtkActor *ac = _vertexActors.at(i);
        _render->RemoveActor(ac);
    }
    c = _edgeActors.size();
    for (int i = 0; i < c; ++i)
    {
        vtkActor *ac = _edgeActors.at(i);
        _render->RemoveActor(ac);
    }
    c = _faceActors.size();
    for (int i = 0; i < c; ++i)
    {
        vtkActor *ac = _faceActors.at(i);
        _render->RemoveActor(ac);
    }
    _faceActors.clear();
    _edgeActors.clear();
    _vertexActors.clear();
}


void FCD3ViewerPrivate::checkRender()
{
    if (_isAutoRender) {
        _renderWindow->Render();
    }
}


void FCD3ViewerPrivate::setupUI()
{
    //窗口初始化
    FCD3Viewer *p = q_ptr;

    _renderWindow = p->renderWindow();
    _render = vtkSmartPointer<vtkRenderer>::New();
    _render->SetGradientBackground(true);
    _render->SetBackground2(0.0, 0.333, 1.0);
    _render->SetBackground(1.0, 1.0, 1.0);
    _renderWindow->AddRenderer(_render);

    //
    vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();

    _axesWidget = vtkOrientationMarkerWidget::New();
    _axesWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    _axesWidget->SetOrientationMarker(axesActor);
    _axesWidget->SetInteractor(p->interactor());
    _axesWidget->SetViewport(0.0, 0.0, 0.2, 0.2);
    _axesWidget->SetEnabled(1);
    _axesWidget->InteractiveOff();

    //工具栏初始化
    _toolBar = new QToolBar(p);
    _toolBar->setIconSize(QSize(16, 16));
    //添加action
    auto createActionFp = [this, p](FCD3Viewer::ToolBarActions flag,
        const QIcon& ico, const QString& obj) {
            QAction *act = new QAction(p);

            act->setObjectName(obj);
            act->setIcon(ico);
            this->_toolBarActionsMap[flag] = act;
            this->_toolBar->addAction(act);
        };

    createActionFp(FCD3Viewer::ActionViewXPlus, QIcon(":/icon/icon/xPlus.png"), "actionViewXPlus");
    createActionFp(FCD3Viewer::ActionViewXMiuns, QIcon(":/icon/icon/xMinus.png"), "actionViewXMiuns");
    createActionFp(FCD3Viewer::ActionViewYPlus, QIcon(":/icon/icon/yPlus.png"), "actionViewYPlus");
    createActionFp(FCD3Viewer::ActionViewYMiuns, QIcon(":/icon/icon/yMinus.png"), "actionViewYMiuns");
    createActionFp(FCD3Viewer::ActionViewZPlus, QIcon(":/icon/icon/zPlus.png"), "actionViewZPlus");
    createActionFp(FCD3Viewer::ActionViewZMiuns, QIcon(":/icon/icon/zMinus.png"), "actionViewZMiuns");
    createActionFp(FCD3Viewer::ActionViewFit, QIcon(":/icon/icon/fit.png"), "actionViewFit");

    updateToolBarPosition();
}


void FCD3ViewerPrivate::updateToolBarPosition()
{
    QSize ws = q_ptr->size();

    switch (_toolBarArea)
    {
    case FCD3Viewer::ToolBarOnTop:
    {
        if (_toolBar->orientation() != Qt::Horizontal) {
            _toolBar->setOrientation(Qt::Horizontal);
        }
        QSize s = _toolBar->sizeHint();
        _toolBar->setGeometry(0, 0, ws.width(), s.height());
    }
    break;

    case FCD3Viewer::ToolBarOnLeft:
    {
        if (_toolBar->orientation() != Qt::Vertical) {
            _toolBar->setOrientation(Qt::Vertical);
        }
        QSize s = _toolBar->sizeHint();
        _toolBar->setGeometry(0, 0, s.width(), ws.height());
    }
    break;

    case FCD3Viewer::ToolBarOnBottom:
    {
        if (_toolBar->orientation() != Qt::Horizontal) {
            _toolBar->setOrientation(Qt::Horizontal);
        }
        QSize s = _toolBar->sizeHint();
        _toolBar->setGeometry(0, ws.height()-s.height(), ws.width(), s.height());
    }
    break;

    case FCD3Viewer::ToolBarOnRight:
    {
        if (_toolBar->orientation() != Qt::Vertical) {
            _toolBar->setOrientation(Qt::Vertical);
        }
        QSize s = _toolBar->sizeHint();
        _toolBar->setGeometry(ws.width()-s.width(), 0, s.width(), ws.height());
    }
    break;
    }
}


//==============================================================


FCD3Viewer::FCD3Viewer(QWidget *parent)
    : QVTKOpenGLNativeWidget(parent)
    , d_ptr(new FCD3ViewerPrivate(this))
{
    d_ptr->setupUI();
    //导入文件
    connect(&(d_ptr->_geoIOWorker), &FCGeometryDataIOWorker::readed, this, [this](FCGeometryDataIOResult r) {
        this->addShape(r.shape());
        r.destory();
        this->fitView();
    });
}


FCD3Viewer::~FCD3Viewer()
{
}


void FCD3Viewer::fitView()
{
    d_ptr->_render->ResetCamera();
    d_ptr->_renderWindow->Render();
}


/**
 * @brief 设置渐变背景
 * @param en
 */
void FCD3Viewer::setGradientBackgroundEnable(bool en)
{
    d_ptr->_render->SetGradientBackground(en);
    d_ptr->checkRender();
}


/**
 * @brief 判断是否渐变背景
 * @return
 * @sa setGradientBackgroundEnable
 */
bool FCD3Viewer::isGradientBackgroundEnable() const
{
    return (d_ptr->_render->GetGradientBackground());
}


/**
 * @brief 设置背景颜色
 * @param clr
 */
void FCD3Viewer::setBackground(const QColor& clr)
{
    if (!clr.isValid()) {
        return;
    }
    d_ptr->_render->SetBackground(clr.redF(), clr.greenF(), clr.blueF());
    d_ptr->checkRender();
}


/**
 * @brief 获取背景颜色
 * @return
 */
QColor FCD3Viewer::getBackground() const
{
    double r, g, b;

    d_ptr->_render->GetBackground(r, g, b);
    QColor res;

    res.setRedF(r);
    res.setGreenF(g);
    res.setBlueF(b);
    return (res);
}


/**
 * @brief 设置背景颜色
 * @param clr
 */
void FCD3Viewer::setBackground2(const QColor& clr)
{
    if (!clr.isValid()) {
        return;
    }
    d_ptr->_render->SetBackground2(clr.redF(), clr.greenF(), clr.blueF());
    d_ptr->checkRender();
}


/**
 * @brief 获取背景颜色
 * @return
 */
QColor FCD3Viewer::getBackground2() const
{
    double r, g, b;

    d_ptr->_render->GetBackground2(r, g, b);
    QColor res;

    res.setRedF(r);
    res.setGreenF(g);
    res.setBlueF(b);
    return (res);
}


/**
 * @brief 设置背景透明度，默认为0.0
 *
 * 透明度的范围为0.0到1.0
 * @param a
 */
void FCD3Viewer::setBackgroundAlpha(double a)
{
    if (a > 1.0) {
        a = 1.0;
    }else if (a < 0) {
        a = 0.0;
    }
    d_ptr->_render->SetBackgroundAlpha(a);
    d_ptr->checkRender();
}


/**
 * @brief 获取背景透明度
 * @return
 * @sa setBackgroundAlpha
 */
double FCD3Viewer::getBackgroundAlpha() const
{
    return (d_ptr->_render->GetBackgroundAlpha());
}


/**
 * @brief 设置是否进行自动刷新
 * @param isenable
 */
void FCD3Viewer::setAutoRender(bool isenable)
{
    d_ptr->_isAutoRender = isenable;
}


/**
 * @brief 渲染
 */
void FCD3Viewer::render()
{
    d_ptr->_renderWindow->Render();
}


/**
 * @brief 设定视图
 * @param lookX
 * @param lookY
 * @param lookZ
 * @param upX
 * @param upY
 * @param upZ
 */
void FCD3Viewer::view(double lookX, double lookY, double lookZ, double upX, double upY, double upZ, double posX, double posY, double posZ)
{
    vtkCamera *camera = d_ptr->_render->GetActiveCamera();

    if (camera == nullptr) {
        return;
    }
    camera->SetPosition(posX, posY, posZ);          //相机位置
    camera->SetFocalPoint(lookX, lookY, lookZ);     //焦点位置
    camera->SetViewUp(upX, upY, upZ);               //朝上方向
    d_ptr->_render->ResetCamera();
    d_ptr->checkRender();
}


/**
 * @brief
 * @param type
 */
void FCD3Viewer::view(FCD3Viewer::ViewType type)
{
    switch (type)
    {
    case ViewXPlus:
        view(0, 0, 0, 0, 0, 1, 5000, 0, 0);
        break;

    case ViewXMiuns:
        view(0, 0, 0, 0, 0, 1, -5000, 0, 0);
        break;

    case ViewYPlus:
        view(0, 0, 0, 0, 0, 1, 0, 5000, 0);
        break;

    case ViewYMiuns:
        view(0, 0, 0, 0, 0, 1, 0, -5000, 0);
        break;

    case ViewZPlus:
        view(0, 0, 0, 0, 1, 0, 0, 0, 5000);
        break;

    case ViewZMiuns:
        view(0, 0, 0, 0, 1, 0, 0, 0, -1);
        break;

    case ViewFit:
        fitView();
        break;

    default:
        break;
    }
}


/**
 * @brief 清空所有的已经高亮显示对象
 */
void FCD3Viewer::clearGeometryHighLight()
{
    restoreGeoColor();
    QList<vtkActor *> setSelectActor = d_ptr->_selectPolydataActorHash.values();//所有的选择的对象的actor数据

    for (int i = 0; i < setSelectActor.size(); i++)
    {
        vtkActor *ac = setSelectActor.at(i);
        d_ptr->_render->RemoveActor(ac);
    }
    d_ptr->_selectPolydataActorHash.clear();
//    _selectItems.clear();
    d_ptr->checkRender();
}


/**
 * @brief 设置几何体的显示效果
 * 设置点线体（面）的显示与隐藏
 * @param f 显示状态
 */
void FCD3Viewer::setGeometryDisplayType(GeometryDisplayTypes f)
{
    clearGeometryHighLight();
    d_ptr->_geometryDisplayTypes = f;
    for (auto var : d_ptr->_vertexActors)
    {
        var->SetVisibility(f.testFlag(DisplayPoint));
    }
    for (auto var : d_ptr->_edgeActors)
    {
        var->SetVisibility(f.testFlag(DisplayCurve));
    }
    for (auto var : d_ptr->_faceActors)
    {
        var->SetVisibility(f.testFlag(DisplaySurface));
    }
    d_ptr->checkRender();
}


/**
 * @brief 导入几何
 * @param filename
 * @return
 */
void FCD3Viewer::importGeometry(const QString& filename)
{
    d_ptr->_geoIOWorker.read(filename);
}


/**
 * @brief 设置工具栏所在位置
 * @param area
 */
void FCD3Viewer::setToolBarArea(FCD3Viewer::ToolBarArea area)
{
    d_ptr->_toolBarArea = area;
}


/**
 * @brief 设置允许显示工具栏
 * @param enable
 */
void FCD3Viewer::setToolBarVisible(bool enable)
{
    d_ptr->_toolBar->setVisible(enable);
}


/**
 * @brief 设置哪些actions可见
 * @param flag
 */
void FCD3Viewer::setToolBarActionFlags(ToolBarActionFlag flag)
{
    d_ptr->_toolActionFlags = flag;
    QToolBar *toolbar = d_ptr->_toolBar;
    QList<QAction *> acts = toolbar->actions();
}


/**
 * @brief 判断是否进行自动绘制
 * @return
 */
bool FCD3Viewer::isAutoRender() const
{
    return (d_ptr->_isAutoRender);
}


/**
 * @brief 还原所有对象颜色并清空高亮显示
 */
void FCD3Viewer::restoreGeoColor()
{
    //还原所有actor的颜色
    for (auto var : d_ptr->_vertexActors)
    {
        var->GetProperty()->SetColor(d_ptr->_geometryPointColor.redF()
            , d_ptr->_geometryPointColor.greenF()
            , d_ptr->_geometryPointColor.blueF());
        var->GetProperty()->SetOpacity(d_ptr->_geometryPointColor.alphaF());
    }
    for (auto var : d_ptr->_edgeActors)
    {
        var->GetProperty()->SetColor(d_ptr->_geometryCurveColor.redF()
            , d_ptr->_geometryCurveColor.greenF()
            , d_ptr->_geometryCurveColor.blueF());
        var->GetProperty()->SetOpacity(d_ptr->_geometryCurveColor.alphaF());
    }
    for (auto var : d_ptr->_faceActors)
    {
        var->GetProperty()->SetColor(d_ptr->_geometrySurfaceColor.redF()
            , d_ptr->_geometrySurfaceColor.greenF()
            , d_ptr->_geometrySurfaceColor.blueF());
        var->GetProperty()->SetOpacity(d_ptr->_geometrySurfaceColor.alphaF());
    }

    d_ptr->checkRender();
}


/**
 * @brief 设置几何点颜色
 * @param c
 */
void FCD3Viewer::setGeometryPointColor(const QColor& c)
{
    d_ptr->_geometryPointColor = c;
}


/**
 * @brief 几何点颜色
 * @return
 */
QColor FCD3Viewer::getGeometryPointColor() const
{
    return (d_ptr->_geometryPointColor);
}


/**
 * @brief 设置几何线颜色
 * @param c
 */
void FCD3Viewer::setGeometryCurveColor(const QColor& c)
{
    d_ptr->_geometryCurveColor = c;
}


/**
 * @brief 几何线颜色
 * @return
 */
QColor FCD3Viewer::getGeometryCurveColor() const
{
    return (d_ptr->_geometryCurveColor);
}


/**
 * @brief 设置几何面颜色
 * @param c
 */
void FCD3Viewer::setGeometrySurfaceColor(const QColor& c)
{
    d_ptr->_geometrySurfaceColor = c;
}


/**
 * @brief 几何面颜色
 * @return
 */
QColor FCD3Viewer::getGeometrySurfaceColor() const
{
    return (d_ptr->_geometrySurfaceColor);
}


/**
 * @brief 几何体的显示效果
 * @return
 */
FCD3Viewer::GeometryDisplayTypes FCD3Viewer::getGeometryDisplayType() const
{
    return (d_ptr->_geometryDisplayTypes);
}


/**
 * @brief 获取工具栏所在位置
 * @return
 */
FCD3Viewer::ToolBarArea FCD3Viewer::getToolBarArea() const
{
    return (d_ptr->_toolBarArea);
}


/**
 * @brief 是否允许使用工具栏
 * @return
 */
bool FCD3Viewer::isToolBarVisible() const
{
    return (d_ptr->_toolBar->isVisible());
}


/**
 * @brief 获取哪些action需要显示
 * @return
 */
FCD3Viewer::ToolBarActionFlag FCD3Viewer::getToolBarActionFlags() const
{
    return (d_ptr->_toolActionFlags);
}


/**
 * @brief 重载resize函数，用于调整工具栏位置
 * @param e
 */
void FCD3Viewer::resizeEvent(QResizeEvent *e)
{
    //调整工具栏位置
    d_ptr->updateToolBarPosition();
    QVTKOpenGLNativeWidget::resizeEvent(e);
}


/**
 * @brief 添加几何
 * @param shape
 */
void FCD3Viewer::addShape(TopoDS_Shape *shape)
{
    IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(*shape);
    vtkSmartPointer<IVtkTools_ShapeDataSource> DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
    vtkSmartPointer<IVtkTools_DisplayModeFilter> DMFilter = vtkSmartPointer<IVtkTools_DisplayModeFilter>::New();
    vtkSmartPointer<vtkDataSetMapper> M = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkActor *actor = vtkActor::New();

    DS->SetShape(aShapeImpl);
    DMFilter->AddInputConnection(DS->GetOutputPort());
    DMFilter->SetDisplayMode(DM_Shading);
    M->SetInputConnection(DMFilter->GetOutputPort());
    actor->SetMapper(M);
    d_ptr->_render->AddActor(actor);
    d_ptr->checkRender();
}


void FCD3Viewer::addBox(double *loc, double *para)
{
    gp_Pnt pt(loc[0], loc[1], loc[2]);
    TopoDS_Shape aBox = BRepPrimAPI_MakeBox(pt, para[0], para[1], para[2]).Shape();

    addShape(&aBox);
}
