#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
    : _output(capacity)
    , _capacity(capacity)
    , _first_unread(0)
    , _first_unassembled(0)
    , _idxEOF(capacity + 5)
    , _cnt_substring(0)
    , _substrings(capacity)
    , _st(deque<bool>(capacity, false)) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    size_t true_index = index, true_len = data.size(), data_idx = 0;
    // keep _substrings size is equal to capacity
    while (_substrings.size() < _capacity) {
        _substrings.push_back('\0');
        _st.push_back(false);
    }

    // caclulate index ture pos in StreamReassembler
    if (true_index < _first_unread) {
        true_index = _first_unread;
        if (true_index - index <= true_len)  // if whole data already in _output, then drop this data
            true_len -= (true_index - index);
        else
            return;
        data_idx += (true_index - index);
    }

    size_t in_index = true_index - _first_unread;

    // if (in_index + true_len > _capacity) {
    //     return;
    // }

    // push data into StreamReassembler only the index-data not arrived before

    for (deque<char>::size_type i = 0; i < true_len && in_index + i < _capacity; ++i) {
        if (_st[in_index + i] == false)
            ++_cnt_substring;

        _substrings[in_index + i] = data[data_idx];
        _st[in_index + i] = true;
        ++data_idx;
    }

    // check is eof idx
    if (eof)
        _idxEOF = true_index + true_len;

    // update next glossy index
    if (in_index == _first_unassembled - _first_unread) {
        while (_first_unassembled - _first_unread < _capacity && _st[_first_unassembled - _first_unread] &&
               _first_unassembled - _first_unread < _capacity)
            ++_first_unassembled;
    }

    // output assembled data into streamer
    if (_first_unread != _first_unassembled) {
        size_t len = _first_unassembled - _first_unread;
        string front_data;
        for (size_t i = 0; i < len; ++i) {
            front_data.push_back(_substrings[i]);
        }
        size_t write_data_len = _output.write(front_data);
        _first_unread += write_data_len;
        _cnt_substring -= write_data_len;
        for (size_t i = 0; i < write_data_len; ++i) {
            _substrings.pop_front();
            _st.pop_front();
        }
    }

    // check is stream EOF
    if (_output.bytes_written() == _idxEOF && empty()) {
        _output.end_input();
        // _first_unread = _first_unassembled = 0;
        // _idxEOF = -1;
    }
}
// The number of bytes in the substrings stored but not yet reassembled
size_t StreamReassembler::unassembled_bytes() const { return _cnt_substring; }
// Is the internal state empty (other than the output stream)?
bool StreamReassembler::empty() const { return _cnt_substring == 0; }
