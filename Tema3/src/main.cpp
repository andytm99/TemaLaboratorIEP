#include <iostream>
#include <memory>
class Car
{
private:
        std::string brandName;
        std::string modelName;
        std::string color;
        int yearOfFabrication;

public:
     Car()
     :  brandName(),
        modelName(),
        color(),
        yearOfFabrication(0)
        {std::cout<<"Empty Car constructor\n";}

     /*Car(std::string n,std::string m,std::string c, int y)
        {
        brandName  = n;
        modelName  = m;
        color = c;
        yearOfFabrication  = y;

        }*/
        ///constructorul comentat este assignment-based
        ///constructorul de mai jos este facut prin metoda "member initialization list"
        ///a doua varianta este mai eficienta deoarece nu se mai apeleaza default constructor

        Car(std::string n,std::string m,std::string c, int y)
       : brandName(n),
         modelName(m),
         color(c),
         yearOfFabrication(y)
       { }
       Car(const Car &C)
       {
       std::cout<<"Copy-Constructor\n";
       this->brandName=C.brandName;
       this->modelName=C.modelName;
       this->color=C.color;
       this->yearOfFabrication=C.yearOfFabrication;
       }

       Car& operator=(const Car& C)
       {
        std::cout<<"Copy assignment operator\n";
        this->brandName=C.brandName;
        this->modelName=C.modelName;
        this->color=C.color;
        this->yearOfFabrication=C.yearOfFabrication;
        return *this;
       }

        ///punem functii pentru a ne usura munca daca vrem sa modificam o valoare pusa gresit;
        void setBrandName(std::string bn)
        {
            this->brandName=bn;
        }
        std::string getBrandName()
        {
            return this->brandName;
        }

        void setModelName(std::string mn)
        {
            this->modelName=mn;
        }
        std::string getModelName()
        {
            return this->modelName;
        }

        void setColor(std::string col)
        {
            this->color=col;
        }
        std::string getColor()
        {
            return this->color;
        }
        void setYearOfFabrication(int ye)
        {
            this->yearOfFabrication=ye;
        }
        int getYearOfFabrication()
        {
            return this->yearOfFabrication;
        }

        /*Car& TestCar()
        {
            static Car TestC;
            return TestC;
        }*/
        ///sectiunea comentata este o varianta de a renunta la variabilele statice globale ce pot crea probleme la folosirea in alte fisiere sursa
        void printCar()//for printing car's details
        {
            std::cout<<this->brandName<<" "<<this->modelName<<" "<<this->color<<" "<<this->yearOfFabrication<<"\n";
        }
     ~Car()
     {
        std::cout<<"Car is destroyed\n";
     }
};



class Motorcycle
{
    private:
    std::string brandName;
    std::string modelName;
    Motorcycle(const Motorcycle&);//copy constructor pus aici pentru a dezactiva aceasta functionalitate
    Motorcycle& operator=(const Motorcycle&);//copy assignment operator pus aici pentru a dezactiva aceasta functionalitate
    bool isLocked=false;
    public:
    Motorcycle()
    {
        std::cout<<"Empty motorcycle constructor\n";
    }
        Motorcycle(std::string n,std::string m)
        {
        brandName  = n;
        modelName  = m;

        }
    //Motorcycle(const Motorcycle&)=delete;//copy constructor deleted
    void setBrandName(std::string bn)
        {
            this->brandName=bn;
        }
        std::string getBrandName()
        {
            return this->brandName;
        }

        void setModelName(std::string mn)
        {
            this->modelName=mn;
        }
        std::string getModelName()
        {
            return this->modelName;
        }
        void setIsLocked(bool x)
        {
            this->isLocked=x;
        }

        void askMotorcycle()
        {
            if(this->isLocked)
            {
                std::cout<<"\nResursa este blocata.\n";
            }
            else
            {
                std::cout<<"\nResursa nu este blocata.\n";
            }
        }

    ~Motorcycle()
    {
        std::cout<<"Motorcycle is destroyed\n";
    }
};
void lock(Motorcycle &m)
{
    std::cout<<"Locking motorcycle resource!";
    m.setIsLocked(true);
}

void unlock(Motorcycle &m)
{
    std::cout<<"Unlocking the motorcycle resource!";
    m.setIsLocked(false);
}

class LockMotorcycle{
private: Motorcycle &lockPtr;
public:
    LockMotorcycle(Motorcycle &ptr):
    lockPtr(ptr){
        lock(lockPtr);
    }
    ~LockMotorcycle(){
        unlock(lockPtr);
    }
};

void printCars(Car& C)//functie de afisat detalii masini
{
    std::cout<<C.getBrandName()<<" "<<C.getModelName()<<" "<<C.getColor()<<" "<<C.getYearOfFabrication()<<"\n";
}
void printMoto(Motorcycle& M)//functie de afisat detalii motociclete
{
    std::cout<<""<<M.getBrandName()<<" "<<M.getModelName()<<"\n";
}
int main()
{
    //nu putem sa copiem valoarea unui unique pointer in alt unique pointer ci doar sa dam transfer de ownership(move)
    std::cout<<"\n\n-------------Unique Pointer example:-------------\n\n";
    std::unique_ptr<Car> uniqueCar(new Car("Ford","Focus","Albastru",2004));
    uniqueCar->printCar();
    uniqueCar->setColor("Rosu");//observam ca prin move transferam ownership deci uniqueCar2 primeste toate proprietatile ale lui uniqueCar
    std::unique_ptr<Car> uniqueCar2=move (uniqueCar);//nu e copiere ci e transfer de ownership
    uniqueCar2->printCar();
    //uniqueCar->printCar();//segmentation fault

    std::cout<<"\n\n-------------Shared Pointer example:-------------\n\n";
    std::shared_ptr<Car> sharedCar(new Car("Mercedes","Benz","Negru",2020));
    sharedCar->printCar();
    std::cout<<"Pointer count ="<<sharedCar.use_count()<<"\n";
    std::shared_ptr<Car> sharedCar2(sharedCar);
    sharedCar->setColor("Portocaliu");
    sharedCar2->printCar();//observam ca pointeaza spre acelasi obiect deci daca facem o schimbare in sharedCar se vede si in sharedCar2
    std::cout<<"Pointer 2 count ="<<sharedCar2.use_count()<<"\n";
    std::shared_ptr<Car> sharedCar3= move(sharedCar);
    sharedCar3->printCar();
    std::cout<<"Pointer 3 count ="<<sharedCar3.use_count()<<"\n";
    std::cout<<"Pointer count ="<<sharedCar.use_count()<<" => Aici observam ca facand transferul catre sharedCar3, pointerul sharedCar nu mai pointeaza spre obiect.\n";
    std::cout<<"\n\n";


    std::cout<<"\n\n-------------Lock Resource Example:-------------\n\n";
    Motorcycle moto("Suzuki","Hayabusa");
    LockMotorcycle *lockedMotorcycle=new LockMotorcycle(moto);
    moto.askMotorcycle();
    delete lockedMotorcycle;
    moto.askMotorcycle();

    return 0;
}
