CC = cc
CFLAGS = -Wall -Wextra -pthread
TESTE = sync_car-runner.c

sync_car: sync_car.c sync_car.h $(TESTE)
	$(CC) $(CFLAGS) -o sync_car sync_car.c $(TESTE)

clean:
	rm -f sync_car *.o

.PHONY: clean