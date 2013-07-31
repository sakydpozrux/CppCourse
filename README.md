CppCourse
=========

My solutions to tasks for **C++ course** at University


Usage
=====

You need C++ compiler with support for C++11. I have tested these programs for both: *gcc* and *clang*. If you use *clang* changing *g++* in each Makefile for *clang++* should be enough.

To compile each task use

    make

then run

    ./main

or (for task 11)

    ./life


Memory leaks
============

I checked all programs for memory leaks and didn't find any.

For example:

    valgrind --tool=memcheck ./main


Contact
=======

Feel free to [send me an email](mailto:sakydpozrux@gmail.com) if you find any bugs or anything is unclear.
