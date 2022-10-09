//Name : Alden Sia Zheng Heng
//ID   : 20196637
//Title: Grocery Store Database
//Date : 15/12/2020

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure of the item list provided
struct item {
    int id;
    char name[20];
    double cost;
    char category;
    struct item *next;
};

//Global variable (as void function cannot return the value)
//flag is used to determine whether there is any changes in the original data loaded
//It is easier to determine the modification occur in program
//Each time the modification occur, flag++
int flag;
//check is used to determine there is any duplicate ID or name of items in the data loaded
//It is easier to determine there is any duplicate or not when pass the data from file through the function and store in linked list
int check = 0;

//Function prototype to be used
void IDsort(struct item **head, char *a);
void Namesort(struct item **head, char *a);
void Costsort(struct item **head, char *a);
void Categorysort(struct item **head, char *a);
void store(struct item *nodePtr, struct item **head,struct item **tail);
void add(struct item *nodePtr, struct item **head, struct item **tail);
void deleting(int a, struct item **head,struct item **tail);
void change(struct item **head,int a);
void search(char itemname[20], struct item **head);
void display(struct item **head);
void save(struct item **head,FILE *b);

//main function
int main(void){
    FILE *a;
    FILE *b;
    int choice1;
    int choice2;
    int deletenode;
    int changenode;
    int id;
    char file_name1[20];
    char file_name2[20];
    char answer[20];
    char itemname[20];
    char name[20];
    char category;
    char arr;
    char choice3[20];
    double cost;

    //Initial value indicate that the stack is empty
    //To capture the head and tail in the linked list
    struct item *head = NULL;
    struct item *tail = NULL;

    //Node that hold the data to insert into linked list
    struct item nodenode;

    printf("Welcome to grocery store!\n");
    printf("Enter the file name with file extension and directory to open\n");
    printf("Example: C:\\Users\\User-PC\\Desktop\\CF-Ex4\\food.txt\n\n");
    printf("User: ");
    scanf("%s",&file_name1);

    //Read the selected file
    a = fopen(file_name1,"r");

    //To determine the file is existed or not
    if(a==NULL)
    {
        printf("No such file!....\n");
        return 0;
    }

    //Read the file until the end of file
    while(fscanf(a, "%d%s%lf %c",&id, name, &cost, &category) !=EOF)
    {
        //Copy the data into the node and then store into the linked list
        nodenode.id = id;
        nodenode.cost = cost;
        strcpy(nodenode.name, name);
        nodenode.category = category;

        //Function to store the data and allocate the head and tail in the linked list
        store(&nodenode,&head,&tail);

        //To check if there is any duplicate name or ID of items read from the file
        if(check !=0)
        {
            return 0;
        }
    }
    printf("%s has been properly loaded into database!\n\n",file_name1);

    //Initialize the flag before show the menu
    flag = 0;

    //Close the file read
    fclose(a);

    //6 selection for user to choose for different function (menu)
    while(1)
    {
        printf("Please make one of the following selections (1-6):\n");
        printf("1. Add new item\n");
        printf("2. Delete item\n");
        printf("3. Change the cost of an item\n");
        printf("4. Search for item\n");
        printf("5. Display inventory details\n");
        printf("6. Quit\n");
        printf("User: ");
        scanf("%d",&choice1);
        switch(choice1)
        {
            //Add new item into the database and store as last node
            case 1:
            printf("\n");
            printf("What is the ID number of the item to add?\n");
            scanf("%d",&nodenode.id);
            printf("What is the name of the item to be added?\n");
            scanf("%s",&nodenode.name);
            printf("What is the cost of the item to be added?\n");
            scanf("%lf",&nodenode.cost);
            printf("What is the product category of the item to be added?\n");
            scanf(" %c",&nodenode.category);

            //Funciton to add newnode into the linked list
            //head and tail are loaded to check whether there is any duplicate item Name or ID
            //If not then allocate the new node as tail
            add(&nodenode,&head,&tail);
            printf("\n");
            break;

            //Delete the node and replace it with last node record
            case 2:
            printf("\n");
            printf("What is the ID number of the product to delete?\n");
            printf("User: ");
            scanf("%d",&deletenode);

            //Function to delete the node that selected by user
            //Tail will be the previous node of it as the last record node will replace the delete node
            deleting(deletenode,&head,&tail);
            break;

            //Search the target ID number of item and change the cost
            case 3:
            printf("\n");
            printf("What is the ID number of the item in question?\n");
            printf("User: ");
            scanf("%d",&changenode);

            //Fucntion to modify the cost
            change(&head,changenode);
            break;

            //Search the item by name
            case 4:
            printf("\n");
            printf("Which item would you like to search for?\n");
            printf("Please enter the item name...\n");
            printf("User: ");
            scanf("%s",&itemname);

            //Function to search the item selected by user and display
            search(itemname,&head);
            break;

            //Display item in either ascending or descending order and based on ID, name, cost and category
            case 5:
            printf("\n");

            //Ask the user to choose either sort or not the item list
            printf("Do you want to sort the item list before display? (Yes | No)\n");
            printf("User: ");
            scanf("%s",&choice3);
            printf("\n");

            //If 'NO', then print the current arrangment of the item list
            if(strcmp(choice3,"No")==0)
            {
                if(head == NULL)
                {
                    printf("The item list is empty. Nothing can print....\n\n");
                    break;
                }
                printf("Here is a listing of all the products in stock:\n");
                display(&head);
                printf("\n");
                break;
            }

            //If yes ask the user to select the type of arrangment
            if(strcmp(choice3,"Yes")==0)
            {
                printf("Please select type of arrangment\n");
                printf("[A] for ascending, [D] for descending\n");
                printf("User: ");
                scanf(" %c",&arr);

                //To determine whether the user choose ascending or descending order
                if(arr == 'A' || arr == 'D')
                {
                    //To determine which kind of matter the user want to sort
                    printf("\nWhich matter you want to choose for sort? (1-4)\n");
                    printf("1. ID\n");
                    printf("2. Name\n");
                    printf("3. Cost\n");
                    printf("4. Category\n");
                    printf("User: ");
                    scanf("%d",&choice2);
                    switch(choice2)
                    {
                        case 1:
                        printf("\n");
                        if(head != NULL)
                        {
                            printf("Here is a listing of all the products in stock:\n");

                            //Sort the data based on the ID and display
                            IDsort(&head,&arr);
                            display(&head);
                            printf("\n");
                        }
                        else
                        {
                            printf("The item list is empty\n");
                            printf("\n");
                        }
                        break;

                        case 2:
                        printf("\n");
                        if(head != NULL)
                        {
                            printf("Here is a listing of all the products in stock:\n");

                            //Sort the data based on the item name (ASCII) and display
                            Namesort(&head,&arr);
                            display(&head);
                            printf("\n");
                        }
                        else
                        {
                            printf("The item list is empty\n");
                            printf("\n");
                        }
                        break;

                        case 3:
                        printf("\n");
                        if(head != NULL)
                        {
                            printf("Here is a listing of all the products in stock:\n");

                            //Sort the data based on the item cost and display
                            Costsort(&head,&arr);
                            display(&head);
                            printf("\n");
                        }
                        else
                        {
                            printf("The item list is empty....\n");
                            printf("\n");
                        }
                        break;

                        case 4:
                        printf("\n");
                        if(head != NULL)
                        {
                            printf("Here is a listing of all the products in stock:\n");

                            //Sort the data based on the category of the item (ASCII) and display
                            Categorysort(&head,&arr);
                            display(&head);
                            printf("\n");
                        }
                        else
                        {
                            printf("The item list is empty\n");
                            printf("\n");
                        }
                        break;

                        default:
                        printf("Wrong choice...\n\n");
                    }
                }

                //If not [A] or [D] character, printf error message
                else
                {
                    printf("Invlaid command for arrangement...\n\n");
                    break;
                }
            }
            break;
            
            //To save the modification file and exit
            case 6:
            printf("\n");
            //If the flag is true or not equal 0, the program should ask the user to save the modification or not
            if(flag != 0)
            {
                printf("Would you like to save the changes made to the database? (Yes | No)\n");
                printf("User: ");
                scanf("%s",&answer);

                if(strcmp(answer,"Yes")==0)
                {
                    //If the database is empty, print message out to tell user cannot saved as there is nothing to save
                    if(head == NULL)
                    {
                        printf("\nThe item list is already empty...\n");
                        printf("There is nothing can be saved...\n");
                        return 0;
                    }
                    printf("\nWhat file would you like to save the new database?\n");
                    printf("*File name must with file extension and directory\n");
                    printf("*The filename cannot be same as the original file loaded!\n");
                    printf("Example: C:\\Users\\User-PC\\Desktop\\CF-Ex4\\newfood.txt\n");
                    printf("User: ");
                    scanf("%s",&file_name2);

                    //Compare the original file name with the new file enter by user
                    if(strcmp(file_name1,file_name2)!=0)
                    {
                        //Open the new file and write the content into it
                        b = fopen(file_name2,"w");
                        
                        //Function to write the content into the newfile
                        save(&head,b);

                        //Close the file
                        fclose(b);
                        printf("\nThe file have been saved! Thank you for shopping....\n");
                        return 0;
                    }
                    else
                    {
                        //If both file name,extension and directory is same, print error message and terminate the program
                        printf("\nThe file name is same as the original data file!\n");
                        printf("Unsuccessfully to save the data.......\n");
                        return 0;
                    }
                }
                if(strcmp(answer,"No")==0)
                {
                     printf("Thank you for shopping....\n");
                    return 0;
                }
            }
            else 
            {
                printf("Thank you for shopping...\n");
                return 0;
            }

            default:
            printf("Enter the wrong choice!\n\n");
        }
    }
    return 0;
}

//Function to store the data when read
void store(struct item *nodePtr, struct item **head,struct item **tail)
{
    //create a newnode to store the data
    struct item *newnode = (struct item *)malloc(sizeof(struct item));

    //Indicate a new head if the database is NULL
    struct item *ptr = *head;
    if(newnode == NULL){
        printf("Memory not available!\n");
        exit(1);
    }
    /*To check there is any duplicate ID or name of the item when loading the file*/
    if(head !=NULL)
    {
        while(ptr !=NULL)
        {
            if(ptr->id == nodePtr->id || strcmp(ptr->name, nodePtr->name)==0)
            {
                printf("There are items have same name or ID in the file!......\n");
                check++;
                return;
            }
            ptr = ptr->next;
        }
    }
    
    *newnode = *nodePtr;                //Copy data to newnode
    newnode->next = NULL;               //Indicate NULL after newnode
    
    //If head node is NULL, indicate the first data read as head node
    if(*head == NULL)
    {
        *head = newnode;
    }

    //Indicate tail as newnode per data stored
    else
    {
        
        (*tail)->next = newnode;
    }
    *tail = newnode;
}

//Function to add data into the linked list and indicate as tail
void add(struct item *nodePtr, struct item **head, struct item **tail)
{
    struct item *newnode = (struct item *)malloc(sizeof(struct item));
    struct item *ptr;
    ptr = *head;

    //If the database is empty, indicate the added data as new head and tail again
    if( ptr == NULL)
    {
        *newnode = *nodePtr;
        newnode->next = NULL;
        if(*head == NULL)
        {
            *head = newnode;
         }
        else
        {
        
            (*tail)->next = newnode;
        }
        *tail = newnode;
        flag++;
        return;
    }

    //To check the add item ID or name is duplicate, if yes then print message and return  
    while(ptr !=NULL)
    {
        if(ptr->id == nodePtr->id || strcmp(ptr->name,nodePtr->name)==0)
        {
            printf("\nSorry, the item you try to add is duplicate with the item stored in the data....\n");
            printf("Try to change either ID or Name and try again...\n\n");
            return;
        }
        else
        {
           ptr = ptr->next;
        } 
    }

    //If not then insert into the database
    *newnode = *nodePtr;
    newnode->next = NULL;
    (*tail)->next = newnode;
    *tail = newnode;
    flag++;
}

//Function to delete the selected data in database
void deleting(int a, struct item **head,struct item **tail)
{
    struct item *temp = *head;
    struct item *prev;
    struct item *beforetail;
    struct item *current = *head;
    
    //If the database is already empty, printf message and return
    if(temp == NULL)
    {
        printf("The item list is already empty. Nothing can be deleted...\n\n");
        return;
    }

    //To determine head = tail in database which mean there only one data left
    if(current == *tail)
    {
        //If last node is selected to delete in database, indicate head and tail as NULL
        if(current->id == a)
        {
            printf("ID %d, %s have been deleted from the database.\n\n",temp->id,temp->name);
            *head = NULL;
            *tail = NULL;
            flag++;
            return;
        }

        //If the input ID is not in the database, print error message and return
        else
        {
            printf("Sorry, there is no item in the database with that ID number.\n\n");
            return;
        }
        
    }

    //To obatain the address of the data before the last node which is tail
    while(current != *tail)
    {
        beforetail = current;
        current = current->next;
    }

    //Insert NULL after indicate the tail
    current->next = NULL;

    //If the fist node (head) is the node that user want
    if(temp != NULL && temp->id == a)
    {
        printf("ID %d, %s have been deleted from the database.\n\n",temp->id,temp->name);
        //Replace the selected node by the last inserted node in database
        temp->id = (*tail)->id;
        strcpy(temp->name,(*tail)->name);
        temp->cost = (*tail)->cost;
        temp->category = (*tail)->category;

        //Discard the last record data in the list
        beforetail->next = NULL;
        //free the last tail to save the memory space
        free(*tail);
        //Indicate the previous node before tail as new tail
        *tail = beforetail;
        //Flag + 1 for record the modification occur in the database
        flag++;
        return;
    }
    
    //If the first node is not the selected item, go through the whole database
    while(temp != NULL && temp->id != a)
    {
        if(temp->id == a)
        {
            printf("ID %d, %s have been deleted from the database.\n\n",temp->id,temp->name);
        }
        prev = temp;
        temp = temp->next;
    }

    //If there is not such ID in the database, print the message and return
    if(temp == NULL)
    { 
        printf("Sorry, there is no item in the database with that ID number.\n\n");
        return;
    }

    //If yes, then replace it with the last record node
    printf("ID %d, %s have been deleted from the database.\n\n",temp->id,temp->name);
    temp->id = (*tail)->id;
    strcpy(temp->name,(*tail)->name);
    temp->cost = (*tail)->cost;
    temp->category = (*tail)->category;

    //Discard the last record data in the list
    beforetail->next = NULL;

    //Free the last node to save memory
    free(*tail);
    
    //Indicate newtail as the previous node before original tail
    *tail = beforetail;

    //Record the modification
    flag++;
}

//Fucntion to display the item stored
void display(struct item **head)
{
    struct item *ptr;
    ptr = *head;
    printf("%-10s|%-20s|%-10s|%-10s\n","ID","Product","Price","Category");
    while(ptr!=NULL)
    {
        printf("%-10d|%-20s|%-10.2lf|%-10c\n",ptr->id,ptr->name,ptr->cost,ptr->category);
        ptr = ptr->next;
    }
}

//Function to open a new txt file, write and save
void save(struct item **head,FILE *b)
{
    struct item *ptr;
    ptr = *head;
    while(ptr!=NULL)
    {
        //Write the content in the database into the file
        fprintf(b, "%-10d%-20s%-10.2lf%-10c\n",ptr->id,ptr->name,ptr->cost,ptr->category);
        ptr = ptr->next;
    }
}

//Function to change the cost of the item in database
void change(struct item **head,int a)
{
    double newcost;
    struct item *temp = *head;
    
    //To find the ID that is same as the item ID store in database
    while(temp != NULL && temp->id != a)
    {
        temp = temp->next;
    }

    //If there is not such ID, then print message and return
    if(temp == NULL)
    { 
        printf("Sorry, there is no item in the database with that ID number.\n\n");
        return;
    }

    //If yes, ask the user to enter the new cost
    printf("\nWhat is the new price for %s?\n",temp->name);
    printf("User: ");
    scanf("%lf",&newcost);

    //Replace the old cost with new cost enter by user
    temp->cost = newcost;
    printf("%s now cost %.2lf\n\n",temp->name,temp->cost);

    //Record the modification in database
    flag++;
    return;
}

//Function to search the item in database
void search(char itemname[20], struct item **head)
{
    struct item *temp = *head;

    //To search the item that match the name that enter by user
    while(temp != NULL && strcmp(temp->name,itemname) !=0)
    {
        temp = temp->next;
    }

    //If there is not such item, print message and return
    if(temp == NULL)
    { 
        printf("Sorry, there is no item in the database with that name.\n\n");
        return;
    }

    //else print out the item information
    printf("\nHere is the product information:\n");
    printf("%-10s|%-20s|%-10s|%-10s\n","ID","Product","Price","Category");
    printf("%-10d|%-20s|%-10.2lf|%-10c\n\n",temp->id,temp->name,temp->cost,temp->category);
    return;
}

//Function to sort the item (either ascending or descending) based on ID
void IDsort(struct item **head, char *a)
{
    struct item *current;
    struct item *Nptr;

    //temporary file to hold the data to swap when sorting
    int tempID;
    double tempCost;
    char tempName[20];
    char tempCategory;
    current = *head;

    //If User select 'A' which is ascending, the database will sort in ascending orser which based on ID
    if(*a == 'A')
    {

        //Selection sort
        while(current->next != NULL)
        {
            Nptr = current->next;
        
            while(Nptr != NULL)
            {
                //Swap when the current ID is larger than others in the database
                if(current->id > Nptr->id)
                {
                    tempID = current->id;
                    current->id = Nptr->id;
                    Nptr->id=tempID;
                    tempCost=current->cost;
                    current->cost =Nptr->cost;
                    Nptr->cost = tempCost;
                    strcpy(tempName,current->name);
                    strcpy(current->name,Nptr->name);
                    strcpy(Nptr->name,tempName);
                    tempCategory = current->category;
                    current->category = Nptr->category;
                    Nptr->category = tempCategory;
                }
                Nptr = Nptr->next;
            }
            current = current->next;
        }
        flag++;
        return;
    }

    //If User select 'D' which is descending, the database will sort in ascending orser which based on ID
    if(*a == 'D')
    {
        //Selection sort
        while(current->next != NULL)
        {
            Nptr = current->next;
        
            while(Nptr != NULL)
            {
                //Swap when the current ID is smaller than others in database
                if(current->id < Nptr->id)
                {
                    tempID = current->id;
                    current->id = Nptr->id;
                    Nptr->id=tempID;
                    tempCost=current->cost;
                    current->cost =Nptr->cost;
                    Nptr->cost = tempCost;
                    strcpy(tempName,current->name);
                    strcpy(current->name,Nptr->name);
                    strcpy(Nptr->name,tempName);
                    tempCategory = current->category;
                    current->category = Nptr->category;
                    Nptr->category = tempCategory;
                }
                Nptr = Nptr->next;
            }
            current = current->next;
        }
        flag++;
        return;
    }
}

//Function to sort the item (either ascending or descending) based on Name
void Namesort(struct item **head, char *a)
{
    struct item *current;
    struct item *Nptr;

    //temporary file to hold the data to swap when sorting
    int tempID;
    double tempCost;
    char tempName[20];
    char tempCategory;
    current = *head;

    //If User select 'A' which is ascending, the database will sort in ascending orser which based on Name
    if(*a == 'A')
    {
        //Selection sort
        while(current->next != NULL)
        {
            Nptr = current->next;
        
            while(Nptr != NULL)
            {
                //Compare the string by ASCII value, if larger than swap
                if(strcmp(current->name,Nptr->name) > 0)
                {
                    tempID = current->id;
                    current->id = Nptr->id;
                    Nptr->id=tempID;
                    tempCost=current->cost;
                    current->cost =Nptr->cost;
                    Nptr->cost = tempCost;
                    strcpy(tempName,current->name);
                    strcpy(current->name,Nptr->name);
                    strcpy(Nptr->name,tempName);
                    tempCategory = current->category;
                    current->category = Nptr->category;
                    Nptr->category = tempCategory;
                }
                Nptr = Nptr->next;
            }
            current = current->next;
        }
        flag++;
        return;
    }

    //If User select 'D' which is descending, the database will sort in ascending orser which based on Name
    if(*a == 'D')
    {
        //Selection sort
        while(current->next != NULL)
        {
            Nptr = current->next;
        
            while(Nptr != NULL)
            {
                //Compare the string by ASCII value, if smaller than swap
                if(strcmp(current->name,Nptr->name) < 0)
                {
                    tempID = current->id;
                    current->id = Nptr->id;
                    Nptr->id=tempID;
                    tempCost=current->cost;
                    current->cost =Nptr->cost;
                    Nptr->cost = tempCost;
                    strcpy(tempName,current->name);
                    strcpy(current->name,Nptr->name);
                    strcpy(Nptr->name,tempName);
                    tempCategory = current->category;
                    current->category = Nptr->category;
                    Nptr->category = tempCategory;
                }
                Nptr = Nptr->next;
            }
            current = current->next;
        }
        flag++;
        return;
    }
}

//Function to sort the item (either ascending or descending) based on Cost
void Costsort(struct item **head,char * a)
{
    struct item *current;
    struct item *Nptr;

    //temporary file to hold the data to swap when sorting
    int tempID;
    double tempCost;
    char tempName[20];
    char tempCategory;
    current = *head;

    //If User select 'A' which is ascending, the database will sort in ascending orser which based on Cost
    if(*a == 'A')
    {
        //Selection sort
        while(current->next != NULL)
        {
            Nptr = current->next;
        
            while(Nptr != NULL)
            {
                //If current cost is larger than others in the database, then swap
                if(current->cost > Nptr->cost)
                {
                    tempID = current->id;
                    current->id = Nptr->id;
                    Nptr->id=tempID;
                    tempCost=current->cost;
                    current->cost =Nptr->cost;
                    Nptr->cost = tempCost;
                    strcpy(tempName,current->name);
                    strcpy(current->name,Nptr->name);
                    strcpy(Nptr->name,tempName);
                    tempCategory = current->category;
                    current->category = Nptr->category;
                    Nptr->category = tempCategory;
                }
                Nptr = Nptr->next;
            }
            current = current->next;
        }
        flag++;
        return;
    }

    //If User select 'D' which is descending, the database will sort in ascending orser which based on Cost
    if(*a == 'D')
    {
        //Selection sort
        while(current->next != NULL)
        {
            Nptr = current->next;
        
            while(Nptr != NULL)
            {
                //If current cost is smaller than others in the database, then swap
                if(current->cost < Nptr->cost)
                {
                    tempID = current->id;
                    current->id = Nptr->id;
                    Nptr->id=tempID;
                    tempCost=current->cost;
                    current->cost =Nptr->cost;
                    Nptr->cost = tempCost;
                    strcpy(tempName,current->name);
                    strcpy(current->name,Nptr->name);
                    strcpy(Nptr->name,tempName);
                    tempCategory = current->category;
                    current->category = Nptr->category;
                    Nptr->category = tempCategory;
                }
                Nptr = Nptr->next;
            }
            current = current->next;
        }
        flag++;
        return;
    }
}

//Function to sort the item (either ascending or descending) based on category
void Categorysort(struct item **head, char *a)
{
    struct item *current;
    struct item *Nptr;

    //temporary to hold the data to swap when sorting
    int tempID;
    double tempCost;
    char tempName[20];
    char tempCategory;
    current = *head;

    //If User select 'A' which is ascending, the database will sort in ascending orser which based on Category
    if(*a == 'A')
    {
        while(current->next != NULL)
        {
            Nptr = current->next;
        
            while(Nptr != NULL)
            {
                //Compare the category with ASCII value, if current is larger then others in database, then swap
                if(current->category > Nptr->category)
                {
                    tempID = current->id;
                    current->id = Nptr->id;
                    Nptr->id=tempID;
                    tempCost=current->cost;
                    current->cost =Nptr->cost;
                    Nptr->cost = tempCost;
                    strcpy(tempName,current->name);
                    strcpy(current->name,Nptr->name);
                    strcpy(Nptr->name,tempName);
                    tempCategory = current->category;
                    current->category = Nptr->category;
                    Nptr->category = tempCategory;
                }
                Nptr = Nptr->next;
            }
            current = current->next;
        }
    flag++;
    return;
    }

    //If User select 'D' which is descending, the database will sort in ascending orser which based on Category
    if(*a == 'D')
    {
        //Selection sort
        while(current->next != NULL)
        {
            Nptr = current->next;
        
            while(Nptr != NULL)
            {
                //Compare the category with ASCII value, if current is smaller then others in database, then swap
                if(current->category < Nptr->category)
                {
                    tempID = current->id;
                    current->id = Nptr->id;
                    Nptr->id=tempID;
                    tempCost=current->cost;
                    current->cost =Nptr->cost;
                    Nptr->cost = tempCost;
                    strcpy(tempName,current->name);
                    strcpy(current->name,Nptr->name);
                    strcpy(Nptr->name,tempName);
                    tempCategory = current->category;
                    current->category = Nptr->category;
                    Nptr->category = tempCategory;
                }
                Nptr = Nptr->next;
            }
            current = current->next;
        }
    flag++;
    return;
    }
}
