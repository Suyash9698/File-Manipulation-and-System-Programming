#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<iostream>
//this one unistd is for write
#include<unistd.h>
#include<sys/stat.h>
#include <iomanip>
using namespace std;
off_t min(off_t buffer_size,off_t input_filesize){
    off_t mini=buffer_size;
    if(input_filesize<=buffer_size){
        mini=input_filesize;
    }
    return mini;
}
int main(int argc,char* argv[]){
    if(argc<2){
        cout<<"Insufficient Number Of Arguments"<<endl;
        exit(1);
    }
   int directory=mkdir("Assignment1_1",0700);
    string outputFile="1_" + string(argv[1]);
    string outputFullPath = "Assignment1_1/" + outputFile;
    creat(outputFullPath.c_str(), 0600);
    int fd1=open(argv[1],O_RDONLY);
    if(fd1==-1){
        std::cout<<"Input File Not Found"<<endl;
        exit(1);
    }
    int fd2=open(outputFullPath.c_str(),O_WRONLY);
    if(fd2==-1){
        std::cout<<"Output File Creation Error"<<endl;
        exit(1);
    }
    //1 KB
    char buffer[8192];
    struct stat file;
    stat(argv[1],&file);
    lseek(fd1,0,SEEK_SET);
    lseek(fd2,0,SEEK_SET);
    off_t remaining=file.st_size;
     off_t mini=min(sizeof(buffer),remaining);
    off_t sum=0;
    bool flag=false;
    for(off_t i=min(remaining,sizeof(buffer));;i+=mini){
        lseek(fd1,-i,SEEK_END);
        if(read(fd1,buffer,mini)<=0){
            break;
        }
        off_t k=0;
        off_t l=mini-1;
        while(k<l){
            off_t temp=buffer[k];
            buffer[k]=buffer[l];
            buffer[l]=temp;
            k+=1;
            l-=1;
        }
        write(fd2,buffer,mini);
        sum+=mini;
        off_t  percentage=(((sum*1.0))*100)/file.st_size;
        cout<<percentage<<"%\r";
        remaining=remaining-mini;
        mini=min(mini,remaining);
    }
    cout<<endl;
    close(fd1);
    close(fd2);

}