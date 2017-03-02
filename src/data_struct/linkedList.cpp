#include <iostream>
#include <string>
#include <memory>

using namespace std;

/*
References:
* http://codereview.stackexchange.com/questions/129035/building-a-simple-singly-linked-list-in-c11
* https://www.youtube.com/watch?v=NobHlGUjV3g&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P&index=3
* http://stackoverflow.com/questions/20226797/print-linkedlist-recursively-using-c

Compile
	g++ -std=c++11 linkedList.cpp -o linkedList
*/

template <class someType>
class LinkedList {
private:
	class Node {
	public:
		someType data;
		shared_ptr<Node> refNext;
	};
	shared_ptr<Node> m_head = nullptr;
	shared_ptr<Node> m_curr = nullptr;
public:
	void AddItem(someType value){
		// Create new node
		//Node *newItem_ptr = new Node{value,nullptr};
		shared_ptr<Node> newItem_ptr (new Node{value,nullptr});

		// Is the begining of the list
		if (m_head == nullptr) {
			m_head = newItem_ptr;
			m_curr = newItem_ptr;
			m_head->refNext = nullptr;
			m_curr->refNext = nullptr;
		} else {
			// Not beginning
			m_curr->refNext = newItem_ptr;
			// Point to the new element
			m_curr = newItem_ptr;
		}
	}

	void printList() {
		// This part is complexity O(n)
		for (auto n=m_head; n != nullptr; n=n->refNext){
			cout << n->data << endl;
		}
	}

	void printListRecursive(shared_ptr<Node> m_curr) {
		// All recursive functions must have some sort of if-statement to stop
		if (m_curr->refNext == nullptr)
		{
			return;
		} else {
			cout << m_curr->data << endl;
			printListRecursive(m_curr->refNext);
		}
	}
	void printListRecursive()
	{
		printListRecursive(m_head);
	}

	void DeleteItem(int pos){
		// Point with a shared_ptr to the head
		auto n=m_head;
		// If you choose the first position
		if (pos == 0){
			// Head will point to the second node
			m_head = n->refNext;
		} else {
			// Fix the references of the list
			for (auto idx = 0; idx < pos-1; idx++){
				n = n->refNext;
			}
			// Now n points to the element before the delete
			auto n2 = n->refNext;
			n->refNext = n2->refNext;
		}
	}

	shared_ptr<LinkedList> CreateCopy(){
		// Avoid copy empty list
		if (m_head == nullptr)
			return nullptr;
		// Create a new instance of the object
		shared_ptr<LinkedList> newList = shared_ptr<LinkedList>(new LinkedList);

		// Now iterate on the current list
		for (auto n=m_head; n != nullptr; n=n->refNext){
			// Create a new element
			newList->AddItem(n->data);
		}

		return newList;
	}

};

int main(){
	cout << "Example linked list" << endl;
	LinkedList<string> lList;
	lList.AddItem("Leo");
	lList.AddItem("Aline");
	lList.AddItem("Sofia");
	lList.AddItem("Flop");
	lList.AddItem("Marcos");
	lList.AddItem("Helena");
	lList.AddItem("Marcia");
	lList.AddItem("Leticia");
	lList.printList();

	cout << "Delete a position:";
	int position;
	cin >> position;
	lList.DeleteItem(position);
	lList.printList();

	shared_ptr<LinkedList<string>> lListCopy = lList.CreateCopy();
	cout << endl << endl << "Print a copy of the list" << endl;
	lListCopy->printListRecursive();

}
