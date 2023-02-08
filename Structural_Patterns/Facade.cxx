#include <iostream>
#include <list>
#include <ctime>
#include <random>

using namespace std;

/**
 *  Facade
 * 
 * - provides a simplified (but limited) interface to a complex system of classes, library or framework
 * 
 * - usually the facade manage the full life cycle of objects they use
 * 
 */


class Subsystem1
{
    public:
        string operation1() const {
            return "Subsystem1: Ready !!\n";
        }

        string operationN() const {
            return "Subsystem1: Get Ready !!\n";
        }
};

class Subsystem2
{
    public:
        string operation1() const {
            return "Subsystem2: Go !!\n";
        }

        string operationZ() const {
            return "Subsystem2: Fire !!\n";
        }
};

class Facade
{
    protected:
        Subsystem1 *subsys1_ = nullptr;
        Subsystem2 *subsys2_ = nullptr;
    
    public:
        Facade(Subsystem1 *sys1, Subsystem2 *sys2) : 
            subsys1_(sys1), subsys2_(sys2) {
                if (!subsys1_)
                    subsys1_ = new Subsystem1;
                if (!subsys2_)
                    subsys2_ = new Subsystem2;
            }
        
        ~Facade() {
            delete subsys1_;
            delete subsys2_;
        }

        string operation() {
            string res = "Facade initializes subsystems:\n";
            res += subsys1_->operation1();
            res += subsys2_->operation1();
            res += "Facage orders subsytems to perform actions: \n";
            res += subsys1_->operationN();
            res += subsys2_->operationZ();
            return res;
        }
};


int main() {
    std::cout << "Facade\n\n";

    Subsystem1 *ss1 = new Subsystem1;
    Subsystem2 *ss2 = new Subsystem2;
    Facade *facade = new Facade(ss1, ss2);

    cout << facade->operation() << "\n";

    delete facade;

    return 0;
}