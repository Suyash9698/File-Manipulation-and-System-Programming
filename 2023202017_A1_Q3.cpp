#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<iostream>
//this one unistd is for write
#include<unistd.h>
#include<sys/stat.h>
#include <iomanip>
#include <dirent.h>
using namespace std;
//function to find minimum
off_t min(off_t buffer_size,off_t input_filesize){
    off_t mini=buffer_size;
    if(input_filesize<=buffer_size){
        mini=input_filesize;
    }
    return mini;
}
//function to unset a particular bit in a number
mode_t unset(mode_t num,int k){
    mode_t here= ((~(1<<k)) & num); 
    return here;
}
//function to check permissions of user
void permissionUser(struct stat var,string s,char* argv){
    if((var.st_mode & 0400)!=0){
        cout<<"User has read permissions on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"User has read permissions on "+ s +": No"<<endl;
    }
    if((var.st_mode & 0200)!=0){
        cout<<"User has write permission on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"User has write permission on "+ s +": No"<<endl;
    }
    if((var.st_mode & 0100)!=0){
        cout<<"User has execute permission on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"User has execute permission on "+ s +": No"<<endl;
    }
}
//function to check permissions of group
void permissionGroup(struct stat var,string s,char* argv){
 if((var.st_mode & 0040)!=0){
        cout<<"Group has read permissions on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"Group has read permissions on "+ s +": No"<<endl;
    }
    if((var.st_mode & 0020)!=0){
        cout<<"Group has write permission on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"Group has write permission on "+ s +": No"<<endl;
    }
    if((var.st_mode & 0010)!=0){
        cout<<"Group has execute permission on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"Group has execute permission on "+ s +": No"<<endl;
    }     
}
//function to check permissions of others
void permissionOther(struct stat var,string s,char* argv){
     if((var.st_mode & 0004)!=0){
        cout<<"Other has read permissions on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"Other has read permissions on "+ s +": No"<<endl;
    }
    if((var.st_mode & 0002)!=0){
        cout<<"Other has write permission on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"Other has write permission on "+ s +": No"<<endl;
    }
    if((var.st_mode & 0001)!=0){
        cout<<"Other has execute permission on "+ s +": Yes"<<endl;
    }
    else{
        cout<<"Other has execute permission on "+ s +": No"<<endl;
    }
}


int main(int argc,char* argv[]){
    if(argc<4){
        cout<<"Insufficient Number Of Arguments"<<endl;
        exit(1);
    }
    //checking existence of directory
    struct stat check;
    if(stat(argv[3],&check)==0){
        cout<<"Directory is created: Yes"<<endl;
    }
    else{
        cout<<"Directory is created: No"<<endl;
    }
    int fd1=open(argv[1],O_RDONLY);
    if(fd1==-1){
        std::cout<<"New File Not Found"<<endl;
        exit(1);
    }
    int fd2=open(argv[2],O_RDONLY);
    if(fd2==-1){
        std::cout<<"Old File Not Found"<<endl;
        exit(1);
    }
    struct stat newFile;
    stat(argv[1],&newFile);
    struct stat oldFile;
    stat(argv[2],&oldFile);    


    struct stat file1;
    struct stat file2;
    stat(argv[1],&file1);
    stat(argv[2],&file2);
    char buffer1[8192];
    char buffer2[8192];
    off_t remaining=file1.st_size;
    off_t mini=min(remaining,sizeof(buffer1));
    off_t i=0;
    off_t j=mini;
    bool flag=true;
    while(true){
        lseek(fd1,0,SEEK_CUR);
        lseek(fd2,-j,SEEK_END);
        off_t res1=read(fd1,buffer1,mini);
        off_t res2=read(fd2,buffer2,mini);
        if(res1==0 && res2==0){
            break;
        }
        if(res1==0 || res2==0){
            flag=false;
            break;
        }
        //reversing buffer2 content
        off_t fp=0;
        off_t lp=mini-1;
        while(fp<lp){
            off_t temp=buffer2[fp];
            buffer2[fp]=buffer2[lp];
            buffer2[lp]=temp;
            fp+=1;
            lp-=1;
        }
        for(off_t p=0;p<mini;p++){
            if(buffer1[p]!=buffer2[p]){
                flag=false;
                break;
            }

        }
        if(flag==false){
            cout<<"Whether file contents are reversed in newfile: No"<<endl;
            break;
        }
        remaining=remaining-mini;
        mini=min(mini,remaining);
        i+=mini;
        j+=mini;
    }
    if(flag==true){
        cout<<"Whether file contents are reversed in newfile: Yes"<<endl;
    }
    //checking the permissions of newfile
    permissionUser(newFile,"newfile",argv[1]);
    permissionGroup(newFile,"newfile",argv[1]);
    permissionOther(newFile,"newfile",argv[1]);
    //checking the permissions of oldfile
    permissionUser(oldFile,"oldfile",argv[2]);
    permissionGroup(oldFile,"oldfile",argv[2]);
    permissionOther(oldFile,"oldfile",argv[2]);
    //checking the permissions of directory
    permissionUser(check,"directory",argv[3]);
    permissionGroup(check,"directory",argv[3]);
    permissionOther(check,"directory",argv[3]);
    
    cout<<endl;
    close(fd1);
    close(fd2);

}