
#ifndef STACK_H
#define STACK_H

template<class T>
class Stack {
private:

    template<class D>
    class StackNode {
    public:
        D data;
        StackNode* next;

        StackNode(D data, StackNode* next) {
            this->data = data;
            this->next = next;
        }
    };

public:
    StackNode<T>* _node;
    unsigned int _size;

public:
    Stack();

    int pop(T& obj);
    int operator >> (T& obj);

    void push(T obj);
    void operator << (T obj);

    void reverse();

    unsigned int size();

    void for_each(void (*fn) (T& obj));

    void clear();

    ~Stack();

};

template<class T>
Stack<T>::Stack() {
    _node = nullptr;
    _size = 0;
}

template<class T>
void Stack<T>::operator << (T obj) {
    push(obj);
}

template<class T>
void Stack<T>::push(T obj) {
    StackNode<T>* new_node = new StackNode<T>(obj, this->_node);
    this->_node = new_node;
    _size++;
}

template<class T>
int Stack<T>::operator >> (T& obj) {
    return pop(obj);
}


template<class T>
int Stack<T>::pop(T& obj) {

    StackNode<T>* ret = this->_node;
    if (ret == nullptr) {
        return 0;
    }
    this->_node = this->_node->next;
    _size--;

    obj = ret->data;
    delete ret;

    return 1;

}

template<class T>
void Stack<T>::reverse() {
    T obj;
    Stack<T> s;
    while (pop(obj)) {
        s << obj;
    }
    this->_node = s._node;
}

template<class T>
unsigned int Stack<T>::size() {
    return _size;
}

template<class T>
void Stack<T>::for_each(void (*fn) (T& obj)) {
    StackNode<T>* node_next = this->_node;
    while (node_next) {
        fn(node_next->data);
        node_next = node_next->next;
    }
}

template<class T>
void Stack<T>::clear() {
    StackNode<T>* node_next = this->_node;
    while (node_next) {
        node_next = this->_node->next;
        delete this->_node;
        _size--;
        this->_node = node_next;
    }
}

template<class T>
Stack<T>::~Stack() {
    clear();
}

#endif

