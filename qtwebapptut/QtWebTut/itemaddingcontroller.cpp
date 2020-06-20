#include <QTime>
#include "template.h"
#include "global.h"
#include "itemaddingcontroller.h"

ItemAddingController::ItemAddingController(QObject* parent)
    :HttpRequestHandler(parent)
{

}

void ItemAddingController::service(HttpRequest &request, HttpResponse &response){
    QByteArray language=request.getHeader("Accept-Language");
    HttpSession session = sessionStore->getSession(request,response,true);
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    QSqlDatabase database = sqlconnection("item_adding");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }
    Template t=templateCache->getTemplate("files/add",language);
    QString username = session.get("username").toString();
    QDir pathhh = QDir("../QtWebTut/docroot/files/user-images");
    QString pathh = pathhh.filePath("");
    QByteArray title = request.getParameter("title");
    QByteArray description = request.getParameter("description");
    QByteArray photo = request.getParameter("photo");
    QByteArray price = request.getParameter("price");
    QByteArray link = request.getParameter("link");
    QByteArray category = request.getParameter("category");
    QSqlQuery *user_id_que = new QSqlQuery(database);
    user_id_que->exec("SELECT id FROM accounts WHERE login='"+session.get("username").toString()+"'");
    QString user_id;
    while(user_id_que->next()){
        user_id = user_id_que->value(0).toString();
    }

    QSqlQuery *num_rows = new QSqlQuery(database);
    num_rows->exec("SELECT COUNT(*) FROM categories WHERE user_id="+user_id);
    int numrows;
    while(num_rows->next()){
        numrows = num_rows->value(0).toInt();
        qDebug("Number of rows");
        qDebug() << numrows;
    }
    t.loop("category", numrows);

    QSqlQuery *categories = new QSqlQuery(database);
    categories->exec("SELECT name,category_id FROM categories WHERE user_id="+user_id);
    int counter = 0;
    while(categories->next()){
        QString number = QString::number(counter);
        t.setVariable("category"+number+".name",categories->value(0).toString());
        t.setVariable("category"+number+".id",categories->value(1).toString());
        counter++;
    }

    if (request.getParameter("photo") != ""){
        QTemporaryFile* file=request.getUploadedFile("photo");

        if (file)
        {
            qDebug("Success upload");
            while (!file->atEnd() && !file->error())
            {
                const QByteArray buffer=file->read(10000000);
                QImage image = QImage::fromData(buffer);
                QDir pathhh = QDir::currentPath();
                QString path_ph = pathhh.relativeFilePath("../QtWebTut/docroot/files/user-images/");
                const QString saveFileName = path_ph + "/" + QString::number(QDateTime::currentMSecsSinceEpoch(),10) + photo;
                QString command = "INSERT INTO items(title, ";
                int desc=0, pr=0,lnk=0, ph=0;
                if(!description.isEmpty() && desc == 0){
                    command.append("descript, photo, ");
                    desc++;
                    ph=1;
                    if(!price.isEmpty()&& pr==0){
                        pr++;
                        command.append("price, ");
                    }
                    if(!link.isEmpty() && lnk == 0){
                        lnk++;
                        command.append("link, ");
                    }
                }
                if(!price.isEmpty()&& pr==0){
                    pr++;
                    ph=2;
                    command.append("price, photo, ");
                    if(!link.isEmpty() && lnk == 0){
                        lnk++;
                        command.append("link, ");
                    }
                }
                if(!link.isEmpty()&&lnk==0){
                    lnk++;
                    ph=3;
                    command.append("link, photo, ");
                }
                if(desc==0&&pr==0&&ph==0){
                    command.append("photo, ");
                }
                command.append("category, user_id) VALUES('"+ title + "', ");
                if(desc == 1 || pr == 1 || lnk == 1 ){
                    if(desc == 1){
                        command.append("'" + description + "', ");
                        if(ph==1){
                            command.append("'" + QString::number(QDateTime::currentMSecsSinceEpoch(),10) + photo + "', ");
                        }
                    }
                    if(pr==1){
                        command.append(price + ", ");
                        if(ph==2){
                            command.append("'" + QString::number(QDateTime::currentMSecsSinceEpoch(),10) + photo + "', ");
                        }
                    }
                    if(lnk==1){
                        command.append("'" + link + "', ");
                        if(ph==3){
                            command.append("'" + QString::number(QDateTime::currentMSecsSinceEpoch(),10) + photo + "', ");
                        }
                    }
                }
                else{
                    command.append("'" + QString::number(QDateTime::currentMSecsSinceEpoch(),10) + photo + "', ");
                }
                command.append(category + ", " + user_id + ")");
                  qDebug() << "User id: " + user_id + "\n";
                  qDebug() << "Command: " + command + "\n";

                  QSqlQuery *add_item = new QSqlQuery(database);
                  add_item->exec(command);
                qDebug() << "Directory: " + saveFileName + "\n";
                if(image.save(saveFileName)){
                    qDebug("Success upload");
                    response.write("<p class=\"prog\">Предмет успешно добавлен!</p><p class=\"prog\"><a href=\"/items\">Мои предметы</a></p>");
                }else{
                    qDebug("Erorr loaded!");
                }
            }
        }
        else
        {
            qDebug("upload failed");
        }
    }
    t.setCondition("logged-in", !username.isEmpty());
    response.write(t.toUtf8(), true);
}


