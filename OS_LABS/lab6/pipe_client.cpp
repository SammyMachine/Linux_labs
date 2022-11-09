/* The client program  pipe_client.cpp */
#include"pipe_local.h"
// added
char privatefifo_name[B_SIZ];
int privatefifo;
void signal_handler (int sig) {
    if (sig == SIGINT) {
        close(privatefifo);
        remove(privatefifo_name);
        exit(0);
    }
}
int main(void)
{
int	n, publicfifo;
static char buffer[PIPE_BUF];
struct message msg;
    /* Make the name for the private FIFO */
sprintf(msg.fifo_name, "/tmp/fifo %d", getpid());
sprintf(privatefifo_name, "/tmp/fifo %d", getpid());
    /* OPEN the public FIFO for writing */
// added
if ((publicfifo=open(PUBLIC, O_WRONLY)) == -1) {
    if (fork() == 0) {
        execl("./server", "&");
    }
    else {
        publicfifo = open(PUBLIC, O_WRONLY);
    }
    sleep(3);
}
if ((publicfifo=open(PUBLIC, O_WRONLY))==-1){
    perror(PUBLIC);
    exit(2);
}
    /* Generate the private FIFO */
if (mknod(msg.fifo_name, S_IFIFO | 0666, 0)<0){
    perror(msg.fifo_name);
    exit(1);
    }
signal(SIGINT, signal_handler);
while(1){	/* FOREVER */
    write(fileno(stdout), "\ncmd>", 6);
    memset(msg.cmd_line, 0x0, B_SIZ);	/* Clear first */
    n = read(fileno(stdin), msg.cmd_line, B_SIZ); /* Get cmd */
	if(!strncmp("quit", msg.cmd_line, n-1))
	break;				/* EXIT? */
    write(publicfifo, (char *) &msg, sizeof(msg)); /* to PUBLIC */
    /* OPEN private FIFO to read returned command output */
	if((privatefifo = open(msg.fifo_name, O_RDONLY))==-1){
	    perror(msg.fifo_name);
	    exit(3);
	    }
    /* READ private FIFO and display on standard error */
    while((n=read(privatefifo, buffer, PIPE_BUF))>0){
	write(fileno(stderr), buffer, n);
	}
	close(privatefifo);
    }
    close(publicfifo);
    unlink(msg.fifo_name);
}
    
	



