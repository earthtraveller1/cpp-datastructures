/* This file contains basically an implementation of the dynamic array in modern C++. It is written
 * to target C++20, so yeah. */

#include <algorithm>
#include <cstddef>
#include <initializer_list>

namespace earthtraveller1
{
template <typename T> class DynamicArray
{
  public:
    // Default constructor creates an empty array.
    DynamicArray() = default;

    // Creates an array with a specific capacity.
    explicit DynamicArray(size_t p_capacity) : m_length(0), m_capacity(p_capacity), m_ptr(new T[p_capacity]) {}

    // Creates an array from an initializer list.
    DynamicArray(std::initializer_list<T> p_init_list)
        : m_length(p_init_list.size()), m_capacity(p_init_list.size()), m_ptr(new T[m_capacity])
    {
        size_t i = 0;
        for (auto& item : p_init_list)
        {
            m_ptr[i] = std::move(item);
            i++;
        }
    }

    // Copy constructor
    DynamicArray(const DynamicArray<T>& source) : m_length(source.m_length), m_capacity(source.m_capacity), m_ptr(new T[m_capacity])
    {
        for (size_t i = 0; i < m_length; i++)
        {
            m_ptr[i] = source.m_ptr[i];
        }
    }

    // Move constructor
    DynamicArray(DynamicArray<T>&& source) : m_length(source.m_length), m_capacity(source.m_capacity), m_ptr(source.m_ptr)
    {
        // Reset the source members, because ownership has been moved!
        source.m_length = 0;
        source.m_capacity = 0;
        source.m_ptr = nullptr;
    }

    // Copy assignment operator
    auto operator=(const DynamicArray<T>& source) -> DynamicArray<T>&
    {
        // Copy and swap idiom
        DynamicArray<T> copy = source;

        std::swap(copy.m_length, m_length);
        std::swap(copy.m_capacim_capacity);
        std::swap(copy.m_ptr, m_ptr);

        return *this;
    }

    // Move assignment operator
    auto operator=(DynamicArray<T>&& source) -> DynamicArray<T>&
    {
        // Get rid of the old data first.
        delete[] m_ptr;

        m_length = source.m_length;
        m_capacity = source.m_capacity;
        m_ptr = source.m_ptr;

        // Reset the source members, because ownership has been moved.
        source.m_length = 0;
        source.m_capacity = 0;
        source.m_ptr = nullptr;
    }

    // Push an element to the end of the array.
    auto append(const T& item) -> void
    {
        if (m_capacity == 0)
        {
            m_capacity = 1;
            m_length = 1;

            m_ptr = new T[m_capacity];

            m_ptr[0] = item;

            return;
        }

        // If there isn't enough space, reallocate.
        if (m_length == m_capacity)
        {
            m_capacity *= 2;
            const auto new_ptr = new T[m_capacity];

            // Copy old data over to the new buffer.
            for (size_t i = 0; i < m_length; i++)
            {
                new_ptr[i] = m_ptr[i];
            }

            delete[] m_ptr;
            m_ptr = new_ptr;
        }

        m_ptr[m_length++] = item;
    }

    // Removes the last item from the array and returns it.
    auto pop() -> T
    {
        return m_ptr[--m_length];
    }

    auto operator[](size_t p_index) -> T&
    {
        if (p_index >= m_length)
        {
            throw std::out_of_range("Array index out of bounds!");
        }

        return m_ptr[p_index];
    }

    auto operator[](size_t p_index) const -> const T&
    {
        if (p_index >= m_length)
        {
            throw std::out_of_range("Array index out of bounds!");
        }

        return m_ptr[p_index];
    }

    // Destructor
    virtual ~DynamicArray() { delete[] m_ptr; }

  private:
    // The length of the array. Basically, how many valid elements are in the array.
    size_t m_length;

    // The capacity of the array. Basically, how many elements can be stored in the array.
    size_t m_capacity;

    // The actual pointer to the array on the heap.
    T* m_ptr;
};
} // namespace earthtraveller1
