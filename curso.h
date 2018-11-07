using namespace std;

//REFERENTE A CURSOS Y CRITERIOS DE EVALUACION
class campo{
	public:
		string nombre;
		int valor;
		int cantidad;
		
		campo *siguiente;
		
		campo();
};

class curso{
	public:
		string titulo;
		string nrc;
		int active;
		int hrs_pw;
		int cupo_dis;
		int cupo;
		int tipo;
		int days;
		int hrs_ini;
		int hrs_fin;
		
		campo *inicio;
		curso *sig;
		
		curso();
		BOOL dir_exist(const char*);
		bool vacia();
		int load();
		void insertar_pila(campo *);
		void insertar_cola(campo *);
		void nuevocurso(curso *);
		void week(curso *);
		void display_week(int, int);
		void hours(curso *, int);
		void detalles(curso *);
		void write_files(curso *);
		void set_file(curso *, const char*);
		void write_reg(curso *, const char *);
		int  see_reg(curso *);
};

class cursos{
	private:
		curso *ini;
	public:
		//
		cursos();
		bool exist();
		void agregar();
		void agregar_p(curso *);
		void agregar_c(curso *);
		void listado();
		int  cantidad();
		void localizar(int);
		int  read_files();
		void inscribir(int , const char *);
		int avance(int);
};

//REFERENTE A ALUMNOS

class alumno{
	public:
		string codigo;
		string nombre;
		string apellido;
		string carrera;
		int calendario;
		int situacion;
		
		alumno *siguiente;
		
		alumno();
};

class alumnos{
	private:
		alumno *nicio;
	public:
		alumnos();
		BOOL dir_exist(const char*);
		bool empty();
		void nuevoalumno();
		void ins_alumnoP(alumno *);
		void ins_alumnoC(alumno *);
		int  lista_alumnos();
		void loc(int);
		void inspec(alumno *);
		int  read_files();//busca archivos de alumnos
		void set_f(alumno * , const char*);//lee archivos y los convierte en alumnos
		void write_f(alumno *);//escribe un archivo
		string  returncode(int);
		void consulta(const char*);
};
