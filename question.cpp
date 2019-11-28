#include <iostream>
using namespace std;
class Blue {
protected:
    struct Red {
        int redValue;
    };
    int blueValue;
    Red* red;
public:
    Blue();
    void function() {
        red = new Red;
    }
};