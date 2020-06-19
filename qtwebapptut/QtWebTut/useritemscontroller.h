#ifndef USERITEMSCONTROLLER_H
#define USERITEMSCONTROLLER_H
#include "httprequesthandler.h"
#include "httprequest.h"
#include "httpresponse.h"
#include <QImage>
#include <QDir>

using namespace stefanfrings;


class UserItemsController : public HttpRequestHandler
{
    Q_OBJECT
public:
    UserItemsController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // USERITEMSCONTROLLER_H

