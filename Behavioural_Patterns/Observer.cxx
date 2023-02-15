#include <iostream>
#include <list>
#include <ctime>
#include <random>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


using namespace std;

/**
 *  Observer
 *
 * - allows some objects to notify other objects about changes in their state.
 * 
 * - provides a way to subscribe / unsubscribe
 *
 */

class IObserver
{
    public:
        virtual ~IObserver() {}
        virtual void update(const string& message_from_subject) = 0;
};

class ISubject
{
    public:
        virtual ~ISubject() {}
        virtual void attach(IObserver *observer) = 0;
        virtual void detach(IObserver *observer) = 0;
        virtual void notify() = 0;
};

class Subject : public ISubject
{
    private:
        std::list<IObserver*> list_observer_;
        string message_;

    public:
        virtual ~Subject() {
            cout << "GoodBye I was a subject\n";
        }

        void attach(IObserver *observer) override {
            list_observer_.push_back(observer);
        }

        void detach(IObserver *observer) override {
            list_observer_.remove(observer);
        }

        void notify() override {
            cout << "There are " << list_observer_.size() << " observers. Notify them all.\n";
            for (auto *o : list_observer_) {
                o->update(message_);
            }
        }

        void createMessage(const string& msg) {
            message_ = msg;
            notify();
        }

        void someBusinessLogic() {
            message_ = "change message losc";
            notify();
            cout << "I'm about to do some thing important\n";
        }
};

class Observer : public IObserver
{
    private:
        string message_from_subject_;
        Subject &subject_;
        static int static_number_;
        int number_;

    public:
        Observer(Subject &subject) : subject_(subject) {
            subject.attach(this);
            number_ = Observer::static_number_++;
            cout << "Hi ! I'm observer " << number_ << ".\n";
        }

        virtual ~Observer() {
            cout << "GoodBye, I was Observer " << number_ << ".\n";
        }

        void update(const string& message_from_subject) override {
            message_from_subject_ = message_from_subject;
            printInfo();
        }

        void printInfo() const {
            cout << "Observer " << number_ << ": a new message is available --> " << message_from_subject_ << ".\n";
        }

        void removeFromTheList() {
            subject_.detach(this);
            cout << "Observer " << number_ << " removed from the list.\n";
        }
};

int Observer::static_number_ = 0;


int main() {
    std::cout << "Observer\n\n";


    Subject *subject = new Subject;

    Observer *obs0 = new Observer(*subject);
    Observer *obs1 = new Observer(*subject);
    Observer *obs2 = new Observer(*subject);
    Observer *obs3;
    Observer *obs4;

    subject->createMessage("Hello World!");
    obs2->removeFromTheList();

    subject->createMessage("Allez le LOSC!!!");
    obs3 = new Observer(*subject);

    obs1->removeFromTheList();
    obs4 = new Observer(*subject);

    subject->createMessage("LOSC LOSC LOSC");
    obs4->removeFromTheList();

    subject->someBusinessLogic();

    obs3->removeFromTheList();
    obs0->removeFromTheList();

    delete obs0;
    delete obs1;
    delete obs2;
    delete obs3;
    delete obs4;
    delete subject;

    return 0;
}