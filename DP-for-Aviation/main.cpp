/**
 *  main.cpp
 *  the main procedure for shortest path
 *
 *  Created by David Wang on 16/10/13.
 *
 */

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#define NUM 14
#define LEVEL 6

const double A = 6378245.0;
const double E_SQUARE = 0.006693421623;
const double COEF = 57.29577951;
const double FUNCA = 1.0050517739;
const double FUNCB = 0.00506237764;
const double FUNCC = 0.00001062451;
const double FUNCD = 0.00000002081;
const double LONG = 117;
const double LAT = 33;
const double COORDINATE[NUM][2] = { 121.4, 31.2, 119.26, 32.23, 119.54, 32.3, 120.18, 31.34, 118.2, 35.03, 119.09, 33.3, 119.1, 34.36, 117.40, 36.12, 118.02, 37.22, 118.03, 36.48, 116.52, 38.18, 117.2, 39.13, 117.21, 38.21, 116.6, 40.1};
const int ARR[LEVEL] = { 1, 3, 3, 3, 3, 1};

double coor[NUM][2] = {0};
double result[NUM] = {0};
int resultPath[NUM][LEVEL] = {0};

double getS(double latitude)
{
    return (A*(1-E_SQUARE)*(FUNCA/COEF*latitude-FUNCB/2*sin(2*latitude)+FUNCC/4*sin(4*latitude)-FUNCD/6*sin(6*latitude)));
}

double getX(double latitude)
{
    return (getS(latitude)-getS(LAT));
}

double getY(double longitude, double latitude)
{
    return (A*cos(latitude)/sqrt(1-E_SQUARE*sin(latitude)*sin(latitude))*(longitude-LONG)/COEF);
}

double getDistance(double x1, double y1, double x2, double y2)
{
    return (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}

void init()
{
    int i;
    for(i=0;i<NUM;i++)
    {
        coor[i][0] = getX(COORDINATE[i][1]);
        coor[i][1] = getY(COORDINATE[i][0],COORDINATE[i][1]);
        //cout<<"x = "<<coor[i][0]<<"  y = "<<coor[i][1]<<endl;
    }
    //cout<<"x = "<<getX(32)<<" y = "<<getY(121,32)<<endl;
}

void solve()
{
    /*double res = 0;
    res += getDistance(coor[0][0], coor[0][1], coor[2][0], coor[2][1]);
    res += getDistance(coor[2][0], coor[2][1], coor[5][0], coor[5][1]);
    res += getDistance(coor[5][0], coor[5][1], coor[9][0], coor[9][1]);
    res += getDistance(coor[9][0], coor[9][1], coor[12][0], coor[12][1]);
    res += getDistance(coor[12][0], coor[12][1], coor[13][0], coor[13][1]);
    cout<<"result = "<<res<<endl;*/
    int i,j,k,past,now,tmpnum;
    double tmp;
    past = 0;
    now = ARR[0];
    
    for(i=1;i<LEVEL;i++)
    {
        for(j=now;j<now+ARR[i];j++)
        {
            tmp = 0;
            tmpnum = -1;
            for(k=past;k<past+ARR[i-1];k++)
            {
                tmp = result[k]+getDistance(coor[j][0], coor[j][1], coor[k][0], coor[k][1]);
                if ((result[j] == 0) || (tmp<result[j])) {
                    result[j] = tmp;
                    tmpnum = k;
                }
            }
            for(k=0;k<i-1;k++)
            {
                resultPath[j][k] = resultPath[tmpnum][k];
            }
            resultPath[j][i-1] = tmpnum;
        }
        past += ARR[i-1];
        now += ARR[i];
    }
}

void output()
{
    resultPath[13][5] = 13;
    cout<<"最短距离为："<<setiosflags(ios::fixed)<<setprecision(2)<<result[NUM-1]/1000<<" Km"<<endl;
    cout<<"最短距离经过的第1个点经纬度为："<<COORDINATE[resultPath[NUM-1][0]][0]<<"  "<<COORDINATE[resultPath[NUM-1][0]][1]<<endl;
    cout<<"最短距离经过的第2个点经纬度为："<<COORDINATE[resultPath[NUM-1][1]][0]<<"  "<<COORDINATE[resultPath[NUM-1][1]][1]<<endl;
    cout<<"最短距离经过的第3个点经纬度为："<<COORDINATE[resultPath[NUM-1][2]][0]<<"  "<<COORDINATE[resultPath[NUM-1][2]][1]<<endl;
    cout<<"最短距离经过的第4个点经纬度为："<<COORDINATE[resultPath[NUM-1][3]][0]<<"  "<<COORDINATE[resultPath[NUM-1][3]][1]<<endl;
    cout<<"最短距离经过的第5个点经纬度为："<<COORDINATE[resultPath[NUM-1][4]][0]<<"  "<<COORDINATE[resultPath[NUM-1][4]][1]<<endl;
    cout<<"最短距离经过的第6个点经纬度为："<<COORDINATE[resultPath[NUM-1][5]][0]<<"  "<<COORDINATE[resultPath[NUM-1][5]][1]<<endl;
}

int main(int argc, const char * argv[])
{
    init();
    solve();
    output();
    
    return 0;
}
