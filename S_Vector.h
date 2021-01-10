//
// Created by wusong on 2021/1/8.
//

#ifndef S_VECTOR_S_VECTOR_H
#define S_VECTOR_S_VECTOR_H
template <typename data_type>
class S_Vector {

public:
    S_Vector() = default;
    explicit S_Vector(unsigned int size);
    S_Vector(unsigned int size, data_type value);
    S_Vector(S_Vector& x);
    bool reserve(const unsigned int &new_capacity);
    int resize(unsigned int new_size);
    int resize(unsigned int new_size,data_type value);
    S_Vector<data_type>& operator= (const S_Vector<data_type>& x);         // copy
    S_Vector<data_type>& operator= (S_Vector<data_type>&& x) noexcept;     // move
    data_type& operator[] (unsigned int pos);
    const data_type& operator[] (unsigned int pos) const;

    int length();
    int size();
    int capacity();
    int push_back(const data_type &value);
    int pop_back();
    int insert(const unsigned int &pos, const data_type &value);
    int insert(const unsigned int &pos, const unsigned int &n, const data_type &value);
    data_type at(unsigned int pos);
    int begin(){return 0;};
    int end(){return data_size;};
    unsigned int erase(const unsigned int &pos);
    unsigned int erase(const unsigned int &start_pos, const unsigned int &end_pos);
    void clear();
    ~S_Vector();

private:
    data_type * data = nullptr;
    unsigned int data_size = 0;
    unsigned int v_capacity = 0;
};

template<typename data_type>
S_Vector<data_type>::S_Vector(unsigned int size) {
    if(size == 0) return;
    this->data = new(std::nothrow) data_type[size];
    if(this->data == nullptr) {
//        exit(-1);                   // which is better?
//        throw std::bad_alloc();
        return;
    }
    else{
        data_size = size;
        v_capacity = size;
    }
}

template <typename data_type>
S_Vector<data_type>::S_Vector(unsigned int size, data_type value) : S_Vector(size){
    if(this->data != nullptr) {
        for(int i=0; i<size; ++i)
            this->data[i] = value;
    }
}

template<typename data_type>
S_Vector<data_type>::S_Vector(S_Vector &x) {
    this->data = new(std::nothrow) data_type[x.v_capacity];
    if(this->data != nullptr){
        for(int i=0; i<x.data_size; ++i){
            this->data[i] = x.data[i];
        }
        data_size  = x.data_size;
        v_capacity = x.v_capacity;
    }
}

template<typename data_type>
bool S_Vector<data_type>::reserve(const unsigned int &new_capacity) {
    if(new_capacity < v_capacity) return false;
    auto * temp = new(std::nothrow) data_type[new_capacity];
    if(temp == nullptr){
//        exit(-1);                   // which is better?
//        throw std::bad_alloc();
        return false;
    }

    for(int i=0; i<data_size; ++i){
        temp[i] = this->data[i];
    }
    delete[] this->data;             // release
    this->data = temp;
    temp = nullptr;
    v_capacity = new_capacity;
    return true;
}

template<typename data_type>
int S_Vector<data_type>::resize(unsigned int new_size) {
    if(new_size > data_size){
        if(!reserve(new_size)) return -1;
    }
    data_size = new_size;
    return data_size;
}

template<typename data_type>
int S_Vector<data_type>::resize(unsigned int new_size, data_type value) {
    if(new_size > data_size){
        if(reserve(new_size)) return -1;
        for(;data_size != new_size; data_size ++)
            this->data[data_size] = value;
    }
    data_size = new_size;
    return data_size;
}

template<typename data_type>
S_Vector<data_type> &S_Vector<data_type>::operator=(const S_Vector<data_type> &x) {
    if(this == &x) return *this;
    this->clear();
    if(this->data!= nullptr) delete[] this->data;               // release old memory
    this->data = new(std::nothrow) data_type[x.v_capacity];     // alloc new memory
    if(this->data != nullptr){
        for(int i=0; i<x.data_size; ++i){     //copy data
            this->data[i] = x.data[i];
        }
        data_size  = x.data_size;
        v_capacity = x.v_capacity;
    }
    return *this;
}

template<typename data_type>
S_Vector<data_type> &S_Vector<data_type>::operator=(S_Vector<data_type> &&x) noexcept {
    if(this == &x) return *this;
    this->clear();
    if(this->data!= nullptr) delete[] this->data;               // release old memory
    this->data = new(std::nothrow) data_type[x.v_capacity];     // alloc new memory
    if(this->data != nullptr){                //copy data
        for(int i=0; i<x.data_size; ++i){
            this->data[i] = x.data[i];
        }
        data_size  = x.data_size;
        v_capacity = x.v_capacity;
    }
    return *this;
}

template<typename data_type>
data_type &S_Vector<data_type>::operator[](const unsigned int pos) {
    if(pos < data_size) return this->data[pos];
    else{
        throw std::range_error("A cross-border access occurred.\r\nyour input pos exceeded the max_size.\r\n");
    }
}

template<typename data_type>
const data_type &S_Vector<data_type>::operator[](unsigned int pos) const {
    const data_type value = this->data[pos];
    if(pos < data_size) return value;
    else{
        throw std::range_error("A cross-border access occurred.\r\nyour input pos exceeded the max_size.\r\n");
    }
}

template <typename data_type>
int S_Vector<data_type>::length() {
    return data_size;
}

template <typename data_type>
int S_Vector<data_type>::size() {
    return data_size;
}

template <typename data_type>
int S_Vector<data_type>::capacity() {
    return v_capacity;
}

template<typename data_type>
int S_Vector<data_type>::push_back(const data_type &value) {
    if(data_size == v_capacity) {                                     // dynamic capacity adjustment
        if(!reserve(data_size == 0 ? 1 : data_size*2)){
            return -1;
        }
    }
    this->data[data_size++] = value;
    return data_size;
}

template<typename data_type>
int S_Vector<data_type>::pop_back() {
    return data_size > 0 ? --data_size : -1;
}

template<typename data_type>
int S_Vector<data_type>::insert(const unsigned int &pos, const data_type &value) {

    if((this->data == nullptr && pos > 0)  || pos >= data_size) return -1;

    unsigned int i=0, j=0;
    if(data_size == v_capacity){
        unsigned int new_capacity = data_size == 0 ? 1 : (data_size+1)*2;
        auto * temp = new(std::nothrow) data_type[new_capacity];      // realloc
        if(temp == nullptr){
            return -1;
        }
        while (j < data_size){                     // copy data
            if(i!=pos) temp[i] = this->data[j++];
            i++;
        }
        temp[pos] = value;
        data_size ++;
        v_capacity = new_capacity;
        if(this->data != nullptr)                 // Free original memory
            delete[] this->data;
        this->data = temp;                        // new ptr
        temp = nullptr;
    }
    else{
        i = data_size;
        while (pos < i){                          // move data backward
            this->data[i] = this->data[i-1];
            i --;
        }
        data_size ++;
        this->data[pos] = value;
    }
    return static_cast<int>(pos);
}

template<typename data_type>
int S_Vector<data_type>::insert(const unsigned int &pos, const unsigned int &n, const data_type &value) {

    if(this->data == nullptr && pos > 0) return -1;

    unsigned int i=0, j=0;
    if((data_size+n) > v_capacity){
        unsigned int new_capacity = data_size == 0 ? 1 : (data_size+n)*2;
        auto * temp = new(std::nothrow) data_type[new_capacity];     // realloc
        if(temp == nullptr){
            return -1;
        }
        while (i != pos){
            temp[i] = this->data[i];
            i ++;
        }
        while(j != n){                     // fill the n data
            temp[i++] = value;
            j ++;
        }
        j = pos;
        while(j < data_size){
            temp[i++] = this->data[j++];
        }
        data_size += n;
        v_capacity = new_capacity;
        if(this->data != nullptr)
            delete[] this->data;
        this->data = temp;
        temp = nullptr;
    }
    else{
        i = data_size - 1;
        j = i + n;
        while(i >= pos){                          // move n units(sizeof(data_type)) backward
            this->data[j--] = this->data[i--];
        }
        i = pos;
        j = n;
        while(j--){
            this->data[i++] = value;
        }
        data_size += n;
    }
    return static_cast<int>(pos+n);
}

template<typename data_type>
data_type S_Vector<data_type>::at(unsigned int pos) {
    if(pos < data_size)
        return this->data[pos];
    else
        throw std::range_error("A cross-border access occurred.\r\nyour input pos exceeded the max_size.\r\n");
}

template<typename data_type>
unsigned int S_Vector<data_type>::erase(const unsigned int &start_pos, const unsigned int &end_pos) {
    unsigned int offset_a = start_pos, offset_b = end_pos;
    if(end_pos > data_size) offset_b = data_size;
    for(;offset_b < data_size; offset_b++)
        this->data[offset_a++] = this->data[offset_b];
    data_size -= (end_pos - start_pos);
    return start_pos;
}

template<typename data_type>
unsigned int S_Vector<data_type>::erase(const unsigned int &pos) {
    if(pos > data_size) return data_size;
    unsigned int start_pos = pos;
    for(unsigned int i=pos+1; i<data_size; ++i){
        this->data[start_pos++] = this->data[i];
    }
    data_size -= 1;
    return pos;
}

template<typename data_type>
void S_Vector<data_type>::clear() {
    data_size = 0;
//    v_capacity = 0;
//    if(this->data)
//        delete[] this->data;
//    data = nullptr;
}

template<typename data_type>
S_Vector<data_type>::~S_Vector() {
    if(this->data != nullptr)
        delete[] this->data;
}

#endif //S_VECTOR_S_VECTOR_H
