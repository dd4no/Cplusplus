// Dave Defourneaux
// Cummulative Time Counter

#include <iostream.h>
#include <stdlib.h>
#include <conio.h>

void main()
{

	int hours = 0;
	int tot_min = 0;
	int tot_sec = 0;
	int track = 0;
	char choice = 'Y';
	
	do
	{	
	int min = 0;
	int sec = 0;
	int remain_s = 0;
	int remain_m = 0;
	
	system ("cls");

	cout << endl << track << " track(s)";
	cout << endl << "--------------";
	cout << endl << hours << " : " << tot_min << " : " << tot_sec;
	cout << endl << "--------------";
	cout << endl << endl << "Enter Minutes: ";
	cin >> min;
	cout << endl << "Enter Seconds: ";
	cin >> sec;
	
	tot_sec += sec;
	if (tot_sec >= 60)
		{
		++tot_min;
		remain_s = tot_sec % 60;
		tot_sec = 0;
		tot_sec += remain_s;
		}
	
	
	tot_min += min;
	if (tot_min >= 60)
		{
		++hours;
		remain_m = tot_min % 60;
		tot_min = 0;
		tot_min += remain_m;
		}
	
	track++;

	cout << endl << endl << track << " track(s)";
	cout << endl << "--------------";
	cout << endl << hours << " : " << tot_min << " : " << tot_sec;
	cout << endl << "--------------";

	cout << endl << endl << "Another Track??? ";
	cin >> choice;
	}while (( choice != 'n') && (choice != 'N'));

	system ("cls");

	cout << endl << "TOTAL" << endl;
	cout << endl << track << " track(s)";
	cout << endl << "--------------";
	cout << endl << hours << " : " << tot_min << " : " << tot_sec;
	cout << endl << "--------------" << endl;

	cout << endl << "Hit any key to end...";
	_getch();

}



