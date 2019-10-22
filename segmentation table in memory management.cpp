//implement segmentation memory management program
#include<iostream>
#include<conio.h>
#define MAX 100
using namespace std;

int limit[MAX];
int base[MAX];
int logical[MAX];
int physical[MAX];
int n;

void calculate_physical_address() {
	int seg_no;
	int logical_add;
	do {
		cout << "enter the segment number and logical address------->(-1,-1) to quit:  ";
		cin >> seg_no >> logical_add;
		if (seg_no == -1 && logical_add == -1) {
			cout << "user terminated program...... :(" <<endl;
			break;
		}
		else {
			if (seg_no > n) {
				cout << "segment number overbound " << endl;
			}
			else {
				if (logical_add < limit[seg_no]) {
					physical[seg_no] = logical_add + base[seg_no];
					cout << "segment<" << seg_no << ">---->  " << "physical address: " << physical[seg_no] << endl;

				}
				else {
					cout << "segment<" << seg_no << ">---->  " << "adressing error" << endl;
				}
			}
		}
	} while ((seg_no != -1) && (logical_add != -1));
}

void segment_table(int n) {
	cout << "enter the base address values corresponding to the segemnt number::" << endl;
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		cin >> base[i];
	}
	cout << "enter the limit values corresponding to the segment number::" << endl;
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		cin >> limit[i];
	}
	calculate_physical_address();
}

int main()
{
	cout << "enter the size of the segment table" << endl;
	cin >> n;
	segment_table(n);
	_getch();
}