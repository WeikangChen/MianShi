
struct A { void f(); };
struct B { int f(); };
struct C : A, B { };

int main() {
   C* pc;

   pc->A();     // statement 1
   pc->A::f();    // statement 2
   pc->B::f();    // statement 3
   pc->A::B::f();    // statement 4

   return 0;
}
