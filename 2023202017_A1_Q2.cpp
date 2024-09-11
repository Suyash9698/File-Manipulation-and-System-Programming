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
    if(argc<4){
        cout<<"Insufficient number of arguments"<<endl;
        exit(1);
    }
    size_t startIndex=stoll(argv[2]);
    size_t endIndex=stoll(argv[3]);
   int directory=mkdir("Assignment1_2",S_IRWXU | S_IROTH | S_IXOTH);
    string outputFile="2_" + string(argv[1]);
    string outputFullPath = "Assignment1_2/" + outputFile;
    creat(outputFullPath.c_str(), S_IRUSR | S_IWUSR);
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
    if(startIndex<0 || endIndex>=file.st_size){
        cout<<"Invalid indexing provided"<<endl;
        exit(1);
    }
    off_t remaining=file.st_size;
    off_t mini=min(sizeof(buffer),remaining);
    off_t sum=0;
    remaining=startIndex-0;
    off_t offset=file.st_size-startIndex-1;
    mini=min(sizeof(buffer),remaining);
    //reverse from index 0 to start
    if(mini>0){
     for(off_t i=mini;;i+=mini){
        lseek(fd1,-i-offset-1,SEEK_END);
        if(read(fd1,buffer,mini)<=0){
            break;
        }
        off_t k=0;
        off_t l=mini-1;
        while(k<l){
            off_t temp=buffer[k];
            buffer[k]=buffer[l];
            buffer[l]=temp;
            k++;
            l--;
        }
        write(fd2,buffer,mini);
        sum+=mini;
        off_t  percentage=(((sum*1.0))*100)/file.st_size;
        cout<<percentage<<"%\r";
        remaining=remaining-mini;
        mini=min(mini,remaining);
     }
    }
    lseek(fd1,-offset-1,SEEK_END);
     remaining=endIndex-startIndex+1;
     mini=min(sizeof(buffer),remaining);
     //no reverse from start to end
     if(mini>0){
     for(off_t i=startIndex;;i+=mini){
        lseek(fd1,0,SEEK_CUR);
        if(read(fd1,buffer,mini)<=0){
            break;
        }
        off_t k=0;
        off_t l=mini-1;
        write(fd2,buffer,mini);
        sum+=mini;
        off_t  percentage=(((sum*1.0))*100)/file.st_size;
        cout<<percentage<<"%\r";
        remaining=remaining-mini;
        mini=min(mini,remaining);
     }
     }

     //reverse from ending to filesize
     remaining=file.st_size-(endIndex+1);
     mini=min(sizeof(buffer),remaining);
     if(mini>0){
     for(off_t i=mini;;i+=mini){
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
            k++;
            l--;
        }
        write(fd2,buffer,mini);
        sum+=mini;
        off_t  percentage=(((sum*1.0))*100)/file.st_size;
        cout<<percentage<<"%\r";
        remaining=remaining-mini;
        mini=min(mini,remaining);
     }
    }
    cout<<endl;
    lseek(fd2,0,SEEK_SET);
    close(fd1);
    close(fd2);

}