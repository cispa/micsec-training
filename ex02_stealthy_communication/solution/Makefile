all: sender receiver sharedmem

sender: sender.c
	gcc sender.c -Os -Wall -Wno-unused-variable -o sender

receiver: receiver.c
	gcc receiver.c -Os -Wall -Wno-unused-variable -o receiver

sender-solution: sender-solution.c
	gcc sender.c -Os -Wall -Wno-unused-variable -o sender

receiver-solution: receiver-solution.c
	gcc receiver.c -Os -Wall -Wno-unused-variable -o receiver

sharedmem:
	dd if=/dev/zero of=sharedmem bs=4096 count=256

run: sender receiver
	taskset -c 1 ./sender

clean:
	rm -f sender receiver sharedmem
