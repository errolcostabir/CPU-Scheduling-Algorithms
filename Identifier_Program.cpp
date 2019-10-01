#include<iostream>
#include<conio.h>
#include<ctype.h>
#include<string>
using namespace std;
int main()
{
	int n, flag, i;
	string str;
	do {
		cout << "\nEnter the string:  \n";
		cin >> str;
		if ((isalpha(str[0])) || (str[0] == '_'))
		{
			flag = 1;
		}
		else
		{
			flag = 0;
		}
		if (flag == 1)
		{
			for (i = 1; i<str.length(); i++)
			{
				if ((isalnum(str[i]))|| (str[i] == '_')||(str[i]==NULL))
				{
					continue;
				}
				else
				{
					flag = 0;
					break;
				}
			}
		}
		if (flag == 1)
		{
			cout<<"VALID"<<endl;
		}
		else
		{
			cout<<"INVALID"<<endl;
		}
	} while (str != " ");
	_getch();
}