#include<stdio.h>
#include<conio.h>
struct sjf {
	int pid, wt, tat, arrival, burst,fin;
	bool completed = false;
};
void finish_s(struct sjf p[],int n) {
	int smallest_burst, temp_pid, temp_arr;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p[j].burst < p[i].burst) {
				smallest_burst = p[j].burst;
				p[j].burst = p[i].burst;
				p[i].burst = smallest_burst;

				temp_arr = p[j].arrival;
				p[j].arrival = p[i].arrival;
				p[i].arrival = temp_arr;

				temp_pid = p[j].pid;
				p[j].pid = p[i].pid;
				p[i].pid = temp_pid;
			}
		}
	}
	int smallest = p[0].arrival, finish = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[j].arrival < smallest)
			{
				smallest = p[j].arrival;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (p[i].arrival == smallest) {
			p[i].fin = p[i].burst + finish;
			finish = p[i].fin;
			p[i].completed = true;
		}
	}
	for (int i = 0; i < n; i++) {
		if ((p[i].completed != true) && (p[i].arrival > smallest) && (p[i].arrival < finish)) {
			p[i].fin = p[i].burst + finish;
			finish = p[i].fin;
			p[i].completed = true;
		}
	}
}

void print_table(struct sjf p[], int n, float avg_wt, float avg_tat) {
	printf("\nprocess\tarrival\tburst\tfinish\ttat\twt\n");
	for (int j = 0; j < n; j++)
	{
		printf("\np%d\t%d\t%d\t%d\t%d\t%d\n", p[j].pid, p[j].arrival, p[j].burst, p[j].fin, p[j].tat, p[j].wt);
	}
	printf("\nthe avg tat= %f  and avg wt= %f\n", avg_tat, avg_wt);
}

void avg(struct sjf p[], int n) {
	for (int i = 0; i < n; i++)
	{
		p[i].tat = p[i].fin - p[i].arrival;
	}
	for (int i = 0; i < n; i++)
	{
		p[i].wt = p[i].tat - p[i].burst;
	}
	float avg_tat = 0;
	for (int i = 0; i < n; i++)
	{
		avg_tat = p[i].tat + avg_tat;
	}
	avg_tat = avg_tat / n;
	float avg_wt = 0;
	for (int i = 0; i < n; i++)
	{
		avg_wt = p[i].wt + avg_wt;
	}
	avg_wt = avg_wt / n;
	print_table(p, n,avg_wt,avg_tat);
}

void main(){

	struct sjf p[100];
	int n;
	printf("\nenter the number of processes\n");
	scanf_s("%d", &n);
	printf("\nenter the arrival and burst time \n");
	for (int i = 0; i < n; i++) {
		p[i].pid=i;
		scanf_s("%d %d", &p[i].arrival, &p[i].burst);
	}
	finish_s(p, n);
	avg(p, n);
	_getch();
}