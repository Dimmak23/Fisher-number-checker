/*
Thise code is solution of "Fisher Number" challange.

A Fisher number is an integer whose multipliers are
equal to the number's cube. For example, 12 is a Fisher number,
because 12^3 = 2 x 3 x 4 x 6 x 12.

For example:
Input: 12
Output: true (12^3 = 2 x 3 x 4 x 6 x 12)

Input: 8 
Output: false (8^3 != 2 x 4 x 8)

Write a program to check if the user input is a Fisher number
or not.

Bonus: Print all the Fisher numbers in a given range.

______________________________________________________________

Input instructions.

For getting code work you should:

1) Press character (s/S)-for single number checker
or (r/R)-for range searcher and after that press ENTER button.

2) Enter int number if you choose (s/S) and than SUBMIT
or enter first number in the range and that ENTER
and last number in the range and than SUBMIT.
______________________________________________________________

EXAMPLE #1:

For input:
r [ENTER]
1 [ENTER]
50 [SUBMIT]

You will get on the screen:

You choose range-search mode.
Entered first number in the range: 1.
Entered last number in the range: 50.

So, here you got Fisher numbers from 1 to 50:

[1, 12, 18, 20, 28, 32, 44, 45, 50].

Come again, good bye!
______________________________________________________________

EXAMPLE #2:

For input:
S [ENTER]
80730 [SUBMIT]

You will get on the screen:

You choose single number search mode.
Entered 80730 number for analysis.
Success, 80730 - is a Fisher number.

Come again, good bye!

*/
#include <iostream>
#include <cmath>
#include <vector>

class programMode {

	private:

		char option;
		bool mode = false;
		bool approved = true;

	protected:
		// Recursive function for calculating
		// factors multiplication
		int factor(int x, int a){
			if (x <= 1) return 1;
			if (a%x == 0) return x*factor(x-1,a);
			else return factor(x-1,a);
		}
		// Check if multiplication of all numbers a equal
		// to cube of the original number
		bool equaltoCube(int a){
			int b = 1;
			int c = pow(a,2);
			b = factor((a/2),a);
			if (b == c) return true;
			else return false;	
		}

	public:

		bool getMode(){
			return mode;
		}
		bool getApproved(){
			return approved;
		}
		openningMessage(){
			std::cout << "\nChoose your goal of research:"
					  << "\n(s/S) - for varifing single number equal"
					  << " to Fisher number,"
					  << "\n(r/R) - for showing all Fisher numbers "
					  << "in the given range.\n\n";
			std::cin >> option;
		}
		openningMessage(bool validity){
			// Invalid input
			if (!validity)
				std::cout << "\nYou enter " << option
						  << " for research option."
						  << " It's invalid input.\n";
		}
		scanDialog(){
			// Setting range-search mode
			if ( (option == 's') || (option == 'S') ) mode = true;
			// Setting range-search mode
			else if ( (option == 'r') || (option == 'R') ) mode = false;
			// Not allow to program work when input invalid
			else approved = false;
		}
		virtual ~programMode(){
			std::cout << "\nCome again, goodbye!\n";
		}

};

class singleNumber : private programMode {
	
	private:
	int resNumber;

	public:
	singleNumber(){
		std::cout << "\nYou choose single number search mode.";		
	}
	void setNumber(){
		std::cout << "\n\nEnter here number for analysis: ";
		std::cin >> resNumber;
	}
	int getNumber(){
		return resNumber;
	}
	void researchNumber(){
		if (equaltoCube(resNumber))
			std::cout << "\nSuccess, " << resNumber
					  << " - is Fisher number.\n";
		else std::cout << "\nFailure, " << resNumber
					   << " - is not a Fisher number.\n";
	}
	//~singleNumber(){ }

};

class rangeNumbers : private programMode {
	
	private:
	int lRange;
	int rRange;
	std::vector<int> number;
	int size;
	int clear;

	public:
	rangeNumbers(){
		std::cout << "\nYou choose range-search mode.";
	}
	void setRange(){
		std::cout << "\n\nEnter first number in the range: ";
		std::cin >> lRange;
		std::cout << "\nEnter last number in the range: ";
		std::cin >> rRange;
	}
	int getlRange(){
		return lRange;
	}
	int getrRange(){
		return rRange;
	}
	void researchRange(){
		clear = 0;

		for (int j = lRange; j <= rRange; j++)
			if (equaltoCube(j)) number.push_back(j);
		
		size = number.size();

		if (size)
		{
			std::cout << "\nSo, here you got Fisher numbers"
			<< " from " << lRange << " to " << rRange << ":\n\n[";
				for (int j = 0; j < size; j++)
					{
						if (clear++ != 0) std::cout << ',' << '\t';
						if (clear == 7)
							{
								std::cout << '\n';
								clear = 1;
							} 
						std::cout << number[j];
					}
			std::cout << ']' << '.' << '\n';
		}
		else std::cout << "\nUnfortunately, there is not a single"
					   << " Fisher number in the scope.\n";
	}
	//~rangeNumbers(){ }

};

int main(){

	programMode* fisher = new programMode;

	fisher -> openningMessage();
	
	fisher -> scanDialog();

	fisher -> openningMessage(fisher -> getApproved());

	// Single-input mode
	if ( fisher -> getApproved() && fisher -> getMode() ) {
		
		singleNumber* check = new singleNumber;
		check -> setNumber();
		check -> researchNumber();	
	}

	// Range-input mode
	if ( fisher -> getApproved() && !fisher -> getMode() ) {

		rangeNumbers* check = new rangeNumbers;
		check -> setRange();
		check -> researchRange();
	}

	delete fisher;
	
	return 0;
}