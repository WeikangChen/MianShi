class A {

public:

    virtual ~A() { f(); }

    virtual void f() { cout << "A::f" << endl; }

};

class B: public A {

public:

    ~B() { }

    virtual void f() { cout << "B::f" << endl; }

};

A* a = new B;

delete a;
