#include "global.h"

void update_high_scores (char name[20], int score)
{
     int i,n,j;
     char names[21][20],t[20];
     int scores[21];
     FILE *high_scores;
     high_scores = fopen("high_scores.txt", "r");
     n=0;
     while (fscanf(high_scores,"%d",&scores[n])!=EOF)
     {
         fscanf(high_scores," %s", names[n]);
         n++;
     }
     fclose (high_scores);
     scores[n]=score;
     strcpy(names[n],name);
     i=n;
     while ((i>0)&&(scores[i]>scores[i-1]))
     {
        strcpy(t,names[i]);
        strcpy(names[i],names[i-1]);
        strcpy(names[i-1],t);
        j=scores[i];
        scores[i]=scores[i-1];
        scores[i-1]=j;
        i--;
     }
     while ((i>0)&&(scores[i]==scores[i-1])&&(strcmp(names[i],names[i-1])<0))
     {
        strcpy(t,names[i]);
        strcpy(names[i],names[i-1]);
        strcpy(names[i-1],t);
        j=scores[i];
        scores[i]=scores[i-1];
        scores[i-1]=j;
        i--;
     }
     if (n<20) n++;
     i=0;
     high_scores = fopen("high_scores.txt", "w");
     while (i<n)
     {
         fprintf(high_scores, "%d %s\n", scores[i], names[i]);
         i++;
     }
     fclose (high_scores);
}
