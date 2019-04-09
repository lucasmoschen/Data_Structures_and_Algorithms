#include <iostream>
#include <iomanip>

using namespace std;

template<typename U>
struct Node{
    U data;
    Node<U> *pChild[2];

    Node(U x):data(x){
    	pChild[0] = pChild[1] = NULL;
	}
};

template<typename T>
class LinkedList{
private:
    Node<T> *pRoot;

public:
LinkedList<T>(): pRoot(NULL){}

    bool find(T x, Node<T> **&pNode) {
        pNode = &pRoot;
        while(*pNode) {
            if ((*pNode)->data==x) return true;
            pNode = &((*pNode)->pChild[(*pNode)->data < x]);
        }
        return 0;
    }
    
	//bool find_class(int x){
	//	Node *p = pRoot;
	//	while(p!=NULL){
	//		if(p->data==x) return true;
	//		p = p->pNext;
	//	}
	//	return false;
	//}


    void insert(T x) {
        Node<T> **pNode;
        if ((find(x, pNode))) return;
        Node<T> *newNode = new Node<T>(x);
        *pNode = newNode;
    }
    
    void print() {
    	print(pRoot);
		cout << endl;
	}

    void print(Node<T> *p, int indent = 0) {
        while(p) {
        	print(p->pChild[1], indent +6);
            cout << setw(indent) << " ";
            print(p->pChild[0], indent+6);
        }
    }
};

int main() {
	
    LinkedList<int> list;
    list.insert(6);
	list.insert(25);
	list.insert(5);
	list.insert(4);
	list.print();
	//list.remove(2.4);
	//list.print();
	//list.~LinkedList();

    return 0;
}
