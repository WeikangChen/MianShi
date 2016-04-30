
#include <string>
#include <iostream>
using namespace std;
class Animal
{
private:
   std::string m_strName;

protected:
   Animal(const std::string& strName):  m_strName(strName)
   {
   }
public:
   const std::string& GetName() { return m_strName; }
   const char* Speak() { return "???"; }
};

class Cat: public Animal
{
public:
   Cat(const std::string& strName): Animal(strName)
   {
   }
   const char* Speak() { return "Meow"; }
};

class Dog: public Animal
{
public:
   Dog(const std::string& strName) : Animal(strName)
   {
   }
   const char* Speak() { return "Woof"; }
};

int main()
{
   Cat cCat("Fred");
   Animal *pAnimal = &cCat;
   cout << "Animal is named " << pAnimal->GetName() << ", and it says " << pAnimal->Speak() << endl;

   int a = 5;

int b = 0;

int &r = a;


r = b++;


cout << a << r << b;
   return 0;
}
