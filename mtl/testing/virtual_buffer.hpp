#pragma once

#include <cstddef>
namespace mtl::debug {
    template <class t_element_type, size_t v_size = 1024> class buffer {
    public:
        using element_type = t_element_type;
        constexpr static size_t buffer_size = v_size;

        bool push(element_type element) {
            m_data[m_head] = element;
            m_head = recycle(++m_head);
            if (m_head == m_tail) {
                throw 0;
            }
        }

        element_type pop() {
            if (m_head == m_tail) {
                throw 0;
            }
            auto element = m_data[m_tail];
            m_tail = recycle(++m_tail);
            return element;
        }

        void clear() {
            m_head = m_tail = 0;
        }

        bool empty() const {
            return m_tail == m_head;
        }

        bool is_same(const element_type *data, size_t size) {
            for (size_t i = 0; i < size; ++i) {
                if (m_data[recycle(m_tail + i)] != data[i] || recycle(m_tail + i) == m_head) {
                    return false;
                }
            }
            return true;
        }

    private:
        size_t recycle(size_t position) {
            return position % buffer_size;
        } 

    private:
        size_t m_head = 0;
        size_t m_tail = 0;
        element_type m_data[buffer_size];
    };
} // namespace mtl::debug
