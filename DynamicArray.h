
#ifndef UNTITLED_DYNAMICARRAY_H
#define UNTITLED_DYNAMICARRAY_H


#include <cstdint>

template<class T>
class DynamicArray {
public:
    uint32_t size{};
    T *data;

    explicit DynamicArray(uint32_t size);
    explicit DynamicArray(char const *msg);

    T &operator[](uint32_t i) {
        return data[i];
    };

    ~DynamicArray();

};

template<class T>
DynamicArray<T>::DynamicArray(uint32_t size) {
    this->size = size;
    data = new T[size];
}

template<class T>
DynamicArray<T>::DynamicArray(char const *msg) {
    size = 0;
    while (*(msg + this->size++) != 0) {}
    data = new T[size];
    for (int i = 0; i<size; i++) *(data + i) = *(msg + i);
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}


#endif //UNTITLED_DYNAMICARRAY_H
