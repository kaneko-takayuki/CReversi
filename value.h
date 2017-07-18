//評価関数用ヘッダ

//評価盤面
int value_table[N+2][N+2]={{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
			   {  0, 100, -20,   0,  -1,  -1,   0, -20, 100,   0},
			   {  0, -20, -40,  -2,  -2,  -2,  -2, -40, -20,   0},
			   {  0,   0,  -2,   0,  -1,  -1,   0,  -2,   0,   0},
			   {  0,  -1,  -2,  -1,  -1,  -1,  -1,  -2,  -1,   0},
			   {  0,  -1,  -2,  -1,  -1,  -1,  -1,  -2,  -1,   0},
			   {  0,   0,  -2,   0,  -1,  -1,   0,  -2,   0,   0},
			   {  0, -20, -40,  -2,  -2,  -2,  -2, -40, -20,   0},
			   {  0, 100, -20,   0,  -1,  -1,   0, -20, 100,   0},
			   {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}};

//評価盤面を更新する関数
void Change_Value_Table(int present_board[N+2][N+2])
{
  if(present_board[1][1]!=BLANK){
    value_table[1][2]=10;
    value_table[2][1]=10;
    value_table[2][2]=10;
  }
  if(present_board[1][8]!=BLANK){
    value_table[1][7]=10;
    value_table[2][8]=10;
    value_table[2][7]=10;
  }
  if(present_board[8][1]!=BLANK){
    value_table[7][1]=10;
    value_table[8][2]=10;
    value_table[7][2]=10;
  }
  if(present_board[8][8]!=BLANK){
    value_table[7][8]=10;
    value_table[8][7]=10;
    value_table[7][7]=10;
  }
}

//評価関数
int Judge(int judge_board[N+2][N+2], int color)
{
  int score=0; //得点

  switch(how_to_judge){
  case 0 : 
    score+=(W_VT*Judge_Table(judge_board, color));
    score+=(W_OL*Judge_Open_Level(judge_board, color));
    score+=(W_CP*Num_Can_Put(judge_board, color));
    score+=(W_ND*Num_Decision_Stone(judge_board, color));
    break;

  case 1 : 
    score+=Diff_Stone(judge_board, color);
    break;
  }

  if(Num_Stone(judge_board, color)==0)
     score=ALL_REVERSE; //自分の石が無くなってしまうならばこの分岐はダメだというフラグを返す。

  return score;
}

//評価テーブルの得点を返す
int Judge_Table(int judge_board[N+2][N+2], int color)
{
  int i, j;
  int score=0; //得点

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(judge_board[i][j]==color)
	score+=value_table[i][j];

  return score;
}

//解放度の得点を返す
//自分の石の周りにどれだけ空白があるか(解放されているか)
int Judge_Open_Level(int judge_board[N+2][N+2], int color)
{
  int i, j, k;
  int score=0; //得点
  int a[N+2][N+2]={{0}};

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(judge_board[i][j]==color)
	for(k=0; k<8; k++)
	  if(judge_board[i+dx[k]][j+dy[k]]==BLANK)
	    a[i][j]=1;

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(a[i][j]==1)
	score--;

  return score;
}

//着手可能数による得点を返す(自分-相手)
int Num_Can_Put(int judge_board[N+2][N+2], int color)
{
  int i, j;
  int mine=0, opponent=0; //自分と相手の着手可能数

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(judge_board[i][j]==color){
	if(Can_Put(judge_board, i, j, color)==1)
	  mine++;
      }
      else if(judge_board[i][j]==-color)
	if(Can_Put(judge_board, i, j, -color)==1)
	  opponent++;
  
  return (mine-opponent);
}

//確定石の得点(自分-相手)を返す
int Num_Decision_Stone(int judge_board[N+2][N+2], int color)
{
  return (Calculate_Num_Decision_Stone(judge_board, color)-Calculate_Num_Decision_Stone(judge_board, -color));

}

//辺の確定石の得点を返す
int Calculate_Num_Decision_Stone(int judge_board[N+2][N+2], int color)
{
  int i, j;
  int score=0;

  //左上からの確定石計算
  if(judge_board[1][1]==color){
    for(i=1; i<N+1; i++){
      if(judge_board[i][1]==color)
	score++;
      else
	break;
    }
    if(i==9)
      score-=9; //確定石重複補正

    for(j=1; j<N+1; j++){
      if(judge_board[1][j]==color)
	score++;
      else
	break;
    }
    if(j==9)
      score-=9; //確定石重複補正
  }

  //左下からの確定石計算
  if(judge_board[8][1]==color){
    for(i=N; i>0; i--){
      if(judge_board[i][1])
	score++;
      else
	break;
    }

    for(j=1; j<N+1; j++){
      if(judge_board[1][j]==color)
	score++;
      else
	break;
    }
    if(j==9)
      score-=9; //確定石重複補正
  }

  //右上からの確定石計算
  if(judge_board[1][8]==color){
    for(i=1; i<N+1; i++){
      if(judge_board[i][8]==color)
	score++;
      else
	break;
    }
    if(i==9)
      score-=9; //確定石重複補正

    for(j=N; j>0; j--){
      if(judge_board[1][j]==color)
	score++;
      else
	break;
    }
  }
  
  //右下からの確定石計算
  if(judge_board[8][8]==color){
    for(i=N; i>0; i--){
      if(judge_board[i][8]==color)
	score++;
      else
	break;
    }

    for(j=N; j>0; j--){
      if(judge_board[8][j]==color)
	score++;
      else
	break;
    }
  }
  
  return score;
}

//駒数の得点(自分-相手)を返す
int Diff_Stone(int judge_board[N+2][N+2], int color)
{
  int i, j;
  int mine=0, opponent=0; //自分と相手の石の個数

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(judge_board[i][j]==color)
	mine++;
      else if(judge_board[i][j]==-color)
	opponent++;

  return (mine-opponent);
}

//色colorの石の数を返す
int Num_Stone(int judge_board[N+2][N+2], int color)
{
  int i, j;
  int num=0; //石の数

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(judge_board[i][j]==color)
	num++;

  return num;
}
