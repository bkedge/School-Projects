#Brady Kedge

CC = gcc
CFLAGS = -g
LOG = log.out

OSS = oss
OSSOBS = oss.o
OSSC = oss.c

USER = user
USEROBS = user.o
USERC = user.c

all: $(OSS) $(USER)

$(OSS): $(OSSOBS)
	$(CC) $(CFLAGS) -o $(OSS) $(OSSOBS)

$(OSSOBS): $(OSSC)
	$(CC) $(CFLAGS) -c $(OSSC)

$(USER): $(USEROBS)
	$(CC) $(CFLAGS) -o $(USER) $(USEROBS)

$(USEROBS): $(USERC)
	$(CC) $(CFLAGS) -c $(USERC)

clean:
	rm $(OSS) $(USER) *.o $(LOG)
