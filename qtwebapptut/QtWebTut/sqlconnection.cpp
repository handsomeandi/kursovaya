#include "sqlconnection.h"


QSqlDatabase sqlconnection(const QString name_of_db){
    static QSqlDatabase db =  QSqlDatabase::addDatabase("QMYSQL",name_of_db);
    QString winpas = getenv("PAS");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("50662153Ff");
    db.setDatabaseName("users");
    return db;
}
