Lab 1 Writeup
=============

My name: [luoyue]

My SUNet ID: [your sunetid here]

I collaborated with: [list sunetids here]

I would like to thank/reward these classmates for their help: [list sunetids here]

This lab took me about [n] hours to do. I [did/did not] attend the lab session.

Program Structure and Design of the StreamReassembler:
[x] deque<char>数据结构

Implementation Challenges:
- [x] 每一个片段的开头是整个流的索引，不是片段的索引
- [x] 有可能一个片段没有数据，但正好EOF
- [x] 有可能一个片段长度等于capacity，且没有EOF
- [x] 有可能一个片段长度等于capacity，且有EOF，并且需要能获得该片段
- [x] 碎片可能交叉或重叠:SubmitSegment{"abc", 0},SubmitSegment{"bcdefgh", 1}
- [ ] 有可能导致lab0的缓冲区满 

Remaining Bugs:
[]

- Optional: I had unexpected difficulty with: [describe]

- Optional: I think you could make this lab better by: [describe]

- Optional: I was surprised by: [describe]

- Optional: I'm not sure about: [describe]
