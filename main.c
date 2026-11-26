#include "header.h"

int main()
{
	STUDENT *headptr=0;
	char op;

	while(1)
	{
		printf("Enter your choice\n");
		printf("a/A: Add new record\n");
		printf("d/D: Delete a record\n");
		printf("s/S: Show the list\n");
		printf("m/M: Modify a record\n");
		printf("v/V: Save records\n");
		printf("t/T: Sort the list\n");
		printf("l/L: Delete all records\n");
		printf("r/R: Reverse the list\n");
		printf("e/E:exit\n");

		scanf(" %c",&op);

		switch(op)
		{

            case 'a':
	    case 'A':add_student(&headptr);break;

            case 'd':
            case 'D':delete_student(&headptr);break;

            case 's':
	    case 'S':show_students_list(headptr);break;

            case 'm':
	    case 'M':modify_student(&headptr);break;

            case 'v':
	    case 'V':save_students(headptr);break;

            case 't':
	    case 'T':sort_students(headptr);break;

            case 'l':
	    case 'L':delete_all(&headptr);break;

            case 'r':
	    case 'R':reverse_list(&headptr);break;
		
            case 'e':
            case 'E':exit_program(&headptr);break;;

            default: printf("Invalid\n");
        }
    }
}

void add_student(STUDENT **ptr)
{
    STUDENT *new, *temp;
    new = malloc(sizeof(STUDENT));

    printf("Enter rollno name and percentage:\n");
    scanf("%d%s%f",&new->rollno,new->name, &new->percentage);

    new->next = NULL;

    if(*ptr == NULL)
        *ptr=new;
    else
    {
        temp=*ptr;

        while(temp->next)
            temp=temp->next;
        temp->next=new;
    }
}


void delete_student(STUDENT **ptr)
{
    STUDENT *del, *prev;
    char name[50],ch;
    int roll,count=0;

    if (*ptr==0)
    {
        printf("No records found\n");
        return;
    }

    printf("R/r : Delete by roll number\n");
    printf("N/n : Delete by name\n");
    printf("Enter choice: ");
    scanf(" %c", &ch);

    if (ch=='R'||ch=='r')
    {
        printf("Enter roll number: ");
        scanf("%d",&roll);
    }
    else if (ch =='N'||ch=='n')
    {
        printf("Enter name: ");
        scanf("%s",name);

        del=*ptr;

        while (del!=0)
        {
            if (strcmp(del->name,name)==0)
            {
                printf("Roll No:%d Name:%s\n",del->rollno,del->name);
                count++;
            }

            del=del->next;
        }

        if (count==0)
        {
            printf("Name not found\n");
            return;
        }

        if (count>1)
        {
            printf("Enter roll number to delete: ");
            scanf("%d",&roll);
        }
        else
        {
            del=*ptr;

            while(strcmp(del->name,name)!= 0)del=del->next;

            roll=del->rollno;
        }
    }
    else
    {
        printf("Invalid choice\n");
        return;
    }

    del=*ptr;
    prev=NULL;

    while(del!=0)
    {
        if (del->rollno==roll)
        {
            if ((ch=='N'||ch=='n') && strcmp(del->name,name)!= 0)
            {
                prev=del;
                del=del->next;
                continue;
            }

            if (*ptr==del)
                *ptr=del->next;
            else
                prev->next=del->next;

            free(del);

            printf("Record deleted successfully\n");
            return;
        }

        prev=del;
        del=del->next;
    }

    printf("Record not found\n");
}


void show_students_list(STUDENT *ptr)
{
    STUDENT *temp;

    if (ptr==0)
    {
        printf("No records found\n");
        return;
    }

    temp=ptr;
    printf("Roll No.\tName\t\tPercentage\n");
    printf("---------------------------------------------\n");

    while(temp!=0)
    {
        printf("%d\t\t%s\t\t%f\n", temp->rollno,temp->name,temp->percentage);
        temp = temp->next;
    }
    printf("---------------------------------------------\n");
}

void save_students(STUDENT *ptr)
{
    FILE *fp;
    STUDENT *temp;

    fp=fopen("student.dat","w");

    if (fp==0)
    {
        printf("File not present\n");
        return;
    }

    temp=ptr;

    while (temp!=0)
    {
        fprintf(fp,"%d%s%f\n",temp->rollno,temp->name,temp->percentage);

        temp = temp->next;
    }

    fclose(fp);

    printf("Records saved successfully\n");
}

void reverse_list(STUDENT **ptr)
{
    STUDENT *prev=0;
    STUDENT *temp=*ptr;
    STUDENT *next;

    if (*ptr==0)
    {
        printf("file is empty\n");
        return;
    }

    while (temp!=0)
    {
        next = temp->next;
        temp->next=prev;
        prev=temp;
        temp=next;
    }

    *ptr=prev;

    printf("List reversed successfully\n");
}


void modify_student(STUDENT **ptr)
{
    STUDENT *temp, *found=0;
    char choice,name[30];
    int roll,count = 0;
    float percentage;

    if(*ptr==0)
    {
        printf("No records available\n");
        return;
    }

    printf("Enter which record to search for modification\n");
    printf("R/r : Search by roll number\n");
    printf("N/n : Search by name\n");
    printf("P/p : Search by percentage\n");

    printf("Enter your choice: ");
    scanf(" %c", &choice);

    if(choice=='r'||choice=='R')
    {
        printf("Enter roll number: ");
        scanf("%d", &roll);

        temp=*ptr;

        while(temp!=0)
        {
            if(temp->rollno==roll)
            {
                found=temp;
                break;
            }

            temp=temp->next;
        }
    }
    else if(choice=='n'||choice=='N')
    {
        printf("Enter name: ");
        scanf("%s",name);

        temp=*ptr;

        while(temp!=0)
        {
            if(strcmp(temp->name,name)==0)
            {
                printf("%d%s%f\n",temp->rollno, temp->name, temp->percentage);

                found = temp;
                count++;
            }

            temp = temp->next;
        }

        if(count>1)
        {
            printf("Enter roll number to modify: ");
            scanf("%d", &roll);

            found=0;
            temp=*ptr;

            while(temp!=0)
            {
                if(temp->rollno==roll&&strcmp(temp->name,name)==0)
                {
                    found=temp;
                    break;
                }

                temp=temp->next;
            }
        }
    }
    else if(choice=='p'||choice=='P')
    {
        printf("Enter percentage: ");
        scanf("%f",&percentage);

        temp=*ptr;
        count=0;

        while(temp!=0)
        {
            if(temp->percentage==percentage)
            {
                printf("%d%s%f\n",temp->rollno,temp->name,temp->percentage);

                found=temp;
                count++;
            }

            temp=temp->next;
        }

        if(count>1)
        {
            printf("Enter roll number to modify: ");
            scanf("%d",&roll);

            found=0;
            temp=*ptr;

            while(temp!=0)
            {
                if(temp->rollno== roll&&temp->percentage==percentage)
                {
                    found=temp;
                    break;
                }

                temp=temp->next;
            }
        }
    }
    else
    {
        printf("Invalid choice\n");
        return;
    }

    if(found==0)
    {
        printf("Record not found\n");
        return;
    }

    printf("\nCurrent Student Details\n");
    printf("%d%s%f\n",found->rollno,found->name,found->percentage);

    printf("\nEnter updated name and percentage:\n");
    scanf("%s%f",found->name,&found->percentage);

    printf("Record modified successfully\n");
}

void sort_students(STUDENT *ptr)
{
    STUDENT *temp1,*temp2;
    int roll;
    float percentage;
    char name[30];
    char choice;

    if(ptr==0)
    {
        printf("No records available\n");
        return;
    }

    printf("N/n : Sort with name\n");
    printf("P/p : Sort with percentage\n");

    printf("Enter your choice: ");
    scanf(" %c", &choice);

    if(choice=='n'||choice=='N')
    {
        temp1=ptr;

        while(temp1!=NULL)
        {
            temp2=temp1->next;

            while(temp2!=NULL)
            {
                if(strcmp(temp1->name,temp2->name) > 0)
                {
                    roll=temp1->rollno;
                    temp1->rollno = temp2->rollno;
                    temp2->rollno = roll;

                    strcpy(name,temp1->name);
                    strcpy(temp1->name,temp2->name);
                    strcpy(temp2->name,name);

                    percentage=temp1->percentage;
                    temp1->percentage=temp2->percentage;
                    temp2->percentage=percentage;
                }

                temp2=temp2->next;
            }

            temp1=temp1->next;
        }
    }
    else if(choice=='p'||choice=='P')
    {
        temp1=ptr;

        while(temp1!=0)
        {
            temp2=temp1->next;

            while(temp2!=NULL)
            {
                if(temp1->percentage<temp2->percentage)
                {
                    roll=temp1->rollno;
                    temp1->rollno=temp2->rollno;
                    temp2->rollno=roll;

                    strcpy(name,temp1->name);
                    strcpy(temp1->name,temp2->name);
                    strcpy(temp2->name,name);

                    percentage=temp1->percentage;
                    temp1->percentage=temp2->percentage;
                    temp2->percentage=percentage;
                }

                temp2=temp2->next;
            }

            temp1=temp1->next;
        }
    }
    else
    {
        printf("Invalid choice\n");
        return;
    }

    printf("\nSorted Student Records\n");

    temp1 = ptr;

    while(temp1!=0)
    {
        printf("%d%s%f\n",temp1->rollno,temp1->name,temp1->percentage);
        temp1 = temp1->next;
    }
}


void delete_all(STUDENT **ptr)
{
    STUDENT *temp;
    if(*ptr==0)
    {
        printf("No records found\n");
        return;
    }
    while(*ptr!=0)
    {
        temp=*ptr;
        *ptr=(*ptr)->next;
        free(temp);
    }
    *ptr=0;

    printf("All records deleted\n");
}


void exit_program(STUDENT **ptr)
{
    char choice;

    printf("\nS/s : Save and Exit\n");
    printf("E/e : Exit Without Saving\n");

    printf("Enter your choice: ");
    scanf(" %c", &choice);

    if (choice=='S'||choice=='s')
    {
        save_students(*ptr);

        while(*ptr!=0)
        {
            STUDENT *temp=*ptr;
            *ptr=(*ptr)->next;
            free(temp);
        }

     //   printf("Records saved successfully\n");
        printf("Program terminated\n");
        exit(0);
    }
    else if(choice=='E'||choice=='e')
    {
        while(*ptr!=0)
        {
            STUDENT *temp=*ptr;
            *ptr=(*ptr)->next;
            free(temp);
        }

        printf("Changes not saved\n");
        printf("Program terminated\n");
        exit(0);
    }
    else
    {
        printf("Invalid choice\n");
    }
}
