#include "Main_CSM.h"


int main() {
    CustomerServiceModule csm;
    csm.initializeWithDummyUsers();
    csm.run();
    return 0;
}