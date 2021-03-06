// DoubleInput.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define sampleSize 10     //样本数量
#define ETA_W    0.05    //权值调整率
#define ETA_B    0.05    //阀值调整率
#define trainTimes 100     //一个样本训练次数
#define sampleLoopTimes 5 //所有样本循环次数

const double k_cst = 5; //目标 k & b
const double b_cst = 3;
double input[sampleSize] = { 0 };
double output[sampleSize] = { 0 };
const int plusMinus[2] = { -1,1 };
double k = 0, k2 = 0;  //待训练 k & b
double b = 0, b2 = 0;
double before = 0, after = 0; //一次训练前后误差
int which = 3; //训练哪一组

void IntiTrainingDate()// out = k * in + b 
{
    for (int i = 0; i < sampleSize; i++)
    {
        input[i] = i;
        output[i] = k_cst * i + b_cst;
    }
}

void Training()
{
    bool change = true;
    for (int i = 1; i <= sampleLoopTimes; i++)
    {
        for (int i = 0; i < sampleSize; i++)
        {
            which = i;
            for (int i = 0; i < trainTimes; i++)
            {
                before = pow(fabs((input[which] * k + b) - output[which]), 2);
                if (change) //change the value alternately
                    k2 = k + plusMinus[rand() % 2] * ETA_W;
                else
                    b2 = b + plusMinus[rand() % 2] * ETA_B;
                after = pow(fabs((input[which] * k2 + b2) - output[which]), 2);
                if (after < before)
                    if (change)//update the value
                        k = k2;
                    else
                        b = b2;
                change = !change;
            }
        }
        printf("The %d times training:\n", i);
        printf("Real  k=%f\tb=%f\n", k_cst, b_cst);
        printf("Train k=%f\tb=%f\n\n", k, b);
    }
}

void Test()
{
    double Value = 0;
    double Predict = 0;
    puts("Start Testing...");
    for (int i = 0; i < sampleSize; i++)
    {
        Value = k * i + b;
        Predict = k_cst * i + b_cst;
        printf("Input:%2d\tOutput:%.4f\tPredictValue:%.4f\n", i, Value, Predict);
    }
    puts("Over Test.");
}
int main()
{
    srand((unsigned)time(NULL));
    IntiTrainingDate();
    Training();
    Test();
    puts("\nProgram Over");
    getchar();
    return 0;
}



