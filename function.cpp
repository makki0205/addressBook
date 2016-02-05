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
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int statusflash(struct STATUS* status){
	FILE* fp=0;
	fp=fopen("./status.dat","w");
	fwrite(status,11,1,fp);
	fclose(fp);
	return OK;
}
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int statusread(struct STATUS* status){
	FILE* fp=0;
	fp=fopen("./status.dat","r");
	fread(status,11,1,fp);
	fclose(fp);
	return OK;
}
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int select(int max){
	int val=0;
	int key=0;
	max -= 1;
	select_print(val,max);
	while (1) {
		key=getch();
		switch (key) {
		case 'w':
			(val!=0)?val--:val=max;
			select_print(val,max);
			break;
		case 's':
			(val!=max)?val++:val=0;
			select_print(val,max);
			break;
		case (10):
			return val;
		}
	}
}
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名	   	: 															   */
/* 機能概要	   : 															  */
/* 引数        : 					 : 				 : 							*/
/* 戻り値		: 					: 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
void select_print(int cursor,int max){
	int index = 0 ;
	for ( index = 0; index <= max; index++) {
		locate(index+2,0);
		(index==cursor)?printf("→"):printf("　");
	}
	locate(max+3,0);
}
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int menu_print(const char* item){
	/* 引数チェック---------------------------------------------------------- */
if ( item == NULL){
	return ERR;
}
	printf("　%s\n",item);
	return OK;
}
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int menu(struct BOOK* data){
	/* 引数チェック---------------------------------------------------------- */
if (data == NULL){
	return ERR;
}
	int selectNo=0;
	cls();
	printf("--アドレス帳--\n");
	menu_print("アドレス帳新規追加");
	menu_print("アドレス帳参照");
	menu_print("アドレス帳修正");
	menu_print("アドレス帳削除");
	menu_print("アドレス帳並び替え");
	menu_print("アプリケーション終了");
	selectNo=select(6);
	switch (selectNo) {
	case (0):adddata();
	}
	return 0;
}
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int bookread(struct BOOK* data ,int index){
	int size;
	FILE* fp;
	/* 引数チェック---------------------------------------------------------- */
if ( data== NULL){
	return ERR;
}
	size=sizeof(struct BOOK);
	fp=fopen("addressbook.dat","r");
	/* ファイルポインタcheck------------------------------------------------- */
	if (fp==0) {
		return ERR;
	}
	fread(data,size,1,fp);
	fclose(fp);
	return OK;
}
/* -------------------------------------------------------------------------- */
/* 関数名		: 															   */
/* 機能名		: 															   */
/* 機能概要	   : 															  */
/* 引数		 : 					: 				 : 							*/
/* 戻り値		: 				   : 				: 						   */
/* 作成日		: 															   */
/* -------------------------------------------------------------------------- */
int bookwrite(struct BOOK* data ,int index ){
	int size = 0;
	FILE* fp = 0;
	/* 引数チェック---------------------------------------------------------- */
	if ( data== NULL){
		return ERR;
	}
	size=sizeof( struct BOOK );
	fp = fopen ( "addressbook.dat" , "w" );
	/* ファイルポインタcheck------------------------------------------------- */
	if (fp==0) {
		return ERR;
	}
	fseek(fp,size*index,SEEK_SET);
	fwrite(data,size, 1 , fp );
	fclose(fp);
	return OK;
}
/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
