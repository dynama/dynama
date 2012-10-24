#include<stdio.h>
#include<sqlite3.h>
#include<stdbool.h>

bool setup_database(char* databaseName){
	sqlite3 *db;
	FILE *file;

	if(file = fopen(databaseName, "r"))
	{
		fclose(file);
		return true;

	}
	else
	{
		sqlite3_open(databaseName, &db);
		printf("Database file just created, needs to be set up.\n");
		return true;
	}
}

