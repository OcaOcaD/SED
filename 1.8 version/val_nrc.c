#include <stdio.h>

void val();

int main(){
	val();
	return 0;
}

void val(){
	char sin_validar[32];
	char resultante[7];
	int index, index_val, i;
	
	fflush(stdin); gets(sin_validar);
	index = 0;
	index_val = 0;
	
	while(sin_validar[index] != '\0' && index_val < 7){
		if(sin_validar[index] > 47 && sin_validar[index] < 58){
			resultante[index_val] = sin_validar[index];
			index_val++;
		}else{
			printf("%c Ignorado\n", sin_validar[index]);
		}
		index++;
	}
	
	printf("Resultante: ");
	for(i = 0; resultante[i] != '\0' && i < 6; i++){
		printf("%c", resultante[i]);
	}
}
