#include <stdio.h>
#include <stdlib.h>

int** arr = NULL;
int bol = 0;

void show(int N);
void create_dot(int* arr, int N);
void DFS(int* visited, int v, int p);

int main(void)
{
    int N = 0;
    
    FILE* f = NULL;
    int* arrv = NULL;
    
    if((f = fopen("data1.txt", "r")) != NULL){

        fscanf(f, "%d", &N);
        arrv = (int*)malloc(sizeof(int)*N*N);
        arr = (int**)calloc(sizeof(int*), N);
        for(int i = 0; i < N; i++){
            arr[i] = (int*)malloc(sizeof(int));
            arr[i][0] = -1;
        }
        
        
        int c = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                int tmp = 0;
                fscanf(f, "%d", &tmp);
                arrv[j+i*N] = tmp;
                if(tmp >= 1) {
                    arr[i][c] = j;
                    c++;
                    arr[i] = (int*)realloc(arr[i], sizeof(int)*(c+1));
                }
            }
            arr[i][c] = -1;
            c = 0;
        }
    }
    else
        printf("File data.txt did not open :(\n");
    fclose(f);




    int* visited = (int*)calloc(N, sizeof(int));
    for(int i = 0; i < N; i++)  {
      if (visited[i] != 1) {
        DFS(visited, i, -1);
      }
    }
    if (bol == 1) {
      printf("Graph has cycles\n");
    } else {
      printf("Graph has no cycles\n");
    }

    printf("\n");
    create_dot(arrv, N);
    show(N);
    free(arr);
    free(arrv);
    free(visited);
    
    return 0;
}

void show(int N){
    for (int i = 0; i < N; i++){
      printf("%d вершина: ", i);
        for(int j = 0; arr[i][j] != -1; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void DFS(int* visited, int v, int p) {
  visited[v] = 1;
  for (int i = 0; arr[v][i] != -1; i++) {
    if (visited[arr[v][i]] != 1) {
      DFS(visited, arr[v][i], v);
    } else if (arr[v][i] != p) {
      bol = 1;
    }
  }
}

void create_dot(int* arr, int N){
    FILE* f = NULL;

    if((f = fopen("out.dot", "w")) != NULL){
        fprintf(f, "graph abc {\n");
        for(int j = 0; j < N; j++){
            for(int i = j; i < N; i++){
                for(int k = 0; k < arr[i+j*N]; k++)
                	fprintf(f, "%d -- %d;\n", j+1, i+1);
            }
        }
        fprintf(f, "}");
        fclose(f);
    }
    else
        printf("dot cannpt be open\n");
}
