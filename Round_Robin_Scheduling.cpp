#include<stdio.h>
#include<conio.h>
#define MAX 100
int queue[MAX];
int i,j,time = 0, front = 0, rear = 0, queue_count = 0;
struct rr {
	int arrival, fin, burst, tat, wt, pid;
};
void insert(int value) {
	queue[rear++] = value;
}
int del() {
	int x;
	x = queue[front++];
	return x;
}
//to check if process has arrived
void check(struct rr p[],int n) {
	while (p[j].arrival <= time&&j<n) {
		queue_count++;
		insert(j++);
	}
}
void finish_s(struct rr p[], int quantum,int n) {
	//finding total burst time
	int total_burst=0;
	for (i = 0; i < n; i++) {
		total_burst = p[i].burst + total_burst;
	}
	
	int temp_st[MAX], flag = 0, count = 0, proc;
	j = 0;
	//store the burst time in temporary variable
	for (i = 0; i<n; i++) {
		temp_st[i] = p[i].burst;
	}
	time = p[0].arrival;
	queue_count = 1; //queue_count to check if queue is empty 
	insert(j++);
	while (time <= total_burst) {
		if (flag == 1 || queue_count != 0) {  //flag to check if process isunder execution
			if (flag == 0 && count == 0) {
				proc = del();
				count = 0;
				flag = 1;
			}
			temp_st[proc]--;
			if (temp_st[proc] == 0) {
				time++;
				count = 0;
				p[proc].fin = time;
				flag = 0;
				queue_count--;
				check(p,n);
				continue;
			}
			count++;
			if (count == quantum) {
				count = 0;
				time++;
				check(p,n);
				insert(proc);
				flag = 0;
			}
			else {
				time++;
				check(p,n);
			}
		}
		else {
			time++;
			check(p,n);
		}
	}
}

void print_table(struct rr p[],int n,float avg_tat,float avg_wt) {
	printf("\nprocess\tarrival\tburst\tfinish\ttat\twt\n");
	for (j = 0; j < n; j++)
	{
		printf("\np%d\t%d\t%d\t%d\t%d\t%d\n", p[j].pid, p[j].arrival, p[j].burst, p[j].fin, p[j].tat, p[j].wt);
	}
	printf("\nthe avg tat= %f  and avg wt= %f\n", avg_tat, avg_wt);

}

void avt_tat(struct rr p[],int n) {
	for (i = 0; i < n; i++)
	{
		p[i].tat = p[i].fin - p[i].arrival;
	}
	for (i = 0; i < n; i++)
	{
		p[i].wt = p[i].tat - p[i].burst;
	}
	float avg_tat = 0;
	for (i = 0; i < n; i++)
	{
		avg_tat = p[i].tat + avg_tat;
	}
	avg_tat = avg_tat / n;
	float avg_wt = 0;
	for (i = 0; i < n; i++)
	{
		avg_wt = p[i].wt + avg_wt;
	}
	avg_wt = avg_wt / n;
	print_table(p,n,avg_tat, avg_wt);
}

void main() {
	
	int n;
	struct rr p[MAX];
	printf("\nentre the number of processes\n");
	scanf_s("%d", &n);
	printf("\nenter the arrival and burst time\n");
	for (i = 0; i < n; i++) {
		p[i].pid = i;
		scanf_s("%d %d", &p[i].arrival, &p[i].burst);
	}
	int quantum;
	printf("\nenter the quantum time\n");
	scanf_s("%d", &quantum);

	//sorting
	int temp_arr, temp_burst, temp_pid;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (p[j].arrival < p[i].arrival) {
				temp_arr = p[i].arrival;
				p[i].arrival = p[j].arrival;
				p[j].arrival = temp_arr;

				temp_burst = p[i].burst;
				p[i].burst = p[j].burst;
				p[j].burst = temp_burst;

				temp_pid = p[i].pid;
				p[i].pid = p[j].pid;
				p[j].pid = temp_pid;

			}
		}
	}
	//to find finish time of each process
	finish_s(p, quantum,n);
	//to find avg_tat and avg_wt of process
	avt_tat(p,n);
	_getch();
}



