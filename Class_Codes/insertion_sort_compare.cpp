#include <iostream> //importa o módulo iostream, muito utilizada
#include <stdlib.h>  //importa aleatoriedade
#include <time.h>
#include <fstream> //work with csv
#include <string>
#include <iterator>
#include <vector>
#include <list>

using namespace std;

float insertion_sort_vector(vector<int> vec) {
	clock_t tempo;
	tempo = clock();
	int i, key, j;	
	for (i = 0;i<vec.size();i++){
		key = vec[i];
		j = i - 1;
		while (j >= 0 and vec[j] > key){
			vec[j+1] = vec[j];
			j = j - 1;			
		}
		vec[j+1] = key;
	}
	float t1 = 1.0*(clock() - tempo)/(CLOCKS_PER_SEC);
	return t1;	
}

float insertion_sort_list(list<int> l){
	clock_t tempo2;
	tempo2 = clock();
	list<int>::iterator it;
	list<int>::iterator it2;
	int key;	
	for (it = l.begin(); it != l.end(); it++){
		key = *it;
		it2 = it;
		if(it2 != l.begin()){
			--it2;
			while (it2 != l.begin() and *it2 > key) --it2;
			if (key >= *it2) ++it2;
			l.insert(it2,key);
			l.erase(it);
		}
	}
	float t2 = 1.0*(clock() - tempo2)/(CLOCKS_PER_SEC);
	return t2;
}

int main() {
	int i;
	float t_vector, t_list;
	fstream myfile;
	fstream myfile2;
	myfile.open("vector.csv",fstream::out);
	myfile2.open("list.csv",fstream::out);
	vector<int> a1;
	list<int> a2;
	for (i = 1000; i < 100000; i = i + 1000){
		int j;
		for (j = 0; j < i; j++){
			a1.push_back(rand()%1000);
			a2.push_back(rand()%1000);	
		}
		t_vector = insertion_sort_vector(a1);
		t_list = insertion_sort_list(a2);
		string t1_string = to_string(t_vector);
		string t2_string = to_string(t_list);
		string i_string = to_string(i);
		myfile << i_string << ", " << t1_string;
		myfile << "\n";
		myfile2 << i_string << ", " << t2_string;         
		myfile2 << "\n";
		a1.clear();
		a2.clear();
	}
	myfile.close();
	myfile2.close();
	return 0;
}
