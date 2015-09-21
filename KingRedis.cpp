#include <cstring>
#include <iostream>
#include <stdio.h>

#include "KingRedis.h"

KingRedis::KingRedis(const char *_ip,int _port,const char *_passwd){
    kr_serverIp = _ip;
    kr_port = _port;
    kr_password = _passwd;
}


KingRedis::~KingRedis(){
    freeReply();
    redisFree(kr_link);
}

std::string KingRedis::getBuffer(){
    return kr_buffer;
}

bool KingRedis::connect(){
    kr_link = redisConnect(kr_serverIp,kr_port);
    if(kr_link->err){
        std::cout << "connect error:" << kr_link->errstr << std::endl;
        return false;
    }

    if(strlen(kr_password)){
        if(!execCommand("auth %s",kr_password)){
            std::cout << kr_buffer << std::endl;
            return false;
        }
    }
    return true;
}

void KingRedis::freeReply(){
    if(kr_reply == NULL) return;
    freeReplyObject(kr_reply);
    return;
}

bool KingRedis::execCommand(const char *cmd,va_list ap){
    freeReply();
    kr_reply = (redisReply *)redisvCommand(kr_link,cmd,ap);

    _convertReply();
    if(kr_reply->type == REDIS_REPLY_ERROR) return false;
    return true;
}

bool KingRedis::execCommand(const char *cmd,...){
    bool res;
    va_list ap;
    va_start(ap,cmd);
    res = execCommand(cmd,ap);
    va_end(ap);
    return res;
}

void KingRedis::_convertReply(){
    if(kr_reply == NULL)
        return;
    kr_buffer.clear();
    char buff[32]={0};

    switch(kr_reply->type){
        case REDIS_REPLY_STRING://1
        case REDIS_REPLY_ERROR: //6
        case REDIS_REPLY_STATUS://5
            kr_buffer.append(kr_reply->str);
           break;
        //2
        case REDIS_REPLY_ARRAY:
            if((int)kr_reply->elements>0){
                for(int i=0;i<(int)kr_reply->elements;i++){
                    kr_buffer.append(kr_reply->element[i]->str);
                    kr_buffer.append(" ");
                }
            }
            break;
        //3
        case REDIS_REPLY_INTEGER:
            sprintf(buff,"%lld",kr_reply->integer);
            kr_buffer.append(buff);
            break;
        case REDIS_REPLY_NIL://4
        default:
            break;
    }
    return ;
}
