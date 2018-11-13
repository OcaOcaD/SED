#include <iostream>
#include <string>

using namespace std;

string val(string sin_validar){
	string resultante;
	int index, index_val, i;
	
	index = 0;
	index_val = 0;
	
	while(sin_validar[index] != '\0' && index_val < 7){
		if(sin_validar[index] > 47 && sin_validar[index] < 58){
			resultante[index_val] = sin_validar[index];
			index_val++;
		}else{
			//ignore
		}
		index++;
	}
	return resultante;
}

int main(){
	
	string cake, valido;
	cout <<"Dame cake"<<endl;
	cin >> cake;
	valido = val(cake);
	cout << valido;
	return 0;
}

