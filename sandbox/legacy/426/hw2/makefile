CC = cc
CFLAGS = -fno-stack-protector
LDFLAGS = -lsqlite3 -zexecstack
OBJECTS = inout.o signin.o signout.o

all: inout signin signout

inout.o: inout.c inout.h
	$(CC) -c -o $@ $< $(CFLAGS)

signin.o: signinout.c inout.h
	$(CC) -DSTATUS="IN" -c -o $@ $< $(CFLAGS)

signout.o: signinout.c inout.h
	$(CC) -DSTATUS="OUT" -c -o $@ $< $(CFLAGS)

inout: inout.o
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

signin: signin.o
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

signout: signout.o
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-rm inout signin signout $(OBJECTS)


