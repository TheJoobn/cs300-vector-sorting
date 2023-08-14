2/*
█░█ █▀▀ █▀▀ ▀█▀ █▀█ █▀█ █▀ █▀█ █▀█ ▀█▀ █ █▄░█ █▀▀ ░ █▀▀ █▀█ █▀█
▀▄▀ ██▄ █▄▄ ░█░ █▄█ █▀▄ ▄█ █▄█ █▀▄ ░█░ █ █░▀█ █▄█ ▄ █▄▄ █▀▀ █▀▀*/
//============================================================================
// Name        : VectorSorting.cpp

// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE

/* Author: Jaden Knutson - Created Options: 3, 4, 5, and 6 for user menu.
						 - Created Functions: Partition, quickSort, and selectionSort */

						 /* Log:			5/10/2023	10am - starting setup and structure
										 5/11/2023	3am - created functions and option 3 & 4
										 5/12/2023	2pm - Created options 5 & 6 for file switching*/

										 /* Description: Vector Sorting Algorithms -
														 This program allows the user to pass in the path to a bid CSV file that can then be
														 loaded by entering "1" at the menu. Once the file file is loaded, the user can choose
														 between different menu items such as display all bids (option 2), selection sort the bids (option 3),
														 and quick sort all bids (option 4). By default, the initial CSV file is: eBid_Monthly_Sales_Dec_2016.csv.
														 When the user wants to end the program, they must enter "9".

														 5/12/23  - I have added in menu options 5 and 6 so the user can choose between the two bid files.
														 Option 5 - Switches the load directory to: eBid_Monthly_Sales.csv
														 Option 6 - Switches the load directory to: eBid_Monthly_Sales_Dec_2016.csv
																  - Once the new directory is switched, the user can reload by entering "1" and can now sort/display the new file.

										 File Names:
												 //eBid_Monthly_Sales.csv		   - 12024  lines
												 //eBid_Monthly_Sales_Dec_2016.csv  - 77	    line
												 /*VectorSorting.exe eBid_Monthly_Sales.csv - pass file name to program directly as a paramete at the command line or
																							- OR pass a bidld after the file name */

																							/*================================================================================================================================*/
#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"
using namespace std;

//============================================================================
//Function Library:	 pre-initializing functions
double strToDouble();
void displayBid();
double strToDouble();

//Newly created functions - 5/10/2023
int partition();
void quickSort();
void selectionSort();

/*================================================================================================================================*/
//============================================================================
// Global definitions visible to all methods and classes
//============================================================================
// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

//============================================================================
// Static methods used for testing
//============================================================================
/**
* Display the bid information to the console (std::out
*
* @param bid struct containing the bid info
*/
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
		<< bid.fund << endl;
	return;
}
//============================================================================
/**
* Prompt user for bid information using console (std::in)
*
* @return Bid struct containing the bid info
*/
Bid getBid() {
	Bid bid;

	cout << "Enter Id: ";
	cin.ignore();
	getline(cin, bid.bidId);

	cout << "Enter title: ";
	getline(cin, bid.title);

	cout << "Enter fund: ";
	cin >> bid.fund;

	cout << "Enter amount: ";
	cin.ignore();
	string strAmount;
	getline(cin, strAmount);
	bid.amount = strToDouble(strAmount, '$');

	return bid;
}
//============================================================================
/**
* Load a CSV file containing bids into a container
*
* @param csvPath the path to the CSV file to load
* @return a container holding all the bids read
*/
vector<Bid> loadBids(string csvPath) {
	cout << "Loading CSV file " << csvPath << endl;

	// Define a vector data structure to hold a collection of bids.
	vector<Bid> bids;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	try {
		// loop to read rows of a CSV file
		for (int i = 0; i < file.rowCount(); i++) {

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');


			//TESTER - Shows each bid loaded from CSV file
			//cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bids.push_back(bid);
		}
	}
	catch (csv::Error& e) {
		std::cerr << e.what() << std::endl;
	}
	return bids;
}

//============================================================================
/**
* Simple C function to convert a string to a double
* after stripping out unwanted char
*
* credit: http://stackoverflow.com/a/24875936
*
* @param ch The character to strip out
*/
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/* NO NOTEABLE EDITS ABOVE */



























/*
░██████╗░██╗░░░░░░░██╗░█████╗░██████╗░  
██╔════╝░██║░░██╗░░██║██╔══██╗██╔══██╗  
╚█████╗░░╚██╗████╗██╔╝███████║██████╔╝  
░╚═══██╗░░████╔═████║░██╔══██║██╔═══╝░  
██████╔╝░░╚██╔╝░╚██╔╝░██║░░██║██║░░░░░  
╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚═╝╚═╝░░░░░  

██████╗░███████╗░██████╗██╗░░░██╗██████╗░███╗░░░███╗██╗████████╗
██╔══██╗██╔════╝██╔════╝██║░░░██║██╔══██╗████╗░████║██║╚══██╔══╝
██████╔╝█████╗░░╚█████╗░██║░░░██║██████╦╝██╔████╔██║██║░░░██║░░░
██╔══██╗██╔══╝░░░╚═══██╗██║░░░██║██╔══██╗██║╚██╔╝██║██║░░░██║░░░
██║░░██║███████╗██████╔╝╚██████╔╝██████╦╝██║░╚═╝░██║██║░░░██║░░░
╚═╝░░╚═╝╚══════╝╚═════╝░░╚═════╝░╚═════╝░╚═╝░░░░░╚═╝╚═╝░░░╚═╝░░░*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
	/*█▀▀ █ ▀▄▀ █▀▄▀█ █▀▀     █▀█ ▄▀█ █▀█ ▀█▀ █ ▀█▀ █ █▀█ █▄░█
	  █▀░ █ █░█ █░▀░█ ██▄     █▀▀ █▀█ █▀▄ ░█░ █ ░█░ █ █▄█ █░▀█ - Implement the quick sort logic over bid.title*/
	  /*================================================================================================================================*/
	  /*	 PARTITION FUNCTION NOTES
	  * Partition the vector of bids into two parts, low and high
	  * @param bids Address of the vector<Bid> instance to be partitioned
	  * @param begin Beginning index to partition
	  * @param end Ending index to partition */
	  //--------------------------------------------------------------------
	  //set low and high equal to begin and end
	  // pick the middle element as pivot point
	  // while not done 
		  // keep incrementing low index while bids[low] < bids[pivot]
		  // keep decrementing high index while bids[pivot] < bids[high]
		  /* If there are zero or one elements remaining,
			  all bids are partitioned. Return high */
			  // else swap the low and high bids (built in vector method)
				   // move low and high closer ++low, --high
		   //return high;
	  //--------------------------------------------------------------------

int partition(vector<Bid>& bids, int begin, int end) {
	
	//Initialize variables 
	Bid pivotBid = bids.at(begin + (end - begin) / 2);
	int low = begin;
	int high = end;
	bool done = false;

	// While not done - loop continues until it is done
	while (!done) {
		// keep incrementing low index while bids[low] < bids[pivot]
		while (bids[low].title < pivotBid.title) {
			++low;
		}

		// keep decrementing high index while bids[pivot] < bids[high]
		while (pivotBid.title < bids[high].title) {
			--high;
		}

		/* If there are zero or one elements remaining, all bids are partitioned. Return high */
		if (low >= high) {
			done = true;
		}

		/* else swap the low and high bids, move low and high closer ++low, --high. Return high;*/
		else {
			std::swap(bids[low], bids[high]); // Use std::swap to swap the bids
			++low;
			--high;
		}
	}

	return high;
}//END Function
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/

















/*================================================================================================================================*/
/*================================================================================================================================*/
	/*█▀▀ █ ▀▄▀ █▀▄▀█ █▀▀     █▀█ █░█ █ █▀▀ █▄▀ █▀ █▀█ █▀█ ▀█▀
	  █▀░ █ █░█ █░▀░█ ██▄     ▀▀█ █▄█ █ █▄▄ █░█ ▄█ █▄█ █▀▄ ░█░  - Perform a quick sort on bid title*/
	  /*================================================================================================================================*/
	  /*   QUICKSORT FUNCTION NOTES
	  * Average performance: O(n log(n))
	  * Worst case performance O(n^2))
	  * @param bids address of the vector<Bid> instance to be sorted
	  * @param begin the beginning index to sort on
	  * @param end the ending index to sort on */
	  //--------------------------------------------------------------------
	  //set mid equal to 0
	  /* Base case: If there are 1 or zero bids to sort,
		  partition is already sorted otherwise if begin is greater
		  than or equal to end then return*/
		  /* Partition bids into low and high such that
		  midpoint is location of last element in low */
		  // recursively sort low partition (begin to mid)
		  // recursively sort high partition (mid+1 to end)
	  //--------------------------------------------------------------------
void quickSort(vector<Bid>& bids, int begin, int end) {
	//initialize j to zero
	int j = 0;

	//This is the base case 
	if (begin >= end) {
		return;
	}

	//Partitions the vector to variable j using partition function
	j = partition(bids, begin, end);

	//Calls quickSort function two times, one for the first half (low partition) and one for the second half (high partition)
	quickSort(bids, begin, j); // recursively sort low partition (begin to mid)
	quickSort(bids, j + 1, end); // recursively sort high partition (mid+1 to end)

}//END Function
/*================================================================================================================================*/
/*================================================================================================================================*/





/*================================================================================================================================*/
/*================================================================================================================================*/
	/*█▀▀ █ ▀▄▀ █▀▄▀█ █▀▀     █▀ █▀▀ █░░ █▀▀ █▀▀ ▀█▀ █ █▀█ █▄░█     █▀ █▀█ █▀█ ▀█▀
	  █▀░ █ █░█ █░▀░█ ██▄     ▄█ ██▄ █▄▄ ██▄ █▄▄ ░█░ █ █▄█ █░▀█     ▄█ █▄█ █▀▄ ░█░ - Implement the selection sort logic over bid.title*/
	  /*================================================================================================================================*/
	  /*   SELECTIONSORT FUNCTION NOTES
	  * Perform a selection sort on bid title
	  * Average performance: O(n^2))
	  * Worst case performance O(n^2))
	  * @param bid address of the vector<Bid>
	  * instance to be sorted */
	  //--------------------------------------------------------------------
	  //define min as int (index of the current minimum bid)
		  // check size of bids vector
		  // set size_t platform-neutral result equal to bid.size()
		  // pos is the position within bids that divides sorted/unsorted
		  // for size_t pos = 0 and less than size -1 
			  // set min = po
			  // loop over remaining elements to the right of position
				  // if this element's title is less than minimum title
					  // this element becomes the minimum
			  // swap the current minimum with smaller one found
				  // swap is a built in vector method
	  //--------------------------------------------------------------------



















/* 
░██████╗░██╗░░░░░░░██╗░█████╗░██████╗░  
██╔════╝░██║░░██╗░░██║██╔══██╗██╔══██╗  
╚█████╗░░╚██╗████╗██╔╝███████║██████╔╝  
░╚═══██╗░░████╔═████║░██╔══██║██╔═══╝░  
██████╔╝░░╚██╔╝░╚██╔╝░██║░░██║██║░░░░░  
╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚═╝╚═╝░░░░░  

██████╗░███████╗░██████╗██╗░░░██╗██████╗░███╗░░░███╗██╗████████╗
██╔══██╗██╔════╝██╔════╝██║░░░██║██╔══██╗████╗░████║██║╚══██╔══╝
██████╔╝█████╗░░╚█████╗░██║░░░██║██████╦╝██╔████╔██║██║░░░██║░░░
██╔══██╗██╔══╝░░░╚═══██╗██║░░░██║██╔══██╗██║╚██╔╝██║██║░░░██║░░░
██║░░██║███████╗██████╔╝╚██████╔╝██████╦╝██║░╚═╝░██║██║░░░██║░░░
╚═╝░░╚═╝╚══════╝╚═════╝░░╚═════╝░╚═════╝░╚═╝░░░░░╚═╝╚═╝░░░╚═╝░░░*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/

void selectionSort(vector<Bid>& bids) {

	//Handles outside loop while i is less then bids size, first half
	for (int i = 0; i < bids.size(); ++i) {
		int indexSmallest = i;

		//Handles inside loop while j is less then bids size, second half
		for (int j = i + 1; j < bids.size(); ++j) {

			// if this element's title is less than the minimum title, this element becomes the minimum
			if (bids[j].title < bids[indexSmallest].title) {
				indexSmallest = j;
			}
		}

		// Swap the current minimum with the smaller one found
		std::swap(bids[i], bids[indexSmallest]);
	}
} //END Function



/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/





























 /*░██████╗████████╗░█████╗░██████╗░████████╗      ███╗░░░███╗░█████╗░██╗███╗░░██╗
	██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝      ████╗░████║██╔══██╗██║████╗░██║
	╚█████╗░░░░██║░░░███████║██████╔╝░░░██║░░░      ██╔████╔██║███████║██║██╔██╗██║
	░╚═══██╗░░░██║░░░██╔══██║██╔══██╗░░░██║░░░      ██║╚██╔╝██║██╔══██║██║██║╚████║
	██████╔╝░░░██║░░░██║░░██║██║░░██║░░░██║░░░      ██║░╚═╝░██║██║░░██║██║██║░╚███║
	╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░      ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝  - The one and only main() method*
/*================================================================================================================================*/
int main(int argc, char* argv[]) {

	// process command line arguments
	string csvPath;
	switch (argc) {

	case 2:
		csvPath = argv[1];
		break;
	default:
		csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
	}

	/*===============================================================================*/
	// Define a vector to hold all the bids
	vector<Bid> bids;

	// Define a timer variable
	clock_t ticks;

	int choice = 0;

	/*===============================================================================*/
	// While loop outputs menu options until "9" is entered.
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << " 1. Load Bids" << endl;
		cout << " 2. Display All Bids" << endl;
		cout << " 3. Selection Sort All Bids" << endl;
		cout << " 4. Quick Sort All Bids" << endl;

		//Added options 5 and 6 to be able to change between the two CSV files
		cout << " 5. Switch load designation to: eBid_Monthly_Sales.csv" << endl;
		cout << " 6. Switch load designation to: eBid_Monthly_Sales_Dec_2016.csv (default)" << endl;

		//Used to terminate the program
		cout << " 9. Exit" << endl;
		cout << "Enter choice: ";

		// Input validation
		if (!(cin >> choice)) {
			// Clear the input buffer to prevent an infinite loop
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number between 1 and 9." << endl;
			continue;
		}

		cout << endl;

		/*===============================================================================*/
		//Start Switch
		switch (choice) {

			//--------------------------------------------------------------------
			// Option 1: User can load the bids from the current CSV file
		case 1:
			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			try {
				bids = loadBids(csvPath);
				cout << bids.size() << " bids read" << endl;
			}
			catch (const char* error) {
				cout << error << endl;
			}

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

			//--------------------------------------------------------------------
			//Option 2: Once the file is loaded, this displays all the bids in the current order (sorted or unsorted)
		case 2:
			if (bids.empty()) {
				cout << "Error: No bids have been loaded. Please load bids before trying to display them." << endl;
				break;
			}
			// Loop and display the bids read
			for (int i = 0; i < bids.size(); ++i) {
				displayBid(bids[i]);
			}
			cout << endl;
			break;


			/*===============================================================================*/
			/*===============================================================================*/
			/* NOTEABLE EDITS ABOVE */
				// - added options 5 and 6 to user menu display











			/*================================================================================================================================*/
				/*█▀▀ █ ▀▄▀ █▀▄▀█ █▀▀     ▄█ █▄▄
				  █▀░ █ █░█ █░▀░█ ██▄     ░█ █▄█  - Invoke the selection sort and report timing results*/
				  /*================================================================================================================================*/
				  /*================================================================================================================================*/
						  /* Option 3:  -The Program uses the selectSort Function to Sort the bids in the currently designated CSV file,
										-The Program then Outputs the amount of bids sorted,
										-Lastly The Program Caclulates and outputs the time it took to sort the bids. */
		case 3:
			// Initialize a timer variable before loading bids 
			ticks = clock();

			//Sorts the bid using selectionSort Function
			selectionSort(bids);
			cout << bids.size() << " bids sorted" << endl;

			// Calculate elapsed time and display result  
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks  
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;
			/*================================================================================================================================*/
			/*================================================================================================================================*/
				/*█▀▀ █ ▀▄▀ █▀▄▀█ █▀▀     ▀█ █▄▄
				  █▀░ █ █░█ █░▀░█ ██▄     █▄ █▄█  - Invoke the quick sort and report timing results*/
				  /*================================================================================================================================*/
				  /*================================================================================================================================*/
						  /* Option 4:  -The Program uses the quickSort Function to quickly sort the bids in the currently designated CSV file,
										-The Program then Outputs the amount of bids sorted,
										-Lastly The Program Caclulates and outputs the time it took to sort the bids. */
		case 4:
			// Initialize a timer variable before loading bids  
			ticks = clock();

			//Quick Sorts the bids using the quickSort Function
			quickSort(bids, 0, int(bids.size() - 1));
			cout << bids.size() << " bids sorted" << endl;

			// Calculate elapsed time and display result  
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks 
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

			/*================================================================================================================================*/
			/*================================================================================================================================*/
					/* Option 5 - Changes the designated load file to eBid_Monthly_Sales.csv */
		case 5:
			csvPath = "eBid_Monthly_Sales.csv";
			cout << "You've switched the load designation to: eBid_Monthly_Sales.csv" << endl;
			cout << "Please Re-Load the bids." << endl;
			cout << endl;
			break;

			//--------------------------------------------------------------------
			/* Option 6 - Changes the designated load file to eBid_Monthly_Sales_Dec_2016.csv */
		case 6:
			csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
			cout << "You've switched the load designation to: eBid_Monthly_Sales_Dec_2016.csv" << endl;
			cout << "Please Re-Load the bids." << endl;
			cout << endl;
			break;

		}//End Switch-Case

/*================================================================================================================================*/
/*================================================================================================================================*/
	}//End While
	cout << "GoodBye!" << endl;  //Ending message to user.
	return 0;
}//End Main
/*================================================================================================================================*/
/*================================================================================================================================*/
  /*███████╗███╗░░██╗██████╗░      ███╗░░░███╗░█████╗░██╗███╗░░██╗
	██╔════╝████╗░██║██╔══██╗      ████╗░████║██╔══██╗██║████╗░██║
	█████╗░░██╔██╗██║██║░░██║      ██╔████╔██║███████║██║██╔██╗██║
	██╔══╝░░██║╚████║██║░░██║      ██║╚██╔╝██║██╔══██║██║██║╚████║
	███████╗██║░╚███║██████╔╝      ██║░╚═╝░██║██║░░██║██║██║░╚███║
	╚══════╝╚═╝░░╚══╝╚═════╝░      ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝*/