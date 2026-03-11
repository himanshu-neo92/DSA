#include "TestBase.h"
#include "TestRegister.cpp"

int main() {
    TestBase::getInstance().runAll();
    return 0;
}
