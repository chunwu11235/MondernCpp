#include <iostream>
#include "design_patterns.h"

// #include "design_patterns.h"

int main() {
    // demo_abstract_factory();
    // demo_builder();
    std::cout << "--- Design Patterns ---" << std::endl;
    demo_builder();
    demo_abstract_factory();
    demo_factory();
    demo_prototype();
    demo_adaptor();
    demo_composite();
    demo_dynamic_decorator();
    demo_static_decorator();
    demo_functional_decorator();
    demo_strategy();
    demo_template_method();
}