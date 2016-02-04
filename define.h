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
#include "ktconio.h"
/* -------------------------------------------------------------------------- */
/* 定数定義																	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* 構造体定義																 */
/* -------------------------------------------------------------------------- */
#ifndef __STRUCT__
#define __STRUCT__
struct BOOK
{
	SCHR name[30];
	SCHR kana[30];
	SCHR post[8];
	SCHR address[80];
	SCHR number[18];
};
struct STATUS
{
	SCHR size;
	SCHR flg[10];
};
#endif

/* -------------------------------------------------------------------------- */
/* プロトタイプ宣言(private)												  */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int select(int max);
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名	   	: 															   */
/* 機能概要	   : 															  */
/* 引数        : 					 : 				 : 							*/
/* 戻り値		: 					: 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
void select_print(int cursor,int max);
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int menu_print(const char* item);
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int menu(struct BOOK* data);
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int adddata(void);
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int statusflash(struct STATUS* status);
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int statusread(struct STATUS* status);
/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
