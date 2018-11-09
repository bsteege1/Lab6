
// SortedDriver.cpp
// Brandon Steege
//Lab6


// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	int count(0); //count used to compare to size of vector
	double iso; // variable used to hold delta
	double minimum; // variable that holds minimum delta
	vector<double> isolated;
	while (count < number.size())
	{
		if (count == 0) //used for initial value in vector
		{
			iso = abs(number.at(count) - number.at(count + 1));//initializes iso to be the delta value
			isolated.push_back(iso); //adds iso to new vector
		}
		else if(count < (number.size() - 1)) //used rest of values excluding last value in vector
		{
			minimum = abs(number.at(count) - number.at(count - 1)); //minimum initialized to be prev delta
			iso = abs(number.at(count) - number.at(count + 1)); //iso initialized to be next delta
			if (minimum < iso)
			{
				isolated.push_back(minimum);//pushes back smaller value
			}
			else
			{
				isolated.push_back(iso);//pushes back smaller value
			}
		}
		else
		{
			isolated.push_back((abs(number.at(count)- number.at(count - 1))));//pushes back last value's delta
		}
		count++; //increments count
	}
	
	double tempMax(0); //used for comparing
	double location; //used to store the location of the greatest delta

	for (int i(1); i < (isolated.size()); i++) //this loop compares current value with tempmax to determine the greates delta
	{
		if (isolated.at(i) > tempMax)
		{
			tempMax = isolated.at(i);
			location = number.at(i);
		}
	}

	return location;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	int count(0);//value used to caount number of times two of the same values exist
	for (list<string>::iterator itA = A.begin(), itB = B.begin(); itA != A.end() && itB != B.end();)
	{
		if (*itA < *itB)//compares both pointers
		{
			itA++; //iterates to next location in a 
		}
		else if (*itA > *itB)//compares both pointers
		{
			itB++; //iterates to next location in b
		}
		else
		{
			itA++; //iterates to next location in a 
			count++; //increments count
		}
	}
	return (A.size() - count);//returens number of different values in two lists
}

int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
