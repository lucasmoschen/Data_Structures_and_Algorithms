#include <iostream> //importa o módulo iostream, muito utilizada
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;

template<class T>
void print(vector<T> &vec) {
	std::copy(vec.begin(),vec.end(), ostream_iterator<T>(cout," "));
	cout << endl; //endline
	
	//vector<int>::iterator iter;
	//for (iter = vec.begin(); iter != vec.end(); iter++){
	//	cout << *iter << 
	//}
}

template<class T>
void insertion_sort(vector<T> &vec) {
	int i, j;	
	for (i = 0;i<vec.size();i++){
		T key = vec[i];
		j = i - 1;
		while (j >= 0 and vec[j] > key){
			vec[j+1] = vec[j];
			j = j - 1;			
		}
		vec[j+1] = key;
	}
}

int main() {
	vector<float> a = {4.0,5.0,6.0,1.1,41.0,5.0,8.0,2.0,1.0};
	print(a);
    insertion_sort<float>(a);
    print(a);
		
	return 0;
}
