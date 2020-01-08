#include<iostream>
#include "../../../include/sqlite3/sqlite3.h"

class BaseModel{

std::string table_name;

public:
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        const char * DIR = "../storage/tmp/database.db";
    static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        int i;
        for(i = 0; i<argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }
    void Initialize(){
         /* Open database */
        rc = sqlite3_open(DIR, &db);
        if( rc ) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        } else {
            fprintf(stderr, "Opened database successfully\n");
        }
          char *sql;
        /* Create SQL statement */
        sql = "CREATE TABLE Professor (" \
            "ID INT PRIMARY KEY NOT NULL," \
            "Password TEXT NOT NULL," \
            "FirsName TEXT NOT NULL," \
            "LastName TEXT NOT NULL," \
            "Faculty_ID INT NOT NULL," \
            "Is_supervisor INT," \
            "Grade_id INT," \
            "Courses_list Char(1000)," \
            "Students_list Char(1000) )" ;
        /* Execute SQL statement */
        if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Table created successfully\n");
        }
        sqlite3_close(db);
    }
    void Insert(){

    }
    void select(){}
    void remove(){}
    void update(){}

};
int main(){

    BaseModel bm;
    bm.Initialize();
}