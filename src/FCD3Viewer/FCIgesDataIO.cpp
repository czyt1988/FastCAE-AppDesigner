#include "FCIgesDataIO.h"
#include <TopoDS_Shape.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Reader.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <QFileInfo>
#include <QDebug>
FCIgesDataIO::FCIgesDataIO(QObject *par) : FCAbstractGeometryDataIO(par)
{
}


FCIgesDataIO::~FCIgesDataIO()
{
}


void FCIgesDataIO::read()
{
    FCGeometryDataIOResult res;
    TopoDS_Shape aShape;

    IGESControl_Controller::Init();
    IGESControl_Reader Reader;
    std::string str = getFileName().toStdString();
    const char *c_fn = str.c_str();
    Standard_Integer status = Reader.ReadFile(c_fn);

    if (status != IFSelect_RetDone) {
        switch (status)
        {
        case IFSelect_RetVoid:
            res.setErrorString(tr("created nothing, or no data to process"));
            break;

        case IFSelect_RetStop:
            res.setErrorString(tr("indicates end or stop"));
            break;

        case IFSelect_RetFail:
            res.setErrorString(tr("execution was run and has failed"));
            break;

        case IFSelect_RetError:
            res.setErrorString(tr("error in command or input data, no execution"));
            break;

        default:
            res.setErrorString(tr("unknow error"));
            break;
        }
        m_errString = res.getErrorString();
        qWarning() << m_errString;
        emit readed(res);
        return;
    }

    Reader.SetReadVisible(Standard_True);
    Reader.PrintCheckLoad(Standard_True, IFSelect_GeneralInfo);
    Reader.ClearShapes();
    Reader.TransferRoots();

    aShape = Reader.OneShape();

    TopTools_HSequenceOfShape *sequanceOfShape = new TopTools_HSequenceOfShape;

    sequanceOfShape->Append(aShape);

    Standard_Integer index = sequanceOfShape->Length();
    TopoDS_Shape theCompSolid = sequanceOfShape->ChangeValue(index);
    TopoDS_Shape *shape = new TopoDS_Shape;

    *shape = theCompSolid;
    res.setShape(shape);
    QFileInfo info(getFileName());
    const QString name = info.fileName();

    res.setFileName(name);
    qInfo() << tr("finish read igs file:") << getFileName();
    emit readed(res);
}


/**
 * @brief @todo 目前暂不支持igs的写功能
 */
void FCIgesDataIO::write()
{
    emit writed(false);
}


QString FCIgesDataIO::errorString() const
{
    return (m_errString);
}
