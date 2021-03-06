#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<malloc.h>
COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left cornor of the screen
 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
int total_running_time=0;
int a[100],acount;
acount=0;
char out[1000],temp1[20],temp2[20];
struct process{
    int pid,burst_time,priority,waiting_time,last_ran,burst1;
    struct process* next;
};
int count=0;
struct process* head1=NULL;
struct process* head2=NULL;
struct process* head3=NULL;
void priority_inserter(int pid,int burst,int p)
{
    count++;
    struct process* newnode=(struct process*)malloc(sizeof(struct process));
    newnode->burst_time=burst;
    newnode->pid=pid;
    newnode->priority=p;
    newnode->waiting_time=0;
    newnode->burst1=burst;
    newnode->last_ran=0;
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
    strcat(out,"|");
    int ch=1;
    int pid,priority,burst;
    while(ch)
    {
        system("cls");
        printf("\nEnter Pid for the process ");
        scanf("%d",&pid);
        printf("\nEnter Burst Time for the process ");
        scanf("%d",&burst);
        if(burst<=0)
        {
            printf("The burst time cannot be less than 0\nPlease enter again");
            Sleep(2000);
            continue;
        }
        printf("\nEnter priority of the process ");
        scanf("%d",&priority);
        if(priority<0||priority>16)
        {
            printf("You have entered priority higher than the range!!!\nPlease enter again\n");
            Sleep(2000);
            continue;
        }
        if(priority>=6 &&priority<=10)
            priority_inserter(pid,burst,priority);
        else{
            struct process* newnode=(struct process*)malloc(sizeof(struct process));
            newnode->pid=pid;
            newnode->burst_time=burst;
            newnode->priority=priority;
            newnode->waiting_time=0;
            newnode->burst1=burst;
            newnode->last_ran=0;
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
                       count++;
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
                        count++;
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
    //printf("\nDoing Round Robin\n");
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

            //printf("Current time is %d,last ran on %d\n",total_running_time,ptr->last_ran);
            ptr->waiting_time+=total_running_time-ptr->last_ran;
            printf("%d\t\t\tP%d\t\t\t",total_running_time,ptr->pid);
            sprintf(temp1,"    %d   | ",ptr->pid);
            strcat(out,temp1);
            a[acount]=total_running_time;
            acount++;
            //printf("Process with pid %d is completed\n",ptr->pid);
            total_time-=ptr->burst_time;
            total_running_time+=ptr->burst_time;
            ptr->last_ran=total_running_time;
            printf("%d\n",total_running_time);
            a[acount]=total_running_time;
            acount++;
            ptr->burst_time=0;
            if(ptr->next==NULL)
                ptr=head1;
            else
                ptr=ptr->next;
        }
        else if(tq<=total_time&&tq<ptr->burst_time)
        {
            //printf("Current time is %d,last ran on %d\n",total_running_time,ptr->last_ran);
            ptr->waiting_time+=total_running_time-ptr->last_ran;
            printf("%d\t\t\tP%d\t\t\t",total_running_time,ptr->pid);
            sprintf(temp1,"    %d   | ",ptr->pid);
            strcat(out,temp1);
            a[acount]=total_running_time;
            acount++;
            //printf("Process with pid %d executed for 4 units of time \n",ptr->pid);
            total_time-=tq;
            ptr->burst_time-=tq;
            total_running_time+=4;
            ptr->last_ran=total_running_time;
            printf("%d\n",total_running_time);
            a[acount]=total_running_time;
            acount++;
            if(ptr->next==NULL)
                ptr=head1;
            else
                ptr=ptr->next;
        }
        else{
            //printf("Current time is %d,last ran on %d\n",total_running_time,ptr->last_ran);
            ptr->waiting_time+=total_running_time-ptr->last_ran;
            printf("%d\t\t\tP%d\t\t\t",total_running_time,ptr->pid);
            sprintf(temp1,"    %d   | ",ptr->pid);
            strcat(out,temp1);
            a[acount]=total_running_time;
            acount++;
            ptr->burst_time-=total_time;
            total_running_time+=total_time;
            ptr->last_ran=total_running_time;
            printf("%d\n",total_running_time);
            a[acount]=total_running_time;
            acount++;
            total_time=0;
        }

    }
}
void priority()
{
    if(isEmpty(head2))
        return;
    //printf("Doing priority\n");
    struct process* ptr=head2;
    int total_time=10;
    while(total_time>0)
    {
        if(isExhausted(head2))
        {
            return;
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
      //      printf("Current time is %d,last ran on %d\n",total_running_time,ptr->last_ran);
            ptr->waiting_time+=total_running_time-ptr->last_ran;
            printf("%d\t\t\tP%d\t\t\t",total_running_time,ptr->pid);
            sprintf(temp1,"    %d   | ",ptr->pid);
            strcat(out,temp1);
            a[acount]=total_running_time;
            acount++;
            total_time-=ptr->burst_time;
            total_running_time+=ptr->burst_time;
            ptr->last_ran=total_running_time;
            printf("%d\n",total_running_time);
            a[acount]=total_running_time;
            acount++;
            ptr->burst_time=0;
            if(ptr->next==NULL)
                ptr=head2;
            else
                ptr=ptr->next;
        }
        else{
          //  printf("Current time is %d,last ran on %d\n",total_running_time,ptr->last_ran);
            ptr->waiting_time+=total_running_time-ptr->last_ran;
            printf("%d\t\t\tP%d\t\t\t",total_running_time,ptr->pid);
            sprintf(temp1,"    %d   | ",ptr->pid);
            strcat(out,temp1);
            a[acount]=total_running_time;
            acount++;
            ptr->burst_time-=total_time;
            total_running_time+=total_time;
            ptr->last_ran=total_running_time;
            printf("%d\n",total_running_time);
            a[acount]=total_running_time;
            acount++;
            total_time=0;
        }
    }
}
void fcfs()
{
    if(isEmpty(head3))
        return;
    //printf("Doing first come first serve\n");
    struct process* ptr=head3;
    int total_time=10;
    while(total_time>0)
    {
        if(isExhausted(head3))
        {
            return;
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
      //      printf("Current time is %d,last ran on %d\n",total_running_time,ptr->last_ran);
            ptr->waiting_time+=total_running_time-ptr->last_ran;
            printf("%d\t\t\tP%d\t\t\t",total_running_time,ptr->pid);
            sprintf(temp1,"    %d   | ",ptr->pid);
            strcat(out,temp1);
            a[acount]=total_running_time;
            acount++;
            total_time-=ptr->burst_time;
            total_running_time+=ptr->burst_time;
            ptr->last_ran=total_running_time;
            printf("%d\n",total_running_time);
            a[acount]=total_running_time;
            acount++;
            ptr->burst_time=0;
            if(ptr->next==NULL)
                ptr=head3;
            else
                ptr=ptr->next;
        }
        else{
          //  printf("Current time is %d,last ran on %d\n",total_running_time,ptr->last_ran);
            ptr->waiting_time+=total_running_time-ptr->last_ran;
            printf("%d\t\t\tP%d\t\t\t",total_running_time,ptr->pid);
            sprintf(temp1,"    %d   | ",ptr->pid);
            strcat(out,temp1);
            a[acount]=total_running_time;
            acount++;
            ptr->burst_time-=total_time;
            total_running_time+=total_time;
            ptr->last_ran=total_running_time;
            printf("%d\n",total_running_time);
            a[acount]=total_running_time;
            acount++;
            total_time=0;
        }
    }
}

void print1()
{
    printf("\n\nPID\t\tBurst Time\t\tPriority\t\tWaiting time\n-----------------------------------------------------------------------------\n");
    struct process* ptr=head1;
    while(ptr!=NULL)
    {
        printf("%d\t\t%d\t\t\t%d\t\t\t%d\n",ptr->pid,ptr->burst1,ptr->priority,ptr->waiting_time);
        ptr=ptr->next;
    }
    ptr=head2;
    while(ptr!=NULL)
    {
        printf("%d\t\t%d\t\t\t%d\t\t\t%d\n",ptr->pid,ptr->burst1,ptr->priority,ptr->waiting_time);
        ptr=ptr->next;
    }
    ptr=head3;
    while(ptr!=NULL)
    {
        printf("%d\t\t%d\t\t\t%d\t\t\t%d\n",ptr->pid,ptr->burst1,ptr->priority,ptr->waiting_time);
        ptr=ptr->next;
    }

}

void total_waiting_time_calculator()
{
    int time=0,turn_around=0;
    struct process* ptr=head1;
    while(ptr!=NULL)
    {
        time+=ptr->waiting_time;
        turn_around+=ptr->burst1+ptr->waiting_time;
        ptr=ptr->next;
    }
    ptr=head2;
    while(ptr!=NULL)
    {
        time+=ptr->waiting_time;
        turn_around+=ptr->burst1+ptr->waiting_time;
        ptr=ptr->next;
    }
    ptr=head3;
    while(ptr!=NULL)
    {
        time+=ptr->waiting_time;
        turn_around+=ptr->burst1+ptr->waiting_time;
        ptr=ptr->next;
    }
    printf("\nThe Total waiting time is %d\nTotal Turn around time is %d\n",time,turn_around);
    float avg_time,avg_turn_around;
    avg_time=(float)time/count;
    avg_turn_around=(float)turn_around/count;
    printf("\nAverage waiting time is %f\nAverage turn around time is %f\n",avg_time,avg_turn_around);
}
void gantt_printer()
{
    int x=0,y=1;
    int i=0,j=0;
    int pipe[30];
    int pipecount=0;
    y=3;
    for(int i=0;i<strlen(out);i++)
    {
        if(isdigit(out[i])||out[i]==124)
        {
            gotoxy(x,y);
            printf("%c",out[i]);
            pipe[pipecount]=x;
            pipecount++;
            x+=4;

        }

    }
    y=2;
    //printf("%d",pipe[pipecount-1]);
    for(int i=0;i<pipe[pipecount-1];i++)
    {
        gotoxy(i,y);
        printf("~");
        gotoxy(i,y+2);
        printf("~");
    }
    x=0;
    y=5;
    i=0;
    j=0;
    for(i=0;i<acount;i+=2)
    {
        gotoxy(pipe[j],y);
        printf("%d",a[i]);
        j+=2;
    }
    gotoxy(pipe[j],y);
    printf("%d",total_running_time);
}
int main()
{
    printf("Welcome to Multi Level Queue Scheduling\nQueue 1 using Round Robin\t\tPriority Range 1-5\nQueue 2 using Priority Scheduling\tPriority Range 6-10\nQueue 3 using FCFS Scheduling\t\tPriority Range 11-15\n");
    system("pause");
    inserter();
    system("cls");
    printf("\n\nStarting time\t\tPid\t\tEnd Time\n-------------------------------------------------\n");
    while(!isExhausted(head1)||!isExhausted(head2)||!isExhausted(head3))
    {
            round_robin();
            priority();
            fcfs();
    }
    printf("Total time taken=%d\n",total_running_time);
    print1();
    system("pause");
    system("cls");
    printf("Gantt Chart");
    gantt_printer();
    total_waiting_time_calculator();
}
/*
1
10
2
1
2
12
4
1
3
5
9
1
4
15
6
1
5
9
12
1
6
19
14
0
*/

