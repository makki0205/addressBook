﻿/* -------------------------------------------------------------------------- */
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
/* 関数名		:                                                              */
/* 機能名		: ファイルがなければ構築する                                   */
/* 機能概要	   : ファイルを作成                                               */
/* 引数		 :                  :                :							*/
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
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
		if (fp==NULL) {
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
/* 関数名		:                                                              */
/* 機能名		:                                                              */
/* 機能概要	   :                                                              */
/* 引数		 :                  :                :                          */
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
/* -------------------------------------------------------------------------- */
int statuswrite ( struct STATUS *status )
{
    FILE *fp = 0;
    fp = fopen( "./status.dat", "w" );
	if (fp==NULL) {
		return ERR;
	}
    fwrite( status, sizeof( struct STATUS ), 1, fp );
    fclose( fp );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		:                                                              */
/* 機能名		:                                                              */
/* 機能概要	   :                                                              */
/* 引数		 :                  :                :                          */
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
/* -------------------------------------------------------------------------- */
int statusread ( struct STATUS *status )
{
    FILE *fp = 0;
    fp = fopen( "./status.dat", "r" );
	if (fp==NULL) {
		return ERR;
	}
    fread( status, sizeof( struct STATUS ), 1, fp );
    fclose( fp );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		:                                                              */
/* 機能名		:                                                              */
/* 機能概要	   :                                                              */
/* 引数		 :                  :                :                          */
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
/* -------------------------------------------------------------------------- */
int select ( int max )
{
	SINT check=0;
    int val = 0;
    int key = 0;
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
/* 関数名		:                                                              */
/* 機能名	    :                                                              */
/* 機能概要	   :                                                              */
/* 引数        :                   :               :                          */
/* 戻り値		:                   :               :                          */
/* 作成日		:                                                              */
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
/* 関数名		:                                                              */
/* 機能名		:                                                              */
/* 機能概要	   :                                                              */
/* 引数		 :                  :                :                          */
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
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
/* 関数名		:                                                              */
/* 機能名		:                                                              */
/* 機能概要	   :                                                              */
/* 引数		 :                  :                :                          */
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
/* -------------------------------------------------------------------------- */
int post_print ( char *post )
{
	SINT check=0;
    int index  = 0;
    int barflg = 0;
    int size   = 0;
	/* 引数チェック---------------------------------------------------------- */
	if (post == NULL){
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
/* 関数名		:                                                              */
/* 機能名		:                                                              */
/* 機能概要	   :                                                              */
/* 引数		 :                  :                :                          */
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
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
            check=adddata( );
			if (check==ERR) {
				return ERR;
			}
            break;
        case 1:
            check=viewdata( );
			if (check==ERR) {
				return ERR;
			}
            break;
        case 2:
			check=viewdata( );
			if (check==ERR) {
				return ERR;
			}
			check=update(check);
			if (check==ERR) {
				return ERR;
			}
			locate(10,0);
            break;
        case 3:
		check=viewdata();
		if (check==ERR) {
			return ERR;
		}
		check=deletedata(check);
		if (check==ERR) {
			return ERR;
		}
            break;
        case 4:
            break;
        case 5: return 1;
    }
    printf( "何か押してください\n" );
    rewind( stdin );
    getch( );

    return 0;
}

/* -------------------------------------------------------------------------- */
/* 関数名		:                                                              */
/* 機能名		:                                                              */
/* 機能概要	   :                                                              */
/* 引数		 :                  :                :                          */
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
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
/* 関数名		:                                                              */
/* 機能名		:                                                              */
/* 機能概要	   :                                                              */
/* 引数		 :                  :                :                          */
/* 戻り値		:                  :                :                          */
/* 作成日		:                                                              */
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
