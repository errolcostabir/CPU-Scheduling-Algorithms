#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
int i, j;

struct priority {
	int burst_time;
	int arrival_time;
	int priority;
	int pid;
	int tat;
	int wt;
	int fin;
	bool completed;
};
//calculate the finish time of each process
void finish_time(struct priority p[],int n) {
	int finish_t=0;
	int flag = 0;
	int temp_pid, temp_arival, temp_priority, temp_burst;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (p[i].priority > p[j].priority) {
				temp_priority = p[i].priority;
				p[i].priority = p[j].priority;
				p[j].priority = temp_priority;

				temp_arival = p[i].arrival_time;
				p[i].arrival_time = p[j].arrival_time;
				p[j].arrival_time = temp_arival;

				temp_burst = p[i].burst_time;
				p[i].burst_time = p[j].burst_time;
				p[j].burst_time = temp_burst;

				temp_pid = p[i].pid;
				p[i].pid = p[j].pid;
				p[j].pid = temp_pid;
			}
		}
	}
	int smallest_arrival=p[0].arrival_time;
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if (p[i].arrival_time > p[j].arrival_time) {
				smallest_arrival = p[j].arrival_time;
			}
		}
	}

	
	for (i = 0; i < n; i++) {
		if ((p[i].arrival_time == smallest_arrival)&&(p[i].completed==false)) {
			finish_t += p[i].burst_time;
			p[i].completed = true;
			p[i].fin = finish_t;
		}
	}

	do {
		for (i = 0; i < n; i++) {
			if ((p[i].arrival_time < finish_t)&&(p[i].completed!=true)) {
				finish_t += p[i].burst_time;
				p[i].completed = true;
				p[i].fin = finish_t;
			}
		}

		for (i = 0; i < n; i++) {
			if (p[i].completed == true) {
				flag = 1;
			}
			else {
				flag = 0;
			}
		}
	} while (flag != 1);

}
//print the table
void print_table(struct priority p[],int n,float avg_wt,float avg_tat) {
	printf("\nprocess\tarrival\tburst\tpriority\tfinish\ttat\twt\n");
	for (j = 0; j < n; j++)
	{
		printf("\np%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[j].pid, p[j].arrival_time, p[j].burst_time,p[j].priority,p[j].fin, p[j].tat, p[j].wt);
	}
	printf("\nthe avg tat= %f  and avg wt= %f\n", avg_tat, avg_wt);
}
//calculate the avg tat and avg wt
void avg_t(struct priority p[],int n) {
	for (i = 0; i < n; i++)
	{
		p[i].tat = p[i].fin - p[i].arrival_time;
	}
	for (i = 0; i < n; i++)
	{
		p[i].wt = p[i].tat - p[i].burst_time;
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
	print_table(p,n, avg_wt, avg_tat);
}
//main function
void main() {
	int n;
	struct priority p[100];
	printf("enter the number of processes\n");
	scanf_s("%d", &n);

	printf("enter the BURST & ARRIVAL time of the processes\n");
	for (i = 0; i < n; i++) {
		p[i].pid = i;
		p[i].completed = false;
		scanf_s("%d %d", &p[i].burst_time,&p[i].arrival_time);
	}

	printf("enter the PRIORITY of the processes\n");
	for (i = 0; i < n; i++) {
		scanf_s("%d", &p[i].priority);
	}
	
	finish_time(p,n);
	avg_t(p,n);
	_getch();
}