#include "FCGeometryDataIOResult.h"
#include <TopoDS_Shape.hxx>

class FCGeometryDataIOResultPrivate {
    FC_IMPL_PUBLIC(FCGeometryDataIOResult)
public:
    FCGeometryDataIOResultPrivate(FCGeometryDataIOResult *p);
    TopoDS_Shape *_shape;
    QString _errString;
    QString _fileName;
};

FCGeometryDataIOResultPrivate::FCGeometryDataIOResultPrivate(FCGeometryDataIOResult *p)
    : q_ptr(p)
    , _shape(nullptr)
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FCGeometryDataIOResult::FCGeometryDataIOResult()
    : d_ptr(new FCGeometryDataIOResultPrivate(this))
{
}


FCGeometryDataIOResult::FCGeometryDataIOResult(const FCGeometryDataIOResult& rhs)
    : d_ptr(new FCGeometryDataIOResultPrivate(this))
{
    d_ptr->_shape = rhs.d_ptr->_shape;
    d_ptr->_errString = rhs.d_ptr->_errString;
}


FCGeometryDataIOResult& FCGeometryDataIOResult::operator=(FCGeometryDataIOResult& rhs)
{
    d_ptr->_shape = rhs.d_ptr->_shape;
    d_ptr->_errString = rhs.d_ptr->_errString;
    return (*this);
}


FCGeometryDataIOResult::FCGeometryDataIOResult(FCGeometryDataIOResult&& rhs)
{
    d_ptr.reset(rhs.d_ptr.take());
}


FCGeometryDataIOResult& FCGeometryDataIOResult::operator=(FCGeometryDataIOResult&& rhs)
{
    d_ptr.reset(rhs.d_ptr.take());
    return (*this);
}


FCGeometryDataIOResult::~FCGeometryDataIOResult()
{
}


bool FCGeometryDataIOResult::isValid() const
{
    return (shape() != nullptr);
}


TopoDS_Shape *FCGeometryDataIOResult::shape()
{
    return (d_ptr->_shape);
}


const TopoDS_Shape *FCGeometryDataIOResult::shape() const
{
    return (d_ptr->_shape);
}


void FCGeometryDataIOResult::setShape(TopoDS_Shape *s)
{
    d_ptr->_shape = s;
}


void FCGeometryDataIOResult::destory()
{
    if (d_ptr->_shape) {
        delete (d_ptr->_shape);
    }
    d_ptr->_shape = nullptr;
}


void FCGeometryDataIOResult::setErrorString(const QString& err)
{
    d_ptr->_errString = err;
}


QString FCGeometryDataIOResult::getErrorString() const
{
    return (d_ptr->_errString);
}


void FCGeometryDataIOResult::setFileName(const QString& fileName)
{
    d_ptr->_fileName = fileName;
}


QString FCGeometryDataIOResult::getFileName() const
{
    return (d_ptr->_fileName);
}
