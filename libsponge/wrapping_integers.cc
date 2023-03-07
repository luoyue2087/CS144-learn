#include "wrapping_integers.hh"

// Dummy implementation of a 32-bit wrapping integer

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.


using namespace std;

//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) {
    uint32_t ans =0;
    uint64_t mod = pow(static_cast<uint64_t>(2),32);
    ans = (n + isn.raw_value()) % (mod);
    return WrappingInt32{ans};
}

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.
// In your TCP implementation, you’ll use the index of 
// the last reassembled byte as the checkpoint.
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {
    uint64_t mod = pow(static_cast<uint64_t>(2),32);
    uint64_t ret = (n.raw_value() + mod - isn.raw_value()) % mod;//[0, mod-1]
    if(ret>=checkpoint)return ret;

    uint64_t diff = checkpoint-ret;
    uint32_t prob = diff/mod;

    if(prob==0)return ret+mod;// prob=0, it means that checkpoint - ret <= mod
    
    // else find a value that satisfy between left of checkpoint and right of checkpoint
    // and value = ret + k * mod
    uint64_t up = ret + (prob+1)*mod, down = up - mod;
    if(up-checkpoint>checkpoint-down)return down;
    return up;
}
