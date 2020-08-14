#include "kdtree.h"

void sort(Point2D point2D[],int index[],int dim, int point_count)
{
    float a,b;
    int c;
    for (int i=point_count-1;i>0;i--)
    {
        for (int j=1;j<=i;j++)
        {
           
            if (dim==0)
            {                
                a=point2D[index[j-1]].x;
                b=point2D[index[j]].x;
            }
            else
            {
                a=point2D[index[j-1]].y;
                b=point2D[index[j]].y;                
            }
            if (a>b)
            {
                c=index[j];
                index[j]=index[j-1];
                index[j-1]=c;
            }            
        }        
    }
}
