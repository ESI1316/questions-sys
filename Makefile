CC=gcc
CFLAGS= -std=c99 -pedantic-errors
LFLAGS=
NOLINK= -c
ALL=as_coeur as_trefle PRc ls_wc process prod test client serveur shell_ls PRa PRb PRc PRd PRe blake_carreau

all : Demo $(ALL)
	@clear

blake_carreau : blake_carreau.o
	$(CC) $(LFLAGS) $^ -o $@
as_coeur : as_coeur.o
	$(CC) $(LFLAGS) $^ -o $@
PRa : PRa.o
	$(CC) $(LFLAGS) $^ -o $@
PRb : PRb.o
	$(CC) $(LFLAGS) $^ -o $@
PRc : PRc.o
	$(CC) $(LFLAGS) $^ -o $@ 
PRd : PRd.o
	$(CC) $(LFLAGS) $^ -o $@ 
PRe : PRe.o
	$(CC) $(LFLAGS) $^ -o $@ 
as_trefle : as_trefle.o
	$(CC) $(LFLAGS) $^ -o $@
ls_wc : ls_wc.o
	$(CC) $(LFLAGS) $^ -o $@ 
process : process.o
	$(CC) $(LFLAGS) $^ -o $@ 
prod : prod.o
	$(CC) $(LFLAGS) $^ -o $@ 
test : test.o
	$(CC) $(LFLAGS) $^ -o $@ 
client : client.o
	$(CC) $(LFLAGS) $^ -o $@ 
serveur : serveur.o
	$(CC) $(LFLAGS) $^ -o $@ 
shell_ls : shell_ls.o
	$(CC) $(LFLAGS) $^ -o $@ 

%.o : %.c 
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

clean :
	@rm -rf *.o
	@rm -rf $(ALL)
