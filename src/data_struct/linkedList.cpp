#include <iostream>
#include <string>
#include <memory>

using namespace std;

/*
References:
* http://codereview.stackexchange.com/questions/129035/building-a-simple-singly-linked-list-in-c11
* https://www.youtube.com/watch?v=NobHlGUjV3g&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P&index=3

Compile	
	g++ -std=c++11 linkedList.cpp -o linkedList
*/

template <class someType>
class LinkedList {
private:
	class Node {
	public:
		someType data;
		Node* refNext;
	};
	Node* m_head = nullptr;
	Node* m_curr = nullptr;
public:
	void AddItem(someType value){
		// Create new node
		Node *newItem_ptr = new Node{value,nullptr};
		//shared_ptr<Node> newItem_ptr (new Node{value,nullptr});
				
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
		for (auto n=m_head; n != nullptr; n=n->refNext){
			cout << n->data << endl;
		}
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

}