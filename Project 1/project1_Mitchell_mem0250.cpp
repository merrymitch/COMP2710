/* FILE NAME: project1_Mitchell_mem0250.cpp
 * Author:    Mary Mitchell (mem0250)
 * Class:     COMP 2710
 * Version:   5/28/2021
 *
 * Sources:   The recommended stackoverflow tip from Po-wei Harn on piazza in regards
 *            to checking cin values for non-float values. 
 *
 * Compile:   g++ project1_Mitchell_mem0250.cpp 
 * Run:       ./a.out
 * Located:   home/u1/mem0250/project1_Mitchell_mem0250.cpp
 */
#include <iostream>
#include <limits>
using namespace std;

int main() {
   // VARIABLE INITIALIZATION
   float loan = -1;
   float interestRate = -1;
   float monthlyPaid = -1;
   float interestRateC = 0;
   int currentMonth = 0;
   float totalInterest = 0;

   // CURRENCY FORMATTING
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   
   // USER INPUT
    
   cout << "\nLoan Amount: ";
   cin >> loan;
   if (!cin) {
	cout << "\nInput is invalid\n";
	return 0;
   }
   if (loan <= 0 ) {
   	cout << "Invalid Loan\n";
	return 0;
   }

   cout << "Interest Rate (% per year): ";
   cin >> interestRate;
   if (!cin) {
	cout << "\nInput is invalid\n";
	return 0;
   }
   if (interestRate <= -1) {
	cout << "Invalid Interest Rate\n";
	return 0;
   }
   
   // GET PROPER INTEREST RATES FOR CALCULATIONS
   interestRate /= 12;
   interestRateC = interestRate / 100;
   
   cout << "Monthly Payments: ";
   cin >> monthlyPaid;
   if (!cin) {
	cout << "\nInput is invalid\n";
	return 0;
   }
   if (monthlyPaid <= 0) {
	cout << "\nInvalid Payment\n";
   }
   cout << endl;
   if ((interestRateC * loan) >= monthlyPaid) {
   	cout << "Insufficient Payment\n";
	return 0;
   }	
   
   //  AMORTIZATON TABLE
   cout << "*****************************************************************\n"
        << "\tAmortization Table\n"
        << "*****************************************************************\n"
        << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
    
   // LOOP TO FILL TABLE
   while (loan > 0) {
      if (currentMonth == 0) {
         cout << currentMonth++ << "\t$" << loan;
         if (loan < 1000) cout << "\t"; // Formatting MAGIC
         cout << "\tN/A\tN/A\tN/A\t\tN/A\n";
      }
      else {
         // First calculate the interest payment. 
         float monthlyInterest = interestRateC * loan;
         // Then deduct the interest payment from the monthly amount. 
         float debtPaid = monthlyPaid - monthlyInterest;
	 // Calculate total interest.
	 totalInterest = totalInterest + monthlyInterest;
         // Subtract the debt from the stereo loan. 
         loan = loan - debtPaid;
         // Check for loan less than 0.
         if (loan <= 0) {
            monthlyPaid = monthlyPaid + loan;
            debtPaid = debtPaid + loan;
            loan = 0;
         }
         //Output
         cout << currentMonth++ << "\t$";
	 cout << loan;
         if (loan < 1000) {
        	 cout << "\t";
         }
         double rateOutput = interestRateC * 100;
         cout << "\t$" << monthlyPaid << "\t" << rateOutput << "\t$";
         cout << monthlyInterest << "\t\t$" << debtPaid << "\n";
      }
   }
   
   cout << "****************************************************************\n";
   cout << "\nIt takes " << --currentMonth << " months to pay off "
        << "the loan.\n"
        << "Total interest paid is: $" << totalInterest;
   cout << endl << endl;
   return 0;
}
