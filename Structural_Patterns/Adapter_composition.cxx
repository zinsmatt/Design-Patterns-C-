#include <iostream>
#include <list>
#include <ctime>
#include <random>

using namespace std;

/**
 *  Adapter (by object composition)
 * 
 * 
 */


class Target
{
    public:
        virtual ~Target() {}

        virtual string request() const {
            return "Normal Request made by the target";
        }
};

class ToAdapt
{
    public:
        string specialRequest() const {
            return "XXXSpecial request my by the object to adaptXXX";
        }
};

class Adapter : public Target
{
    private:
        ToAdapt *to_adapt_ = nullptr;

    public:
        Adapter(ToAdapt *to_adapt) : to_adapt_(to_adapt) {}

        virtual string request() const override {
            auto res = to_adapt_->specialRequest();
            return res.substr(3, res.size()-6);
        }
};



int main() {
    std::cout << "Adapter (by object composition)\n\n";

    Target target;
    cout << "target request: " << target.request() << "\n\n";

    ToAdapt to_adapt;
    cout << "to adapt special request: " << to_adapt.specialRequest() << "\n\n";


    Adapter adapter(&to_adapt);
    cout << "to adapt adatped request: " << adapter.request() << "\n\n";


    return 0;
}