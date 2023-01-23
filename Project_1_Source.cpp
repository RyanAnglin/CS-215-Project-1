//---------------------------------------------------------
// CS 215 - Fall 2017 - Project 1 
// Project 1: Gas Station 
// Author: Ryan Anglin 
// Section: 001
// Date: 09/14/2017
// --------------------------------------------------------

// COMPILIER DIRECTIVES 
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// CONSTANT DECLARATIONS (These were provided by Kevin Joiner, the instructor of CS215 at the University of Kentucky)  

const int   REWARDS_TOP_LIMIT = 3000;      // 3000 or more points gets the top discount
const int   REWARDS_MED_LIMIT = 2000;      // 2000 to 2999 points gets the medium discount
const int   REWARDS_LOW_LIMIT = 1000;      // 1000 to 1999 points gets the low discount
const int   REWARDS_USED_DEDUCTION = 500;  // rewards points deducted when discount is given
const float TOP_DISCOUNT = 0.15;           // Top rewards discount is $0.15 per gallon
const float MED_DISCOUNT = 0.10;           // Medium rewards discount $0.10 per gallon
const float LOW_DISCOUNT = 0.05;           // Low rewards discount is $0.05 per gallon
const float NO_DISCOUNT = 0.0;             // Amount to discount when there is no discount
float PPG_HI = 2.509;               // Base Price Per Gallon for 89 octane gasoline
float PPG_MED = 2.409;               // Base Price Per Gallon for 87 octane gasoline
float PPG_LOW = 2.289;               // Base Price Per Gallon for 85 octane gasoline
const float OCTANE_HI = 89;               // High Octane level
const float OCTANE_MED = 87;               // Medium Octane level
const float OCTANE_LOW = 85;               // Low Octane level
const float CASH_DISCOUNT_RATE = 0.02;     // 2% discount on subtotal when paying with cash


// VARIABLE DECLARATIONS 

string rewardsCustomer;
string CASH_OR_CREDIT;
int rewardsPointsInput;
int NEW_REWARDS;
int OCTANE_LEVEL;
float PRICE;
float NUMBER_OF_GALLONS; 
float SUB_TOTAL; 
float CASH_DISCOUNT; 
float TOTAL; 

//Function Definition and Logo Display 

void main() {
	cout << "+-----------------------------------------------+\n";
	cout << ":          NOT YOUR MOTHER'S GAS, STATION        :\n";
	cout << ":                   by Ryan Anglin               :\n";
	cout << "+-----------------------------------------------+\n";
	cout << "\n";

	//REWARDS CUSTOMER QUESTION 
	cout << "Are you a rewards customer? (yes/no): ";
	cin >> rewardsCustomer;
	rewardsPointsInput = 0;

	if (rewardsCustomer == "yes") {									// If the User is a Rewards Customer, enter the points 
		cout << "Enter your current rewards point:     ";
		cin >> rewardsPointsInput;
		//PRICE RE-CALCULATIONS FOR REWARDS CUSTOMER
		if (rewardsPointsInput >= REWARDS_TOP_LIMIT) {				// If Rewards Points are >= 3000 
			PPG_HI = (PPG_HI - TOP_DISCOUNT);
			PPG_MED = (PPG_MED - TOP_DISCOUNT);
			PPG_LOW = (PPG_LOW - TOP_DISCOUNT);
		}
		else if ((rewardsPointsInput >= REWARDS_MED_LIMIT)) {		// If Rewards Points  are NOT >=3000 but >=2000
			PPG_HI = (PPG_HI - MED_DISCOUNT);
			PPG_MED = (PPG_MED - MED_DISCOUNT);
			PPG_LOW = (PPG_LOW - MED_DISCOUNT);
		}
		else if ((rewardsPointsInput >= REWARDS_LOW_LIMIT)) {		// If Rewards Points are NOT >= 2000 but >= 1000 
			PPG_HI = (PPG_HI - LOW_DISCOUNT);
			PPG_MED = (PPG_MED - LOW_DISCOUNT);
			PPG_LOW = (PPG_LOW - LOW_DISCOUNT);
		}
		else if ((rewardsPointsInput < REWARDS_LOW_LIMIT)) {		// If Rewards Points are NOT >= 1000 
			PPG_HI = (PPG_HI - NO_DISCOUNT);
			PPG_MED = (PPG_MED - NO_DISCOUNT);
			PPG_LOW = (PPG_LOW - NO_DISCOUNT);
			cout << "Sorry! No Rewards Discount\n";
			cout << "\n";
		}
	}
	if (rewardsCustomer != "yes") {                                // If the User is NOT a Rewards Customer, print the following
			cout << "Ask our attendant about becoming one!\n";
			cout << "\n";
	}

	//NEW/ORIGINAL PRICE PER GALLON OUTPUT (AFTER REWARDS POINTS SCALING) 
	cout << "Price Per Gallon: \n";
	cout << "89 Octane  $ " << PPG_HI << "\n";
	cout << "87 Octane  $ " << PPG_MED << "\n";
	cout << "85 Octane  $ " << PPG_LOW << "\n";


	//OCTANE LEVEL INPUT & PRICING BASED ON OCTANE LEVEL 
	cout << "Enter Octane Level:       "; cin >> OCTANE_LEVEL;

	if (OCTANE_LEVEL == OCTANE_HI)										// Does the input Octane Level equal the Highest Octane Percentage? 
		PRICE = PPG_HI;
	else if (OCTANE_LEVEL == OCTANE_MED)								// Does the input Octante Level equal the Medium Octane Percentage? 
		PRICE = PPG_MED;
	else if (OCTANE_LEVEL == OCTANE_LOW)								// Does the input Octane Level equal the Lowest Octane Percentage? 
		PRICE = PPG_LOW;
	else if ((OCTANE_LEVEL != OCTANE_HI) || (OCTANE_LEVEL != OCTANE_MED) || (OCTANE_HI != OCTANE_LOW)) {  // Invalid Octane Level Input 
		cout << "Invalid input...We'll assume 85.000\n"; cout << "\n";
		PRICE = PPG_LOW;
		OCTANE_LEVEL = OCTANE_LOW;										// Automatically assign OCTANE_LEVEL to LOW for Invalid Input
	}

	//GALLONS & CASH OR CREDIT INPUT 
	cout << "Enter Number of Gallons:  "; cin >> NUMBER_OF_GALLONS;
	cout << "Cash or Credit:           "; cin >> CASH_OR_CREDIT;
	if ((CASH_OR_CREDIT != "Cash") && (CASH_OR_CREDIT != "Credit"))		// If the "Cash or Credit" input is Invalid print the following
		cout << "Opps! We didn't quite get that. We'll assume you meant Credit\n";  // Automatically assign Credit for Invalid Inputs
	cout << "\n";

	//FULL-PRICE & DISCOUNT CALCULATIONS  

	SUB_TOTAL = round((PRICE)*(NUMBER_OF_GALLONS) * 100) / 100;
	CASH_DISCOUNT = round((SUB_TOTAL)*(CASH_DISCOUNT_RATE) * 100) / 100;
	TOTAL = ((SUB_TOTAL)-(CASH_DISCOUNT));
	
	//REWARDS  POINTS CALCULATIONS 
	NEW_REWARDS = rewardsPointsInput - REWARDS_USED_DEDUCTION;
	if ((NEW_REWARDS < 0))												// If the calculation becomes negative, just output the orginal input for points 
		NEW_REWARDS = rewardsPointsInput;


	//RECIEPT OUTPUT
	cout << "+-------------------------------------------+\n";
	cout << ":     NOT YOUR MOTHER'S GAS, STATION        :\n";
	cout << ":              RECIEPT                      :\n";
	cout << "+-------------------------------------------+\n";
	cout << "OCTANE:                                " << setprecision (2) << setw(5) << OCTANE_LEVEL << "\n";
	cout << "GALLONS:                               " << setprecision (5) << setw(5) << NUMBER_OF_GALLONS << "\n";
	cout << "Price Per Gallon:               $      " << setprecision (4) << setw(5) << PRICE << "\n";
	if (CASH_OR_CREDIT != "Cash") {								       // If the User input anything BUT "Cash" just print the Total 
		cout << "Total:                          $      " << setprecision(5) << setw(5) << TOTAL << endl;
	}
	if (CASH_OR_CREDIT == "Cash") {									   // IF the User input is "Cash," print discount and subtotal 
		cout << "Subtotal:                       $      " << setprecision(5) << setw(5) << SUB_TOTAL << "\n";
		cout << "Cash Discount:                  $      " << setprecision(3) << setw(5) << CASH_DISCOUNT << "\n";
		cout << "Total:                          $      " << setprecision(5) << setw(5) << TOTAL << "\n";
	}
	if (rewardsCustomer >= "yes")									   // If the User was a Rewards Customer, print out their new rewards points value.
		cout << "Rewards:                               " << setw(5) << NEW_REWARDS << "\n"; 
	
	cout << "+-------------------------------------------+\n";
	cout << "\n";

	// Pause for Result

	system("pause");
}
