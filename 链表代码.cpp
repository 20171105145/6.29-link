//
//  main.cpp
//  7.9
//
//  Created by 杜炎峰 on 2018/7/9.
//  Copyright © 2018年 杜炎峰. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <tzfile.h>
#include <string>
#define MAX_SIZE 1000
using namespace std;

struct student{
    string name;
    string stuNum;
    string sex;
    string year;
    string className;
    string phoneNum;
    double score[MAX_SIZE];
    double sumScore;
    double averageScore;
    int refNum;
    student *next;
    int num;
};

void Choose_And_Operate(student *d) {
    double maxScore = d->score[0];
    double minScore = d->score[0];
    int maxMark = 0;
    int minMark = 1;
    for(int i = 0;i < d->refNum;i++) {
        if(maxScore < d->score[i]) {
            maxScore = d->score[i];
            maxMark = i;
        }
        if(minScore <= d->score[i]) {
            minScore = d->score[i];
            minMark = i;
        }
    }
    for(int i = 0;i < d->refNum;i++) {
        if(i == maxMark || i == minMark) {
            continue;
        } else {
            d->sumScore += d->score[i];
        }
    }
    d->averageScore = d->sumScore / (d->refNum - 2);
}

student Create(student *d,FILE *fp) {
    student *head,*tail,*p;
    head = (student*)malloc(sizeof(struct student));
    
    return *head;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
