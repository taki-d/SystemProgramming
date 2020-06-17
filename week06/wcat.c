#include <stdio.h>
#include <stdlib.h>	/* exit() */
#include <string.h>	/* memset(), memcpy() */
#include <sys/types.h>	/* socket() */
#include <sys/socket.h>	/* socket() */
#include <netinet/in.h>	/* struct sockaddr_in */
#include <netdb.h>	/* getaddrinfo() */
#include <string.h>	/* strlen() */
#include <unistd.h>	/* close() */

// for debug message
//#define DEBUG

extern void send_http_request_fixed( FILE *out, char *server, char *path);
extern	int get_txt_from_server( char *server, int portno, char *path);
extern  int echo_send_request( FILE *out, char *message );
extern  int echo_receive_reply( FILE *in, char buf[], int size );
extern	int tcp_connect( char *server, int portno );
extern  int fdopen_sock( int sock, FILE **inp, FILE **outp );

int main( int argc, char *argv[] ){
    char *server ;
    int portno ;
    char *path ;
    int err;
    if( argc != 4 )
    {
        fprintf( stderr,"Usage: %s host port 'message'\n",argv[0] );
        exit( -1 );
    }
    server  = argv[1] ;
    portno  = strtol( argv[2],0,10 );
    path = argv[3];

    err = get_txt_from_server(server, portno, path);
    return( err );
}

#define	BUFFERSIZE	1024

void send_http_request_fixed( FILE *out, char *server, char *path ) {
    fprintf(out, "GET %s HTTP/1.0\r\n", path);
    fprintf(out, "Host: %s\r\n", server);
    fprintf(out, "\r\n");
}

int get_txt_from_server( char *server, int portno, char *path){
    int sock ;
    FILE *in, *out ;
    char rbuf[BUFFERSIZE];
    int res;

    sock = tcp_connect( server, portno );
    if( sock<0 )
        return( 1 );
    if( fdopen_sock(sock,&in,&out) < 0 )
    {
        fprintf(stderr,"fdooen()\n");
        close( sock );
        return( 1 );
    }

    #ifdef DEBUG
    send_http_request_fixed(stdout, server, path);
    #endif

    send_http_request_fixed(out, server, path);

    #ifdef DEBUG
    printf("sent http get request to %s:%d\n", server, portno);
    #endif

    while(fgets(rbuf, BUFFERSIZE, in) != NULL){
        fputs(rbuf, stdout);
    }

    #ifdef DEBUG
    printf("recieved responce\n");
    #endif

    fclose( in );
    fclose( out );
    return( 0 );
}


#define PORTNO_BUFSIZE 30

int tcp_connect( char *server, int portno ) {
    struct addrinfo hints, *ai, *p;
    char portno_str[PORTNO_BUFSIZE];
    int s, err;
    snprintf( portno_str,sizeof(portno_str),"%d",portno );
    memset( &hints, 0, sizeof(hints) );
    hints.ai_socktype = SOCK_STREAM;
    if( (err = getaddrinfo( server, portno_str, &hints, &ai )) )
    {
        fprintf(stderr,"unknown server %s (%s)\n",server,
            gai_strerror(err) );
        goto error0;
    }
    for( p=ai ; p ; p=p->ai_next )
    {
        if( (s = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0 )
        {
            perror("socket");
            goto error1;
        }
        if( connect(s, p->ai_addr, p->ai_addrlen) >= 0 )
        {
            break;
        }
        else
        {
            close( s );
        }
    }
    freeaddrinfo( ai );
    return( s );
error1:
    freeaddrinfo( ai );
error0:
    return( -1 );
}

int fdopen_sock( int sock, FILE **inp, FILE **outp ) {
    int sock2 ;
    if( (sock2=dup(sock)) < 0 )
    {
        return( -1 );
    }
    if( (*inp = fdopen( sock2, "r" )) == NULL )
    {
        close( sock2 );
        return( -1 );
    }
    if( (*outp = fdopen( sock, "w" )) == NULL )
    {
        fclose( *inp );
        *inp = 0 ;
        return( -1 );
    }
    setvbuf(*outp, (char *)NULL, _IONBF, 0);
    return( 0 );
}

