#include <iostream>
#include "src/ArgsMapper/argsmapper.h"

int main(int, char *argv[]) {
    try {
        const ArgsMapper mapper(argv);
    } catch (char const *errMsg) {
        std::cerr << errMsg;
    }

    return 0;
}
