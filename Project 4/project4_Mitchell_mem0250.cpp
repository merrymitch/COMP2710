/*
 * File Name: project4_Mitchell_mem0250.cpp
 * Author:    Mary Mitchell
 * UserID:    mem0250
 * Class:     COMP 2710
 * Version:   16 July 2021
 *
 * Info:      Program for a simple trivia game.
 *
 * Sources:   I used information from the hint and from the project
 * 	      briefing to help write this program. I also consulted stackoverflow
 * 	      in regards to cin/getline to help understand how my inputs were working.
 *
 * Location:  home/u1/mem0250
 * Compile:   g++ project4_Mitchell_mem0250.cpp
 * Run:       ./a.out
 */

#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <string>
using namespace std;

//Variables
int num_of_questions = 0;
bool continue_on = true;

//Structure for creating a linked list that holds a trivia question,
//answer, and point amount.
struct trivia_node {
   string question;
   string answer;
   int point;
   trivia_node *next;
};

//Creates a pointer to trivia_node.
typedef trivia_node* ptr_node;

//Prototypes
void init_question_list(ptr_node& q_list);
void add_question(ptr_node& q_list);
int ask_question(ptr_node q_list, int num_ask);
void Unit_Test();

//Creates two versions.
//#define UNIT_TESTING
#define trivia_quiz

//Main method 
int main() {
   ptr_node node_list = new trivia_node;
	//Creates a new trivia game
	//Sets up three original questions
	//Sets up loop for user to input his or her own questions
	//Quiz questions are stored in linked list
#ifdef trivia_quiz
   init_question_list(node_list);
   string cont_input;
   cout << "*** Welcome to Mary's trivia quiz game ***\n";
	//cout << "(Please note that inputs for this game are case sensitive and point values should be positive integers.)";
   do {
      add_question(node_list);
   } while (continue_on);
   cout << endl;
   ask_question(node_list, num_of_questions);
   cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
   return 0;

#endif
//Method for testing
#ifdef UNIT_TESTING
	cout << "*** This is a debugging version ***\n";
	Unit_Test();
	return 0;
#endif
}

// Method Definitions

//Initializes the quiz to have these three questions inputed into the linked list.
void init_question_list(ptr_node& q_list) {
	//Set pointer to the first question node and declare its values
   ptr_node cur_ptr = q_list;
   ptr_node cur_ptr2 = new trivia_node;
   ptr_node cur_ptr3 = new trivia_node;
   cur_ptr->question = "How long was the shortest war on record? (Hint: how many minutes)";
   cur_ptr->answer = "38";
   cur_ptr->point = 100;
   cur_ptr->next = cur_ptr2;
   num_of_questions++;
	//Create second question node and declare its values
   cur_ptr2->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)?";
   cur_ptr2->answer = "Bank of Italy";
   cur_ptr2->point = 50;
   cur_ptr2->next = cur_ptr3;
   num_of_questions++;
	//Create third question node and declare its values
   cur_ptr3->question = "What is the best-selling video game of all time? (Hint Call of Duty or Wii Sports)?";
   cur_ptr3->answer = "Wii Sports";
   cur_ptr3->point = 20;
   cur_ptr3->next = NULL;
   num_of_questions++;
}

//Gives user the option to add a question to the linked list
//Question is added to the front of the linked list
void add_question(ptr_node& q_list) {
   string user_answer;
   ptr_node new_q = new trivia_node;
	//User is asked for a question
   cout << "Enter a question: ";
   getline(cin, new_q->question);
	//User is asked for an answer
   cout << "Enter an answer: ";
   getline(cin, new_q->answer);
	//User is asked for a point amount
   cout << "Enter award points: ";
   cin >> new_q->point;
	//New trivia is added to the front of the list
   new_q->next = q_list;
   q_list = new_q;
	//Increment the amount of questions
   num_of_questions++;
	//Ask user whether or not to continue
   cout << "Continue? (Yes/No): ";
   getline(cin.ignore(), user_answer);
	//Give a little wiggle room for the case sensitivity of 'Yes'
   if (user_answer.compare("Yes") == 0 || user_answer.compare("YES") == 0 || user_answer.compare("yes") == 0) {
      continue_on = true;
   }
   else {
      continue_on = false;
   }
}

//Checks for null value
//Ask the user trivia questions and starts the game
int ask_question(ptr_node q_list, int num_ask) {
   int point_total = 0;
   string user_answer;
   ptr_node cur_ptr = q_list;
	//If the list is empty just return
   if (q_list = NULL) {
      return 0;
   }
	//If the amount of questions to ask is less than one, give a warning
   if (num_ask < 1) {
      cout << "Warning - the number of trivia to be asked must equal to or be larger than 1.";
   }
   //If there are less questions than the asked number, give a warning
   else if (num_of_questions < num_ask) {
      cout << "Warning - There is only " << num_of_questions << " trivia in the list.";
   }
   //Loop through the linked list, get user's answers, detemines correctness, and calculates point value
   else {
      for (int x = 0; x < num_ask; x++) {
         cout << "Question: " << cur_ptr->question << endl;
         cout << "Answer: ";
         getline(cin, user_answer);
      	//If correct the points are incremented
         if (user_answer.compare(cur_ptr->answer) == 0) {
            cout << "Your answer is correct! You receive " << cur_ptr->point << " points." << endl;
            point_total += cur_ptr->point;
            cout << "Your total points: " << point_total << endl;
         }
         //If incorrect the points remain the same
         else {
            cout << "Your answer is wrong. The correct answer is " << cur_ptr->answer << endl;
            cout << "Your total points: " << point_total << endl;
         }
      	//Move to next question in list
         cur_ptr = cur_ptr->next;
         cout << endl;
      }
   }
   return 0;
}

//Test cases to check whether the methods work
void Unit_Test() {
   ptr_node node_list = new trivia_node;
   init_question_list(node_list);
	//Case 1
   cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
   assert(0 == ask_question(node_list, 0));
   cout << "\nCase 1 Passed\n\n";
	//Case 2
   cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
   assert(0 == ask_question(node_list, 1));
   cout << "Case 2.1 passed" << endl;
   cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
   assert(0 == ask_question(node_list, 1));
   cout << "Case 2.2 passed" << endl;
	//Case 3
   cout <<"\nUnit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
   assert(0 == ask_question(node_list, 3));
   cout << "Case 3 passed\n\n";
	//Case 4
   cout << "Unit Test Case 4: Ask five questions in the linked list." << endl;
   assert(0 == ask_question(node_list, 5));
   cout << "\nCase 4 passed\n";
   cout << "\n*** End of the Debugging Version ***\n";
}































