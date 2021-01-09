#include <iostream>
#include "S_Vector.h"
#include <vector>
#include <string>

using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;

    S_Vector<vector<int> *> temp;
    int K = 50;
    for(int i = 0; i<K; ++i){
        temp.push_back(new vector<int>(1,i));
        cout << "size:" << temp.size() << "\tcapacity:" << temp.capacity()  << "\taddr:"<< &temp[0] << endl;
    }

//    for(int i = 0; i<K/2; ++i){
//        temp.pop_back();
//        cout << "size:" << temp.size() << "\tcapacity:" << temp.capacity()  << "\taddr:"<< &temp[0] << endl;
//    }

    temp.erase(temp.begin()+2,temp.begin()+8);
    temp.erase(temp.end()-1);
    cout << "size:" << temp.size() << "\tcapacity:" << temp.capacity()  << "\taddr:"<< endl;
    //temp.erase(2,5);
//    temp.clear();
//    cout << "size:" << temp.size() << "\tcapacity:" << temp.capacity()  << "\taddr:"<< endl;
//    S_Vector<int> tt = temp;
//    cout << "size:" << tt.size() << "\tcapacity:" << tt.capacity()  << "\taddr:"<< &tt[0] << endl;

    for(unsigned int i=0; i<temp.size(); ++i){
        cout << temp.at(i)->data()[0] << endl;
    }


    return 0;
}
