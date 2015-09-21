#ifndef KING_REDIS_H
#define KING_REDIS_H
#include <string>
#include <hiredis.h>
#include <cstdarg>

class KingRedis {
    public:
        const char *kr_serverIp;
        int kr_port;
        const char *kr_password;

        KingRedis(const char *_ip,int _port,const char *_passwd="");
        //析构函数
        ~KingRedis();
        bool connect();
        bool execCommand(const char *cmd,va_list ap);

        bool execCommand(const char *cmd,...);
        std::string getBuffer();
        void freeReply();
    private:
        redisContext *kr_link=NULL;
        redisReply *kr_reply=NULL;
        std::string kr_buffer;
        int kr_retCode;


        void _convertReply();
};
#endif // KING_REDIS_H
