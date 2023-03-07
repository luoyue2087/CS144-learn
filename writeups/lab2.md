## 开始
```bash
git branch lab2-startercode
git fetch
git merge origin/lab2-startercode
```

## 任务
- [x] Implementing the WrappingInt32
- [ ] Implementing the TCP receiver
    - [ ] receive segments from its peer.
    - [ ] reassemble the ByteStreamusing your StreamReassembler.
    - [ ] calculate the acknowledgment number (ackno) and the window size.

TheTCPReceiverreceives segments fromthe Internet(via thesegment received()method) and turns them into calls to yourStreamReassembler, which eventually writes to the incomingByteStream.

In addition to writing to the incoming stream, theTCPReceiveris responsible for telling thesender two things :
1.the index of the “first unassembled” byte, which is called the “acknowledgment number”or “ackno.” This is the first byte that the receiver needs from the sender.
2.the distance between the “first unassembled” index and the “first unacceptable” index.This is called the “window size”.


* 需要将64-bit的索引转换为32-bit的，因为TCP header空间是宝贵的
* 用32-bit实现环形指针，因为数据流没有限制，但32bits只有4GB
* TCP报文段的序号是随机值开始的 (Initial Sequence Number, ISN)
* 第一字节的序列号是 ISN+1 (mod 23^2)
* 为了确保能完整收到，SYN和FIN各占一个序列号，但是并不算在数据流的大小计算中

* [TCP报文段说明](https://cs144.github.io/doc/lab2/class_t_c_p_segment.html)
* [TCP头部说明](https://cs144.github.io/doc/lab2/struct_t_c_p_header.html)
* size_t TCPSegment::length_in_sequence_space() const : Equal to payload length plus one byte if SYN is set, plus one byte if FIN is set
*  In your TCP implementation, you’ll use the index of the last reassembled byte as the checkpoint.

* TCPReceiver::segment received()
    * Set the Initial Sequence Number if necessary.
    * Push any data, or end-of-stream marker, to theStreamReassembler.
## 测试方式
* ctest -R wrap 测试 WrappingInt32 类是否实现
* make check_lab2

## 测试结果
```bash

Test project /home/ly/Desktop/cpp_code/CS144learn/build
    Start 1: t_wrapping_ints_cmp
1/4 Test #1: t_wrapping_ints_cmp ..............   Passed    0.01 sec
    Start 2: t_wrapping_ints_unwrap
2/4 Test #2: t_wrapping_ints_unwrap ...........   Passed    0.00 sec
    Start 3: t_wrapping_ints_wrap
3/4 Test #3: t_wrapping_ints_wrap .............   Passed    0.00 sec
    Start 4: t_wrapping_ints_roundtrip
4/4 Test #4: t_wrapping_ints_roundtrip ........   Passed    0.20 sec

100% tests passed, 0 tests failed out of 4
```

## origin readme.md
Lab 2 Writeup
============ =

My name : [your name here]

My SUNet ID : [your sunetid here]

I collaborated with : [list sunetids here]

I would like to thank / reward these classmates for their help : [list sunetids here]

This lab took me about[n] hours to do.I[did / did not] attend the lab session.

Program Structureand Design of the TCPReceiverand wrap / unwrap routines :
[]

Implementation Challenges :
[]

Remaining Bugs :
[]

- Optional : I had unexpected difficulty with : [describe]

- Optional : I think you could make this lab better by : [describe]

- Optional : I was surprised by : [describe]

- Optional : I'm not sure about: [describe]
