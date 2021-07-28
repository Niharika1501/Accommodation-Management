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

typedef struct accommodation_type_node
{
    bool isAccommodated;
    struct accommodation_type_node* next;    
}accommodation_type;
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
    Node*q = NULL;
    Node *r = NULL;
    while(p && (p->next))
    {
        if(p->data.idtype==0)
        {       
            q = p->next;
            r = p;
            while(q && q->data.idtype==0)
            {
                if(stringChecker(p->data.id.aadhaar,q->data.id.aadhaar))
                {   
                    r->next = q->next;
                    delete(q);
                    if(q->next)
                    {
                        q = q->next;
                    }
                   
                }
                else
                {
                    q=q->next;
                    r=r->next;
                    
                }
            }
            p=p->next;
        }
        else if(p->data.idtype==1)
        {           
            q = p->next;
            r = p;
            // cout<<p->data.lastname << " ";
            while(q && q->data.idtype==1)
            {   
                if(stringChecker(p->data.id.passport,q->data.id.passport))
                {
                    r->next = q->next;
                    delete(q);
                    if(q->next)
                    {
                        q = q->next;
                    }
                   
                }
                else
                {
                    q=q->next;
                    r=r->next;
                    
                }
            }
            p=p->next;

        }
        else
        {
            q = p->next;
            r = p;
            while(q && q->data.idtype==2)
            {
                if(stringChecker(p->data.id.empcode,q->data.id.empcode))
                {   
                    r->next = q->next;
                    delete(q);
                    if(q->next)
                    {
                        q = q->next;
                    }
                   
                }
                else
                {
                    q=q->next;
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
    LLNode* iterating;
    LLNode* temp;
    Node* original = p->next;
    int found = 0;
    while(original)
    {   
        found = 0;
        trailing = NULL;
        iterating = (*indexHeadptr);
        while((!found))
        {
            if(iterating != NULL && ((strcmp(iterating->val->data.firstname,original->data.firstname)<0) || ((strcmp(iterating->val->data.firstname,original->data.firstname)==0) && (strcmp(iterating->val->data.lastname,original->data.lastname)<0))))
            {
                trailing=iterating;
                iterating=iterating->nextNode;
            }
            else
            {   
                found = 1;
                if(iterating==NULL)
                {   
                    temp = makeLLNode(original);
                    trailing->nextNode = temp;                                        
                }
                else if(iterating == (*indexHeadptr))
                {
                    temp = makeLLNode(original);
                    temp->nextNode = (*indexHeadptr);
                    (*indexHeadptr) = temp;
                }
                else
                {
                    temp = makeLLNode(original);
                    trailing->nextNode = temp;
                    temp->nextNode = iterating;
                }
            }
        }
        original = original->next;
    }
    
    // printIndexRecords(*indexHeadptr);    

    // }
}

void SearchRecords(Node*p, LLNode** index_head)
{   
    char name[15];
    std::cout << "Enter the firstname :"<< " ";
    std::cin >> name;
    recordsAlphabetically(index_head,p);

    LLNode* ptr = (*index_head);
    int found = 0;
    while(ptr)
    {
        if(strcmp(ptr->val->data.firstname,name)==0)
        {   
            found = 1;
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
        }
        ptr=ptr->nextNode;
    }
    if(found==0)
    {
        cout << "Record with this firstname does not exists"<<endl;
    }

}

void deleteRecords(Node** originalHead, LLNode* indexhead)
{   
    int idNumber;
    char idNum[20];
    std::cout<< "Enter id type:"<<" ";
    cin>> idNumber;
    if(idNumber==0)
    {
        cout<<"Enter Aadhaar:"<<" ";
        cin>> idNum;
    }
    else if(idNumber==1)
    {
        cout<<"Enter Passport:"<<" ";
        cin>> idNum;
    }
    else
    {
        cout<<"Enter Empcode:"<<" ";
        cin>> idNum;
    }
    Node* p = (*originalHead);
    Node* r = NULL;
    while(p)
    {
        if(p->data.idtype==idNumber && ((strcmp(p->data.id.aadhaar,idNum)==0)||(strcmp(p->data.id.passport,idNum)==0)||(strcmp(p->data.id.empcode,idNum)==0)))
        {
            if(p==(*originalHead))
            {
                (*originalHead)=(*originalHead)->next;
                delete(p);
            }
            else
            {
                r->next = p->next;
                delete(p);
            }
        }
        r=p;
        p=p->next;
    }
    recordsAlphabetically(&indexhead,(*originalHead));
}

void updateRecords(Node** originalHead, LLNode* indexheadptr)
{   
    int idNumber;
    char idNum[20];
    char update_firstname[15],update_lastname[15],update_accommodation[10],update_address[100];
    std::cout<< "Enter id type of the record you wish to update:"<<" ";
    cin>> idNumber;
    if(idNumber==0)
    {
        cout<<"Enter Aadhaar of the record you wish to update:"<<" ";
        cin>> idNum;
    }
    else if(idNumber==1)
    {
        cout<<"Enter Passport of the record you wish to update:"<<" ";
        cin>> idNum;
    }
    else
    {
        cout<<"Enter Empcode of the record you wish to update:"<<" ";
        cin>> idNum;
    }
    Node* p = (*originalHead);
    int found = 0;
    while(p && (!found))
    {
        if(idNumber==0 && (strcmp(p->data.id.aadhaar,idNum)==0))
        {
            found = 1;
        }
        else if(idNumber==1 && (strcmp(p->data.id.passport,idNum)==0))
        {
            found = 1;
        }
        else if(idNumber==2 && (strcmp(p->data.id.empcode,idNum)==0))
        {
            found = 1;
        }
        else
        {
            p=p->next;
        }
    }
    if(found==1)
    {
        int opt;
        cout<<"1.Update firstname"<<endl;
        cout<<"2.Update lastname"<<endl;
        cout<<"3.Update Accomodation Type"<<endl;
        cout<<"4.Update Address"<<endl;
        cout<<"5.Update id type"<<endl;
        cin>>opt;
        switch (opt)
        {
            case 1:
                cout<<"Enter firstname:"<<" ";
                cin>>update_firstname;
                strcpy(p->data.firstname,update_firstname);
                recordsAlphabetically(&indexheadptr,(*originalHead));
                break;
            case 2:
                cout<<"Enter laststname:"<<" ";
                cin>>update_lastname;
                strcpy(p->data.lastname,update_lastname);
                recordsAlphabetically(&indexheadptr,(*originalHead));
                break;
            case 3:
                cout<<"Enter accommodation type:"<<" ";
                cin>>update_accommodation;
                strcpy(p->data.accommodation_type,update_accommodation);
                break;
            case 4:
                cout<<"Enter address:"<<" ";
                cin>>update_address;
                strcpy(p->data.address,update_address);
                break;    
            case 5:
            cout<<"If you want to change id type of a record, it is recommended to delete that record and enter a new entry with desired idtype"<<endl;
            break;
            default:
                break;
        }
    }
    else
    {
        cout<<"Record doesn't exist"<<endl;
    }
}
accommodation_type* type1head = NULL;
accommodation_type* type2head = NULL;
accommodation_type* type3head = NULL;
accommodation_type* type4head = NULL;
void Insert_acc_type(accommodation_type** head_ptr)
{
    accommodation_type* aptr = *head_ptr;
    accommodation_type* temp;
    
    if (aptr == NULL)
    {
        temp = (accommodation_type* )malloc(sizeof(accommodation_type));
        temp->isAccommodated = true;
        temp->next = NULL;
        *head_ptr = temp;
        
    }
    else
    {
        while (aptr->next!=NULL)
        {
            aptr = aptr->next;
        }        
        temp = (accommodation_type* )malloc(sizeof(accommodation_type));
        temp->isAccommodated = true;
        aptr->next = temp;
        temp->next = NULL; 
             
    }    
}

int count_nodes(accommodation_type** head_ptr)
{
    accommodation_type* aptr = *head_ptr;
    int count = 0;
    
    while (aptr != NULL)
    {
        count++;
        aptr = aptr->next;
    }
    
    return count;
}

void Delete_acc_type(accommodation_type** head_ptr)
{
    
    accommodation_type* temp;
    temp = *head_ptr;
    if (*head_ptr != NULL)
    {
        *head_ptr = (*head_ptr)->next;
    }    
    
    free(temp);
}

void AllocationHelper(Node* head, char str1[], char str2[], char str3[], char str4[],accommodation_type_node* typehead, char changedAllocation[])
{           
    int id_type;
    char id_aadhaar[15];
    char id_passport[15];
    char id_empcode[15];
    char temp_str[20];
    cout<<"Enter the ID-Type(0,1 or 2) of the person whose accommodation type you wish to change"<<" ";
	cin>> id_type;
	if(id_type==0)
	{
		cout<<"Enter the Aadhaar number :"<<" ";
		cin>> id_aadhaar;
	}
	else if(id_type==1)
	{
		cout<<"Enter the Passport number :"<<" ";
		cin>> id_passport;
	}
	else if(id_type==2)
	{
		cout<<"Enter the employee code :"<<" ";
		cin>> id_empcode;
	}
    int found=0;
	Node* nptr = head;
    Node* tptr = NULL;
	while((nptr != NULL) && !(found))
	{
		if((id_type==0) && (!strcmp((nptr->data).id.aadhaar,id_aadhaar)))
		{
			found=1;
		}
		else if((id_type==1) && (!strcmp((nptr->data).id.passport,id_passport)))
		{
			found=1;
		}
		else if((id_type==2) && (!strcmp((nptr->data).id.empcode,id_empcode)))
		{
			found=1;
		}
		else
		{
            tptr = nptr;
			nptr = nptr->next;
		}		
	}
    if (found == 1)
    {
        strcpy(temp_str,(nptr->data).accommodation_type);
        strcpy((nptr->data).accommodation_type,changedAllocation);
        cout<<(nptr->data).accommodation_type;
        Insert_acc_type(&typehead);
        if(strcmp(temp_str,str1)==0)
        {                    
            Delete_acc_type(&type1head);                    
        }
        else if(strcmp(temp_str,str2)==0)
        {
            Delete_acc_type(&type2head);
        }
        else if(strcmp(temp_str,str3)==0)
        {
            Delete_acc_type(&type3head);
        }
        else
        {
            Delete_acc_type(&type4head);
        }  
    }
    else
    {
        cout<<"No such resident found"<<" ";
    }                     
}    
void specialRequestAllocation(Node* head)
{
    char str1[20]="type-I";
	char str2[20]="type-II";
	char str3[20]="type-III";
	char str4[20]="type-IV";
    Node* nptr = head;
    while (nptr!=NULL)
    {
        if(!strcmp((nptr->data).accommodation_type,str1))
        {
            Insert_acc_type(&type1head);
        }
        else if(!strcmp((nptr->data).accommodation_type,str2))
        {
            Insert_acc_type(&type2head);
        }
        else if(!strcmp((nptr->data).accommodation_type,str3))
        {
            Insert_acc_type(&type3head);
        }
        else
        {
            Insert_acc_type(&type4head);
        }
        nptr=nptr->next;
    } 
    
    char requested_accommo_type[20];
    char changedAllocation[15];
	cout << "Enter the accommodation type which you want to request for allocation :"<<" ";
	cin >> requested_accommo_type;
	if(strcmp(requested_accommo_type,str1)==0)
    {
        if(count_nodes(&type1head)<10)
        {   
            // strcpy(changedAllocation,str1);
            AllocationHelper(head,str1,str2,str3,str4,type1head,requested_accommo_type);
        }
        else
        {
            cout<<"This Accommodation type is already full, cannot allocate"<<" ";
        }
    }
    else if(strcmp(requested_accommo_type,str2)==0)
    {
        if(count_nodes(&type2head)<10)
        {
            AllocationHelper(head,str1,str2,str3,str4,type2head,requested_accommo_type);
        }
        else
        {
            cout<<"This Accommodation type is already full, cannot allocate"<<" ";
        }
    }
    else if(strcmp(requested_accommo_type,str3)==0)
    {
        if(count_nodes(&type3head)<10)
        {
            AllocationHelper(head,str1,str2,str3,str4,type3head,requested_accommo_type);
        }
        else
        {
            cout<<"This Accommodation type is already full, cannot allocate"<<" ";
        }
    }
    else
    {
        if(count_nodes(&type4head)<10)
        {
            AllocationHelper(head,str1,str2,str3,str4,type4head,requested_accommo_type);
        }
        else
        {
            cout<<"This Accommodation type is already full, cannot allocate"<<" ";
        }
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
            SearchRecords(head,&indexHead);
            break;  
        case 6:
            deleteRecords(&head,indexHead);
            break;
        case 7:
            updateRecords(&head,indexHead);
            break;
        case 8:
            specialRequestAllocation(head);
            break;
        default:
            break;
        }
        std::cout<<"Do you want to continue?(Y/N):"<<" ";
        std::cin >> option;
    }

}