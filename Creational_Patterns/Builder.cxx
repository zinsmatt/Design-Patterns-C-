#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 *  Builder:
 * 
 * - useful to create complex objects. It avoids to have a large nb of subclasses: House, HouseWithGarden, HouseWithGardenNoPool, HouseWithGarendWithPool, HouseNoGardenWithPool, ...
 * - Avoids to have large ugly constructors: House(windows, doors, rooms, roof, hasGarage, hasGarden, hasSwimmingPool, ... )
 *
 * - can be used with a Director which contains a recipe to build certain type of objects
 * 
 */



class Product1
{
    public:
        std::vector<string> parts_;
        void listParts() const {
            cout << "Product parts: ";
            for (auto &s : parts_)
                cout << s << " ";
            cout << "\n\n";
        }

};


// Builder interface
class Builder
{
    // No base product because the concrete builder can build different types of unrelated objects
    public:
        virtual ~Builder() {}

        virtual void producePartA() = 0;
        virtual void producePartB() = 0;
        virtual void producePartC() = 0;
};

class ConcreteBuilder1 : public Builder
{
    private:
        Product1* product_ = nullptr;

    public:
        ConcreteBuilder1() {
            this->reset();
        }

        ~ConcreteBuilder1() {
            if (product_)
                delete product_;
        }

        void reset() {
            product_ = new Product1;
        }

        void producePartA() override {
            this->product_->parts_.push_back("PartA1");
        }
        void producePartB() override {
            this->product_->parts_.push_back("PartB1");
        }
        void producePartC() override {
            this->product_->parts_.push_back("PartC1");
        }

        Product1* getProduct() {
            auto* p = product_;
            reset();
            return p;
        }
};




class Director
{
    private:
        Builder *builder_ = nullptr;

    public:
        void setBuilder(Builder* builder) {
            builder_ = builder;
        }

        void buildMinimalViableProduct() {
            builder_->producePartA();
        }

        void buildFullProduct() {
            builder_->producePartA();
            builder_->producePartB();
            builder_->producePartC();
        }
};




int main() {
    std::cout << "Builder\n";

    Director director;

    ConcreteBuilder1 *builder = new ConcreteBuilder1();
    director.setBuilder(builder);
    cout << "Standard product:\n";
    director.buildMinimalViableProduct();

    auto* prod1 = builder->getProduct();
    prod1->listParts();
    
    cout << "Full product: \n";
    director.buildFullProduct();

    auto *prod2 = builder->getProduct();
    prod2->listParts();

    cout << "Custom product : \n";
    builder->producePartA();
    builder->producePartC();
    auto *prod3 = builder->getProduct();
    prod3->listParts();

    delete prod1;
    delete prod2;
    delete prod3;
    delete builder;
    
    return 0;
}