#ifndef ___SERVERTYPES_HEADER___
#define ___SERVERTYPES_HEADER___

#define SERVER_STRING "Server: sure webserver/0.1.0\r\n"
#define CONFIG_FILE "config.cfg"
#define RESOPONE_OK "HTTP/1.0 200 OK\r\n"
#define FILE_NOT_FOUND "HTTP/1.0 404 NOT FOUND\r\n"
#define UNKNOW_METHOD "HTTP/1.0 501 Method Not Implemented\r\n"
#define BAD_REQUEST "HTTP/1.0 400 BAD REQUEST\r\n"
#define SERVER_ERROR "HTTP/1.0 500 Internal Server Error\r\n"
#define WEB_TEXT "Content-type: text/html\r\n"

#define bool int
#define true 1
#define false !(true)

#define MAXLINE 260
#define MAX_PATH 260
#define MAX_BUF 1024



#endif
