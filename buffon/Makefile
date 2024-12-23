IDIR = /home/mjjeon/Homeworks/SPRNG/sprng5/include
LIBDIR = /home/mjjeon/Homeworks/SPRNG/sprng5/lib
CC = mpicxx

main : mean.o write_file.o main.o
	$(CC) -o main mean.o write_file.o main.o -L$(LIBDIR) -lsprng

main.o : main.cpp
	$(CC) -c -o main.o main.cpp -I$(IDIR)

mean.o : mean.cpp
	$(CC) -c -o mean.o mean.cpp -I$(IDIR) 

write_file.o : write_file.cpp
	$(CC) -c -o write_file.o write_file.cpp -I$(IDIR) 

clean:
	rm *.o main
