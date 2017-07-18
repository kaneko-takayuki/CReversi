//実行用プログラム

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"definition.h" //関数宣言用ヘッダ
#include"function.h" //ゲーム進行用ヘッダ
#include"value.h" //評価用ヘッダ
#include"CPU.h" //CPU用ヘッダ

int main(void)
{
  int i;
  int mode; //対戦モード

  //初期配置
  board[4][5]=board[5][4]=BLACK_STONE; //黒い石を置く
  board[4][4]=board[5][5]=WHITE_STONE; //白い石を置く
  for(i=0; i<10; i++){
    board[0][i]=WALL;
    board[9][i]=WALL;
    board[i][0]=WALL;
    board[i][9]=WALL;
  }

  puts("【モードを選んでください】");
  printf("対人戦…0 / CPU戦…1 : ");
  scanf("%d", &mode);

  if(mode==0)
    Play_Game_Player(); //対人戦開始
  else if(mode==1){
    Play_Game_CPU(); //CPU戦開始
  }
  else{
    puts("\a対象外の数字です");
    exit(EXIT_FAILURE);
  }

  return 0;
}
