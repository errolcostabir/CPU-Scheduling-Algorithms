#include<stdio.h>
#include<conio.h>
struct fcfs {
	int pid, fin, arrival, burst, tat, wt;// avg_tat, avg_wt;
};
void finish_s(struct fcfs p[],int n) {
	int finish = 0;
	for (int i = 0; i < n; i++) {
		if (p[i].arrival == 0) {
			p[i].fin = p[i].burst + finish;
			finish = p[i].fin;
		}
		else if ((p[i].arrival > 0) && (p[i].arrival < finish)) {
			p[i].fin = p[i].burst + finish;
			finish = p[i].fin;
		}
	}
}
void print_table(struct fcfs p[], int n, float avg_tat, float avg_wt) {
	printf("\nprocess\tarrival\tburst\tfinish\ttat\twt\n");
	for (int j = 0; j < n; j++)
	{
		printf("\np%d\t%d\t%d\t%d\t%d\t%d\n", p[j].pid, p[j].arrival, p[j].burst, p[j].fin, p[j].tat, p[j].wt);
	}
	printf("\nthe avg tat= %f  and avg wt= %f\n", avg_tat, avg_wt);

}
void avt_tat(struct fcfs p[],int n) {
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
	print_table(p, n,avg_tat,avg_wt);
}


int main() {
	struct fcfs p[100];
	int n;
	printf("\nenter the number of processes\n");
	scanf_s("%d", &n);
	printf("\nenter the arrival and burst  time\n");
	for (int i = 0; i < n; i++) {
		p[i].pid = i;
		scanf_s("%d %d", &p[i].arrival, &p[i].burst);
	}

	int temp_arrival;
	int temp_pid;
	int temp_burst;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p[j].arrival < p[i].arrival) {
				temp_arrival = p[i].arrival;
				p[i].arrival = p[j].arrival;
				p[j].arrival = temp_arrival;

				temp_burst = p[i].burst;
				p[i].burst = p[j].burst;
				p[j].burst = temp_burst;

				temp_pid = p[i].pid;
				p[i].pid = p[j].pid;
				p[j].pid = temp_pid;

			}
		}
	}
	finish_s(p, n);
	avt_tat(p, n);
	
	
	_getch();
}
