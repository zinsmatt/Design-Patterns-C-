cmake_minimum_required(VERSION 3.14)
project(Design-Patterns)

set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -pthread")



set(NAMES_CREATIONAL
AbstractFactory
Builder
FactoryMethod
FactoryMethod_template
Prototype
Singleton)

set(NAMES_STRUCTURAL
Adapter_composition
Adapter_inheritance
Bridge
Composite
Decorator
Facade
Flyweight
Proxy)

set(NAMES_BEHAVIOURAL
Chain_of_Responsability
Iterator
Memento
State
Template_Method
Command
Mediator
Observer)


message("\nCreational patterns:")
foreach(name ${NAMES_CREATIONAL})
    message(${name})
    add_executable(${name} Creational_Patterns/${name}.cxx)
endforeach()


message("\nStructural patterns:")
foreach(name ${NAMES_STRUCTURAL})
    message(${name})
    add_executable(${name} Structural_Patterns/${name}.cxx)
endforeach()


message("\nBehavioural patterns:")
foreach(name ${NAMES_BEHAVIOURAL})
    message(${name})
    add_executable(${name} Behavioural_Patterns/${name}.cxx)
endforeach()
