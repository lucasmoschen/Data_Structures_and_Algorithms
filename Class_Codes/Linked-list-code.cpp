#include <iostream>

using namespace std;

struct Node{ //define o tipo de dado Node, com um ponteiro pnext e um inteiro, o dado
    int data;
    Node *pNext; //ponteiro a um "Node"

    Node(int x):data(x), pNext(NULL){} //Define o nó root
};

//o código em public pode ser acessado em qualquer parte do código, na classe. Enquanto private só pode ser acessado de forma indireta.
//Apenas funções amigas e a classe podem acessar o código dentro de private.
class LinkedList{
private: 
    Node *pRoot;
    int length;

public:
    LinkedList(): pRoot(NULL), length(0) {} 

    bool find(int x, Node **&pNode) { 
        pNode = &pRoot;
       while(*pNode) {
            if ((*pNode)->data==x) return true;
            pNode = &((*pNode)->pNext);
        }
        return 0;
    }

	bool find_class(int x){
		Node *p = pRoot;
		while(p!=NULL){
			if(p->data==x) return true;
			p = p->pNext;
		}
		return false;
	}

    void insert(int x) {
        Node **pNode; 
        if ((find(x, pNode))) return;
        Node *newNode = new Node(x); 
        newNode->pNext = *pNode; //-> é um operador correspondente ao . da classe, mas se relaciona a ponteiros
        *pNode = newNode;
       length++;
    }

    void print() {
        Node *obj = pRoot;
        while(obj) {
            cout << obj->data  << " ";
            obj=obj->pNext;
        }
        cout << endl;

    }

    void remove(int x) {
        Node **pNode;
        if(!find(x, pNode)) return;
        *pNode = (*pNode)->pNext;
    }
};

int main() {
    LinkedList list;
	list.insert(2);
	list.insert(3);
	list.insert(4);
	list.remove(2);
    list.print();

    return 0;
}
