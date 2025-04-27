
#include <iostream>
#include <string>
const int Tam=50;

class alumno {
private: 
    std::string nombre;
    std::string carrera;
    int aprovadas;
    float promedio;
public:
    alumno() { nombre = " "; carrera = " "; aprovadas = 0; promedio = 0.0; }

    void setNombre(std::string nom) { nombre = nom; }
    void setCarrera(std::string carr) {carrera = carr; }
    void setAprovadas(int apro) { aprovadas = apro; }
    void setpromedio(float prom) { promedio = prom; }

    std::string getNombre() const { return nombre; }
    std::string getCarrera() const { return carrera; }
    int getAprovadas() const { return aprovadas; }
    float getPromedio() const { return promedio; }


    
    friend std::ostream& operator<<(std::ostream& os, const alumno& emp);

    friend std::istream& operator>>(std::istream& is, alumno& emp);



    bool operator==(const alumno& otro) const {
        return promedio == otro.promedio && nombre == otro.nombre && aprovadas == otro.aprovadas && carrera == otro.carrera; 
    }

    bool operator > (const alumno& otro) const {
        return promedio > otro.promedio;
    }

    bool operator < (const alumno& otro) const{
        return promedio < otro.promedio;
    }

    bool operator != (const alumno& otro) const{
        return promedio != otro.promedio;
    }

    alumno operator + (const alumno& otro) const {
        alumno temp;
        temp.promedio = this ->promedio + otro.promedio;
        return temp;
    }


};

class ListaEmpleado {
    private:
        alumno datos[Tam];
        int ult;
    public:
    ListaEmpleado() : ult(-1) {}

    bool vacia() const { return ult == -1; }
    bool llena() const { return ult == Tam - 1; }

    void insertar(int pos, const alumno& emp) {
        if (llena()) {
            std::cout << "\nError: La lista esta llena." << std::endl;
        } else if (pos < 0 || pos > ult + 1) {
            std::cout << "\nError: Posicion invalida." << std::endl;
        } else {
            for (int i = ult; i >= pos; --i) {
                datos[i + 1] = datos[i];
            }
            datos[pos] = emp;
            ++ult;
        }
    }

    void ordenarPorPromedio() {
        for (int i = 1; i <= ult; i++) {
            alumno temp = datos[i];
            int j = i - 1;
            
            while (j >= 0 && datos[j].getPromedio() < temp.getPromedio()) {
                datos[j + 1] = datos[j];
                j--;
            }
            datos[j + 1] = temp;
        }
    }

    void eliminar(int pos) {
        if (vacia()) {
            std::cout << "\nError: La lista esta vacia." << std::endl;
        } else if (pos < 0 || pos > ult) {
            std::cout << "\nError: Posicion invalida." << std::endl;
        } else {
            for (int i = pos; i < ult; ++i) {
                datos[i] = datos[i + 1];
            }
            --ult;
        }
    }

    alumno recuperar(int pos) const {
        if (vacia() || pos < 0 || pos > ult) {
            std::cout << "\nError: Posicion invalida o lista vacia." << std::endl;
            return alumno();
        } else {
            return datos[pos];
        }
    }

    int ultimo() const { return ult; }

    int buscar(const std::string& emp) const {
        for (int i = 0; i <= ult; i++){
            if (datos[i].getNombre() == emp || datos[i].getCarrera() == emp){
                return i;
            }
        }
        return -1;
    }

    };
    

    std::ostream& operator<<(std::ostream& os, const alumno& emp){
        os << "\nNombre del alumno: " << emp.nombre << std::endl;
        os << "Nombre de la materia: " << emp.carrera << std::endl;
        os << "Materias aprovadas: " << emp.aprovadas << std::endl;
        os << "Promedio: " << emp.promedio << std::endl;
        return os;
    }

    std::istream& operator>>(std::istream& is, alumno& emp) {
        std::cout << "Introduce el nombre del alumno: ";
        is >> emp.nombre;
    
        std::cout << "Introduce el nombre de la materia: ";
        is >> emp.carrera;
    
        std::cout << "Introduce las materias aprovadas: ";
        is >> emp.aprovadas;
    
        std::cout << "Introduce el promedio: ";
        is >> emp.promedio;
    
        return is;
    }

int main()
{
    ListaEmpleado Milista;
    alumno emp;
    int op = 0, num, pos;
    while (op != 9) {
        std::cout << "\n Bienvenido \n elige una opcion: \n 1: Registrar alumnos. \n 2: Mostrar todos los alumnos. \n 3: Eliminar un alumno. \n 4: Mostrar un alumno. \n 5: Buscar alumno. \n 6: Verificar si la lista esta vacia. \n 7: Verificar si la lista esta llena. \n 8: Ordenar los alumnos (Promedio). \n Presiona 9 para salir. \n \n";
        std::cin >> op;
        switch (op){
            case 1:
            std::cout << "Cuantos alumnos quieres registrar? ";
            std::cin >> num;
            for (int i = 0; i < num; i++) {
                std::cout << "\nIntroduce los datos del alumno " << i + 1 << ":\n";
                std::cin >> emp;
                std::cout << "En que posicion deseas insertar? (0-" << Milista.ultimo() + 1 << "): ";
                std::cin >> pos;
                Milista.insertar(pos, emp);
                }
                break;
            case 2:
            std::cout << "\nAlumnos registrados:\n";
            for (int i = 0; i <= Milista.ultimo(); i++) {
                std::cout << Milista.recuperar(i) << std::endl;
            }
                break;
            case 3:
            std::cout << "Que posicion deseas eliminar? (0-" << Milista.ultimo() << "): ";
            std::cin >> pos;
            Milista.eliminar(pos);
            std::cout << "\nEmpleado eliminado.\n";
                break;
            case 4:
            std::cout << "Que posicion deseas recuperar? (0-" << Milista.ultimo() << "): ";
            std::cin >> pos;
            std::cout << "\nAlumno en la posicion " << pos << ":\n";
            std::cout << Milista.recuperar(pos) << std::endl;
                break;

            case 5:{
                std::string empBuscar;
                if (Milista.vacia()) {
                    std::cout << "\nError: La lista esta vacia." << std::endl;
                    break;
                }
                std::cout << "Introduce los datos del alumno a buscar:\n";
                std::cin >> empBuscar;
                pos = Milista.buscar(empBuscar);
                if (pos != -1) {
                    std::cout << "\nAlumno encontrado en la posicion " << pos << ":\n";
                    std::cout << Milista.recuperar(pos) << std::endl;
                } else {
                    std::cout << "\nAlumno no encontrado.\n";
                }
                break;
            }
            case 6:{
                if (Milista.vacia()){
                    std::cout << "La lista esta vacia" << std::endl;
                }
                else{
                    std::cout << "La no lista esta vacia" << std::endl;
                }

                    break;
            }

            case 7:{
                if (Milista.llena()){
                    std::cout << "La lista esta llena" << std::endl;
                }
                else{
                    std::cout << "La lista no esta llena" << std::endl;
                }

                    break;
            }
            case 8:
                Milista.ordenarPorPromedio();
                std::cout << "\nLista ordenada por promedio (de mayor a menor).\n";

                for (int i = 0; i <= Milista.ultimo(); i++) {
                    std::cout << Milista.recuperar(i) << std::endl;
                }
                break;
            case 9:
                std::cout <<"Gracias." << std::endl;
                break;
            default:
                std::cout << "\nIntroduce una opcion correcta. \n";
            break;         
        }
    }
}
