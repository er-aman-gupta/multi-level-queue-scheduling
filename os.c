#include<stdio.h>
#include<malloc.h>
struct process{
    int arrival_time,burst_time,priority,pid;
    struct process* next;
};
struct process* head1=NULL;
struct process* head2=NULL;
struct process* head3=NULL;
void inserter(int a,int b,int p,int p_id)
{
    struct process* head=NULL;
    if(p>0&&p<=5)
        head=head1;
    else if(p>5&&p<=10)
        head=head2;
    else if(p>10&&p<=15)
        head=head3;
    else
    {
        printf("Wrong priority!!!!!\nPlease enter again.\n");
        return;
    }
    struct process* newnode=(struct process*)malloc(sizeof(struct process));
    newnode->arrival_time=a;
    newnode->burst_time=b;
    newnode->priority=p;
    newnode->pid=p_id;
    newnode->next=NULL;
    if(head==NULL)
    {
        head=newnode;
        //newnode->next=NULL;

        if(head==NULL)
        {
        printf("NOT");
        }
    }
    else{
    struct process* ptr=head;
        if(head->arrival_time>a)
        {
            newnode->next=head;
            head=newnode;

        }

        else{
            while(ptr->next!=NULL&&ptr->next->priority<p)
            {
                ptr=ptr->next;
            }
            newnode->next=ptr->next;
            ptr->next=newnode;
        }
    }
    if(p>0&&p<=5)
        head1=head;
    else if(p>5&&p<=10)
        head2=head;
    else if(p>10&&p<=15)
        head3=head;
}
void print1()
{
    printf("In header 1");
    struct process* ptr=head1;
    while(ptr!=NULL)
    {
        printf("Arrival%d\n",ptr->arrival_time);
        printf("Burst%d\n",ptr->burst_time);
        printf("Priority%d\n",ptr->priority);
        printf("PID%d\n\n",ptr->pid);
        ptr=ptr->next;
    }

}
void print2()
{
    printf("In header 2");
    struct process* ptr=head2;
    while(ptr!=NULL)
    {
        printf("Arrival%d\n",ptr->arrival_time);
        printf("Burst%d\n",ptr->burst_time);
        printf("Priority%d\n",ptr->priority);
        printf("PID%d\n\n",ptr->pid);
        ptr=ptr->next;
    }

}
void print3()
{
    printf("In header 3");
    struct process* ptr=head3;
    while(ptr!=NULL)
    {
        printf("Arrival%d\n",ptr->arrival_time);
        printf("Burst%d\n",ptr->burst_time);
        printf("Priority%d\n",ptr->priority);
        printf("PID%d\n\n",ptr->pid);
        ptr=ptr->next;
    }

}

int main()
{
    int ch=1,a,b,p,p_id;
    while(ch)
    {
        printf("Enter the arrival time");
        scanf("%d",&a);
        printf("Enter the Burst time");
        scanf("%d",&b);
        printf("Enter the priority time");
        scanf("%d",&p);
        printf("Enter the pid time");
        scanf("%d",&p_id);
        inserter(a,b,p,p_id);
        printf("Want to enter more ??");
        scanf("%d",&ch);

    }
    //print1();
    //print2();
    //print3();

}

