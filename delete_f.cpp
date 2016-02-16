﻿/* -------------------------------------------------------------------------- */
/* delete_f.cpp																  */
/*																			  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							  日付		氏名			*/
/* -------------------------------------------------------------------------- */
/* 000		新規作成								2016/02/16	葛巻 大樹	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル															  */
/* -------------------------------------------------------------------------- */
#include "define.h"

/* -------------------------------------------------------------------------- */
/* 関数名		: delete													   */
/* 機能名		: データの削除                                                 */
/* 機能概要	   : データを削除する											  */
/* 引数		 : SINT				: index			 : 削除するデータの情報	  */
/* 戻り値		: SINT			   : OK				: 正常終了				   */
/*             : SINT			  : ERR            : 異常終了				  */
/* 作成日		: 葛巻大樹							2016/02/16				   */
/* -------------------------------------------------------------------------- */
int deletedata ( SINT index )
{
    SINT          check = 0;
    struct STATUS sta;
    memset( &sta, 0, sizeof( sta ) );
    check = statusread( &sta );
    if( check == ERR ) {
        return ERR;
    }
    if( index == 99 && sta.flg[index] == 0 ) {
        printf( "データは存在しません\n" );
    } else {
        printf( "%d番目のデータを削除しました\n", index );
        sta.flg[index] = 0;
        check          = statuswrite( &sta );
        if( check == ERR ) {
            return ERR;
        }
    }

    return OK;
}

/* -------------------------------------------------------------------------- */
/*              Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
