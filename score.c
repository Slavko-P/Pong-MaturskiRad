#include "types.h"
#include <sqlite3.c>
#include <sqlite3.h>

sqlite3 *db;
char *zErrMsg;
int rc;
char *sql;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		SDL_Log("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	return 0;
}

int sql3_connect_database() {
	
	if (sqlite3_open("test.db", &db)) {
		SDL_ShowSimpleMessageBox(NULL, "Error", sqlite3_errmsg(db), NULL);
		return(-1);
	}
	else {
		SDL_Log("Opened database successfully");
	}

	/* Create SQL statement */
	sql = "CREATE TABLE IF NOT EXISTS HIGHSCORE("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"MINUTES        REAL	NOT NULL," \
		"SECONDS		REAL	NOT NULL);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		SDL_Log("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		SDL_Log("Table created successfully\n");
	}

	sqlite3_close(db);
	return 1;
}

void sql3_insert(int ID, char name[], float minutes, float seconds) {
	snprintf(sql, 100, "INSERT INTO HIGHSCORE (ID,NAME,MINUTES,SECONDS) VALUES (%d, '%s', %f, %f);", ID, name, minutes, seconds);
	
	/*rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		SDL_Log("SQL error: %s", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		SDL_Log("Records created successfully");
	}
	sqlite3_close(db);*/
}