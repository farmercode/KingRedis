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

        /**
         *连接redis服务器
         */
        bool connect();

        /**
         *执行redis命令
         */
        bool execCommand(const char *cmd,va_list ap);
        /**
         *执行redis命令
         */
        bool execCommand(const char *cmd,...);

        /**
         *获得redis返回结果
         */
        std::string getBuffer();

        /**
         *释放Reply
         */
        void freeReply();
    private:
        redisContext *kr_link=NULL;
        redisReply *kr_reply=NULL;
        std::string kr_buffer;
        int kr_retCode;

        /**
         *将返回的Reoly转化为string
         */
        void _convertReply();
};
#endif // KING_REDIS_H
