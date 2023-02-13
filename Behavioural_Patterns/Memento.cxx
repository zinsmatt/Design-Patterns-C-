#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Memento
 *
 * - allows to make snapshot of an object's state and restoring it in the future.
 * - for example for serialization
 *
 * - add a serialization method inside the class instead of having an external function
 * - then a caretaker class can handle an history of several saved states
 *
 */


class Memento
{
    public:
        virtual ~Memento() {}
        virtual string GetName() const = 0;
        virtual string date() const = 0;
        virtual string state() const = 0;
};

class ConcreteMemento : public Memento
{
    private:
        string state_;
        string date_;

    public:

    ~ConcreteMemento() {cout << "Destructor ConcreteMemento\n";}
        ConcreteMemento(const string& state) : state_(state) {
            std::time_t now = std::time(0);
            date_ = std::ctime(&now);
        }

        string state() const override {
            return state_;
        }

        string GetName() const override {
            return date_ + " / (" + state_.substr(0, 9) + "...)";
        }

        string date() const override {
            return date_;
        }
};



// Main object that holds some important state
class Originator
{
    private:
        string state_ = nullptr;

        string GenerateRandomString(int length=10) {
            const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            int l = sizeof(alphanum) - 1;
            string res;
            for (int i = 0; i < length; ++i) {
                res += alphanum[std::rand() % l];
            }
            return res;
        }

    public:
        Originator(const string& state) : state_(state) {
            cout << "Originator: My initial state is: " << state_ << "\n";
        }

        void DoSomething() {
            std::cout << "Originator: I'm dogin something important.\n";
            state_ = GenerateRandomString(30);
            std::cout << "and my state has changed to: " << state_ << "\n";
        }


        Memento* Save() {
            return new ConcreteMemento(state_);
        }

        void Restore(Memento *memento) {
            state_ = memento->state();
            std::cout << "Originator: My state has be restored to: " << state_ << "\n";
        }
};



/**
 * The Caretaker doesn't depend on the Concrete Memento class. Therefore, it
 * doesn't have access to the originator's state, stored inside the memento. It
 * works with all mementos via the base Memento interface.
 */
class Caretaker
{
    private:
        std::vector<Memento*> mementos_;

        Originator *originator_;

    public:
        Caretaker(Originator *originator) : originator_(originator) {}

        ~Caretaker() {
            cout << "Destructor Caretaker" << endl;
            for (auto *m : mementos_) {
                cout << "delete memento " << m->GetName() << endl;;
                delete m;
            }
        }

        void Backup() {
            std::cout << "\nCaretaker: Saving Originator's state...\n";
            mementos_.push_back(originator_->Save());
        }

        void Undo() {
            if (mementos_.empty())
                return;

            Memento *latest = mementos_.back();
            mementos_.pop_back();

            cout << "Caretaker: Restoring state to: " << latest->GetName() << "\n";
            try {
                originator_->Restore(latest);
            } catch (...) {
                this->Undo();
            }
            delete latest;
        }

        void ShowHistory() const {
            cout << "Caretaker: Here's the list of mementors:\n";
            for (auto* m : mementos_) {
                cout << m->GetName() << "\n";
            }
        }
};




int main() {
    std::cout << "Memento\n\n";

    Originator *originator = new Originator("losc losc losc losc");
    Caretaker *caretaker = new Caretaker(originator);

    caretaker->Backup();
    originator->DoSomething();

    caretaker->Backup();
    originator->DoSomething();

    caretaker->Backup();
    originator->DoSomething();

    cout << "\n";
    caretaker->ShowHistory();

    cout << "\nClient: Now, let's rollback:\n\n";
    caretaker->Undo();

    cout << "\nClient: Once more!\n\n";
    caretaker->Undo();


    delete originator;
    delete caretaker;


    return 0;
}