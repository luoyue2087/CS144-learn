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
    , _idxEOF(capacity)
    , _cnt_substring(0)
    , _substrings(capacity) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    // check _substrings is bigger than capacity
    while (_substrings.size() < _capacity)
        _substrings.push_back("");

    // caclulate index ture pos in StreamReassembler
    size_t in_index = index - _first_unread;
    if (in_index >= _capacity)
        return;

    // push data into StreamReassembler only the index-data not arrived before
    if(_substrings[in_index].empty()){
        _cnt_substring+=data.size();
        _substrings[in_index] = data;
    }

    // check is eof idx
    if (eof)
        _idxEOF = index;

    // update next glossy index
    if (in_index == _first_unassembled - _first_unread) {
        while (_first_unassembled - _first_unread < _capacity &&
               _substrings[_first_unassembled - _first_unread].size() > 0)
            ++_first_unassembled;
    }

    // output assembled data into streamer
    while(_first_unread!=_first_unassembled){
        string front_data = _substrings.front();
        _substrings.pop_front();
        while(_output.write(front_data)!=front_data.size()){
            sleep(1);
        }
        ++_first_unread;
        _cnt_substring-=front_data.size();
    }
    

    // check is stream EOF
    if(_first_unassembled == _idxEOF+1 && empty() ){
        _output.end_input();
        _first_unread = _first_unassembled = 0;
        _idxEOF = _capacity;
    }
}
// The number of bytes in the substrings stored but not yet reassembled
size_t StreamReassembler::unassembled_bytes() const { return _cnt_substring; }
// Is the internal state empty (other than the output stream)?
bool StreamReassembler::empty() const { return _cnt_substring==0; }
