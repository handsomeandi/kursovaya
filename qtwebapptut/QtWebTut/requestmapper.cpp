#include "requestmapper.h"
#include "global.h"
#include "httpsession.h"

RequestMapper::RequestMapper(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());
    HttpSession session = sessionStore->getSession(request,response,true);
    QString username = session.get("username").toString();

    if(path == "/"){
        mainPageController.service(request,response);
    }
    else if(path.startsWith("/login")){
        if(session.contains("username")){
            response.redirect("/");
        }else{
            loginController.service(request,response);
        }
    }
    else if(path.startsWith("/register")){
        registerController.service(request,response);
    }
    else if(path.startsWith("/logout")){
        logout.service(request,response);
        response.redirect("/");
    }
    else if(path.startsWith("/add")){
        qDebug() << "Username: ";
        qDebug() <<session.get("username").toString();
        if(session.get("username").toString() == ""){
            response.redirect("/login");
        }else{
            itemAddingController.service(request,response);
        }
    }else if(path.startsWith("/items")){
        if(session.get("username").toString() == ""){
            response.redirect("/login");
        }else{
            userItemsController.service(request,response);
        }
    }else if(path.startsWith("/change")){
        if(session.get("username").toString() == ""){
            response.redirect("/login");
        }else{
            changeItemController.service(request,response);
        }
    }else if(path.startsWith("/category_add")){
        if(session.get("username").toString() == ""){
            response.redirect("/login");
        }else{
            categoryAdd.service(request,response);
        }
    }else if(path.startsWith("/categories")){
        if(session.get("username").toString() == ""){
            response.redirect("/login");
        }else{
            categoriesController.service(request,response);
        }
    }else if(path.startsWith("/user_list")){
        userListController.service(request,response);
    }
    else if(path.startsWith("/other_users")){
        otherUserItemsController.service(request,response);
    }
    else{
        staticFileController->service(request,response);
    }
    qDebug("RequestMapper: finished request");
}
