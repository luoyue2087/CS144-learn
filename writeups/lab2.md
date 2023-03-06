## 开始
```bash
git branch lab2-startercode
git fetch
git merge origin/lab2-startercode
```

## 任务

TheTCPReceiverreceives segments fromthe Internet(via thesegment received()method) and turns them into calls to yourStreamReassembler, which eventually writes to the incomingByteStream.

In addition to writing to the incoming stream, theTCPReceiveris responsible for telling thesender two things :
1.the index of the “first unassembled” byte, which is called the “acknowledgment number”or “ackno.” This is the first byte that the receiver needs from the sender.
2.the distance between the “first unassembled” index and the “first unacceptable” index.This is called the “window size”.


- [ ] 需要将64-bit的索引转换为32-bit的，因为TCP header空间是宝贵的
- [ ] 用32-bit实现环形指针，因为数据流没有限制，但32bits只有4GB
- [ ] TCP报文段的序号是随机值开始的 (Initial Sequence Number, ISN)
- [ ] 第一字节的数据 是 ISN+1 (mod 232)

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
