#ifndef INCLUDED_vector_hpp
#define INCLUDED_vector_hpp

#include <cstddef>
#include <initializer_list>
#include <iostream>

namespace hello {
    template<typename T> class Vector {
    public:
        Vector()
            : m_capacity(0),
              m_len(0),
              m_ptr(nullptr) {};

        Vector(size_t capacity)
            : m_capacity(capacity),
              m_len(0),
              m_ptr(new T[m_capacity])
        {}

        Vector(std::initializer_list<T> list) {
            m_capacity = list.size();
            m_len = list.size();

            m_ptr = new T[m_capacity];

            size_t i = 0;
            auto list_element = list.begin();

            while (list_element != list.end()) {
                m_ptr[i] = *list_element;
                
                i++;
                list_element++;
            }
        } 

        Vector(const Vector&) = delete;
        Vector& operator=(const Vector&) = delete;

        Vector(Vector&& rhs):
            m_capacity(rhs.m_capacity),
            m_len(rhs.m_len),
            m_ptr(rhs.m_ptr)
        {
            rhs.m_capacity = 0;
            rhs.m_len = 0;
            rhs.m_ptr = nullptr;
        }

        Vector& operator=(Vector&& rhs) {
            if (m_capacity == 1)
                delete m_ptr;
            else
                delete[] m_ptr;

            m_ptr = rhs.m_ptr;
            m_len = rhs.m_len;
            m_capacity = rhs.m_capacity;

            rhs.m_ptr = nullptr;
            rhs.m_len = 0;
            rhs.m_capacity = 0;

            return *this;
        }

        auto append(int element) {
            if (m_len == 0 || m_ptr == nullptr) {
                m_capacity = 2;
                m_ptr = new T[m_capacity];
                m_ptr[0] = element;
                m_len = 1;
            } else {
                m_len += 1;
                if (m_len >= m_capacity)
                {
                    m_capacity += m_capacity / 2;
                    int* new_ptr = new T[m_capacity];

                    const size_t old_len = m_len - 1;
                    for (size_t i = 0; i < old_len; i++) {
                        new_ptr[i] = m_ptr[i];
                    }

                    delete[] m_ptr;
                    m_ptr = new_ptr;
                }

                m_ptr[m_len - 1] = element;
            }
        }

        auto len() const -> size_t {
            return m_len;
        }

        auto operator[](size_t index) -> T& {
            return m_ptr[index];
        }

        auto operator[](size_t index) const -> const T& {
            return m_ptr[index];
        }

        auto begin() -> T* {
            return m_ptr;
        }

        auto end() -> T* {
            return m_ptr + m_len;
        }

        auto begin() const -> const T* {
            return m_ptr;
        }

        auto end() const -> const T* {
            return m_ptr + m_len;
        }

        auto cbegin() const -> const T* {
            return m_ptr;
        }

        auto cend() const -> const T* {
            return m_ptr + m_len;
        }

    private:
        size_t m_capacity;
        size_t m_len;
        T* m_ptr;
    };
}

template<typename T> auto operator<<(std::ostream& stream, const hello::Vector<T>& vector) -> std::ostream& {
    stream << "[";
    for (size_t i = 0; i < vector.len(); i++) {
        stream << vector[i];

        if (i != vector.len() - 1) {
            stream << ", ";
        }
    }
    stream << "]";

    return stream;
}

#endif
