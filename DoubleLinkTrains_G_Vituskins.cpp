#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Node {
public:
    T value;
    Node* pPrev;
    Node* pNext;

    Node(T value) {
        this->value = value;
        this->pPrev = nullptr;
        this->pNext = nullptr;
    }
};



template<typename T>
class List {
protected:
    int size;
    Node<T>* first;
    Node<T>* last;

    bool isEmpty() {
        return first == nullptr;
    }

    void deleteAll() {
        Node<T>* temp = first;
        Node<T>* temp1 = nullptr;
        for (int i = 0; i < size; i++) {
            temp1 = temp;
            temp = temp->pNext;
            delete temp1;
        }
    }

public:
    List() {
        size = 0;
        first = nullptr;
        last = nullptr;
    }

    ~List() {
        deleteAll();
    }

    void push(T value) {
        Node<T>* temp = new Node<T>(value);

        if (isEmpty()) {
            first = temp;
            last = temp;
        }
        else {
            temp->pPrev = last;
            last->pNext = temp;
            last = temp;
        }
        size++;
    }

    void printListFromBegin() {
        if (isEmpty()) {
            cout << "List is empty";
        }
        else {
            Node<T>* temp = first;
            while (temp != nullptr) {
                cout << temp->value << " ";
                temp = temp->pNext;
            }
            cout << "\n";
        }
    }

    void printListFromEnd() {
        if (isEmpty()) {
            cout << "List is empty";
        }
        else {
            Node<T>* temp = last;
            while (temp != nullptr) {
                cout << temp->value << " ";
                temp = temp->pPrev;
            }
            cout << "\n";
        }
    }

    void remove(int index) {
        if (isEmpty()) {
            return;
        } else if (index == 0) {
            removeFirst();
        } else if (index == size - 1) {
            removeLast();
        } else {
            if (index < size / 2) {
                removeFromStart(index);
            } else {
                removeFromEnd(index);
            }
        }
    }

    void removeFromStart(int index) {
        Node<T>* temp = first;
        for (int i = 0; i < index; i++) {
            temp = temp->pNext;
        }
        temp->pPrev->pNext = temp->pNext;
        temp->pNext->pPrev = temp->pPrev;
        size--;
        delete temp;
    }

    void removeFromEnd(int index) {
        Node<T>* temp = last;
        for (int i = 0; i < size - index - 1; i++) {
            temp = temp->pPrev;
        }
        temp->pPrev->pNext = temp->pNext;
        temp->pNext->pPrev = temp->pPrev;
        size--;
        delete temp;
    }

    void removeFirst() {
        if (isEmpty()) {
            return;
        }
        Node<T>* temp = first;
        first = temp->pNext;
        first->pPrev = nullptr;
        size--;
        delete temp;
    }

    void removeLast() {
        if (isEmpty()) {
            return;
        }
        Node<T>* temp = last;
        last = temp->pPrev;
        last->pNext = nullptr;
        size--;
        delete temp;
    }

    int getSize() {
        return size;
    }
};

template<typename T>
class TrainStation: public List<T> {
private:
    Node<T>* current;
    bool forward;

    T nextStation() {
        current = current->pNext;
        return current->value;
    }

    T prevStation() {
        current = current->pPrev;
        return current->value;
    }
public:

    TrainStation() {
        this->current = nullptr;
        this->forward = true;
    }

    void next() {
        if (current == nullptr) {
            current = this->first;
            cout << current->value << endl;
        } else if (forward) {
            cout << nextStation() << endl;
            if (current->pNext == nullptr)
                forward = false;
        } else if (!forward) {
            cout << prevStation() << endl;
            if (current->pPrev == nullptr)
                forward = true;
        }
    }

    void resetCurrent() {
        current = nullptr;
    }
};


void printConditions() {
    cout << "write \"1\" to run the train to the next station\n";
    cout << "write \"2\" to exit\n";
}


int main() {

    int numOfStations;
    bool programLoop = true;
    int click;
    string station;

    TrainStation<string> train;

    cout << "Enter number of stations\n";
    cin >> numOfStations;
    for (int i = 0; i < numOfStations; i++) {
        cout << "Input " << i + 1 << ". station: \n";
        cin >> station;
        train.push(station);
    }

    printConditions();
    while (programLoop) {
        cin >> click;
        switch (click) {
            case 2:
                programLoop = false;
                break;
            case 1:
                train.next();
                break;
        }
    }
    system("pause");
}