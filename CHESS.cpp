/***************************************************************************************************************************************************************
����û�����ľ�����2.0��֮���Խ�2.0��������Ϊֻ�����һ�Σ�������Ϊԭ��д�õĴ��뱻��ɾ�ˣ��汾��Ҳû�ˣ�
ʹ�ù��ߣ�EasyX�⺯��������֮��ȫ��C���﷨
�ô�����Ҫ���������֣�ͼ�ν��棨main��rules��choose��set��slight��delight��vs�����ƶ�����ϵͳ��vs��availabel��������ָ��ϵͳ��move��suiji��ai��sure����
AI���棺
LEVEL1����ȫ�����
LEVEL2����sure�����ж��˲��ɷ�ʤ���������ߣ�����չ����һ�����Բ������������̣�����sure�Բ��������̽��п�ʤ�ж�����ʤ�ߴ���lose�����м�Ϊ�����߷���֮��������
�߷������һ������ȫ���Ǵ����߷�����ֱ������ߣ�
LEVEL3�ǰ���һ����sure���е��ж���ai���������棬��ɵ�Ч���ǿ��Խ��������ڱ�ʤ���߷�ֱ�������������һ����ɵ�������
LEVEL4�ǵ�������3�Σ���Ϊ�ڲ�level��ֵ��ʵ��5������ɵ�Ч���ǿ��Խ��������ڱ�ʤ���߷�ֱ�����������������������ɵ�������
LEVEL5���ǵ�������4�Σ�level=6������ɵ�Ч���ǿ��Խ��������ڱ�ʤ���߷�ֱ�����������������������ɵ�������
�����ڸ���ľ����ԣ�ֻ�����ֿ������������ڱ�ʤ���߷����ʶ�LEVEL5����û�����壩
***************************************************************************************************************************************************************/
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#define LEFT 210
#define TOP 200/*�������ϽǶ���*/
#define Point(p,x) (((p)->position & (3<<(2*(x))))>>(2*(x)))/*��Ӧ���ϵĶ���*/
#define Setchess(a,img) (putimage(LEFT + 1 + fabs((a) % 3 * 80),TOP + 1 + (a) / 3 * 80,img))
#define Clear(a) clearrectangle(LEFT + 1 + fabs((a) % 3 * 80), TOP + 1 + (a) / 3 * 80, LEFT + 79 + fabs((a) % 3 * 80), TOP + 79 + (a) / 3 * 80)/*���һ����*/
#define light(a) fillrectangle(LEFT + 1 + fabs((a) % 3 * 80), TOP + 1 + (a) / 3 * 80, LEFT + 79 + fabs((a) % 3 * 80), TOP + 79 + (a) / 3 * 80)/*������ѡ��*/
IMAGE player1, player2, player1win, player2win;
int mode, which,T;
typedef struct board {
	unsigned long position;
	struct board *ahead;
	struct board *next;
}board;/*����*/
void slight(int *a)/*����*/
{
	int i;
	setfillcolor(0x55FFFF);
	for (i = 0; i < 3; i++)
	{
		if (a[i] != -1)
		{
			light(a[i]);
		}
	}
}
void delight(int *a)/*ȡ������*/
{
	int i;
	for (i = 0; i < 3; i++)
		if (a[i] != -1)
		{
			Clear(a[i]);
		}
}
int available(int a, int *b, board *p,int obj)/*��ѡ��*/
{
	int sum=0, t;
	board q;
	b[0] = b[1] = b[2] = -1;
	switch (a)
	{
	case 0:
		if (!Point(p, 1)) b[sum++] = 1;
		if (!Point(p, 3)) b[sum++] = 3;
		break;				
	case 1:					
		if (!Point(p, 0)) b[sum++] = 0;
		if (!Point(p, 2)) b[sum++] = 2;
		if (!Point(p, 4)) b[sum++] = 4;
		break;				
	case 2:					
		if (!Point(p, 1)) b[sum++] = 1;
		if (!Point(p, 5)) b[sum++] = 5;
		break;				
	case 3:					
		if (!Point(p, 0)) b[sum++] = 0;
		if (!Point(p, 4)) b[sum++] = 4;
		if (!Point(p, 6)) b[sum++] = 6;
		break;				
	case 4:					
		if (!Point(p, 1)) b[sum++] = 1;
		if (!Point(p, 3)) b[sum++] = 3;
		if (!Point(p, 5)) b[sum++] = 5;
		if (!Point(p, 7)) b[sum++] = 7;
		break;				
	case 5:					
		if (!Point(p, 2)) b[sum++] = 2;
		if (!Point(p, 4)) b[sum++] = 4;
		if (!Point(p, 8)) b[sum++] = 8;
		break;				
	case 6:;				
		if (!Point(p, 3)) b[sum++] = 3;
		if (!Point(p, 7)) b[sum++] = 7;
		break;				
	case 7:					
		if (!Point(p, 4)) b[sum++] = 4;
		if (!Point(p, 6)) b[sum++] = 6;
		if (!Point(p, 8)) b[sum++] = 8;
		break;				
	case 8:					
		if (!Point(p, 5)) b[sum++] = 5;
		if (!Point(p, 7)) b[sum++] = 7;
		break;
	}
	for (t = sum--; sum >= 0; sum--)
	{
		q.position = p->position & ~((3 << (2 * a)) + (3 << (2 * b[sum]))) | (obj << (2 * b[sum]));
		if (Point(&q, 4) && (((Point(&q, 0) == Point(&q, 1)) && (Point(&q, 1) == Point(&q, 2)) && ((Point(&q, 3) == Point(&q, 4)) && (Point(&q, 4) == Point(&q, 5)))) || (((Point(&q, 0) == Point(&q, 3)) && (Point(&q, 3) == Point(&q, 6)) && ((Point(&q, 1) == Point(&q, 4)) && (Point(&q, 4) == Point(&q, 7)))))))
			b[sum] = -1;
	}
	return t;
}
void set(board *p)/*չ������*/
{
	setbkcolor(0xFFFFFF);
	clearrectangle(LEFT, TOP, LEFT + 240, TOP + 240);
	setcolor(0);
	int i, k;
	for (i = 0; i < 3; i++)
		for (k = 0; k < 3; k++)
		{
			rectangle(LEFT + k * 80, TOP + i * 80, LEFT + (k + 1) * 80, TOP + (i + 1) * 80);
			if (Point(p, k + 3 * i)==1)
				Setchess(k + 3 * i, &player1);
			if (Point(p, k + 3 * i) == 2)
				Setchess(k + 3 * i, &player2);
		}
	outtextxy(50, 280, "����");
	outtextxy(460, 280, "���¿�ʼ");
	outtextxy(280, 500, "����");
}
int suiji(board *p,int obj,int way[2])/*�������*/
{
	int a[3];
	do
	{
		do {
			way[0] = rand() % 9;
		} while (Point(p, way[0]) != obj);
		if (available(way[0], a, p,obj))
		{
			while ((way[1] = rand() % 3) + 1)
				if (a[way[1]] > -1)
					break;
			break;
		}
	} while (true);
	way[1] = a[way[1]];
	return 1;
}
int sure(board IF, int obj, int way[2])/*ȷ�ϴ˲��ɷ�ʤ��*/
{
	int i, k = 0, we[3], ava[3][3];
	board base = IF;/*��ü�������λ��*/
	for (i = 0; i < 9; i++)
	{
		if (Point(&IF, i) == obj)
			we[k++] = i;
	}
	for (k = 0; k < 3; k++)/*��ÿ�������*/
		available(we[k], ava[k], &IF, obj);
	for (k = 0; k < 3; k++)
		for (i = 0; i < 3; i++)
		{
			if (ava[k][i] > -1)
			{
				IF.position = base.position & ~((3 << (2 * we[k])) + (3 << (2 * ava[k][i]))) | (obj << (2 * ava[k][i]));/*��ͼ��֮���ж��Ƿ�ʤ��*/
				if (Point(&IF, 4) && (((Point(&IF, 0) == Point(&IF, 4)) && (Point(&IF, 8) == Point(&IF, 4))) || ((Point(&IF, 2) == Point(&IF, 4)) && (Point(&IF, 6) == Point(&IF, 4)))))
				{
					way[0] = we[k];
					way[1] = ava[k][i];
					return 1;
				}
			}
		}
	way[0] = way[1] = -1;
	return 0;
}
int ai(board *p, int obj, int *way,int level)/*lv2�����ϵ�AI*/
{
	int we[3], ava[3][3], lose[7][2] = { {-1 ,-1} ,{-1,-1} ,{-1,-1} ,{-1, -1} ,{ -1, -1} ,{ -1, -1}, { -1, -1} }, lost = 0, sum = 0, i, k = 0,flag;
	board IF;
	if (sure(*p,obj,way))/*һ��ʤҲ��ʤ*/
		return 1;
	for (i = 0; i < 9; i++)/*�õ���������λ��*/
		if (Point(p, i) == obj)
			we[k++] = i;
	for (k = 0; k < 3; k++)/*�õ����п��ߵ�λ��*/
		sum+=available(we[k], ava[k], p, obj);
	for (k=0;k<3;k++)/*��ÿһ���߷����з���*/
		for (i = 0; i < 3; i++)
			if (ava[k][i] > -1)
			{
				IF.position = p->position & ~((3 << (2 * we[k])) + (3 << (2 * ava[k][i]))) | (obj << (2 * ava[k][i]));
				if (level == 2)/*����ֻ��Ҫ�ж���һ���᲻�����̴���ʧ�ܣ��ִܾ���lose������*/
					if (obj == 1)
					{
						if (sure(IF, 2, way))
						{
							lose[lost][0] = we[k];
							lose[lost++][1] = ava[k][i];
							continue;
						}
					}
					else
					{
						if (sure(IF, 1, way))
						{
							lose[lost][0] = we[k];
							lose[lost++][1] = ava[k][i];
							continue;
						}
					}
				else/*���߼�����и�Զ���ж�*/
				{
					if (obj == 1)
					{
						if ((flag = ai(&IF, 2, way, level - 1)) < 0)/*�з������ұ�ʤ*/
						{
							way[0] = we[k];
							way[1] = ava[k][i];
							return 1;
						}
						else if (flag > 0)/*�з���ʤ��·��ͨ*/
						{
							lose[lost][0] = we[k];
							lose[lost++][1] = ava[k][i];
							continue;
						}
					}
					else 
					{
						if ((flag = ai(&IF, 1, way, level - 1)) < 0)/*�з������ұ�ʤ*/
						{
							way[0] = we[k];
							way[1] = ava[k][i];
							return 1;
						}
						else if (flag > 0)/*�з���ʤ��·��ͨ*/
						{
							lose[lost][0] = we[k];
							lose[lost++][1] = ava[k][i];
							continue;
						}
					}
				}
			}
	if (lost == sum)/*��·���ߣ�����*/
	{
		suiji(p, obj, way);
		return -1;
	}
	else/*��һ�����Ǳ����·*/
	{
		while (true)
		{
			suiji(p, obj, way);
			for (i = 0; i < 7 && (way[0] != lose[i][0] || way[1] != lose[i][1]); i++);
			if (i == 7)
				return 0;
		}
	}
}
board *move(board *p, long obj,int *way)/*��Ҷ��ӣ�ͨ�������߷�������way�����У�*/
{
	MOUSEMSG m;
	int from, to, a[3], flag = 0, flag2;
	while (true)/*ѡ���Լ��˵�*/
	{
		m = GetMouseMsg();
		/*�����ǲ˵�������Ӧ*/
		if ((m.x > 50) && (m.x < 130) && (m.y > 280) && (m.y < 340))
		{
			if (flag != 1)
			{
				settextcolor(0x0000EE);
				outtextxy(50, 280, "����");
				settextcolor(0);
				flag = 1;
			}
		}
		else if ((m.x > 460) && (m.x < 620) && (m.y > 280) && (m.y < 340))
		{
			if (flag != 2)
			{
				settextcolor(0x0000EE);
				outtextxy(460, 280, "���¿�ʼ");
				settextcolor(0);
				flag = 2;
			}
		}
		else if ((m.x > 280) && (m.x < 360) && (m.y > 500) && (m.y < 560))
		{
			if (flag != 3)
			{
				settextcolor(0x0000EE);
				outtextxy(280, 500, "����");
				settextcolor(0);
				flag = 3;
			}
		}
		else if (flag)
		{
			outtextxy(50, 280, "����");
			outtextxy(460, 280, "���¿�ʼ");
			outtextxy(280, 500, "����");
			flag = 0;
		}/*����Ϊѡ��ʱ�����������Ӧ*/
		if ((m.uMsg == WM_LBUTTONDOWN) && (m.x > LEFT) && (m.x < LEFT + 240) && (m.y > TOP) && (m.y < TOP + 240))
		{
			from = (m.x - LEFT) / 80 + (m.y - TOP) / 80 * 3;/*������ͣ��λ�õ����*/
			if (Point(p, from) == obj)
				break;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)/*�˵������Ӧ*/
			switch (flag)
			{
			case 1:
				if (mode == 1)
				{
					if (p->ahead)
					{
						p = p->ahead;
						free(p->next);
						set(p);
						way[0] = way[1] = -1;
						return p;
					}
				}
				else if (p->ahead && (p->ahead)->ahead)
					{
						p = p->ahead;
						free(p->next);
						p = p->ahead;
						free(p->next);
						set(p);
						break;
					}
				break;
			case 2:
				while (p->ahead)
				{
					p = p->ahead;
					free(p->next);
				}
				set(p);
				if ((obj == 2) || (which == 2))
				{
					way[0] = way[1] = -1;
					return p;
				}
				break;
			case 3:
				while (p->ahead)
				{
					p = p->ahead;
					free(p->next);
				}
				way[0] = way[1] = -2;
				return p;
			case 0:break;
			}
	}
	available(from, a, p,obj);
	slight(a);
	while (true)/*ѡλ*/
	{
		m = GetMouseMsg();
		/*�����ǲ˵����������Ӧ*/
		if ((m.x > 50) && (m.x < 130) && (m.y > 280) && (m.y < 340))
		{
			if (flag != 1)
			{
				settextcolor(0x0000EE);
				outtextxy(50, 280, "����");
				settextcolor(0);
				flag = 1;
			}
		}
		else if ((m.x > 460) && (m.x < 620) && (m.y > 280) && (m.y < 340))
		{
			if (flag != 2)
			{
				settextcolor(0x0000EE);
				outtextxy(460, 280, "���¿�ʼ");
				settextcolor(0);
				flag = 2;
			}
		}
		else if ((m.x > 280) && (m.x < 360) && (m.y > 500) && (m.y < 560))
		{
			if (flag != 3)
			{
				settextcolor(0x0000EE);
				outtextxy(280, 500, "����");
				settextcolor(0);
				flag = 3;
			}
		}
		else if (flag)
		{
			outtextxy(50, 280, "����");
			outtextxy(460, 280, "���¿�ʼ");
			outtextxy(280, 500, "����");
			flag = 0;
		}/*����Ϊ�˵�*/
		if ((m.uMsg == WM_LBUTTONUP) && (m.x > LEFT) && (m.x < LEFT + 240) && (m.y > TOP) && (m.y < TOP + 240))/*����*/
		{
			to = (m.x - LEFT) / 80 + (m.y - TOP) / 80 * 3;
			if ((to == a[0]) || (to == a[1]) || (to == a[2]))
			{
				delight(a);
				way[0] = from; way[1] = to;
				break;
			}
			else if (Point(p, to) == obj)/*�л�ѡ��*/
			{
				delight(a);
				available(from = to, a, p,obj);
				slight(a);
			}
		}
		else if (m.uMsg == WM_LBUTTONDOWN)/*�˵������Ӧ*/
			switch (flag)
			{
			case 1:
				if (mode == 1)
				{
					if (p->ahead)
					{
						p = p->ahead;
						free(p->next);
						set(p);
						way[0] = way[1] = -1;
						return p;
					}
				}
				else if (p->ahead && (p->ahead)->ahead)
				{
					p = p->ahead;
					free(p->next);
					p = p->ahead;
					free(p->next);
					set(p);
					p=move(p, obj, way);
					return p;
				}
				break;
			case 2:
				while (p->ahead)
				{
					p = p->ahead;
					free(p->next);
				}
				set(p);
				if ((obj == 2) || (which == 2))
				{
					way[0] = way[1] = -1;
					return p;
				}
				break;
			case 3:
				while (p->ahead)
				{
					p = p->ahead;
					free(p->next);
				}
				way[0] = way[1] = -2;
				p->next = NULL;
				return p;
			}
	}
	return p;
}
void vs(int *level)/*�����������*/
{
	MOUSEMSG m;
	setbkcolor(0xFFFFFF);
	settextcolor(BLACK);
	int way[2];
	board beginning = { 0250052,NULL,&beginning }, *head = &beginning, *p = head;
	/*position�ĵ�18λ�ϱ�ʾ����,���Ͻ�Ϊ��2λ*/
	cleardevice();
	set(p);/*չ������*/
	while (!Point(p, 4) ||!(((Point(p, 0) == Point(p, 4)) && (Point(p, 8) == Point(p, 4))) || ((Point(p, 2) == Point(p, 4)) && (Point(p, 6) == Point(p, 4)))))
	{/*�����˸���ģʽ�Ķ���*/
		if (which != 2)/*��ʾͼ��*/
			Setchess(-7, &player1);
		else
			Setchess(-7, &player2);
		if (mode == 3)/*��������ָ��*/
		{
			if (level[0] == 1)
				suiji(p, 1, way);
			else
				ai(p, 1, way, level[0]);
			Sleep(T);
		}
		else if (which != 2)
			p = move(p, 1, way);
		else
			if (level[1] == 1)
				suiji(p, 2, way);
			else
				ai(p, 2, way, level[1]);
		if (way[0] == -2)/*�ж���������ָ�-2ָ�������˵���-1��ʾ�л����ӵ��ˣ���������ǰ����*/
			return;
		else if (way[0] != -1)
		{
			if (p->next = (board *)malloc(sizeof(board)))
			{
				p->next->position = p->position;
				p->next->ahead = p;
				p = p->next;
				if (which!=2)
					p->position = p->position & ~((3 << (2 * way[0])) + (3 << (2 * way[1]))) | (1 << (2 * way[1]));/*��ͼ*/
				else 
					p->position = p->position & ~((3 << (2 * way[0])) + (3 << (2 * way[1]))) | (2 << (2 * way[1]));
				if (which != 2)/*�ƶ���Ļ�ϵ�����*/
				{
					Clear(way[0]);
					Setchess(way[1], &player1);
				}
				else
				{
					Clear(way[0]);
					Setchess(way[1], &player2);
				}
			}
			if (Point(p, 4) && (((Point(p, 0) == Point(p, 4)) && (Point(p, 8) == Point(p, 4))) || ((Point(p, 2) == Point(p, 4)) && (Point(p, 6) == Point(p, 4)))))
				break;/*�жϽ�����*/
		}
		/*����Ϊ���ֶ��ӣ�����Ϊ���ֶ��ӣ��ṹͬ��*/
		if (which != 2)
			Setchess(-7, &player2);
		else
			Setchess(-7, &player1);
		if (mode == 1)
			p = move(p, 2, way);
		else if (mode == 3)
		{
			if (level[1] == 1)
				suiji(p, 2, way);
			else
				ai(p, 2, way, level[1]);
			Sleep(T);
		}
		else if (which == 1)
			if (level[1] == 1)
				suiji(p, 2, way);
			else
				ai(p, 2, way, level[1]);
		else
			p=move(p, 1, way);
		if (way[0] == -2)
			return;
		else if (way[0] != -1)
		{
			if (p->next = (board *)malloc(sizeof(board)))
			{
				p->next->position = p->position;
				p->next->ahead = p;
				p = p->next;
				if (which!=2)
					p->position = p->position & ~((3 << (2 * way[0])) + (3 << (2 * way[1]))) | (2 << (2 * way[1]));/*��ͼ*/
				else 
					p->position = p->position & ~((3 << (2 * way[0])) + (3 << (2 * way[1]))) | (1 << (2 * way[1]));
			}
			if (which != 2)
			{
				Clear(way[0]);
				Setchess(way[1], &player2);
			}
			else
			{
				Clear(way[0]);
				Setchess(way[1], &player1);
			}
			if (Point(p, 4) && (((Point(p, 0) == Point(p, 4)) && (Point(p, 8) == Point(p, 4))) || ((Point(p, 2) == Point(p, 4)) && (Point(p, 6) == Point(p, 4)))))
				break;/*�жϽ�����*/
		}
	}
	settextstyle(60, 20, 0);
	settextcolor(0x0000EE);
	if (mode == 1)/*������Ϸ�����ı�־*/
		outtextxy(LEFT + 80, TOP - 80, "WIN!");
	else if (mode==2)
		if (Point(p, 4) == 1)
			outtextxy(LEFT + 40, TOP - 80, "YOU WIN!");
		else
			outtextxy(LEFT + 30, TOP - 80, "YOU LOSE!");
	else if (Point(p, 4) == 1)
		outtextxy(LEFT + 40, TOP - 80, "�ȷ�����");
	else
		outtextxy(LEFT + 40, TOP - 80, "��������");
	if (Point(p, 4) == 1)
		Setchess(-7, &player1win);
	else
		Setchess(-7, &player2win);
	while (p->ahead)/*�������*/
	{
		p = p->ahead;
		free(p->next);
	}
	int flag = 0;
	outtextxy(460, 280, "����һ��");
	/*�����ǲ˵�*/
	while (true)
	{
		m = GetMouseMsg();
		if ((m.x > 50) && (m.x < 130) && (m.y > 280) && (m.y < 340))
		{
			if (flag != 1)
			{
				settextcolor(0x0000EE);
				outtextxy(50, 280, "����");
				settextcolor(0);
				flag = 1;
			}
		}
		else if ((m.x > 460) && (m.x < 620) && (m.y > 280) && (m.y < 340))
		{
			if (flag != 2)
			{
				settextcolor(0x0000EE);
				outtextxy(460, 280, "����һ��");
				settextcolor(0);
				flag = 2;
			}
		}
		else if ((m.x > 280) && (m.x < 360) && (m.y > 500) && (m.y < 560))
		{
			if (flag != 3)
			{
				settextcolor(0x0000EE);
				outtextxy(280, 500, "����");
				settextcolor(0);
				flag = 3;
			}
		}
		else if (flag)
		{
			outtextxy(50, 280, "����");
			outtextxy(460, 280, "����һ��");
			outtextxy(280, 500, "����");
			flag = 0;
		}/*����Ϊ�˵�*/
		if (m.uMsg == WM_LBUTTONDOWN)
			switch (flag)
			{
			case 1: break;
			case 2:vs(level);return;
			case 3:return;
			default: break;
			}
	}
}
void choose(void)/*ѡ��AI�Ѷȡ��Ⱥ����Լ�EVEƵ�ʽ���*/
{
	MOUSEMSG m;
	int  level[2] = { 0,0 };
	setbkcolor(0xFFFFFF);
	settextcolor(BLACK);;
	which = T = 0;
	int flag1 = 0, flag2 = 0, flag3 = 0;
	srand((unsigned)time(NULL));
	cleardevice();
	loadimage(NULL, _T("PNG"), _T("VS"), 640, 640, 0);
	outtextxy(440, 160, "LEVEL1");
	outtextxy(440, 240, "LEVEL2");
	outtextxy(440, 320, "LEVEL3");
	outtextxy(440, 400, "LEVEL4");
	outtextxy(440, 480, "LEVEL5");
	if (mode == 2)
	{
		outtextxy(80, 320, "���");
		level[0] = 5;
		outtextxy(290, 100, "PVE");
		loadimage(&player1, _T("PNG"), _T("player"), 79, 79);
		putimage(80, 60, &player1);
	}
	else
	{
		outtextxy(80, 160, "LEVEL1");
		outtextxy(80, 240, "LEVEL2");
		outtextxy(80, 320, "LEVEL3");
		outtextxy(80, 400, "LEVEL4");
		outtextxy(80, 480, "LEVEL5");
		outtextxy(290, 100, "EVE");
	}
	while (true)/*AI�ѶȲ˵���Ӧ*/
	{
		m = GetMouseMsg();
		/*�������Ҳ�AI�������Ч��*/
		if (m.x > 440 && m.x < 560 && m.y>160 && m.y < 220)
		{
			if (flag1 != 1)
			{
				settextcolor(0x0000EE);
				settextstyle(24, 8, 0);
				clearrectangle(440, 160, 570, 220);
				outtextxy(440, 180, "������Ϥ����");
				settextstyle(60, 20, 0);
				settextcolor(BLACK);
				flag1 = 1;
			}
		}
		else if (m.x > 440 && m.x < 560 && m.y>240 && m.y < 300)
		{
			if (flag1 != 2)
			{
				settextcolor(0x0000EE);
				settextstyle(24, 8, 0);
				clearrectangle(440, 240, 570, 300);
				outtextxy(440, 260, "AI�ո����׹���");
				settextstyle(60, 20, 0);
				settextcolor(BLACK);
				flag1 = 2;
			}
		}
		else if (m.x > 440 && m.x < 560 && m.y>320 && m.y < 380)
		{
			if (flag1 != 3)
			{
				settextcolor(0x0000EE);
				settextstyle(24, 8, 0);
				clearrectangle(440, 320, 570, 380);
				outtextxy(440, 340, "AIû��ô������");
				settextstyle(60, 20, 0);
				settextcolor(BLACK);
				flag1 = 3;
			}
		}
		else if (m.x > 440 && m.x < 560 && m.y>400 && m.y < 460)
		{
			if (flag1 != 5)
			{
				settextcolor(0x0000EE);
				settextstyle(24, 8, 0);
				clearrectangle(440, 400, 570, 460);
				outtextxy(440, 420, "�����������");
				settextstyle(60, 20, 0);
				settextcolor(BLACK);
				flag1 = 5;
			}
		}
		else if (m.x > 440 && m.x < 560 && m.y>480 && m.y < 540)
		{
			if (flag1 != 6)
			{
				settextcolor(0x0000EE);
				settextstyle(24, 8, 0);
				clearrectangle(440, 480, 570, 540);
				outtextxy(440, 500, "�����ʧ��");
				settextstyle(60, 20, 0);
				settextcolor(BLACK);
				flag1 = 6;
			}
		}
		else if (flag1)
		{
			outtextxy(440, 160, "LEVEL1");
			outtextxy(440, 240, "LEVEL2");
			outtextxy(440, 320, "LEVEL3");
			outtextxy(440, 400, "LEVEL4");
			outtextxy(440, 480, "LEVEL5");
			flag1 = 0;
		}
		/*���������AI�������Ч��*/
		if (mode == 3)
		{
			if (m.x > 80 && m.x < 200 && m.y>160 && m.y < 220)
			{
				if (flag2 != 1)
				{
					settextcolor(0x0000EE);
					settextstyle(24, 8, 0);
					clearrectangle(80, 160, 210, 220);
					outtextxy(80, 180, "������Ϥ����");
					settextstyle(60, 20, 0);
					settextcolor(BLACK);
					flag2 = 1;
				}
			}
			else if (m.x > 80 && m.x < 200 && m.y>240 && m.y < 300)
			{
				if (flag2 != 2)
				{
					settextcolor(0x0000EE);
					settextstyle(24, 8, 0);
					clearrectangle(80, 240, 210, 300);
					outtextxy(80, 260, "AI�ո����׹���");
					settextstyle(60, 20, 0);
					settextcolor(BLACK);
					flag2 = 2;
				}
			}
			else if (m.x > 80 && m.x < 200 && m.y>320 && m.y < 380)
			{
				if (flag2 != 3)
				{
					settextcolor(0x0000EE);
					settextstyle(24, 8, 0);
					clearrectangle(80, 320, 210, 380);
					outtextxy(80, 340, "AIû��ô������");
					settextstyle(60, 20, 0);
					settextcolor(BLACK);
					flag2 = 3;
				}
			}
			else if (m.x > 80 && m.x < 200 && m.y>400 && m.y < 460)
			{
				if (flag2 != 5)
				{
					settextcolor(0x0000EE);
					settextstyle(24, 8, 0);
					clearrectangle(80, 400, 210, 460);
					outtextxy(80, 420, "�����������");
					settextstyle(60, 20, 0);
					settextcolor(BLACK);
					flag2 = 5;
				}
			}
			else if (m.x > 80 && m.x < 200 && m.y>480 && m.y < 540)
			{
				if (flag2 != 6)
				{
					settextcolor(0x0000EE);
					settextstyle(24, 8, 0);
					clearrectangle(80, 480, 210, 540);
					outtextxy(80, 500, "�����ʧ��");
					settextstyle(60, 20, 0);
					settextcolor(BLACK);
					flag2 = 6;
				}
			}
			else if (flag2)
			{
				outtextxy(80, 160, "LEVEL1");
				outtextxy(80, 240, "LEVEL2");
				outtextxy(80, 320, "LEVEL3");
				outtextxy(80, 400, "LEVEL4");
				outtextxy(80, 480, "LEVEL5");
				flag2 = 0;
			}
		}
		/*�����ǿ�ʼ���������Ч��*/
		if (m.x > 290 && m.x < 350 && m.y>100 && m.y < 160)
		{
			settextcolor(0x0000EE);
			outtextxy(290, 100, "GO��");
			settextcolor(BLACK);
			flag3 = 1;
		}
		else if (flag3)
		{
			if (mode == 2)
				outtextxy(290, 100, "PVE");
			else
				outtextxy(290, 100, "EVE");
			flag3 = 0;
		}
		/*�����ǵ��Ч��*/
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (mode == 3 && flag2)
				level[0] = flag2;
			if (flag1)
				level[1] = flag1;
			if (mode == 3)
			{
				switch (level[0])
				{/*����ͷ��*/
				case 1: loadimage(&player1, _T("PNG"), _T("LEVEL1"), 79, 79, 0); break;
				case 2: loadimage(&player1, _T("PNG"), _T("LEVEL2"), 79, 79, 0); break;
				case 3: loadimage(&player1, _T("PNG"), _T("LEVEL3"), 79, 79, 0); break;
				case 5: loadimage(&player1, _T("PNG"), _T("LEVEL4"), 79, 79, 0); break;
				case 6: loadimage(&player1, _T("PNG"), _T("LEVEL5"), 79, 79, 0); break;
				default:break;
				}
			}
			switch (level[1])
			{/*����ͷ��*/
			case 1: loadimage(&player2, _T("PNG"), _T("LEVEL1"), 79, 79, 0); break;
			case 2: loadimage(&player2, _T("PNG"), _T("LEVEL2"), 79, 79, 0); break;
			case 3: loadimage(&player2, _T("PNG"), _T("LEVEL3"), 79, 79, 0); break;
			case 5: loadimage(&player2, _T("PNG"), _T("LEVEL4"), 79, 79, 0); break;
			case 6: loadimage(&player2, _T("PNG"), _T("LEVEL5"), 79, 79, 0); break;
			default:break;
			}
			if (mode == 3 && level[0])
				putimage(80, 60, &player1);
			if (level[1])
				putimage(480, 60, &player2);
		}
		if (level[0] && level[1])/*˫����ѡ�����*/
			if (m.uMsg == WM_LBUTTONDOWN && flag3)
			{
				if (mode == 2)
					loadimage(&player1win, _T("PNG"), _T("PLAYERWIN"), 79, 79, 0);
				else
					switch (level[0])
					{/*����ʤ����־*/
					case 1: loadimage(&player1win, _T("PNG"), _T("LEVEL1WIN"), 79, 79, 0); break;
					case 2: loadimage(&player1win, _T("PNG"), _T("LEVEL2WIN"), 79, 79, 0); break;
					case 3: loadimage(&player1win, _T("PNG"), _T("LEVEL3WIN"), 79, 79, 0); break;
					case 5: loadimage(&player1win, _T("PNG"), _T("LEVEL4WIN"), 79, 79, 0); break;
					case 6: loadimage(&player1win, _T("PNG"), _T("LEVEL5WIN"), 79, 79, 0); break;
					default:break;
					}
				switch (level[1])
				{/*����ʤ����־*/
				case 1: loadimage(&player2win, _T("PNG"), _T("LEVEL1WIN"), 79, 79, 0); break;
				case 2: loadimage(&player2win, _T("PNG"), _T("LEVEL2WIN"), 79, 79, 0); break;
				case 3: loadimage(&player2win, _T("PNG"), _T("LEVEL3WIN"), 79, 79, 0); break;
				case 5: loadimage(&player2win, _T("PNG"), _T("LEVEL4WIN"), 79, 79, 0); break;
				case 6: loadimage(&player2win, _T("PNG"), _T("LEVEL5WIN"), 79, 79, 0); break;
				default:break;
				}
				break;
			}
	}
	/*������ѡ���Ⱥ��ֽ���*/
	if (mode == 2)
	{
		flag1 = 0;
		cleardevice();
		outtextxy(260, 240, "��ѡ��");
		outtextxy(280, 320, "����");
		outtextxy(280, 400, "����");
		while (true)
		{
			m = GetMouseMsg();
			if (m.x > 280 && m.x < 360 && m.y > 320 && m.y < 380)
			{
				if (flag1 != 1)
				{
					settextcolor(0x0000EE);
					outtextxy(280, 320, "����");
					settextcolor(BLACK);
					flag1 = 1;
				}
			}
			else if (m.x > 280 && m.x < 360 && m.y > 400 && m.y < 460)
			{
				if (flag1 != 2)
				{
					settextcolor(0x0000EE);
					outtextxy(280, 400, "����");
					settextcolor(BLACK);
					flag1 = 2;
				}
			}
			else if (flag1)
			{
				outtextxy(280, 320, "����");
				outtextxy(280, 400, "����");
				flag1 = 0;
			}
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				which = flag1;
				if (which)
					break;
			}
		}
	}
	/*������ѡ��EVEƵ�ʽ���*/
	if (mode == 3)
	{
		flag1 = 0;
		cleardevice();
		outtextxy(260, 240, "��ѡ��");
		outtextxy(240, 320, "�۲����");
		outtextxy(240, 400, "�۲���");
		while (true)
		{
			m = GetMouseMsg();
			if (m.x > 240 && m.x < 400 && m.y > 320 && m.y < 380)
			{
				if (flag1 != 1)
				{
					settextcolor(0x0000EE);
					outtextxy(240, 320, "�۲����");
					settextcolor(BLACK);
					flag1 = 1;
				}
			}
			else if (m.x > 240 && m.x < 400 && m.y > 400 && m.y < 460)
			{
				if (flag1 != 2)
				{
					settextcolor(0x0000EE);
					outtextxy(240, 400, "�۲���");
					settextcolor(BLACK);
					flag1 = 2;
				}
			}
			else if (flag1)
			{
				outtextxy(240, 320, "�۲����");
				outtextxy(240, 400, "�۲���");
				flag1 = 0;
			}
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				switch (flag1)
				{
				case 1:T = 1000; break;
				case 2:T = 10; break;
				default:break;
				}
				if (T)
					break;
			}
		}
	}
	vs(level);
}
void rules(void)/*��ʾ����*/
{
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(RED);
	outtext("��û�����ľ�����     ����");
	settextcolor(0);
	outtextxy(280, 500, "����");
	settextstyle(24, 8, 0);
	outtextxy(0, 80, "1.PVPģʽ��������Ҷ�ս��PVEģʽ���˻���ս");
	outtextxy(0, 160, "2.ʤ��������һ��������ĳ�Խ��߳�һ��ֱ��");
	outtextxy(0, 240, "3.����Ϸ��������һ��bug��������bugʱ����ǿ�ƻ��岢����");
	outtextxy(0, 320, "��������751598415@qq.com��GitHub��https://github.com/LMA936/CHESS");
	outtextxy(0, 400, "��ǣ����Ѿ���������#�ˣ���������ֻʣ���˿ɹ������exe");
	outtextxy(0, 480, "level5�䲻�ˣ��벻Ҫ����˾�����Ϊ��å");
	settextstyle(60, 20, 0);
	/*�˵�*/
	MOUSEMSG m;
	int flag = 0;
	while (true)
	{
		m = GetMouseMsg();
		if ((m.x > 280) && (m.x < 360) && (m.y > 500) && (m.y < 560))
		{
			if (!flag)
			{
				settextcolor(0x0000EE);
				outtextxy(280, 500, "����");
				settextcolor(0);
				flag = 1;
			}
		}
		else if (flag)
		{
			outtextxy(280, 500, "����");
			flag = 0;
		}/*����Ϊ�˵�*/
		if ((m.uMsg == WM_LBUTTONDOWN) && flag)
		{
			settextcolor(WHITE);
			return;
		}
	}
}
int main(void)/*������*/
{
	initgraph(640, 640);
title:
	mode = 0;
	setbkcolor(0);
	cleardevice();
	setcolor(WHITE);
	loadimage(NULL, _T("PNG"), _T("BACKGROUND"), 640, 640,0);
	settextstyle(24, 8, 0);
	outtextxy(292, 36, "(rules)");
	outtextxy(200,610 , "����������棬�������øŲ�����");
	settextstyle(60, 20, 0);
	outtextxy(260, 60, "#CHESS");
	outtextxy(150, 280, "PVP");
	outtextxy(420, 280, "PVE");
	outtextxy(280, 550, "EXIT");
	/*�����Ǵ�ӡ��ʼ����*/
	MOUSEMSG m;
	int flag = 0;
	int a[2] = { 5,5 };
	while (true)/*�˵�*/
	{
		m = GetMouseMsg();
		if ((m.x > 150) && (m.x < 210) && (m.y > 280) && (m.y < 340))
		{
			if (flag != 1)
			{
				settextcolor(0x0000EE);
				outtextxy(150, 280, "PVP");
				settextcolor(WHITE);
				flag = 1;
			}
		}
		else if ((m.x > 420) && (m.x < 480) && (m.y > 280) && (m.y < 340))
		{
			if (flag != 2)
			{
				settextcolor(0x0000EE);
				outtextxy(420, 280, "PVE");
				settextcolor(WHITE);
				flag = 2;
			}
		}
		else if ((m.x > 280) && (m.x < 360) && (m.y > 550) && (m.y < 610))
		{
			if (flag != 3)
			{
				settextcolor(0x0000EE);
				outtextxy(280, 550, "EXIT");
				settextcolor(WHITE);
				flag = 3;
			}
		}
		else if ((m.x > 260) && (m.x < 380) && (m.y > 60) && (m.y < 120))
		{
			if (flag != 4)
			{
				settextcolor(0x0000EE);
				outtextxy(260, 60, "#CHESS");
				settextcolor(WHITE);
				flag = 4;
			}
		}
		else if (flag)
		{
			outtextxy(260, 60, "#CHESS");
			outtextxy(150, 280, "PVP");
			outtextxy(420, 280, "PVE");
			outtextxy(280, 550, "EXIT");
			flag = 0;
		}/*����Ϊ�˵�*/
		/*�����������ͣ��Ӧ�������ǵ����Ӧ*/
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			switch (flag)
			{
			case 0:break;
			case 1:
				mode = 1;
				loadimage(&player1, _T("PNG"), _T("PLAYER"), 79, 79, 0);
				loadimage(&player2, _T("PNG"), _T("LEVEL5"), 79, 79, 0);
				loadimage(&player1win, _T("PNG"), _T("PLAYERWIN"), 79, 79, 0);
				loadimage(&player2win, _T("PNG"), _T("LEVEL5WIN"), 79, 79, 0);
				vs(a);
				goto title;
				break;
			case 2:mode = 2; choose(); goto title; break;
			case 3:closegraph(); return 0;
			case 4:rules(); goto title; break;
			}
			if (m.x>260&&m.x<375&&m.y>250&&m.y<300)/*�ʵ�EVE*/
			{
				mode = 3;
				choose();
				goto title;
			}
		}
	}
}
