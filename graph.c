#include <stdio.h>
#include <stdlib.h>

void new_string (int n, FILE *file, int i, int j){
    while (n)
    {
        fprintf(file, "%d -- %d\n", i, j);
        n--;
    }
}

int main(void)
{
    int i = 0, j = 0, m = 1, x = 0, fl = 0, res = 0;
    char c;
    FILE *graph_data;
    FILE *input;

    input = fopen("input.txt", "r");
    graph_data = fopen("graph_data.txt", "w");
    fprintf(graph_data, "graph G{\n");

    while (j < m){
        while (((c = fgetc(input)) != '\n') && (c != EOF)){ //проход по строке
            if ((c != ' ') && ((c > '9') || (c < '0'))){
                printf ("Wrong sign\n");
                exit (1);
            }
            else{
                if (c == ' ') { //если дошли до знака пробела, значит вносим связь в файл
                    if (j == 0) { //считаем количество чисел в первой строке
                        m++;
                    }
                    if ((x != 0) && (i >= j)) { //число лежит выше главной диагонали и не равно 0
                        new_string(x, graph_data, i, j);
                    }
                    if ((i != j) && (x == 1)) { //число лежит не на главной диагонали (петля), если граф является простым циклом, то в каждой строке содержится две единицы
                        fl++;
                    }
                    x = 0;
                    i++;
                }
                else {
                    x = x*10 + (c - '0'); //для случая, если число ребер двузначное и тд число
                }
            }
        }
        if ((x != 0) && (i >= j)) { //записываем число полученное при выходе по условиям (c == '\n') || (c == EOF)
        	new_string(x, graph_data, i, j);
        }
        if ((i != j) && (x == 1)) {
        	fl++;
        }
        if (i != (m - 1)){ //проверяем равно ли количество чисел в строке количеству в первой строке
            printf ("The length of the string is incorrect, perhaps there is an extra space somewhere or the matrix is not square\n");
            exit (1);
        }
        if (fl != 2) { //в строке содержится не две единицы
            res = 1;
        }
        x = 0;
        fl = 0;
        i = 0;
        j++;
    }

    fprintf(graph_data, "}");
    fclose(graph_data);
    fclose(input);

    if (res == 1){
        printf ("This graph is not a simple cycle\n");
    }
    else {
        printf ("This graph is a simple cycle\n");
    }

    system ("dot -T png graph_data.txt -o graph.png && sxiv graph.png");
    return 0;
}
