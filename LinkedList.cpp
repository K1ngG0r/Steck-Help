#include <iostream>

template<typename T>
class LinkedList {
private:
    class Node {
    public:
        T value;
        Node* next;
        Node() :value{ 0 }, next{ nullptr } {}
        Node(T value) : value{ value }, next{ nullptr } {}
    };
    Node* first;
    Node* last;
public:
    LinkedList() :first{ nullptr }, last{ nullptr } {}

    LinkedList(const LinkedList& list) : LinkedList()
    {
        Node* current = list._first;
        while (current)
        {
            Push(current->value);
            current = current->next;
        }
    }
    
    ~LinkedList() {
        if (!IsEmpty()) {
            Node* current = first->next;
            while (current != nullptr) {
                delete first;
                first = current;
                current = current->next;
            }
            delete first;
            first = nullptr;
            last = nullptr;
        }
    }

    LinkedList& Push(T value) {
        Node* node = new Node(value);
        if (IsEmpty()) {
            first = node;
            last = node;
            return *this;
        }
        last->next = node;
        last = node;
    }

    bool IsEmpty() const {
        return first == nullptr;
    }

    int Size() {
        int count = 0;
        Node* current = first->next;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }


    friend std::ostream& operator <<(std::ostream& out, const LinkedList& list) {
        if (!list.IsEmpty()) {
            Node* current = list.first;
            while (current != nullptr) {
                out << current->value << '\t';
                current = current->next;
            }
        }
        else
            out << "List is empty" << std::endl;
        return out;
    }

    friend LinkedList& operator+(const LinkedList& one, const LinkedList& two) {
        LinkedList<T> tmp{};
        Node* current_1 = one.first;
        Node* current_2 = two.first;
        while (current_1 != nullptr) {
            tmp.Push(current_1->value);
            current_1 = current_1->next;
        }
        while (current_2 != nullptr) {
            tmp.Push(current_2->value);
            current_2 = current_2->next;
        }
        tmp.last = one.last;
        tmp.last->next = two.first;
        tmp.last = two.last;
        tmp.first = one.first;
        return tmp;
    } 
};

int main()
{
    LinkedList<int> arr;
    LinkedList<int> arra;

    arr.Push(5);
    arr.Push(2);
    arr.Push(3);
    arr.Push(10);
    arr.Push(1);
    std::cout << arr << std::endl;

    arra.Push(1);
    arra.Push(2);
    arra.Push(3);
    arra.Push(4);
    arra.Push(5);
    std::cout << arra << std::endl;

    LinkedList<int> sum = arr + arra;
    std::cout << "happy" << std::endl;
    std::cout << sum << std::endl;
}