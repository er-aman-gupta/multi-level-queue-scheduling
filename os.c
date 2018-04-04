#include<stdio.h>
#include<malloc.h>
struct process{
    int pid,burst_time,priority;
    struct process* next;
};
struct process* head1=NULL;
struct process* head2=NULL;
struct process* head3=NULL;
void priority_inserter(int pid,int burst,int p)
{
    struct process* newnode=(struct process*)malloc(sizeof(struct process));
    newnode->burst_time=burst;
    newnode->pid=pid;
    newnode->priority=p;
    newnode->next=NULL;
    if(head2==NULL)
    {
        head2=newnode;
    }
    else{
    struct process* ptr=head2;
        if(head2->priority>p)
        {
            newnode->next=head2;
            head2=newnode;

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
}

void inserter()
{

    int ch=1;
    int pid,priority,burst;
    while(ch)
    {
        printf("\nEnter Pid for the process ");
        scanf("%d",&pid);
        printf("\nEnter Burst Time for the process ");
        scanf("%d",&burst);
        printf("\nEnter priority of the process ");
        scanf("%d",&priority);
        if(priority>=6 &&priority<=10)
            priority_inserter(pid,burst,priority);
        else{
            struct process* newnode=(struct process*)malloc(sizeof(struct process));
            newnode->pid=pid;
            newnode->burst_time=burst;
            newnode->priority=priority;
            newnode->next=NULL;
            switch(priority)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:{
                            if(head1==NULL)
                            {
                                head1=newnode;
                            }
                            else{
                                struct process* ptr=head1;
                                while(ptr->next!=NULL)
                                {
                                    ptr=ptr->next;
                                }
                                ptr->next=newnode;
                            }
                       }
                       break;
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:{
                            if(head3==NULL)
                            {
                                head3=newnode;
                            }
                            else{
                                struct process* ptr=head3;
                                while(ptr->next!=NULL)
                                {
                                    ptr=ptr->next;
                                }
                                ptr->next=newnode;
                            }
                        }
                        break;
            }
        }
        printf("Want to enter more??");
        scanf("%d",&ch);
    }
}
int isEmpty(struct process* head)
{
    if(head==NULL)
        return 1;
    else return 0;
}
int isExhausted(struct process* head)
{
    struct process* ptr=head;
    if(isEmpty(head))
        return 1;
    else{
        while(ptr!=NULL)
        {
            if(ptr->burst_time!=0)
                return 0;
            ptr=ptr->next;
        }
    }
    return 1;
}
void round_robin()
{
    if(isEmpty(head1))
        return;
    printf("\nDoing Round Robin");
    struct process* ptr=head1;
    int tq=4,total_time=10;
    while(total_time>0)
    {
        if(isExhausted(head1))
            return;
        if(ptr->burst_time==0)
        {
            if(ptr->next==NULL)
                ptr=head1;
            else
                ptr=ptr->next;
            continue;
        }
        if(tq<=total_time&&tq>=ptr->burst_time)
        {
            printf("Process with pid %d is completed\n",ptr->pid);
            total_time-=ptr->burst_time;
            ptr->burst_time=0;
            if(ptr->next==NULL)
                ptr=head1;
            else
                ptr=ptr->next;
        }
        else if(tq<=total_time&&tq<ptr->burst_time)
        {
            printf("Process with pid %d executed for 4 units of time \n",ptr->pid);
            total_time-=tq;
            ptr->burst_time-=tq;
            if(ptr->next==NULL)
                ptr=head1;
            else
                ptr=ptr->next;
        }
        else{
            printf("Process with pid %d executed for %d units of time \n",ptr->pid,total_time);
            ptr->burst_time-=total_time;
            total_time=0;
        }

    }
}
void priority()
{
    if(isEmpty(head2))
        return 1;
    printf("Doing priority\n");
    struct process* ptr=head2;
    int total_time=10;
    while(total_time>0)
    {
        if(isExhausted(head2))
        {
            return 1;
        }
        if(ptr->burst_time==0)
        {
            if(ptr->next==NULL)
                ptr=head2;
            else
                ptr=ptr->next;
            continue;
        }
        if(total_time>=ptr->burst_time)
        {
            printf("Process with pid %d is completed\n",ptr->pid);
            total_time-=ptr->burst_time;
            ptr->burst_time=0;
            if(ptr->next==NULL)
                ptr=head2;
            else
                ptr=ptr->next;
        }
        else{
            printf("Process with pid %d executed for %d units of time \n",ptr->pid,total_time);
            ptr->burst_time-=total_time;
            total_time=0;
        }
    }
}
void fcfs()
{
    if(isEmpty(head3))
        return 1;
    printf("Doing first come first serve\n");
    struct process* ptr=head3;
    int total_time=10;
    while(total_time>0)
    {
        if(isExhausted(head3))
        {
            return 1;
        }
        if(ptr->burst_time==0)
        {
            if(ptr->next==NULL)
                ptr=head3;
            else
                ptr=ptr->next;
            continue;
        }
        if(total_time>=ptr->burst_time)
        {
            printf("Process with pid %d is completed\n",ptr->pid);
            total_time-=ptr->burst_time;
            ptr->burst_time=0;
            if(ptr->next==NULL)
                ptr=head3;
            else
                ptr=ptr->next;
        }
        else{
            printf("Process with pid %d executed for %d units of time \n",ptr->pid,total_time);
            ptr->burst_time-=total_time;
            total_time=0;
        }
    }
}

/*void print1()
{
    struct process* ptr=head3;
    while(ptr!=NULL)
    {
        printf("\npid %d",ptr->pid);
        ptr=ptr->next;
    }
}*/
int main()
{
    inserter();

    while(!isExhausted(head1)||!isExhausted(head2)||!isExhausted(head3))
    {
            round_robin();
    priority();
    fcfs();
    }
}

/*
1
24
1
1
2
3
2
1
3
23
6
1
4
11
7
1
5
36
11
1
6
25
15
0
*/
