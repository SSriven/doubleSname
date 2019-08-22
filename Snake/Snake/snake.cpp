
/*
蛇蛇大作战
作者：施瑞文
*/

#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")

#define R 30      
#define fram_width 30    //宽度
#define fram_height 30   //高度
#define SIZE 16            //方格边长

//玩家1
#define UP 'w' //72      上
#define DOWN 's' //80  下
#define LEFT 'a' //75   左
#define RIGHT 'd' //77  右
//玩家2
#define DOWN2 'k'    //72,80,75,77是方向键对应的键值  下
#define LEFT2 'j'   //左
#define RIGHT2 'l'   //右
#define UP2 'i'   //上

char ch = 'a';//用于记录方向，传统模式
char c = LEFT2;   //记录玩家2方向
int m;     //全局变量，用于循环计数
int score = 0;    //玩家1分数和传统模式分数
int score2 = 0;    //玩家2分数
char maxScore[5] = "0";   //记录传统模式历史最高分

struct Food     //食物结构体
{
	int x;     //食物的横坐标
	int y;     //食物的纵坐标
}food;

struct Snake {   //玩家1贪吃蛇
	int len;    //蛇的长度
	int x[780];   //蛇的每一节的横坐标
	int y[780];   //蛇的每一节的纵坐标
	int count;    //蛇吃到的食物数量
	int speed;    //蛇的速度
}snake;

struct newSnake   //玩家2 
{
	int len;
	int x[780];
	int y[780];
	int count;
	int speed;
}new_snake;

void initmap();   //画边框
void menu();      //菜单
void getfood();   //随机产生食物
void chushihua();   //初始化蛇
void eatfood();     //判断蛇是否吃到食物
int die();            //判断蛇是否死亡
void move();     //迁移蛇的坐标，移动蛇
void turn(char t);    //转向
void print();           //打印蛇
void play();            //开始传统模式游戏
void start();           //开始特效
int StringToInt(char a[], int n);   //将字符串转化为整数
void wall();           //传统模式的障碍物
void score_rule();   //显示分数和规则

					 //双人PK模式
void double_initmap();   //双人PK地图
void new_chushihua();   //初始化玩家2的蛇
void double_play();     //开始双人PK模式游戏
void double_eatfood();   //判断是否吃到食物
void double_turn(char t);  //转向
void double_print();     //打印玩家2的蛇
void double_move1(); //双人模式玩家1移动
void double_move2();  //双人模式玩家2移动
void double_getfood();//双人模式随机产生食物
void double_score_rule();//双人模式  显示分数和操作规则
int double_die();    //双人模式判断玩家1是否死亡
int double_die2();  //双人模式判断玩家2是否死亡
int win(int grade);   //判断赢家

void main()
{
	do
	{
		initgraph(640, 480);   //产生画板
		PlaySound("D:\\VS项目\\Snake_bgm\\start.WAV", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//播放音乐
		menu();   //进入菜单
		closegraph();  //关闭画板
	} while (1);
	system("pause");
}

int StringToInt(char a[], int n)//将字符串转化为整数
{
	if (n == 1)
		return a[0] - 48;
	else
		return StringToInt(a, n - 1) * 10 + a[n - 1] - 48;
}

void start()//开始特效
{
	int x, y, i;
	for (i = 0; i<30; i++)
	{
		x = i;
		for (y = x; y<R - x; y++)
		{
			setfillcolor(BROWN);
			fillrectangle(x*SIZE, y*SIZE, x*SIZE + SIZE, y*SIZE + SIZE);
		}
		x = (R - 1 - i);
		for (y = i; y <= x; y++)
		{
			setfillcolor(BROWN);
			fillrectangle(x*SIZE, y*SIZE, x*SIZE + SIZE, y*SIZE + SIZE);
		}
		x = i;
		for (y = x; y<R - x; y++)
		{
			setfillcolor(BROWN);
			fillrectangle(y*SIZE, x*SIZE, y*SIZE + SIZE, x*SIZE + SIZE);
		}
		x = (R - 1 - i);
		for (y = i; y <= x; y++)
		{
			setfillcolor(BROWN);
			fillrectangle(y*SIZE, x*SIZE, y*SIZE + SIZE, x*SIZE + SIZE);
		}
		Sleep(50);
	}
	for (i = 0; i<30; i++)
	{
		x = i;
		for (y = x; y<R - x; y++)
		{
			setfillcolor(BLACK);
			solidrectangle(x*SIZE, y*SIZE, x*SIZE + SIZE, y*SIZE + SIZE);
		}
		x = (R - 1 - i);
		for (y = i; y <= x; y++)
		{
			setfillcolor(BLACK);
			solidrectangle(x*SIZE, y*SIZE, x*SIZE + SIZE, y*SIZE + SIZE);
		}
		x = i;
		for (y = x; y<R - x; y++)
		{
			setfillcolor(BLACK);
			solidrectangle(y*SIZE, x*SIZE, y*SIZE + SIZE, x*SIZE + SIZE);
		}
		x = (R - 1 - i);
		for (y = i; y <= x; y++)
		{
			setfillcolor(BLACK);
			solidrectangle(y*SIZE, x*SIZE, y*SIZE + SIZE, x*SIZE + SIZE);
		}
		Sleep(50);
	}
}

void double_getfood()//双人模式随机产生食物
{
	int flag;
	while (1)
	{
		flag = 1;
		food.x = rand() % (fram_width - 2) + 1;
		food.y = rand() % (fram_height - 2) + 1;
		for (m = 0; m<snake.len; m++)
		{
			if (food.x == snake.x[m] && food.y == snake.y[m]) //判断食物是否落到蛇身上
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			continue;
		for (m = 0; m<new_snake.len; m++)
		{
			if (food.x == new_snake.x[m] && food.y == new_snake.y[m])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			continue;
		if (flag == 1)
		{
			if ((new_snake.count + snake.count) % 5 == 0 && (new_snake.count + snake.count) != 0)//每产生5个小食物后产生1个大食物
			{
				setfillcolor(WHITE);
				fillcircle(food.x*SIZE + SIZE / 2, food.y*SIZE + SIZE / 2, SIZE / 2);
			}
			else
			{
				setfillcolor(WHITE);
				fillcircle(food.x*SIZE + SIZE / 2, food.y*SIZE + SIZE / 2, SIZE / 4);
			}
			break;
		}
	}
}

void getfood()//产生食物
{
	int flag;
	while (1)
	{
		flag = 1;
		food.x = rand() % (fram_width - 2) + 1;
		food.y = rand() % (fram_height - 2) + 1;
		for (m = 1; m<fram_width / 3; m++)
		{
			if ((food.x == m && food.y == fram_height / 4) || (food.x == m && food.y == 3 * fram_height / 4))//判断食物是否落到蛇身上
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			continue;
		for (m = 2 * fram_width / 3; m<fram_width; m++)
		{
			if (food.x == m && food.y == fram_height / 2)//判断食物是否落到障碍物上
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			continue;
		for (m = 0; m<snake.len; m++)
		{
			if (food.x == snake.x[m] && food.y == snake.y[m])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			continue;
		if (flag == 1)
		{
			if (snake.count % 5 == 0 && snake.count != 0)
			{
				setfillcolor(WHITE);
				fillcircle(food.x*SIZE + SIZE / 2, food.y*SIZE + SIZE / 2, SIZE / 2);
			}
			else
			{
				setfillcolor(WHITE);
				fillcircle(food.x*SIZE + SIZE / 2, food.y*SIZE + SIZE / 2, SIZE / 4);
			}
			break;
		}
	}
}

void double_eatfood()//双人模式判断是否吃到食物
{
	if (snake.x[0] == food.x&&snake.y[0] == food.y)//如果玩家1吃到食物
	{
		snake.len++;
		if ((snake.count + new_snake.count) % 5 == 0 && (snake.count + new_snake.count) != 0)
		{
			score += 15;
		}
		else
			score += 5;
		snake.count++;
		double_getfood();
	}
	else if (new_snake.x[0] == food.x&&new_snake.y[0] == food.y)//如果玩家2吃到食物
	{
		new_snake.len++;
		if ((snake.count + new_snake.count) % 5 == 0 && (snake.count + new_snake.count) != 0)
		{
			score2 += 15;
		}
		else
			score2 += 5;
		new_snake.count++;
		double_getfood();
	}
}

void eatfood()//传统模式  判断是否吃到食物
{
	if (snake.x[0] == food.x&&snake.y[0] == food.y)
	{
		//PlaySound("E:\\bgm\\eatbig.WAV",NULL,SND_FILENAME|SND_ASYNC);
		snake.len++;
		/*for(m=snake.len-1;m>0;m--)
		{
		snake.x[m]=snake.x[m-1];
		snake.y[m]=snake.y[m-1];
		}*/
		//snake.x[snake.len-1]=a[0];
		//snake.y[snake.len-1]=a[1];

		if (snake.count % 5 == 0 && snake.count != 0)
		{
			score += 20;
			if (snake.speed>100)
				snake.speed -= 50;
			else
				snake.speed = 100;
		}
		else
			score += 5;
		snake.count++;
		getfood();//吃完还有
	}
}

void new_chushihua()//初始化玩家2
{
	//产生蛇头
	new_snake.x[0] = (fram_width) / 3;
	new_snake.y[0] = (fram_height) / 3;
	new_snake.speed = 300;
	moveto(new_snake.x[0] * SIZE, new_snake.y[0] * SIZE);
	setfillcolor(BLUE);
	fillcircle(new_snake.x[0] * SIZE + SIZE / 2, new_snake.y[0] * SIZE + SIZE / 2, SIZE / 2);

	//产生蛇身
	fillcircle(new_snake.x[0] * SIZE + SIZE / 2, new_snake.y[0] * SIZE + SIZE / 2, SIZE / 2);
	new_snake.len = 4;
	for (int k = 1; k < new_snake.len; k++)//依次给后一节蛇身赋值
	{
		//将前一节坐标赋给后一节
		new_snake.x[k] = new_snake.x[k - 1] + 1;
		new_snake.y[k] = new_snake.y[k - 1];
		moveto(new_snake.x[k] * SIZE, new_snake.y[k] * SIZE);
		setfillcolor(YELLOW);//填充颜色
		fillcircle(new_snake.x[k] * SIZE + SIZE / 2, new_snake.y[k] * SIZE + SIZE / 2, SIZE / 2);
		//fillrectangle(new_snake.x[k] * SIZE, new_snake.y[k] * SIZE, new_snake.x[k] * SIZE + SIZE, new_snake.y[k] * SIZE + SIZE);//画蛇
	}
}

void chushihua()
{
	//产生蛇头
	snake.x[0] = (fram_width) / 2;
	snake.y[0] = (fram_height) / 2;
	snake.speed = 300;
	moveto(snake.x[0] * SIZE, snake.y[0] * SIZE);
	setfillcolor(GREEN);
	fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);

	//产生蛇身
	//fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);
	snake.len = 4;
	for (int k = 1; k < snake.len; k++)
	{
		//将前一节坐标赋给后一节
		snake.x[k] = snake.x[k - 1] + 1;
		snake.y[k] = snake.y[k - 1];
		moveto(snake.x[k] * SIZE, snake.y[k] * SIZE);
		setfillcolor(RED);//填充颜色
		fillcircle(snake.x[k] * SIZE + SIZE / 2, snake.y[k] * SIZE + SIZE / 2, SIZE / 2);
		//fillrectangle(snake.x[k] * SIZE, snake.y[k] * SIZE, snake.x[k] * SIZE + SIZE, snake.y[k] * SIZE + SIZE);//画蛇
	}
}

void move()//迁移坐标，移动蛇
{
	//每次移动将蛇尾巴画为背景色
	moveto(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE);
	setfillcolor(BLACK);
	solidrectangle(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE, snake.x[snake.len - 1] * SIZE + SIZE, snake.y[snake.len - 1] * SIZE + SIZE);
	if (snake.y[0] == 0)     //穿墙
		snake.y[0] = fram_height - 2;
	else if (snake.y[0] == fram_height - 1)
		snake.y[0] = 0;
	for (m = snake.len - 1; m > 0; m--)
	{
		//将后一节坐标赋值给前一节坐标
		snake.x[m] = snake.x[m - 1];
		snake.y[m] = snake.y[m - 1];
	}
}

void double_move1()//双人模式移动玩家1
{
	//每次移动将蛇尾巴画为背景色
	moveto(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE);
	setfillcolor(BLACK);
	solidrectangle(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE, snake.x[snake.len - 1] * SIZE + SIZE, snake.y[snake.len - 1] * SIZE + SIZE);
	if (snake.y[0] == 0)     //穿墙
		snake.y[0] = fram_height - 2;
	else if (snake.y[0] == fram_height - 1)
		snake.y[0] = 0;
	else if (snake.x[0] == 0)
		snake.x[0] = fram_width - 2;
	else if (snake.x[0] == fram_width - 1)
		snake.x[0] = 0;
	for (m = snake.len - 1; m > 0; m--)
	{
		//将后一节坐标赋值给前一节坐标
		snake.x[m] = snake.x[m - 1];
		snake.y[m] = snake.y[m - 1];
	}
}

void double_move2()//双人模式移动玩家2
{

	//int k;
	//每次移动将蛇尾巴画为背景色
	moveto(new_snake.x[new_snake.len - 1] * SIZE, new_snake.y[new_snake.len - 1] * SIZE);
	setfillcolor(BLACK);
	solidrectangle(new_snake.x[new_snake.len - 1] * SIZE, new_snake.y[new_snake.len - 1] * SIZE, new_snake.x[new_snake.len - 1] * SIZE + SIZE, new_snake.y[new_snake.len - 1] * SIZE + SIZE);
	if (new_snake.y[0] == 0)     //穿墙
		new_snake.y[0] = fram_height - 2;
	else if (new_snake.y[0] == fram_height - 1)
		new_snake.y[0] = 0;
	else if (new_snake.x[0] == 0)
		new_snake.x[0] = fram_width - 2;
	else if (new_snake.x[0] == fram_width - 1)
		new_snake.x[0] = 0;
	for (m = new_snake.len - 1; m > 0; m--)
	{
		//将后一节坐标赋值给前一节坐标
		new_snake.x[m] = new_snake.x[m - 1];
		new_snake.y[m] = new_snake.y[m - 1];
	}
	/*int k;
	int i;
	moveto(new_snake.x[new_snake.len - 1] * SIZE, new_snake.y[new_snake.len - 1] * SIZE);
	setfillcolor(BLACK);
	solidrectangle(new_snake.x[new_snake.len - 1] * SIZE, new_snake.y[new_snake.len - 1] * SIZE, new_snake.x[new_snake.len - 1] * SIZE + SIZE, new_snake.y[new_snake.len - 1] * SIZE + SIZE);

	moveto(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE);
	setfillcolor(BLACK);
	solidrectangle(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE, snake.x[snake.len - 1] * SIZE + SIZE, snake.y[snake.len - 1] * SIZE + SIZE);
	if (snake.y[0] == 0)     //穿墙
	snake.y[0] = fram_height;
	else if (snake.y[0] == fram_height)
	snake.y[0] = 0;
	if (new_snake.y[0] == 0)     //穿墙
	new_snake.y[0] = fram_height;
	else if (new_snake.y[0] == fram_height)
	new_snake.y[0] = 0;
	for (m = new_snake.len - 1,k=snake.len - 1; m > 0,k>0; m--,k--)
	{
	snake.x[k] = snake.x[k - 1];
	snake.y[k] = snake.y[k - 1];
	new_snake.x[m] = new_snake.x[m - 1];
	new_snake.y[m] = new_snake.y[m - 1];
	if(k==0||m==0)
	break;
	}
	if(m>k)
	{
	for(i=m;i>0;i--)
	{
	new_snake.x[i] = new_snake.x[i - 1];
	new_snake.y[i] = new_snake.y[i - 1];
	}
	}
	else if(m<k)
	{
	for(i=k;i>0;i--)
	{
	snake.x[i] = snake.x[i - 1];
	snake.y[i] = snake.y[i - 1];
	}
	}*/
}

void double_turn(char t)
{
	if (t == UP2)
		new_snake.y[0]--;
	else if (t == DOWN2)
		new_snake.y[0]++;
	else if (t == LEFT2)
		new_snake.x[0]--;
	else if (t == RIGHT2)
		new_snake.x[0]++;
}

void turn(char t)
{
	if (t == UP)
		snake.y[0]--;
	else if (t == DOWN)
		snake.y[0]++;
	else if (t == LEFT)
		snake.x[0]--;
	else if (t == RIGHT)
		snake.x[0]++;
}

void print()//打印蛇
{
	//打印蛇头
	moveto(snake.x[0] * SIZE, snake.y[0] * SIZE);
	setfillcolor(GREEN);
	fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);
	//打印蛇身
	for (m = 1; m<snake.len; m++)
	{
		setfillcolor(RED);
		fillcircle(snake.x[m] * SIZE + SIZE / 2, snake.y[m] * SIZE + SIZE / 2, SIZE / 2);
		//fillrectangle(snake.x[m] * SIZE, snake.y[m] * SIZE, snake.x[m] * SIZE + SIZE, snake.y[m] * SIZE + SIZE);
	}
}

void double_print()//双人模式   同时打印两条蛇
{
	int len = new_snake.len<snake.len ? new_snake.len : snake.len;//len取两者中的较小值
	moveto(new_snake.x[0] * SIZE, new_snake.y[0] * SIZE);
	setfillcolor(BLUE);
	fillcircle(new_snake.x[0] * SIZE + SIZE / 2, new_snake.y[0] * SIZE + SIZE / 2, SIZE / 2);//画玩家2的蛇头
	moveto(snake.x[0] * SIZE, snake.y[0] * SIZE);
	setfillcolor(GREEN);
	fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);//画玩家1的蛇头
	for (m = 1; m<len; m++)//同时画玩家1和玩家2的蛇身
	{
		setfillcolor(RED);
		fillcircle(snake.x[m] * SIZE + SIZE / 2, snake.y[m] * SIZE + SIZE / 2, SIZE / 2);
		//fillrectangle(snake.x[m] * SIZE, snake.y[m] * SIZE, snake.x[m] * SIZE + SIZE, snake.y[m] * SIZE + SIZE);
		setfillcolor(YELLOW);
		fillcircle(new_snake.x[m] * SIZE + SIZE / 2, new_snake.y[m] * SIZE + SIZE / 2, SIZE / 2);
		//fillrectangle(new_snake.x[m] * SIZE, new_snake.y[m] * SIZE, new_snake.x[m] * SIZE + SIZE, new_snake.y[m] * SIZE + SIZE);
	}
	for (m = len; m<(new_snake.len>snake.len ? new_snake.len : snake.len); m++)
	{
		if (new_snake.len>snake.len)//如果玩家2的蛇比玩家1的蛇长，则把玩家2比玩家1多处的那部分补全
		{
			setfillcolor(YELLOW);
			fillcircle(new_snake.x[m] * SIZE + SIZE / 2, new_snake.y[m] * SIZE + SIZE / 2, SIZE / 2);
			//fillrectangle(new_snake.x[m] * SIZE, new_snake.y[m] * SIZE, new_snake.x[m] * SIZE + SIZE, new_snake.y[m] * SIZE + SIZE);
		}
		else//如果玩家1的蛇比玩家2的蛇长，则把玩家1比玩家2多处的那部分补全
		{
			setfillcolor(RED);
			fillcircle(snake.x[m] * SIZE + SIZE / 2, snake.y[m] * SIZE + SIZE / 2, SIZE / 2);
			//fillrectangle(snake.x[m] * SIZE, snake.y[m] * SIZE, snake.x[m] * SIZE + SIZE, snake.y[m] * SIZE + SIZE);
		}
	}
}

int win(int grade)//判断输赢
{
	if (score >= grade)//如果玩家1率先达到50分，则玩家1胜利
		return 1;
	else if (score2 >= grade)//否则玩家2胜利
		return 2;
}

void wall()//画障碍物
{
	for (m = 1; m<fram_width / 3; m++)
	{
		setfillcolor(BROWN);
		fillrectangle(m*SIZE, fram_height / 4 * SIZE, m*SIZE + SIZE, fram_height / 4 * SIZE + SIZE);
	}
	for (m = 2 * fram_width / 3; m<fram_width; m++)
	{
		setfillcolor(BROWN);
		fillrectangle(m*SIZE, fram_height / 2 * SIZE, m*SIZE + SIZE, fram_height / 2 * SIZE + SIZE);
	}
	for (m = 1; m<fram_width / 3; m++)
	{
		setfillcolor(BROWN);
		fillrectangle(m*SIZE, 3 * fram_height / 4 * SIZE, m*SIZE + SIZE, 3 * fram_height / 4 * SIZE + SIZE);
	}
}

void double_score_rule()//分数与规则
{
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 3 * SIZE, "玩家1:");
	setfillcolor(GREEN);
	fillcircle(34 * SIZE + SIZE / 2, 3 * SIZE + SIZE / 2, SIZE / 2);

	//产生蛇身
	//fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);
	for (int k = 35; k <38; k++)
	{
		//snake.x[k] = snake.x[k - 1] + 1;//横着画出蛇
		//snake.y[k] = snake.y[k - 1];//纵坐标不变
		//moveto(snake.x[k] * SIZE, snake.y[k] * SIZE);
		setfillcolor(RED);
		//fillcircle(snake.x[k]*SIZE+SIZE/2, snake.y[k]*SIZE+SIZE/2, SIZE/2);
		//fillrectangle(k * SIZE, 3 * SIZE, k * SIZE + SIZE, 3 * SIZE + SIZE);
		fillcircle(k * SIZE + SIZE / 2, 3 * SIZE + SIZE / 2, SIZE / 2);
	}
	char count1[5];
	itoa(score, count1, 10);//将整数转化为字符串
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 5 * SIZE, "分数:");
	setfillcolor(BLACK);
	solidrectangle(34 * SIZE, 5 * SIZE, 38 * SIZE + SIZE, 5 * SIZE + SIZE);
	outtextxy(34 * SIZE, 5 * SIZE, count1);
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 7 * SIZE, "玩家2:");
	setfillcolor(BLUE);
	fillcircle(new_snake.x[0] * SIZE + SIZE / 2, new_snake.y[0] * SIZE + SIZE / 2, SIZE / 2);

	//产生蛇身
	fillcircle(34 * SIZE + SIZE / 2, 7 * SIZE + SIZE / 2, SIZE / 2);
	for (int j = 35; j < 38; j++)
	{
		setfillcolor(YELLOW);
		//fillcircle(snake.x[k]*SIZE+SIZE/2, snake.y[k]*SIZE+SIZE/2, SIZE/2);
		//fillrectangle(j * SIZE, 7 * SIZE, j* SIZE + SIZE, 7 * SIZE + SIZE);
		fillcircle(j * SIZE + SIZE / 2, 7 * SIZE + SIZE / 2, SIZE / 2);
	}
	char count2[5];
	itoa(score2, count2, 10);
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 9 * SIZE, "分数:");
	setfillcolor(BLACK);
	solidrectangle(34 * SIZE, 9 * SIZE, 38 * SIZE + SIZE, 9 * SIZE + SIZE);
	outtextxy(34 * SIZE, 9 * SIZE, count2);
	line(30 * SIZE, 11 * SIZE, 40 * SIZE, 11 * SIZE);
	settextcolor(RED);
	outtextxy(31 * SIZE, 13 * SIZE, "玩家1:");
	settextcolor(GREEN);
	outtextxy(31 * SIZE, 14 * SIZE, "  w: 上   s: 下");
	outtextxy(31 * SIZE, 15 * SIZE, "  a: 左   d: 右");
	settextcolor(RED);
	outtextxy(31 * SIZE, 17 * SIZE, "玩家2:");
	settextcolor(GREEN);
	outtextxy(31 * SIZE, 18 * SIZE, "  i: 上   k: 下");
	outtextxy(31 * SIZE, 19 * SIZE, "  j: 左   l: 右");
	settextcolor(RED);
	outtextxy(31 * SIZE, 21 * SIZE, "规则:");
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 23 * SIZE, "1.率先达到目标分者");
	outtextxy(31 * SIZE, 24 * SIZE, "  胜利。");
	outtextxy(31 * SIZE, 25 * SIZE, "2.游戏过程中若碰到");
	outtextxy(31 * SIZE, 26 * SIZE, "  对方身体，则减15");
	outtextxy(31 * SIZE, 27 * SIZE, "  分，并在初始位置");
	outtextxy(31 * SIZE, 28 * SIZE, "  复活");
}

void score_rule()
{
	char count[5];
	FILE *fp;
	fp = fopen("maxscore", "a+");//读取文件中的内容
	if (fp != NULL)
	{
		settextcolor(GREEN);
		while (fgets(maxScore, 5, fp) != NULL)//将文件中的内容写入maxScore数组中
			outtextxy(35 * SIZE, 5 * SIZE, maxScore);//将最高分显示在画板上
		fclose(fp);
	}
	itoa(score, count, 10);//将整数转化为字符串
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 3 * SIZE, "分数:");
	setfillcolor(BLACK);
	solidrectangle(34 * SIZE, 3 * SIZE, 38 * SIZE + SIZE, 3 * SIZE + SIZE);
	outtextxy(34 * SIZE, 3 * SIZE, count);
	outtextxy(31 * SIZE, 5 * SIZE, "最高分:");
	line(30 * SIZE, 9 * SIZE, 40 * SIZE, 9 * SIZE);
	outtextxy(31 * SIZE, 11 * SIZE, "  w:     上");
	outtextxy(31 * SIZE, 13 * SIZE, "  s:     下");
	outtextxy(31 * SIZE, 15 * SIZE, "  a:     左");
	outtextxy(31 * SIZE, 17 * SIZE, "  d:     右");
}

void double_initmap()
{
	for (int i = 1; i < fram_width - 1; i++)
	{
		//moveto(i*SIZE, 0);
		setfillcolor(BLACK);
		fillrectangle(i*SIZE, 0, i*SIZE + SIZE, SIZE);
		//moveto(i*SIZE, i*SIZE*(fram_width-1)+SIZE);
		setfillcolor(BLACK);
		fillrectangle(i*SIZE, SIZE*(fram_width - 1), i*SIZE + SIZE, SIZE*(fram_width - 1) + SIZE);
	}
	for (int j = 0; j < fram_height; j++)
	{
		//moveto(0, j*SIZE);
		setfillcolor(BLACK);
		fillrectangle(0, j*SIZE, SIZE, j*SIZE + SIZE);
		//moveto(j*SIZE*(fram_height-1)+SIZE, j*SIZE);
		setfillcolor(BLACK);
		fillrectangle(SIZE*(fram_height - 1), j*SIZE, SIZE*(fram_height - 1) + SIZE, j*SIZE + SIZE);
	}
}

void initmap()
{

	//产生围栏
	for (int i = 1; i < fram_width - 1; i++)
	{
		//moveto(i*SIZE, 0);
		setfillcolor(BLACK);
		fillrectangle(i*SIZE, 0, i*SIZE + SIZE, SIZE);
		//moveto(i*SIZE, i*SIZE*(fram_width-1)+SIZE);
		setfillcolor(BLACK);
		fillrectangle(i*SIZE, SIZE*(fram_width - 1), i*SIZE + SIZE, SIZE*(fram_width - 1) + SIZE);
	}
	for (int j = 0; j < fram_height; j++)
	{
		//moveto(0, j*SIZE);
		setfillcolor(BROWN);
		fillrectangle(0, j*SIZE, SIZE, j*SIZE + SIZE);
		//moveto(j*SIZE*(fram_height-1)+SIZE, j*SIZE);
		setfillcolor(BROWN);
		fillrectangle(SIZE*(fram_height - 1), j*SIZE, SIZE*(fram_height - 1) + SIZE, j*SIZE + SIZE);
	}

}

int double_die1()
{
	for (int i = 1; i<new_snake.len; i++)
	{
		if (snake.x[0] == new_snake.x[i] && snake.y[0] == new_snake.y[i])
		{
			return 1;
		}
	}
	return 0;
}

int double_die2()
{
	for (int i = 1; i<snake.len; i++)
	{
		if (new_snake.x[0] == snake.x[i] && new_snake.y[0] == snake.y[i])
		{
			return 1;
		}
	}
	return 0;
}

int die()
{
	for (int i = 1; i<snake.len; i++)
	{
		if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
		{
			return 1;
		}
	}
	for (m = 1; m<fram_width / 3; m++)
	{
		if ((snake.x[0] == m && snake.y[0] == fram_height / 4) || (snake.x[0] == m && snake.y[0] == 3 * fram_height / 4))
		{
			return 1;
		}
	}
	for (m = 2 * fram_width / 3; m<fram_width; m++)
	{
		if (snake.x[0] == m && snake.y[0] == fram_height / 2)
		{
			return 1;
		}
	}
	if (snake.x[0] == 0 || snake.x[0] == fram_width - 1)
	{
		return 1;
	}
	return 0;
}

void menu()
{
	char str[100];
	InputBox(str, 100, "请选择：\n\n 1.传统模式\n\n 2.双人PK\n\n 3.退出游戏", "蛇蛇大作战", "", 250, 100, false);
	if (strcmp(str, "1") == 0)
	{

		PlaySound("D:\\VS项目\\Snake_bgm\\bgm1.WAV", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		start();
		initmap();
		wall();
		score_rule();
		srand(time(NULL));
		play();
	}
	else if (strcmp(str, "2") == 0)
	{
		PlaySound("D:\\VS项目\\Snake_bgm\\double_play.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		start();
		double_initmap();
		srand(time(NULL));
		double_play();
	}
	else if (strcmp(str, "3") == 0)
	{
		exit(0);
	}
}

void double_play()//开始双人PK游戏
{
	char str[5];
	int len;
	int grade;
	while (1)
	{
		int flag = 1;
		InputBox(str, 5, "请输入目标分数(1~1000)\n只能输入数字", "蛇蛇大作战", "", 200, 100, false);
		len = strlen(str);
		str[len] = '\0';
		if (str[0] == NULL)
			continue;
		for (int i = 0; i<len; i++)
			if (str[i]<'0' || str[i]>'9')
			{
				flag = 0;
				break;
			}
		if (!flag)
			continue;
		grade = StringToInt(str, len);
		if (grade>0 && grade <= 1000)
			break;
	}
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 1 * SIZE, "目标分数:");
	settextcolor(BROWN);
	outtextxy(36 * SIZE, 1 * SIZE, str);
	char k = 'a';
	char t = LEFT2;  //k和t分别记录蛇前一时刻移动的方向
	new_snake.count = 0;
	snake.count = 0;
	score = 0;
	score2 = 0;
	new_chushihua();
	chushihua();  //初始化
	int move1 = 0, move2 = 0;//标记按键的归属
	char key, key1 = LEFT, key2 = LEFT2;//初始方向
	double_getfood();//产生食物
	while (1)
	{
		double_eatfood();//判断是否吃到食物
		double_move2();
		double_move1();//移动蛇
		move1 = 0;
		move2 = 0;
		if (kbhit())//如果有按键
		{
			key = getch();//获取按键值
			switch (key)//判断按键
			{

			case UP2:
			case DOWN2:
			case LEFT2:
			case RIGHT2:key2 = key; move2 = 1; break;//如果按键属于玩家2，move2=1；
			case UP:
			case DOWN:
			case LEFT:
			case RIGHT:key1 = key; move1 = 1; break;//如果按键属于玩家1，move1=1；
			}
		}
		if (move1 == 1)//如果move1=1，即按键属于玩家1
		{
			if (k == LEFT && key1 == RIGHT)    //防止反向咬到自己
				key1 = LEFT;
			else if (k == UP && key1 == DOWN)
				key1 = UP;
			else if (k == RIGHT && key1 == LEFT)
				key1 = RIGHT;
			else if (k == DOWN && key1 == UP)
				key1 = DOWN;
			turn(key1);//转向
		}
		if (move2 == 1)//如果move2=1，即按键属于玩家2
		{
			if (t == UP2 && key2 == DOWN2)    //防止反向咬到自己
				key2 = UP2;
			else if (t == DOWN2 && key2 == UP2)
				key2 = DOWN2;
			else if (t == LEFT2 && key2 == RIGHT2)
				key2 = LEFT2;
			else if (t == RIGHT2 && key2 == LEFT2)
				key2 = RIGHT2;
			double_turn(key2);//转向
		}

		if (move2 == 0)//如果按键属于玩家1，则玩家2的蛇继续维持上一时刻的方向
			double_turn(t);
		if (move1 == 0)//如果按键属于玩家2，则玩家1的蛇继续维持上一时刻的方向
			turn(k);

		k = key1;
		t = key2;//获取上一时刻的方向
				 //fflush(stdin);
				 //print();

		if (double_die1())//判断玩家1是否死亡
		{
			//PlaySound("F:\\Snake_bgm\\gameover.WAV", NULL, SND_FILENAME | SND_ASYNC);
			if (score >= 15)//如果分数大于15分
				score -= 15;
			else      //如果分数小于15分，则分数清零
				score = 0;
			for (m = 0; m<snake.len; m++)//死亡后，将遗体用背景色覆盖
			{
				setfillcolor(BLACK);
				solidrectangle(snake.x[m] * SIZE, snake.y[m] * SIZE, snake.x[m] * SIZE + SIZE, snake.y[m] * SIZE + SIZE);
			}
			k = key1 = LEFT;
			chushihua();//初始化蛇
		}
		if (double_die2())//如果玩家2死亡
		{
			//PlaySound("F:\\Snake_bgm\\gameover.WAV", NULL, SND_FILENAME | SND_ASYNC);
			if (score2 >= 15)
				score2 -= 15;
			else
				score2 = 0;
			for (m = 0; m<new_snake.len; m++)
			{
				setfillcolor(BLACK);
				solidrectangle(new_snake.x[m] * SIZE, new_snake.y[m] * SIZE, new_snake.x[m] * SIZE + SIZE, new_snake.y[m] * SIZE + SIZE);
			}
			t = key2 = LEFT2;
			new_chushihua();
		}
		double_print();//画蛇
		double_initmap();
		double_score_rule();
		if (win(grade) == 1)//如果玩家1胜利
		{
			PlaySound("D:\\VS项目\\Snake_bgm\\win.WAV", NULL, SND_FILENAME | SND_ASYNC);
			settextcolor(YELLOW);
			LOGFONT f;
			gettextstyle(&f);                     // 获取当前字体设置
			f.lfHeight = 48;                      // 设?米痔甯叨任? 48
			_tcscpy(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
			f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
			settextstyle(&f);                     // 设置字体样式
			outtextxy(8 * SIZE, 12 * SIZE, _T("玩家1胜利!"));
			outtextxy(8 * SIZE, 15 * SIZE, _T("按空格键继续!"));
			while (getch() != ' ')
			{
				;
			}
			break;
		}
		else if (win(grade) == 2)//如果玩家2胜利
		{
			PlaySound("D:\\VS项目\\Snake_bgm\\win.WAV", NULL, SND_FILENAME | SND_ASYNC);
			settextcolor(YELLOW);
			LOGFONT f;
			gettextstyle(&f);                     // 获取当前字体设置
			f.lfHeight = 48;                      // 设?米痔甯叨任? 48
			_tcscpy(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
			f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
			settextstyle(&f);                     // 设置字体样式
			outtextxy(8 * SIZE, 12 * SIZE, _T("玩家2胜利!"));
			outtextxy(8 * SIZE, 15 * SIZE, _T("按空格键继续!"));
			while (getch() != ' ')
			{
				;
			}
			break;
		}
		Sleep(150);
	}
}

void play()   //开始传统模式游戏
{
	char k = 'a';//k记录前一时刻移动的方向
	char ch = 'a';
	snake.count = 0;
	score = 0;
	chushihua();
	getfood();
	while (1)
	{

		if (kbhit())
		{
			while (1)//如果按其他键，则暂停
			{
				ch = getch();
				if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
					break;
				else
					continue;
			}
		}
		eatfood();
		move();
		if (k == 'a'&&ch == 'd')    //防止反向咬到自己
			ch = 'a';
		else if (k == 'w'&&ch == 's')
			ch = 'w';
		else if (k == 'd'&&ch == 'a')
			ch = 'd';
		else if (k == 's'&&ch == 'w')
			ch = 's';
		turn(ch);
		k = ch;


		if (die())
		{
			PlaySound("D:\\VS项目\\Snake_bgm\\gameover.WAV", NULL, SND_FILENAME | SND_ASYNC);
			settextcolor(YELLOW);
			LOGFONT f;
			gettextstyle(&f);                     // 获取当前字体设置
			f.lfHeight = 48;                      // 设?米痔甯叨任? 48
			_tcscpy(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
			f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
			settextstyle(&f);                     // 设置字体样式
			outtextxy(8 * SIZE, 12 * SIZE, _T("Game Over!"));
			outtextxy(8 * SIZE, 15 * SIZE, _T("按空格键继续!"));
			FILE *fp;
			int len;
			len = strlen(maxScore);
			maxScore[len] = '\0';
			int maxscore;
			char ms[5];
			maxscore = StringToInt(maxScore, len);//将字符串转化为整数
			if (score>maxscore)//如果破纪录
			{
				fp = fopen("maxscore", "w");//将新纪录写入文件，并将文件中的原内容清空
				if (fp != NULL)
				{
					itoa(score, ms, 10);
					fputs(ms, fp);
				}
				fclose(fp);
			}
			while (getch() != ' ')
			{
				;
			}
			break;
		}
		print();
		initmap();//画边框
		wall();//画障碍物
		score_rule();//显示分数和规则
		Sleep(snake.speed);//速度
	}
}