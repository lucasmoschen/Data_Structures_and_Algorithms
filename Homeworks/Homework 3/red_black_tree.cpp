#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

struct Node {
    int data;
    Node *pChild[2];
    Node *parent;
    int color; //1 - black, 0 - red, 2 - double black

    Node(int x, int color): data(x), color(0), parent(nullptr){
        pChild[0] = pChild[1] = nullptr;
    }
	Node *sibling() { 
		if (parent == NULL) return NULL; 
		if (parent->pChild[data < parent->data]) return parent->pChild[data < parent->data];
	}
	
	Node *uncle() { 
		if (parent == NULL or parent->parent == NULL) return NULL; 
		if (parent->parent->pChild[parent->data < parent->parent->data]){
			return parent->parent->pChild[parent->data < parent->parent->data];	
		}
	}
	
	bool hasRedChild() { 
    return (pChild[0]!=NULL && pChild[0]->color == 0) or
    		(pChild[1]!=NULL && pChild[1]->color == 0);
	}
};

class RBTree {
protected:
    Node *pRoot;

public:
	
	template<typename T, typename... Args>                 //Constructor with Variadic Templates
    RBTree(T x, Args... values): pRoot(nullptr) {
		insert(x);
		insert(values...);
	}
	
	template<typename T>
	RBTree(T x){
		insert(x);
	}

    bool find(int x) {
        Node **p;
        return find(x, p);
    }
    
    template<typename T, typename... Args>
	void insert(T x, Args... values) {
		insert(x);
		insert(values...);
	}
	
	template<typename T>                                       	//Function insert
    void insert(T x) {												
        Node **p;						
        Node **pfather;
        if (!find(x, p)) {
        	pfather = p;										//the function find returns a leave, the father of our son.
        	if (*p){
        		p = &((*p)->pChild[(*p)->data < x]);
			}
            *p = new Node(x,0);
            (*p)->parent = *pfather;                            
			if (p == pfather) (*p)->parent = nullptr;           //just in case of the root
			recolor_node(*p);									//recoloring to black or red
		}                                   
	}
	
	template<typename T, typename... Args>
	void remove(T x, Args... values){
		remove(x);
		remove(values...);
	}
	
	template<typename T>
    void remove(T x) {
        Node **p;
        if(find(x, p))
            remove(*p);
    }

    void print() {
        print(pRoot);
        cout << endl;
        cout << "------------------------------------" << endl;
    }
    
private:
	
    bool find(int x, Node **&p) {
        p = &pRoot;
        Node **pfather = &pRoot;
        while(*p) {
            if ((*p)->data==x) return true;
            pfather = p;
            p = &((*p)->pChild[(*p)->data < x]);
        }
        p = pfather;                                             //return the pointer to the father
        return false;
    }
    
    void remove(Node *p) {
        if (!p->pChild[0] || !p->pChild[1]){						//o nó tem no máximo um filho
        	delete_case1(p);
		}else{
            Node **succesor = &(p->pChild[1]);    
            find_min(succesor,0);
            if ((*succesor)->color == 0 ){
            	int data = (*succesor)->data;
				remove(*succesor);
				p->data = data;
			}else{
				Node **precessor = &(p->pChild[0]);
            	find_min(precessor,1);
				int data = (*precessor)->data;
				remove(*precessor);
				p->data = data;			
			}
        }
    }
    
    void delete_case1(Node *p){                                   //caso em que o nó é a raiz
		if (p->parent==nullptr){
			if (p->pChild[p->pChild[1]!=nullptr]){
				pRoot = p->pChild[p->pChild[1]!=nullptr];
				(p->pChild[p->pChild[1]!=nullptr])->color = 1;
				p->pChild[p->pChild[1]!=nullptr]->parent = nullptr;				
			}
			else{
				pRoot = nullptr;
			}
		}
		else{
			delete_case2(p);
		}
	}
	
	void delete_case2(Node *p){									//caso em que o nó é vermelho ou tem um filho vermelho
		if (p->color == 0){
 			p->parent->pChild[p->data > p->parent->data] = nullptr;
 			return;
		}
		else{
			if (p->pChild[0] or p->pChild[1]){
				if (p->pChild[p->pChild[1]!=nullptr]->color ==  0 && p->pChild[p->pChild[1]!=nullptr]->sibling() == nullptr){
					p->pChild[p->pChild[1]!=nullptr]->color = 1; 
					replace_node(p,p->pChild[1]!=nullptr);
				}
				else if (p->parent->color == 1) delete_case3(p);
				else delete_case4(p);
			}
			else if (p->parent->color == 1) delete_case3(p);
			else delete_case4(p);	
		}
	}
	
	void delete_case3(Node *p){               //caso em que o nó é preto e não tem filhos não pretos
		Node *pbrother = p->sibling();
		bool brother = p->data < pbrother->data;
		if (pbrother->color == 1){            // caso em que a cor do irmão é preta
			if (brother == 1){
				if (pbrother->hasRedChild()){
					if (pbrother->pChild[1]){
						if (pbrother->pChild[1]->color == 1){
							pbrother->pChild[0]->color = 1;
							align_nodes(pbrother);
							left_rotate(p->parent);
							p->parent->pChild[0] = nullptr;							
						}else{
							pbrother->pChild[1]->color = 1;
							left_rotate(p->parent);
							p->parent->pChild[0] = nullptr;
						}
					}else if(pbrother->pChild[0]){
						pbrother->pChild[0]->color = 1;
						align_nodes(pbrother);
						left_rotate(p->parent);
						p->parent->pChild[0] = nullptr;
					}else delete_case5(p);		
				}else delete_case5(p);	
			}else{          
				if (pbrother->hasRedChild()){
					if (pbrother->pChild[0]){
						if (pbrother->pChild[0]->color == 1){
							pbrother->pChild[1]->color = 1;
							align_nodes(pbrother);
							right_rotate(p->parent);
							p->parent->pChild[1] = nullptr;							
						}else{
							pbrother->pChild[0]->color = 1;
							right_rotate(p->parent);
							p->parent->pChild[1] = nullptr;
						}
					}else if(pbrother->pChild[1]){
						pbrother->pChild[1]->color = 1;
						align_nodes(pbrother);
						right_rotate(p->parent);
						p->parent->pChild[1] = nullptr;
					}else delete_case5(p);		
				}else delete_case5(p);	
			}
		}
		else delete_case6(p);
	}
	
	void delete_case4(Node *p){                        //caso em que o pai é vermelho
		if (p->pChild[0] == nullptr && p->pChild[1] == nullptr){
			p->parent->parent->pChild[p->parent->data > p->parent->parent->data] = p->sibling();
			p->sibling()->parent = p->parent->parent;
			p->sibling()->pChild[p->data > p->parent->data] = p->parent;
			p->parent->parent = p->sibling();
			p->parent->pChild[0] = p->parent->pChild[1] = nullptr;			
		}else{
			if (p->data < p->parent->data){
				if(p->sibling()->pChild[0]->color == 1) left_rotate(p->parent);
				else{
					p->parent->color = 1;
					right_rotate(p->sibling());
					left_rotate(p->parent);					
				}
				if (p->parent) p->parent->pChild[0] = nullptr;
			}else{
				if(p->sibling()->pChild[1]->color == 1) right_rotate(p->parent);
				else{
					p->parent->color = 1;
					left_rotate(p->sibling());
					right_rotate(p->parent);
				}
				if (p->parent) p->parent->pChild[1] = nullptr;
			}
		}
	}
	
	void delete_case5(Node *p){                             //caso em que o irmão é preto e não tem filhos
		p->sibling()->color = 0;
		Node *pfather = p->parent;
		Node *granpa = p->parent->parent;
		if (p->parent->parent == nullptr){
			p->parent->color=1;
			p->parent->pChild[p->data > p->parent->data] = nullptr;
			return;	
		}
		delete_case2(p->parent);
		granpa->pChild[pfather->data > granpa->data] = pfather;		
		p->parent->pChild[p->data > p->parent->data] = nullptr;		
	}
	
	void delete_case6(Node *p){                               //caso em que o irmão é vermelho
		bool brother = p->data < p->parent->data;
		Node *pbrother = p->sibling();
		if (p->pChild[0] == nullptr && p->pChild[1] == nullptr){
			if (brother == 1){
				bool compare;
				if (pbrother->pChild[0] == nullptr){
					p->parent->pChild[0] = nullptr;
					return;
				}
				if (pbrother->pChild[0]->pChild[0]) compare = 1;
				else compare = 0;
				Node *temp = pbrother->pChild[0];
				pbrother->parent->color = 0;
				pbrother->color = 1;
				left_rotate(p->parent);
				left_rotate(p->parent);
				if (compare==1){
					p->parent->color = 1;
					align_nodes(p->parent);
					right_rotate(temp);
				}
				p->parent->pChild[0] = nullptr;			
			}else{
				bool compare;
				if (pbrother->pChild[1] == nullptr){
					p->parent->pChild[1] = nullptr;
					return;
				}
				if (pbrother->pChild[1]->pChild[1]) compare = 1;
				else compare = 0;
				Node *temp = pbrother->pChild[1];
				pbrother->parent->color = 0;
				pbrother->color = 1;
				right_rotate(p->parent);
				right_rotate(p->parent);
				if (compare==1){
					p->parent->color = 1;
					align_nodes(p->parent);
					left_rotate(temp);
				}
				p->parent->pChild[1] = nullptr;
			}	
		}else{
			if (brother == 1){
				if (pbrother->pChild[0]->pChild[0]->color == 1){
					pbrother->color = 1;
					p->parent->color = 0;
					left_rotate(p->parent);
					left_rotate(p->parent);
				}else{
					pbrother->color = 1;
					left_rotate(p->parent);
					right_rotate(p->sibling());
					left_rotate(p->parent);
				}
				if (p->parent) p->parent->pChild[0] = nullptr;
			}else{
				if (pbrother->pChild[1]->pChild[1]->color == 1){
					pbrother->color = 1;
					p->parent->color = 0;
					right_rotate(p->parent);
					right_rotate(p->parent);
				}else{
					pbrother->color = 1;
					right_rotate(p->parent);
					left_rotate(p->sibling());
					right_rotate(p->parent);
				}
				if (p->parent) p->parent->pChild[1] = nullptr;			
			}
		}		
	}
	
	void align_nodes(Node *p){
		if (p->parent->data < p->data){
			p->pChild[0]->parent = p->parent;
			Node *temp = p->pChild[0]->pChild[1];
			p->pChild[0]->pChild[1] = p;
			p->parent->pChild[1] = p->pChild[0];
			p->parent = p->pChild[0]; 
			p->pChild[0] = temp; 
		}
		else{
			p->pChild[1]->parent = p->parent;
			Node *temp = p->pChild[1]->pChild[0];
			p->pChild[1]->pChild[0] = p;
			p->parent->pChild[0] = p->pChild[1];
			p->parent = p->pChild[1]; 
			p->pChild[1] = temp;			
		}
	}
    
    void replace_node(Node *&n, int child){
    	(n->pChild[child])->parent = n->parent;
    	(n->parent)->pChild[n->data > (n->parent)->data] = n->pChild[child];
	}

    void find_min(Node **&p,int i) {
        while((*p)->pChild[i]){
            p = &((*p)->pChild[i]);
        }
    }

    void print(Node *p, int indent=0) {
        if (p) {
            print(p->pChild[1], indent+8);
            cout << setw(indent) << ' ';
            cout<< p->data << " " << p->color << " " ;
            if (p->parent){
            	cout << (p->parent)->data << " ";
			}
			cout << endl;
            print(p->pChild[0], indent+8);
        }
    }
    
	void recolor_node(Node *p) {
		if (p->parent == nullptr) {
			p->color = 1;
		}else if (p->parent->color == 1) {
			return;
		}else if (p->uncle()) {
			if (p->uncle()->color == 0) recolor1(p);
			else recolor2(p);
		}else recolor2(p);
	}
	
	void recolor1(Node *p){
		p->parent->color = 1;
		p->uncle()->color = 1;
		p->parent->parent->color = 0;
		recolor_node(p->parent->parent);
	}
	
	void recolor2(Node *p){
    	Node* pfather = p->parent;
 		Node* pgranpa = p->parent->parent;
 		if (p == pfather->pChild[1] && pfather == pgranpa->pChild[0]){
 			left_rotate(pfather);
			p = p->pChild[0];	
		}else if(p == pfather->pChild[0] && pfather == pgranpa->pChild[1]){
			right_rotate(pfather);
			p = p->pChild[1];
		}
 		recolor3(p);		
	}
	
	void recolor3(Node *p){
		Node *pfather = p->parent;
		Node *pgranpa = p->parent->parent;
		if (p == pfather->pChild[0]) right_rotate(pgranpa);
		else left_rotate(pgranpa);
		pfather->color = 1;
		pgranpa->color = 0;
	}
    
	
	void right_rotate(Node *p){
		if (p->parent){
			(p->parent)->pChild[p->data > (p->parent)->data]= p->pChild[0];	
		}
		(p->pChild[0])->parent = p->parent;
		Node *temp;
		temp = (p->pChild[0])->pChild[1];
		(p->pChild[0])->pChild[1] = p; 
		if (p->parent==nullptr){
			pRoot = p->pChild[0];
		}
		p->parent = p->pChild[0];
		p->pChild[0] = temp;
		if (p->pChild[0]){(p->pChild[0])->parent = p;} 		
	}
	
	void left_rotate(Node *p){
		if (p->parent){
			(p->parent)->pChild[p->data > (p->parent)->data]= p->pChild[1];	
		}
		(p->pChild[1])->parent = p->parent;
		Node *temp = (p->pChild[1])->pChild[0];
		(p->pChild[1])->pChild[0] = p; 
		if (p->parent==nullptr){
			pRoot = p->pChild[1];
		}
		p->parent = p->pChild[1];
		(p->pChild[1]) = temp;
		if (p->pChild[1]){(p->pChild[1])->parent = p;}	
	}
	
	bool isRBTree(Node *p){
		if (p->color == 0) return 0;
		else{
			while(p){
				
			}
		}
	}
    
};

int main() {
    RBTree tree(41,38,31,12,19,8);
    tree.remove(8);
    tree.insert(32,11);
    tree.print();
    tree.remove(41);
    tree.print();
    
	RBTree tree2(5,3,4,20,13,17,2,15,41,45,14,52,51,12,47,65,35);
	tree2.print();
	tree2.insert(4,100,6,42,57,91,48,50,30,41,4,5,6);
	tree2.print();
	tree2.remove(50,47,17,91,14,35,30,48,42,41,100,65);
	tree2.print();
	
	RBTree tree3(1,2,3);
	for (int i = 0; i < 50; i++){
		int a = rand() %50;
		tree3.insert(a);
	}
	tree3.print();
	
	for (int j = 0; j < 50; ++j){
		tree3.remove(rand()%50);
	}
	tree3.print();
}
