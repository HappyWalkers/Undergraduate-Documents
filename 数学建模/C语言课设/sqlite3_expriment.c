//sqlite3_experiment.c 

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "meal_tele_fun.h"

int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int exp()
{
	sqlite3 *db;
	int rc;
	char *sql;
	char *zErrMsg;
	
	rc = sqlite3_open("meal_tele.db3",&db);//rc使返回值，用来报错 
	if(rc)
    {
        fprintf(stderr,"Can not open database:%s\n",sqlite3_errmsg(db));
        return -1;
    }
    else
    {
    	fprintf(stdout,"database open successfully.\n");
	}
	
	sql = "insert into mystruct (number,name,tele,peo_num,time,like) values(0,\'test\',0,0,\'test\',\'test\');";//sql语句 ,引号转义 
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK )
	{
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   	}
	else
	{
      fprintf(stdout, "Records created successfully\n");
   	}
	
	Info std[101];
	read(std);
	print_all(std);
	char sqlstr[100]={0};
	for(int i=1;i<=100;i++)
	{
		if(std[i].tele==0 && std[i].peo_num==0 && std[i].number==0)//遇到尚未存入信息的项就截止 
    		{
    			break;
    		}
    	memset(sqlstr,0,100);
    	sprintf(
    	sqlstr,
		"insert into mystruct (number,name,tele,peo_num,time,like) values(%d,\'%s\',%ld,%d,\'%s\',\'%s\');",
    	std[i].number,
    	std[i].name,
    	std[i].tele,
     	std[i].peo_num,
    	std[i].time,
    	std[i].like);
	
    	puts(sqlstr);
	
    	sql = sqlstr;
    	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
        if( rc != SQLITE_OK )
     	{
           fprintf(stderr, "SQL error: %s\n", zErrMsg);
           sqlite3_free(zErrMsg);
     	}
    	else
     	{
           fprintf(stdout, "Records created successfully\n");
     	}
	}
	
 	sql = "select * from mystruct"; 
   	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
	{
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   	}
	else
	{
      fprintf(stdout, "Records created successfully\n");
   	}
   	
   	char **dbResult;   
   	int nRow, nColumn;
   	rc = sqlite3_get_table( db, sql, &dbResult, &nRow, &nColumn, &zErrMsg );
   	if( rc != SQLITE_OK )
	{
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   	}
	else
	{
    	int i,j;
    	for(i=0;i<nColumn;i++)
    	  	printf("%s\t\t",dbResult[i]);
    	putchar('\n');
    	
    	for(i=0;i<nRow;i++){
    		for(j=0;j<nColumn;j++){
    			printf("%s\t\t",dbResult[nColumn+i*nColumn+j]);
			}
			putchar('\n');
		}
    	
      
   	}
   	
    sqlite3_close(db);
}

