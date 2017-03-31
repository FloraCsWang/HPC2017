linker: int_ring.c int_modified.c
	mpicc  int_ring.c -o int_ring
	mpicc  int_modified.c -o int_modified


clean:
	rm -f  int_ring *~
	rm -f  int_modified *~