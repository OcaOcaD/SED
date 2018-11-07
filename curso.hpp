#include "curso.h"

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

campo::campo(){
	nombre = "";
	valor = 0;
	cantidad = 0;
	
	siguiente = NULL;
}

curso::curso(){
	nrc = "";
	titulo = "";
	sig = NULL;
	inicio = NULL;
}

cursos::cursos(){
	ini = NULL;
}

alumno::alumno(){
	codigo = "";
	nombre = "";
	apellido = "";
	carrera = "";
	calendario = 4037;
	situacion = 0;
	
	siguiente = NULL;
}

alumnos::alumnos(){
	nicio = NULL;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

BOOL curso::dir_exist(const char* dirName){
	DWORD attribs = GetFileAttributesA(dirName);
  	if (attribs == INVALID_FILE_ATTRIBUTES){
    	return 0;
  	}
  	return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}

bool curso::vacia(){
	if(inicio == NULL){
		return true;
	}else{
		return false;
	}
}

void curso::nuevocurso(curso *cur){
	string carpeta;
	string curso_nrc;
	string curso_titulo;
	string campo_nombre;
	int horas;
	int cupo_max;
	int type;
	int valor;
	int cantidad;
	short contador;
	short comprobacion;
	short pregunta;
	
	campo *criterio;
	campo *aux;
	
	//VERIFICANDO QUE NO EXISTA UN NRC IGUAL
	do{
		carpeta = "cursos\\";
		cout << "Ingrese el NRC del nuevo curso: ";
		fflush(stdin);
		getline(cin, curso_nrc);
		carpeta.append(curso_nrc);
		if(dir_exist(carpeta.c_str()) != 0){
			cout << "Ya existe un curso con dicho NRC (" << carpeta << ')' << endl;
		}
	}while(curso_nrc.length() < 4 || curso_nrc.length() > 6 || dir_exist(carpeta.c_str()) != 0);
	//SI NO SE REPITE CREAMOS LA CARPETA
	if (CreateDirectory(carpeta.c_str(), NULL)){
		//El directorio fue creado exitosamente
	}else if (ERROR_ALREADY_EXISTS == GetLastError()){
		cout << "ERROR:El NRC se repite" << endl;
	}else{
		cout << "ERROR: null" << endl;
	}
		
	cout << "Ingrese titulo del curso: ";
	fflush(stdin);
	getline(cin, curso_titulo);
	
	cout << "0. Seminario\n1.Catedra" << endl;
	do{
		cout << "Eleccion ";
		cin >> type;
	}while(type < 0 || type > 1);
	
	do{
		cout << "Cantidad de horas por semana: " << endl;
		cin >> horas;
	}while(horas != 2 && horas != 4);
	
	do{
		cout << "Ingrese los cupos: ";
		cin >> cupo_max;
	}while(cupo_max < 0 || cupo_max > 255);
	
	//
	cur->active = 1;
	cur->titulo = curso_titulo;
	cur->nrc = curso_nrc;
	cur->tipo = type;
	cur->hrs_pw = horas;
	cur->cupo = cupo_max;
	cur->cupo_dis = cupo_max;
	
	pregunta = 1;
	contador = 0;
	comprobacion = 0;
	
	//AGREGANDO ASISTENCIA COMO CRITERIO POR DEFECTO
	criterio = new campo;
	criterio->nombre = "ASISTENCIA";
	criterio->cantidad = 34;
	criterio->valor = 0;
	
	if(vacia()){
		insertar_pila(criterio);
	}else{
		insertar_cola(criterio);
	}
	
	do{
		criterio = new campo;
		
		system("cls");
		cout << "Criterios de evaluacion    Suma de puntos: " << contador << "/100" << endl;
		cout << "Nombre del campo de evaluacion: ";
		fflush(stdin);
		getline(cin, campo_nombre);
		
		//............................
		criterio->nombre = campo_nombre;
				
		do{
			cout << "Ponderacion (puntos): ";
			cin >> valor;
			valor = abs(valor);
			if((contador + valor) > 100){
				cout << "ERROR: suma incorrecta...\n";
				getch();
				comprobacion = 1;
			}else{
				comprobacion = 0;
			}
		}while(comprobacion != 0);
		
		//............................
		criterio->valor = valor;
		
		contador += valor;
		do{
			cout << "Cantidad de " <<  campo_nombre << ": ";
			cin >>cantidad;
			cantidad = abs(cantidad);
		}while(cantidad == 0);
		
		//............................
		criterio->cantidad = cantidad;
		
		if(vacia()){
			insertar_pila(criterio);
		}else{
			insertar_cola(criterio);
		}
		
		if(contador < 100){
			cout << "Desea agregar otro campo?\nSI = 1\nNO = 0\nOpcion: ";
			cin >> pregunta;
		}else{
			pregunta = 0;
		}
	}while(pregunta != 0);
	if(contador < 100){
		aux = inicio;
		aux->valor = 100 - contador;
	}
	week(cur);
	write_files(cur);
}

void curso::display_week(int cursor1, int cursor2){
	cout <<"CONFIG. DIAS DE CLASE\n";
	cout <<"|";
	if(cursor1 == 6 && cursor2 == 6){
		Terminal_Color(224);
		cout <<"   LUNES   ";
		Terminal_Restore();
	}else if(cursor1 == 6 || cursor2 == 6){
		Terminal_Color(14);
		cout <<"   LUNES   ";
		Terminal_Restore();
	}else{
		cout <<"   LUNES   ";
	}
	cout <<"|";
	if(cursor1 == 5 && cursor2 == 5){
		Terminal_Color(224);
		cout <<"  MARTES   ";
		Terminal_Restore();
	}else if(cursor1 == 5 || cursor2 == 5){
		Terminal_Color(14);
		cout <<"  MARTES   ";
		Terminal_Restore();
	}else{
		cout <<"  MARTES   ";
	}
	cout <<"|";
	if(cursor1 == 4 && cursor2 == 4){
		Terminal_Color(224);
		cout <<" MIERCOLES ";
		Terminal_Restore();
	}else if(cursor1 == 4 || cursor2 == 4){
		Terminal_Color(14);
		cout <<" MIERCOLES ";
		Terminal_Restore();
	}else{
		cout <<" MIERCOLES ";
	}
	cout <<"|";
	if(cursor1 == 3 && cursor2 == 3){
		Terminal_Color(224);
		cout <<"  JUEVES   ";
		Terminal_Restore();
	}else if(cursor1 == 3 || cursor2 == 3){
		Terminal_Color(14);
		cout <<"  JUEVES   ";
		Terminal_Restore();
	}else{
		cout <<"  JUEVES   ";
	}
	cout <<"|";
	if(cursor1 == 2 && cursor2 == 2){
		Terminal_Color(224);
		cout <<"  VIERNES  ";
		Terminal_Restore();
	}else if(cursor1 == 2 || cursor2 == 2){
		Terminal_Color(14);
		cout <<"  VIERNES  ";
		Terminal_Restore();
	}else{
		cout <<"  VIERNES  ";
	}
	cout <<"|";
	if(cursor1 == 1 && cursor2 == 1){
		Terminal_Color(224);
		cout <<"  SABADO   ";
		Terminal_Restore();
	}else if(cursor1 == 1 || cursor2 == 1){
		Terminal_Color(14);
		cout <<"  SABADO   ";
		Terminal_Restore();
	}else{
		cout <<"  SABADO   ";
	}
	cout <<"|";
}

void curso::hours(curso *cur, int hrs){
	short estado;
	short caracter;
	short lim;
	short pos, i;
	short hora_i, hora_f;
	
	if(cur->days != 1 && cur->days != 2 && cur->days != 4 && cur->days != 8 && cur->days != 16 && cur->days != 32){
		hrs = hrs/2;
	}
	
	cout <<"\nCONFIG. HORAS DE CLASE\n";
	cout <<"   |07 08 09 10 11 12 13 14 15 16 17 18 19 20 21|\n";
	cout <<"   '  '  '  '  '  '  '  '  '  '  '  '  '  '  '  '";
	estado = 1;
	lim = 45 - (hrs*3);
	pos = 0;
	hora_i = 7;
	hora_f = 7;
	do{
		gotoxy(pos, 8);
		if(pos == 0){
			cout <<"   ";
		}else{
			cout <<"'  ";
		}
		for(i = 0; i < hrs; ++i){
			//cout <<"%c%c%c", '\xFE', '\xFE', '\xFE');
			Terminal_Color(224);
			cout <<"'  ";
		}
		Terminal_Restore();
		cout <<"'  ";
    	if(estado >= 1){
    		gotoxy(0,10);
    		//cout <<"limite %.2d\npos %.2d\n%.2d:00 - %.2d:55\n", lim, pos, hora_i, hora_f - 1);
    		cout << setfill('0') << setw(2) << hora_i << ":00 - " << setfill('0') << setw(2) << hora_f - 1 << ":55" << endl;
    		cout <<"ENTER para confirmar";
		}
        caracter = getch();
        switch (caracter){
            case 75:
                //"Flecha IZQUIERDA\n"
                pos-=3;
                if(pos < 0){
                	pos = 0;
				}
                break;
            case 77:
                //"Flecha DERECHA\n"
                if(pos >= lim){
                	//nothing
				}else{
					pos+=3;
				}
                break;
            case 13:
            	estado++;
                //ENTER
                break;
            case 8:
            	estado--;
            	if(estado == 0){
            		estado = 1;
				}
                //BACKSPACE
                break;
        }
        hora_i = 7 + (pos/3);
        hora_f = hora_i + hrs;
    }while(caracter != 27 && estado != 2);
    cur->hrs_ini = hora_i;
    cur->hrs_fin = hora_f;
}

void curso::week(curso *cur){
	short estado;
	short caracter;
	short cursor1;
	short cursor2;
	short i, ac1,ac2;
	short byte;
	
	//estado == 1 mueve el priemr cursor
	//estado == 2 mueve el segundo cursor
	//estado == 3 confirma y sale
	cursor1 = 1;
	cursor2 = 2;
	estado = 1;
	
    do{
    	system("cls");
    	display_week(cursor1, cursor2);
    	if(estado == 3){
    		gotoxy(0,3);
    		cout <<"ENTER para confirmar";
		}
        caracter = getch();
        switch (caracter){
            case 75:
                //"Flecha IZQUIERDA\n"
                if(estado == 1){
                	cursor1++;
                	if(cursor1 == 7){
                		cursor1 = 1;
					}
				}else if(estado == 2){
					cursor2++;
                	if(cursor2 == 7){
                		cursor2 = 1;
					}
				}
                break;
            case 77:
                //"Flecha DERECHA\n"
                //"Flecha IZQUIERDA\n"
                if(estado == 1){
                	cursor1--;
                	if(cursor1 == 0){
                		cursor1 = 6;
					}
				}else if(estado == 2){
					cursor2--;
                	if(cursor2 == 0){
                		cursor2 = 6;
					}
				}
                break;
            case 13:
            	estado++;
                //ENTER
                break;
            case 8:
            	estado--;
            	if(estado == 0){
            		estado = 1;
				}
                //BACKSPACE
                break;
        }
    }while(caracter != 27 && estado != 4);
    
    ac1 = 1;
    for(i = 1; i < cursor1; i++){
    	ac1 = ac1*2;
	}
	ac2 = 1;
    for(i = 1; i < cursor2; i++){
    	ac2 = ac2*2;
	}
	if(ac1 == ac2){
		byte = ac1;
	}else{
		byte = ac1 +ac2;
	}
	cur->days = byte;
	cout <<"\nRegistrado: ";
	switch(byte){
		case 1: cout <<"SABADO"; break;
		case 2: cout <<"VIERNES"; break;
		case 3: cout <<"VIERNES - SABADO"; break;
		case 4: cout <<"JUEVES"; break;
		case 5: cout <<"JUEVES - SABADO"; break;
		case 6: cout <<"JUEVES - VIERNES"; break;
		case 8: cout <<"MIERCOLES"; break;
		case 9: cout <<"MIERCOLES - SABADO"; break;
		case 10: cout <<"MIERCOLES - VIERNES"; break;
		case 12: cout <<"MIERCOLES - JUEVES"; break;
		case 16: cout <<"MARTES"; break;
		case 17: cout <<"MARTES - SABADO"; break;
		case 18: cout <<"MARTES - VIERNES"; break;
		case 20: cout <<"MARTES - JUEVES"; break;
		case 24: cout <<"MARTES - MIERCOLES"; break;
		case 32: cout <<"LUNES"; break;
		case 33: cout <<"LUNES - SABADO"; break;
		case 34: cout <<"LUNES - VIERNES"; break;
		case 36: cout <<"LUNES - JUEVES"; break;
		case 40: cout <<"LUNES - MIERCOLES"; break;
		case 48: cout <<"LUNES - MARTES"; break;
	}
	cout <<"\n";
	hours(cur, cur->hrs_pw);
}

void curso::write_files(curso *cur){
	int byte = 0;
	campo *nodo = inicio;
	string carpeta = "cursos\\";
	string criterios;
	string registro;
	string null_code = "AAAAAAAAA";
	
	system("cls");
	carpeta.append(cur->nrc);
	
	//VERIFICAR DE NUEVO QUE EL DIRECTORIO EXISTE
	if(dir_exist(carpeta.c_str()) != 0){
		/*fread no se detiene cuando lee caracter nulo
		  fwrite no escribe el caracter nulo string*/
		//si existe escribir los datos en un .bin
		FILE *archivo;
		criterios.append(carpeta);
		criterios.append("\\criterios.bin");
		registro.append(carpeta);
		registro.append("\\registro.bin");
		
		//INICIA ESCRITURA SOBRE CRITERIOS.BIN
	    archivo = fopen(criterios.c_str(), "wb");
	    if (archivo == NULL){ 
	        printf("Unable to create file"); 
	        return;
	    }
	    //escribiendo el titulo del curso y char nulo
	    fwrite(cur->nrc.c_str(), sizeof(char), cur->nrc.length(), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    //escribiendo el titulo del curso y char nulo
	    fwrite(cur->titulo.c_str(), sizeof(char), cur->titulo.length(), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    //escribiendo datos
	    fwrite(&cur->active, sizeof(char), sizeof(char), archivo);
	    fwrite(&cur->hrs_pw, sizeof(char), sizeof(char), archivo);
	    fwrite(&cur->cupo_dis, sizeof(char), sizeof(char), archivo);
	    fwrite(&cur->cupo, sizeof(char), sizeof(char), archivo);
	    fwrite(&cur->tipo, sizeof(char), sizeof(char), archivo);
	    fwrite(&cur->days, sizeof(char), sizeof(char), archivo);
	    fwrite(&cur->hrs_ini, sizeof(char), sizeof(char), archivo);
	    fwrite(&cur->hrs_fin, sizeof(char), sizeof(char), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    //aqui empiezan los criterios de evaluacion
	    while(nodo->siguiente != NULL){
			//se escribe nombre y caracter nulo
			fwrite(nodo->nombre.c_str(), sizeof(char), nodo->nombre.length(), archivo);
			fwrite(&byte, sizeof(char), sizeof(char), archivo);
			//se escriben argumentos aqui y caracter nulo
			fwrite(&nodo->valor, sizeof(char), sizeof(char), archivo);
			fwrite(&nodo->cantidad, sizeof(char), sizeof(char), archivo);
			fwrite(&byte, sizeof(char), sizeof(char), archivo);
			nodo = nodo->siguiente;
		}
		//se escribe nombre y caracter nulo
		fwrite(nodo->nombre.c_str(), sizeof(char), nodo->nombre.length(), archivo);
		fwrite(&byte, sizeof(char), sizeof(char), archivo);
		//se escriben argumentos aqui y caracter nulo
		fwrite(&nodo->valor, sizeof(char), sizeof(char), archivo);
		fwrite(&nodo->cantidad, sizeof(char), sizeof(char), archivo);
		fwrite(&byte, sizeof(char), sizeof(char), archivo);
		fclose(archivo);
		
		//INICIA ESCRITURA SOBRE REGISTRO.BIN
	    archivo = fopen(registro.c_str(), "wb");
	    if (archivo == NULL){ 
	        printf("Unable to create file"); 
	        return;
	    }
	    //aqui empiezan los criterios de evaluacion
	    nodo = inicio;
	    fwrite(null_code.c_str(), sizeof(char), null_code.length(), archivo);
	    while(nodo->siguiente != NULL){
			//se escriben argumentos aqui y caracter nulo
			fwrite(&nodo->cantidad, sizeof(char), sizeof(char), archivo);
			nodo = nodo->siguiente;
		}
		fwrite(&nodo->cantidad, sizeof(char), sizeof(char), archivo);
		fwrite(&byte, sizeof(char), sizeof(char), archivo); // salto de linea
		fclose(archivo);
	}else{
		cout << "El directorio (" << carpeta << ')' << "\nNo pudo ser localizado" << endl;;
	}
}

void curso::set_file(curso *cur, const char* direccion){
	char caracter[2] = {65, 0};
	int byte;
	int flag;
	int crit;
	int cn;
	FILE *archivo;
	campo *criterio;
	
	archivo = fopen(direccion, "rb");
	if (archivo == NULL){ 
	    printf("Unable to read file"); 
	    return;
	}
	
	flag = 1;
	crit = 1;
	cn = 0;
	while (fread(&byte, sizeof(char), sizeof(char), archivo)){
		if(flag == 1){//nrc
			if(byte == 0){
				flag++;
			}else{
				caracter[0] = byte;
				cur->nrc.append(caracter);
			}
		}else if(flag == 2){
			if(byte == 0){
				flag++;
			}else{
				caracter[0] = byte;
				cur->titulo.append(caracter);
			}
		}else if(flag == 3){
			cur->active = byte;
			flag++;
		}else if(flag == 4){
			cur->hrs_pw = byte;
			flag++;
		}else if(flag == 5){
			cur->cupo_dis = byte;
			flag++;
		}else if(flag == 6){
			cur->cupo = byte;
			flag++;
		}else if(flag == 7){
			cur->tipo = byte;
			flag++;
		}else if(flag == 8){
			cur->days = byte;
			flag++;
		}else if(flag == 9){
			cur->hrs_ini = byte;
			flag++;
		}else if(flag == 10){
			cur->hrs_fin = byte;
			flag++;
		}else if(flag == 11){
			//el caracter nulo
			flag++;
		}else if(flag > 11){
			if(crit == 1){
				if(cn == 0){
					criterio = new campo;
					cn = 1;
				}
				if(byte == 0){
					crit++;
				}else{
					caracter[0] = byte;
					criterio->nombre.append(caracter);
				}
			}else if(crit == 2){
				criterio->valor = byte;
				crit++;
			}else if(crit == 3){
				criterio->cantidad = byte;
				crit++;
			}else if(crit == 4){
				if(vacia()){
					insertar_pila(criterio);
				}else{
					insertar_cola(criterio);
				}
				crit = 1;
				cn = 0;
			}
		}
	}//end while
}//end function

void curso::insertar_pila(campo *criterio){
	criterio->siguiente = inicio; //el nuevo nodo apunta al inicio
	inicio = criterio;//el inicio apunta a nuevo nodo
}

void curso::insertar_cola(campo *criterio){
	campo *aux = inicio;//puntero tipo nodo apunta al inicio
	while(aux->siguiente != NULL){//recorrer hasta el final
		aux = aux->siguiente;//aux ahora apunta al nuevo nodo
	}//end while
	aux->siguiente = criterio;//ahora el nuevo nodo se agrego(final)
}

void curso::detalles(curso *u){
	campo *nodo = inicio;
	if(vacia()){
		//nada
	}else{
		cout << "NRC    : " << u->nrc << endl;
		cout << "Curso  : " << u->titulo << endl;
		cout << "cupos  : " << u->cupo << endl;
		cout << "Disp.  : " << u->cupo_dis << endl;
		if(u->active == 1){
			cout << "Estado : ACTIVO" << endl;
		}else if(u->active == 0){
			cout << "Estado : INACTIVO" << endl;
		}else{
			cout << "Estado : EN REVISION" << endl;
		}
		cout << "Horario: ";
		switch(u->days){
			case 1: cout <<"SABADO"; break;
			case 2: cout <<"VIERNES"; break;
			case 3: cout <<"VIERNES - SABADO"; break;
			case 4: cout <<"JUEVES"; break;
			case 5: cout <<"JUEVES - SABADO"; break;
			case 6: cout <<"JUEVES - VIERNES"; break;
			case 8: cout <<"MIERCOLES"; break;
			case 9: cout <<"MIERCOLES - SABADO"; break;
			case 10: cout <<"MIERCOLES - VIERNES"; break;
			case 12: cout <<"MIERCOLES - JUEVES"; break;
			case 16: cout <<"MARTES"; break;
			case 17: cout <<"MARTES - SABADO"; break;
			case 18: cout <<"MARTES - VIERNES"; break;
			case 20: cout <<"MARTES - JUEVES"; break;
			case 24: cout <<"MARTES - MIERCOLES"; break;
			case 32: cout <<"LUNES"; break;
			case 33: cout <<"LUNES - SABADO"; break;
			case 34: cout <<"LUNES - VIERNES"; break;
			case 36: cout <<"LUNES - JUEVES"; break;
			case 40: cout <<"LUNES - MIERCOLES"; break;
			case 48: cout <<"LUNES - MARTES"; break;
		}
		cout << "\nHora   : ";
		cout << setfill('0') << setw(2) << u->hrs_ini << ":00 - " << setfill('0') << setw(2) << u->hrs_fin - 1 << ":55" << endl;
		if(u->tipo == 1){
			cout << "Extraordinario: True" << endl;
		}else{
			cout << "Extraordinario: False" << endl;
		}
		cout << "\nCRITERIOS DE EVALUACION\n" << endl;
		while(nodo->siguiente != NULL){
			cout << setfill(' ') << setw(3) << nodo->cantidad << ' ' << setfill(' ') << setw(16) << nodo->nombre << ": " 
			<< setfill(' ') << setw(4) << nodo->valor << " puntos" << endl;
			nodo = nodo->siguiente;
		}
		cout << setfill(' ') << setw(3) << nodo->cantidad << ' ' << setfill(' ') << setw(16) << nodo->nombre << ": " 
		<< setfill(' ') << setw(4) << nodo->valor << " puntos" << endl;
	}
	cout << endl;
}

void curso::write_reg(curso *cur, const char *codi){
	int y, y2;
	int i, k;
	short caracter, estado;
	campo *nodo = inicio;
	float entregados;
	float promedio;
	FILE *archivo;
	
	string direccion;
	
	system("cls"); y2 = 4;
	cout << "AVANCE DE "<< codi << endl << endl;
	while(nodo->siguiente != NULL){
		y2++;
		cout << setfill(' ') << setw(16) << nodo->nombre << setfill(' ') << setw(4) << nodo->cantidad << " / 0" << endl;
		nodo = nodo->siguiente;
	}
	cout << setfill(' ') << setw(16) << nodo->nombre << setfill(' ') << setw(4) << nodo->cantidad << " / 0" << endl;
	cout << "          _________________\n" << endl;
	
	//preparando la direccion
	direccion = "cursos\\";
	direccion.append(cur->nrc);
	direccion.append("\\registro.bin");
	//termina de preparar direccion
	
	//escribiendo codigo
	archivo = fopen(direccion.c_str(), "ab");
	if (archivo == NULL){ 
	        printf("Unable to create file"); 
	        return;
	    }
	fwrite(codi, sizeof(char), 9, archivo);
	
	y = 1;
	entregados = 0;
	promedio = 0;
	nodo = inicio;
	
	while(nodo->siguiente != NULL){
		y++;
		//
		do{
			gotoxy(23,y);
			caracter = getch();
			switch(caracter){
				case 75:
					entregados--;
					if(entregados < 0){
						entregados = 0;
					}
					break;
				case 77:
					entregados++;
					if(entregados > nodo->cantidad){
						entregados = nodo->cantidad;
					}
					break;
			}
			if((entregados/nodo->cantidad) > 0.8){
				Terminal_Color(10);
			}else if((entregados/nodo->cantidad) >= 0.6){
				Terminal_Color(14);
			}else if((entregados/nodo->cantidad) < 0.6){
				Terminal_Color(12);
			}
			cout << entregados << ' ';
			Terminal_Restore();
		}while(caracter != 13);
		//escribiendo criterio
		k = (int)entregados;
		fwrite(&k, sizeof(char), sizeof(char), archivo);
		promedio += (entregados/nodo->cantidad) * (nodo->valor);
		entregados = 0;
		nodo = nodo->siguiente;
		gotoxy(22, y2);
		if(promedio > 80){
			Terminal_Color(10);
		}else if(promedio >= 60){
			Terminal_Color(14);
		}else if(promedio < 60){
			Terminal_Color(12);
		}
		cout << promedio << '%';
		Terminal_Restore();
	}
	
	y++;
	do{
		gotoxy(23,y);
		caracter = getch();
		switch(caracter){
			case 75:
				entregados--;
				if(entregados < 0){
					entregados = 0;
				}
				break;
			case 77:
				entregados++;
				if(entregados > nodo->cantidad){
					entregados = nodo->cantidad;
				}
				break;
		}
		if((entregados/nodo->cantidad) > 0.8){
			Terminal_Color(10);
		}else if((entregados/nodo->cantidad) >= 0.6){
			Terminal_Color(14);
		}else if((entregados/nodo->cantidad) < 0.6){
			Terminal_Color(12);
		}
		cout << entregados << ' ';
		Terminal_Restore();
	}while(caracter != 13);
	//escribiendo criterio
	k = (int)entregados;
	fwrite(&k, sizeof(char), sizeof(char), archivo);
	promedio += (entregados/nodo->cantidad) * (nodo->valor);
	entregados = 0;
	nodo = nodo->siguiente;
	gotoxy(22, y2);
	if(promedio > 80){
		Terminal_Color(10);
	}else if(promedio >= 60){
		Terminal_Color(14);
	}else if(promedio < 60){
		Terminal_Color(12);
	}
	cout << promedio << '%';
	Terminal_Restore();
	//escribiendo salto de linea
	fwrite(&entregados, sizeof(char), sizeof(char), archivo);
	fclose(archivo);
	
}

int curso::see_reg(curso * cur){
	string direccion;
	string codigo;
	campo *nodo = inicio;
	FILE *archivo;
	int num_crit, num_alu, first;
	short byte, bandera_glo, bandera_loc;
	
	first = 1;
	num_crit = 1;
	system("cls");
	cout << "     CODIGO";
	while(nodo->siguiente != NULL){
		cout << setfill(' ') << setw(16) << nodo->nombre;
		nodo = nodo->siguiente;
		num_crit++;
	}
	cout << setfill(' ') << setw(16) << nodo->nombre << endl;
	
	direccion = "cursos\\";
	direccion.append(cur->nrc);
	direccion.append("\\registro.bin");
	
	archivo = fopen(direccion.c_str(), "rb");
	if (archivo == NULL){ 
	    printf("Unable to create file"); 
	    return 0;
	}
	num_alu = 0;
	bandera_glo = 0;
	bandera_loc = 0;
	while (fread(&byte, sizeof(char), sizeof(char), archivo)){
		//codigo
		if(bandera_glo == 0){
			if(bandera_loc < 8){
				bandera_loc++;
				if(first == 1){
					//ignore
				}else{
					cout << (char)byte;
				}
			}else{
				bandera_glo = 1;
				bandera_loc = 0;
				//termina con codigo
				if(first == 1){
					//ignore
				}else{
					cout << (char)byte;
				}
			}
		//empiezan criterios
		}else if(bandera_glo == 1){
			if(bandera_loc < num_crit){
				if(first == 1){
					//ignore
				}else{
					cout << setfill(' ') << setw(16) << byte;
				}
				bandera_loc++;
			}else{
				bandera_glo = 0;
				bandera_loc = 0;
				//terminan criterios
				cout << endl << "  ";
				num_alu++;
				if(first == 1){
					first = 0;
				}
			}
		}
	}
	fclose(archivo);
	return num_alu;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

bool cursos::exist(){
	if(ini != NULL){
		return true;
	}else{
		return false;
	}
}

void cursos::agregar_p(curso *materia){
	curso *aux = ini;//puntero tipo nodo apunta al inicio
	while(aux->sig != NULL){//recorrer hasta el final
		aux = aux->sig;//aux ahora apunta al nuevo nodo
	}//end while
	aux->sig = materia;//ahora el nuevo nodo se agrego(final)
}

void cursos::agregar_c(curso *materia){
	materia->sig = ini;
	ini = materia;//el inicio apunta a nuevo nodo
}

void cursos::agregar(){
	curso *materia;
	materia = new curso;
	materia->nuevocurso(materia);
	if(exist()){
		//some comment
		agregar_p(materia);
	}else{
		agregar_c(materia);
	}
}

void cursos::listado(){
	curso *aux = ini;//puntero tipo nodo apunta al inicio
	
	if(!exist()){
		return;
	}else{
		while(aux->sig != NULL){//recorrer hasta el final
			cout << "  " << setfill(' ') << setw(7) << aux->nrc << "  " << aux->titulo << endl;
			aux = aux->sig;//aux ahora apunta al nuevo nodo
		}//end while
		cout << "  " << setfill(' ') << setw(7) << aux->nrc << "  " << aux->titulo << endl;
	}
}

int cursos::cantidad(){
	int i;
	curso *aux = ini;//puntero tipo nodo apunta al inicio
	if(!exist()){
		return 0;
	}else{
		i = 1;
		while(aux->sig != NULL){//recorrer hasta el final
			aux = aux->sig;//aux ahora apunta al nuevo nodo
			i++;
		}//end while
		return i;
	}
}

void cursos::localizar(int loc){
	curso *aux = ini;//puntero tipo nodo apunta al inicio
	if(!exist()){
		return;
	}else{
		int i = 1;
		while(aux->sig != NULL && i < loc){//recorrer hasta el final
			aux = aux->sig;//aux ahora apunta al nuevo nodo
			i++;
		}//end while
		if(i != loc){
			return;
		}else{
			aux->detalles(aux);
		}
	}
}

int cursos::read_files(){
	string cur_dir;
	short i;
	DIR *dp;
  	struct dirent *ep;
  	curso *materia;
  	
  	dp = opendir ("cursos");
  	i = -1;
  	
  	if (dp != NULL){
    	while (ep = readdir (dp)){
    		if(i < 1){
    			
			}else{
				cur_dir = "";
				cur_dir.append("cursos\\");
				cur_dir.append(ep->d_name);
				cur_dir.append("\\criterios.bin");
				
				//se crea el curso
				materia = new curso;
				materia->set_file(materia, cur_dir.c_str());
				if(exist()){
					//some comment
					agregar_p(materia);
				}else{
					agregar_c(materia);
				}
			}
			i++;
		}
    	(void) closedir (dp);
	}else{
		cout <<"<dir> cursos NO encontrado\n";
	}
	return i;
}

void cursos::inscribir(int cur, const char * codi){
	curso *aux = ini;//puntero tipo nodo apunta al inicio
	if(!exist()){
		return;
	}else{
		int i = 1;
		while(aux->sig != NULL && i < cur){//recorrer hasta el final
			aux = aux->sig;//aux ahora apunta al nuevo nodo
			i++;
		}//end while
		if(i != cur){
			return;
		}else{
			aux->write_reg(aux, codi);
		}
	}
	getch();
}

int cursos::avance(int cur){
	int numero;
	curso *aux = ini;//puntero tipo nodo apunta al inicio
	if(!exist()){
		return 0;
	}else{
		int i = 1;
		while(aux->sig != NULL && i < cur){//recorrer hasta el final
			aux = aux->sig;//aux ahora apunta al nuevo nodo
			i++;
		}//end while
		if(i != cur){
			return 0;
		}else{
			numero = aux->see_reg(aux);
			return numero;
		}
	}
	getch();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

bool alumnos::empty(){
	if(nicio == NULL){
		return true;
	}else{
		return false;
	}
}

BOOL alumnos::dir_exist(const char* dirName){
	DWORD attribs = GetFileAttributesA(dirName);
  	if (attribs == INVALID_FILE_ATTRIBUTES){
    	return 0;
  	}
  	return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}

void alumnos::nuevoalumno(){
	string cod;
	string comp;
	string name;
	string last_name;
	string career;
	int actual[7] = {34,35,36,37,38,39,40};
	int dif, caracter, i;
	int situation;
	int eti = 1;
	FILE *archivo;
	
	alumno *nuevoal;
	
	system("cls");
	cout << "El codigo del alumno debe ser numerico y debe\ntener una longitud de nueve digitos" << endl;
	do{
		cout << "Codigo: "; cin >> cod;
		comp = "alumnos\\";
		comp.append(cod);
		comp.append(".bin");
		
		archivo = fopen(comp.c_str(), "rb");
	    if (archivo != NULL){ 
	        cout <<"Codigo ya registrado\n"; 
		}else{
			eti = 0;
			fclose(archivo);
		}
	}while(cod.length() != 9 || eti == 1);
	
	cout << "Nombre(s) del alumno: ";
	fflush(stdin);
	getline(cin, name);
	
	cout << "Apellido(s) del alumno: ";
	fflush(stdin);
	getline(cin, last_name);
	
	cout << "Carrera: ";
	fflush(stdin);
	getline(cin, career);
	
	system("cls");
	cout << "CALENDARIO INGRESO\n  __________";
	gotoxy(0,11);
	cout << "  __________\nn de semestres: ";
	do{
		gotoxy(0,2);
		for(i = 0; i < 7; ++i){
			if(actual[i] > 37 || actual[i] < 24){
				Terminal_Color(8);
				if(i == 3){
					cout << "  " << '\xDA'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xBF'<< endl;
					if(actual[i] % 2 == 0){
						cout << "  " << '\xB3'<< "20" << actual[i] / 2<< " A" <<'\xB3' << endl;
					}else{
						cout << "  " << '\xB3'<< "20" << actual[i] / 2<< " B" <<'\xB3' << endl;
					}
					cout << "  "  << '\xC0'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xD9'<< endl;
				}else{
					if(actual[i] % 2 == 0){
						cout << "    20" << actual[i] / 2 << " A" << endl;
					}else{
						cout << "    20" << actual[i] / 2 << " B" << endl;
					}
				}
				Terminal_Restore();
			}else{
				if(i == 3){
					cout << "  "  << '\xDA'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xBF'<< endl;
					if(actual[i] % 2 == 0){
						cout << "  " << '\xB3'<< "20" << actual[i] / 2<< " A" <<'\xB3' << endl;
					}else{
						cout << "  " << '\xB3'<< "20" << actual[i] / 2<< " B" <<'\xB3' << endl;
					}
					cout << "  "  << '\xC0'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xC4'<< '\xD9'<< endl;
				}else{
					if(actual[i] % 2 == 0){
						cout << "    20" << actual[i] / 2 << " A" << endl;
					}else{
						cout << "    20" << actual[i] / 2 << " B" << endl;
					}
				}
			}
		}
		dif = (37 - actual[3]) + 1;
		gotoxy(16,12);
		if(dif > 14 || dif < 1){
			Terminal_Color(12);
			cout << dif << ' ';
			Terminal_Restore();
		}else{
			cout << dif << ' ';
		}
		
		caracter = getch();
		
		switch(caracter){
			case 72:
				for(i = 0; i < 7; i++){
					actual[i] = actual[i] - 1;
				}
				break;
			case 80:
				for(i = 0; i < 7; i++){
					actual[i] = actual[i] + 1;
				}
				break;
		}
	}while(caracter != 13 || dif > 14 || dif < 1);
	
	system("cls");
	cout << "0. Egresado\n1. Baja adimistrativa\n2. Activo\n3. Art. 34\n4. Art. 35\n" << endl;
	do{
		cout << "Situacion del alumno: "; cin >> situation;
	}while(situation > 4 || situation < 0);
	
	cout << "Alumno Registrado satisfactoriamente" << endl;
	//se crea el nodo alumno
	nuevoal = new alumno;
	nuevoal->codigo = cod;
	nuevoal->nombre = name;
	nuevoal->apellido = last_name;
	nuevoal->carrera = career;
	nuevoal->calendario = actual[3];
	nuevoal->situacion = situation;
	//se agrega a la lista
	if(empty()){
		ins_alumnoP(nuevoal);
	}else{
		ins_alumnoC(nuevoal);
	}
	//se llama a la funcion que escribe archivos
	write_f(nuevoal);
}

void alumnos::ins_alumnoP(alumno *na){
	na->siguiente = nicio; //el nuevo nodo apunta al inicio
	nicio = na;//el inicio apunta a nuevo nodo
}

void alumnos::ins_alumnoC(alumno *na){
	alumno *aux = nicio;//puntero tipo nodo apunta al inicio
	while(aux->siguiente != NULL){//recorrer hasta el final
		aux = aux->siguiente;//aux ahora apunta al nuevo nodo
	}//end while
	aux->siguiente = na;//ahora el nuevo nodo se agrego(final)
}

int alumnos::lista_alumnos(){
	int i;
	alumno *aux = nicio;//puntero tipo nodo apunta al inicio
	i = 0;
	system("cls");
	cout << "     CODIGO|                CARRERA|    SITUACION|\n";
	if(empty()){
		return i;
	}else{
		while(aux->siguiente != NULL){//recorrer hasta el final
			i++;
			cout << "  " << aux->codigo << setfill(' ') << setw(24) << aux->apellido << "  ";
			if(aux->situacion == 0){
				cout << "    EGRESADO\n";
			}else if(aux->situacion == 1){
				cout << "    INACTIVO\n";
			}else if(aux->situacion == 2){
				cout << "      ACTIVO\n";
			}else if(aux->situacion == 3){
				cout << "     ART. 34\n";
			}else if(aux->situacion == 4){
				cout << "    ART.  35\n";
			}
			aux = aux->siguiente;//aux ahora apunta al nuevo nodo
		}//end while
		i++;
		cout << "  " << aux->codigo << setfill(' ') << setw(24) << aux->apellido << "  ";
		if(aux->situacion == 0){
			cout << "    EGRESADO\n";
		}else if(aux->situacion == 1){
			cout << "    INACTIVO\n";
		}else if(aux->situacion == 2){
			cout << "      ACTIVO\n";
		}else if(aux->situacion == 3){
			cout << "      ART. 34\n";
		}else if(aux->situacion == 4){
			cout << "     ART.  35\n";
		}
		return i;
	}
}

void alumnos::loc(int n){
	alumno *aux = nicio;//puntero tipo nodo apunta al inicio
	if(empty()){
		return;
	}else{
		int i = 1;
		while(aux->siguiente != NULL && i < n){//recorrer hasta el final
			aux = aux->siguiente;//aux ahora apunta al nuevo nodo
			i++;
		}//end while
		if(i != n){
			cout << "Error 404, system not found" << endl;
		}else{
			inspec(aux);
		}
	}
}

void alumnos::inspec(alumno *alu){
	system("cls");
	cout << "Codigo    : " << alu->codigo << endl;
	cout << "Aombres   : " << alu->nombre << endl;
	cout << "Apellidos : " << alu->apellido << endl;
	cout << "Carrera   : " << alu->carrera << endl;
	if(((37 - alu->calendario) + 1) % 2 == 0){
		cout << "Calendario: 20" << alu->calendario/2 << " A" << endl;
	}else{
		cout << "Calendario: 20" << alu->calendario/2 << " B" << endl;
	}
	cout << "Semestre  : " << (37 - alu->calendario) + 1 << endl;
	cout << "Situacion : ";
	if(alu->situacion == 0){
		cout << "EGRESADO\n";
	}else if(alu->situacion == 1){
		cout << "INACTIVO\n";
	}else if(alu->situacion == 2){
		cout << "ACTIVO\n";
	}else if(alu->situacion == 3){
		cout << "ART. 34\n";
	}else if(alu->situacion == 4){
		cout << "ART.  35\n";
	}
	
}

int alumnos::read_files(){
	string dir;
	short i;
	DIR *dp;
  	struct dirent *ep;
  	alumno *na;
  	
  	dp = opendir ("alumnos");
  	i = -1;
  	
  	if (dp != NULL){
    	while (ep = readdir (dp)){
    		if(i < 1){
    			
			}else{
				dir = "";
				dir.append("alumnos\\");
				dir.append(ep->d_name);
				
				//se crea el curso
				na = new alumno;
				set_f(na, dir.c_str());
				if(empty()){
					//some comment
					ins_alumnoP(na);
				}else{
					ins_alumnoC(na);
				}
			}
			i++;
		}
    	(void) closedir (dp);
	}else{
		cout <<"<dir> cursos NO encontrado\n";
	}
	return i;
}

void alumnos::set_f(alumno *na , const char *direccion){
	int byte;
	int flag, binflag;
	char caracter[2] = {65,0};
	FILE *archivo;
	
	archivo = fopen(direccion, "rb");
	if (archivo == NULL){ 
	    printf("Unable to read file"); 
	    return;
	}
	flag = 1;
	binflag = 1;
	while (fread(&byte, sizeof(char), sizeof(char), archivo)){
		if(flag == 1){
			if(byte == 0){
				flag++;
			}else{
				caracter[0] = byte;
				na->codigo.append(caracter);
			}
		}else if(flag == 2){
			if(byte == 0){
				flag++;
			}else{
				caracter[0] = byte;
				na->nombre.append(caracter);
			}
		}else if(flag == 3){
			if(byte == 0){
				flag++;
			}else{
				caracter[0] = byte;
				na->apellido.append(caracter);
			}
		}else if(flag == 4){
			if(byte == 0){
				flag++;
			}else{
				caracter[0] = byte;
				na->carrera.append(caracter);
			}
		}else if(flag == 5){
			if(byte == 0){
				flag++;
			}else{
				na->calendario = byte;
			}
		}else if(flag == 6 || flag == 7){
			if(byte == 0){
				flag++;
			}else{
				na->situacion = byte;
			}
		}
	}
}

void alumnos::write_f(alumno *na){
	string carpeta = "alumnos";
	string file_name = "";
	int byte = 0;
	FILE *archivo;
	
	//VERIFICAR DE NUEVO QUE EL DIRECTORIO EXISTE
	if(dir_exist(carpeta.c_str()) != 0){
		file_name.append(carpeta);
		file_name.append("\\");
		file_name.append(na->codigo);
		file_name.append(".bin");
		
		//INICIA ESCRITURA SOBRE CRITERIOS.BIN
	    archivo = fopen(file_name.c_str(), "wb");
	    if (archivo == NULL){ 
	        printf("Unable to create file"); 
	        return;
	    }
	    //escribiendo codigo y \0
	    fwrite(na->codigo.c_str(), sizeof(char), na->codigo.length(), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    //escribiendo nombres y \0
	    fwrite(na->nombre.c_str(), sizeof(char), na->nombre.length(), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    //escribiendo apellido y \0
	    fwrite(na->apellido.c_str(), sizeof(char), na->apellido.length(), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    //escribiendo carrera y \0
	    fwrite(na->carrera.c_str(), sizeof(char), na->carrera.length(), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    //escribiendo calendario y \0
	    fwrite(&na->calendario, sizeof(char), sizeof(char), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    //escribiendo situacion y \0
	    fwrite(&na->situacion, sizeof(char), sizeof(char), archivo);
	    fwrite(&byte, sizeof(char), sizeof(char), archivo);
	    
	    fclose(archivo);
	}else{
		cout << "El directorio (" << carpeta << ')' << "\nNo pudo ser localizado" << endl;;
	}
}

string alumnos::returncode(int n){
	alumno *aux = nicio;//puntero tipo nodo apunta al inicio
	if(empty()){
		return "empty";
	}else{
		int i = 1;
		while(aux->siguiente != NULL && i < n){//recorrer hasta el final
			aux = aux->siguiente;//aux ahora apunta al nuevo nodo
			i++;
		}//end while
		if(i != n){
			return "null";
		}else{
			return aux->codigo;
		}
	}
}

void alumnos::consulta(const char* codig){
	alumno *aux = nicio;
	if(empty()){
		return;
	}else{
		int i = 1;
		while(aux->siguiente != NULL && strcmp(aux->codigo.c_str(), codig) != 0){//recorrer hasta el final
			aux = aux->siguiente;//aux ahora apunta al nuevo nodo
			i++;
		}//end while
		if(strcmp(aux->codigo.c_str(), codig) != 0){
			return;
		}else{
			inspec(aux);
		}
	}
}
