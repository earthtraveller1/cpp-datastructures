#include <iostream>

#include <earthtraveller1/linked-list.hpp>

using hello::LinkedList;

auto main(int argc, const char* const* argv) -> int {
    LinkedList<int> list{1, 2, 3, 4, 5};
    list.append(6);
    list.append(7);
    list.insert(2, 8);
    list.insert(0, 9);

    list.remove(4);

    std::cout << "My List: " << list << std::endl;
}

