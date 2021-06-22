#include "FCGeometryDataIOWorker.h"
#include "FCAbstractGeometryDataIO.h"
#include "FCIgesDataIO.h"
#include <QThread>
#include <QFileInfo>
#include <QDebug>
class FCGeometryDataIOWorkerPrivate {
public:
    FC_IMPL_PUBLIC(FCGeometryDataIOWorker)
    FCGeometryDataIOWorkerPrivate(FCGeometryDataIOWorker *p);
    bool _isWorking;
};

FCGeometryDataIOWorkerPrivate::FCGeometryDataIOWorkerPrivate(FCGeometryDataIOWorker *p)
    : q_ptr(p)
    , _isWorking(false)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////

FCGeometryDataIOWorker::FCGeometryDataIOWorker(QObject *p) : QObject(p)
    , d_ptr(new FCGeometryDataIOWorkerPrivate(this))
{
    qRegisterMetaType<FCGeometryDataIOResult>("qRegisterMetaType");
}


FCGeometryDataIOWorker::~FCGeometryDataIOWorker()
{
}


/**
 * @brief 判断是否正在读取
 * @return
 */
bool FCGeometryDataIOWorker::isWorking() const
{
    return (d_ptr->_isWorking);
}


/**
 * @brief 根据后缀产生不同的io
 * @param filename
 */
void FCGeometryDataIOWorker::read(const QString& filename)
{
    d_ptr->_isWorking = true;
    QFileInfo f(filename);
    QString suffix = f.suffix();

    //通过后缀建立io
    FCAbstractGeometryDataIO *io = nullptr;

    if ((suffix == QStringLiteral("iges")) || (suffix == QStringLiteral("igs"))) {
        io = new FCIgesDataIO();
    }
    if (io == nullptr) {
        qWarning() << tr("know suffix:") << suffix;
        FCGeometryDataIOResult r;
        emit readed(r);
    }
    qInfo() << tr("start read:") << filename;
    io->setFileName(filename);
    //建立多线程
    QThread *thread = new QThread();

    io->moveToThread(thread);
    connect(thread, &QThread::finished, io, &FCAbstractGeometryDataIO::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    //业务逻辑
    connect(this, &FCGeometryDataIOWorker::startRead, io, &FCAbstractGeometryDataIO::read);
    connect(io, &FCAbstractGeometryDataIO::readed, this, &FCGeometryDataIOWorker::readed);
    //清理工作
    connect(io, &FCAbstractGeometryDataIO::readed, this, [thread, this](FCGeometryDataIOResult result) {
        Q_UNUSED(result);
        thread->quit();
        this->d_ptr->_isWorking = false;
    });
    //线程开启
    thread->start();
    //开始读取
    emit startRead();
}
