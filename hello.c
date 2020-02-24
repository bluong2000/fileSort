#include <stdio.h>
#include <sys/types.h>
#include <dirent.h> 
#include <libgen.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h> 
//#include <unistd.h>
#include <errno.h>

struct node{
    int length;
    char *str;
    struct node *next;

};

//takes in file using command line
//read all tokens and determines if data is integers or strings
//then sort it
int strcmp(const char *x, const char *y);
void createNode(struct node*  head, void* string, int arrSize);

int main (int argc,  char *argv[]){

    if(argc!= 2){
        printf("enter a single file name");
        exit(EXIT_FAILURE);
    
    }
    else{

	struct node *head;
	head =  NULL;	
//	struct new node hd = NULL;
 //       struct node* head = &hd;
        long length;
        int count = 0;
        printf("hello\n");
        int i = strcmp("apples", "apple");
        printf("%d\n", i);
//      char *fileName = 
        int fd1 = open( argv[1], O_RDONLY);
        off_t fsize = lseek(fd1, 0, SEEK_END);
        close(fd1);
				
        int fd2 = open(argv[1], O_RDONLY);
        void *buff[fsize];
        void *tempArr = malloc(fsize * sizeof(char)); // load buffer data into here until comma or whitespace ------ check if malloc worked
        int tac = 0; //temporary counter
        for( count; read(fd2, &buff[count], 1) > 0; count++){  //reads buffer char by char
                if(isspace(buff[count]) != 0){
                
                    if (tac == 0){
                        continue;
                   } else {
                      	createNode(head, tempArr[0], tac);
                        //createNode
                        tac = 0;
                    }
                } else if ( buff[count] == ','){
                
                     if (tac == 0)
                        continue;
                     else {
     			createNode(head, tempArr[0], tac);

                        //createNode
                        tac = 0;
                     }
                }
                else {
                
                    tempArr[tac] = buff[count];
                    tac++;
                }
                
                printf("%c\n" ,  buff[count]);  
                    
        }
        
        free(tempArr);

    //  for (int i = 0; i<)
        printf("%s\t" , argv[1]);
        printf("%d\t" , fsize);
        printf("%d\t", count);
        return 0;
    }
    

}


int strcmp ( const char *x, const char *y){
    while( *x && *x == *y){
        x++;
        y++;
    }
    return (int)(unsigned char)(*x) - (int)(unsigned char)(*y);

}

int intcmp (int x, int y ){
    int result = x - y;
    if (result <= 0 )
        return x;
    if (result > 0 )
        return y;

}
 
void createNode(struct node*  head, void* string, int arrSize){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->str[arrSize];
    newNode->str = string;
    newNode->next = (head);
    *head = newNode;
    
}




