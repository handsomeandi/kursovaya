#include "registercontroller.h"
#include "template.h"
#include "global.h"
#include<QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "picosha2.h"


RegisterController::RegisterController(QObject* parent):HttpRequestHandler(parent)
{

}


void RegisterController::service(HttpRequest &request, HttpResponse &response) {
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    HttpSession session = sessionStore->getSession(request,response,true);
    QString username = session.get("username").toString();
    QByteArray name = request.getParameter("name");
    QByteArray surname = request.getParameter("surname");
    QByteArray login = request.getParameter("login");
    QByteArray email = request.getParameter("email");
    QByteArray pwd = request.getParameter("pwd");
    QByteArray pwd_repeat = request.getParameter("pwd-repeat");
    QByteArray privacy = request.getParameter("privacy");
    QByteArray hashed_pwd = pwd.toHex();
    QByteArray hashed_rep = pwd_repeat.toHex();
    QSqlDatabase database = sqlconnection("register_connection");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }

    if(!name.isEmpty() && !surname.isEmpty() && !login.isEmpty() && !email.isEmpty() && !pwd.isEmpty() && !pwd_repeat.isEmpty()){

        QSqlQuery *query = new QSqlQuery(database);
        QString command = "INSERT INTO accounts(f_name, surname, login, email, pwd, pwd_repeat, prof_type) VALUES (";
        command.append("\"").append(name).append("\", \"").append(surname).append("\", \"").append(login).append("\", \"").append(email).append("\", \"")
                .append(hashed_pwd).append("\", \"").append(hashed_rep).append("\", ").append(privacy).append(")");
        std::string showcommand = command.toStdString();
        std::cout << showcommand;
        QSqlQuery *que = new QSqlQuery(database);
        que->exec("SELECT login,email FROM accounts");
        int counter = 0;
        while(que->next()){
            QString val0 = que->value(0).toString();
            QString val1 = que->value(1).toString();
            if(login == val0 || email == val1){
                counter++;
            }
        }
        if(counter>0){
            response.write("<p class=\"prog\">Пользователь уже существует</p>");
        }else{
            response.write("<p class=\"prog\">Пользователь зарегестрирован!</p><p class=\"prog\"><a href=\"/login\">Войти</a></p>");
            query->exec(command);
            QSqlQuery *get_user_id = new QSqlQuery(database);
            get_user_id->exec("SELECT id FROM accounts WHERE login='"+login+"'");
            QString user_id;
            while(get_user_id->next()){
                user_id = get_user_id->value(0).toString();
            }
            QSqlQuery *create_categories = new QSqlQuery(database);
            QString create_cat_com = "INSERT INTO categories(user_id, category_id, name, privacy) VALUES ("+user_id +",1,'Одежда',1), ("+user_id +",2,'Электроника',1), ("+user_id+",3,'Автомобили',1), ("+user_id+",4,'Недвижимость',1), ("+user_id+",5,'Другое',1)";
            qDebug() << create_cat_com;
            create_categories->exec(create_cat_com);
        }
    }
    Template t=templateCache->getTemplate("files/register",language);
    t.setVariable("username", username);
    t.setCondition("logged-in", !username.isEmpty());
    response.write(t.toUtf8());
}



