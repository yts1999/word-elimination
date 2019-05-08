#include "manager.h"

Manager::Manager() {}

int Manager::get_probnum() const {
    return probnum;
}

void Manager::inc_probnum() {
    probnum++;
}
