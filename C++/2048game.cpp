#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "getch.h"

using namespace std;

// 创建二维数组
int arr[4][4];
// 是否移动或合并过
bool IS_MOVE_MERGE = true;

// 系统初始化
void init_sys(void)
{
	// 设置随机数获取位置
	srand(time(NULL));
	FILE* frp = fopen("data.txt","r+");
    int i=0,j=0;
	for(i=0; i<4; i++)	//读取文本中的数据到内存
	{
		int num = 0;
		for(j=0; j<4; j++)
		{
			num = fscanf(frp,"%d ",&arr[i][j]);
		}
	}
	fclose(frp);
	IS_MOVE_MERGE = true;
	//system("rm data.txt");
}


// 保存
void save(void)
{
	FILE* fwp = fopen("data.txt","w");
	int i= 0,j=0;
	for(i=0; i<4; i++)	//数据存储回本地
	{
	    int num = 0;
		for(j=0; j<4; j++)
		{
			num = fprintf(fwp,"%d ",arr[i][j]);
		}
	}

	fclose(fwp);
	cout<<"save()"<<endl;
}

// 退出
void quit(void)
{
	FILE* fwp = fopen("data.txt","w");
	cout<<"exit()"<<endl;
}

// 显示界面
void show_view(void)
{
	// 清理屏幕
	system("clear");

	for(int i=0; i<4; i++)
	{
		cout<<"---------------------"<<endl;
		for(int j=0; j<4; j++)
		{
			if(arr[i][j])
				printf("|%4d",arr[i][j]);
			else
				printf("|    ");
		}
		cout<<"|"<<endl;
	}
	cout<<"---------------------"<<endl;
}

bool is_null(void)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(0 == arr[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

// 创建一个数
void creat_num(void)
{
	// 进入循环前要先保证有空位置
	while(is_null()&&IS_MOVE_MERGE)
	{
		int x = rand() % 4;
		int y = rand() % 4;
		if(0 == arr[x][y])
		{
			arr[x][y] = 2;
			break;
		}
	}
}

void up(void)
{
	for(int y=0; y<4; y++)
	{
		int end = 0;
		for(int x=1; x<4; x++)
		{
			for(int m=x; m>end && arr[m][y]; m--)
			{
				if(arr[m][y] == arr[m-1][y])
				{
					arr[m-1][y] *= 2;
					arr[x][y]= 0;
					end = m;
					IS_MOVE_MERGE = true;
				}
				else if(0 == arr[m-1][y])
				{
					arr[m-1][y] = arr[m][y];
					arr[m][y] = 0;
					IS_MOVE_MERGE = true;
				}
			}
		}
	}
}
void down(void)
{
	for(int y=0; y<4; y++)
	{
		int end = 3;
		for(int x=2; x>=0; x--)
		{
			for(int m=x; m<end && arr[m][y]; m++)
			{
				if(arr[m][y] == arr[m+1][y])
				{
					arr[m+1][y] *= 2;
					arr[m][y] = 0;
					end = m;
					IS_MOVE_MERGE = true;
				}
				else if(0 == arr[m+1][y])
				{
					arr[m+1][y] = arr[m][y];
					arr[m][y] = 0;
					IS_MOVE_MERGE = true;
				}
			}
		}
	}
}
void right(void)
{
	for(int x=0; x<4; x++)
	{
		int end = 3;
		for(int y=2; y>=0; y--)
		{
			for(int m=y; m<end && arr[x][m]; m++)
			{
				if(arr[x][m] == arr[x][m+1])
				{
					arr[x][m+1] *= 2;
					arr[x][m] = 0;
					end = m;
					IS_MOVE_MERGE = true;
				}
				else if(0 == arr[x][m+1])
				{
					arr[x][m+1] = arr[x][m];
					arr[x][m] = 0;
					IS_MOVE_MERGE = true;
				}
			}
		}
	}
}

void left(void)
{
	for(int x=0; x<4; x++)
	{
		int end = 0;
		for(int y=1; y<4; y++)
		{
			for(int m=y; m>end && arr[x][m]; m--)
			{
				if(arr[x][m] == arr[x][m-1])
				{
					arr[x][m-1] *= 2;
					arr[x][m] = 0;
					end = m;
					IS_MOVE_MERGE = true;
				}
				else if(0 == arr[x][m-1])
				{
					arr[x][m-1] = arr[x][m];
					arr[x][m] = 0;
					IS_MOVE_MERGE = true;
				}
			}
		}
	}
}

// 判断是否结束
bool is_over(void)
{
	if(is_null())
	{
		return false;
	}

	for(int x=0; x<4; x++)
	{
		for(int y=0; y<3; y++)
		{
			if(arr[x][y] == arr[x][y+1])
			{
				return false;
			}
		}
	}
	for(int x=0; x<3; x++)
	{
		for(int y=0; y<4; y++)
		{
			if(arr[x][y] == arr[x+1][y])
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	init_sys();
	while(1)
	{
		// 创建一个数
		creat_num();
		// 显示界面
		show_view();
		// 判断游戏是否结束
		if(is_over())
		{
			cout<<"游戏结束!"<<endl;
			return 0;
		}
		// 假定此次不能移动或合并
		IS_MOVE_MERGE = false;
		// 获取方向键，并处理
		switch(getch())
		{
			case 183: up(); break;//up
			case 184: down(); break;//down
			case 185: right(); break;//right
			case 186: left(); break;//left
			case 's': save(); return 0;
			case 'S': save(); return 0;
			case 'q': quit(); return 0;
			case 'Q': quit(); return 0;
		}
	}
}

