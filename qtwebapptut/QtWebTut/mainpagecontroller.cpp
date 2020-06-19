#include "template.h"
#include "global.h"
#include "mainpagecontroller.h"
#include<QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "picosha2.h"
#include <iostream>

MainPageController::MainPageController(QObject* parent)
    :HttpRequestHandler(parent) {
    // empty
}

void MainPageController::service(HttpRequest &request, HttpResponse &response) {


    HttpSession session = sessionStore->getSession(request,response,true);
    QString username = session.get("username").toString();
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    if(!session.contains("username")){
        Template t=templateCache->getTemplate("files/index",language);
        response.write(t.toUtf8(), true);
    }else{
        Template t=templateCache->getTemplate("files/feed",language);
        QString username = session.get("username").toString();
        QSqlDatabase database = sqlconnection("feed_connection");
        if(database.open()){
                qDebug("Connected");
        }
        else{
            qDebug("Not connected");
        }

        QSqlQuery *photo_query = new QSqlQuery(database);
        photo_query->exec("SELECT photo FROM items");
        QMap<QString,QString> photos_for_sort;
        QStringList sort_photos;
        while(photo_query->next()){
            sort_photos.append(photo_query->value(0).toString());
//            photos_for_sort[photo_query->value(0).toString().mid(0,13)] = photo_query->value(0).toString();
        }
        sort_photos.sort();
        t.loop("feed_items", sort_photos.size());
        for(int i=sort_photos.size()-1;i>=0;i--){
            QSqlQuery *photo_feed = new QSqlQuery(database);
            photo_feed->exec("SELECT title, user_id FROM items where photo='"+sort_photos[i]+"'");
            while(photo_feed->next()){
                t.setVariable("feed_items"+QString::number(i)+".title", photo_feed->value(0).toString());
                QSqlQuery *get_username = new QSqlQuery(database);
                get_username->exec("SELECT login FROM accounts where id="+photo_feed->value(1).toString());
                while(get_username->next()){
                    t.setVariable("feed_items"+QString::number(i)+".username", get_username->value(0).toString());
                }
                t.setVariable("feed_items"+QString::number(i)+".id", photo_feed->value(1).toString());
            }
        }
        t.setVariable("username", username);
        t.setCondition("logged-in", !username.isEmpty());
        response.write(t.toUtf8(), true);
    }
}
