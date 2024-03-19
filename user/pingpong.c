#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int p1[2] , p2[2] ; 
    char buf[1] ; 
    int childpid , parentpid ; 
    pipe(p1) , pipe(p2) ; 
    int pid = fork() ; 
    if(pid == 0){
        close(p1[1]); // p1 read only
        close(p2[0]); // p2 write only
        childpid = getpid() ; 
        read(p1[0] , buf , 1) ; 
        fprintf(1, "%d: received ping\n", childpid);
        write(p2[1], "x", 1);
        close(p1[0]) , close(p2[1]) ; 
        exit(0) ; 
    }
    else {
        close(p1[0]); // p1 write only
        close(p2[1]); // p2 read only
        parentpid = getpid() ; 
        write(p1[1] , "x" , 1) ; 
        read(p2[0], buf, 1); 
        fprintf(1, "%d: received pong\n", parentpid);
        close(p1[1]); close(p2[0]);
        exit(0) ; 
    }
    exit(0) ; 
}