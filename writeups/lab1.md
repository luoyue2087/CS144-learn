Lab 1 Writeup
=============

My name: [luoyue]

My SUNet ID: [your sunetid here]

I collaborated with: [list sunetids here]

I would like to thank/reward these classmates for their help: [list sunetids here]

This lab took me about [n] hours to do. I [did/did not] attend the lab session.

Program Structure and Design of the StreamReassembler:
- [x] deque<char>数据结构

Implementation Challenges:
- [x] 完成一个带缓冲区、可重组报文段（仅有id）的类
- [x] 每一个片段的开头是整个流的索引，不是片段的索引
- [x] 有可能一个片段没有数据，但正好EOF
- [x] 有可能一个片段长度等于capacity，且没有EOF
- [x] 有可能一个片段长度等于capacity，且有EOF，并且需要能获得该片段
- [x] 碎片可能交叉或重叠:SubmitSegment{"abc", 0},SubmitSegment{"bcdefgh", 1}
- [x] 有可能导致lab0的缓冲区满 
- [x] 一半越界的碎片也需要保存前半部分 emmmm...


## test result

```bash
ly@ubuntu:build$ cmake .. -DCMAKE_BUILD_TYPE=Release && make -j4 && make check_lab1
Test project /home/ly/Desktop/cpp_code/CS144learn/build
      Start 18: t_strm_reassem_single
 1/16 Test #18: t_strm_reassem_single ............   Passed    0.00 sec
      Start 19: t_strm_reassem_seq
 2/16 Test #19: t_strm_reassem_seq ...............   Passed    0.01 sec
      Start 20: t_strm_reassem_dup
 3/16 Test #20: t_strm_reassem_dup ...............   Passed    0.01 sec
      Start 21: t_strm_reassem_holes
 4/16 Test #21: t_strm_reassem_holes .............   Passed    0.01 sec
      Start 22: t_strm_reassem_many
 5/16 Test #22: t_strm_reassem_many ..............   Passed    0.15 sec
      Start 23: t_strm_reassem_overlapping
 6/16 Test #23: t_strm_reassem_overlapping .......   Passed    0.01 sec
      Start 24: t_strm_reassem_win
 7/16 Test #24: t_strm_reassem_win ...............   Passed    0.24 sec
      Start 25: t_strm_reassem_cap
 8/16 Test #25: t_strm_reassem_cap ...............   Passed    0.12 sec
      Start 26: t_byte_stream_construction
 9/16 Test #26: t_byte_stream_construction .......   Passed    0.01 sec
      Start 27: t_byte_stream_one_write
10/16 Test #27: t_byte_stream_one_write ..........   Passed    0.00 sec
      Start 28: t_byte_stream_two_writes
11/16 Test #28: t_byte_stream_two_writes .........   Passed    0.00 sec
      Start 29: t_byte_stream_capacity
12/16 Test #29: t_byte_stream_capacity ...........   Passed    0.56 sec
      Start 30: t_byte_stream_many_writes
13/16 Test #30: t_byte_stream_many_writes ........   Passed    0.02 sec
      Start 53: t_address_dt
14/16 Test #53: t_address_dt .....................   Passed    0.09 sec
      Start 54: t_parser_dt
15/16 Test #54: t_parser_dt ......................   Passed    0.01 sec
      Start 55: t_socket_dt
16/16 Test #55: t_socket_dt ......................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 16

Total Test time (real) =   1.26 sec
[100%] Built target check_lab1
```

Remaining Bugs:
- [x] 数据量太多，unassembled_bytes 异常：用'\0'的方式判断不是很合理，使用st deque来记录状态
- [x] 注意判断碎片的长度有效性：如果一个碎片已经完全被重组了，那么直接丢弃该碎片

- Optional: I had unexpected difficulty with: [describe]

- Optional: I think you could make this lab better by: [describe]

- Optional: I was surprised by: [describe]

- Optional: I'm not sure about: [describe]
