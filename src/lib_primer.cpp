# include "lib_primer.h"

void use_auto() {
    // ex.2.35
    const int i = 42;
    auto j = i; 
    const auto &k = i; 
    auto *p = &i; 
    const auto j2 = i, &k2 = i;
}