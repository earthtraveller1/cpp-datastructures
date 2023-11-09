#ifndef INCLUDED_linked_list_hpp
#define INCLUDED_linked_list_hpp

#include <cstddef>
#include <ostream>

namespace hello {
    template <typename T> class LinkedList {
    public:
        LinkedList() : m_first{} {}

        LinkedList(std::initializer_list<T> init_list)
            : m_first{} 
        {
            for (const auto& element : init_list) {
                append(element);
            }
        }

        auto insert(size_t position, T value) -> void {
            Node* current = m_first;

            if (current == nullptr && position == 0) {
                m_first = new Node{};
                m_first->value = value;

                return;
            }

            for (size_t i = 0; i < position; i++) {
                Node* next = current->next;
                current = next;
            }

            Node* new_node = new Node{};
            new_node->next = current->next;
            current->next = new_node;
            new_node->value = value;
        }

        auto append(T value) -> void {
            if (size() == 0) {
                insert(0, value);
            } else {
                insert(size() - 1, value);
            }
        }

        auto size() const -> size_t {
            size_t size = 0;
            const Node* current = m_first;

            while (current != nullptr) {
                size++;
                
                Node* next = current->next;
                current = next;
            }

            return size;
        }

        auto operator[](size_t index) -> T& {
            Node* current = m_first;

            for (size_t i = 0; i < index; i++) {
                Node* next = current->next;
                current = next;
            }

            return current->value;
        }

        auto operator[](size_t index) const -> const T& {
            const Node* current = m_first;

            for (size_t i = 0; i < index; i++) {
                const Node* next = current->next;
                current = next;
            }

            return current->value;
        }
        
    private:
        struct Node {
            Node* next;
            T value;
        };

        // The first node.
        Node* m_first;
    };
}

template<typename T> auto operator<<(std::ostream& stream, const hello::LinkedList<T> list) -> std::ostream& {
    stream << "[";
    const auto list_len = list.size();
    for (size_t i = 0; i < list_len; i++) {
        stream << list[i];

        if (i != list_len - 1) {
            stream << ", ";
        }
    }
    stream << "]";

    return stream;
}

#endif
