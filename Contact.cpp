/*
 * Author:      Allen_3
 * LANG:        C++
 * */
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
using namespace std;

/**********************MACROS DEFINES**************************/
#define OUTPUT_FILE         "ContactList.txt"
#define OUTPUT_FILE_AUTO    "ContactList_autosave.txt"
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
_info *List = NULL , *Tail = NULL;
int  ListLength = 0;
int  command;

/************************PROTOTYPES****************************/
void Print_WelcomeInfo();
void Print_CommandInfo();
void Print_ErrorInfo();
void Add_NewContact();
int  getListChoice();
void List_ContactInfo();
void FILE_List_ContactInfo(FILE *stream , tm *GMTtime);
void OutputToFile(bool );
int  getDeleteChoice();
void Delete_Contact_byname();
void Delete_Contact_bytelnum();
int  getQueryChoice();
void Query_Contact_byname();
void Query_Contact_bytelnum();
int  getModifyChoice();
void Modify_Contact_name(int );
void Modify_Contact_telnum(int );
void Modify_Contact_birthday(int );

/*********************FUNCTIONS DEFINES************************/
void Print_WelcomeInfo(){
    printf("****************************************************************************\n\n\n");
    printf("\tWelcome to use this Contact Program!\n\n\n");
    printf("****************************************************************************\n");
}   //Print_WelcomeInfo

void Print_CommandInfo(){
    printf("\n\n\n");
    printf("====================================Main Menu=========================================\n");
    printf("\tHere are the commands you can type in (just type in the entry number)\n\n");
    printf("\t0. List all contacts.\n");
    printf("\t1. Create a new contact.\n");
    printf("\t2. Delete a contact.\n");
    printf("\t3. Query detail information.\n");
    printf("\t4. Modify a contact's information.\n");
    printf("\t5. Exit this Program.\n");
    printf("\n");
    printf("Command: ");
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
    printf("\tBirthday(**** ** ** or just type in 0 to skip this): ");
    int option;
    scanf("%d" , &option);
    if (option != 0){
        scanf("%d%d" , &newNode->birthday.month , &newNode->birthday.day);
    }   //option != 0
    
    if (List){
        newNode->next = NULL;
        newNode->last = Tail;
        Tail->next = newNode;
        Tail = newNode;
    }
    else{
        newNode->last = NULL;
        newNode->next = NULL;
        List = newNode;
        Tail = newNode;
    }
}   //Add_NewContact

int getListChoice(){
    int command;
    printf("--------------------------------------------------------------------------------\n");
    printf("\t\tHere are the commands you can type in (just type in the entry number)\n\n");
    printf("\t\t1. List all contacts information on the screen.\n");
    printf("\t\t2. Output all contacts information in the file \"ContactList.txt\".\n");
    printf("\t\t3. Back to the Main menu.\n");
    printf("Command: ");
    scanf("%d" , &command);
    return command;
}   //getListChoice

void List_ContactInfo(){
    if (ListLength == 0){ 
        printf("****************************************************************************\n\n\n");
        Print_ErrorInfo(0);
        return;
    }   //  List Empty
    int ID = 1;
    _info *Node = List;
    printf("----------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------\n");
    if (ListLength == 1)
        printf("There is only 1 contact here:\n");
    else 
        printf("There are %d contacts here:\n" , ListLength);
    while (Node){
        printf("****************************************************************************\n");
        printf("Contact ID:        %d\n" , ID ++);
        printf("Contact Name:      %s\n" , Node->name);
        printf("Contact Telephone: %s\n" , Node->telnum);
        printf("Contact Birthday:  %04d--%02d--%02d\n" , Node->birthday.year , Node->birthday.month , Node->birthday.day);
        Node = Node->next;
    }   //while Node
}   //List_ContactInfo

void FILE_List_ContactInfo(FILE * stream , tm * GMTtime){
    fprintf(stream , "Latest saving time: %4d_%02d_%02d %2d:%2d +0080 GMT\n" , (GMTtime->tm_year + ORIGIN_YEAR) , GMTtime->tm_mon , 
            GMTtime->tm_mday , (GMTtime->tm_hour + CCT) , GMTtime->tm_min);

    int ID = 1;
    _info *Node = List;
    fprintf(stream , "----------------------------------------------------------------------------\n");
    fprintf(stream , "----------------------------------------------------------------------------\n");
    if (ListLength == 1)
        fprintf(stream , "There is only 1 contact here:\n");
    else
        fprintf(stream , "There are %d contacts here:\n" , ListLength);
    while (Node){
        fprintf(stream , "****************************************************************************\n");
        fprintf(stream , "Contact ID:        %d\n" , ID ++);
        fprintf(stream , "Contact Name:      %s\n" , Node->name);
        fprintf(stream , "Contact Telephone: %s\n" , Node->telnum);
        fprintf(stream , "Contact Birthday:  %04d--%02d--%02d\n" , Node->birthday.year , Node->birthday.month , Node->birthday.day);
        Node = Node->next;
    }   //while Node
}   //FILE_List_ContactInfo

void OutputToFile(bool isAutoSave){
    if (!isAutoSave && (ListLength == 0)){
        printf("****************************************************************************\n\n\n");
        Print_ErrorInfo(0);
        return ;
    }   //  List Empty
    FILE *FILEout;
    if (isAutoSave){
        if (ListLength > 0)
            printf("\nCurrent contact list will auto save in the file \"ContactList_autosave.txt\"\n\n");
        FILEout = fopen(OUTPUT_FILE_AUTO , "w");
    }
    else
        FILEout = fopen(OUTPUT_FILE , "w");

    time_t rawTime = time(0);
    tm * GMTtime = gmtime(&rawTime);

    FILE_List_ContactInfo(FILEout , GMTtime);

    fclose(FILEout);
}   //OutputToFile

int getDeleteChoice(){
    int command;
    printf("--------------------------------------------------------------------------------\n");
    printf("\t\tHere are the commands you can type in (just type in the entry number)\n\n");
    printf("\t\t1. Delete by name.\n");
    printf("\t\t2. Delete by telephone number.\n");
    printf("\t\t3. Back to the Main menu.\n");
    printf("Command: ");
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
            ListLength --;

            LastNode = Node->last;
            NextNode = Node->next;
            if (!LastNode && !NextNode){
                delete Node;
                List = NULL;
                break;
            }   //  Only one Node
            if (!LastNode){
                NextNode->last = NULL;
                List = NextNode;
                delete Node;
                break;
            }   //  Head
            if (!NextNode){
                LastNode->next = NULL;
                delete Node;
                break;
            }   //  Tail

            LastNode->next = NextNode;
            NextNode->last = LastNode;

            delete Node;
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
            ListLength --;

            LastNode = Node->last;
            NextNode = Node->next;
            if (!LastNode && !NextNode){
                delete Node;
                List = NULL;
                break;
            }   //  Only one Node
            if (!LastNode){
                NextNode->last = NULL;
                List = NextNode;
                delete Node;
                break;
            }   //  Head
            if (!NextNode){
                LastNode->next = NULL;
                delete Node;
                break;
            }   //  Tail

            LastNode->next = NextNode;
            NextNode->last = LastNode;

            delete Node;
            break;
        }   //  Find the target
        Node = Node->next;
    }   //while Node
    if (!isGetTelnum){
        Print_ErrorInfo(3);
    }   //  Target does not exist
}   //Delete_Contact_bytelnum

int getQueryChoice(){
    int command;
    printf("--------------------------------------------------------------------------------\n");
    printf("\t\tHere are the commands you can type in (just type in the entry number)\n\n");
    printf("\t\t1. Query by name.\n");
    printf("\t\t2. Query by telephone number.\n");
    printf("\t\t3. Back to the Main menu.\n");
    printf("Command: ");
    scanf("%d" , &command);
    return command;
}   //getQueryChoice

void Query_Contact_byname(){
    char name[20];
    int  ID = 1;
    _info *Node = List;

    printf("\t\tThe name you want to query: \n");
    scanf("%s" , name);

    bool isGetName = false;
    while (Node){        
        if (strcmp(Node->name , name) == 0){
            isGetName = true;
            
            printf("****************************************************************************\n\n\n");
            printf("Contact ID:        %d\n" , ID);
            printf("Contact Name:      %s\n" , Node->name);
            printf("Contact Telephone: %s\n" , Node->telnum);
            printf("Contact Birthday:  %04d--%02d--%02d\n" , Node->birthday.year , Node->birthday.month , Node->birthday.day);

            break;
        }   //  Find the target
        Node = Node->next;
        ID ++;
    }   //while Node
    if (!isGetName){
        Print_ErrorInfo(2);
    }   //  Target does not exist
}   //Query_Contact_byname

void Query_Contact_bytelnum(){
    char telnum[20];
    int ID = 1;
    _info *Node = List;

    printf("\t\tThe telephone number you want to query: \n");
    scanf("%s" , telnum);

    bool isGetTelnum = false;
    while (Node){
        if (strcmp(Node->telnum , telnum) == 0){
            isGetTelnum = true;

            printf("****************************************************************************\n\n\n");
            printf("Contact ID:        %d\n" , ID);
            printf("Contact Name:      %s\n" , Node->name);
            printf("Contact Telephone: %s\n" , Node->telnum);
            printf("Contact Birthday:  %04d--%02d--%02d\n" , Node->birthday.year , Node->birthday.month , Node->birthday.day);

            break;
        }   //  Find the target
        Node = Node->next;
        ID ++;
    }   //while Node
    if (!isGetTelnum){
        Print_ErrorInfo(3);
    }   //  Target does not exist
}   //Query_Contact_bytelnum

int getModifyChoice(int *TargetID_add){
    int command;
    char ch;
    printf("--------------------------------------------------------------------------------\n");
    printf("Attention: To use this function , you should first get the contact's ID. In order to get that , you can either use funtion 0 or 3 in the Main Menu. \'y\' to go ahead , \'n\' to return tu the Main Menu. \n");
    scanf("%c%c" , &ch , &ch);
    if (ch == 'n' || ch == 'N')
        return -1;      //  Go back to the Main menu
    printf("\t\tThe contact's ID: ");
    scanf("%d" , TargetID_add);
    printf("\t\tHere are the commands you can type in (just type in the entry number)\n\n");
    printf("\t\t1. Modify the contact's name.\n");
    printf("\t\t2. Modify the contact's telephone number.\n");
    printf("\t\t3. Modify the contact's birthday date.\n");
    printf("Command: ") ;
    scanf("%d" , &command);
    return command;
}   //getModifyChoice

void Modify_Contact_name(int TargetID){
    int ID = 1;
    char name[20];
    _info *Node = List;
    printf("\t\tThe new name: ");
    scanf("%s" , name);

    while (Node){
        if (ID == TargetID){
            memcpy(Node->name , name , sizeof(char) * 20);
            break;
        }   //  Find the target
        ID ++;
        Node = Node->next;
    }   //while Node
}   //Modify_Contact_name

void Modify_Contact_telnum(int TargetID){
    int ID = 1;
    char telnum[20];
    _info *Node = List;
    printf("\t\tThe new telephone number: ");
    scanf("%s" , telnum);

    while (Node){
        if (ID == TargetID){
            memcpy(Node->telnum , telnum , sizeof(char) * 20);
            break;
        }   //  Find the target
        ID ++;
        Node = Node->next;
    }   //while Node
}   //Modify_Contact_telnum

void Modify_Contact_birthday(int TargetID){
    int ID = 1 , year , month , day;
    _info *Node = List;
    printf("\t\tThe new birthday date(**** ** **): ");
    scanf("%d%d%d" , &year, &month , &day);
    
    while (Node){
        if (ID == TargetID){
            Node->birthday.year  = year;
            Node->birthday.month = month;
            Node->birthday.day   = day;
            break;
        }   //  Find the target
        ID ++;
        Node = Node->next;
    }   //while Node
}   //Modify_Contact_birthday

int main(){
    Print_WelcomeInfo();
    while (true){
        Print_CommandInfo();
        scanf("%d" , &command);
        if (command == 0){
            int option = getListChoice();
            if (option == 1)
                List_ContactInfo();
            else if (option == 2)
                OutputToFile(false);
            else if (option == 3)
                continue;
            else
                Print_ErrorInfo(1);
        }   //  List

        else if (command == 1){
            Add_NewContact();
        }   //  Add

        else if (command == 2){
            int option = getDeleteChoice();
            if (option == 1)
                Delete_Contact_byname();
            else if (option == 2)
                Delete_Contact_bytelnum();
            else if (option == 3)
                continue;
            else
                Print_ErrorInfo(1);
        }   //  Delete

        else if (command == 3){
            int option = getQueryChoice();
            if (option == 1)
                Query_Contact_byname();
            else if (option == 2)
                Query_Contact_bytelnum();
            else if (option == 3)
                continue;
            else
                Print_ErrorInfo(1);
        }   //  Query

        else if (command == 4){
            int TargetID;
            int option = getModifyChoice(&TargetID);
            if (option == -1)
                continue;
            else if (option == 1)
                Modify_Contact_name(TargetID);
            else if (option == 2)
                Modify_Contact_telnum(TargetID);
            else if (option == 3)
                Modify_Contact_birthday(TargetID);
            else
                Print_ErrorInfo(1);
        }   //  Modify

        else if (command == 5){
            OutputToFile(true);
            return 0;
        }   //  Exit

        else
            Print_ErrorInfo(1);

    }   //  main while

    return 0;
}   //main
