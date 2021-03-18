# pragma once
# ifndef OOP_H
# define OOP_H


// abstract class has at least one pure virtual/abstract method
// and cannot be instantiated
class Abstract{
    public:
        virtual void show() const = 0; // pure virtual function (abstract method in Java), must be overriden by child classes
};

class Base: public Abstract{
    private:
        int n_private{};
    protected:
        int n_protected{};
    public:
        int n_public{};
        Base();
        Base(int n_private, int n_protected);
        virtual ~Base(); // Base class should always has a virtual destructor

        void show() const override;
        virtual void func() const; // allow child to override, note: all member functions are virtual in java
};

class Derived: public Base{
    private:
        int n_derived{};

    public:
        Derived();
        Derived(int n_derived);
        Derived(int n_derived, int n_private, int n_protected);
        ~Derived();

        void show() const override;
        void func() const override;
};


void demo_oop();


# endif