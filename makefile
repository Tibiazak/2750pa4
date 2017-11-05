all: bank wc

bank: bank.o
	gcc bank.o -o bank

bank.o: bank.c
	gcc -c bank.c

wc: wc.o
	gcc wc.o -o wc

wc.o: wc.c
	gcc -c wc.c

clean:
	-rm -f *.o bank wc
