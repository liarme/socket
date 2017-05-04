/*CREATE TABLE student (student_no varchar(12) NOT NULL PRIMARY KEY,student_name varchar(12) NOT NULL);*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "errmsg.h"
#include "mysqld_error.h"


MYSQL conn;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

void connection(const char* host, const char* user, const char* password, const char* database) {
	mysql_init(&conn); // 注意取地址符&

	if (mysql_real_connect(&conn, host, user, password, database, 0, NULL, 0)) {
		printf("Connection success!\n");
	} else {
		fprintf(stderr, "Connection failed!\n");
		if (mysql_errno(&conn)) {
			fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
		}
		exit(EXIT_FAILURE);
	}
}

void display_row() {
	unsigned int field_count = mysql_field_count(&conn);
	int i = 0;
	while (i < field_count) {
		if (sqlrow[i]) printf("%s ", sqlrow[i]);
		else printf("NULL");
		i++;
	}
	printf("\n");
}

void display_header() {
	MYSQL_FIELD *field_ptr;
	printf("Column details:\n");
	while ((field_ptr = mysql_fetch_field(res_ptr)) != NULL) {
		printf("\t Name: %s\n", field_ptr->name);	
		printf("\t Table: %s\n", field_ptr->table);	
		printf("\t Type: ");
		if (IS_NUM(field_ptr->type)) {
			printf("Numeric field\n");	
		} else {
			switch(field_ptr->type) {
				case FIELD_TYPE_VAR_STRING:
					printf("VARCHAR\n");
					break;
				case FIELD_TYPE_LONG:
					printf("LONG");
					break;
				default:
					printf("Type is %d, check in msyql_com.h\n", field_ptr->type);
			}	
		}
		printf("\t Max width %ld\n", field_ptr->length);
		if (field_ptr->flags & AUTO_INCREMENT_FLAG)
			printf("\t Auto increments\n");
		printf("\n");
	}
}

int main (int argc, char *argv[]) {

	connection("localhost", "root", "shuang", "shuangde");
	int res = mysql_query(&conn, "SELECT * from student");
	if (res) {
		fprintf(stderr, "SELECT error: %s\n", mysql_error(&conn));
	} else {
		res_ptr = mysql_use_result(&conn);
		if (res_ptr) {
			int first = 1;
			while ((sqlrow = mysql_fetch_row(res_ptr))) {
				if (first) {
					display_header();
					first = 0;	
				}
				display_row();
			}
			if (mysql_errno(&conn)) {
				fprintf(stderr, "Retrive error: %s\n", mysql_error(&conn));
			}
			mysql_free_result(res_ptr);
		} 
	}
	mysql_close(&conn);
	exit(EXIT_SUCCESS);
}