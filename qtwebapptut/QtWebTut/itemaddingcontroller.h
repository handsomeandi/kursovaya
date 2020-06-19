#ifndef ITEMADDINGCONTROLLER_H
#define ITEMADDINGCONTROLLER_H

#include "httprequesthandler.h"
#include "httprequest.h"
#include "httpresponse.h"
#include <QImage>
#include <QDir>

using namespace stefanfrings;

class ItemAddingController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(ItemAddingController)
public:
    ItemAddingController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // ITEMADDINGCONTROLLER_H


