#include <QTime>
#include "logout.h"
#include "template.h"
#include "global.h"

Logout::Logout(QObject* parent)
    :HttpRequestHandler(parent) {
    // empty
}

void Logout::service(HttpRequest &request, HttpResponse &response) {
    QByteArray language=request.getHeader("Accept-Language");
    HttpSession session = sessionStore->getSession(request,response,true);
    if(session.contains("username")){
        session.remove("username");
        session.remove("logged_in");
        if(session.contains("items")){
            session.remove("items");
        }
    }

}
