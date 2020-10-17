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
    void *str;
    struct node *next;
    struct node *prev;
};
 
int BUFFER_TYPE_A0 = 0;
 
 
 
//takes in file using command line
//read all tokens and determines if data is integers or strings
//then sort it
int strcmp(const char *x, const char *y);
void createNode(struct node**  head, char* string, int arrSize);
int comparator(void*b1, void*b2);
int insertionSort(void* toSort, int(*comparator)(void*,void*));
int quickSort(void* tosort, int(*comparator)(void*, void*));
int partition(void **array, int low, int high);
void qSort(void **arr, int low, int high);
void swapArr(void** arg1, void** arg2);
void ** list( void* head);
 
 
int main (int argc,  char *argv[]){
 
 
    if (argc < 3 || argc > 3) {
        if ((argc - 1) == 1)
            fprintf(stderr, "Fatal Error: expected two arguments, had one\n");
        else if ((argc -1) == 0)
            fprintf(stderr, "Fatal Error: expected two arguments, had none\n");
        else 
            fprintf(stderr, "Fatal Error: expected two arguments, argument list too long\n");
        exit(-1);
    }
 
    char* quick = "-q";
    char* insert = "-i";
 
    if (comparator((void*) argv[1], (void*) quick) != 0 && comparator((void*) argv[1], (void*) insert) != 0) {
        fprintf(stderr, "Fatal Error: %s is an invalid sorting flag, use -i or -q\n", argv[1]);
        exit(-1);
    }
 
    char* userSort = argv[1];
 
    struct node *hd;
    hd =  NULL; 
    struct node *prv;
    prv = NULL;
 
    struct node ** tail = &prv;
    struct node ** head = &hd;
    int count = 0;
    //printf("hello\n");
        int fd1 = open( argv[2], O_RDONLY);
        if (fd1 == -1) {
            fprintf(stderr, "Fatal Error: file %s does not exist\n", argv[2]);
            exit(-1);
        }
 
        off_t fsize = lseek(fd1, 0, SEEK_END);
        close(fd1);
 
        if (fsize == 0)
            printf("Warning: your text file is empty\n");
                    
        int fd2 = open(argv[2], O_RDONLY);
        char *buff = malloc(fsize*sizeof(char) + 1);
        memset(buff, '\0', fsize + 1);
        char *tempArr = malloc(fsize * sizeof(char)); // load buffer data into here until comma or whitespace ------ check if malloc worked
        int readIn = 0; 
        int status = 0;
        int tac = 0; //temporary counter
        do{  //reads buffer char by char
            status = read(fd2, buff+readIn, fsize - readIn);
            readIn += status;
                
                    
        } while (status > 0 && readIn < fsize); // ( count; read(fd2, &buff[count], 1) > 0; count++)
         close(fd2);
 
    while (buff[count] != '\0') {
        //printf("buff[count] = %c\n", buff[count]);
 
        if ( buff[count] == ','){
                
            createNode(head, tempArr, tac);
            tac = 0;
        }
        else if ( buff[count] == '\n' || buff[count] == '\t') {
 
            count++;
            continue;
        }
        else {   
            tempArr[tac] = buff[count];
            tac++;
        }
 
        count++;
        //printf("count = %d\n", count);
        
    }
 
    if (tac != 0) 
        createNode(head, tempArr, tac);
 
    struct node* curr = hd;
/*
    while ( curr != NULL ){             // remove
        printf("%s\n", curr->str);
        curr = curr->next;
    }
*/ 
    
    //printf("\n\n%s\n\n", buff); 
    free(tempArr);
    free(buff);
 
    //pritnf("type of vars = %d", BUFFER_TYPE_A0);
 
 
 
//    printf("-------------------------------------------\n");  // comment out
 
    if (strcmp(userSort, "-i") == 0) {
        int work = insertionSort((void*)hd, comparator);
        int j = 0;
 
        for (j; j < work; j++)
            hd = hd->prev;
 
 
        curr = hd;
 
    while ( curr != NULL ){
 
        char* tempstr = (char*)curr->str;
 
        if(BUFFER_TYPE_A0 == 1 && tempstr[0] == '\0')
            printf("0\n");
        else
            printf("%s\n", curr->str);
        curr = curr->next;
	
	
	
        }


 
    }
    else {
        quickSort((void*)hd, comparator);
    }
/*
 struct node *temp = NULL;
while((temp = hd)!= NULL){
	hd = hd-> next;
	free(temp->str);
	free(temp);


}
 */
    return 0;
 
    
 
}
 
int comparator(void*b1, void*b2){
 
    char* c1 = (char*)b1;
    char* c2 = (char*)b2;
 
    if(isdigit(c1[0]) == 1 || c1[0] == '-'){
    //if(BUFFER_TYPE_A0 == 1){
 
        int d1 = atoi(c1);
        int d2 = atoi(c2);
        
        return d1 - d2;
 
    }   
 
 
    return strcmp(c1,c2);
 
}
 
int strcmp ( const char *x, const char *y){
    while( *x && *x == *y){
        x++;
        y++;
    }
    return (int)(unsigned char)(*x) - (int)(unsigned char)(*y);
 
}
 
 
void createNode(struct node**  head, char  *string, int arrSize){
 
    int c = 0;
    int newSize = 0;
    char newstring[arrSize];
    int index = 0;
 
    //memset(string, )
 
    for (c; c < arrSize; c++) {
 
      if (string[c] != ' ') {
        newSize++;
        newstring[index] = string[c];
        index++;
 
        if (string[c] == '-' || isdigit(string[c]) == 1) 
            BUFFER_TYPE_A0 = 1;
      }
 
    }
 
    arrSize = newSize;
 
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
 
    char* data = malloc((arrSize * sizeof(char)) + 1);
    
    c = 0;
    for (c; c < arrSize; c++) 
        data[c] = newstring[c];
 
    data[c] = '\0';
 
    newNode->str = (void*)data;
 
    if (*head == NULL) {
        *head = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
        return;
    }
 
    (*head)->prev = newNode;
    newNode->next = *head;
    newNode->prev = NULL;
    *head = newNode;
}
 
int insertionSort(void* toSort, int(*comparator)(void*,void*)){
  
    struct node* head = (struct node*) toSort;
    struct node* hd = (struct node*) toSort;
    struct node* curr = head;
    struct node* nxt = curr;
 
 
    while (curr != NULL && curr->next != NULL) {
 
        nxt = curr->next;
 
        //printf("\n\tcurr-> %s\n", curr->str);
 
        if (comparator(curr->str, nxt->str) >= 0) {
 
            struct node* back = curr->prev;
            struct node* change = nxt;
 
            //printf("\nchange-> %s\n", change->str);
 
            while (back != NULL) {
 
                //printf("\n\t\tback-> %s\t %d\n", back->str, comparator(back->str, nxt->str));
 
                if (comparator(back->str, nxt->str) < 0) 
                    break;
                back = back->prev;
            }
 
            if (back == NULL) {
 
                struct node* temp = head;
                
                curr->next = change->next;
                if (change->next != NULL)
                    (change->next)->prev = curr;
 
                change->prev = NULL;
                change->next = temp;
                temp->prev = change;
                head = head->prev;
 
                nxt = curr;
 
                //printf("\n\t\t\thead is %s\n\n", head->str);
            }
            else {
 
                curr->next = change->next;
                if (change->next != NULL)
                    (change->next)->prev = curr;
                change->prev = back;
                change->next = back->next;
                (back->next)->prev = change;
                back->next = change;
                nxt = curr;
 
            }
            
            continue;
        }
        else {
 
            curr = curr->next;
            continue;
        }
        
    }
 
    int shift = 0;
    int hF = 0;
    curr = head;
    while ( curr != NULL ){
 
        if (curr == hd) 
            hF = 1;
        //printf("\n\t%s\n", curr->str);
        curr = curr->next;
 
        if (hF == 0)
            shift++;
    }
 
    return shift;
    
}
 
 
 
int quickSort(void* toSort, int(*comparator)(void*, void*)){
     struct node *hd = toSort;
    void ** arr = list(toSort);
    int size = 0;
    while(hd!= NULL){
        size++;
        hd= hd->next;
 
    }
    qSort(arr, 0, size-1);
    int x = 0;
        for(x;x<size;x++){
        
            char* val = (char*)arr[x];
            if (BUFFER_TYPE_A0 == 1 && val[0] == '\0')
                printf("0\n");
            else
                printf("%s\n", arr[x] );
    }
	void ** arr2 = arr;


	
	void**temp1;
	
	for((temp1=arr); *temp1; temp1++){
		
		free(*temp1);
	}
	free(arr);
	void**temp2 = arr;

	int i =0;
	int j = 0;

/*	
	for(i; i<(size-1);i++){
		int len = strlen(arr[i]);
		for(j; j<len; j++){
			free(arr[i]);
		}
	}
*/
	free(arr);
//	printf("\n\n\n\n%s",(char*)arr2[0]); 
	return 1;
 
}
 
 
 
 
void ** list( void* head){
 
    struct node *hd = head;
    int lsize = 0;
    while(hd!= NULL){
        hd = hd->next;
        lsize++;  //finding size of linked list
 
    }
    void **arr = malloc(lsize*sizeof(char));
    hd =head;
    int i = 0;
    while(i<lsize){
        
        int strLength = strlen((char*)hd->str);
    //    arr[i] = malloc((strLength*sizeof(char)+1));
            
        printf("str length is: %d\n", strLength);
        arr[i] = (char*)hd->str;
        i++;
        hd = hd->next;
 
    }
 
    return arr;
 
}
void swapArr(void** arg1, void** arg2){
    void* str = *arg1;
    *arg1 = *arg2;
    *arg2 = str;
}
 
 
void qSort(void **arr, int low, int high){
 
    int x = 0;
    for(x; x < high; x++ ){
//        printf("Array output: %s\n" , arr[x]);
 
 
    }
//    printf("\n\n");
        if(low< high){
    
            int pi = partition(arr, low, high);    
            qSort(arr, pi+1, high);
            qSort(arr, low, pi-1);
        
        }
    
 
}
int partition(void **array, int low, int high){
    int i =high +1;
    int j = high;
    for(j ; j >= low; j--){
 
        if(comparator(array[j], array[low])>0){
            i--;
            swapArr(&array[i], &array[j]);
 
        }
 
    }
    swapArr(&array[i-1], &array[low]);
    return i - 1;
}
 
 
 
 



