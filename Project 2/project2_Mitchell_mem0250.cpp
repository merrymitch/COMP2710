/* FILE NAME: project2_Mitchell_mem0250.cpp
 * AUTHOR:    Mary Mitchell
 * USER ID:   mem0250
 * VERSION:   6/11/2021
 *
 * SOURCES:   I used the project2_hints.pdf as well as the help Dr. Li
 *            provided in his lecture briefing of the project. 
 *            Otherwise the code was mine.
 *
 * COMPILE:   g++ project2_Mitchell_mem0250.cpp
 * RUN:       ./a.out
 */

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

// VARIABLES
const int a_accuracy = 33;
const int b_accuracy = 50;
const int c_accuracy = 100;
const int TOTAL_RUNS = 10000;

// PROTOTYPES
/*
 * Input: A_alive indicates Aaron is alive true for alive, false for dead
 *        B_alive indicates Bob is alive
 *        C_alive indicates Charlie is alive
 * Return: true if at least two are alive otherwise return false
 */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);

/*
 * Call by reference
 * Strategy 1: Everyone shoots to kill the highest accuracy player alive
 * Input: B_alive indicates Bob is alive or dead
 *        C_alive indicates Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed
 *         Change C_alive into false if Charlie is killed
 */ 
void Aaron_shoots1(bool& B_alive, bool& C_alive); 

/*
 * Call by reference
 * Input: A_alive indicates Aaron is alive or dead
 *        C_alive indicates Charlie is alive or dead
 * Return: Change A_alive into false if Aaron is killed
 *         Change C_alive into false if Charlie is killed
 */     
void Bob_shoots(bool& A_alive, bool& C_alive);

/*
 * Call by reference
 * Input: A_alive indicates Aaron is alive or dead
 *        B_alive indicates Bob is alive or dead
 * Return: Change A_alive into false if Aaron is killed
 *         Change B_alive into false if Bob is killed
 */
void Charlie_shoots(bool& A_alive, bool& B_alive);

/*
 * Call by reference
 * Strategy 2: Aaron intentionally misses if both are alive
 * Input: B_alive indicates Bob is alive or dead
 *        C_alive indicates Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed
 *         Change C_alive into false if Charlie is killed
 */
void Aaron_shoots2(bool& B_alive, bool& C_alive);

// Simple method to implement pause function in linux
void Press_any_key(void);

// TEST PROTOTYPES
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

//MAIN METHOD
int main() {
   // Initializes random number generator's seed and calls test functions
   cout << "*** Welcome to Mary's Duel Simulator ***\n";
   srand(time(0));
   test_at_least_two_alive();
   Press_any_key();
   test_Aaron_shoots1();
   Press_any_key();
   test_Bob_shoots();
   Press_any_key();
   test_Charlie_shoots();
   Press_any_key();
   test_Aaron_shoots2();
   Press_any_key();
   
   // Starts strategy 1 and runs 10,000 times
   cout << "Ready to test strategy 1 (run 10000 times):\n";
   Press_any_key();
   int aaronWins1 = 0;
   int bobWins = 0;
   int charlieWins = 0;
   for (int i = 0; i < TOTAL_RUNS; i++) {
      bool aaronAlive = true;
      bool bobAlive = true;
      bool charlieAlive = true;
      while (at_least_two_alive(aaronAlive, bobAlive, charlieAlive)) {
         if (aaronAlive) {
            Aaron_shoots1(bobAlive, charlieAlive);
         }
         if (bobAlive) {
            Bob_shoots(aaronAlive, charlieAlive);
         }
         if (charlieAlive) {
            Charlie_shoots(aaronAlive, bobAlive);
         }
      }
      if (aaronAlive) {
         aaronWins1++;
      }
      if (bobAlive) {
         bobWins++;
      }
      if (charlieAlive) {
         charlieWins++;
      }
   }
   
   // Statistics for Strategy 1.
   cout << "Aaron won " << aaronWins1 << "/10000 duels or " << static_cast<double>(aaronWins1)/
           TOTAL_RUNS * 100 << "%\n"
        << "Bob won " << bobWins << "/10000 duels or " << static_cast<double>(bobWins)/
           TOTAL_RUNS * 100 << "%\n"
        << "Charlie won " << charlieWins << "/10000 duels or " << static_cast<double>(charlieWins)/
           TOTAL_RUNS * 100 << "%\n"
        << endl;
   
   // Reinitializes variables and starts strategy 2 to run 10,000 times
   cout << "Ready to test strategy 2 (run 10000 times):\n";
   Press_any_key();
   int aaronWins2 = 0;
   bobWins = 0;
   charlieWins = 0;
   for (int i = 0; i < TOTAL_RUNS; i++) {
      bool aaronAlive = true;
      bool bobAlive = true;
      bool charlieAlive = true;
      while (at_least_two_alive(aaronAlive, bobAlive, charlieAlive)) {
         if (aaronAlive) {
            Aaron_shoots2(bobAlive, charlieAlive);
         }
         if (bobAlive) {
            Bob_shoots(aaronAlive, charlieAlive);
         }
         if (charlieAlive) {
            Charlie_shoots(aaronAlive, bobAlive);
         }
      }
      if (aaronAlive) {
         aaronWins2++;
      }
      if (bobAlive){
         bobWins++;
      }
      if (charlieAlive){
         charlieWins++;
      }
   }
   
   // Statistics for Strategy 2.
   cout << "Aaron won " << aaronWins2 << "/10000 duels or " << static_cast<double>(aaronWins2)/
           TOTAL_RUNS * 100 << "%\n"
        << "Bob won " << bobWins << "/10000 duels or " << static_cast<double>(bobWins)/
           TOTAL_RUNS * 100 << "%\n"
        << "Charlie won " << charlieWins << "/10000 duels or " << static_cast<double>(charlieWins)/
           TOTAL_RUNS * 100 << "%\n"
        << endl;
   // Compare Strategy 1 and Strategy 2.    
   if (aaronWins1 > aaronWins2) {
      cout << "Strategy 1 is better than strategy 2.\n";
   }
   else {
      cout << "Strategy 2 is better than strategy 1.\n";
   }
   return 0;
}

// FUNCTION AND TESTING IMPLEMENTATIONS
// Implementation of functions. Look above for documentation of them.
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
   if (A_alive && (B_alive || C_alive)) {
      return true;
   }
   else if (B_alive && C_alive) {
      return true;
   }
   else {
      return false;
   }
}

void test_at_least_two_alive(void) {
   cout << "Unit Testing 1: Function - at_least_two_alive()\n";
   
   cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
   assert(true == at_least_two_alive(true, true, true));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
   assert(true == at_least_two_alive(false, true, true));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
   assert(true == at_least_two_alive(true, false, true));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
   assert(true == at_least_two_alive(true, true, false));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
   assert(false == at_least_two_alive(false, false, true));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
   assert(false == at_least_two_alive(false, true, false));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(true, false, false));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(false, false, false));
   cout << "\tCase passed...\n";
}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
   assert(C_alive || B_alive);
   int shootResult = rand() % 100;
   if (C_alive) {
      if (shootResult <= (a_accuracy)) {
         C_alive = false;
      }
   }
   else {
      if (shootResult <= (a_accuracy)) {
         B_alive = false;
      }
   }
}

/*
 * Case 1: Test Bob bc he is alive and wasn't the target.
 * Case 2: Test Bob bc he is dead. 
 * Case 3: Test Charlie bc he is dead. 
 */
void test_Aaron_shoots1(void) {
   cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
   bool bob_a;
   bool charlie_a;
   cout << "\tCase 1: Bob alive, Charlie alive\n"
        << "\t\tAaron is shooting at Charlie\n";
   bob_a = true;
   charlie_a = true;
   Aaron_shoots1(bob_a, charlie_a);
   assert(true == bob_a);
   
   cout << "\tCase 2: Bob dead, Charlie alive\n"
        << "\t\tAaron is shooting at Charlie\n";
   bob_a = false;
   charlie_a = true;
   Aaron_shoots1(bob_a, charlie_a);
   assert(false == bob_a);
   
   cout << "\tCase 3: Bob alive, Charlie dead\n"
        << "\t\tAaron is shooting at Bob\n";
   bob_a = true;
   charlie_a = false;
   Aaron_shoots1(bob_a, charlie_a);
   assert(false == charlie_a);
}

void Bob_shoots(bool& A_alive, bool& C_alive) {
   assert(C_alive || A_alive);
   int shootResult = rand() % 100;
   if (C_alive) {
      if (shootResult <= (b_accuracy)) {
         C_alive = false;
      }
   }
   else {
      if (shootResult <= (b_accuracy)) {
         A_alive = false;
      }
   }
}

/*
 * Case 1: Test Aaron bc he is the least accurate and wasn't targetted.
 * Case 2: Test Aaron bc he is dead.
 * Case 3: Test Charlie bc he is dead. 
 */
void test_Bob_shoots(void) {
   cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
   bool aaron_a;
   bool charlie_a;
   cout << "\tCase 1: Aaron alive, Charlie alive\n"
        << "\t\tBob is shooting at Charlie\n";
   aaron_a = true;
   charlie_a = true;
   Bob_shoots(aaron_a, charlie_a);
   assert(true == aaron_a);
   
   cout << "\tCase 2: Aaron dead, Charlie alive\n"
        << "\t\tBob is shooting at Charlie\n";
   aaron_a = false;
   charlie_a = true;
   Bob_shoots(aaron_a, charlie_a);
   assert(false == aaron_a);
   
   cout << "\tCase 3: Aaron alive, Charlie dead\n"
        << "\t\tBob is shooting at Aaron\n";
   aaron_a = true;
   charlie_a = false;
   Bob_shoots(aaron_a, charlie_a);
   assert(false == charlie_a);
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {
   assert(A_alive || B_alive);
   int shootResult = rand() % 100;
   if (B_alive) {
      if (shootResult <= (c_accuracy)) {
         B_alive = false;
      }
   }
   else {
      if (shootResult <= (c_accuracy)) {
         A_alive = false;
      }
   }
}

/*
 * Case 1 - 3: Test both bc Charlie never misses. 
 */
void test_Charlie_shoots(void) {
   cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
   bool aaron_a;
   bool bob_a;
   cout << "\tCase 1: Aaron alive, Bob alive\n"
        << "\t\tCharlie is shooting Bob\n";
   aaron_a = true;
   bob_a = true;
   Charlie_shoots(aaron_a, bob_a);
   assert(true == aaron_a);
   assert(false == bob_a);
   
   cout << "\tCase 2: Aaron dead, Bob alive\n"
        << "\t\tCharlie is shooting Bob\n";
   aaron_a = false;
   bob_a = true;
   Charlie_shoots(aaron_a, bob_a);
   assert(false == aaron_a);
   assert(false == bob_a);
   
   cout << "\tCase 3: Aaron alive, Bob dead\n"
        << "\t\tCharlie is shooting Aaron\n";
   aaron_a = true;
   bob_a = false;
   Charlie_shoots(aaron_a, bob_a);
   assert(false == aaron_a);
   assert(false == bob_a);
}

void Aaron_shoots2(bool& B_alive, bool& C_alive) {
   assert(C_alive || B_alive);
   int shootResult = rand() % 100;
   if (!C_alive || !B_alive) {
      if (C_alive) {
         if (shootResult <= (a_accuracy)) {
            C_alive = false;
         }
      }
      else {
         if (shootResult <= (a_accuracy)) {
            B_alive = false;
         }
      }
   }
}

/*
 * Case 1: Bob and Charlie tested bc Aaron misses.
 * Case 2: Bob tested bc he should be dead.
 * Case 3: Charlie tested bc he should be dead. 
 */
void test_Aaron_shoots2(void) {
   cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
   bool bob_a;
   bool charlie_a;
   cout << "\tCase 1: Bob alive, Charlie alive\n"
        << "\t\tAaron intentionally misses his first shot\n"
        << "\t\tBoth Bob and Charlie are alive\n";
   bob_a = true;
   charlie_a = true;
   Aaron_shoots2(bob_a, charlie_a);
   assert(true == bob_a);
   assert(true == charlie_a);
   
   cout << "\tCase 2: Bob dead, Charlie alive\n"
        << "\t\tAaron is shooting at Charlie\n";
   bob_a = false;
   charlie_a = true;
   Aaron_shoots2(bob_a, charlie_a);
   assert(false == bob_a);
   
   cout << "\tCase 3: Bob alive, Charlie dead\n"
        << "\t\tAaron is shooting at Bob\n";
   bob_a = true;
   charlie_a = false;
   Aaron_shoots2(bob_a, charlie_a);
   assert(false == charlie_a);
}

void Press_any_key(void) {
   // Must press ENTER twice.
   cout << "Press any key to continue...";
   cin.ignore().get();
}

// CHECKLIST
/*
 * Accurate Interface
 * Three Constants 
 * Five Functions
 * Five Function Tests
 * Use Assert
 */
