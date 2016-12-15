#Brady Kedge

CC = gcc
CFLAGS = -g
LOG = test.out

MASTER = master
MASTEROBS = master.o
MASTERC = master.c

SLAVE = slave
SLAVEOBS = slave.o
SLAVEC = slave.c

all: $(MASTER) $(SLAVE)

$(MASTER): $(MASTEROBS)
	$(CC) $(CFLAGS) -o $(MASTER) $(MASTEROBS)

$(MASTEROBS): $(MASTERC)
	$(CC) $(CFLAGS) -c $(MASTERC)

$(SLAVE): $(SLAVEOBS)
	$(CC) $(CFLAGS) -o $(SLAVE) $(SLAVEOBS)

$(SLAVEOBS): $(SLAVEC)
	$(CC) $(CFLAGS) -c $(SLAVEC)

clean:
	rm $(MASTER) $(SLAVE) *.o $(LOG)
