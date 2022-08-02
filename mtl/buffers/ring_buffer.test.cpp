#include <cstdint>
#include <type_traits>

#include <mtl/buffers/ring_buffer.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Zero length buffer has valid behaviour.") {
    std::byte value;
    mtl::buffers::ring_buffer<std::byte, 0> buffer;
    
    CHECK(buffer.empty());
    CHECK(buffer.full());
    CHECK(buffer.size() == 0);
    CHECK(buffer.empty_size() == 0);
    CHECK(buffer.full_size() == 0);
    CHECK(buffer.pop(value) == 0);
    CHECK(buffer.push(value) == 0);
    CHECK(buffer.read(&value, 1) == 0);
    CHECK(buffer.write(&value, 1) == 0);
}

TEST_CASE("Buffer with one element has valid behaviour.") {
    std::byte value;
    mtl::buffers::ring_buffer<std::byte, 1> buffer;
    
    // Check initial.
    CHECK(buffer.empty());
    CHECK_FALSE(buffer.full());
    CHECK(buffer.size() == 0);
    CHECK(buffer.empty_size() == 1);
    CHECK(buffer.full_size() == 1);
    // Try to pop empty.
    CHECK(buffer.pop(value) == 0);
    CHECK(buffer.empty());
    CHECK_FALSE(buffer.full());
    CHECK(buffer.size() == 0);
    CHECK(buffer.empty_size() == 1);
    // Push/check.
    CHECK(buffer.push(static_cast<std::byte>(0x77)) == 1);
    CHECK_FALSE(buffer.empty());
    CHECK(buffer.full());
    CHECK(buffer.size() == 1);
    CHECK(buffer.empty_size() == 0);
    // Push to full and check.
    CHECK(buffer.push(value) == 0);
    CHECK_FALSE(buffer.empty());
    CHECK(buffer.full());
    CHECK(buffer.size() == 1);
    CHECK(buffer.empty_size() == 0);
    // Pop and check.
    CHECK(buffer.pop(value) == 1);
    CHECK(value == static_cast<std::byte>(0x77));
    CHECK(buffer.empty());
    CHECK_FALSE(buffer.full());
    CHECK(buffer.size() == 0);
    CHECK(buffer.empty_size() == 1);
    // Read empty and check.
    CHECK(buffer.read(&value, 1) == 0);
    CHECK(buffer.empty());
    CHECK_FALSE(buffer.full());
    CHECK(buffer.size() == 0);
    CHECK(buffer.empty_size() == 1);
    // Write and check.
    CHECK(buffer.write(&value, 1) == 1);
    CHECK_FALSE(buffer.empty());
    CHECK(buffer.full());
    CHECK(buffer.size() == 1);
    CHECK(buffer.empty_size() == 0);
    // Read and check.
    CHECK(buffer.read(&value, 1) == 1);
    CHECK(buffer.empty());
    CHECK_FALSE(buffer.full());
    CHECK(buffer.size() == 0);
    CHECK(buffer.empty_size() == 1);
    // Write 2 elements.
    CHECK(buffer.write(&value, 2) == 1);
    CHECK_FALSE(buffer.empty());
    CHECK(buffer.full());
    CHECK(buffer.size() == 1);
    CHECK(buffer.empty_size() == 0);
    // Read 2 and check.
    CHECK(buffer.read(&value, 2) == 1);
    CHECK(buffer.empty());
    CHECK_FALSE(buffer.full());
    CHECK(buffer.size() == 0);
    CHECK(buffer.empty_size() == 1);
    // External read empty.
    auto area = buffer.use_chunk_for_external_read();
    CHECK(area.size == 0);
    // External write.
    area = buffer.allocate_chunk_for_external_write();
    CHECK(area.size == 1);
    *area.data = static_cast<std::byte>(0xa5);
    buffer.commit_chunk_after_external_write(area);
    CHECK_FALSE(buffer.empty());
    CHECK(buffer.full());
    CHECK(buffer.size() == 1);
    CHECK(buffer.empty_size() == 0);
    // External read.
    area = buffer.use_chunk_for_external_read();
    CHECK(area.size == 1);
    CHECK(*area.data == static_cast<std::byte>(0xa5));
    buffer.skip_chunk_after_external_read(area);
    CHECK(buffer.empty());
    CHECK_FALSE(buffer.full());
    CHECK(buffer.size() == 0);
    CHECK(buffer.empty_size() == 1);
}
