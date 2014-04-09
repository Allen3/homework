#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

/*********************STRUCTS DEFINES**************************/
struct _date{
    int year , month , day;
}__attribute__((packed));  //_date

struct _info{
    int ID;
    char name[20];
    char telnum[20];
    _date birthday;
    _info *next;
}__attribute__((packed));  //_info

/*********************VARIABLE DEFINES*************************/
_info *List = NULL;
int ListLength = 0;

/*********************FUNCTIONS DEFINES************************/
void Print_WelcomeInfo();
void Print_CommandInfo();
void Print_ErrorInfo();
void Add_NewContact();
void List_ContactInfo();
int  getDeleteChoice();
void Delete_Contact_byname();
void Delete_Contact_bytelnum();

void Print_WelcomeInfo(){
    printf("****************************************************************************\n");
    printf("\tWelcome to use this Contact Program!\n");
}   //Print_WelcomeInfo

void Print_CommandInfo(){
    printf("============================================================================\n");
    printf("\tHere are the commands you can type in (just type in the entry number)\n");
    printf("\t0. List all contacts.\n");
    printf("\t1. Create a new contact.\n");
    printf("\t2. Delete a contact.\n");

}   //Print_CommandInfo

void Print_ErrorInfo(){
    printf("Sorry , invalid input occurs :(\n");
}   //Print_ErrorInfo

void Add_NewContact(){
    _info *newNode = new _info;
    newNode->ID = ++ ListLength;
    printf("\tName: ");
    scanf("%s" , newNode->name);
    printf("\tTelephone: ");
    scanf("%s" , newNode->telnum);
    printf("\tBirthday(**** ** **): ");
    scanf("%d%d%d" , &newNode->birthday.year , &newNode->birthday.month , &newNode->birthday.day);
    
    if (List)
        List->next = newNode;
    else
        List = newNode;
}   //Add_NewContact

void List_ContactInfo(){
    _info *Node = List;
    while (Node){
        printf("****************************************************************************\n");
        printf("Contact ID:        %d\n" , Node->ID);
        printf("Contact Name:      %s\n" , Node->name);
        printf("Contact Telephone: %s\n" , Node->telnum);
        printf("Contact Birthday:  %.4d--%.2d--%.2d\n" , Node->birthday.year , Node->birthday.month , Node->birthday.day);
        Node = Node->next;
    }   //while Node
}   //List_ContactInfo

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
    _info Node = List;

    printf("\t\tThe name you want to delete: \n");
    scanf("%s" , name);
    
    //???
    while (Node){
        if (strcmp(Node->name , name) == 0){

        }   //  Find the target
        Node = Node->next;
    }   //while Node

}   //Delete_Contact_byname

int main(){
    Print_WelcomeInfo();
    while (true){
        Print_CommandInfo();
        int command;
        scanf("%d" , &command);
        if (command == 0){
            List_ContactInfo();
        }   //  List_ContactInfo
        else if (command == 1){
            Add_NewContact();
        }   //  Add_NewContact
        else if (command == 2){
            command = getDeleteChoice();
            if (command == 1)
                Delete_Contact_byname();
            else if (command == 2)
                Delete_Contact_bytelnum();
            else
                Print_ErrorInfo();
        }   //  Delete_Contact


    }   //  main while

    return 0;
}   //main
