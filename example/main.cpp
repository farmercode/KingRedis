#include <cstring>
#include <iostream>
#include <hiredis.h>
#include <string>

#include "KingRedis.h"

using namespace std;

struct student{
    char name[15];
    int age;
    char sex[6];
};

int main()
{
    cout << "This is a redis test program!" << endl;
    const char *ip = "localhost";
    int port = 6379;

    string buffer;
    KingRedis *kr= new KingRedis(ip,port,"123456");
    if(!kr->connect()){
        return 1;
    }
    student s1 = {0};
    strcpy(s1.name,"王长春");
    s1.age = 25;
    strcpy(s1.sex,"男");

    kr->execCommand("HMSET s1 name %s age %d sex %s",s1.name,s1.age,s1.sex);
    cout << "hmset result:" << kr->getBuffer() << endl;

    kr->execCommand("HGETALL s1");

    cout << "HGETALL:" << kr->getBuffer() << endl;
    return 0;
}
