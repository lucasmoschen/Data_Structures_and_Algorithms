#include <iostream> //importa o módulo iostream, muito utilizada
#include <vector>
#include <stdlib.h>  //importa aleatoriedade

using namespace std;

void print(vector<int> v) {
	for(int i=0; i<v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl; //endline
}

void insertion_sort(vector<int> vec) {
	int i, key, j;	
	for (i = 1;i<vec.size();i++){
		key = vec[i];
		j = i - 1;
		while (j >= 0 and vec[j] > key){
			vec[j+1] = vec[j];
			j = j - 1;			
		}
		vec[j+1] = key;
	}
	print(vec);
}

int main() {
	vector<int> a;
	int i,n;
	n = 100;
	for(i=0;i<n;i++){
		a.push_back(rand()%100);
	}
	print(a);
    insertion_sort(a);
		
	return 0;
}
