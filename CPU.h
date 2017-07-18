//CPU用ヘッダ

void Copy_Board(int copied_board[N+2][N+2], int copy_board[N+2][N+2])
{
  int i, j;

  for(i=0; i<N+2; i++)
    for(j=0; j<N+2; j++)
      copied_board[i][j]=copy_board[i][j];
}

//選択ソートによってpoint型配列をn個分降順にソート
void Selection_Sort(point a[QUE_MAX], int n)
{
  int i, j, k;
  point tmp;

  for(i=0; i<n-1; i++){
    k=i;
    for(j=k+1; j<n; j++){
      if(a[k].val<a[j].val){
        k=j;
      }
    }
    tmp=a[k];
    a[k]=a[i];
    a[i]=tmp;
  }
}

void CPU_Decision(int present_board[N+2][N+2], int *x, int *y, int color, int num_stone)
{
  int tmp_board[N+2][N+2]; //シュミレーション用
  int i, j;
  point a[QUE_MAX]; //探索候補を格納する配列
  int head=0, tail=0; //探索候補キューaの先頭と末尾
  int max=-10000; //探索先の最適値
  int depth=level*2; //探索する深さの指定(2, 4, 6, 8)

  puts("---考え中---");

  if(num_stone>=(N*N-level*4)){ //ラストスパートをかけるとき(60, 56, 52, 48)
    depth=64-LAST_SPART; //最後まで読む
    how_to_judge=1; //評価方法切り替え
  }

  //深さlevelで探索して、それぞれのvalから探索順位を決める
  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(Can_Put(present_board, i, j, color)==1){
	Copy_Board(tmp_board, present_board); //盤面をコピー
	Put(tmp_board, i, j, color); //石を置く
	a[tail].x=i;
	a[tail].y=j;
	a[tail].val=Min(tmp_board, level, -10000, 10000, -color);
	tail++;
      }
  Selection_Sort(a, tail); //aをvalで降順に並び替え

  head=0;
  printf("%d / %d", head, tail);
  while(head!=tail){
    fflush(stdout);
    Copy_Board(tmp_board, present_board); //盤面をコピー
    Put(tmp_board, a[head].x, a[head].y, color); //石を置く
    a[head].val=Min(tmp_board, depth, max, 10000, -color);
    if(max<a[head].val){
      *x=a[head].x;
      *y=a[head].y;
      max=a[head].val; //評価の最大値を更新
    }
    head++;
    printf("\r%d / %d", head, tail);
  }
  puts("");
}

int Max(int present_board[N+2][N+2], int depth, int alpha, int beta, int color)
{
  int tmp_board[N+2][N+2]; //シュミレーション用
  int i, j;
  int tmp;
  int max=alpha; //親に返すこのノードの子の中で値が最大となる値

  if(depth<=0) //葉まで来た
    return Judge(present_board, color);
  if(Can_Put_Board(present_board, color)!=1) //盤面に置く所が無ければ
    return Min(present_board, depth-1, alpha, beta, -color); //相手のターン

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(Can_Put(present_board, i, j, color)==1){ //(i,j)に石を置けるとき
	Copy_Board(tmp_board, present_board); //盤面をコピー
	Put(tmp_board, i, j, color); //石を置く
	tmp=Min(tmp_board, depth-1, max, beta, -color);
	if(max<tmp)
	  max=tmp; //より大きい値が見つかったらmaxに格納
	if(beta<=tmp) //子の値が親の他の子の値より大きかったら
	  return 10000; //相手は絶対にこのノードを取らないので、これ以上探索しても無駄なのでカット(βカット)
      }
  return max; //このノードの最大値を親に返す
}

int Min(int present_board[N+2][N+2], int depth, int alpha, int beta, int color)
{
  int tmp_board[N+2][N+2]; //シュミレーション用
  int i, j;
  int tmp; //子の値を一時的に格納しておく変数
  int min=beta;

  if(Can_Put_Board(present_board, color)!=1) //盤面に置く所が無い場合
    return Max(present_board, depth-1, alpha, beta, -color); //相手のターン

  for(i=1; i<N+1; i++)
    for(j=1; j<N+1; j++)
      if(Can_Put(present_board, i, j, color)==1){ //(i,j)に石を置けるとき
        Copy_Board(tmp_board, present_board); //盤面をコピー
        Put(tmp_board, i, j, color); //石を置く
        tmp=Max(tmp_board, depth-1, alpha, min, -color);
        if(min>tmp)
          min=tmp; //より小さい値が見つかったらminに格納
        if(alpha>=tmp) //子の値が親の他の子の値より小さかったら
          return -10000; //相手は絶対にこのノードの子の値は取らないので、これ以上探索しても無駄なのでカット(αカット)
      }
  return min; //このノードの最小値を親に返す
}
