/***
En éste archivo se encuentran funciones para controlar los tipos de entrada de datos y evitar fallos al ejecutar
*/
/*
  Name        : Diversas funciones para evitar errores con los tipos de entrada de datos
  Author      : Donaldo García
  Date        : 05 Noviembre 2018
  
  Description : Cabecera que facilita la
  				forma en la que definimos
  				los colores de la terminal
  				de windows.
  Notes:		Solo sirve para la terminal
  				de windows.
  				Para utilizar primero debe
  				incluir <windows.h>, luego
  				en la funcion main debe llamar
				a la funcion Terminal_init();
				esto para inicializar de
				forma correcta todo y evitar
				resultados inesperados.
				El argumento de tipo short
				que recibe Terminal_color();
				debe ser un entero en un
				rango entre 0 y 255.
  Version     : 1.00
  
  Shared for  : es.stackoverflow.com
  				Universidad de Guadalajara
  				C.U.C.E.I.
  
*/
/*Funcion que devuelve verdadero si el caracter es un digito y falso si no*/
bool onlyNumbers(char number){			
	if	( number < '0' || number > '9' ){
		return false;
	}else{
		return true;
	}
}
bool oknrc(string nrc){
	bool state = true;
	if	( nrc.length() != 5 ){	//Si el NRC tiene una longitud diferente de 5, está mal escrito
		//cout <<"Wrong lenght"<<endl;
		return false;
	}
	if	( nrc[0] < 'A' || nrc[0] > 'Z'  ){ //El primer carácter debe de ser una letra mayuscula.
		if	( nrc[0] > 'a' && nrc[0] < 'z' ){
			nrc[0] = toupper( nrc[0] );	//convertir a mayusculas si era minusculas
		}else{
			return false;
		}
	}
	for	( int i = 1; i <= 4; i++ ){	//4 porque todos los NRC tienen esa longitud
		//Los demás caráctere deben de ser números. así que lo reducimos a esa posibilidad
		if	( nrc[i] < '0' || nrc[i] > '9' ){ //< 0 || > 9	
			//cout <<"Character: "<< i <<", "<< nrc[i] << " no es un numero" << endl;
			return false;
		}else{
			//cout <<"Character: "<< i <<", "<< nrc[i] << " SIII es un numero" << endl;
		}
	}
	return state;
}
