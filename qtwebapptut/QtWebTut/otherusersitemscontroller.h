#ifndef OTHERUSERSITEMSCONTROLLER_H
#define OTHERUSERSITEMSCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class OtherUsersItemsController : public HttpRequestHandler {
    Q_OBJECT
public:
    OtherUsersItemsController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // OTHERUSERSITEMSCONTROLLER_H

