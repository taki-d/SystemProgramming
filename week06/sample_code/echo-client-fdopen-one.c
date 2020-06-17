/*
  echo-client-fdopen-one.c -- 文字列を送受信するクライアント(TCP/IP版)
  ~yas/syspro/ipc/echo-client-fdopen-one.c
  Created on: 2009/06/01 21:13:38
*/
#include <stdio.h>
#include <stdlib.h>	/* exit() */
#include <string.h>	/* memset(), memcpy() */
#include <sys/types.h>	/* socket() */
#include <sys/socket.h>	/* socket() */
#include <netinet/in.h>	/* struct sockaddr_in */
#include <netdb.h>	/* getaddrinfo() */
#include <string.h>	/* strlen() */
#include <unistd.h>	/* close() */

extern	int echo_client_one( char *server, int portno, char *message );
extern  int echo_send_request( FILE *out, char *message );
extern  int echo_receive_reply( FILE *in, char buf[], int size );
extern	int tcp_connect( char *server, int portno );
extern  int fdopen_sock( int sock, FILE **inp, FILE **outp );

int
main( int argc, char *argv[] )
{
	char *server ;
	int portno ;
	char *message ;
	int err;
	if( argc != 4 )
	{
		fprintf( stderr,"Usage: %s host port 'message'\n",argv[0] );
		exit( -1 );
	}
	server  = argv[1] ;
	portno  = strtol( argv[2],0,10 );
	message = argv[3];
	err = echo_client_one( server, portno, message );
	return( err );
}

#define	BUFFERSIZE	1024

int
echo_client_one( char *server, int portno, char *message )
{
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
	res = echo_send_request( out, message );
	if( res < 0 )
	{
		fprintf(stderr,"fprintf()\n");
		fclose( in );
		fclose( out );
		return( 1 );
	}
	printf("sent: %d bytes [%s\n]\n",res,message );
	res = echo_receive_reply( in, rbuf, BUFFERSIZE );
	if( res < 0 )
	{
		fprintf(stderr,"fprintf()\n");
		fclose( in );
		fclose( out );
		return( 1 );
	}
	printf("received: %d bytes [%s]\n", res, rbuf );
	fclose( in );
	fclose( out );
	return( 0 );
}

int
echo_send_request( FILE *out, char *message )
{
	int res;
	res = fprintf( out, "%s\n", message ); /* send a request with '\n' */
	return( res );
}

int
echo_receive_reply( FILE *in, char buf[], int size )
{
	char *res;
	res = fgets( buf, size, in ); /* receive a reply message */
	if( res )
		return( strlen(buf) );
	else
		return( -1 );
}

/* 新城、筑波大学／情報学類／システムプログラム講義用 */
#define PORTNO_BUFSIZE 30

int
tcp_connect( char *server, int portno )
{
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

int
fdopen_sock( int sock, FILE **inp, FILE **outp )
{
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
