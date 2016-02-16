﻿/* -------------------------------------------------------------------------- */
/* update_f.cpp																  */
/*																			  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							  日付		氏名			*/
/* -------------------------------------------------------------------------- */
/* 000000	新規作成								2016/02/16	葛巻 大樹	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル															  */
/* -------------------------------------------------------------------------- */
#include "define.h"
/* -------------------------------------------------------------------------- */
/* 関数名		: update													   */
/* 機能名		: 更新を行う												      */
/* 機能概要	   : 更新を行う													 */
/* 引数		 : SINT				: index			 : 更新を行うデータ			*/
/* 戻り値		: SINT			   : OK				: 正常終了				   */
/*             : SINT			  : ERR            : 異常終了				  */
/* 作成日		: 葛巻大樹							2016/02/16				   */
/* -------------------------------------------------------------------------- */
int update ( SINT index )
{
    struct BOOK data;
    memset( &data, 0, sizeof( data ) );
    bookread( &data, index );
    SINT updateNo = 0;
	if (index==99) {
		printf("項目は存在しません\n" );
		return ERR;
	}
    cls( );
    printf( "どの項目を修正しますか？\n" );
    menu_print( "名前" );
    menu_print( "カナ" );
    menu_print( "郵便番号" );
    menu_print( "住所" );
    menu_print( "電話番号" );
    updateNo = select( 5 );
    switch( updateNo ) {
        case 0:
            addname( &data );
            break;
        case 1:
            addkana( &data );
            break;
        case 2:
            addpost( &data );
            break;
        case 3:
            addaddress( &data );
            break;
        case 4:
            addnumber( &data );
            break;
        default:
            break;
    }
	bookwrite(&data,index);
	return OK;

}

/* -------------------------------------------------------------------------- */
/*              Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
