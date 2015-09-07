CC=gcc
CFLAGS= -std=c99 -pedantic-errors
LFLAGS=
NOLINK= -c
OBJETDIR=objets/
EXECDIR=builds/
ALL=as_coeur as_trefle PRc ls_wc process prod test client serveur shell_ls PRa PRb PRc PRd PRe blake_carreau double_open echo_cat utilities nosa_carreau alarm_t interbloc ls_file huit_coeur

all : Demo $(OBJETDIR) $(ALL)
	@clear

$(OBJETDIR) : 
	@mkdir $(OBJETDIR)

huit_coeur : $(OBJETDIR)huit_coeur.o
	$(CC) $(LFLAGS) $^ -o $@
alarm_t : $(OBJETDIR)alarm_t.o
	$(CC) $(LFLAGS) $^ -o $@
interbloc : $(OBJETDIR)interbloc.o
	$(CC) $(LFLAGS) $^ -o $@
double_open : $(OBJETDIR)double_open.o
	$(CC) $(LFLAGS) $^ -o $@
echo_chat : $(OBJETDIR)echo_chat.o
	$(CC) $(LFLAGS) $^ -o $@
utilities : $(OBJETDIR)utilities.o
	$(CC) $(LFLAGS) $^ -o $@
blake_carreau : $(OBJETDIR)blake_carreau.o
	$(CC) $(LFLAGS) $^ -o $@
nosa_carreau : $(OBJETDIR)nosa_carreau.o
	$(CC) $(LFLAGS) $^ -o $@
as_coeur : $(OBJETDIR)as_coeur.o
	$(CC) $(LFLAGS) $^ -o $@
PRa : $(OBJETDIR)PRa.o
	$(CC) $(LFLAGS) $^ -o $@
PRb : $(OBJETDIR)PRb.o
	$(CC) $(LFLAGS) $^ -o $@
PRc : $(OBJETDIR)PRc.o
	$(CC) $(LFLAGS) $^ -o $@ 
PRd : $(OBJETDIR)PRd.o
	$(CC) $(LFLAGS) $^ -o $@ 
PRe : $(OBJETDIR)PRe.o
	$(CC) $(LFLAGS) $^ -o $@ 
as_trefle : $(OBJETDIR)as_trefle.o
	$(CC) $(LFLAGS) $^ -o $@
ls_wc : $(OBJETDIR)ls_wc.o
	$(CC) $(LFLAGS) $^ -o $@ 
process : $(OBJETDIR)process.o
	$(CC) $(LFLAGS) $^ -o $@ 
prod : $(OBJETDIR)prod.o
	$(CC) $(LFLAGS) $^ -o $@ 
test : $(OBJETDIR)test.o
	$(CC) $(LFLAGS) $^ -o $@ 
client : $(OBJETDIR)client.o
	$(CC) $(LFLAGS) $^ -o $@ 
serveur : $(OBJETDIR)serveur.o
	$(CC) $(LFLAGS) $^ -o $@ 
shell_ls : $(OBJETDIR)shell_ls.o
	$(CC) $(LFLAGS) $^ -o $@ 

$(OBJETDIR)%.o : %.c 
	$(CC) $(CFLAGS) $(NOLINK) $^ -o $@

clean :
	@rm -rf $(OBJETDIR)/*.o
	@rmdir $(OBJETDIR)
	@rm -rf $(ALL)
