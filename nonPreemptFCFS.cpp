/*
 * FCFS Scheduler Simulator (Non Pre-emptive)
 * By - Mohd. Saqib (Debugging session was really mind boggling, so remember this name)
 */
#include<iostream>
#include<stdlib.h>
#include<pthread.h>
#include<queue>
struct proc_t{
    int bt, arr, wt, tat, rt;
    bool done;
};
using namespace std;
void swap(proc_t &a, proc_t &b){
	proc_t t;
	t=a;
	a=b;
	b=t;
}
void sort(proc_t proc[], int n){
	for (int i=n-1; i>0; --i){
		for(int j=0; j<i; ++j){
			if(proc[j].arr > proc[j+1].arr){
				swap(proc[j], proc[j+1]);
			}
		}
	}
}
int main1()
{
    int n,avwt=0,avtat=0,i;
    proc_t proc[20];
    cout<<"Enter total number of processes(maximum 20):";
    cin>>n;
    cout<<"\nEnter Process Burst Time and arrival time\n";
    for(i=0;i<n;i++)
    {
        cin>>proc[i].bt>>proc[i].arr;
        proc[i].done = false;
        proc[i].rt = proc[i].bt;
    }
    // sort processes by arrival time
	sort(proc, n);
//	for(i=0; i<n; ++i)  // are they sorted?
//		cout<<proc[i].arr<<' ';
//	cout<<endl;
    int t=0, next=0;
    queue<proc_t *> readyq;
    proc_t null;
    null.done=true;  // dummy process
    proc_t *executing;
    executing = &null;  // just to prevent executing->done from failing
    executing->done=true; // dummy process is always done
    while(next<n || !readyq.empty() || !executing->done){  // all process not done OR readyQ is not empty OR process is executing
	    if(t==proc[next].arr){
            readyq.push(&(proc[next]));
            ++next;
	    }
	    if (!readyq.empty() && executing->done){  // processes are available and previous executing process is done
            executing = readyq.front(); // get next
            readyq.pop();
            executing->wt = t-(executing->arr);  // calculate waiting time
            avwt += executing->wt;
	    }
        if(!executing->done){  // execute if not done
            --(executing->rt);
        }
	    ++t;
	    if(executing->rt==0){
            executing->rt=-1;  // so that, control doesn't come back here if there is nothing to execute
            executing->done=true;
            // store Turnaround Time
            executing->tat = t - (executing->arr);
            avtat += executing->tat;
	    }
    }
    cout<<"\nProcess\t\tBurst Time\tArrrival Time\tWaiting Time\tTurnaround Time";
    //calculating turnaround time
    for(i=0;i<n;i++)
    {
        cout<<"\nP["<<i<<"]"<<"\t\t"<<proc[i].bt<<"\t\t"<<proc[i].arr<<"\t\t"<<proc[i].wt<<"\t\t"<<proc[i].tat;
    }
    avwt/=n;
    avtat/=n;
    cout<<"\n\nAverage Waiting Time:"<<avwt;
    cout<<"\nAverage Turnaround Time:"<<avtat;
    return 0;
}
