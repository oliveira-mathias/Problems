#include <iostream>
#include <queue>
#include <utility>

using namespace std;

class Shelter {
  queue<pair<int, int>> dogQueue;
  queue<pair<int, int>> catQueue;
  int time;

  public:
  Shelter() : time(0) {}

  void enqueue(bool isDog, int id) {
    if(isDog) {
      dogQueue.push({time++, id});
    }
    else {
      catQueue.push({time++, id});
    }
  }

  int dequeueAny() {
    if(dogQueue.empty() && catQueue.empty()) {
      throw "Invalid Dequeue Any";
    }

    const auto [dogTime, dogId] = (dogQueue.empty()) ? make_pair(numeric_limits<int>::max(), -1) : dogQueue.front();

    const auto [catTime, catId] = (catQueue.empty()) ? make_pair(numeric_limits<int>::max(), -1) : catQueue.front();

    if(dogTime < catTime) {
      dogQueue.pop();
      return dogId;
    }
    else {
      catQueue.pop();
      return catId;
    }

  }

  int dequeueCat() {
    if(catQueue.empty()) {
      throw "Invalid Dequeue Cat";
    }

    const auto [_, catId] = catQueue.front();
    catQueue.pop();

    return catId;
  }
  
  int dequeueDog() {
    if(dogQueue.empty()) {
      throw "Invalid Dequeue Dog";
    }

    const auto [_, dogId] = dogQueue.front();
    dogQueue.pop();

    return dogId;
  }
};
