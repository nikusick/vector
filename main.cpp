#include <iostream>
#include <vector>
#include "Vector.h"

using namespace std;

int main() {
    Value arr[3] = {1, 2, 3};
    Vector *v1 = new Vector(arr, 3, 2.0f);
    Vector *v2 = new Vector(*v1);
    Vector v;
    v1->insert(arr, 3,2);
    cout << v1->size() << " " << v1->capacity() << endl;
    v1->erase(1, 6);
    for (auto&& item : *v1) {
        cout << item;
    }
    delete v1, v2;
    return 0;
}
