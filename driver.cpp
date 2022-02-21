/*****************************************
 ** File:    mytest.cpp
 ** Project: CMSC 341 Project 3, Fall 2020
 ** Author:  Kyle Rivera
 ** Date:    11/09/2020
 ** Section: 06
 ** E-mail:  drivera1@umbc.edu
 **
 ** This file contains the test drive program for project 3.
 ** This program tests PQueue class and its min-skew heap structure.
 ** It tests every public function that PQueue has such as:
 ** insertPatient, mergewithQueue, setPriorityFn, getNextPatient, etc.
 ** It also tests the time complexity of enqueue/dequeue of PQueue
 ** with respect to N.
 **
 ***********************************************/


#include "pqueue.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
// Priority functions compute an integer priority for a patient.  Internal
// computations may be floating point, but must return an integer.

int priorityFn1(const Patient &patient);
int priorityFn2(const Patient &patient);
void insertPQueue(PQueue &queue, int n_elem);
void popPQueue(PQueue &queue);

int main() {
	try
	{
		cout << "Creating test queue...." << endl;
		PQueue test(priorityFn1);

		Patient patient1("Sam", 1, 37, 79,  36, 133, 75);
		Patient patient2("Liz", 5, 37, 98, 26,  70, 100);
		Patient patient3("Nick", 2, 37, 85, 34, 125, 85);
		Patient patient4("Eva", 4, 37, 95,  22, 115, 95);

		// Insert test: tests insertPatient() while indirectly testing mergeWithQueue
		cout << "******************INSERT TEST******************" << endl;
		cout << "Inserting Nick, Sam, Liz, and Eva...." << endl;
		test.insertPatient(patient3);
		test.insertPatient(patient1);
		test.insertPatient(patient2);
		test.insertPatient(patient4);
		// Test if _size isn't incremented correctly
		if(test.numPatients() != 4)
		{
			cout << "\nTEST FAIL: _size is wrong" << endl;
		}
		cout << "\ntest Queue dump: " << endl;
		test.dump();
		cout << "\nPrinting patient test queue: " << endl;
		test.printPatientQueue();

		// Copy-clear test: tests assignment/copy constructors and clear()
		cout << "\n******************COPY/CLEAR TEST******************" << endl;
		cout << "Constructing test2 queue with test...."  << endl;
		PQueue test2(test);
		cout << "\ntest Queue dump: " << endl;
		test2.dump();
		cout << "\nPrinting patient test queue: " << endl;
		test2.printPatientQueue();

		// Test if original queue member variables are copied correctly
		if(test2.numPatients() != 4)
		{
			cout << "\nTEST FAIL: _size is wrong" << endl;
		}
		if(test.getPriorityFn() != test2.getPriorityFn() )
		{
			cout << "\nTEST FAIL: priority not copied correctly" << endl;
		}
		cout << "\nClearing test2...." << endl;
		test2.clear();

		// Test if original queue is affected by clear; therefore, a shallow copy is made
		if((test.numPatients() != 4)||(test.getPriorityFn() != priorityFn1))
		{
			cout << "\nTEST FAIL: shallow copy detected" << endl;
		}
		cout << "\nAssigning test3 queue with test...."  << endl;
		PQueue test3 = test;
		cout << "\ntest Queue dump: " << endl;
		test3.dump();
		cout << "\nPrinting patient test queue: " << endl;
		test3.printPatientQueue();

		// Test if original queue member variables are copied correctly
		if(test3.numPatients() != 4)
		{
			cout << "\nTEST FAIL: _size is wrong" << endl;
		}
		if(test.getPriorityFn() != test3.getPriorityFn() )
		{
			cout << "\nTEST FAIL: priority not copied correctly" << endl;
		}
		cout << "\nClearing test3...." << endl;
		test3.clear();

		// Test if original queue is affected by clear; therefore, a shallow copy is made
		if((test.numPatients() != 4)||(test.getPriorityFn() != priorityFn1))
		{
			cout << "\nTEST FAIL: shallow copy detected" << endl;
		}

		// Merge test: tests mergeWithQueue
		cout << "\n******************MERGE TEST******************" << endl;
		cout << "Creating merge queue...." << endl;
		PQueue merge(priorityFn1);

		Patient patient5("John", 3, 39, 91, 27, 115, 110);
		Patient patient6("Mia", 3,  33, 93, 28, 118, 98);

		cout << "\nInserting John, Mia...." << endl;
		merge.insertPatient(patient5);
		merge.insertPatient(patient6);

		cout << "\nMerging test and merge queue...." << endl;
		test.mergeWithQueue(merge);
		cout << "\ntest Queue dump: " << endl;
		test.dump();
		cout << "\nPrinting patient test queue: " << endl;
		test.printPatientQueue();

		// Merge queue should be unaffected for there to be no double frees
		if((merge.numPatients() != 2))
		{
			cout << "\nTEST FAIL: shallow merge detected/double frees" << endl;
		}

		// Set Priority test: tests Set priority FN, and getNextPatient indirectly
		cout << "\n******************SET PRIORITY TEST******************" << endl;
		cout << "Setting test priorityFn to priorityFn2...." << endl;
		test.setPriorityFn(priorityFn2);
		// Test if priority is unchanged
		if(test.getPriorityFn() != priorityFn2)
		{
			cout << "TEST FAIL: Priority unchanged" << endl;
		}
		cout << "\ntest Queue dump: " << endl;
		test.dump();
		cout << "\nPrinting patient test queue: " << endl;
		test.printPatientQueue();
		cout << "\nSetting test priorityFn back to priorityFn1...." << endl;
		test.setPriorityFn(priorityFn1);
		cout << "\ntest Queue dump: " << endl;
		test.dump();
		cout << "\nPrinting patient test queue: " << endl;
		test.printPatientQueue();

		// Get Next Patient test: tests getNextPatient
		cout << "\n******************GET NEXT PATIENT TEST******************" << endl;
		cout << "Finalized test queue dump: " << endl;
		test.dump();
		cout << "\nGetting all of the patients.... " << endl;
		// Should print all patients with respect to number in queue
		while (test.numPatients() > 0) {
		    Patient patient = test.getNextPatient();
		    std::cout << "[" << priorityFn1(patient) << "] " << patient << std::endl;
		  }

		// Time complexity test: tests enqueue/dequeue with relevance to big O log n
		cout << "\n******************TIME COMPLEXITY CHECK FOR ENQUEUE/DEQUEUE******************" << endl;
		clock_t time;

		PQueue t_queue1(priorityFn1);
		int x = 1000;
		time = clock();
		insertPQueue(t_queue1, x);
		time = clock() - time;
		cout << "Time taken to insert " << x << " items is " << setprecision(5)
				<< (float)time/CLOCKS_PER_SEC << " seconds" << endl;
		time = clock();
		popPQueue(t_queue1);
		time = clock() - time;
		cout << "Time taken to pop " << x << " items is " << setprecision(5)
				<< (float)time/CLOCKS_PER_SEC << " seconds" << endl;
		cout << endl;

		PQueue t_queue2(priorityFn1);
		x = 10000;
		time = clock();
		insertPQueue(t_queue2, x);
		time = clock() - time;
		cout << "Time taken to insert " << x << " items is " << setprecision(5)
				<< (float)time/CLOCKS_PER_SEC << " seconds" << endl;
		time = clock();
		popPQueue(t_queue2);
		time = clock() - time;
		cout << "Time taken to pop " << x << " items is " << setprecision(5)
				<< (float)time/CLOCKS_PER_SEC << " seconds" << endl;
		cout << endl;


		PQueue t_queue3(priorityFn1);
		x = 100000;
		time = clock();
		insertPQueue(t_queue3, x);
		time = clock() - time;
		cout << "Time taken to insert " << x << " items is " << setprecision(5)
				<< (float)time/CLOCKS_PER_SEC << " seconds" << endl;
		time = clock();
		popPQueue(t_queue3);
		time = clock() - time;
		cout << "Time taken to pop " << x << " items is " << setprecision(5)
				<< (float)time/CLOCKS_PER_SEC << " seconds" << endl;
		cout << endl;

		// Sets the user to input number of items inside the PQueue
		string y_n;
		cout << "Test for different N? (y if yes) ";
		cin >> y_n;
		if(y_n == "y")
		{
			cout << "How many items should we insert? (-1 to quit) ";
			cin >> x;
			while(x != -1)
			{
				PQueue queue1(priorityFn1);
				time = clock();
				insertPQueue(queue1, x);
				time = clock() - time;
				cout << "Time taken to insert " << x << " items is " << setprecision(5)
						<< (float)time/CLOCKS_PER_SEC << " seconds" << endl;
				time = clock();
				popPQueue(queue1);
				time = clock() - time;
				cout << "Time taken to pop " << x << " items is " << setprecision(5)
						<< (float)time/CLOCKS_PER_SEC << " seconds" << endl;
				cout << endl;
				cout << "How many items should we insert? (-1 to quit) ";
				cin >> x;
			}
		}
	}
	catch(exception &e)
	{
		cout << e.what() << endl;
	}

  return 0;
}

int priorityFn1(const Patient&patient) {
  int pri = 5;
  if ((patient.getOxygen()<80 && (patient.getRR() > 35 || patient.getRR() < 8)) ||
      (patient.getHR() > 130 && patient.getBP() < 80))
      pri = 1;
  else if (((patient.getOxygen() >= 80 && patient.getOxygen() <= 89) &&
      (patient.getRR() >= 31 && patient.getRR() <= 35)) ||
      (patient.getTemperature() >= 40 || patient.getTemperature() <= 32))
      pri = 2;
  else if ((patient.getOxygen() >= 90 && patient.getOxygen() <= 94) &&
      (patient.getRR() >= 26 && patient.getRR() <= 30))
      pri = 3;
  else if ((patient.getOxygen() >= 95 && patient.getOxygen() <= 97) &&
      (patient.getRR() >= 21 && patient.getRR() <= 25))
      pri = 4;
  else
      pri = 5;
  return pri;
}

int priorityFn2(const Patient&patient) {
  //priority only based on triage
  //traige is set by a health care professional
  return patient.getTriage();
}
void insertPQueue(PQueue &queue, int n_elem)
{
	srand(time(NULL));
	while(n_elem != 0)
	{
		int TR = rand() % (6 - 1) + 1;
		int TEMP = rand() % (43 - 30) + 30;
		int OX = rand() % (102 - 70) + 70;
		int RR = rand() % (41 - 5) + 5;
		int HR = rand() % (141 - 35) + 35;
		int BP = rand() % (161 - 70) + 70;
		Patient temp(" ", TR, TEMP, OX, RR , HR, BP); //rng
		queue.insertPatient(temp);
		n_elem--;
	}
}
void popPQueue(PQueue &queue)
{
	while(queue.numPatients() != 0)
	{
		queue.getNextPatient();
	}
}
