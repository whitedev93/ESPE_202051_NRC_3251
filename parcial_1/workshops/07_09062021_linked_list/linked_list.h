#pragma once
#include <iostream>
#include <functional>
#include "node.h"

template<typename T>
class LinkedList {
    public:
        LinkedList() = default;
        void push_back(const T& value);
        void push_front(const T& value);
        void push_at(const T& value, int index);
        Node<T> *at(int index);
        int size();

        void remove_at(int index);

        void for_each(std::function<void(Node<T>*)> callback);
        void for_each(std::function<void(T)> callback);
        
        void until(std::function<bool(Node<T>*)> callback);
        void until(std::function<bool(T)> callback);

        Node<T>* find(std::function<bool(Node<T>*)> callback);
        Node<T>* find(std::function<bool(T)> callback);

        Node<T>* last();

    private:
        Node<T> *head = nullptr;
        int _size = 0;
};

template<typename T>
void LinkedList<T>::push_back(const T& value) {
    _size++;

    if (head == nullptr) {
        head = new Node<T>(value);
        return;
    }

    Node<T> *last = head;
    Node<T> *node = new Node<T>(value);

    while (last->get_next() != nullptr) {
        last = last->get_next();
    }

    last->set_next(node);
}

template<typename T>
void LinkedList<T>::push_front(const T& value) {
    _size++;

    if (head == nullptr) {
        head = new Node<T>(value);
        return;
    }

    Node<T> *temp = head;
    head = new Node<T>(value);
    head->set_next(temp);
}

template<typename T>
void LinkedList<T>::push_at(const T& value, int index) {
    if (index < 0 || index == _size) {
        throw std::invalid_argument("index out of bounds");
    }

    if (index == 0 || _size == 0) {
        return push_front(value);
    }

    Node<T> *target = at(index);
    Node<T> *previous = at(index - 1);
    Node<T> *node = new Node<T>(value);

    previous->set_next(node);
    node->set_next(target);
    _size++;
}

template<typename T>
Node<T> *LinkedList<T>::at(int index) {
    if (index < 0 || index == _size) {
        throw std::invalid_argument("index out of bounds");
    }

    if (index == 0) {
        return head;
    }

    int current_index = 0;
    Node<T> *last = head;

    while (last->get_next() != nullptr) {
        if (current_index == index) {
            break;
        }

        current_index++;
        last = last->get_next();
    }

    return last;
}

template <typename T>
void LinkedList<T>::remove_at(int index) {
    if (index < 0 || index == _size) {
        throw std::invalid_argument("index out of bounds");
    }
    
    if (index == 0) {
        head = head->get_next();
        delete head;
    } else if (index == _size - 1) {
        Node<T> *node = last();
        Node<T> *previous = at(index - 1);
        
        previous->set_next(nullptr);
        delete node;
    } else {
        Node<T> *current = at(index);
        Node<T> *previous = at(index - 1);
        Node<T> *next = at(index + 1);
        
        previous->set_next(next);
        delete current;
    }
}

template<typename T>
int LinkedList<T>::size() {
    return _size;
}

template<typename T>
void LinkedList<T>::for_each(std::function<void(Node<T>*)> callback) {
    Node<T> *current = head;

    while (current != nullptr) {
        callback(current);
        current = current->get_next();
    }
}

template<typename T>
void LinkedList<T>::until(std::function<bool(Node<T>*)> callback) {
    Node<T> *current = head;

    while (current != nullptr) {
        if (!callback(current)) break;
        current = current->get_next();
    }
}

template<typename T>
void LinkedList<T>::for_each(std::function<void(T)> callback) {
    for_each([&](Node<T> *node) {
        callback(node->get_data());
    });
}

template<typename T>
void LinkedList<T>::until(std::function<bool(T)> callback) {
    until([&](Node<T> *node) {
        return callback(node->get_data());
    });
}

template<typename T>
Node<T> *LinkedList<T>::find(std::function<bool(Node<T>*)> callback) {
    Node<T> *current = head;

    while (current != nullptr) {
        if (callback(current)) {
            return current;
        }

        current = current->get_next();
    }

    return nullptr;
}

template<typename T>
Node<T> *LinkedList<T>::find(std::function<bool(T)> callback) {
    return find([&](Node<T> *node) -> bool {
        return callback(node->get_data());
    });
}

template<typename T>
Node<T> *LinkedList<T>::last() {
    Node<T> *last = head;

    while (last->get_next() != nullptr) {
        last = last->get_next();
    }

    return last;
}