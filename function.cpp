/* -------------------------------------------------------------------------- */
/* function.cpp																  */
/*																			  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							  日付		氏名			*/
/* -------------------------------------------------------------------------- */
/* 000000	  新規作成								2015/10/20	葛巻 大樹	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル															  */
/* -------------------------------------------------------------------------- */
#include "define.h"
/* -------------------------------------------------------------------------- */
/* 関数名		: systemset                                                    */
/* 機能名		: ファイルがなければ構築する                                   */
/* 機能概要	   : ファイルを作成                                               */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16             */
/* -------------------------------------------------------------------------- */
int systemset ( void )
{
    FILE         *fp;
    struct STATUS sta;
    memset( &sta, 0, sizeof( sta ) );
    fp = fopen( "addressbook.dat", "r" );
    if( fp == NULL ) {
        system( "touch addressbook.dat" );
        fp = fopen( "./status.dat", "w" );
        if( fp == NULL ) {
            return ERR;
        }
        fwrite( &sta, sizeof( sta ), 1, fp );
        fclose( fp );
    } else {
        fclose( fp );
    }

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: statuswrite                                                  */
/* 機能名		: ステータスを書く                                             */
/* 機能概要	   : ステータスを書く                                             */
/* 引数		 : STATUS*          : stats          : 構造体ポインタ           */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
int statuswrite ( struct STATUS *status )
{
    FILE *fp = 0;
    fp = fopen( "./status.dat", "w" );
    if( fp == NULL ) {
        return ERR;
    }
    fwrite( status, sizeof( struct STATUS ), 1, fp );
    fclose( fp );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: statusread                                                   */
/* 機能名		: ステータスを読む                                             */
/* 機能概要	   : ステータスを読み格納する                                     */
/* 引数		 : STATUS*          : stats          : 構造体ポインタ           */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
int statusread ( struct STATUS *status )
{
    FILE *fp = 0;
    fp = fopen( "./status.dat", "r" );
    if( fp == NULL ) {
        return ERR;
    }
    fread( status, sizeof( struct STATUS ), 1, fp );
    fclose( fp );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: select                                                       */
/* 機能名		: 選ぶ                                                         */
/* 機能概要	   : maxまでの値で矢印が動き選べる                                */
/* 引数		 : int              : max            : 最大値                   */
/* 戻り値		: SINT             : val            : 選ばれた値               */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
int select ( int max )
{
    SINT check = 0;
    int  val   = 0;
    int  key   = 0;
    max -= 1;
    select_print( val, max );
    while( 1 ) {
        key = getch( );
        switch( key ) {
            case 'w':
                ( val != 0 ) ? val-- : val = max;
                select_print( val, max );
                break;
            case 's':
                ( val != max ) ? val++ : val = 0;
                select_print( val, max );
                break;
            case ( 10 ):

                return val;
        }
    }
}

/* -------------------------------------------------------------------------- */
/* 関数名		: select_print                                                 */
/* 機能名	    : セレクタを印字                                               */
/* 機能概要	   : セレクタを印字する（→）                                     */
/* 引数        : int               : cursor        :                          */
/* 			   : int			   : max		   :						  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
void select_print ( int cursor, int max )
{
    int index = 0;
    for( index = 0 ; index <= max ; index++ ) {
        locate( index + 2, 0 );
        ( index == cursor ) ? printf( "→" ) : printf( "  " );
    }
    locate( max + 3, 0 );
}

/* -------------------------------------------------------------------------- */
/* 関数名		: menu_print                                                   */
/* 機能名		: メニューを印字                                               */
/* 機能概要	   : メニューをセレクト用に印字                                   */
/* 引数		 : const char*      : item           : 表示コンテンツ           */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
int menu_print ( const char *item )
{
    /* 引数チェック---------------------------------------------------------- */
    if( item == NULL ) {
        return ERR;
    }
    printf( "  %s\n", item );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: post_print                                                   */
/* 機能名		: 郵便番号をプリントする                                       */
/* 機能概要	   : 郵便番号をー付きで出力                                       */
/* 引数		 : char*            : post           : 郵便番号アドレス         */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
int post_print ( char *post )
{
    SINT check  = 0;
    int  index  = 0;
    int  barflg = 0;
    int  size   = 0;
    /* 引数チェック---------------------------------------------------------- */
    if( post == NULL ) {
        return ERR;
    }
    size = strlen( post );
    if( size >= 3 ) {
        barflg = 1;
    }
    locate( 3, 12 );
    for( index = 0 ; index < 3 ; index++ ) {
        printf( "%c", *post );
        post++;
    }
    if( barflg == 1 ) {
        printf( "-" );
    }
    printf( "%s", post );
    for( index = size ; index <= 7 ; index++ ) {
        printf( " " );
    }

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: menu                                                         */
/* 機能名		: アドレス帳メニュー                                           */
/* 機能概要	   : アドレス帳各種メニュー                                       */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
int menu ( void )
{
    int selectNo = 0;
    int check    = 0;
    cls( );
    printf( "--アドレス帳--\n" );
    menu_print( "アドレス帳新規追加" );
    menu_print( "アドレス帳参照" );
    menu_print( "アドレス帳修正" );
    menu_print( "アドレス帳削除" );
    menu_print( "アドレス帳並び替え" );
    menu_print( "アプリケーション終了" );
    selectNo = select( 6 );
    switch( selectNo ) {
        case 0:
            check = adddata( );
            if( check == ERR ) {
                return ERR;
            }
            break;
        case 1:
            check = viewdata( );
            if( check == ERR ) {
                return ERR;
            }
            break;
        case 2:
            check = viewdata( );
            if( check == ERR ) {
                return ERR;
            }
            check = update( check );
            if( check == ERR ) {
                return ERR;
            }
            locate( 10, 0 );
            break;
        case 3:
            check = viewdata( );
            if( check == ERR ) {
                return ERR;
            }
            check = deletedata( check );
            if( check == ERR ) {
                return ERR;
            }
            break;
        case 4:
			check=sortdata();
			if (check==ERR) {
				return ERR;
			}
            break;
        case 5: return 1;
    }
    printf( "何か押してください\n" );
    rewind( stdin );
    getch( );

    return 0;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: bookread                                                     */
/* 機能名		: BOOKデータを読む                                             */
/* 機能概要	   : index番目のデータを読む                                      */
/* 引数		 : STATUS*          : data           : 構造体ポインタ           */
/* 			   : int			  : index		   : 添え字				   */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
int bookread ( struct BOOK *data, int index )
{
    int   size;
    FILE *fp;
    /* 引数チェック---------------------------------------------------------- */
    if( data == NULL ) {
        return ERR;
    }
    size = sizeof( struct BOOK );
    fp   = fopen( "addressbook.dat", "r" );
    /* ファイルポインタcheck------------------------------------------------- */
    if( fp == 0 ) {
        return ERR;
    }
    fseek( fp, index * size, SEEK_SET );
    fread( data, size, 1, fp );
    fclose( fp );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: bookwrite                                                    */
/* 機能名		: BOOKデータを書く                                             */
/* 機能概要	   : index番目のデータを書く                                      */
/* 引数		 : STATUS*          : data           : 構造体ポインタ           */
/* 			   : int			  : index		   : 添え字				   */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/16                 */
/* -------------------------------------------------------------------------- */
int bookwrite ( struct BOOK *data, int index )
{
    int   size = 0;
    FILE *fp   = 0;
    /* 引数チェック---------------------------------------------------------- */
    if( data == NULL ) {
        return ERR;
    }
    size = sizeof( struct BOOK );
    fp   = fopen( "addressbook.dat", "r+" );
    /* ファイルポインタcheck------------------------------------------------- */
    if( fp == 0 ) {
        return ERR;
    }
    fseek( fp, size * index, SEEK_SET );
    fwrite( data, size, 1, fp );
    fclose( fp );

    return OK;
}

/* -------------------------------------------------------------------------- */
/*              Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
