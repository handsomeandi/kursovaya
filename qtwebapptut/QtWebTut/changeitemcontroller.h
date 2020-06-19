#ifndef CHANGEITEMCONTROLLER_H
#define CHANGEITEMCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class ChangeItemController : public HttpRequestHandler
{
    Q_OBJECT
public:
    ChangeItemController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // CHANGEITEMCONTROLLER_H

