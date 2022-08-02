#pragma once

#include <cstddef>
#include <mtl/buffers/common.hpp>
#include <mtl/traits/types.hpp>



namespace mtl::buffers {
	template<class t_element_type, size_t v_buffer_size>
	class ring_buffer {
	public:
		constexpr static size_t buffer_size = v_buffer_size;
		using element_type = t_element_type;
		using size_type = typename mtl::traits::types::pick<mtl::traits::typesp::min_integral_for_value<buffer_size>>::type;
		using memory_area = mtl::memory_area<element_type, size_type>;

		bool empty() const {
			return m_head == m_tail;
		}

		bool full() const {
			return m_tail == recycle_pointer(m_head + 1);
		}

		size_type size() const {
			element_type *head = m_head;
			element_type *tail = m_tail;

			if (head >= tail) {
				return head - tail;
			} else {
				return full_size() + 1 + head - tail;
			}
		}

		size_type empty_size() const {
			return full_size() - size();
		}

		constexpr size_type full_size() const {
			return buffer_size;
		}

		void clear() {
			m_head = m_tail = m_buffer;
		}

		size_type push(const element_type& element) {
			if (full()) {
				return 0;
			}
			*m_head = element;
			m_head = recycle_pointer(m_head + 1);
			return 1;
		}

		size_type pop(element_type &element) {
			if (empty()) {
				return 0;
			}

			element = *m_tail;
			m_tail = recycle_pointer(m_tail + 1);
			return 1;
		} 

		size_type write(element_type *data, size_type size) {
			size_type elements_written;
			for (elements_written = 0; elements_written < size && push(*data++); ++elements_written) {}
			return elements_written;
		}

		size_type read(element_type *data, size_type size) {
			size_type elements_read;
			for (elements_read = 0; elements_read < size && pop(*data++); ++elements_read) {}
			return elements_read;
		}

		memory_area allocate_chunk_for_external_write() {
			element_type *tail = m_tail;
			element_type *head = m_head;

			if (head >= tail) {
				if (tail == m_buffer) {
					return {head, static_cast<size_type>(m_buffer + full_size() - head)};
				} 
				return {head, static_cast<size_type>(m_buffer + full_size() + 1 - head)};
			}

			return {head, static_cast<size_type>(tail - head - 1)};
		}

		void commit_chunk_after_external_write(const memory_area& area) {
			m_head = recycle_pointer(area.data + area.size);
		}

		memory_area use_chunk_for_external_read() const {
			element_type *tail = m_tail;
			element_type *head = m_head;
			
			if (tail <= head) {
				return {tail, static_cast<size_type>(head - tail)};
			}

			return {tail, static_cast<size_type>(m_buffer + full_size() - tail + 1)};
		}

		void skip_chunk_after_external_read(const memory_area& area) {
			m_tail = recycle_pointer(area.data + area.size);
		}

	private:
		inline element_type *recycle_pointer(element_type *element) {
			if (element <= m_buffer + full_size()) {
				return element;
			}
			return m_buffer;
		}

		inline const element_type *recycle_pointer(const element_type *element) const {
			if (element <= m_buffer + full_size()) {
				return element;
			}
			return m_buffer;
		}

	private:
		element_type *m_head = m_buffer;
		element_type *m_tail = m_buffer;
		element_type m_buffer[buffer_size + 1];
	};
}
