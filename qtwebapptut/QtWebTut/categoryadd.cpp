#include "categoryadd.h"
#include "template.h"
#include "global.h"

CategoryAdd::CategoryAdd(QObject* parent)
    :HttpRequestHandler(parent) {

}

void CategoryAdd::service(HttpRequest &request, HttpResponse &response) {
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    HttpSession session = sessionStore->getSession(request,response,true);
    Template t=templateCache->getTemplate("files/cataddition",language);
    QSqlDatabase database = sqlconnection("category_adding");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }
    QString name_of_cat = request.getParameter("name");
    QString cat_privacy = request.getParameter("added_category_privacy");
    QSqlQuery *user_id_q = new QSqlQuery(database);
    QString user_id;
    user_id_q->exec("SELECT * FROM accounts WHERE login='"+session.get("username").toString()+"'");
    while(user_id_q->next()){
        user_id = user_id_q->value(0).toString();
    }
    QSqlQuery *number_of_categories = new QSqlQuery(database);
    number_of_categories->exec("SELECT COUNT(*) FROM categories WHERE user_id="+user_id);
    QString num_of_categories;
    while(number_of_categories->next()){
        num_of_categories = number_of_categories->value(0).toString();
    }
    int prev_cat = num_of_categories.toInt();
    int cat_id = prev_cat+1;
    QString category_id = QString::number(cat_id);
    QSqlQuery *add_new_cat = new QSqlQuery(database);
    add_new_cat->exec("INSERT INTO categories(user_id, category_id, name, privacy) VALUES ("+user_id+", "+category_id+", '"+name_of_cat + "', " +cat_privacy + ")");
    response.write(t.toUtf8());
    if(!name_of_cat.isEmpty()){
        response.write("<p class=\"prog\">Категория успешно добавлена!</>");
    }
}
