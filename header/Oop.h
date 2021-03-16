# pragma once
# ifndef OOP_H
# define OOP_H

class Base{
    private:
        int n_private{};
    protected:
        int n_protected{};
    public:
        int n_public{};
        Base();
        ~Base();
};

class Derived: public Base{
    private:
        int n_derived{};

    public:
        Derived();
        Derived(int n_derived);
        ~Derived();
};


void demo_oop();


# endif