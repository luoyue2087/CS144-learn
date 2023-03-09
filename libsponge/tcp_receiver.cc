#include "tcp_receiver.hh"

// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.
using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    // cout <<"first un: "<< _reassembler.getFirstUnassembled()<<endl;
    // cout <<"abs_seq: "<< unwrap(seg.header().seqno, _ISN, _reassembByteNum) <<": "<<seg.payload().copy()
    //     <<", syn:"<<seg.header().syn
    //     <<", fin:"<<seg.header().fin <<endl;
    
    // 1. receive ISN
    if (_is_recv_ISN) {
        // size_t payloadSize = seg.payload().size();
        // size_t reassemblerSize = _reassembler.stream_out().buffer_size();//reassembler.buffer.size

        _reassembByteNum = _reassembler.getFirstUnassembled();
        uint64_t seqno_abs = unwrap(seg.header().seqno, _ISN, _reassembByteNum);
        // printf("---seq_abs: %ld\n", seqno_abs);
        // cout<<seg.payload().copy()<<endl;
        _reassembler.push_substring(seg.payload().copy(), seqno_abs - 1, seg.header().fin);  //-1 for ISN have one byte
        // printf("reassembByteNum=%ld\n",_reassembler.getFirstUnassembled());
        // _reassembByteNum += (reassemblerSize + payloadSize - _reassembler.unassembled_bytes());
    } else {
        // 2. no receive ISN and cur is ISN
        if (seg.header().syn) {
            _is_recv_ISN = true;
            _ISN = seg.header().seqno;  
            if(seg.payload().size()){
                _reassembByteNum = _reassembler.getFirstUnassembled();
                uint64_t seqno_abs = unwrap(seg.header().seqno+1, _ISN, _reassembByteNum);
                _reassembler.push_substring(seg.payload().copy(), seqno_abs - 1, seg.header().fin);
            }

            // buffer data to reassembler
            size_t bufferSize = _tcpReceiverBuffer.size();
            if (bufferSize > 0) {
                for (size_t iBuffer = 0; iBuffer < bufferSize; ++iBuffer) {
                    // size_t payloadSize = seg.payload().size();
                    // size_t reassemblerSize = _reassembler.stream_out().buffer_size();
                    const TCPSegment &segInBuffer = _tcpReceiverBuffer[iBuffer];

                    // cout    <<"abs_seq: "<< unwrap(segInBuffer.header().seqno, _ISN, _reassembByteNum) <<": "<<segInBuffer.payload().copy()
                    //         <<", syn:"<<segInBuffer.header().syn
                    //         <<", fin:"<<segInBuffer.header().fin <<endl;
                            
                    _reassembByteNum = _reassembler.getFirstUnassembled();
                    uint64_t seqno_abs = unwrap(segInBuffer.header().seqno, _ISN, _reassembByteNum);
                    
                    _reassembler.push_substring(segInBuffer.payload().copy(), seqno_abs - 1, segInBuffer.header().fin);
                }
                _tcpReceiverBuffer.clear();
            } else if (seg.header().fin) {  // no data and fin=true
                // _reassembByteNum = _reassembler.getFirstUnassembled();
                // uint64_t seqno_abs = unwrap(seg.header().seqno, _ISN, _reassembByteNum);
                // _reassembler.push_substring("", seqno_abs, true);
                _reassembler.stream_out().end_input();
                // ++_reassembByteNum;
            }
        } else {
            // 3. no receive ISN and cur is not ISN
            if (seg.header().fin) {
                _reassembByteNum = _reassembler.getFirstUnassembled();
                uint64_t seqno_abs = unwrap(seg.header().seqno, _ISN, _reassembByteNum);
                _reassembler.push_substring(seg.payload().copy(), seqno_abs - 1, seg.header().fin);
            }
            /* else if (_tcpReceiverBuffer.size() < _capacity)
                _tcpReceiverBuffer.push_back(seg);
            */
            // if buffer over than _capacity, drop out this segment
        }
    }

    if (seg.header().fin) {
        _is_recv_FIN = true;
        _FIN = seg.header().seqno;
    }
}

// “ackno.” This is the first byte that the receiver needs from the sender
optional<WrappingInt32> TCPReceiver::ackno() const {
    if (_is_recv_ISN) {
        uint64_t tmp = _reassembler.getFirstUnassembled();
        // printf("----%d\n",_reassembler.stream_out().input_ended());
        if (_reassembler.stream_out().input_ended()){ //need check if have receive all data
            ++tmp;  // FIN = 1 byte
        }
        ++tmp;  // ISN = 1 byte
        return WrappingInt32(wrap(tmp, WrappingInt32(_ISN)));
    }
    return std::nullopt;
}

size_t TCPReceiver::window_size() const { return _capacity - _reassembler.stream_out().buffer_size(); }
