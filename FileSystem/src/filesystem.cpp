#include <filesystem.h>

class FS {
  private:
    int size; 
    char *unidad;
    //string *directory ;  datos según la organización elegida
    //si un archivo tiene permiso 733   rwxrwxrwx 111011011
    //755   111101101
    int *fat ;
    string activeFolder ;
    string usuario ;

  public: 
    FS(int size) {
      this->size= size ;
      unidad = new char [size];   
      srand(time(NULL));
    }

  bool verificarPermisos(string file) {

  }

  int solicitarEspacio() {
    //recorrer hasta encontrar un bloque
    //return resultado ;
  }

  //
  int write(char *data, string file, string user){
    //verificar permisos
    //buscar(file)
    //verificar si está abierto
    //save(42+tam(descriptor), data)
  }

  bool execute(string file, string user){
    bool ejecutado = false;
    return ejecutado;
  }
  

  //REQUIERE: carpeta actual
  char* list(){

  }

  bool changeFolder(string folder) {

  }

  bool upFolder() {

  }

  bool create(string file, string user){
    bool result= false ;
    //verificar permisos
    //asignar espacio 
    //guardar descriptor  (nombre, fecha, extension, permisos, carpeta )
    //save(unidad[42],{ file, date, 511, activeFolder}) ;

    return result ;
  }
  
  void read(string file, string user){

  }

  int append(char *data, string file, string user){
    return 0;
  }  
};