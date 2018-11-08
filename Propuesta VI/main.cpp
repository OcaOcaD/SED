//numero de compilaciones 375
#include <iostream>
#include <iomanip>//formato al texto
#include <string.h>//manejo de cadenas
#include <windows.h>//crear directorios y otros
#include <terminal.h>//diseño de terminal
#include <dirent.h>//obtener listado del directorio
#include <conio.h>//getch()
#include "curso.hpp"
cursos c;
alumnos a;

#define AL_REG 8
#define AL_GLO516

BOOL DirectoryExists(const char*);// verifica si existe un directorio
void dir_cursoExist();//........... verifica que la carpeta de cursos existe
void dir_alumnoExist();//verifica que la carpeta de alumnos exista
void read_data();
void loading_screen();//solo es de orden estetico

//OPCIONES ...... NIVEL 1
void menu_listener();
//.......................
void cursonuevo();
void listado_cursos();
void alumnonuevo();
void listado_alumno();
void buscar_alumno();
//OPCIONES ...... NIVEL 2
void opciones_cursos(int);
void opciones_alumno(int);
//.......................
void modif_curso();
void detalles_curso(int);
void listado_avance(int);
void incribir_alumno(int);

void modif_alumno(int);
//   inspeccionar es la misma
//OPCIONES ...... NIVEL 3
void opciones_avance(int, int);
//.......................
void dar_baja();
void modif_avance();
void inspeccionar(int);

int main(){
	int num_c;
	//iniciar la interfaz de la terminal
	Terminal_Init();
	//verificar que existan los directorios correspondientes
	dir_cursoExist();
	dir_alumnoExist();
	//leer todos los cursos y colocarlos en la lista
	read_data();
	//leer todos los alumnmos y colocarlos en la lista
	//pantalla de carga
	loading_screen();
	//delay time
	Sleep(1000);
	menu_listener();
	return 0;
}

BOOL DirectoryExists(const char* dirName){
	DWORD attribs = GetFileAttributesA(dirName);
  	if (attribs == INVALID_FILE_ATTRIBUTES){
    	return 0;
  	}
  	return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}

void dir_cursoExist(){
	const char direccion[] = "cursos";
	if(DirectoryExists(direccion) == 0){
		//SE CREA LA CARPETA COMO NOMBRE NRC
		if (CreateDirectory(direccion, NULL)){
			//El directorio fue creado exitosamente
		}else if (ERROR_ALREADY_EXISTS == GetLastError()){
			cout <<"ERROR: la carpeta ya existe";
		}else{
			cout <<"ERROR: error desconocido";
		}
	}else{
		cout <<"<dir> alumnos encontrado\n";
	}
}

void dir_alumnoExist(){
	const char direccion[] = "alumnos";
	if(DirectoryExists(direccion) == 0){
		//SE CREA LA CARPETA COMO NOMBRE NRC
		if (CreateDirectory(direccion, NULL)){
			//El directorio fue creado exitosamente
		}else if (ERROR_ALREADY_EXISTS == GetLastError()){
			cout <<"ERROR: la carpeta ya existe";
		}else{
			cout <<"ERROR: error desconocido";
		}
	}else{
		cout <<"<dir> alumnos encontrado\n";
	}
}

void read_data(){
	short num_c;
	short num_a;
	num_c = c.read_files();
	num_a = a.read_files();
	cout << "Cursos encontrados : " << num_c - 1 << endl;
	cout << "Alumnos encontrados: " << num_a - 1 << endl;
	return;
}

void loading_screen(){
	int i;
	
	cout << "\nCargando los datos\n" << "\n\n      Un momento...";
	gotoxy(6, 10);
	cout << '\xB0' << '\xB0' << '\xB0' << '\xB0' << '\xB0' << '\xB0' << '\xB0' << '\xB0';
	gotoxy(6, 10);
	for(i = 0; i < 8; i++){
		cout << '\xB2';
		Sleep(100);
	}
}

void menu_listener(){
	short estado;
	short caracter;
	
	estado = 1;
    do{
    	system("cls");
    	if(estado == 1){
			cout <<" >Nuevo curso\n  Listado de cursos\n  Nuevo alumno\n  Listado de alumnos\n  Buscar alumno";
		}else if(estado == 2){
			cout <<"  Nuevo curso\n >Listado de cursos\n  Nuevo alumno\n  Listado de alumnos\n  Buscar alumno";
		}else if(estado == 3){
			cout <<"  Nuevo curso\n  Listado de cursos\n >Nuevo alumno\n  Listado de alumnos\n  Buscar alumno";
		}else if(estado == 4){
			cout <<"  Nuevo curso\n  Listado de cursos\n  Nuevo alumno\n >Listado de alumnos\n  Buscar alumno";
		}else if(estado == 5){
			cout <<"  Nuevo curso\n  Listado de cursos\n  Nuevo alumno\n  Listado de alumnos\n >Buscar alumno";
		}
        caracter = getch();
        switch (caracter){
            case 72:
                //"Flecha ARRIBA\n"
                estado--;
                if(estado == 0){
                	estado = 5;
				}
                break;
            case 80:
                //"Flecha ABAJO\n"
                estado++;
                if(estado == 6){
                	estado = 1;
				}
                break;
            case 13:
                if(estado == 1){
                	cursonuevo();
				}else if(estado == 2){
					listado_cursos();
				}else if(estado == 3){
					alumnonuevo();
				}else if(estado == 4){
					listado_alumno();
				}else if(estado == 5){
					buscar_alumno();
				}
                break;
            case 8:
                //"Tecla BACKSPACE\n"
                break;
        }
    }while(caracter != 27);
}

void cursonuevo(){
	system("cls");
	cout<< "NUEVO CURSO" << endl;
	c.agregar();
	getch();
}

void listado_cursos(){
	int i;
	int nodos;
	short estado;
	short caracter;
	
	system("cls");
	cout << "LISTADO DE CURSOS" << endl;
	c.listado();
	nodos = c.cantidad();
	estado = 1;
	
    do{
    	gotoxy(1, estado);
    	cout << ">";
        caracter = getch();
        gotoxy(1, estado);
    	cout << " ";
        switch (caracter){
            case 72:
                //"Flecha ARRIBA\n"
                estado--;
                if(estado == 0){
                	estado = nodos;
				}
                break;
            case 80:
                //"Flecha ABAJO\n"
                estado++;
                if(estado == nodos + 1){
                	estado = 1;
				}
                break;
            case 13:
            	opciones_cursos(estado);
            	system("cls");
				cout << "LISTADO DE CURSOS" << endl;
				c.listado();
                break;
        }
    }while(caracter != 27 && caracter != 8);
}

void alumnonuevo(){
	a.nuevoalumno();
	getch();
}

void listado_alumno(){
	int i;
	short estado;
	short caracter;
	
	estado = 1;
	i = a.lista_alumnos();
    do{
        caracter = getch();
        switch (caracter){
            case 72:
                //"Flecha ARRIBA\n"
                gotoxy(0, estado);
                cout << "  ";
                estado--;
                if(estado == 0){
                	estado = i;
				}
				gotoxy(0, estado);
                cout << " >";
                break;
            case 80:
                //"Flecha ABAJO\n"
                gotoxy(0, estado);
                cout << "  ";
                estado++;
                if(estado == i + 1){
                	estado = 1;
				}
				gotoxy(0, estado);
                cout << " >";
                break;
            case 13:
            	opciones_alumno(estado);
            	a.lista_alumnos();
                break;
        }
    }while(caracter != 27 && caracter != 8);
}

void buscar_alumno(){
	string codigo;
	system("cls");
	cout << "Ingrese el codigo o apellidos: ";
	fflush(stdin); getline(cin, codigo);
	a.consulta(codigo.c_str());
	getch();
}

void opciones_cursos(int c){
	short estado;
	short caracter;
	
	estado = 1;
    do{
    	system("cls");
    	cout <<"Opcines para curso " << c << endl;
    	if(estado == 1){
			cout <<" >Modif. evaluacion\n  Detalles del curso\n  Avance del curso\n  Inscribir alumno";
		}else if(estado == 2){
			cout <<"  Modif. evaluacion\n >Detalles del curso\n  Avance del curso\n  Inscribir alumno";
		}else if(estado == 3){
			cout <<"  Modif. evaluacion\n  Detalles del curso\n >Avance del curso\n  Inscribir alumno";
		}else if(estado == 4){
			cout <<"  Modif. evaluacion\n  Detalles del curso\n  Avance del curso\n >Inscribir alumno";
		}
        caracter = getch();
        switch (caracter){
            case 72:
                //"Flecha ARRIBA\n"
                estado--;
                if(estado == 0){
                	estado = 4;
				}
                break;
            case 80:
                //"Flecha ABAJO\n"
                estado++;
                if(estado == 5){
                	estado = 1;
				}
                break;
            case 13:
            	if(estado == 1){
            		modif_curso();
				}else if(estado == 2){
					detalles_curso(c);
				}else if(estado == 3){
					listado_avance(c);
				}else if(estado == 4){
					incribir_alumno(c);
				}
                break;
        }
    }while(caracter != 27 && caracter != 8);
}

void opciones_alumno(int a){
	short estado;
	short caracter;
	
	estado = 1;
    do{
    	system("cls");
    	cout <<"Opcines para almuno " << a << endl;
    	if(estado == 1){
			cout <<" >Modif. datos\n  Inspeccionar";
		}else if(estado == 2){
			cout <<"  Modif. datos\n >Inspeccionar";
		}
        caracter = getch();
        switch (caracter){
            case 72:
                //"Flecha ARRIBA\n"
                estado--;
                if(estado == 0){
                	estado = 2;
				}
                break;
            case 80:
                //"Flecha ABAJO\n"
                estado++;
                if(estado == 3){
                	estado = 1;
				}
                break;
            case 13:
            	if(estado == 1){
            		modif_alumno(a);
				}else if(estado == 2){
					inspeccionar(a);
				}
                break;
        }
    }while(caracter != 27 && caracter != 8);
}

void modif_curso(){
	cout <<"\nAqui se modifica la evaluacion\n";
	getch();
}

void detalles_curso(int ca){
	system("cls");
	c.localizar(ca);
	getch();
}

void listado_avance(int cu){
	int i;
	short estado;
	short caracter;
	
	estado = 1;
	i = c.avance(cu);
    do{
    	
    	gotoxy(1, estado + 1);
        cout << ">";
        caracter = getch();
        gotoxy(1, estado + 1);
        cout << " ";
        switch (caracter){
            case 72:
                //"Flecha ARRIBA\n"
                estado--;
                if(estado <= 0){
                	estado = i - 1;
				}
                break;
            case 80:
                //"Flecha ABAJO\n"
                estado++;
                if(estado >= i){
                	estado = 1;
				}
                break;
            case 13:
            	opciones_avance(cu, estado);
            	c.avance(cu);
                break;
        }
    }while(caracter != 27 && caracter != 8);
}

void incribir_alumno(int cu){
	int i;
	short estado;
	short caracter;
	string codigo;
	
	estado = 1;
	i = a.lista_alumnos();
    do{
        caracter = getch();
        switch (caracter){
            case 72:
                //"Flecha ARRIBA\n"
                gotoxy(0, estado);
                cout << "  ";
                estado--;
                if(estado == 0){
                	estado = i;
				}
				gotoxy(0, estado);
                cout << " >";
                break;
            case 80:
                //"Flecha ABAJO\n"
                gotoxy(0, estado);
                cout << "  ";
                estado++;
                if(estado == i + 1){
                	estado = 1;
				}
				gotoxy(0, estado);
                cout << " >";
                break;
            case 13:
            	codigo = a.returncode(estado);
            	//a.inscribir(c, estado);
            	c.inscribir(cu, codigo.c_str());
            	a.lista_alumnos();
                break;
        }
    }while(caracter != 27 && caracter != 8);
}

void modif_alumno(int){
	cout <<"\nAqui se modifican datos del alumno\n";
	getch();
}

void opciones_avance(int cur, int al){
	short estado;
	short caracter;
	string codigo;
	
	estado = 1;
    do{
    	system("cls");
    	cout <<"opciones para alumno " << al << endl;
    	if(estado == 1){
			cout <<" >Dar de baja\n  Modif. avance\n  Inspeccionar";
		}else if(estado == 2){
			cout <<"  Dar de baja\n >Modif. avance\n  Inspeccionar";
		}else if(estado == 3){
			cout <<"  Dar de baja\n  Modif. avance\n >Inspeccionar";
		}
        caracter = getch();
        switch (caracter){
            case 72:
                //"Flecha ARRIBA\n"
                estado--;
                if(estado == 0){
                	estado = 3;
				}
                break;
            case 80:
                //"Flecha ABAJO\n"
                estado++;
                if(estado == 4){
                	estado = 1;
				}
                break;
            case 13:
            	if(estado == 1){
            		//dar de baja
            		c.op_avance(cur, al, 1);
				}else if(estado == 2){
					//modificar avance
					c.op_avance(cur, al, 2);
				}else if(estado == 3){
					//inspeccionar
					codigo = c.op_avance(cur, al, 3);
					cout << codigo << "\n";
					a.consulta(codigo.c_str());
					getch();
				}
                break;
        }
    }while(caracter != 27 && caracter != 8);
}

void dar_baja(){
	cout <<"\nAqui se da de baja el alumno seleccionado\n";
	getch();
}

void modif_avance(){
	cout <<"\nAqui se registran trabajos entregados\n";
	getch();
}

void inspeccionar(int c){
	a.loc(c);
	getch();
}
