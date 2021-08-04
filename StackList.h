//
// Created by dmitry on 23.07.2021.
//

#ifndef UNTITLED_STACKLIST_H
#define UNTITLED_STACKLIST_H

template<class T>
struct StackItem {
    StackItem *prev;
    T item;
};

template<class T>
class StackList {
public:
    StackItem<T> *top;

    StackList();

    ~StackList();

    void push(T item);

    T pop();

};


template<class T>
StackList<T>::StackList() {
    top = nullptr;
}

template<class T>
T StackList<T>::pop() {
    if (!top) return nullptr;
    auto item = top->item;
    auto toDelete = top;
    top = top->prev;
    delete toDelete;
    return item;
}

template<class T>
void StackList<T>::push(T item) {
    auto topPrev = top;
    top = new StackItem<T>;
    top->prev = topPrev;
    top->item = item;
}


template<class T>
StackList<T>::~StackList() {
    while (top) {
        auto toDelete = top;
        top = top->prev;
        delete toDelete;
    }
}

#endif //UNTITLED_STACKLIST_H
