#include "FCToolBox.h"
#include "FCNodeListWidget.h"
void FCToolBox::addItems(const QMap<QString, QList<FCNodeMetaData> >& datas)
{
    for (auto i = datas.begin(); i != datas.end(); ++i)
    {
        FCNodeListWidget *nlw = new FCNodeListWidget(this);
        nlw->addItems(i.value());
        addItem(nlw, i.key());
    }
}
