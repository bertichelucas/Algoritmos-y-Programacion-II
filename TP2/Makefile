CFLAGS=-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
MATHFLAG=-lm

count_min_sketch.o: count_min_sketch.c count_min_sketch.h
	gcc $(CFLAGS) -c count_min_sketch.c
pruebas_cms.o: pruebas_cms.c
	gcc $(CFLAGS) -c pruebas_cms.c

testing.o: testing.c testing.h
	gcc $(CFLAGS) -c testing.c

strutil.o: strutil.c strutil.h
	gcc $(CFLAGS) -c strutil.c

hash.o: hash.c hash.h lista.o
	gcc $(CFLAGS) -c hash.c

lista.o: lista.c lista.h
	gcc $(CFLAGS) -c lista.c

heap.o: heap.c heap.h
	gcc $(CFLAGS) -c heap.c

procesar_tweets.o: procesar_tweets.c
	gcc $(CFLAGS) -c procesar_tweets.c

procesar_usuarios.o: procesar_usuarios.c
	gcc $(CFLAGS) -c procesar_usuarios.c

procesar_tweets: hash.o heap.o count_min_sketch.o strutil.o lista.o procesar_tweets.o
	gcc hash.o heap.o count_min_sketch.o strutil.o lista.o procesar_tweets.o -o procesar_tweets

procesar_usuarios: hash.o strutil.o procesar_usuarios.o
	gcc hash.o strutil.o procesar_usuarios.o lista.o -o procesar_usuarios

cms_test: count_min_sketch.o pruebas_cms.o testing.o
	gcc count_min_sketch.o pruebas_cms.o testing.o  -o pruebas_cms
clear:
	rm *.o
