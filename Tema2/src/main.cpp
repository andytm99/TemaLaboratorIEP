#include <iostream>
class Pasager
{
};
class Car
{
private:
        std::string brandName;
        std::string modelName;
        std::string color;
        int yearOfFabrication;

public:
        int horsePower=99;
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
        if(this==&C)  //this condition solves our self assignment problem
        {
        std::cout<<"Self Assignment Car\n";
        return *this;
        }

        std::cout<<"Copy assignment operator\n";
        this->brandName=C.brandName;
        this->modelName=C.modelName;
        this->color=C.color;
        this->yearOfFabrication=C.yearOfFabrication;
        //this->horsePower=C.horsePower;
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

    ~Motorcycle()
    {
        std::cout<<"Motorcycle is destroyed\n";
    }
};
void printCars(Car& C)//functie de afisat detalii masini
{
    std::cout<<C.getBrandName()<<" "<<C.getModelName()<<" "<<C.getColor()<<" "<<C.getYearOfFabrication()<<"\n";
}
void printMoto(Motorcycle& M)//functie de afisat detalii motociclete
{
    std::cout<<"---------"<<M.getBrandName()<<" "<<M.getModelName()<<"--------\n";
}
class Garage
{

private:
        Car *masina;

public:
     Garage()
     :  masina()
        {std::cout<<"Empty Garage constructor\n";}

        Garage(Car *m)
       : masina(m)
       { std::cout<<"Garage constructor\n";}

       Garage(const Garage &B)
       {
       std::cout<<"Copy-Constructor\n";
       this->masina=B.masina;
       }

       Garage& operator=(const Garage& B)
       {
        if(this==&B)  //this condition solves our self assignment problem
        {
        std::cout<<"Self Assignment Garage\n";
        return *this;
        }

        std::cout<<"Copy assignment operator\n";
        Car *pOrig = masina; // remember original masina
        masina = new Car(*B.masina); // point masina to a copy of B's Car
        delete pOrig;
        return *this;
       }

};

int main()
{
    int x=7;
    std::cout<<x<<"\n";
    Car c1("Ford","Focus","Albastru",2004);
    Car c2(c1);//Copy constructor
    {
    Car c3;//punem acolade pentru a vedea ca se distruge obiectul c3 atunci cand si-a indeplinit scopul (in cazul nostru cand acolada s-a inchis)
    }
    printCars(c1);
    c1.setModelName("Fiesta");//schimbam numele modelului
    c1.setYearOfFabrication(2010);//schimbam anul fabricatiei
    printCars(c1);
    printCars(c2);
    Motorcycle m1;
    Motorcycle m3("Suzuki","Hayabusa");
    printMoto(m3);
    //Motorcycle m2=m3;//aici este eroare deoarece este "dezactivata functionalitatea de copy constructor
    //m1=m3;
    Car a,b,c;
    a=b=c=c1;
    printCars(a);
    c1=c1;//self assignment car
    /*Car *masina1;
    Garage garaj1(masina1);
    garaj1=garaj1;//self assignment garaj*/
    Car c4;
    c1.horsePower=80;
    c4=c1;
    std::cout<<c4.horsePower<<"\n";

    return 0;
}
