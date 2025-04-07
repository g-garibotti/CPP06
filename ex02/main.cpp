#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate(void)
{
    srand(time(NULL));
    int random = rand() % 3;
    
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else
        return new C();
}


void	identify(Base* p)
{
	if (dynamic_cast<A*>(p))
    {
		std::cout << "Identify as A" << std::endl;
	}
    else if (dynamic_cast<B*>(p))
    {
		std::cout << "Identify as B" << std::endl;
	} 
    else if (dynamic_cast<C*>(p))
    {
		std::cout << "Identify as C" << std::endl;
	}
}

void	identify(Base& p)
{
	if (dynamic_cast<A*>(&p))
    {
		std::cout << "Identify as A" << std::endl;
	}
    else if (dynamic_cast<B*>(&p))
    {
		std::cout << "Identify as B" << std::endl;
	}
    else if (dynamic_cast<C*>(&p))
    {
		std::cout << "Identify as C" << std::endl;
	}
}

int	main() {
	Base *base = generate();
	
	identify(base);
	identify(*base);
	delete base;
	return (0);
}