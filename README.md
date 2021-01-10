# S_Vector Class
A simple implementation of vector class.

[Quick Start & Usage](#Quick-Start--Usage)

[Member Functions](#Member-Functions)

[Log](#Update-Log)

---

## Quick Start & Usage

### Func test

- Show the S_Vector basic functions.
- Cmake version: v3.17.
```shell
$ git clone https://github.com/GhostWarlock/S_Vector
$ cd S_Vector
$ mkdir build
$ cd build
$ cmake ..
$ ./S_Vector
```

### Usage

- copy the **S_Vector.h**(Path: S_Vector/S_Vector.h) to you project. include S_Vector.h in source file.
- See also C++ Reference: [***std::vector***](http://www.cplusplus.com/reference/vector/)

```c++
#include "S_Vector.h"
...


int main (void){
    S_Vector<int> i_vector;            // NULL
    S_Vector<std::string> str_vector;
    S_Vector<std::string> str_vector(10,"initial value");
    ...
    
    return 0;
}
```

## Member Functions

S_Vector Class is a simple implementation of **C++11 std::vector**, the use of basic functions is same as std::vector. See C++ Reference: [***std::vector***](http://www.cplusplus.com/reference/vector)

### S_Vector::S_Vector

- **S_Vector()**
- **explicit S_Vector(unsigned int size)**
- **S_Vector(unsigned int size, data_type value)**
- **S_Vector(S_Vector &x)**

### S_Vector::reserve

- **bool reserve(const unsigned int new_capacity)**

### S_Vector::resize

- **int resize(unsigned int new_size)**
- **int resize(unsigned int new_size, data_type value)**

### S_Vector::operator=

- **S_Vector<data_type> &operator=(const S_Vector<data_type> &x)**
- **S_Vector<data_type> &operator=(S_Vector<data_type> &&x) noexcept**

### S_Vector::operator[]

- **data_type& operator[] (unsigned int pos)**
- **const data_type& operator[] (unsigned int pos) const**

### S_Vector::size

- **int size()**

### S_Vector::length

- **int length()**

### S_Vector::capacity

- **int capacity()**

### S_Vector::pop_back

- **int pop_back()**

### S_Vector::push_back

- **int push_back(const data_type &value)**

### S_Vector::insert

- **int insert(const unsigned int &pos, const data_type &value)**
- **int insert(const unsigned int &pos, const unsigned int &n, const data_type &value)**


### S_Vector::at

- **data_type at(unsigned int pos)**

### S_Vector::begin

- **int begin()**

### S_Vector::end

- **int end()**

### S_Vector::erase

- **unsigned int erase(const unsigned int &pos)**
- **unsigned int erase(const unsigned int &start_pos, const unsigned int &end_pos)**


### S_Vector::clear

- **unsigned int erase(const unsigned int &start_pos, const unsigned int &end_pos)**

### S_Vector::swap
- **Waiting for update.**

### S_Vector::shrink_to_fit
- **Waiting for update.**

### S_Vector::empty
- **Waiting for update.**

### S_Vector::~S_Vector
- **~S_Vector()**

---
## Update Log

- Version: V1.0.&nbsp;&nbsp;&nbsp;&nbsp;*2021/01/10*









