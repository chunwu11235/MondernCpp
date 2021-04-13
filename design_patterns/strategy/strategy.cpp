#include "strategy.h"
#include <iostream>
#include <vector>
#include "string.h"
#include <memory>

using namespace std;

struct Book{
    int total_page{};
    int current_page{};

    Book(int total_page): total_page{total_page}, current_page{0} {};
    void move_current_page(int pages) {
        if( current_page + pages < total_page ) {
            current_page += pages;
        }else{
            current_page = total_page;
        };
    }
};

struct IStudyStrategy {
    virtual void study(Book&) const = 0;
};

struct StudyAtHome : IStudyStrategy {
    void study(Book& book) const override {
        book.move_current_page(20);
    }
};

struct StudyAtLibrary : IStudyStrategy {
    void study(Book& book) const override {
        book.move_current_page(50);
    }
};

struct Undergrad{
    string name{};
    Book& book;
    shared_ptr<IStudyStrategy> strategy;
    Undergrad(string&& name, Book& book, const shared_ptr<IStudyStrategy>& strategy): 
        name{std::move(name)}, book{book}, strategy{strategy} {};

    void prepareForMidterm() const {
        cout << name << " started from page " << book.current_page << endl;
        strategy->study(book);
        cout << name << " has read to page" << book.current_page << endl;
    }

    void setStrategy(const shared_ptr<IStudyStrategy>& strategy) {
        this->strategy = strategy;
    }
};

template<typename T>
struct Kid{
    const T& strategy;
    Book& book;

    Kid(Book& book, const T& strategy): book{book}, strategy{strategy} {};
    void readingForFun() const {
        cout << "A kid started to reading from page " << book.current_page << endl;
        strategy.study(book);
        cout << "and has read to page " << book.current_page << endl;
    }
};


void demo_strategy() {
    std::cout << "--- demo strategy \n";

    std::cout << "--- dynamic strategy\n";

    auto strategy1 = make_shared<StudyAtHome>();
    auto strategy2 = make_shared<StudyAtLibrary>();
    Book Math101{300};
    Book CS101{500};

    Undergrad Lisa{"Lisa", Math101, strategy1};
    Lisa.prepareForMidterm();
    Lisa.setStrategy(strategy2);
    Lisa.prepareForMidterm();

    Kid<StudyAtHome> Kyle{CS101, StudyAtHome{}};
    Kyle.readingForFun();

};