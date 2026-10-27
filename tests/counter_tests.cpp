#include <cstdio>

#include "../src/counter.h"

#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            std::printf("FAILED: %s (line %d)\n", #cond, __LINE__);        \
            return 1;                                                      \
        }                                                                  \
    } while (0)

int main() {
    Counter c;
    CHECK(c.Value() == 0);
    CHECK(c.Increment() == 1);
    CHECK(c.Increment() == 2);
    CHECK(c.Value() == 2);
    c.Reset();
    CHECK(c.Value() == 0);
    std::printf("All tests passed\n");
    return 0;
}
