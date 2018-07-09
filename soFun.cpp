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
	struct student *head;       //ͷ�ڵ�
	struct student *p1 = NULL;  //p1���洴�����½ڵ�ĵ�ַ
	struct student *p2 = NULL;  //p2����ԭ�������һ���ڵ�ĵ�ַ

	int n = 0;          //����ǰ����Ľڵ�����Ϊ0��������
	p1 = (struct student *) malloc (sizeof(student));   //����һ���½ڵ�
	p2 = p1;            //����ڵ㿪�ٳɹ�����p2�Ȱ�����ָ�뱣�������Ա�����

	if(p1==NULL) {      //�ڵ㿪�ٲ��ɹ�
		printf ("\nCann't create it, try it again in a moment!\n");
		return NULL;
	} else {            //�ڵ㿪�ٳɹ�
		head = NULL;        //��ʼheadָ��NULL
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
			n += 1;         //�ڵ���������1��
			if(n == 1) {    //����ڵ�������1����headָ��մ����Ľڵ�p1
				head = p1;
				fprintf(fp2,"%s,%s,%s,%s,%s,%s,","ѧ�ţ�","������","�Ա�","�������£�","�༶��","��ϵ��ʽ��");
				for(int j = 1; j <= refNum; j++) {
					fprintf(fp2,"��ί%d,",j);
				}
				fprintf(fp2,"ƽ���֣�\n");
				p2->next = NULL;  //��ʱ��p2����p1,Ҳ����p1->nextָ��NULL��
			} else {
				p2->next = p1;   //ָ���ϴ�����ոտ��ٵ��½ڵ�
			}

			p2 = p1;            //��p1�ĵ�ַ��p2������Ȼ��p1�����µĽڵ�
			Choose_And_Operate(*p1,refNum);
			fprintf(fp2,"%s,%s,%s,%s,%s,%s,",p1->stuNum,p1->name,p1->sex,p1->year,p1->className,p1->phoneNum);
			for(int j = 0; j < refNum; j++) {
				fprintf(fp2,"%d,",p1->score[j]);
			}
			fprintf(fp2,"%lf\n",p1->averageScore);

		}     //ֻҪѧ�Ų�Ϊ0���ͼ���¼����һ���ڵ�
		p1 = (struct student *) malloc (sizeof(student));
	}
	p2->next = NULL;     //�˾���Ǹ��ݵ�����������һ���ڵ�Ҫָ��NULL

	free(p1);           //p1->numΪ0��ʱ��������whileѭ���������ͷ�p1
	p1 = NULL;          //�ر�Ҫ���ǰ��ͷŵı��������ΪNULL,����ͱ��"Ұָ��"������ַ��ȷ����ָ��
	return head;        //���ش��������ͷָ��
}


int main() {
	FILE *fp = NULL;
	FILE *fp2 = NULL;
	student *ptr;
	if((fp = fopen("student.csv","r")) == NULL || (fp2 = fopen("student2.csv","w+")) == NULL) {
		printf("�ļ���ʧ�ܣ����������������!\n");
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
