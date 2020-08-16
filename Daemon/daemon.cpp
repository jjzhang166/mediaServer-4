#include<bits/stdc++.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
int main(){
    if(daemon(0,0)==-1){
        puts("error");
        exit(-1);
    }
    while(true){
        sleep(1);
    }
}
