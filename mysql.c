#include "tcp_net_socket.h"

int mysql_server (char *argv)
{  
		MYSQL *conn_ptr;
		MYSQL_RES *res;
		MYSQL_ROW row;
		char *query_a = " where student_name='",*query_b = "'",query[100] = {"select * from student"};
		int flag,t;
		conn_ptr=mysql_init(NULL); //连接初始化  
		if(!conn_ptr){  
				fprintf(stderr, "mysql_init failed\n");  
				return EXIT_FAILURE;  
		}  
  
		conn_ptr = mysql_real_connect(conn_ptr, "localhost", "yangguo","accp132accp","oktest", 0, NULL, 0); //建立实际连接  
		//参数分别为：初始化的连接句柄指针，主机名（或者IP），用户名，密码，数据库名，0，NULL，0）后面三个参数在默认安装mysql>的情况下不用改  
		if(conn_ptr){  
			printf("Connection success\n");  
			return 0;
		}  
		strcat(query,query_a);
		strcat(query,argv);
		strcat(query,query_b);
		flag = mysql_real_query(conn_ptr, query, (unsigned int)strlen(query));
		if(flag) {
			printf("Query failed!\n");
			return 0;
		}
		/*mysql_store_result讲全部的查询结果读取到客户端*/
		res = mysql_store_result(conn_ptr);
		/*mysql_fetch_row检索结果集的下一行*/
		while(row = mysql_fetch_row(res)) {
		/*mysql_num_fields返回结果集中的字段数目*/
			for(t=0; t<mysql_num_fields(res); t++)
			{
				printf("%s\t", row[t]);
			}
			printf("\n");
		}
		mysql_close(conn_ptr); //关闭连接  
		return EXIT_SUCCESS;  
}  