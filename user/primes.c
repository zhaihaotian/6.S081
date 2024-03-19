#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void create_child_process();

int main(){
    int p[2] ; 
    pipe(p) ; 
    int pid = fork() ; 
    if(pid != 0){
        close(p[0]) ; 
        for(int i = 2 ; i <= 35 ; i++){
            write(p[1] , &i , sizeof(int)) ; 
        }
        close(p[1]) ; 
        wait(0) ; 
    } else {
        create_child_process(p) ; 
    }
    exit(0) ; 
}

void create_child_process(int p[]){
    int x , y ; 
    int child_p[2] ; 
    close(p[1]) ; 
    if(read(p[0] , &x , sizeof(int))){
        fprintf(1 , "prime %d\n" , x) ; 
        pipe(child_p) ; 
        if(fork() != 0){
            close(child_p[0]) ; 
            while(read(p[0] , &y , sizeof(int))){
                if (y % x != 0)
                    write(child_p[1] , &y , sizeof(int)) ; 
            }
            close(p[0]) ; 
            close(child_p[1]) ; 
            wait(0) ; 
            exit(0); 
        }
        create_child_process(child_p) ; 
        exit(0) ; 
    }
}