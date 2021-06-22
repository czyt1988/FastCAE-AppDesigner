#include "FCAbstractGeometryDataIO.h"

class FCAbstractGeometryDataIOPrivate {
public:
    FC_IMPL_PUBLIC(FCAbstractGeometryDataIO)
    FCAbstractGeometryDataIOPrivate(FCAbstractGeometryDataIO *p) : q_ptr(p)
    {
    }


    QString _fileName;
};

FCAbstractGeometryDataIO::FCAbstractGeometryDataIO(QObject *par) : QObject(par)
    , d_ptr(new FCAbstractGeometryDataIOPrivate(this))
{
}


FCAbstractGeometryDataIO::~FCAbstractGeometryDataIO()
{
}


void FCAbstractGeometryDataIO::setFileName(const QString& filename)
{
    d_ptr->_fileName = filename;
}


QString FCAbstractGeometryDataIO::getFileName() const
{
    return (d_ptr->_fileName);
}
