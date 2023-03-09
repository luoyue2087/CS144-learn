# 前言
CS144 实验课 2021版

## 课程简介

- 所属大学：Stanford
- 先修要求：一定的计算机系统基础，CS106L
- 编程语言：C++
- 课程难度：🌟🌟🌟🌟🌟
- 预计学时：100 小时

这门课的主讲人之一是网络领域的巨擘 [Nick McKeown](http://yuba.stanford.edu/~nickm/index.html) 教授。这位拥有自己创业公司的学界业界双巨佬会在他慕课每一章节的最后采访一位业界的高管或者学界的高人，非常开阔眼界。

在这门课的 Project 中，你将用 C++ 循序渐进地搭建出整个 TCP/IP 协议栈，实现 IP 路由以及 ARP 协议，最后利用你自己的协议栈代替 Linux Kernel 的网络协议栈和其他学生的计算机进行通信，非常 amazing！

## 课程资源

- 课程网站：https://cs144.github.io/
- 课程视频：https://www.youtube.com/watch?v=r2WZNaFyrbQ&list=PL6RdenZrxrw9inR-IJv-erlOKRHjymxMN
- 课程教材：无
- 课程作业：https://cs144.github.io/，8 个 Project 带你实现整个 TCP/IP 协议栈


# 实验目标
学习并掌握TCP/IP的基础编码知识
# 完成情况
- [x] Lab 0 : a flow-controlled byte stream (ByteStream).
- [x] Lab 1 : stream assembler (StreamReassembler).
- [x] Lab 2 : TCP receiver
- [ ] Lab 3 : TCP sender
- [ ] Lab 4 : TCP connection
- [ ] Lab 5 : Network Interface
- [ ] Lab 6 : IP routing
- [ ] Lab 7 : Putting it all together 

# 注释
* 首先要安装g++-8或clang-6，请根据自己的linux发行版自行搜索对应方法。我用的是g++-8，如果安装后CMAKE的时候还是提示g++版本不够，那就百度一下怎么把用g++-8替代gcc，再不行的话那就为gcc-8创建一个名为cc的软连接，为g++-8创建一个名为c++的软链接。

* 另外，如果你CMAKE的时候报出了如下错误：

```bash
CMake Error: The following variables are used in this project, but they are set to NOTFOUND.
Please set them or make sure they are set and tested correctly in the CMake files:
LIBPCAP
    linked by target "udp_tcpdump" in directory /home/kangyu/sponge/apps
    linked by target "ipv4_parser" in directory /home/kangyu/sponge/tests
    linked by target "ipv4_parser" in directory /home/kangyu/sponge/tests
    linked by target "tcp_parser" in directory /home/kangyu/sponge/tests
    linked by target "tcp_parser" in directory /home/kangyu/sponge/tests
```
```bash
sudo apt-get install libpcap-dev
```

# 参考
- [康宇PL's Blog](https://www.cnblogs.com/kangyupl/p/stanford_cs144_labs.html)
- [PKUFlyingPig](https://github.com/PKUFlyingPig/CS144-Computer-Network)
- [Lexssama's Blogs](https://lexssama.github.io/tags/CS144/)
- [huangrt01](https://github.com/huangrt01/CS-Notes/blob/master/Notes/Output/Computer-Networking-Lab-CS144-Stanford.md)
- [kiprey](https://kiprey.github.io/tags/CS144/)
- [doraemonzzz](http://doraemonzzz.com/tags/CS144/)
- [ViXbob's libsponge](https://vixbob.moe/25.html)
- [吃着土豆坐地铁的博客](https://www.epis2048.net/categories/Code/Stanford-CS144/)
- [Smith](https://www.inlighting.org/archives/2021-cs144-notes/)
- [星遥见](https://www.cnblogs.com/weijunji/tag/CS144/)
- [EIMadrigal](https://www.cnblogs.com/EIMadrigal/p/15500472.html)
- [Joey](http://yuzijun.life/2021-02/CS144)


# origin readme.md content
For build prereqs, see [the CS144 VM setup instructions](https://web.stanford.edu/class/cs144/vm_howto).

## Sponge quickstart

To set up your build directory:

	$ mkdir -p <path/to/sponge>/build
	$ cd <path/to/sponge>/build
	$ cmake ..

**Note:** all further commands listed below should be run from the `build` dir.

To build:

    $ make

You can use the `-j` switch to build in parallel, e.g.,

    $ make -j$(nproc)

To test (after building; make sure you've got the [build prereqs](https://web.stanford.edu/class/cs144/vm_howto) installed!)

    $ make check_labN *(replacing N with a checkpoint number)*

The first time you run `make check_lab...`, it will run `sudo` to configure two
[TUN](https://www.kernel.org/doc/Documentation/networking/tuntap.txt) devices for use during
testing.

### build options

You can specify a different compiler when you run cmake:

    $ CC=clang CXX=clang++ cmake ..

You can also specify `CLANG_TIDY=` or `CLANG_FORMAT=` (see "other useful targets", below).

Sponge's build system supports several different build targets. By default, cmake chooses the `Release`
target, which enables the usual optimizations. The `Debug` target enables debugging and reduces the
level of optimization. To choose the `Debug` target:

    $ cmake .. -DCMAKE_BUILD_TYPE=Debug

The following targets are supported:

- `Release` - optimizations
- `Debug` - debug symbols and `-Og`
- `RelASan` - release build with [ASan](https://en.wikipedia.org/wiki/AddressSanitizer) and
  [UBSan](https://developers.redhat.com/blog/2014/10/16/gcc-undefined-behavior-sanitizer-ubsan/)
- `RelTSan` - release build with
  [ThreadSan](https://developer.mozilla.org/en-US/docs/Mozilla/Projects/Thread_Sanitizer)
- `DebugASan` - debug build with ASan and UBSan
- `DebugTSan` - debug build with ThreadSan

Of course, you can combine all of the above, e.g.,

    $ CLANG_TIDY=clang-tidy-6.0 CXX=clang++-6.0 .. -DCMAKE_BUILD_TYPE=Debug

**Note:** if you want to change `CC`, `CXX`, `CLANG_TIDY`, or `CLANG_FORMAT`, you need to remove
`build/CMakeCache.txt` and re-run cmake. (This isn't necessary for `CMAKE_BUILD_TYPE`.)

### other useful targets

To generate documentation (you'll need `doxygen`; output will be in `build/doc/`):

    $ make doc

To format (you'll need `clang-format`):

    $ make format

To see all available targets,

    $ make help
