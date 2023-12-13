all: tx rx 

tx: tx.c
	gcc tx.c -o tx

rx: rx.c
	gcc rx.c -o rx

clean:
	rm -f rx tx
