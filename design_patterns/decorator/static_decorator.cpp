#include "static_decorator.h"
#include <iostream>
#include "string.h"

// mixin inheritance
// perfect forwarding

struct Person{
    virtual void talk() const = 0;
};

struct America: public Person{
    void talk() const override {
        std::cout << "talking in English\n";
    }
};

struct Japanese: public Person{
    void talk() const override {
        std::cout << "talking in Japansese\n";
    }
};

template <typename T>
struct PhD : T{
    std::string school{};
    std::string field{};

    // variadic template
    template<typename... Args>
    PhD(std::string&& school, std::string&& field, Args&&... args): school{school}, field{field}, T{std::forward<Args>(args)...} {};

    void research() const {
        std::cout << "doing research in " << field << std::endl;
    }
};

template <typename T>
struct SuperHero : T{
    std::string superPower{};

    // variadic template
    template<typename... Args>
    SuperHero(std::string&& superPower, Args&&... args): superPower{superPower}, T{std::forward<Args>(args)...} {};

    void saveTheWorld() const {
        std::cout << "saving the world with " << superPower << std::endl;
    }
};


void demo_static_decorator() {
    std::cout << "--- Demo Static Decorator---\n";

    std::cout << "---\n";
    SuperHero<PhD<Japanese>> p1{"Math", "UW", "Math"};
    p1.talk();
    p1.research();
    p1.saveTheWorld();

    std::cout << "---\n";
    PhD<SuperHero<America>> p2{"X-Mansion", "telepath", "invisibility"};
    p2.research();
    p2.saveTheWorld();
    p2.talk();
    
}