// 相关函数：

// 这是在成功调用mysql_query之后使用此函数，这个函数将立刻保存在客户端中返回的所有数据。它返回一个指向结果集结构的指针，如果失败返回NULL
MYSQL_RES *mysql_store_result(MYSQL *connection);

// 这个函数接受由mysql_store_result返回的结果结构集，并返回结构集中的行数
my_ulonglong mysql_num_rows(MYSQL_RES *result);


// 这个函数从使用mysql_store_result得到的结果结构中提取一行，并把它放到一个行结构中。当数据用完或发生错误时返回NULL.
MYSQL_ROW mysql_fetch_row(MYSQL_RES *resutl);


// 这个函数用来在结果集中跳转，设置将会被下一个mysql_fetch_row操作返回的行。参数offset是一个行号，它必须是在0～结果总行数-1的范围内。传递
// 0将会导致下一个mysql_fetch_row调用返回结果集中的第一行。
void mysql_data_seek(MYSQL_RES *result, my_ulonglong offset);


// 返回一个偏移值，它用来表示结果集中的当前位置。它不是行号，不能把它用于mysql_data_seek
MYSQL_ROW_OFFSET mysql_row_tell(MYSQL_RES *result);


// 这将在结果集中移动当前的位置，并返回之前的位置
MYSQL_ROW_OFFSET mysql_row_seek(MYSQL_RES *result, MYSQL_ROW_OFFSET offset);


// 完成所有对数据的操作后，必须总是调用这个来善后处理
void mysql_free_result(MYSQL_RES *result);

//编译
//centos 7 mariadb-5.5.52-1.el7.x86_64
gcc -I/usr/include/mysql mysql.c -lmysqlclient -L/usr/lib64/mysql -o connect1