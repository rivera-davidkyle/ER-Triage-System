/*****************************************
 ** This file contains the pqueue class for project 3.
 ** This program contains the functions that creates
 ** a skew heap, and while maintaining the priority
 ** queue data structure. The class also includes a
 ** copy and assignment constructor.
 **
 ***********************************************/
#include "pqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

PQueue::PQueue(prifn_t priFn) {
        priority = priFn;
        _size = 0;
        _heap = nullptr;
}

PQueue::~PQueue()
{
		clear();
}

PQueue::PQueue(const PQueue& rhs)
{
		_size = rhs._size;
		priority = rhs.priority;
		// Uses a helper function to create a deep copy
		_heap = preOrderCopy(rhs._heap);
}

PQueue& PQueue::operator=(const PQueue& rhs)
{
		_size = rhs._size;
		priority = rhs.priority;
		// Uses a helper function to create a deep copy
		_heap = preOrderCopy(rhs._heap);
		return *this;
}

void PQueue::insertPatient(const Patient& input)
{
        if(_heap == nullptr)
        {
			_heap = new Node(input);
			_size++;
        }
        else
        {
        	// Creates a single-node heap
			PQueue temp(priority);
			temp.insertPatient(input);
			// Merges single-node heap to original heap
			mergeWithQueue(temp);
        }
}

Patient PQueue::getNextPatient() {
        Node* temp = _heap;
        Patient t_patient;
        if(temp)
        {
			t_patient = _heap->_patient;
			// Merges root's left/right child
			_heap = mergeHelper(temp->_left, temp->_right);
        }
        _size--;
        // Dequeues root
        delete temp;
		return t_patient;
        }

void PQueue::mergeWithQueue(PQueue& rhs)
{
		// Checks if it merges with itself
		if(_heap == rhs._heap)
		{
		throw runtime_error("ERROR: Self-merging prohibited");
		}

		int pr_1 = (*priority)(_heap->_patient);
		int pr_2 = (*priority)(rhs._heap->_patient);
		// Checks priority for merging
		if(pr_1 < pr_2)
		{
			 _heap = mergeHelper(_heap, rhs._heap);
		}
		else
		{
			// Swaps root if merging queue has lower key
		   Node* temp = _heap;
			_heap = rhs._heap;
			_heap = mergeHelper(_heap, temp);
		}
		_size += rhs._size;
		rhs._heap = nullptr;
}

void PQueue::clear()
{
		// Uses post order helper fn to clear tree
		clearHelper(_heap);
		_size = 0;
}

int PQueue::numPatients() const
{
        return _size;
}

void PQueue::printPatientQueue() const
{
		if(_heap == nullptr)
		{
				cout << "Queue is empty!" << endl;
		}
		else
		{
				preOrderDump(_heap);
		}
}

prifn_t PQueue::getPriorityFn() const
{
        return priority;
}

void PQueue::setPriorityFn(prifn_t priFn)
{
		// Warning if priority is unchanged
		if(priority == priFn)
		{
			cout << "WARNING: Priority Fn unchanged" << endl;
		}
		// Creates temporary heap
		PQueue temp(priFn);
		// Inserts original heap's node to temp based on changed priority
		while(_heap != nullptr)
		{
				temp.insertPatient(_heap->_patient);
				getNextPatient();
		}
		// Temporary heap becomes original heap
		_heap = temp._heap;
		_size = temp._size;
		// Temporary heap becomes a shallow copy of original heap
		// therefore, is pointer to null and deleted
		temp._heap = nullptr;
		priority = priFn;
}

void PQueue::dump() const
{
		inOrderDump(_heap);
		cout << endl;
}

void PQueue :: preOrderDump(Node* temp) const
{
		// Dumps patient details in preOrder traversal
		if(temp != nullptr)
		{
			cout  << "[" << temp->_patient.getTriage() << "] "
					<< temp->getPatient() << endl;
			preOrderDump(temp->_left);
			preOrderDump(temp->_right);
		}
}
void PQueue :: inOrderDump(Node* temp) const
{
		// Dumps patient triage and name in inOrder traversal
		if(temp != nullptr)
		{
		  cout << "(";
		  inOrderDump(temp->_left);
		  cout << temp->_patient.getTriage() << ":" << temp->_patient.getPatient();
		  inOrderDump(temp->_right);
		  cout << ")";
		}
}
Node* PQueue :: preOrderCopy(Node* rhs)
{
		if(rhs == nullptr)
		{
			return rhs;
		}
		// Creates copy with preOrder traversal
		Node* temp = new Node(rhs->_patient);
		temp->_left = preOrderCopy(rhs->_left);
		temp->_right = preOrderCopy(rhs->_right);
		return temp;
}
void PQueue :: clearHelper(Node* temp)
{
		// Clears tree using postOrder traversal
        if(temp)
        {
			clearHelper(temp->_left);
			clearHelper(temp->_right);
			delete temp;
        }
}
void PQueue :: swap(Node* parent)
{
		// Swaps parent's left/right child
        Node* temp = parent->_left;
        parent->_left = parent->_right;
        parent->_right = temp;
}

Node* PQueue :: mergeHelper(Node *heap_1, Node *heap_2)
{
		// Base cases for recursion
		if(heap_1 == nullptr)
		{
			return heap_2;
		}
		else if(heap_2 == nullptr)
		{
			return heap_1;
		}

		// Gets priority of nodes by function pointer
		int pr_1 = (*priority)(heap_1->_patient);
		int pr_2 = (*priority)(heap_2->_patient);
		if(pr_1 > pr_2)
		{
			// Swaps heap_1 and heap_2's values
			Node* temp = heap_1;
			heap_1 = heap_2;
			heap_2 = temp;
		}
		// Unconditional swap of heap_1
		swap(heap_1);
		// Recursion assignment for heap_1's left
		heap_1->_left = mergeHelper(heap_2, heap_1->_left);

		return heap_1;
}
ostream& operator<<(ostream& sout, const Patient& patient) {
  sout << "Patient: " << patient.getPatient() << ", triage: " << patient.getTriage()
	   << ", temperature: " << patient.getTemperature() << ", oxygen: " << patient.getOxygen() << ", RR: "
	   << patient.getRR() << ", HR: " << patient.getHR() << ", BP: " << patient.getBP();
  return sout;
}
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getPatient();
  return sout;
}


