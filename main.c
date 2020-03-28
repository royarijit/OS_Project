#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Declaring the components of a process using a structure type of data
//pid is process id
//priority is the priority of the process in an integer value
//bt is the burst time of the process
//at is the arrival time of the process
//wt is the waiting time of the process
//tt is the turnaround time of the process
struct process{
    int pid,priority,bt,at,wt,tt,rt;
};

//Declaration of the function that will take user input about the various data related to the process
void input_data();

//Declaring a function that will calculate waiting time and the turn around time of the processes
void waiting_time(struct process *q,int);
void turnaround_time(struct process *q,int);


//Declaring the functions for performing the calculation for the waiting and the turnaround time and
//after that we would apply round robin algorithm for the first queue
//we would apply priority scheduling algorithm for the second queue
//we would apply (FCFS) first come first serve algorithm for the third queue
void round_robin();
void priority_scheduling();
void fcfs();


void show_process_data(struct process);
void show_queue(struct process *,int);

//Q1 = Batch Process having Low Priority with FCFS Algorithm
//Q2 = Interactive Process having Medium Priority with Priority Based Sorting
//Q3 = System Process having High Priority with Round Robin Algorith Quantum Time=4

struct process *q1; //This queue is for the low priority processes on which FCFS will be performed
struct process *q2; //This queue is for the medium priority processes on which Priority scheduling will be performed
struct process *q3; //This queue is for the high priority processes on which round robin will be performed

// we have tq of the time quantum = 4
//qn1,qn2,qn3 are the process counts in their respective queues q1,q2,q3 and n is the total number of processes
int qn1=0,qn2=0,qn3=0,n=0,tq=4;

// This function is for taking the user input data about various processes
void input_data(){
    printf("\n Enter no. of processes:\t");
    scanf("%d",&n);

    //after getting the number of input we dynamically allocate memory for each queue
    q1 = (struct process *)malloc(n*sizeof(struct process));
    q2 = (struct process *)malloc(n*sizeof(struct process));
    q3 = (struct process *)malloc(n*sizeof(struct process));
    int i;
    for(i=0;i<n;i++){
        struct process pro;
        pro.pid=i+1;
        printf("\n::::Enter the following data for process%d::::\n\n",i+1);
        printf("Enter arrival time for process P%d: ",pro.pid);
        scanf("%d",&pro.at);
        printf("Enter Priority for process P%d (1-9): ",pro.pid);
        scanf("%d",&pro.priority);
        printf("Enter Burst time for process P%d: ",pro.pid);
        scanf("%d",&pro.bt);
        pro.rt = pro.bt;

        //Now arranging the above provided processes according to their priority in their respective queues
        //priority 0 to 3 goes to q1
        if(pro.priority>0 && pro.priority<=3){
            q1[qn1++]  = pro;
        }
            //priority 4 to 6 goes to q2
        else if(pro.priority>3 && pro.priority<=6){
            q2[qn2++] = pro;
        }
            // rest 7 to 9 goes to q3
        else{
            q3[qn3++] = pro;
        }
    }
}

//Function to calculate waiting time
void waiting_time(struct process *q,int l){
    q[0].wt = 0;
    for(int i=1;i<l;i++){
        q[i].wt = q[i-1].wt + q[i-1].bt;
    }
}

//Function to calculate turn around time
void turnaround_time(struct process *q,int l){
    q[0].wt = 0;
    for(int i=0;i<l;i++){
        q[i].tt = q[i].wt + q[i].bt;
    }
}


//Function to show the details related to the process provided as an argument
void show_process_data(struct process pro){
    printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t%d",pro.pid,pro.priority,pro.at,pro.bt,pro.wt,pro.tt);
}

//Function to show the whole queues on which various algorithms are performed
void show_queue(struct process *q,int l){
    waiting_time(q,l);
    turnaround_time(q,l);
    printf("\n-----------------------------------------------------------------------------------------------------------\n");
    printf("PID\t\tPriority\t\tArrival\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time");
    printf("\n-----------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<l;i++){
        show_process_data(q[i]);
    }
    printf("\n\n");
}


void round_robin_process(struct process *q,int l){
    int t=0;
    int i=0;
    int r=l,flag=0,wait=0,tat=0;
    for(t=0,i=0;r!=0;){
        struct process p = q[i];
        if(p.rt<=tq && p.rt>0){
            t += p.rt;
            p.rt = 0;
            flag = 1;
        }else if(p.rt>tq){
            p.rt -= tq;
            t += tq;
        }
        if(p.rt==0 && flag==1){
            r--;
            wait += t -p.at - p.bt;
            tat += t -p.at;
            flag = 0;
        }

        if(i==r-1){
            i=0;
        }else if(q[i+1].at<t){
            i++;
        }else{
            i=0;
        }

        q[i] = p;
    }
//    printf("\nAverage Waiting Time= %f\n",wait/n);
//    printf("Avg Turnaround Time = %f\n",tat/n);
}
void round_robin(){
    printf("\n\t\tRound Robin\n");
    waiting_time(q3,qn3);
    turnaround_time(q3,qn3);
    round_robin_process(q3,qn3);
    show_queue(q3,qn3);
}


void priority_scheduling_process(struct process *q,int l){
    for(int i=0;i<l;i++){
        for(int j=0;j<l;j++){
            if(q[j].priority>q[i].priority){
                struct process t = q[i];
                q[i] = q[j];
                q[j] = t;
            }
        }
    }
}
void priority_scheduling(){
    printf("\n\t\tPriority Scheduling\n");
    priority_scheduling_process(q2,qn2);
    show_queue(q2,qn2);
}


void fcfs_process(struct process *q,int l){
    for(int i=0;i<l;i++){
        for(int j=0;j<l;j++){
            if(q[j].at>q[i].at){
                struct process t = q[i];
                q[i] = q[j];
                q[j] = t;
            }
        }
    }
}
void fcfs(){
    printf("\n\t\tFirst Come First Serve\n");
    fcfs_process(q1,qn1);
    show_queue(q1,qn1);
}
int main(){
    input_data();
    int i=1;
    for(i=1;i<=3;i++){
        switch(i){
            case 3:
                round_robin();
                break;
            case 2:
                priority_scheduling();
                break;
            case 1:
                fcfs();
                break;
            default:
                printf("done");
        }
        sleep(10);

    }
    printf("\n\n");
}
