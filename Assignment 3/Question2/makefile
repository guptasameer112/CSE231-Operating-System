all: P1_Socket P2_Socket P1_FIFO P2_FIFO P1_SharedMemory P2_SharedMemory

P1_Socket: P1_Socket.c
			gcc P1_Socket.c -o P1_Socket
P2_Socket: P2_Socket.c
			gcc P2_Socket.c -o P2_Socket

P1_FIFO: P1_FIFO.c
			gcc P1_FIFO.c -o P1_FIFO
P2_FIFO: P2_FIFO.c
			gcc P2_FIFO.c -o P2_FIFO

P1_SharedMemory: P1_SharedMemory.c
			gcc P1_SharedMemory.c -o P1_SharedMemory

P2_SharedMemory: P2_SharedMemory.c
			gcc P2_SharedMemory.c -o P2_SharedMemory
clean: 
			rm P1_Socket P2_Socket P1_FIFO P2_FIFO P1_SharedMemory P2_SharedMemory