# KingRedis
redis C++客户端，需要hiredis库

example下面有个简单的例子文件：<br>
Linux编译方法：<br>
g++ -Wall -fexceptions -std=c++11 -g -I/usr/local/include/hiredis/ -I/home/king/gitlib/KingRedis ../KingRedis.cpp main.cpp -o redis -lhiredis

