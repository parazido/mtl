#pragma once

namespace mtl {
    template <class t_type, class t_size_type> struct memory_area {
        using type = t_type;
        using size_type = t_size_type;

        memory_area() = default;

        memory_area(const memory_area &other) {
            data = other.data;
            size = other.size;
        };

        memory_area(type *data_, size_type size_) : data(data_), size(size_) {}

        bool operator==(const memory_area &other) { return data == other.data && size == other.size; }

        type *data;
        size_type size;
    };
} // namespace mtl
