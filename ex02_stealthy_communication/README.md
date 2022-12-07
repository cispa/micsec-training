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

A working solution could look like this:
Terminal 1:
```
./sender
Enter character to send: C
Sent 'C'
Enter character to send: O
Sent 'O'
Enter character to send: V
Sent 'V'
Enter character to send: E
Sent 'E'
Enter character to send: R
Sent 'R'
Enter character to send: T
Sent 'T'
Enter character to send:
```

Terminal 2:
```
./receiver
Received 'C'
Received 'O'
Received 'V'
Received 'E'
Received 'R'
Received 'T'
```
