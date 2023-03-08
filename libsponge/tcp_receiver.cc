#include "tcp_receiver.hh"

// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    if (_is_recv_SYN) {
        size_t payloadSize = seg.payload().size();
        size_t reassemblerSize = _reassembler.stream_out().buffer_size();

        _reassembByteNum += (reassemblerSize + payloadSize - _reassembler.unassembled_bytes());

        uint64_t seqno_abs = unwrap(seg.header().seqno, _ISN, _reassembByteNum);
        _reassembler.push_substring(seg.payload().copy(), seqno_abs - 1, seg.header().fin);
    } else {
        if (seg.header().syn) {
            _is_recv_SYN = true;
            _ISN = seg.header().seqno;

            // buffer data to reassembler
            size_t bufferSize = _tcpReceiverBuffer.size();
            for (size_t iBuffer = 0; iBuffer < bufferSize; ++iBuffer) {
                size_t payloadSize = seg.payload().size();
                size_t reassemblerSize = _reassembler.stream_out().buffer_size();

                _reassembByteNum += (reassemblerSize + payloadSize - _reassembler.unassembled_bytes());

                uint64_t seqno_abs = unwrap(seg.header().seqno, _ISN, _reassembByteNum);
                _reassembler.push_substring(seg.payload().copy(), seqno_abs - 1, seg.header().fin);
            }
        } else {
            if (_tcpReceiverBuffer.size() < _capacity)
                _tcpReceiverBuffer.push_back(seg);
            // if buffer over than _capacity, drop out this segment
        }
    }

    if (seg.header().fin) {
        _is_recv_FIN = true;
        _FIN = seg.header().seqno;
        uint64_t seqno_abs = unwrap(seg.header().seqno, _ISN, _reassembByteNum);
        _reassembler.push_substring("", seqno_abs - 1, true);
    }
}

// “ackno.” This is the first byte that the receiver needs from the sender
optional<WrappingInt32> TCPReceiver::ackno() const {
    if (_is_recv_SYN)
        return WrappingInt32(wrap(_reassembByteNum + 1, WrappingInt32(_ISN)));
    return std::nullopt;
}

size_t TCPReceiver::window_size() const { return _capacity - _reassembler.stream_out().buffer_size(); }
