#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Chain of Responsibility
 * 
 * - allows passing a request along a chain of potential handlers until one of them handles the request
 * 
 * - example: in a GUI propagate a signal from th ebottom to the main app. Stop when the handler can handle it.
 */



class Handler
{
    public:
        virtual Handler* setNext(Handler *handler) = 0;
        virtual string handle(const string& request) = 0;

        virtual ~Handler() {}
};

class AbstractHandler : public Handler
{
    private:
        Handler *next_;
    
    public:
        AbstractHandler() : next_(nullptr) {}

        Handler* setNext(Handler *handler) override {
            next_ = handler;
            return handler; // to easily create a list of handler a->setNext(b)->setNext(c);
        }

        // abstract handler can only propagate the request
        string handle(const string& request) override {
            if (next_) {
                return next_->handle(request);
            }
            return "";
        }
};


class MonkeyHandler : public AbstractHandler
{
    public:
        string handle(const string& request) override {
            if (request == "Banana") {
                return "Monkey: I'll eat the " + request + "\n";
            } else {
                return AbstractHandler::handle(request);
            }
        }
};


class SquirrelHandler : public AbstractHandler
{
    public:
        string handle(const string& request) override {
            if (request == "Nut") {
                return "Squirrel: I'll eat the " + request + "\n";
            } else {
                return AbstractHandler::handle(request);
            }
        }
};


class DogHandler : public AbstractHandler
{
    public:
        string handle(const string& request) override {
            if (request == "MeatBall") {
                return "Dog: I'll eat the " + request + "\n";
            } else {
                return AbstractHandler::handle(request);
            }
        }
};

void ClientCode(Handler &handler) {
    vector<string> food = {"Nut", "Banana", "Cup of Tea", "MeatBall"};

    for (auto& meal : food) {
        cout << "Client: Who wants a " << meal <<  " ?\n";
        string res = handler.handle(meal);
        if (!res.empty()) {
            cout << "    " << res << "\n";
        } else {
            cout << "    " << meal << " was left untouched\n\n";
        }
    }
}



int main() {
    std::cout << "Chain of Responsability\n\n";

    MonkeyHandler *monkey = new MonkeyHandler;
    SquirrelHandler *squirrel = new SquirrelHandler;
    DogHandler *dog = new DogHandler;

    monkey->setNext(squirrel)->setNext(dog);

    cout << "\nChain: monkey > squirrel > dog\n";
    ClientCode(*monkey);

    cout << "\n\nChain: squirrel > dog\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;

    return 0;
}