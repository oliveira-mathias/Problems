#include <iostream>

using namespace std;

struct Node {
  bool isDog;
  int id;
  Node* next;
  Node* prev;
  Node* prevOfType;

  Node(bool _isDog, int _id) : isDog(_isDog), id(_id), next(nullptr), prev(nullptr), prevOfType(nullptr) {}

};

// If the order was LIFO
class Shelter {
  Node sentinel;
  Node* catHead;
  Node* dogHead;
  Node* tail;

  public:
  Shelter() : sentinel(false, -1) {
    catHead = &sentinel;
    dogHead = &sentinel;
    tail = &sentinel;
  }

  void enqueue(bool isDog, int id) {
    Node* aux = new Node(isDog, id);

    tail->next = aux;
    aux->prev = tail;

    if(isDog) {
      aux->prevOfType = dogHead;
      dogHead = aux;
    }
    else {
      aux->prevOfType = catHead;
      catHead = aux;
    }

    tail = aux;
  }

  int deuqueAny() {
    if(tail == &sentinel) {
      throw "Invalid Dequeue Any";
    }

    Node* aux = tail;

    // Removing frofm the main chain
    tail = tail->prev;
    tail->next = nullptr;

    // Removing from type chain
    if(aux->isDog) {
      dogHead = dogHead->prevOfType;
    }
    else {
      catHead = catHead->prevOfType;
    }

    int id = aux->id;
    delete aux;

    return id;
  }

  int dequeueDog() {
    if(dogHead == &sentinel) {
      throw "Invalid Dequeue Dog";
    }

    Node* aux = dogHead;
    dogHead = dogHead->prevOfType;

    if(tail == aux) {
      tail = tail->prev;
    }

    aux->prev->next = aux->next;
    if(aux->next) {
      aux->next->prev = aux->prev;
    }

    int id = aux->id;
    delete aux;

    return id;
  }
  
  int dequeueCat() {
    if(catHead == &sentinel) {
      throw "Invalid Dequeue Cat";
    }

    Node* aux = catHead;
    catHead = catHead->prevOfType;

    if(tail == aux) {
      tail = tail->prev;
    }

    aux->prev->next = aux->next;
    if(aux->next) {
      aux->next->prev = aux->prev;
    }

    int id = aux->id;
    delete aux;

    return id;
  }
};
