#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#define MAX_SIZE 100
using namespace std;

struct student {
	char* stuNum;
	char* name;
	char* sex;
	char* year;
	char* className;
	char* phoneNum;
	int score[MAX_SIZE];
	int sumScore;
	double averageScore;
	student *next;
};

int change(char* line) {
	int sum = 0;
	for(int i = 0; line[i] != '\0'; i++) {
		sum = sum * 10 + (line[i] - '0');
	}
	return sum;
}

void Choose_And_Operate(student &d,int refNum) {
	double maxScore = d.score[0];
	double minScore = d.score[0];
	int maxMark = 0;
	int minMark = 0;
	d.sumScore = 0;
	for(int i = 0; i < refNum; i++) {
		if(maxScore < d.score[i]) {
			maxScore = d.score[i];
			maxMark = i;
		}
		if(minScore >= d.score[i]) {
			minScore = d.score[i];
			minMark = i;
		}
	}
	for(int i = 0; i < refNum; i++) {
		if(i == maxMark || i == minMark) {

			cout << "test " << d.score[i] << " ";
			continue;
		} else {
			d.sumScore += d.score[i];
		}
	}
	d.averageScore = d.sumScore / (refNum - 2);
}

student *Create(int refNum,FILE *fp,FILE *fp2) {
	struct student *head;       //头节点
	struct student *p1 = NULL;  //p1保存创建的新节点的地址
	struct student *p2 = NULL;  //p2保存原链表最后一个节点的地址

	int n = 0;          //创建前链表的节点总数为0：空链表
	p1 = (struct student *) malloc (sizeof(student));   //开辟一个新节点
	p2 = p1;            //如果节点开辟成功，则p2先把它的指针保存下来以备后用

	if(p1==NULL) {      //节点开辟不成功
		printf ("\nCann't create it, try it again in a moment!\n");
		return NULL;
	} else {            //节点开辟成功
		head = NULL;        //开始head指向NULL
		char *stuNum = (char*)malloc(sizeof(char));
		char *name = (char*)malloc(sizeof(char));
		char *sex = (char*)malloc(sizeof(char));
		char *year = (char*)malloc(sizeof(char));
		char *className = (char*)malloc(sizeof(char));
		char *phoneNum = (char*)malloc(sizeof(char));
		char *temp = (char*)malloc(sizeof(char));
		while(!feof(fp)) {
			fscanf(fp," %s ,",stuNum);
			fscanf(fp," %s ,",name);
			fscanf(fp," %s ,",sex);
			fscanf(fp," %s ,",year);
			fscanf(fp," %s ,",className);
			fscanf(fp," %s ,",phoneNum);
			p1->stuNum = stuNum;
			p1->name = name;
			p1->sex = sex;
			p1->year = year;
			p1->className = className;
			p1->phoneNum = phoneNum;
			for(int j = 0; j < refNum; j++) {
				fscanf(fp," %s ,",temp);
				p1->score[j] = change(temp);
				cout << endl << p1->score[j] << " ";
			}
			cout << endl;
			n += 1;         //节点总数增加1个
			if(n == 1) {    //如果节点总数是1，则head指向刚创建的节点p1
				head = p1;
				fprintf(fp2,"%s,%s,%s,%s,%s,%s,","学号：","姓名：","性别：","出生年月：","班级：","联系方式：");
				for(int j = 1; j <= refNum; j++) {
					fprintf(fp2,"评委%d,",j);
				}
				fprintf(fp2,"平均分：\n");
				p2->next = NULL;  //此时的p2就是p1,也就是p1->next指向NULL。
			} else {
				p2->next = p1;   //指向上次下面刚刚开辟的新节点
			}

			p2 = p1;            //把p1的地址给p2保留，然后p1产生新的节点
			Choose_And_Operate(*p1,refNum);
			fprintf(fp2,"%s,%s,%s,%s,%s,%s,",p1->stuNum,p1->name,p1->sex,p1->year,p1->className,p1->phoneNum);
			for(int j = 0; j < refNum; j++) {
				fprintf(fp2,"%d,",p1->score[j]);
			}
			fprintf(fp2,"%lf\n",p1->averageScore);

		}     //只要学号不为0，就继续录入下一个节点
		p1 = (struct student *) malloc (sizeof(student));
	}
	p2->next = NULL;     //此句就是根据单向链表的最后一个节点要指向NULL

	free(p1);           //p1->num为0的时候跳出了while循环，并且释放p1
	p1 = NULL;          //特别不要忘记把释放的变量清空置为NULL,否则就变成"野指针"，即地址不确定的指针
	return head;        //返回创建链表的头指针
}


int main() {
	FILE *fp = NULL;
	FILE *fp2 = NULL;
	student *ptr;
	if((fp = fopen("student.csv","r")) == NULL || (fp2 = fopen("student2.csv","w+")) == NULL) {
		printf("文件打开失败，请重启程序后再试!\n");
		exit(0);
	} else {
		char *line = NULL;
		string result[MAX_SIZE];
		char reline[MAX_SIZE];
		int sumNum = 0;
		int refNum = 0;
		if(fgets(reline,MAX_SIZE,fp)) {
			line = strtok(reline,",");
			while(line != NULL) {
				sumNum++;
				line = strtok( NULL,",");
			}
		}
		refNum = sumNum - 6;
		ptr = Create(refNum,fp,fp2);
	}
	fclose(fp);
	fclose(fp2);
	exit(0);
}
