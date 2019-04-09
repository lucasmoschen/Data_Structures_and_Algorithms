#include <iostream>
#include <exception>

using namespace std;

/////Node is a template/////
template <typename U>
struct Node{
    U data;
    Node *pNext;

    Node(U x):data(x), pNext(NULL){}
};

/////Exception class/////
struct NotFoundException: public exception {
	NotFoundException(){}
	public:
    	const char * what () const throw () {
    	  return "Element not found";
   	}
};

/////LinkedList is a template/////
template <typename L>
class LinkedList{
private:
	Node<L> *pRoot;
    int length;

public:
	
/////constructor//////
	
	template<typename T, typename... Args>
	LinkedList<L>(T x, Args... values): pRoot(NULL), length(0){
		insert(x);
		insert(values...);
	}
	template<typename T>
	LinkedList<L>(T x) {
		insert(x);
	}
	
//////Iterator//////
	
class Iterator {
		Node<L> *pNodo;
	public:
		Iterator() {pNodo = NULL;}
		Iterator(Node<L> *pNode) {pNodo = pNode;}
		Node<L>* node() {return pNodo;}
		void operator=(Iterator it) {pNodo = it.node();}
		
		bool operator!=(Iterator it) {return pNodo != it.node();}
		bool operator==(Iterator it) {return pNodo == it.node();}
		Iterator operator++() {pNodo = pNodo->pNext;}
		L operator*() {return pNodo->data;}
	};
	
	Iterator begin() {return pRoot;}
	Iterator end() {return NULL;}
    
    bool find(L x, Node<L> **&pNode) {
        pNode = &pRoot;
        while(*pNode) {
            if ((*pNode)->data==x) return true;
            pNode = &((*pNode)->pNext);
        }
        return 0;
    }

	template<typename T>
    void insert(T x) {
        Node<L> **pNode;
        if ((find(x, pNode))) return;
        Node<L> *newNode = new Node<L>(x);
        newNode->pNext = *pNode;
        *pNode = newNode;
        length++;
    }
    
    template<typename T, typename... Args>
	insert(T fvalue, Args... values) {
		insert(fvalue);
		insert(values...);
	}


    void print() {
        Node<L> *obj = pRoot;
        while(obj) {
            cout << obj->data << " ";
            obj=obj->pNext;
        }
        cout << endl;
    }

    void remove(L x) {
        Node<L> **pNode;
        if(!find(x, pNode)){
        	throw NotFoundException();
		}
		else{
        	*pNode = (*pNode)->pNext;
		}
    }
    
/////destructor/////
    
    ~LinkedList<L>(){
	Node<L> *pNode = pRoot;
	Node<L> *temp;
		while(pNode!=NULL){
			temp = pNode->pNext;
			delete pNode;
			pNode = temp;
			cout << "Deleted" << " ";
		};
		cout << endl;
		cout << "All deleted";
		cout << endl;		
	};
};

int main() {
	LinkedList<int> ilist(1,10,3);
	ilist.print();
    LinkedList<float> flist(1.2,1.4,100000);
	flist.print();
	LinkedList<string> slist("one", "two", "three");
	slist.print();	
	LinkedList<int> list1(1,2,10,2,3); //observar que a lista não adiciona dois valores iguais
	LinkedList<int>::Iterator it;
	for(it=list1.begin();it!=list1.end();++it){
		cout << *it << " ";
	}
	cout << endl;
	try{
		ilist.remove(20);
	}catch(const NotFoundException& e){
		cerr << e.what();
	}
	cout << endl;
		
    return 0;
}
