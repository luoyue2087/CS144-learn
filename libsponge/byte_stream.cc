#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : m_capacity(capacity), m_deq(deque<char>()), m_input_ended(false), m_bytes_written(0), m_bytes_read(0) {}

size_t ByteStream::write(const string &data) {
    size_t minLen = min(data.size(), m_capacity - m_deq.size());
    for (string::size_type i = 0; i < minLen; ++i)
        m_deq.push_back(data[i]);
    m_bytes_written += minLen;
    return minLen;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t minLen = min(len, m_deq.size());
    return string().assign(m_deq.begin(), m_deq.begin() + minLen);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t minLen = min(len, m_deq.size());
    m_bytes_read += minLen;
    while (minLen > 0) {
        m_deq.pop_front();
        --minLen;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    size_t minLen = min(len, m_deq.size());
    m_bytes_read += minLen;
    return string().assign(m_deq.begin(), m_deq.begin() + minLen);
}

void ByteStream::end_input() { m_input_ended = true; }

// `true` if the stream input has ended
bool ByteStream::input_ended() const { return m_input_ended; }

size_t ByteStream::buffer_size() const { return m_deq.size(); }

bool ByteStream::buffer_empty() const { return m_deq.empty(); }

// `true` if the output has reached the ending
bool ByteStream::eof() const { return buffer_empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return m_bytes_written; }

size_t ByteStream::bytes_read() const { return m_bytes_read; }

size_t ByteStream::remaining_capacity() const { return m_capacity-m_deq.size(); }