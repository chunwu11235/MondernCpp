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
        Base(int n_private, int n_protected);
        ~Base();

        void show() const;
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

        void show() const;
        void func() const;
};


void demo_oop();


# endif