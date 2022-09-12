#include <sqlite3.h>
#include <stdio.h>

int callback(void *, int, char **, char **);

int main(void) {
    
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("test00.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        
	sqlite3_close(db);
        return 1;
    }
    
    rc = sqlite3_exec(db, "SELECT * FROM tblone", callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
	sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    } 
    
    sqlite3_close(db);
    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    
    if (argc != 2) {
        fprintf(stderr, "Failed to retrieve data row\n");
	return 1;
    }

    printf("word='%s' value=%s\n", argv[0], argv[1]);
    return 0;
}
