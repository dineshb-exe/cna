#include<stdio.h>
#include<limits.h>
#define MAX 9999
#define N 7

int main(){
  int s[N][N];
  printf("Enter the cost matrix: ");
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      scanf("%d",&s[i][j]);
    }
  }
  char vertices[]="SAECBDF";
  int cost[N][N],distance[N],pred[N],source;
  int visited[N],count,mind,next,i,j;
  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      if(s[i][j]==0)
        cost[i][j]=MAX;
      else
        cost[i][j]=s[i][j];
  for(i=0;i<N;i++){
    distance[i]=cost[source][i];
    pred[i]=source;
    visited[i]=0;
  }
  distance[source]=0;
  visited[source]=1;
  count=1;
  while(count<N-1){
  mind=MAX;
    for(i=0;i<N;i++)
    if(distance[i]<mind&&!visited[i]){
      mind=distance[i];
      next=i;
    }
    visited[next]=1;
    for(i=0;i<N;i++)
    if(!visited[i])
    if(mind+cost[next][i]<distance[i]){
      distance[i]=mind+cost[next][i];
      pred[i]=next;
    }
    count++;
  }

  printf("\nDistance of destination node=%d",distance[N-1]);
  printf("\nPath=%c",vertices[N-1]);
  j=N-1;
  do{
    j=pred[j];
    printf("<-%c",vertices[j]);
  }while(j!=source);

  printf("\n");
}
