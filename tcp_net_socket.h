#ifndef _TCP_NET_SOCKET_H
#define _TCP_NET_SOCKET_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "mysql_server/mysql.h"
extern int tcp_init(const char* ip,int port);
extern int tcp_accept(int sdf);
extern int tcp_connect(const char* ip,int port);
extern void signalhandler(void);
extern void config_file_testing (char *program_filename);//检查配置文件是否存在
extern void write_config_file (char *role);//写入配置文件
extern void init_daemon(void);//守护进程初始化函数
int mysql_server (char *argv);//mysql数据库
#endif