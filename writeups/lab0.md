Lab 0 Writeup
=============
## 任务
- [x] 完成访问指定网站文件，并输出返回内容
- [x] 完成一个带缓冲区的字符流

## test results

```bash
ly@ubuntu:build$ make check_webget
[100%] Testing webget...
Test project /home/ly/Desktop/cpp_code/CS144learn/build
    Start 31: t_webget
1/1 Test #31: t_webget .........................   Passed    1.29 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   1.30 sec
[100%] Built target check_webget

ly@ubuntu:build$ make check_lab0
[100%] Testing Lab 0...
Test project /home/ly/Desktop/cpp_code/CS144learn/build
    Start 26: t_byte_stream_construction
1/9 Test #26: t_byte_stream_construction .......   Passed    0.01 sec
    Start 27: t_byte_stream_one_write
2/9 Test #27: t_byte_stream_one_write ..........   Passed    0.01 sec
    Start 28: t_byte_stream_two_writes
3/9 Test #28: t_byte_stream_two_writes .........   Passed    0.00 sec
    Start 29: t_byte_stream_capacity
4/9 Test #29: t_byte_stream_capacity ...........   Passed    0.58 sec
    Start 30: t_byte_stream_many_writes
5/9 Test #30: t_byte_stream_many_writes ........   Passed    0.01 sec
    Start 31: t_webget
6/9 Test #31: t_webget .........................   Passed    1.52 sec
    Start 53: t_address_dt
7/9 Test #53: t_address_dt .....................   Passed    0.02 sec
    Start 54: t_parser_dt
8/9 Test #54: t_parser_dt ......................   Passed    0.00 sec
    Start 55: t_socket_dt
9/9 Test #55: t_socket_dt ......................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 9

Total Test time (real) =   2.18 sec
[100%] Built target check_lab0
```

My name: [your name here]

My SUNet ID: [your sunetid here]

I collaborated with: [list sunetids here]

This lab took me about [n] hours to do. I [did/did not] attend the lab session.

My secret code from section 2.1 was: [code here]

- Optional: I had unexpected difficulty with: [describe]

- Optional: I think you could make this lab better by: [describe]

- Optional: I was surprised by: [describe]

- Optional: I'm not sure about: [describe]
