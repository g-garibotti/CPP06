#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main()
{
    Data original;
    original.id = 42;
    original.name = "original";
    original.value = 3.14;
    
    uintptr_t raw = Serializer::serialize(&original);
    Data* recovered = Serializer::deserialize(raw);
    
    std::cout << "Original address: " << &original << std::endl;
    std::cout << "Recovered address: " << recovered << std::endl;
    std::cout << "Are they equal? " << (&original == recovered ? "YES" : "NO") << std::endl;
    
    std::cout << "Recovered data: " << recovered->id << ", ";
    std::cout << recovered->name << ", " << recovered->value << std::endl;
    
    return 0;
}