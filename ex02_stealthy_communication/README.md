# Exercise 2: Stealthy Communication

## Goal
In this exercise, your goal is to develop two processes, a sender and a receiver process that will communicate via the CPU cache.

## Description
To solve the exercise, you have to implement the TODOs inside `sender.c` and `receiver.c`.

## Compilation and Execution
You can build the code by executing the `make` command. This will compile the files `sender.c` and `receiver.c`
Afterward, you need to spawn two terminal windows.
First, you start a terminal with the sender process:
```
./sender
```
Second, you start a terminal with the receiver process:

```
./receiver
```
Next, you can start typing messages inside the sender prompt that will be received and printed by the second process.
