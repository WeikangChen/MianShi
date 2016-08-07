#include<iostream>


struct Base { 
    virtual void print( int x = 1 ) {
        std::cout << "Base:" << x; 
    }

}; 
 
struct Derived : Base { 
    virtual void print( int x = 2) { 
        std::cout << "Derived:" << x; 
    }

}; 

int main() 
{
	Base * B = new Derived; 
	B->print();

	return 0;
}
