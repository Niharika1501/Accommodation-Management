#include<bits/stdc++.h>
using namespace std;

typedef struct accommodation 
{ 
    char firstname[15]; 
    char lastname[15]; 
    char accommodation_type[10];
    int idtype; 
    typedef struct idnum 
    { 
        char aadhaar[10] ; 
        char passport[10]; 
        char empcode[10] ;
    }idnum; 
idnum id;
char address[100]; 
}accomodate; 

typedef struct Node
{
    accomodate data;
    struct Node* next;
}Node;

typedef struct LLNode
{
    Node* val;
    struct LLNode* nextNode;
}LLNode;

LLNode* makeLLNode(Node* ptr)
{
    LLNode* aux = (LLNode*)malloc(sizeof(LLNode));
    aux->val = ptr;
    aux->nextNode = NULL;
    return aux;
}
Node* makeNode(accomodate obj)
{   
    Node* temporary = (Node*)malloc(sizeof(Node));
    temporary->data = obj;
    temporary->next = NULL;
    return temporary;
}

bool stringChecker(char array1[], char array2[])
{       
    int i;
    for(i = 0; array1[i]!='\0'&& array2[i] !='\0'; i++)
    {
        if(array1[i] != array2[i])
        {
            return false;
        }
    }
    if(array1[i]=='\0' && array2[i] =='\0')
    {
        return true;
    }
    return false;
}

void createLinkedList(Node* temp,Node** headptr)
{
    if((*headptr)==NULL)
    {
        (*headptr) = temp;      
    }
    else
    {
        if(temp->data.id.aadhaar[0] != '\0')
        {
            temp->next = (*headptr);
            *headptr = temp;
        }
        else if(temp->data.id.passport[0] != '\0')
        {
            Node* passportNode = (Node*)malloc(sizeof(Node));
            passportNode = (*headptr);
            while(passportNode->data.idtype==0 && (passportNode->next!=NULL))
            {
                passportNode=passportNode->next;
            }
            if(passportNode->next==NULL)
            {
                passportNode->next=temp;
                temp->next=NULL;
            }
            else
            {
                temp->next = passportNode->next;
                passportNode->next = temp;
            }
        }
        else
        {
            Node* empcodeNode = (Node*)malloc(sizeof(Node));
            empcodeNode = (*headptr);
            while(empcodeNode->next!=NULL)
            {
                empcodeNode = empcodeNode->next;
            }
            empcodeNode->next = temp;
            temp->next = NULL;
        }
    }

}

void printIndexRecords(LLNode* indexhead)
{       
    LLNode* ptr = indexhead;
    while(ptr)
    {
       if(ptr->val->data.idtype==0)
        {
            std::cout<<(ptr->val->data).firstname<<" "<<(ptr->val->data).lastname<<" "<<(ptr->val->data).accommodation_type<<" "<<(ptr->val->data).id.aadhaar<<" "
            <<(ptr->val->data).address;
        }
        else if(ptr->val->data.idtype==1)
        {
            std::cout<<(ptr->val->data).firstname<<" "<<(ptr->val->data).lastname<<" "<<(ptr->val->data).accommodation_type<<" "<<(ptr->val->data).id.passport<<" "
            <<(ptr->val->data).address;
        }
        else
        {
            std::cout<<(ptr->val->data).firstname<<" "<<(ptr->val->data).lastname<<" "<<(ptr->val->data).accommodation_type<<" "<<(ptr->val->data).id.empcode<<" "
            <<(ptr->val->data).address;
        }
        std::cout<<endl;

        ptr = ptr->nextNode;
    }
    return;
}

void printRecords(Node* headptr)
{
    Node* p = NULL;
    p = (headptr);
    while(p)
    {   
        if(p->data.idtype==0)
        {
            std::cout<<(p->data).firstname<<" "<<p->data.lastname<<" "<<p->data.accommodation_type<<" "<<p->data.id.aadhaar<<" "
            <<p->data.address;
        }
        else if(p->data.idtype==1)
        {
            std::cout<<(p->data).firstname<<" "<<p->data.lastname<<" "<<p->data.accommodation_type<<" "<<p->data.id.passport<<" "
            <<p->data.address;
        }
        else
        {
            std::cout<<(p->data).firstname<<" "<<p->data.lastname<<" "<<p->data.accommodation_type<<" "<<p->data.id.empcode<<" "
            <<p->data.address;
        }
        std::cout<<endl;

        p = p->next;
    }
}
void insertRecord(Node** headptr)
{       
    int numberOfRecord;
    std::cout << "Enter number of Records:"<<" ";
    std::cin >> numberOfRecord;
    for(int i = 0; i < numberOfRecord; i++)
    {
    accomodate a;
    Node* temp;
    temp = makeNode(a);
    std::cout<<"Enter firstname :"<<" ";
    std::cin >> a.firstname;
    std::cout<<"Enter lastname :"<<" ";
    std::cin >> a.lastname;
    std::cout <<"Enter Accomodation Type:"<<" ";
    std::cin >> a.accommodation_type;
    std::cout<<"Enter ID Type:"<<" ";
    std::cin>> a.idtype;
    if(a.idtype==0)
    {
        std::cout<<"Enter aadhaar:"<<" ";
        std::cin >> a.id.aadhaar;

        a.id.passport[0] = '\0';
        a.id.empcode[0] = '\0';
    }
    else if(a.idtype==1)
    {
        std::cout<<"Enter passport:"<<" ";
        std::cin >> a.id.passport;

        a.id.aadhaar[0] = '\0';
        a.id.empcode[0] = '\0';
    }
    else
    {
        std::cout<<"Enter empcode:"<<" ";
        std::cin >> a.id.empcode;

        a.id.aadhaar[0] = '\0';
        a.id.passport[0] = '\0';
    }
    std::cout <<"Enter address:"<<" ";
    std::cin >> a.address;
    temp = makeNode(a);
    createLinkedList(temp,headptr);
    }
    // printRecords(*headptr);
}

void removeDuplicateRecord(Node* headptr)
{
    Node* p = headptr;
    Node*(*last) = NULL;
    Node *r = NULL;
    while(p && (p->next))
    {
        if(p->data.idtype==0)
        {       
            (*last) = p->next;
            r = p;
            while((*last) && (*last)->data.idtype==0)
            {
                if(stringChecker(p->data.id.aadhaar,(*last)->data.id.aadhaar))
                {   
                    r->next = (*last)->next;
                    delete((*last));
                    if((*last)->next)
                    {
                        (*last) = (*last)->next;
                    }
                   
                }
                else
                {
                    (*last)=(*last)->next;
                    r=r->next;
                    
                }
            }
            p=p->next;
        }
        else if(p->data.idtype==1)
        {           
            (*last) = p->next;
            r = p;
            // cout<<p->data.lastname << " ";
            while((*last) && (*last)->data.idtype==1)
            {   
                if(stringChecker(p->data.id.passport,(*last)->data.id.passport))
                {
                    r->next = (*last)->next;
                    delete((*last));
                    if((*last)->next)
                    {
                        (*last) = (*last)->next;
                    }
                   
                }
                else
                {
                    (*last)=(*last)->next;
                    r=r->next;
                    
                }
            }
            p=p->next;

        }
        else
        {
            (*last) = p->next;
            r = p;
            while((*last) && (*last)->data.idtype==2)
            {
                if(stringChecker(p->data.id.empcode,(*last)->data.id.empcode))
                {   
                    r->next = (*last)->next;
                    delete((*last));
                    if((*last)->next)
                    {
                        (*last) = (*last)->next;
                    }
                   
                }
                else
                {
                    (*last)=(*last)->next;
                    r=r->next;
                    
                }
            }
            p=p->next;
        }
    }
}


void recordsAlphabetically(LLNode** indexHeadptr, Node* p)
{   
    (*indexHeadptr) = makeLLNode(p);
    LLNode* trailing = NULL;
    LLNode* iterating = (*indexHeadptr);
    Node* original = p->next;
    while(original)
    {   
        
        while(iterating)
        {
            if(iterating != NULL && ((strcmp(iterating->val->data.firstname,original->data.firstname)<0) || ((strcmp(iterating->val->data.firstname,original->data.firstname)==0) && (strcmp(iterating->val->data.lastname,original->data.lastname)<0))))
            {
                trailing=iterating;
                iterating=iterating->nextNode;
            }
            else
            {
                if(iterating==(*indexHeadptr))
                {

                }
            }
        }
        original = original->next;
    }
    
    // printIndexRecords(*indexHeadptr);    

    // }
}

void SearchRecords(Node* headptr, char name[])
{
    Node* p = headptr;
    while(p)
    {       
        if(strcmp(p->data.firstname,name) == 0)
        {
            if(p->data.idtype==0)
            {
                std::cout<<(p->data).firstname<<" "<<p->data.lastname<<" "<<p->data.accommodation_type<<" "<<p->data.id.aadhaar<<" "
                <<p->data.address;
            }
            else if(p->data.idtype==1)
            {
                std::cout<<(p->data).firstname<<" "<<p->data.lastname<<" "<<p->data.accommodation_type<<" "<<p->data.id.passport<<" "
                <<p->data.address;
            }
            else
            {
                std::cout<<(p->data).firstname<<" "<<p->data.lastname<<" "<<p->data.accommodation_type<<" "<<p->data.id.empcode<<" "
                <<p->data.address;
            }
            std::cout<<endl;
        }
        p = p->next;
    }
}

int main()
{       
    int choice;
    Node* head = NULL;
    LLNode* indexHead = NULL;
    char option = 'Y';
    while(option == 'Y')
    {
    std::cout << "1.Insert Records"<<endl;
    std::cout<<"2.Remove Duplicate Record"<<endl;
    std::cout<<"3.Print Records"<<endl;
    std::cout<<"4.Print Records in alphabetical order"<<endl;
    std::cout <<"5.Search a Record"<<endl;
    std::cout<<"6.Delete a Record"<<endl;
    std::cout<<"7.Update a record"<<endl;
    std::cout<<"8.Special Request Accomodation"<<endl;
    std::cout << "Enter your choice:"<< endl;
    std::cin >> choice;
    
    switch (choice)
    {
    case 1:
        insertRecord(&head);
        break;
    case 2:
        removeDuplicateRecord(head);
        break;
    case 3:
        printRecords(head);
        break;
    case 4:
        recordsAlphabetically(&indexHead,head);
        printIndexRecords(indexHead);
        break;  
    case 5:
        char name[15];
        std::cout << "Enter the firstname :"<< " ";
        std::cin >> name;
        SearchRecords(head,name);
        break;  
    default:
        break;
    }
    std::cout<<"Do you want to continue?(Y/N):"<<" ";
    std::cin >> option;
    }

}