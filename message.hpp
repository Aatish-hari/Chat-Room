#include<iostream>
#include<string>
#include<string.h>
#ifndef MESSAGE_HPP
#define MESSAGE_HPP
using namespace std;

class Message{
    public:
    Message():bodylength(0){}
    enum {maxbyte = 512};
    enum{header = 4};
    
    Message(string message){
        bodylength = newbodylength(message.size());
        encodeheader();
        memcpy(data+header , message.c_str() , bodylength);
    }

    size_t newbodylength(size_t newlength){
            if(newlength>maxbyte){
            return maxbyte;                                          //checking body length
            }
            return newlength;
        }

        string getdata(){
            int length = header + bodylength;
            string result(data , length);                           //returns full full message including header ex:-0005hello;
            return result;
        }

        string getbody(){
            string datastr = getdata();
            string result = datastr.substr(header , bodylength);      //returns only body ex:-hello;
            return result;
        }

    void encodeheader(){
        char newheader[header+1] = "";
        sprintf(newheader , "%4f" , bodylength);
        memcpy(data , newheader , header);
    }

    bool decodeheader(){
        char newheader[header+1] = "";
        strncpy(newheader , data , header);
        newheader[header] = '\0';
        int headervalue = atoi(newheader);
        if(headervalue > maxbyte){
            bodylength = 0;
            return false;
        }
        bodylength = headervalue;
        return true;
    }

    private:
    char data[header + maxbyte];
    size_t bodylength;
};

#endif
