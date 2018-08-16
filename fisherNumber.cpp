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
			// Setting single number search mode
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

class singleNumber : public programMode {
	
	protected:

	int resNumber;
	std::vector<int> factors;
	bool result = true;

	// Check if multiplication of all numbers a equal
	// to cube of the original number
	void equaltoCube(int a){
		unsigned long long int b = 1;
		unsigned long long int c = pow(a,2);
		std::vector<int> tempo;
		factors.erase(factors.begin(), factors.end());
		for (int i = 2; (i <= (a/2)); i++)
			if (a%i == 0){
				b *= i;
				tempo.push_back(i);
			}
		factors.insert(factors.begin(),tempo.begin(),tempo.end());
		if (b == c) result = true;
		else result = false;	
	}

	public:

	singleNumber(){
	
	}

	void setNumber(){
		std::cout << "\nYou choose single number search mode.";	
		std::cout << "\n\nEnter here number for analysis: ";
		std::cin >> resNumber;
	}

	int getNumber(){
		return resNumber;
	}

	void researchNumber(){
		equaltoCube(resNumber);
	}

	void closeDialog(){

		if (result)
			std::cout << "\nSuccess, " << resNumber
					  << " - is a Fisher number.\n";
		else std::cout << "\nFailure, " << resNumber
					   << " - is not a Fisher number.\n";	

		std::cout << '\n' << resNumber << "^3";
		if (result) std::cout << ' ';
		else std::cout << ' ' << '!';
		std::cout << '=' << ' ';

		for (auto &it : factors) std::cout << it << ' ' << 'x' << ' ';

		std::cout << resNumber << '.' << '\n';		
	}
	
	~singleNumber(){}

};

class rangeNumbers : public singleNumber {
	
	private:
	int lRange;
	int rRange;
	std::vector<int> number;
	std::vector<std::vector<int>> rfactors;
	int size;
	int clear;

	public:

	rangeNumbers(){

	}

	void setRange(){
		std::cout << "\nYou choose range-search mode.";
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
		for (int j = lRange; j <= rRange; j++){
			equaltoCube(j);
			if (result){
				number.push_back(j);
				rfactors.push_back(factors);
			}			
		}
		size = number.size();
	}

	void closeDialog(){
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
			std::cout << '\n';
			for (int j = 0; j < size; j++){
				std::cout << (j+1) << ". " << number[j] << " ^3 = ";
				for (auto &it : rfactors[j]) std::cout << it << ' ' << 'x' << ' ';
				std::cout << number[j] << '.' << '\n';				
			}
		}
		else std::cout << "\nUnfortunately, there is not a single"
					   << " Fisher number in the scope.\n";
	}
	~rangeNumbers(){}

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
		check -> closeDialog();		
	}

	// Range-input mode
	if ( fisher -> getApproved() && !fisher -> getMode() ) {

		rangeNumbers* check = new rangeNumbers;
		check -> setRange();
		check -> researchRange();
		check -> closeDialog();	
	}

	delete fisher;
	
	return 0;
}