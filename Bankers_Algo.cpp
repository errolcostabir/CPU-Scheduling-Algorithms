#include<iostream>
#include<conio.h>
using namespace std;

int p[10];
int i, j, n, m;
int allocation[10][10];
int MAX[10][10];
int available[10];
int need[10][10];

void calculate_sequence() {
	int work[100];
	int flag = 0;
	bool finish[100];
	int k = 0;
	int sequence[10];
	for (i = 0; i < n; i++) {
		finish[i] = false;
	}
	for (i = 0; i < m; i++) {
		work[i] = available[i];
	}
	int g = 0;
	bool complete = false;
	int deadlock = 0;
	for(k=0;k<n;k++){
		for (i = 0; i < n; i++) {
			if (finish[i] == false) {
				flag = 1;
				for (j = 0; j < m; j++) {
					if (need[i][j] <= work[j]) {
						flag = 1;
					}
					else {
						flag = 0;
						break;
					}
				}

				if (flag == 1) {
					sequence[g] = i;
					g++;
					for (j = 0; j < m; j++) {
						work[j] += allocation[i][j];
						finish[i] = true;
					}
				}
			}
		}

		if (g == n) {
			complete = true;
			deadlock = 0;
		}
		else {
			deadlock = 1;
		}
	}


	if (deadlock == 0) {
		cout << "the safe sequence is" << endl << "<";
		for (i = 0; i < n; i++) {
			cout << sequence[i] << " ";
		}
		cout << ">";
	}
	else {
		cout << "DAEDlock" << endl;
	}
	
}

void need_fun() {
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			need[i][j] = MAX[i][j] - allocation[i][j];
		}
	}
	cout << "the NEED MAtrix is" << endl;
	for (i = 0; i < n; i++) {
		cout << "p[" << i << "]" << ": ";
		for (j = 0; j < m; j++) {
			cout << need[i][j] << " ";
		}
		cout << endl;
	}
	calculate_sequence();
}

void inputmatrix() {
	cout << "Enter the row and colums of matrix" << endl;
	cin >> n >> m;
	cout << "enter the elenmnst of ALLOCATION matrix" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> allocation[i][j];
		}
	}
	cout << "enter the elenmnst of MAX matrix" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> MAX[i][j];
		}
	}
	cout << "enter the elenmnst of AVAILABLE matrix" << endl;
	for (i = 0; i < m; i++) {
		cin >> available[i];
	}
	need_fun();
}

int main() {
	inputmatrix();
	_getch();
}


