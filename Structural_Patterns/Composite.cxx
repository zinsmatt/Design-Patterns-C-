#include <iostream>
#include <list>
#include <ctime>
#include <random>

using namespace std;

/**
 *  Composite
 * 
 * - useful when the data can be represented as a tree
 * - Base Interface: Component 
 * - Derived: Leaf and Composite
 * 
 */


// Abstract class
class Component {

    protected:
        Component* parent_ = nullptr;

    public:

        virtual ~Component() {} // to delete a derived class using a pointer of the base class

        void setParent(Component* parent) {
            parent_ = parent;
        }

        Component* getParent() {
            return parent_;
        }

        virtual bool isComposite() const = 0;

        // Integrate add() and remove() to the component interface so that
        // we can manipulate only base class pointers in the client
        virtual void add(Component* c) = 0;
        virtual void remove(Component* c) = 0;

        virtual int cost() const = 0;
        virtual void print() const = 0;
};


class Leaf : public Component
{
    private:
        int cost_ = 0;

    public:
        Leaf(int cost) : cost_(cost) {}

        bool isComposite() const override {
            return false;
        }

        int cost() const override {
            return cost_;
        }

        void add(Component*) override {} // do nothing
        void remove(Component*) override {} // do nothing
        
        void print() const override {
            cout << "Leaf: " << cost_ << "\n";
        }
};

class Composite : public Component
{
    private:
        list<Component*> components_;

    public:
        ~Composite() {
            for (auto pt : components_)
                delete pt;
        }

        int cost() const override {
            int c = 0;
            for (auto pt : components_)
                c += pt->cost();
            return c;
        }

        void add(Component *c) override {
            components_.push_back(c);
            c->setParent(this);
        }

        void remove(Component* c) override {
            components_.remove(c);
            c->setParent(nullptr);
        }

        bool isComposite() const override {
            return true;
        }

        void print() const override {
            cout << "Composite:\n";
            for (auto pt : components_)
                pt->print();
        }
};




int main() {
    srand(time(NULL));

    std::cout << "Composite\n";

    Component *root = new Composite;

    Component* to_delete = nullptr;
    for (int i = 0; i < 4; ++i) {
        Component *c = new Composite;
        if (i == 2)
            to_delete = c;
        for (int j = 0; j < rand()%10; ++j) {
            Component *l = new Leaf(rand() % 100);
            c->add(l);
        }
        root->add(c);
    }

    std::cout << "Total cost = " << root->cost() << "\n";

    root->print();

    root->remove(to_delete);
    cout << "\nDelete component !!\n\n";
    std::cout << "New total cost = " << root->cost() << "\n";

    root->print();

    delete root;
    delete to_delete;

    return 0;
}