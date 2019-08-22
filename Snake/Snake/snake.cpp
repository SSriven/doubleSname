
/*
���ߴ���ս
���ߣ�ʩ����
*/

#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")

#define R 30      
#define fram_width 30    //���
#define fram_height 30   //�߶�
#define SIZE 16            //����߳�

//���1
#define UP 'w' //72      ��
#define DOWN 's' //80  ��
#define LEFT 'a' //75   ��
#define RIGHT 'd' //77  ��
//���2
#define DOWN2 'k'    //72,80,75,77�Ƿ������Ӧ�ļ�ֵ  ��
#define LEFT2 'j'   //��
#define RIGHT2 'l'   //��
#define UP2 'i'   //��

char ch = 'a';//���ڼ�¼���򣬴�ͳģʽ
char c = LEFT2;   //��¼���2����
int m;     //ȫ�ֱ���������ѭ������
int score = 0;    //���1�����ʹ�ͳģʽ����
int score2 = 0;    //���2����
char maxScore[5] = "0";   //��¼��ͳģʽ��ʷ��߷�

struct Food     //ʳ��ṹ��
{
	int x;     //ʳ��ĺ�����
	int y;     //ʳ���������
}food;

struct Snake {   //���1̰����
	int len;    //�ߵĳ���
	int x[780];   //�ߵ�ÿһ�ڵĺ�����
	int y[780];   //�ߵ�ÿһ�ڵ�������
	int count;    //�߳Ե���ʳ������
	int speed;    //�ߵ��ٶ�
}snake;

struct newSnake   //���2 
{
	int len;
	int x[780];
	int y[780];
	int count;
	int speed;
}new_snake;

void initmap();   //���߿�
void menu();      //�˵�
void getfood();   //�������ʳ��
void chushihua();   //��ʼ����
void eatfood();     //�ж����Ƿ�Ե�ʳ��
int die();            //�ж����Ƿ�����
void move();     //Ǩ���ߵ����꣬�ƶ���
void turn(char t);    //ת��
void print();           //��ӡ��
void play();            //��ʼ��ͳģʽ��Ϸ
void start();           //��ʼ��Ч
int StringToInt(char a[], int n);   //���ַ���ת��Ϊ����
void wall();           //��ͳģʽ���ϰ���
void score_rule();   //��ʾ�����͹���

					 //˫��PKģʽ
void double_initmap();   //˫��PK��ͼ
void new_chushihua();   //��ʼ�����2����
void double_play();     //��ʼ˫��PKģʽ��Ϸ
void double_eatfood();   //�ж��Ƿ�Ե�ʳ��
void double_turn(char t);  //ת��
void double_print();     //��ӡ���2����
void double_move1(); //˫��ģʽ���1�ƶ�
void double_move2();  //˫��ģʽ���2�ƶ�
void double_getfood();//˫��ģʽ�������ʳ��
void double_score_rule();//˫��ģʽ  ��ʾ�����Ͳ�������
int double_die();    //˫��ģʽ�ж����1�Ƿ�����
int double_die2();  //˫��ģʽ�ж����2�Ƿ�����
int win(int grade);   //�ж�Ӯ��

void main()
{
	do
	{
		initgraph(640, 480);   //��������
		PlaySound("D:\\VS��Ŀ\\Snake_bgm\\start.WAV", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//��������
		menu();   //����˵�
		closegraph();  //�رջ���
	} while (1);
	system("pause");
}

int StringToInt(char a[], int n)//���ַ���ת��Ϊ����
{
	if (n == 1)
		return a[0] - 48;
	else
		return StringToInt(a, n - 1) * 10 + a[n - 1] - 48;
}

void start()//��ʼ��Ч
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

void double_getfood()//˫��ģʽ�������ʳ��
{
	int flag;
	while (1)
	{
		flag = 1;
		food.x = rand() % (fram_width - 2) + 1;
		food.y = rand() % (fram_height - 2) + 1;
		for (m = 0; m<snake.len; m++)
		{
			if (food.x == snake.x[m] && food.y == snake.y[m]) //�ж�ʳ���Ƿ��䵽������
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
			if ((new_snake.count + snake.count) % 5 == 0 && (new_snake.count + snake.count) != 0)//ÿ����5��Сʳ������1����ʳ��
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

void getfood()//����ʳ��
{
	int flag;
	while (1)
	{
		flag = 1;
		food.x = rand() % (fram_width - 2) + 1;
		food.y = rand() % (fram_height - 2) + 1;
		for (m = 1; m<fram_width / 3; m++)
		{
			if ((food.x == m && food.y == fram_height / 4) || (food.x == m && food.y == 3 * fram_height / 4))//�ж�ʳ���Ƿ��䵽������
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			continue;
		for (m = 2 * fram_width / 3; m<fram_width; m++)
		{
			if (food.x == m && food.y == fram_height / 2)//�ж�ʳ���Ƿ��䵽�ϰ�����
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

void double_eatfood()//˫��ģʽ�ж��Ƿ�Ե�ʳ��
{
	if (snake.x[0] == food.x&&snake.y[0] == food.y)//������1�Ե�ʳ��
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
	else if (new_snake.x[0] == food.x&&new_snake.y[0] == food.y)//������2�Ե�ʳ��
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

void eatfood()//��ͳģʽ  �ж��Ƿ�Ե�ʳ��
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
		getfood();//���껹��
	}
}

void new_chushihua()//��ʼ�����2
{
	//������ͷ
	new_snake.x[0] = (fram_width) / 3;
	new_snake.y[0] = (fram_height) / 3;
	new_snake.speed = 300;
	moveto(new_snake.x[0] * SIZE, new_snake.y[0] * SIZE);
	setfillcolor(BLUE);
	fillcircle(new_snake.x[0] * SIZE + SIZE / 2, new_snake.y[0] * SIZE + SIZE / 2, SIZE / 2);

	//��������
	fillcircle(new_snake.x[0] * SIZE + SIZE / 2, new_snake.y[0] * SIZE + SIZE / 2, SIZE / 2);
	new_snake.len = 4;
	for (int k = 1; k < new_snake.len; k++)//���θ���һ������ֵ
	{
		//��ǰһ�����긳����һ��
		new_snake.x[k] = new_snake.x[k - 1] + 1;
		new_snake.y[k] = new_snake.y[k - 1];
		moveto(new_snake.x[k] * SIZE, new_snake.y[k] * SIZE);
		setfillcolor(YELLOW);//�����ɫ
		fillcircle(new_snake.x[k] * SIZE + SIZE / 2, new_snake.y[k] * SIZE + SIZE / 2, SIZE / 2);
		//fillrectangle(new_snake.x[k] * SIZE, new_snake.y[k] * SIZE, new_snake.x[k] * SIZE + SIZE, new_snake.y[k] * SIZE + SIZE);//����
	}
}

void chushihua()
{
	//������ͷ
	snake.x[0] = (fram_width) / 2;
	snake.y[0] = (fram_height) / 2;
	snake.speed = 300;
	moveto(snake.x[0] * SIZE, snake.y[0] * SIZE);
	setfillcolor(GREEN);
	fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);

	//��������
	//fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);
	snake.len = 4;
	for (int k = 1; k < snake.len; k++)
	{
		//��ǰһ�����긳����һ��
		snake.x[k] = snake.x[k - 1] + 1;
		snake.y[k] = snake.y[k - 1];
		moveto(snake.x[k] * SIZE, snake.y[k] * SIZE);
		setfillcolor(RED);//�����ɫ
		fillcircle(snake.x[k] * SIZE + SIZE / 2, snake.y[k] * SIZE + SIZE / 2, SIZE / 2);
		//fillrectangle(snake.x[k] * SIZE, snake.y[k] * SIZE, snake.x[k] * SIZE + SIZE, snake.y[k] * SIZE + SIZE);//����
	}
}

void move()//Ǩ�����꣬�ƶ���
{
	//ÿ���ƶ�����β�ͻ�Ϊ����ɫ
	moveto(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE);
	setfillcolor(BLACK);
	solidrectangle(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE, snake.x[snake.len - 1] * SIZE + SIZE, snake.y[snake.len - 1] * SIZE + SIZE);
	if (snake.y[0] == 0)     //��ǽ
		snake.y[0] = fram_height - 2;
	else if (snake.y[0] == fram_height - 1)
		snake.y[0] = 0;
	for (m = snake.len - 1; m > 0; m--)
	{
		//����һ�����긳ֵ��ǰһ������
		snake.x[m] = snake.x[m - 1];
		snake.y[m] = snake.y[m - 1];
	}
}

void double_move1()//˫��ģʽ�ƶ����1
{
	//ÿ���ƶ�����β�ͻ�Ϊ����ɫ
	moveto(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE);
	setfillcolor(BLACK);
	solidrectangle(snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE, snake.x[snake.len - 1] * SIZE + SIZE, snake.y[snake.len - 1] * SIZE + SIZE);
	if (snake.y[0] == 0)     //��ǽ
		snake.y[0] = fram_height - 2;
	else if (snake.y[0] == fram_height - 1)
		snake.y[0] = 0;
	else if (snake.x[0] == 0)
		snake.x[0] = fram_width - 2;
	else if (snake.x[0] == fram_width - 1)
		snake.x[0] = 0;
	for (m = snake.len - 1; m > 0; m--)
	{
		//����һ�����긳ֵ��ǰһ������
		snake.x[m] = snake.x[m - 1];
		snake.y[m] = snake.y[m - 1];
	}
}

void double_move2()//˫��ģʽ�ƶ����2
{

	//int k;
	//ÿ���ƶ�����β�ͻ�Ϊ����ɫ
	moveto(new_snake.x[new_snake.len - 1] * SIZE, new_snake.y[new_snake.len - 1] * SIZE);
	setfillcolor(BLACK);
	solidrectangle(new_snake.x[new_snake.len - 1] * SIZE, new_snake.y[new_snake.len - 1] * SIZE, new_snake.x[new_snake.len - 1] * SIZE + SIZE, new_snake.y[new_snake.len - 1] * SIZE + SIZE);
	if (new_snake.y[0] == 0)     //��ǽ
		new_snake.y[0] = fram_height - 2;
	else if (new_snake.y[0] == fram_height - 1)
		new_snake.y[0] = 0;
	else if (new_snake.x[0] == 0)
		new_snake.x[0] = fram_width - 2;
	else if (new_snake.x[0] == fram_width - 1)
		new_snake.x[0] = 0;
	for (m = new_snake.len - 1; m > 0; m--)
	{
		//����һ�����긳ֵ��ǰһ������
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
	if (snake.y[0] == 0)     //��ǽ
	snake.y[0] = fram_height;
	else if (snake.y[0] == fram_height)
	snake.y[0] = 0;
	if (new_snake.y[0] == 0)     //��ǽ
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

void print()//��ӡ��
{
	//��ӡ��ͷ
	moveto(snake.x[0] * SIZE, snake.y[0] * SIZE);
	setfillcolor(GREEN);
	fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);
	//��ӡ����
	for (m = 1; m<snake.len; m++)
	{
		setfillcolor(RED);
		fillcircle(snake.x[m] * SIZE + SIZE / 2, snake.y[m] * SIZE + SIZE / 2, SIZE / 2);
		//fillrectangle(snake.x[m] * SIZE, snake.y[m] * SIZE, snake.x[m] * SIZE + SIZE, snake.y[m] * SIZE + SIZE);
	}
}

void double_print()//˫��ģʽ   ͬʱ��ӡ������
{
	int len = new_snake.len<snake.len ? new_snake.len : snake.len;//lenȡ�����еĽ�Сֵ
	moveto(new_snake.x[0] * SIZE, new_snake.y[0] * SIZE);
	setfillcolor(BLUE);
	fillcircle(new_snake.x[0] * SIZE + SIZE / 2, new_snake.y[0] * SIZE + SIZE / 2, SIZE / 2);//�����2����ͷ
	moveto(snake.x[0] * SIZE, snake.y[0] * SIZE);
	setfillcolor(GREEN);
	fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);//�����1����ͷ
	for (m = 1; m<len; m++)//ͬʱ�����1�����2������
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
		if (new_snake.len>snake.len)//������2���߱����1���߳���������2�����1�ദ���ǲ��ֲ�ȫ
		{
			setfillcolor(YELLOW);
			fillcircle(new_snake.x[m] * SIZE + SIZE / 2, new_snake.y[m] * SIZE + SIZE / 2, SIZE / 2);
			//fillrectangle(new_snake.x[m] * SIZE, new_snake.y[m] * SIZE, new_snake.x[m] * SIZE + SIZE, new_snake.y[m] * SIZE + SIZE);
		}
		else//������1���߱����2���߳���������1�����2�ദ���ǲ��ֲ�ȫ
		{
			setfillcolor(RED);
			fillcircle(snake.x[m] * SIZE + SIZE / 2, snake.y[m] * SIZE + SIZE / 2, SIZE / 2);
			//fillrectangle(snake.x[m] * SIZE, snake.y[m] * SIZE, snake.x[m] * SIZE + SIZE, snake.y[m] * SIZE + SIZE);
		}
	}
}

int win(int grade)//�ж���Ӯ
{
	if (score >= grade)//������1���ȴﵽ50�֣������1ʤ��
		return 1;
	else if (score2 >= grade)//�������2ʤ��
		return 2;
}

void wall()//���ϰ���
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

void double_score_rule()//���������
{
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 3 * SIZE, "���1:");
	setfillcolor(GREEN);
	fillcircle(34 * SIZE + SIZE / 2, 3 * SIZE + SIZE / 2, SIZE / 2);

	//��������
	//fillcircle(snake.x[0] * SIZE + SIZE / 2, snake.y[0] * SIZE + SIZE / 2, SIZE / 2);
	for (int k = 35; k <38; k++)
	{
		//snake.x[k] = snake.x[k - 1] + 1;//���Ż�����
		//snake.y[k] = snake.y[k - 1];//�����겻��
		//moveto(snake.x[k] * SIZE, snake.y[k] * SIZE);
		setfillcolor(RED);
		//fillcircle(snake.x[k]*SIZE+SIZE/2, snake.y[k]*SIZE+SIZE/2, SIZE/2);
		//fillrectangle(k * SIZE, 3 * SIZE, k * SIZE + SIZE, 3 * SIZE + SIZE);
		fillcircle(k * SIZE + SIZE / 2, 3 * SIZE + SIZE / 2, SIZE / 2);
	}
	char count1[5];
	itoa(score, count1, 10);//������ת��Ϊ�ַ���
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 5 * SIZE, "����:");
	setfillcolor(BLACK);
	solidrectangle(34 * SIZE, 5 * SIZE, 38 * SIZE + SIZE, 5 * SIZE + SIZE);
	outtextxy(34 * SIZE, 5 * SIZE, count1);
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 7 * SIZE, "���2:");
	setfillcolor(BLUE);
	fillcircle(new_snake.x[0] * SIZE + SIZE / 2, new_snake.y[0] * SIZE + SIZE / 2, SIZE / 2);

	//��������
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
	outtextxy(31 * SIZE, 9 * SIZE, "����:");
	setfillcolor(BLACK);
	solidrectangle(34 * SIZE, 9 * SIZE, 38 * SIZE + SIZE, 9 * SIZE + SIZE);
	outtextxy(34 * SIZE, 9 * SIZE, count2);
	line(30 * SIZE, 11 * SIZE, 40 * SIZE, 11 * SIZE);
	settextcolor(RED);
	outtextxy(31 * SIZE, 13 * SIZE, "���1:");
	settextcolor(GREEN);
	outtextxy(31 * SIZE, 14 * SIZE, "  w: ��   s: ��");
	outtextxy(31 * SIZE, 15 * SIZE, "  a: ��   d: ��");
	settextcolor(RED);
	outtextxy(31 * SIZE, 17 * SIZE, "���2:");
	settextcolor(GREEN);
	outtextxy(31 * SIZE, 18 * SIZE, "  i: ��   k: ��");
	outtextxy(31 * SIZE, 19 * SIZE, "  j: ��   l: ��");
	settextcolor(RED);
	outtextxy(31 * SIZE, 21 * SIZE, "����:");
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 23 * SIZE, "1.���ȴﵽĿ�����");
	outtextxy(31 * SIZE, 24 * SIZE, "  ʤ����");
	outtextxy(31 * SIZE, 25 * SIZE, "2.��Ϸ������������");
	outtextxy(31 * SIZE, 26 * SIZE, "  �Է����壬���15");
	outtextxy(31 * SIZE, 27 * SIZE, "  �֣����ڳ�ʼλ��");
	outtextxy(31 * SIZE, 28 * SIZE, "  ����");
}

void score_rule()
{
	char count[5];
	FILE *fp;
	fp = fopen("maxscore", "a+");//��ȡ�ļ��е�����
	if (fp != NULL)
	{
		settextcolor(GREEN);
		while (fgets(maxScore, 5, fp) != NULL)//���ļ��е�����д��maxScore������
			outtextxy(35 * SIZE, 5 * SIZE, maxScore);//����߷���ʾ�ڻ�����
		fclose(fp);
	}
	itoa(score, count, 10);//������ת��Ϊ�ַ���
	settextcolor(WHITE);
	outtextxy(31 * SIZE, 3 * SIZE, "����:");
	setfillcolor(BLACK);
	solidrectangle(34 * SIZE, 3 * SIZE, 38 * SIZE + SIZE, 3 * SIZE + SIZE);
	outtextxy(34 * SIZE, 3 * SIZE, count);
	outtextxy(31 * SIZE, 5 * SIZE, "��߷�:");
	line(30 * SIZE, 9 * SIZE, 40 * SIZE, 9 * SIZE);
	outtextxy(31 * SIZE, 11 * SIZE, "  w:     ��");
	outtextxy(31 * SIZE, 13 * SIZE, "  s:     ��");
	outtextxy(31 * SIZE, 15 * SIZE, "  a:     ��");
	outtextxy(31 * SIZE, 17 * SIZE, "  d:     ��");
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

	//����Χ��
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
	InputBox(str, 100, "��ѡ��\n\n 1.��ͳģʽ\n\n 2.˫��PK\n\n 3.�˳���Ϸ", "���ߴ���ս", "", 250, 100, false);
	if (strcmp(str, "1") == 0)
	{

		PlaySound("D:\\VS��Ŀ\\Snake_bgm\\bgm1.WAV", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		start();
		initmap();
		wall();
		score_rule();
		srand(time(NULL));
		play();
	}
	else if (strcmp(str, "2") == 0)
	{
		PlaySound("D:\\VS��Ŀ\\Snake_bgm\\double_play.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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

void double_play()//��ʼ˫��PK��Ϸ
{
	char str[5];
	int len;
	int grade;
	while (1)
	{
		int flag = 1;
		InputBox(str, 5, "������Ŀ�����(1~1000)\nֻ����������", "���ߴ���ս", "", 200, 100, false);
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
	outtextxy(31 * SIZE, 1 * SIZE, "Ŀ�����:");
	settextcolor(BROWN);
	outtextxy(36 * SIZE, 1 * SIZE, str);
	char k = 'a';
	char t = LEFT2;  //k��t�ֱ��¼��ǰһʱ���ƶ��ķ���
	new_snake.count = 0;
	snake.count = 0;
	score = 0;
	score2 = 0;
	new_chushihua();
	chushihua();  //��ʼ��
	int move1 = 0, move2 = 0;//��ǰ����Ĺ���
	char key, key1 = LEFT, key2 = LEFT2;//��ʼ����
	double_getfood();//����ʳ��
	while (1)
	{
		double_eatfood();//�ж��Ƿ�Ե�ʳ��
		double_move2();
		double_move1();//�ƶ���
		move1 = 0;
		move2 = 0;
		if (kbhit())//����а���
		{
			key = getch();//��ȡ����ֵ
			switch (key)//�жϰ���
			{

			case UP2:
			case DOWN2:
			case LEFT2:
			case RIGHT2:key2 = key; move2 = 1; break;//��������������2��move2=1��
			case UP:
			case DOWN:
			case LEFT:
			case RIGHT:key1 = key; move1 = 1; break;//��������������1��move1=1��
			}
		}
		if (move1 == 1)//���move1=1���������������1
		{
			if (k == LEFT && key1 == RIGHT)    //��ֹ����ҧ���Լ�
				key1 = LEFT;
			else if (k == UP && key1 == DOWN)
				key1 = UP;
			else if (k == RIGHT && key1 == LEFT)
				key1 = RIGHT;
			else if (k == DOWN && key1 == UP)
				key1 = DOWN;
			turn(key1);//ת��
		}
		if (move2 == 1)//���move2=1���������������2
		{
			if (t == UP2 && key2 == DOWN2)    //��ֹ����ҧ���Լ�
				key2 = UP2;
			else if (t == DOWN2 && key2 == UP2)
				key2 = DOWN2;
			else if (t == LEFT2 && key2 == RIGHT2)
				key2 = LEFT2;
			else if (t == RIGHT2 && key2 == LEFT2)
				key2 = RIGHT2;
			double_turn(key2);//ת��
		}

		if (move2 == 0)//��������������1�������2���߼���ά����һʱ�̵ķ���
			double_turn(t);
		if (move1 == 0)//��������������2�������1���߼���ά����һʱ�̵ķ���
			turn(k);

		k = key1;
		t = key2;//��ȡ��һʱ�̵ķ���
				 //fflush(stdin);
				 //print();

		if (double_die1())//�ж����1�Ƿ�����
		{
			//PlaySound("F:\\Snake_bgm\\gameover.WAV", NULL, SND_FILENAME | SND_ASYNC);
			if (score >= 15)//�����������15��
				score -= 15;
			else      //�������С��15�֣����������
				score = 0;
			for (m = 0; m<snake.len; m++)//�����󣬽������ñ���ɫ����
			{
				setfillcolor(BLACK);
				solidrectangle(snake.x[m] * SIZE, snake.y[m] * SIZE, snake.x[m] * SIZE + SIZE, snake.y[m] * SIZE + SIZE);
			}
			k = key1 = LEFT;
			chushihua();//��ʼ����
		}
		if (double_die2())//������2����
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
		double_print();//����
		double_initmap();
		double_score_rule();
		if (win(grade) == 1)//������1ʤ��
		{
			PlaySound("D:\\VS��Ŀ\\Snake_bgm\\win.WAV", NULL, SND_FILENAME | SND_ASYNC);
			settextcolor(YELLOW);
			LOGFONT f;
			gettextstyle(&f);                     // ��ȡ��ǰ��������
			f.lfHeight = 48;                      // ��?�����߶��? 48
			_tcscpy(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
			f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
			settextstyle(&f);                     // ����������ʽ
			outtextxy(8 * SIZE, 12 * SIZE, _T("���1ʤ��!"));
			outtextxy(8 * SIZE, 15 * SIZE, _T("���ո������!"));
			while (getch() != ' ')
			{
				;
			}
			break;
		}
		else if (win(grade) == 2)//������2ʤ��
		{
			PlaySound("D:\\VS��Ŀ\\Snake_bgm\\win.WAV", NULL, SND_FILENAME | SND_ASYNC);
			settextcolor(YELLOW);
			LOGFONT f;
			gettextstyle(&f);                     // ��ȡ��ǰ��������
			f.lfHeight = 48;                      // ��?�����߶��? 48
			_tcscpy(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
			f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
			settextstyle(&f);                     // ����������ʽ
			outtextxy(8 * SIZE, 12 * SIZE, _T("���2ʤ��!"));
			outtextxy(8 * SIZE, 15 * SIZE, _T("���ո������!"));
			while (getch() != ' ')
			{
				;
			}
			break;
		}
		Sleep(150);
	}
}

void play()   //��ʼ��ͳģʽ��Ϸ
{
	char k = 'a';//k��¼ǰһʱ���ƶ��ķ���
	char ch = 'a';
	snake.count = 0;
	score = 0;
	chushihua();
	getfood();
	while (1)
	{

		if (kbhit())
		{
			while (1)//�����������������ͣ
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
		if (k == 'a'&&ch == 'd')    //��ֹ����ҧ���Լ�
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
			PlaySound("D:\\VS��Ŀ\\Snake_bgm\\gameover.WAV", NULL, SND_FILENAME | SND_ASYNC);
			settextcolor(YELLOW);
			LOGFONT f;
			gettextstyle(&f);                     // ��ȡ��ǰ��������
			f.lfHeight = 48;                      // ��?�����߶��? 48
			_tcscpy(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
			f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
			settextstyle(&f);                     // ����������ʽ
			outtextxy(8 * SIZE, 12 * SIZE, _T("Game Over!"));
			outtextxy(8 * SIZE, 15 * SIZE, _T("���ո������!"));
			FILE *fp;
			int len;
			len = strlen(maxScore);
			maxScore[len] = '\0';
			int maxscore;
			char ms[5];
			maxscore = StringToInt(maxScore, len);//���ַ���ת��Ϊ����
			if (score>maxscore)//����Ƽ�¼
			{
				fp = fopen("maxscore", "w");//���¼�¼д���ļ��������ļ��е�ԭ�������
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
		initmap();//���߿�
		wall();//���ϰ���
		score_rule();//��ʾ�����͹���
		Sleep(snake.speed);//�ٶ�
	}
}