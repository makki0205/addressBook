/* -------------------------------------------------------------------------- */
/* Main.cpp																	  */
/*																			  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							  日付		氏名			*/
/* -------------------------------------------------------------------------- */
/* 000		新規作成								2015/10/20	葛巻 大樹	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル															  */
/* -------------------------------------------------------------------------- */
#include "define.h"
/* -------------------------------------------------------------------------- */
/* 定数定義																	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* グローバル変数															   */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* プロトタイプ宣言(private)												  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* 関数名		: adddata                                                      */
/* 機能名	    : データの追加                                                 */
/* 機能概要	   : データを追加する                                             */
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大樹                          2016/02/1                  */
/* -------------------------------------------------------------------------- */
int adddata ( void )
{
    SINT          check            = 0;
    SINT          writing_position = -1;
    SINT          index            = 0;
    struct BOOK   data;
    struct STATUS sta;
    memset( &sta, 0, sizeof( sta ));
    memset( &data, 0, sizeof( data ));
    check = statusread( &sta );
    if( check == ERR ) {
        return ERR;
    }
    for( index = 0 ; index < 10 ; index++ ) {
        if( sta.flg[index] == 0 ) {
            writing_position = index;
            break;
        }
    }
    if( writing_position == -1 ) {
        printf( "これ以上追加できません。\n" );

        return 0;
    }
    check = statusread( &sta );
    if( check == ERR ) {
        return ERR;
    }
    check = addname( &data );
    if( check == ERR ) {
        return ERR;
    }
    check = addkana( &data );
    if( check == ERR ) {
        return ERR;
    }
    check = addpost( &data );
    if( check == ERR ) {
        return ERR;
    }
    check = addaddress( &data );
    if( check == ERR ) {
        return ERR;
    }
    check = addnumber( &data );
    if( check == ERR ) {
        return ERR;
    }
    check = bookwrite( &data, writing_position );
    if( check == ERR ) {
        return ERR;
    }
    sta.flg[writing_position] = 1;
    check                     = statuswrite( &sta );
    if( check == ERR ) {
        return ERR;
    }
    printf( "%d番目に追加しました\n", writing_position );

    return 0;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: record_print                                                 */
/* 機能名		: １レコードの出力                                             */
/* 機能概要	   : １レコードの出力                                             */
/* 引数		 : BOOK*            : data           : レコードのデータ			*/
/* 戻り値		: SINT             : OK             : 正常終了                 */
/* 			   :				  : NG			   : 異常終了				  */
/* 作成日		: 葛巻大                            2016/02/1                  */
/* -------------------------------------------------------------------------- */
int record_print ( struct BOOK *data )
{
    SINT check = 0;
    printf( "名前     : %s\n", &data->name[0] );
    printf( "カナ     : %s\n", &data->kana[0] );
    printf( "郵便番号 : " );
    check = post_print( &data->post[0] );
    if( check == ERR ) {
        return ERR;
    }
    printf( "\n住所     : %s\n", &data->address[0] );
    printf( "電話番号 : %s\n", &data->number[0] );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: addname													   */
/* 機能名		: 名前を追加													  */
/* 機能概要	   : を追加しcheckを行う                                          */
/* 引数		 : structBOOK*		: data			 : 一レコード分の情報       */
/* 戻り値		: int			   : OK				: 成功                     */
/* 作成日		: 葛巻大樹							2016/02/05				   */
/* -------------------------------------------------------------------------- */
int addname ( struct BOOK *data )
{
    SINT check = 0;
    char baf[256];
    int  size = 0;
	memset( &baf[0], 0, sizeof( baf ) );
    /* 引数チェック---------------------------------------------------------- */
    if( data == NULL ) {
        return ERR;
    }
    cls( );
    while( 1 ) {
        locate( 0, 0 );
        check = record_print( data );
        if( check == ERR ) {
            return ERR;
        }
        locate( 0, 12 );
        printf( "                                  " );
        locate( 0, 12 );
        gets( &baf[0] );
        size = strlen( &baf[0] );
        if( size < 30 ) {
            break;
        }
        cls( );
        locate( 7, 0 );
        printf( "30バイトで入力してください" );
    }
    strcpy( &data->name[0], &baf[0] );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: addkana													   */
/* 機能名		: カナを追加する                                               */
/* 機能概要	   : カナを追加しcheckを行う                                      */
/* 引数		 : structBOOK*		: data			 : 一レコード分の情報       */
/* 戻り値		: int			   : OK				: 成功                     */
/* 作成日		: 葛巻大樹							2016/02/05				   */
/* -------------------------------------------------------------------------- */
int addkana ( struct BOOK *data )
{
    int  size        = 0;
    int  check       = 0;
    int  returncheck = 0;
    int  index       = 0;
	char baf[256];
	memset( &baf[0], 0, sizeof( baf ) );
    /* 引数チェック---------------------------------------------------------- */
    if( data == NULL ) {
        return ERR;
    }
    cls( );
    while( 1 ) {
        locate( 0, 0 );
        returncheck = record_print( data );
        if( returncheck == ERR ) {
            return ERR;
        }
        locate( 2, 12 );
        printf( "                                  " );
        locate( 2, 12 );
        gets( &baf[0] );
        size = strlen( &baf[0] );
        if( size < 30 ) {
            // for (index = 0; index < size; index++) {
            //  if(baf[index]>='ｦ'&&baf[index]<'ﾟ'||
            //  baf[index]>='0'&&baf[index]<='9'||
            //  baf[index]>='a'&&baf[index]<='z'){
            //      check++;
            //  }else{
            //      break;
            //  }
            // }
            // if (size==check) {
            break;
            // }else{
            //  cls();
            //  locate(7,0);
            //  printf("使えない文字が含まれています");
            // }
        } else {
            cls( );
            locate( 7, 0 );
            printf( "30バイトで入力してください" );
        }
    }
    strcpy( &data->kana[0], &baf[0] );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: addpost													   */
/* 機能名		: 郵便番号を追加                                               */
/* 機能概要	   : 郵便番号を追加しcheckを行								    */
/* 引数		 : structBOOK*		: data			 : 一レコード分の情報       */
/* 戻り値		: int			   : OK				: 成功                     */
/* 作成日		: 葛巻大樹							2016/02/05				   */
/* -------------------------------------------------------------------------- */
int addpost ( struct BOOK *data )
{
    SINT check = 0;
    int  key   = 0;
    char baf[8];
    memset( &baf[0], 0, sizeof( baf ));
    int index = 0;
    cls( );
    check=record_print( data );
	if (check==ERR) {
		return ERR;
	}
    while( 1 ) {
        key = getch( );
        if(( key >= 48) && (key <= 57) && (index < 7) ) {
            baf[index] = key;
            check=post_print( &baf[0] );
			if (check==ERR) {
				return ERR;
			}
            index++;
        }
        if( (key == 10) && (index == 7) ) { break; }
    }
    strcpy( &data->post[0], &baf[0] );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: addaddress												   */
/* 機能名		: 住所を追加													  */
/* 機能概要	   : 住所を追加しcheckを行う										 */
/* 引数		 : structBOOK*		: data			 : 一レコード分の情報       */
/* 戻り値		: int			   : OK				: 成功                     */
/* 作成日		: 葛巻大樹							2016/02/05				   */
/* -------------------------------------------------------------------------- */
int addaddress ( struct BOOK *data )
{
	SINT check=0;
    int  size = 0;
	char baf[256];
	memset( &baf[0], 0, sizeof( baf ) );
    /* 引数チェック---------------------------------------------------------- */
    if( data == NULL ) {
        return ERR;
    }
    cls( );
    while( 1 ) {
        locate( 0, 0 );
        check=record_print( data );
		if (check==ERR) {
			return ERR;
		}
        locate( 4, 12 );
        printf( "                                  " );
        locate( 4, 12 );
        gets( &baf[0] );
        size = strlen( &baf[0] );
        if( size < 80 ) {
            break;
        }
        cls( );
        locate( 7, 0 );
        printf( "80バイトで入力してください" );
    }
    strcpy( &data->address[0], &baf[0] );

    return OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		: addnumber													   */
/* 機能名		: 電話番号を追加											    */
/* 機能概要	   : 電話番号を追加しcheckを行う                                  */
/* 引数		 : structBOOK*		: data			 : 一レコード分の情報       */
/* 戻り値		: int			   : OK				: 成功                     */
/* 作成日		: 葛巻大樹							2016/02/05				   */
/* -------------------------------------------------------------------------- */
int addnumber ( struct BOOK *data )
{
	SINT check=0;
    int  size = 0;
	char baf[256];
	memset( &baf[0], 0, sizeof( baf ) );
    /* 引数チェック---------------------------------------------------------- */
    if( data == NULL ) {
        return ERR;
    }
    cls( );
    while( 1 ) {
        locate( 0, 0 );
        check=record_print( data );
		if (check==ERR) {
			return ERR;
		}
        locate( 5, 12 );
        printf( "                                  " );
        locate( 5, 12 );
        gets( &baf[0] );
        size = strlen( &baf[0] );
        if( size < 18 ) {
            break;
        }
        cls( );
        locate( 7, 0 );
        printf( "18バイトで入力してください" );
    }
    strcpy( &data->number[0], &baf[0] );

    return OK;
}

/* -------------------------------------------------------------------------- */
/*              Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
