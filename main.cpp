#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <cstdlib>

#define PI 3.14159265
const double ang = 2*PI;

using namespace std;

int A[100][100];
int C[100][3];

void Read(int n)
{
    int j,i;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            cin>>A[i][j];
}

void Print(int n)
{
    int j,i;
    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
            if(i!=j)
                cout<<A[i][j]<<" ";
            else
                cout<<"0 ";
        cout<<endl;
    }
}

void Draw(int n)
{
    int gm;
    int gd = DETECT;
    char* st;
    initgraph(&gd, &gm,"");

    int x1=200,y1=200,i,j,r=20*n,k=1;
    for (i=0;i<n;++i)
    {
        C[i+1][0] = x1+trunc(r*cos(i*ang/n));
        C[i+1][1] = y1+trunc(r*sin(i*ang/n));
        C[i+1][2]=0;
        setcolor ((i)%7+1 );
        setlinestyle(0,0,30);
        circle(C[i+1][0],C[i+1][1],5);
        setcolor(BLACK);
        setlinestyle(0,0,2);
        settextstyle(BOLD_FONT, HORIZ_DIR, 7);
        int j=i+1;
        itoa(j,st,10);
        outtextxy(C[i+1][0],C[i+1][1],st);
    }
    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
            if(i!=j && A[i][j]==1)
            {
                setcolor(k);
                k=k%7+1;
                line(C[i+1][0],C[i+1][1],C[j+1][0],C[j+1][1]);
                ++A[i][j];
                ++A[j][i];
            }
    }
    readkey();
    closegraph();
}

int BipartiteOrNot(int n)
{
    //Subprogram returns 1 if the graph is bipartite and 0 in other case.
    //Ya znayu pro traditsii, no zdes' tak udobnee, razve net?
    if(n==1)
    {C[1][2]=1;return(1);}
    int i,j,B[n];
    for(i=0;i<n;++i)
        {B[i]=0;A[i][i]=0;}
    for(i=0;i<n;++i)
        if(!B[i])
        {
            ++B[i];
            if(!C[i+1][2])
                {C[i+1][2]=1;/*cout<<"+RED ";*/}
            for(j=0;j<n;++j)
            {
                if(A[i][j])
                {
                    if(C[j+1][2])
                        if(C[j+1][2]==C[i+1][2])
                            {/*cout<<A[i][j]<<" "<<j+1<<" "<<i+1<<" NeBi";*/return(0);}
                        else;
                    else
                        {C[j+1][2]=(C[i+1][2]%2+1);/*cout<<"+other ";*/}
                }
            }
        }
    cout<<"Bi";
    return(1);
}

//void Paint();

void Paint2(int n)
{
    int gm;
    int gd = DETECT;
    initgraph(&gd, &gm,"");
    setlinestyle(0,0,30);
    int i,j;
    for(i=1;i<n+1;++i)
        if(C[i][2]==1)
        {
            setcolor(RED);
            circle(C[i][0],C[i][1],6);
        }
        else
            {
                setcolor(WHITE);
                circle(C[i][0],C[i][1],6);
            }
    setcolor(WHITE);
    setlinestyle(1,0,3);
    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
            if(A[i][j])
                line(C[i+1][0],C[i+1][1],C[j+1][0],C[j+1][1]);
    }
    readkey();
    closegraph();
}

int main()
{
    int n;
    cout<<"Program is to find if the graph is bipartite or not."<<endl;
    cout<<"Enter the quantity of the graph nodes:"<<endl;
    cin>>n;
    cout<<endl<<"Enter the adjacency matrix (1 is for presence of the rib and 0 is for its absence):"<<endl;
    Read(n);
    Draw(n);

    readkey();
    if(BipartiteOrNot(n))
        Paint2(n);
    else
        cout<<"The graph is not bipartite";
    //Print(n);

    return 0;
}
