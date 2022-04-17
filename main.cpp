#include <iostream>
#include <vector>
#include "Vector.h"

using namespace std;

int main() {
    Value arr[3] = {1, 2, 3};
    Vector *v1 = new Vector(arr, 3, 2.0f);
    Vector *v2 = new Vector(*v1);
    Vector v;
    for (int i = 0; i < 20; ++i) {
        v.pushBack(i);
    }
    cout << v.size() << " " << v.capacity() << endl;
    for (int i = 0; i < 19; ++i) {
        v.popFront();
    }
    cout << v.size() << " " << v.capacity() << endl;
    v.shrinkToFit();
    cout << v.size() << " " << v.capacity() << endl;
    v.popFront();
    v.popFront();
    v.shrinkToFit();
    cout << v.size() << " " << v.capacity() << endl;
    v.pushBack(1);
    cout << v.size() << " " << v.capacity() << endl;
    delete v1, v2;
    return 0;
}
