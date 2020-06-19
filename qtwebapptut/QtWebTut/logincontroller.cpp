
#include <QTime>
#include "logincontroller.h"
#include "template.h"
#include "global.h"

LoginController::LoginController(QObject* parent)
    :HttpRequestHandler(parent) {
    // empty
}

void LoginController::service(HttpRequest &request, HttpResponse &response) {
    HttpSession session = sessionStore->getSession(request,response,true);
    QString username = session.get("username").toString();
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    Template t=templateCache->getTemplate("files/login",language);
    t.setVariable("username", username);
    t.setCondition("logged-in", !username.isEmpty());
    response.write(t.toUtf8());
    QSqlDatabase database = sqlconnection("login_connection");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }
            if(session.contains("username")){
                QByteArray username = session.get("username").toByteArray();
                response.write("You are already logged in.<br><a href=\"/\">Go to main page</a>");
            }
            else{
                QByteArray login = request.getParameter("login");
                QByteArray pwd = request.getParameter("pwd");
                QByteArray password = pwd.toHex();
                if(!login.isNull()){
                    QSqlQuery *query = new QSqlQuery(database);
                    query->exec("SELECT pwd FROM accounts WHERE login='"+login+"'");
                    if(query->size()==0){
                        response.write("<p class=\"prog\">User doesn't exist</p>");
                    }else{
                        while(query->next()){
                            QString result = query->value(0).toString();
                            if(password==result){
                                session.set("username", login);
                                response.write("<p class=\"prog\">Вход выполнен успешно!</p><p class=\"prog\"><a href=\"/\" class=\"link-item\">Главная страница</a></p><p class=\"prog\"><a href=\"/items\" class=\"link-item\">Мои вещи</a></p>");

                            }else{
                                response.write("<p class=\"prog\">Wrong password/login</p>");
                            }
                        }

                    }
                }
            }
    }
