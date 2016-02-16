/* -------------------------------------------------------------------------- */
/* view_f.cpp																  */
/*																			  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							  日付		氏名			*/
/* -------------------------------------------------------------------------- */
/* 000		新規作成								2015/2/13	葛巻 大樹	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル															  */
/* -------------------------------------------------------------------------- */
#include "define.h"

/* -------------------------------------------------------------------------- */
/* 関数名		: viewdata													   */
/* 機能名		: データ参照												      */
/* 機能概要	   : データ参照用のメイン関数									  */
/* 戻り値		:                  :                :                          */
/* 作成日		: 葛巻大樹							2016/02/13				   */
/* -------------------------------------------------------------------------- */
int viewdata ( void )
{
    SINT selectNo = 0;
    SINT index    = 0;
    cls( );
    printf( "--何で検索しますか？\n" );
    menu_print( "番後" );
    menu_print( "カナ" );
    menu_print( "郵便番号" );
    selectNo = select( 3 );
    switch( selectNo ) {
        case 0:
            index = index_find( );
            if( index == -1 ) {
                return ERR;
            }
            break;
        case 1:
            index = kana_find( );
            if( index == -1 ) {
                return ERR;
            }
            break;
        case 2:
            index = post_find( );
            if( index == -1 ) {
                return ERR;
            }
            break;
        default:
            break;
    }

    return index;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: index_find												   */
/* 機能名		: 番号検索													   */
/* 機能概要	   : 番号こ検索を行う											  */
/* 戻り値		: int			   : index			: 番号を返す			      */
/* 作成日		: 葛巻大樹							2016/02/16				   */
/* -------------------------------------------------------------------------- */
int index_find ( void )
{
    SINT          index;
    struct BOOK   data;
    struct STATUS sta;
    memset( &data, 0, sizeof( data ) );
    memset( &sta, 0, sizeof( sta ) );
    statusread( &sta );
    cls( );
    printf( "検索 : " );
    scanf( "%d", &index );
	if (sta.flg[index]==1) {
		bookread(&data,index);
		view_print(&data);
	}else{
		index =99;
	}

    return index;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: view_print                                                   */
/* 機能名		: データを印字                                                 */
/* 機能概要	   : 一人分のデータを印字                                         */
/* 引数		 : struct BOOK*     : data           :	データの先頭アドレス    */
/* 戻り値		:                  :                :                          */
/* 作成日		: 葛巻大樹                           2016/02/14                */
/* -------------------------------------------------------------------------- */
int view_print ( struct BOOK *data )
{
    printf( "名前     : %s\n", &data->name[0] );
    printf( "カナ     : %s\n", &data->kana[0] );
    printf( "郵便番号 : %c%c%c-%s", data->post[0], data->post[1], data->post[2], &data->post[3] );
    printf( "\n住所     : %s\n", &data->address[0] );
    printf( "電話番号 : %s\n", &data->number[0] );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: kana_find													   */
/* 機能名		: カナ検索を行う											    */
/* 機能概要	   : カナ検索を行って表示する									  */
/* 戻り値		:                  :                :                          */
/* 作成日		: 葛巻大樹							2016/02/15				   */
/* -------------------------------------------------------------------------- */
int kana_find ( void )
{
    SINT          index = 0;
    SINT          check = 0;
    SINT          flg   = 0;
    SCHR          buf[100];
    struct BOOK   data[10];
    struct STATUS sta;
    memset( &data[0], 0, sizeof( data ) );
    memset( &sta, 0, sizeof( sta ) );
    statusread( &sta );
    for( index = 0 ; index < 10 ; index++ ) {
        if( sta.flg[index] == 1 ) {
            bookread( &data[index], index );
        }
    }
    cls( );
    printf( "検索： " );
    scanf( "%s", &buf[0] );
    for( index = 0 ; index < 10 ; index++ ) {
        check = strncmp( &buf[0], &data[index].kana[0], strlen( &buf[0] ) );
        if( check == 0 ) {
            flg = 1;
            break;
        }
    }
    if( flg == 0 ) {
        printf( "見つかりませんでした\n" );

        return 99;
    } else {
        view_print( &data[index] );
    }

    return index;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: post_find													   */
/* 機能名		: 郵便番号検索を行う											  */
/* 機能概要	   : 郵便番号検索を行って表示する								    */
/* 引数		 :                  :                :							*/
/* 戻り値		:                  :                :                          */
/* 作成日		: 葛巻大樹							2016/02/15				   */
/* -------------------------------------------------------------------------- */
int post_find ( void )
{
    SINT key       = 0;
    SINT index     = 0;
    SINT findindex = 0;
    SCHR buf[8];
    memset( &buf[0], 0, sizeof( buf ) );
    view_post_print( &buf[0] );
    while( 1 ) {
        key = getch( );
        if( key <= '9' && key >= '0' && index < 7 ) {
            buf[index] = key;
            index++;
            view_post_print( &buf[0] );
        }
        if( key == 127 && index != 0 ) {
            index--;
            buf[index] = '\0';
            view_post_print( &buf[0] );
        }
        if( key == 10 ) {
            findindex = view_post_print( &buf[0] );
            break;
        }
    }

    return findindex;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: view_post_print											   */
/* 機能名		: 参照画面の郵便リアルタイム検索実装						      */
/* 機能概要	   :                                                              */
/* 引数		 : SCHR*			: data			 : データ先頭アドレス　　　	*/
/* 戻り値		:                  :                :                          */
/* 作成日		: 葛巻大樹							2016/02/15				   */
/* -------------------------------------------------------------------------- */
int view_post_print ( SCHR *buf )
{
    SINT          index     = 0;
    SINT          check     = 0;
    SINT          findindex = 99;
    struct BOOK   data;
    struct STATUS sta;
    memset( &data, 0, sizeof( data ) );
    memset( &sta, 0, sizeof( sta ) );
    statusread( &sta );
    cls( );
    locate( 0, 0 );
    printf( "検索 : " );
    if( *buf != 0 ) {
        printf( "%s", buf );
        for( index = 0 ; index < 10 ; index++ ) {
            if( sta.flg[index] == 1 ) {
                bookread( &data, index );
                check = strncmp( buf, &data.post[0], strlen( buf ) );
                if( check == 0 ) {
                    if( findindex == 99 ) {
                        findindex = index;
                    }
                    printf( "\n" );
                    view_print( &data );
                }
            }
        }
    } else {
        for( index = 0 ; index < 10 ; index++ ) {
            if( sta.flg[index] == 1 ) {
                bookread( &data, index );
                printf( "\n" );
                view_print( &data );
            }
        }
    }

    return findindex;
}

/* -------------------------------------------------------------------------- */
/*              Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
