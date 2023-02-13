#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Proxy
 *
 * - useful if you want to add some additional behaviors to an object of
 * some existing class without changing the client code
 *
 * - for example: a proxy can be used to have cache access to a database
 *
 */




/// Interface: declares the common operations for both RealSubject and Proxy
class Subject
{
    public:
        virtual ~Subject() {}
        virtual void request() const = 0;
};


class RealSubject : public Subject
{
    public:
        void request() const override {
            cout << "RealSubject: handling request.\n";
        }
};


class Proxy : public Subject
{
    private:
        RealSubject *real_subject_ = nullptr;

        bool checkAccess() const {
            cout << "Proxy: Checking access prior to firing a real request.\n";
            return true;
        }

        void LogAccess() const {
            cout << "Proxy: Logging the time of request.\n";
        }

    public:
        // not sure why constructor does a copy
        Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject)) {}

        ~Proxy() {
            delete real_subject_;
        }

        void request() const override {
            if (checkAccess()) {
                real_subject_->request();
                LogAccess();
            }
        }
};





int main() {
    std::cout << "Proxy\n\n";

    cout << "Client executing request using a real subject:\n";
    RealSubject *real_subject = new RealSubject;
    real_subject->request();

    cout << "\n\n";

    cout << "Client executing request using a proxy:\n";
    Proxy *proxy = new Proxy(real_subject);
    proxy->request();

    delete real_subject;
    delete proxy;

 
    return 0;
}