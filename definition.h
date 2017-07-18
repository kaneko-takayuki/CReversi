//定義用ヘッダ

#define W_VT 10
#define W_OL 10
#define W_CP 2
#define W_ND 5
#define N 8 //一辺の長さ
#define EXPERIENCE 0 //一手ずつ見ていくようにするかどうか
#define useCPU 0 //CPU同士で対戦させるかどうか
#define BLACK_STONE 1 //黒い石
#define WHITE_STONE -1 //白い石
#define BLANK 0 //黒い石も白い石も置かれていない
#define WALL 100 //壁
#define QUE_MAX 50 //キューの最大要素数
#define LAST_SPART 48 //ラストスパート(評価方法を石の数のみにする)に移行する石の個数
#define ALL_REVERSE -12345 //評価の際、全ての石が取られることを意味する

typedef struct point{
  int x;
  int y;
  int val;
}point;

int board[N+2][N+2]={{0}}; //最外枠のマスに0を入れることで判定を返しをコンパクトにする
int how_to_judge=0; //評価方法切り替え用変数
int level; //レベル指定(深さを設定)

//8方向へのベクトル(上、右上、右、……左、左上の順)
int dx[8]={-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8]={0, 1, 1, 1, 0, -1, -1, -1};

//function.h
int Can_Reverse(int search_board[N+2][N+2], int x, int y, int i, int color);
int Can_Put(int search_board[N+2][N+2], int x, int y, int color);
int Can_Put_Board(int search[N+2][N+2], int color);
void Print(int print_board[N+2][N+2]);
int Reverse(int reverse_board[N+2][N+2], int x, int y, int i, int color);
int Put(int put_board[N+2][N+2], int x, int y, int color);
void Play_Game_Player(void);
void Play_Game_CPU(void);
void Print_Result(void);

//value.h
void Change_Value_Table(int present_board[N+2][N+2]);
int Judge(int judge_board[N+2][N+2], int color);
int Judge_Table(int judge_board[N+2][N+2], int color);
int Judge_Open_Level(int judge_board[N+2][N+2], int color);
int Num_Can_Put(int judge_board[N+2][N+2], int color);
int Num_Decision_Stone(int judge_board[N+2][N+2], int color);
int Calculate_Num_Decision_Stone(int judge_board[N+2][N+2], int color);
int Diff_Stone(int judge_board[N+2][N+2], int color);
int Num_Stone(int judge_board[N+2][N+2], int color);

//CPU.h
void Copy_Board(int copied_board[N+2][N+2], int copy_board[N+2][N+2]);
void Selection_Sort(point a[QUE_MAX], int n);
void CPU_Decision(int present_board[N+2][N+2], int *x, int *y, int color, int num_stone);
int Max(int present_board[N+2][N+2], int depth, int alpha, int beta, int color);
int Min(int present_board[N+2][N+2], int depth, int alpha, int beta, int color);
