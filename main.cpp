#include <iostream>
#include <vector>
#include "Vector.h"

using namespace std;

void assert(const vector<double>& v1, Vector& v2) {
    try {
        cout << "_size v1: " << v1.size() << endl;
        cout << "_size v2: " << v2.size() << endl;
        cout << "_capacity v1: " << v1.capacity() << endl;
        cout << "_capacity v2: " << v2.capacity() << endl;
        if ((v1.size() != v2.size()) | (v1.capacity() != v2.capacity())) {
            throw -1;
        }
        cout << "V1: ";
        for (size_t i = 0; i < v1.size(); ++i) {
            cout << v1[i] << " ";
        }
        Value *v3 = v2.get_data();
        cout << "\nV2: ";
        for (size_t i = 0; i < v2.size(); ++i) {
            cout << v3[i] << " ";
        }
        for (size_t i = 0; i < v2.size(); ++i) {
            if (v1[i] != v3[i]) {
                throw -1;
            }
        }
    }
    catch(int) {
        cout << "Error: v1 != v2" << endl;
    }
}

int main() {
    vector <double> v1; // для стандартной библиотеки
    Vector v2; // для Vector.h
    assert(v1, v2);
    v1.push_back(1);
    assert(v1, v2);
    return 0;
}
