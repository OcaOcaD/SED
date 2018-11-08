/*
  Name        : Terminal color
  Author      : Mario Ronzon
  Date        : 20 octubre 2018
  
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

/* Estructura global */
struct{
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	COORD dwpos;
}Terminal;

/* Prototipos de funciones */
void Terminal_Init();
void Terminal_Color(short);
void Terminal_Save();
void Terminal_Restore();
void gotoxy(short, short);

void Terminal_Init(){
	Terminal.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Terminal_Save();
}//end function

void Terminal_Save(){
	/* Guardar los atributos actuales */
    GetConsoleScreenBufferInfo(Terminal.hConsole, &Terminal.consoleInfo);
    Terminal.saved_attributes = Terminal.consoleInfo.wAttributes;
}//end function

void Terminal_Restore(){
	/* Restaurar los atributos originales */
    SetConsoleTextAttribute(Terminal.hConsole, Terminal.saved_attributes);
}//end function

void Terminal_Color(short arg){
	/*Definir color de terminal*/
	SetConsoleTextAttribute(Terminal.hConsole, arg);
}//end function

void gotoxy(short x, short y){
	Terminal.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Terminal.dwpos.X = x;
	Terminal.dwpos.Y = y;
	SetConsoleCursorPosition(Terminal.hConsole, Terminal.dwpos);
}//end function
