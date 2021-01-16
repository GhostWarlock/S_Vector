//
// Created by wusong on 2021/1/8.
//

#ifndef S_VECTOR_S_VECTOR_H
#define S_VECTOR_S_VECTOR_H

template <typename T>
class S_Vector {
public:
    typedef T value_type;
    typedef value_type* iterator;     //对于vector的线性存储结构，普通指针就可以实现迭代器的功能 因此 iterator类型为value_type
    // for vector memory structure, an ordinary pointer can realize the function of iterator
    // so sets the iterator type as value_ type pointer
public:
    S_Vector() = default;                 // Constructs an empty container, with no elements.
    explicit S_Vector(size_t n);          // Constructs a container with n elements.
    S_Vector(size_t n, value_type value); // Constructs a container with n elements. initialize with the value.
    S_Vector(S_Vector& x);                // Constructs a container with a copy of each of the elements in x, in the same order.

    void reserve(const size_t &new_capacity);      // changes the storage capacity
    void resize(size_t new_size);                  // changes vector size  Increase/decrease
    void resize(size_t new_size,value_type value); // Increase vector size, fill with "value"

    S_Vector<value_type>& operator= (const S_Vector<value_type>& x);         // copy
    S_Vector<value_type>& operator= (S_Vector<value_type>&& x) noexcept;     // move
    value_type& operator[] (size_t pos);
    const value_type& operator[] (size_t pos) const;

    size_t length();       // gets vector length
    size_t size();         // gets vector size, Equal to length
    size_t capacity();     // gets the storage capacity

    void push_back(const value_type &value);      // adds a new element at the end of the vector,
    void pop_back();                              // removes the last element in the vector,

    iterator insert(const iterator &pos, const value_type &value);  // inserts a element in specified pos
    iterator insert(const iterator &pos, const size_t &n, const value_type &value);  // inserts n elements from specified pos

    value_type at(const iterator &pos);    // gets the value at "pos"
    iterator begin(){return start;};       // gets vector start iterator
    iterator end(){return finish;};        // gets vector end iterator
    iterator erase(const iterator &pos);   // erases a element from specified pos
    iterator erase(const iterator &start_pos, const iterator &end_pos); // erases elements from start_pos(included) to end_pos(included).
    void clear();
    ~S_Vector();

private:
    iterator start = nullptr;
    iterator finish = nullptr;
    iterator end_of_storage = nullptr;

private:
    void destroy(value_type &element){
        element.~value_type();          // destroy an element by its destructor
    }

};

/**
 * Create a vector of size n
 * @tparam value_type
 * @param size
 */
template<typename value_type>
S_Vector<value_type>::S_Vector(size_t n) {
    if(n == 0) return;
    start = new value_type[n];
    if(start == nullptr) {
        throw std::bad_alloc();     // alloc failed, throw a bad_alloc exception
    }
    finish = start + n;             // success
    end_of_storage = start + n;
}

/**
 * Create a vector of size n. initialize with the value.
 * @tparam value_type
 * @param size
 * @param value
 */
template <typename value_type>
S_Vector<value_type>::S_Vector(size_t n, value_type value) : S_Vector(n){
    if(start != nullptr) {
        for(auto it = start; it != finish; it++)   // fill with specified value
            *it = value;
    }
}

template<typename value_type>
S_Vector<value_type>::S_Vector(S_Vector &x) {
    size_t alloc_size = x.end_of_storage - x.start;
    start = new value_type[alloc_size];     // alloc new memory
    if(start != nullptr){
        auto it_new = start;
        for(auto it = x.start; it != x.finish; it++){
            *it_new = *it;
            it_new ++;
        }
        finish = start + x.size();
        end_of_storage = start + alloc_size;
    }
    else throw std::bad_alloc();   // alloc failed, throw a bad_alloc exception
}

template<typename value_type>
void S_Vector<value_type>::reserve(const size_t &new_capacity) {
    if(new_capacity <= (finish - start)) return;
    auto * temp = new(std::nothrow) value_type[new_capacity];
    if(temp == nullptr)
        throw std::bad_alloc();   // alloc failed, throw a bad_alloc exception
    size_t i = 0;
    for(auto it = start; it != finish; it++) {  // copy data
        *(temp + i) = *it;
        ++i;
    }
    finish = temp + (finish - start);  // calculate new iterator value: base + n
    delete[] start;                    // free old
    start = temp;                      // update new
    temp = nullptr;
    end_of_storage = start + new_capacity;
}

template<typename value_type>
void S_Vector<value_type>::resize(size_t new_size) {
    if(new_size > capacity()){   //checks whether the capacity is enough.
        reserve(new_size);
    }
    finish = start + new_size;
}

template<typename value_type>
void S_Vector<value_type>::resize(size_t new_size, value_type value) {
    if(new_size > capacity()){   //checks whether the capacity is enough.
        reserve(new_size);
    }
    for(auto it = finish; (it-start) < new_size; ++it){
        *it = value;             // fill with setting value
    }
}

template<typename value_type>
S_Vector<value_type> &S_Vector<value_type>::operator=(const S_Vector<value_type> &x) {
    if(this == &x) return *this;
    this->clear();
    if(start!= nullptr) delete[] start;                // release old memory
    auto alloc_size = x.end_of_storage - x.start;      // same as x.capacity()
    start = new value_type[alloc_size];                // alloc new memory
    if(start != nullptr){
        finish = start;
        for(auto it = x.start; it<x.finish; ++it){     //copy data
            *finish = *it;
            finish ++;
        }
        end_of_storage = start + alloc_size;
    }
    else throw std::bad_alloc();   // alloc failed, throw a bad_alloc exception
    return *this;
}

template<typename value_type>
S_Vector<value_type> &S_Vector<value_type>::operator=(S_Vector<value_type> &&x) noexcept {
    if(this == &x) return *this;
    this->clear();
    if(start!= nullptr) delete[] start;                  // free old memory
    auto alloc_size = x.end_of_storage - x.start;
    start = new(std::nothrow) value_type[x.v_capacity];  // alloc new memory
    if(start != nullptr){
        start = finish = start;
        for(auto it = x.start; it<x.finish; ++it){       //copy data
            *finish = *it;
            finish ++;
        }
    }
    end_of_storage = start + alloc_size;
    return *this;
}

template<typename value_type>
value_type &S_Vector<value_type>::operator[](const size_t pos) {
    if(pos < (finish - start)) return *(start + pos);
    else{
        throw std::range_error("A cross-border access occurred.\r\nyour input pos exceeded the max_size.\r\n");
    }
}

template<typename value_type>
const value_type &S_Vector<value_type>::operator[](size_t pos) const {
    if(pos < (finish - start)) return *(start + pos);
    else{
        throw std::range_error("A cross-border access occurred.\r\nyour input pos exceeded the max_size.\r\n");
    }
}

template <typename value_type>
size_t S_Vector<value_type>::length() {
    return (finish - start);
}

template <typename value_type>
size_t S_Vector<value_type>::size() {
    return (finish - start);
}

template <typename value_type>
size_t S_Vector<value_type>::capacity() {
    return (end_of_storage - start);
}

template<typename value_type>
void S_Vector<value_type>::push_back(const value_type &value) {
    if(finish == end_of_storage) {                        // dynamic capacity adjustment
        reserve(size() == 0 ? 1 : size()*2);
    }
    *finish = value;
    finish ++;
}

template<typename value_type>
void S_Vector<value_type>::pop_back() {
    // destroy
    // How to destroy an object actively
    // when using template class (the type of "value_type" always cannot be known)
    destroy(*(finish-1));
    if(finish != start) finish --;    // remove last elements
}

template<typename value_type>
typename S_Vector<value_type>::iterator S_Vector<value_type>::insert(const iterator &pos, const value_type &value) {
    return insert(pos,1,value);
}

template<typename value_type>
typename S_Vector<value_type>::iterator S_Vector<value_type>::insert(const iterator &pos, const size_t &n, const value_type &value) {
    if((capacity() == 0 && pos > 0) || (pos > finish)) return nullptr;    // insert failed
    if(finish + n > end_of_storage){
        size_t new_capacity = (size()+n)*2;              // double size
        auto temp = new value_type[new_capacity];        // realloc
        if(temp == nullptr) throw std::bad_alloc();      // throw exception
        auto it_new = temp;
        auto it_old = start;
        for(; it_old < pos; ++it_old){                   // step1: copy elements before pos
            *it_new = it_old;
            it_new ++;
        }
        auto pos_new = it_new;                           // step2: fill n elements(followed)
        for(size_t i = 0; i < n; ++i){
            *it_new = value;
            it_new ++;
        }
        for(; it_old < finish; ++it_old){                // step3: copy elements after(include) pos
            *it_new = it_old;
            it_new ++;
        }
        if(start != nullptr)                       // Free original memory
            delete[] start;
        finish = temp + (finish - start) + n;
        start = temp;                              // new ptr
        temp = nullptr;
        return pos_new;
    }
    else{
        auto it = finish > start ? finish - 1 : pos-1;
        for(; it >= pos; it --){                    // step1: moves elements after(include) pos by n bits
            *(it+n) = *it;
        }
        for(size_t count = n; count >= 0; count--){ // step2: fill n elements
            it++;
            *it = value;
        }
        return pos;
    }

}

template<typename value_type>
value_type S_Vector<value_type>::at(const iterator &pos) {
    if(pos < finish)
        return *pos;
    else
        throw std::range_error("A cross-border access occurred.\r\nyour input pos exceeded the max_size.\r\n");
}

template<typename value_type>
typename S_Vector<value_type>::iterator S_Vector<value_type>::erase(const iterator &start_pos, const iterator &end_pos) {
    auto it_a = start_pos, it_b = end_pos;
    if(it_b > finish) it_b = finish;
    auto res = it_b;
    for(; (it_b+1) < finish; it_b++){   // moves forward data after end_pos to start_pos
        destroy(*it_a);             // destroy
        *it_a = *(it_b+1);
        it_a ++;
    }
    finish = it_a;      // update
    return res;
}

template<typename value_type>
typename S_Vector<value_type>::iterator S_Vector<value_type>::erase(const iterator &pos) {
    auto it_a = pos;
    if(it_a > finish) it_a = finish;
    auto res = it_a;
    for(; (it_a+1) < finish; it_a++){   // moves forward data after pos
        destroy(*it_a);             // destroy
        *it_a = *(it_a+1);
    }
    finish = it_a;
    return res;
}

template<typename value_type>
void S_Vector<value_type>::clear() {
    for(auto it = start; it != finish; it++){
        destroy(*it);
    }
    // destroy ???
    finish = start;
}

template<typename value_type>
S_Vector<value_type>::~S_Vector() {
    clear();
    if(start != nullptr)
        delete[] start;
}

#endif //S_VECTOR_S_VECTOR_H
