// DoubleInput.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define sampleSize 10
#define addVal 0.005
#define times 10000
#define sampleTimes 5

const double k_cst = 5;
const double b_cst = 3;
double input[sampleSize] = { 0 };
double output[sampleSize] = { 0 };
const int plusMinus[2] = { -1,1 };
double k = 0, k2 = 0;
double b = 0, b2 = 0;
double before = 0, after = 0;
int which = 3;

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
    for (int i = 1; i <= sampleTimes; i++)
    {
        for (int i = 0; i < sampleSize; i++)
        {
            which = i;
            for (int i = 0; i < times; i++)
            {
                before = pow(fabs((input[which] * k + b) - output[which]), 2);
                if (change)
                    k2 = k + plusMinus[rand() % 2] * addVal;
                else
                    b2 = b + plusMinus[rand() % 2] * addVal;
                after = pow(fabs((input[which] * k2 + b2) - output[which]), 2);
                if (after < before)
                    if (change)
                        k = k2;
                    else
                        b = b2;
                change = !change;
            }
        }
        printf("No.%2d:\n", i);
        printf("Real  k=%f\tb=%f\n", k_cst, b_cst);
        printf("Train k=%f\tb=%f\n\n", k, b);
    }
}

void Test()
{
    double Value = 0;
    double RealV = 0;
    puts("Start Testing...");
    for (int i = 0; i < sampleSize*10; i++)
    {
        Value = k * i + b;
        RealV = k_cst * i + b_cst;
        printf("Input:%2d\tOutput:%.4f\tPredictValue:%.4f\n", i, Value, RealV);
    }
    puts("Over Test.");
}
int main()
{
    srand((unsigned)time(NULL));
    IntiTrainingDate();
    Training();
    //Test();
    puts("\nProgram Over");
    getchar();
    return 0;
}



