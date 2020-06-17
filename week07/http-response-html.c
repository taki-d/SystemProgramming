
/*
 * http-response-html.c -- HTTPの応答を画面に表示する(.html専用、枠組みだけ)
 * ~yas/syspro/ipc/http-response-html.c
 */

#include <stdio.h>  /* fprintf() */
#include <stdlib.h> /* exit() */
#include <string.h> /* strrchr() */

extern void http_send_reply( FILE *out, char *filename );
extern void http_send_reply_bad_request( FILE *out );
extern void http_send_reply_not_found( FILE *out );

int
main( int argc, char *argv[] )
{
	char *filename;

	if( argc != 2 ) {
		fprintf(stderr,"Usage: %s filename\n",argv[0] );
		exit( 1 );
	}
	filename = argv[1];
	http_send_reply( stdout, filename );
}

void
http_send_reply( FILE *out, char *filename )
{
	char *ext;

	ext = strrchr( filename, '.' );
	if( ext == NULL )
	{
		http_send_reply_bad_request( out );
		return;
	}
	else if( strcmp( ext,".html" ) == 0 )
	{
		printf("filename is [%s], and extention is [%s].\n", 
		       filename, ext);
		/*
		 * "Change this" を含めてこの部分を修正する。
		 * snprintf() 等でファイル名を作成する。
		 * fopen()  等でファイルを開く。
		 * ファイルが存在しなければ、http_send_reply_not_found() でエラーを送信する。
		 * ファイルが存在すれば、fread() 等で読み、その内容をfwrite() 等で out に書き込み送信する。
		 * fclose() 等でファイルを閉じる。
		 */
		fprintf(out,"Change this.\n");
		return;
	}
	else
	{
		http_send_reply_bad_request( out );
		return;
	}
}

void
http_send_reply_bad_request( FILE *out )
{
	fprintf(out,"HTTP/1.0 400 Bad Request\r\nContent-Type: text/html\r\n\r\n");
    	fprintf(out,"<html><head></head><body>400 Bad Request</body></html>\n");
}

void
http_send_reply_not_found( FILE *out )
{
	fprintf(out,"HTTP/1.0 404 Not Found\r\nContent-Type: text/html\r\n\r\n");
    	fprintf(out,"<html><head></head><body>404 Not Found</body></html>\n");
}
