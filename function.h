//ゲーム進行用ヘッダ

//(x,y)から方向iにひっくり返せるかどうか
int Can_Reverse(int search_board[N+2][N+2], int x, int y, int i, int color)
{
  if(search_board[x][y]==BLANK || search_board[x][y]==WALL)
    return 0; //ひっくり返せない
  if(search_board[x][y]==color)
    return 1; //ひっくり返せる

  //今注目しているマスに相手の石がある場合、i方向に探索を延ばす
  if(Can_Reverse(search_board, x+dx[i], y+dy[i], i, color)==1)
    return 1; //先を見た結果、ひっくり返せた
  else
    return 0; //先を見た結果
}

//(x,y)に石colorを置けるかどうか
int Can_Put(int search_board[N+2][N+2], int x, int y, int color)
{
  int i;

  //(x,y)に石があったら置けない
  if(search_board[x][y]!=BLANK)
    return 0;

  //8方向をループ
  for(i=0; i<8; i++)
    if(search_board[x+dx[i]][y+dy[i]]==-color) //置く石と違う種類の石が8方向にあったとき
      if(Can_Reverse(search_board, x+dx[i], y+dy[i], i, color)==1) //裏返せたら
	return 1; //1を返す

  return 0; //ひっくり返せなかった
}

//盤面上に置ける手があるかどうか
int Can_Put_Board(int search_board[N+2][N+2], int color)
{
  int i, j;

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(search_board[i][j]==BLANK)
	if(Can_Put(search_board, i, j, color)==1) //一つでも置ける場所があったら
	  return 1; //1を返す

  return 0; //置ける場所が無かった
}

//盤面を表示させる関数
//置ける場所があったら1を返す
int Print_Board(int print_board[N+2][N+2], int color)
{
  int i, j;
  int put_flag=0; //置けるかどうかを示すフラグ

  printf(" 縦/横 1 2 3 4 5 6 7 8 \n"); //横方向の盤面を表す数字
  for(i=1; i<N+1; i++){
    printf("   %c   ", '0'+i); //縦方向の盤面を表す数字
    for(j=1; j<N+1; j++)
      if(print_board[i][j]==BLACK_STONE)
	printf("●︎ "); //黒
      else if(print_board[i][j]==WHITE_STONE)
	printf("○ "); //白
      else if(Can_Put(print_board, i, j, color)==1){
	printf("✴︎︎︎ "); //置ける場所
	put_flag=1;
      }
      else
	printf("_ "); //何も無い場所
    puts("");
  }
  return put_flag;
}

//方向iに向かってひっくり返す
int Reverse(int reverse_board[N+2][N+2], int x, int y, int i, int color)
{
  if(reverse_board[x][y]==BLANK || reverse_board[x][y]==WALL) //探索先が空白でひっくりかえせない
    return 0;
  if(reverse_board[x][y]==color) //探索先が置く石と同じでひっくり返せる
    return 1;

  //相手の石があるとき、探索をi方向に延ばす
  if(Reverse(reverse_board, x+dx[i], y+dy[i], i, color)==1){
    reverse_board[x][y]=color; //探索を延ばした結果、ひっくり返せた
    return 1;
  }
  else
    return 0; //探索を延ばした結果、ひっくり返せなかった
}

//(x,y)に石を置く
int Put(int put_board[N+2][N+2], int x, int y, int color)
{
  int i;

  if(Can_Put(put_board, x, y, color)==0)
    return 0; //置けないとき

  put_board[x][y]=color; //board[x][y]に石colorを置く

  //8方向に石を返していく
  for(i=0; i<8; i++)
    Reverse(put_board, x+dx[i], y+dy[i], i, color);
  
  return 1; //置けた
}

//対人用
void Play_Game_Player(void)
{
  int turn=1; //現在のターン
  int num_stone=4; //石の数
  int x, y;
  int exflag=0; //前のターンに置ける場所があったかどうか

  do{
    //先手(黒)の処理
    if(turn%2==1){
      puts("【黒の番】");
      if(Print_Board(board, BLACK_STONE)==1){ //盤面の表示
	exflag=1; //置ける場所があった
	puts("どこに置く？");
	printf("縦の座標 : "); scanf("%d", &x);
	printf("横の座標 : "); scanf("%d", &y);
	if(Put(board, x, y, BLACK_STONE)==1){ //置く
	  turn++; //ターンを進める
	  num_stone++; //石の数のインクリメント
	}
	else
	  printf("\a縦座標%d, 横座標%dには置けません！！！\n", x, y);
      }
      else{
	puts("【黒は置けません】");
	if(exflag==0)
	  break; //両者置けない
	exflag=0; //置けなかったフラグを立てる
	turn++; //ターンを進める
      }
    }
    else{
      puts("【白の番】");
      if(Print_Board(board, WHITE_STONE)==1){ //盤面の表示
	exflag=1; //置ける場所があった
	puts("どこに置く？");
	printf("縦の座標 : "); scanf("%d", &x);
	printf("横の座標 : "); scanf("%d", &y);
	if(Put(board, x, y, WHITE_STONE)==1){ //置く
	  turn++; //ターンを進める
	  num_stone++; //石の数のインクリメント
	}
	else
	  printf("\a縦座標%d, 横座標%dには置けません！！！\n", x, y);
      }
      else{
	puts("【白は置けません】");
	if(exflag==0)
	  break; //両者置けない
	exflag=0; //置けないフラグを立てる
	turn++; //ターンを進める
      }
    }
  }while(num_stone!=64);

  Print_Board(board, BLACK_STONE); //最終盤面の表示
  Print_Result(); //結果表示
}

//対CPU用
void Play_Game_CPU(void)
{
  int turn=1; //現在のターン
  int num_stone=4; //石の数
  int x, y;
  int exflag=0; //前のターンに置ける場所があったかどうか
  int first; //1ならプレイヤー先攻
  char g; //噛ませ

  srand(time(NULL)); //乱数の種を生成

  do{
    printf("【レベル設定】レベル1…1 / レベル2…2 / レベル3…3 / レベル4…4 : ");
    scanf("%d", &level);
  }while(level<1 || 4<level);

  do{
    printf("プレイヤー先攻…1 / プレイヤー後攻…0 / ランダム…2 : ");
    scanf("%d", &first);
  }while(first<0 || 2<first);

  //ランダムが選ばれたとき、firstを0か1にランダムに設定
  if(first==2)
    first=rand()%2;

  if(first==1)
    puts("【あなたは黒です】");
  else
    puts("【あなたは白です】");

  do{
    if(turn%2==1){
      puts("【黒の番】");
      if(Print_Board(board, BLACK_STONE)==1){ //盤面の表示
        exflag=1; //置ける場所があった

#if useCPU
	first=0; //useCPUがONになっていたらfirstに0を格納して手をCPUに選ばせる
#if EXPERIENCE
       	scanf("%c", &g);
#endif
#endif

	if(first==1){ //プレイヤー
	  puts("どこに置く？");
	  printf("縦の座標 : "); scanf("%d", &x);
	  printf("横の座標 : "); scanf("%d", &y);
	}
	else //CPU
	  CPU_Decision(board, &x, &y, BLACK_STONE, num_stone);

        if(Put(board, x, y, BLACK_STONE)==1){ //置く
	  printf("縦座標%d, 横座標%dに置きました\n", x, y);
          num_stone++; //石の数のインクリメント
	  turn++;
        }
        else
          printf("\a縦座標%d, 横座標%dには置けません！！！\n", x, y);
      }
      else{
        puts("【黒は置けません】");
        if(exflag==0)
          break; //両者置けない
        exflag=0; //置けなかったフラグを立てる
	turn++;
      }
    }
    else{
      puts("【白の番】");
      if(Print_Board(board, WHITE_STONE)==1){ //盤面の表示
        exflag=1; //置ける場所があった

#if useCPU
	first=1; //useCPUがONになっていたらfirstに1を格納して手をCPUに選ばせる
#if EXPERIENCE
       	scanf("%c", &g);
#endif
#endif

	if(first==0){ //プレイヤー
        puts("どこに置く？");
        printf("縦の座標 : "); scanf("%d", &x);
        printf("横の座標 : "); scanf("%d", &y);
	}
	else //CPU
	  CPU_Decision(board, &x, &y, WHITE_STONE, num_stone);

        if(Put(board, x, y, WHITE_STONE)==1){ //置く
	  printf("縦座標%d, 横座標%dに置きました\n", x, y);
          num_stone++; //石の数のインクリメント
	  turn++; //ターンのインクリメント
        }
        else
          printf("\a縦座標%d, 横座標%dには置けません！！！\n", x, y);
      }
      else{
        puts("【白は置けません】");
        if(exflag==0)
          break; //両者置けない
        exflag=0; //置けないフラグを立てる
	turn++;
      }
    }
    if(num_stone==LAST_SPART) //ラストスパートをかける
      how_to_judge=1; //評価方法を切り替える
    Change_Value_Table(board);
  }while(num_stone!=64);

  Print_Board(board, BLACK_STONE); //最終盤面の表示
  Print_Result(); //結果表示
}

void Print_Result(void)
{
  int black=0, white=0;
  int i, j;

  //盤面上の黒と白の数を数える
  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(board[i][j]==BLACK_STONE)
	black++; //黒が置かれていた
      else if(board[i][j]==WHITE_STONE)
	white++;

  if(black>white)
    printf("-%d対%dで黒の勝ち！！-\n", black, white);
  else if(black<white)
    printf("-%d対%dで白の勝ち！！-\n", black, white);
  else
    printf("-%d対%dで引き分け！！-\n", black, white);
}
