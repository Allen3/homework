/*
 * Author:      Allen_3
 * LANG:        C++
 * TIME:        2014_04_09 Wed. Apr. 19:43 +0800 GMT
 * */
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
using namespace std;

/**********************MACROS DEFINES**************************/
#define OUTPUT_FILE         "ContactList.txt"
#define CCT                 (+8)
#define ORIGIN_YEAR         (1900)

/*********************STRUCTS DEFINES**************************/
struct _date{
    int year , month , day;
}__attribute__((packed));  //_date

struct _info{
    char name[20];
    char telnum[20];
    _date birthday;
    _info *next , *last;
}__attribute__((packed));  //_info

/*********************VARIABLE DEFINES*************************/
_info *List = NULL;
int ListLength = 0;

/************************PROTOTYPES****************************/
void Print_WelcomeInfo();
void Print_CommandInfo();
void Print_ErrorInfo();
void Add_NewContact();
int  getListChoice();
void List_ContactInfo();
void FILE_List_ContactInfo(FILE *stream , tm *GMTtime);
void OutputToFile();
int  getDeleteChoice();
void Delete_Contact_byname();
void Delete_Contact_bytelnum();

/*********************FUNCTIONS DEFINES************************/
void Print_WelcomeInfo(){
    printf("****************************************************************************\n");
    printf("\tWelcome to use this Contact Program!\n");
}   //Print_WelcomeInfo

void Print_CommandInfo(){
    printf("\n\n\n\n");
    printf("============================================================================\n");
    printf("\tHere are the commands you can type in (just type in the entry number)\n");
    printf("\t0. List all contacts.\n");
    printf("\t1. Create a new contact.\n");
    printf("\t2. Delete a contact.\n");
    printf("\t3. Exit this Program.\n");
    //Append new funtcions
}   //Print_CommandInfo

void Print_ErrorInfo(int option){
    if (option == 0)
        printf("Sorry , you've got no contact here. :(\n");
    else if (option == 1)
        printf("Sorry , invalid input occurs. :(\n");
    else if (option == 2)
        printf("Sorry , Such a name does not exist in the current contact. :(\n");
    else if (option == 3)
        printf("Sorry , Such a telephone number does not exist in the current contact. :(\n");
}   //Print_ErrorInfo

void Add_NewContact(){
    _info *newNode = new _info;

    ListLength ++;
    printf("\tName: ");
    scanf("%s" , newNode->name);
    printf("\tTelephone: ");
    scanf("%s" , newNode->telnum);
    printf("\tBirthday(**** ** **): ");
    scanf("%d%d%d" , &newNode->birthday.year , &newNode->birthday.month , &newNode->birthday.day);
    
    if (List){
        newNode->last = List;
        List->next = newNode;
    }
    else
        List = newNode;
}   //Add_NewContact

int getListChoice(){
    int command;
    printf("\t\tHere are the commands you can type in (just type in the entry number)\n");
    printf("\t\t1. List all contacts information on the screen.\n");
    printf("\t\t2. Output all contacts information in the file \"ContactList.txt\".\n");
    scanf("%d" , &command);
    return command;
}   //getListChoice

void List_ContactInfo(){
    if (ListLength == 0){ 
        printf("****************************************************************************\n");
        Print_ErrorInfo(0);
        return;
    }   //  List Empty
    int ID = 1;
    _info *Node = List;
    while (Node){
        printf("****************************************************************************\n");
        printf("Contact ID:        %d\n" , ID ++);
        printf("Contact Name:      %s\n" , Node->name);
        printf("Contact Telephone: %s\n" , Node->telnum);
        printf("Contact Birthday:  %.4d--%.2d--%.2d\n" , Node->birthday.year , Node->birthday.month , Node->birthday.day);
        Node = Node->next;
    }   //while Node
}   //List_ContactInfo

void FILE_List_ContactInfo(FILE * stream , tm * GMTtime){
    fprintf(stream , "Latest saving time: %4d_%02d_%02d %2d:%2d +0080 GMT\n" , (GMTtime->tm_year + ORIGIN_YEAR) , GMTtime->tm_mon , 
            GMTtime->tm_mday , (GMTtime->tm_hour + CCT) , GMTtime->tm_min);

    int ID = 1;
    _info *Node = List;
    while (Node){
        fprintf(stream , "****************************************************************************\n");
        fprintf(stream , "Contact ID:        %d\n" , ID ++);
        fprintf(stream , "Contact Name:      %s\n" , Node->name);
        fprintf(stream , "Contact Telephone: %s\n" , Node->telnum);
        fprintf(stream , "Contact Birthday:  %04d--%02d--%02d\n" , Node->birthday.year , Node->birthday.month , Node->birthday.day);
        Node = Node->next;
    }   //while Node
}   //FILE_List_ContactInfo

void OutputToFile(){
    if (ListLength == 0){
        printf("****************************************************************************\n");
        Print_ErrorInfo(0);
        return ;
    }   //  List Empty
    FILE *FILEout = fopen(OUTPUT_FILE , "w");

    time_t rawTime = time(0);
    tm * GMTtime = gmtime(&rawTime);

    FILE_List_ContactInfo(FILEout , GMTtime);

    fclose(FILEout);
}   //OutputToFile

int getDeleteChoice(){
    int command;
    printf("\t\tHere are the commands you can type in (just type in the entry number)\n");
    printf("\t\t1. Delete by name.\n");
    printf("\t\t2. Delete by telephone number.\n");
    scanf("%d" , &command);
    return command;
}   //getDeleteChoice

void Delete_Contact_byname(){
    char name[20];
    _info *Node = List , *NextNode , *LastNode;

    printf("\t\tThe name you want to delete: \n");
    scanf("%s" , name);
    
    bool isGetName = false;
    while (Node){
        if (strcmp(Node->name , name) == 0){
            isGetName = true;            
            LastNode = Node->last;
            NextNode = Node->next;
            if (LastNode)
                LastNode->next = NextNode;
            if (NextNode)
                NextNode->last = LastNode;

            delete Node;
            ListLength --;

            Node = NextNode;
            break;
        }   //  Find the target
        Node = Node->next;
    }   //while Node
    if (!isGetName){
        Print_ErrorInfo(2);
    }   //  Target does not exist
}   //Delete_Contact_byname

void Delete_Contact_bytelnum(){
    char telnum[20];
    _info *Node = List , *NextNode , *LastNode;

    printf("\t\tThe telephone number you want to delete :\n");
    scanf("%s" , telnum);

    bool isGetTelnum = false;
    while (Node){
        if (strcmp(Node->telnum , telnum) == 0){
            isGetTelnum = true;
            LastNode = Node->last;
            NextNode = Node->next;
            if (LastNode)
                LastNode->next = NextNode;
            if (NextNode)
                NextNode->last = LastNode;

            delete Node;
            ListLength --;

            break;
        }   //  Find the target
        Node = Node->next;
    }   //while Node
    if (!isGetTelnum){
        Print_ErrorInfo(3);
    }   //  Target does not exist
}   //Delete_Contact_bytelnum

int main(){
    Print_WelcomeInfo();
    while (true){
        Print_CommandInfo();
        int command;
        scanf("%d" , &command);
        if (command == 0){
            command = getListChoice();
            if (command == 1)
                List_ContactInfo();
            else if (command == 2)
                OutputToFile();
            else
                Print_ErrorInfo(1);
        }   //  List

        else if (command == 1){
            Add_NewContact();
        }   //  Add

        else if (command == 2){
            command = getDeleteChoice();
            if (command == 1)
                Delete_Contact_byname();
            else if (command == 2)
                Delete_Contact_bytelnum();
            else
                Print_ErrorInfo(1);
        }   //  Delete

        else if (command == 3){
            return 0;
        }   //Exit

        else
            Print_ErrorInfo(1);

    }   //  main while

    return 0;
}   //main
