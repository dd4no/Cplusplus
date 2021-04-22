// Dave Defourneaux
// child's math program

#include <iostream.h>
#include <stdlib.h>

// functions
float add(float, float);
float sub(float, float);
float mul(float, float);
float div(float, float);

// main routine
void main()
{
	// variables 
	float num1 = 0.0;
	float num2 = 0.0;
	float answer = 0.0;
	float solution = 0.0;
	int weapon = 0;
	char choice = 'y';
	
	// execute while choice is not "n" or "N"
	do
	{
		// menu and selecton
		cout << endl <<"     Calculate the Value of Two Numbers" << endl;
		cout << endl <<"   **********CHOOSE YOUR WEAPON**********";
		cout << endl <<"               +   -    *    /           " << endl;
		cout << endl <<"              1) ADDITION";
		cout << endl <<"              2) SUBTRACTION";
		cout << endl <<"              3) MULTIPLICATION";
		cout << endl <<"              4) DIVISION" << endl << endl << ">> ";
		
		cin >> weapon;
		
		// numbers input
		cout << endl << "Enter the first number: ";
		cin >> num1;
		cout << endl << "Enter the second number: ";
		cin >> num2;

		// choose appropriate math routine and calculate solution
		switch (weapon)
		{
		case 1: solution = add(num1, num2); break;
		case 2: solution = sub(num1, num2); break;
		case 3: solution = mul(num1, num2); break;
		case 4: solution = div(num1, num2); break;
		}


AGAIN:  // input user's answer to equation & return location for wrong guess
		cout << endl << endl << "What is your answer? ";
		cin >> answer;

		if ( answer == solution ) cout << endl << "You are correct, sir!!" << endl;
		else 
		{
			cout << endl << "WRONG!!!!" << endl;
			goto AGAIN;
		}
		cout << endl <<" Would you like another? ";
		cin >> choice;
		cout << endl << endl;
		system ("cls");
	}while ((choice != 'n') && (choice != 'N'));
}


// addition routine
float add (float n1, float n2)
{
	float solution = 0.0;
	
	cout << endl << "!!!  ADDITION  !!!" << endl;
	cout << endl << n1 << " + " << n2 << " = ???";

	solution = n1 + n2;
	return solution;
}


// subtraction routine
float sub (float n1, float n2)
{
	float solution = 0.0;

	cout << endl << "!!!  SUBTRACTION  !!!" << endl;
	cout << endl << n1 << " - " << n2 << " = ???";

	solution = n1 - n2;
	return solution;
}


// multiplication routine
float mul (float n1, float n2)
{
	float solution = 0.0;

	cout << endl << "!!!  MULTIPLICATION  !!!"  << endl;
	cout << endl << n1 << " * " << n2 << " = ???";

	solution = n1 * n2;
	return solution;
}


// division routine
float div (float n1, float n2)
{
	float solution = 0.0;

	cout << endl << "!!!  DIVISION  !!!" << endl;
	cout << endl << n1 << " / " << n2 << " = ???";

	solution = n1 / n2;
	return solution;
}

