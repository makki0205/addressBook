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
/* 関数名		: 															   */
/* 機能名	   	: 															   */
/* 機能概要	   : 															  */
/* 引数        : 					 : 				 : 							*/
/* 戻り値		: 					: 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int main(int argc, char const *argv[]) {
	int i;
	struct BOOK data;
    memset(&data,0,sizeof(data));               /* 構造体初期化               */
    bookwrite(&data,4);

	// i = menu(&data);
	return 0;
}
/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
