//--------------------------------------Tic Tac Toe ------------------------!
// Create by Abdullah Sheikh ,Huzaifa Shakeel and Raheema Waheed (Fast University Pakistan)
// Project of Operating Systems (OS)
// Run on linux (UBUNTU) Operating System
// Concepts use pthreads ,process ,Named pipes and Semaphores
// !!-------------------------------------- Player 2 (Player or Computer)------------------------------------!!
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>
#include <semaphore.h>
#include <time.h> 

#define MAX_BUF 1024
sem_t s;
char square[10]={'0','1','2','3','4','5','6','7','8','9'};
double playtime=0;        // this variable is used to calculate time of player
double timescore=0;       // this var used to store file value 
char arr[10]="Computer"; //String to get Name of player
char buffer[1024];       //String to get Name of Another player
int choice=0;            //this variable is used to play as a Computer or Player2
int check_w=0;          // this variable check the waiting condition 
int i=0;                // this is for input Player turn 





// ------------------this function (thread t1) for Input turn from player
void * funGetInput(void * arg){

     int check=1;
     char t ;
     while (check)
{
     check=0;
   if(choice==1)
   {
     printf( "Enter value :");
    scanf("%d", &i);

   }
else if(choice==0)
{
  srand(time(NULL));
  int nMax=9;
  int nMin=1;
   i = rand()%(nMax-nMin) + nMin;    
}
    if(i==1 && square[1]=='1')
    {
     t='1';
 square[i]='O';
      board();
    }
  else if(i==2 && square[2] =='2')
    {
     t='2';
 square[i]='O';
      board();
    }
 else if(i==3 && square[3] =='3')
    {
     t='3';
 square[i]='O';
      board();
    }
 else if(i==4 && square[4] =='4')
    {
     t='4';
 square[i]='O';
      board();
    }
 
 else if(i==5 && square[5] =='5')
    {
     t='5';
 square[i]='O';
      board();
    }
 else if(i==6 && square[6]=='6')
    {
     t='6';
     square[i]='O';
      board();
    }
 else if(i==7 && square[7]=='7')
    {
     t='7';
 square[i]='O';
      board();
    }
else if(i==8 && square[8]=='8')
    {
     t='8';
 square[i]='O';
      board();
    }
else if(i==9 && square[9]=='9')
    {
     t='9';
      square[i]='O';
      board();
    }
else
{  
if(choice==1)
   {
    printf("Invalid input! Try Again\n");
}
    check=1;
}
}
               
                check_w=0;
                 return NULL;}

 void ramdomnum()
{
  int nMax=9;
  int nMin=1;
   i = rand()%(nMax-nMin) + nMin;
}       

void waiting()
{
while(check_w==1) // the while run until player takes his/her turn 
{
}

}



// ------------------this function (thread t2) used to calculate time of Player turn 

void * funCalculateTime(void * arg){

   clock_t begin = clock();
    waiting();
  
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   playtime=playtime+time_spent;
    printf("Player2 takes %f seconds \n", time_spent); 
             
                
             return NULL; }


// ------------------this function (thread t3) used to check and store the time score 
void * funCheckAStoreScore(void * arg)
{

   sem_wait(&s);
 if(playtime<timescore)
{
   printf("\n\n    Congrats You Win Game in Minimum time \n");
 
 FILE *fptr;

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen("/home/ns3/OSProject/score.txt","w");

   if(fptr == NULL)
   {
      printf("Error!");   
     // exit(1);             
   }
   fprintf(fptr,"%lf",playtime);
   fclose(fptr);

}

}


int main()
{

  

   printf("Play as \n 1.Player\n 0.Computer\nSelect one\n");
   scanf("%d", &choice);
   

FILE *fptr;

   if ((fptr = fopen("/home/ns3/OSProject/score.txt","r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
      // exit(1);
   }

   fscanf(fptr,"%lf",&timescore);




  FILE *fpt;

   // use appropriate location if you are using MacOS or Linux
   fpt = fopen("/home/ns3/OSProject/score.txt","w");

   if(fpt == NULL)
   {
      printf("Error!");   
     // exit(1);             
   }
   fprintf(fpt,"%lf",timescore);
   fclose(fpt);

  
   fclose(fptr); 


    pthread_t t3; 
   

     int x=1;
    int fd;
      printf( "#####             Tic tac toe         ######\n\n");
      printf( "!!!               Player2                 !!!\n");
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_RDONLY);
    read(fd, buffer, 1024);
   
     close(fd);
     
      if(choice==1)
{
     printf( "Enter Your Name :");
     scanf(" %[^\n]%*c",arr);
}
    fd = open(myfifo, O_WRONLY);
    write(fd,  arr, strlen(arr)+1);
    close(fd);
     printf("Player1: %s", buffer);
     printf("                                Player2: %s\n", arr);
     

  
    while (x==1)
    {

     
      char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
   // char buffer[1024];
    int n;
     fd = open(myfifo, O_RDONLY);
    read(fd, &n, sizeof(n));
     close(fd);

     square[n]='X';
      board();
     int con =CheckWinningCondition();
     if(con==0)
     {
       break;
     }
     else if(con==-1)
{
     printf("\n\n\tMatch Draw\n\n");
     break;

}
      pthread_t t1, t2; 
   // t1 :For takes input from player
   // t2 :To calculate time (Time Taken by player to complete his/her Turn)
   check_w=1;
        
        pthread_create(&t2,NULL,&funCalculateTime,NULL);
        pthread_create(&t1,NULL,&funGetInput,NULL);
         pthread_join(t1,NULL);
        pthread_join(t2,NULL);     
     
  
       fd = open(myfifo, O_WRONLY);
    write(fd,&i, sizeof(i));
    close(fd);
   

    
    int cond =CheckWinningCondition();
     if(cond==0)
     {
        pthread_create(&t3,NULL,&funCheckAStoreScore,NULL);
      
        pthread_join(t3,NULL);
       break;
     }
else if(cond==-1)
{
     printf("\n\n\tMatch Draw\n\n");
     break;

}
}
 

    return 0;
}



void board()
{
   
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");
  printf("Minimum Time Score = %lf seconds", timescore);
 printf("                Your Playtime Score is %f seconds \n", playtime); 


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}

int CheckWinningCondition()
{	

char Winner='0';

if (square[1]==square[2] && square[2]==square[3] && (square[3]=='X' || square[3]=='O')) 
Winner=square[3];
else if (square[1]==square[4] && square[4]==square[7] && (square[7]=='X' || square[7]=='O')){
 Winner=square[7];}
else if (square[3]==square[6] && square[6]==square[9] && (square[9]=='X' || square[9]=='O')){ 
Winner=square[9]; }
else if (square[7]==square[8] && square[8]==square[9] && (square[9]=='X' || square[9]=='O')){
 Winner=square[9];}
else if (square[2]==square[5] && square[5]==square[8] && (square[8]=='X' || square[8]=='O')){
 Winner=square[8];}
else if (square[2]==square[5] && square[5]==square[8] && (square[8]=='X' || square[8]=='O')){
 Winner=square[8];}
else if (square[4]==square[5] && square[5]==square[6] && (square[6]=='X' || square[6]=='O')){
 Winner=square[6];}
else if (square[2]==square[5] && square[5]==square[8] && (square[8]=='X' || square[8]=='O')){
 Winner=square[8];}
else if (square[1]==square[5] && square[5]==square[9] && (square[9]=='X' || square[9]=='O')){
 Winner=square[9];}
else if (square[2]==square[5] && square[5]==square[8] && (square[8]=='X' || square[8]=='O')){
 Winner=square[8];}
else if (square[3]==square[5] && square[5]==square[7] && (square[7]=='X' || square[7]=='O')){
 Winner=square[7];}

else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] 
        != '7' && square[8] != '8' && square[9] != '9')
{
        return -1;
}


if (Winner=='O' ){

printf( "Player 2 Win(%s)",arr);
sem_post(&s);
return 0;
}
else if (Winner=='X'){

printf( "Player 1 Win(%s)",buffer);
return 0;
}

else return 1;
}




