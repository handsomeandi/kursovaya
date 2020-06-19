#ifndef USERLISTCONTROLLER_H
#define USERLISTCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class UserListController : public HttpRequestHandler {
    Q_OBJECT
public:
    UserListController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // USERLISTCONTROLLER_H
