#include<bits/stdc++.h>
using namespace std;
int call_table[100][100]={0};//行号是第几节课，列号是学生的学号 
int score_table[100]={0};//学生的成绩表 
int score_table_ordered[100]={0};//排序后的学生成绩 
int N;//N个常缺课学生 
int absent_stu_num[100];//存放N个常缺课学生的学号 
int focus_table[100];//算法一需点名的学生名单 
int focus_table2[100];//算法二需点名的学生名单 

void score_table_create(){
	N=5+rand()%3;
	for(int i=0;i<90;i++){
		score_table[i]=40+rand()%60;
		score_table_ordered[i]=score_table[i];
	}
}

void absent_stu_num_create(){//从成绩最差的10个学生中随机生成N个常缺课学生 
	score_table_create();
	sort(score_table_ordered,score_table_ordered+90);
	int cnt=N;
	int flag=score_table_ordered[9];
	for(int i=0;i<90;i++){
		if(cnt==0)break;
		if(score_table[i]<=flag){
			absent_stu_num[cnt-1]=i;
			cnt--;
		}
	}
}

void data_create(){//生成数据集 
	absent_stu_num_create();
	for(int i=0;i<N;i++){
		int absent_class[100]={0};//记录常缺课学生缺了哪几节课 
		int vis[100]={0};//保证常缺课学生随机缺了十六节课 
		for(int j=0;j<16;){
			int index=rand()%19;
			if(vis[index]==0){
				vis[index]=1;
				absent_class[j]=index;
			}
			else continue;
			j++; 
		}
		for(int k=0;k<16;k++){
			call_table[absent_class[k]][absent_stu_num[i]]++;
		}
	}
	
	for(int i=0;i<20;i++){//每节课再随机生成三个缺课学生 
		int M=rand()%3;
		int vis[100]={0};
		int absent_stu[100]={0};
		for(int j=0;j<M;){
			int index=rand()%89;
			if(vis[index]==0){
				vis[index]=1;
				absent_stu[j]=index;
			}
			else continue;
			j++;
		}
		for(int k=0;k<M;k++){
			call_table[i][absent_stu[k]]++;			
		}
	} 
}

double rollcall(){//算法一的点名 
	int correct=0;
	int cnt=0;
	double ans=0;
	for(int i=0;i<90;i++){
		if(call_table[0][i]!=0){
			focus_table[cnt]=i;
			cnt++;
		}
	}
	for(int i=0;i<20;i++){
		for(int j=0;j<90;j++){
			if(call_table[i][j]==1){
				for(int k=0;k<N;k++){
					if(focus_table[k]==j){
						correct++;break;
					}	
				}
			}
		}
	}
	ans=(double)correct/(N*20);
	return ans;
}

double rollcall2(){//算法二的点名 
	int cnt=0;
	int correct=0;
	double ans;
	for(int i=0;i<90;i++){
		if(score_table[i]<=score_table_ordered[9]){
			focus_table2[cnt]=i; 
			cnt++;
			if(cnt==N)break;
		}
	}
	for(int i=0;i<20;i++){
		for(int j=0;j<90;j++){
			if(call_table[i][j]==1){
				for(int k=0;k<N;k++){
					if(focus_table2[k]==j){
						correct++;break;
					}	
				}
			}
		}
	}
	ans=(double)correct/(N*20);
	return ans;
}

void init(){//初始化所需数组 
	memset(call_table,0,sizeof(call_table));
	memset(score_table,0,sizeof(score_table));
	memset(score_table_ordered,0,sizeof(score_table_ordered));
	memset(absent_stu_num,0,sizeof(absent_stu_num));
	memset(focus_table,0,sizeof(absent_stu_num));
	memset(focus_table2,0,sizeof(focus_table2));	
}

int main(){
	double sum=0,sum2=0;
	data_create();
	printf("-----第1次测试详细数据-----\n") ;
	printf("\n常缺课学生名单\n");
	for(int i=0;i<N;i++){
		printf("%d ",absent_stu_num[i]);
	}
	printf("\n常缺课学生成绩\n");
	for(int i=0;i<N;i++){	
		printf("%d ",score_table[absent_stu_num[i]]); 
	}
	for(int i=0;i<20;i++){
		printf("\n第%d节课\n",i); 
		for(int j=0;j<90;j++){
			if(j%10==0)printf("\n");
			printf("%d ",call_table[i][j]);
		} 
	}
	double result=rollcall();
	sum+=result;
	printf("\n第一种算法结果是E=%lf\n",result);
	result=rollcall2();
	sum2+=result;
	printf("第二种算法结果是E=%lf\n",result);
	printf("-----循环一百次结果平均值-----\n");
	for(int i=0;i<99;i++){
		srand(i);
		init();
		data_create();
		printf("---第%d次测试---\n",i+1);
		result=rollcall();
		sum+=result;		
		printf("第一种算法结果是E=%lf\n",result);
		result=rollcall2();
		sum2+=result;
		printf("第二种算法结果是E=%lf\n",result);
		printf("N=%d\n",N);
	}
	printf("\n----循环一百次的均值----\n");
	printf("算法一的E=%lf  算法二的E=%lf\n",sum/100,sum2/100);		
}
