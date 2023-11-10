#ifndef INCLUDED_linked_list_hpp
#define INCLUDED_linked_list_hpp

#include <cstddef>
#include <ostream>

namespace hello {
    template <typename T> class LinkedList {
    private:
        struct Node {
            Node* next;
            T value;
        };

    public:
        template <typename NodeType> class Iterator {
        public:
            Iterator(NodeType* p_ptr) : m_ptr(p_ptr) {}

            auto operator++() -> Iterator {
                NodeType* new_ptr = m_ptr->next;
                m_ptr = new_ptr;
                return *this;
            }

            auto operator++(int) -> Iterator {
                NodeType* old_ptr = m_ptr;
                m_ptr = old_ptr->next;
                return Iterator{old_ptr};
            }

            auto operator!=(Iterator other) -> bool {
                return other.m_ptr != m_ptr;
            }

            auto operator*() -> T {
                return m_ptr->value;
            }

        private:
            NodeType* m_ptr;
        };

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

        auto remove(size_t position) -> void {
            Node* current = m_first, previous = nullptr;

            for (size_t i = 0; i < position; i++) {
                Node* next = current->next;
                previous = current;
                current = next;
            }

            // Now, current should point to the target Node.

            Node* next = current->next;
            delete current;
            previous->next = next;
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

        auto begin() -> Iterator<Node> {
            return Iterator<Node>{m_first};
        }

        auto end() -> Iterator<Node> {
            return Iterator<Node>{nullptr};
        }

        auto cbegin() const -> Iterator<const Node> {
            return Iterator<const Node>{m_first};
        }

        auto cend() const -> Iterator<const Node> {
            return Iterator<const Node>{nullptr};
        }

        auto begin() const -> Iterator<const Node> {
            return cbegin();
        }

        auto end() const -> Iterator<const Node> {
            return cend();
        }
        
    private:
        // The first node.
        Node* m_first;
    };
}

template<typename T> auto operator<<(std::ostream& stream, const hello::LinkedList<T>& list) -> std::ostream& {
    stream << "[";
    const auto list_len = list.size();
    size_t i = 0;
    for (const auto item : list) {
        stream << item;

        if (i != list_len - 1) {
            stream << ", ";
        }

        i++;
    }
    stream << "]";

    return stream;
}

#endif
