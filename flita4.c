#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STR 40


typedef struct {
    long begin;
    long end;
} edge;

edge* CreateEdgeList(FILE* file, long long edge_num);
void VertexSearch(int degree, edge* edge_list, long long edge_num);



int main(int argc, char *argv[])
{
    
    char filename[MAX_STR] = "testgraph.txt";
    FILE *file;

    file = fopen(filename, "r");
        if (file == NULL) {
            puts("Error opening the file");
            return 1;
        }
    
    long long edge_num = 0;
    int degree;
    if (argc == 3)
    {
        edge_num = atoi(argv[2]);
        degree = atoi(argv[1]);
    }
    else 
    {
        long long c;
        while ((c = fgetc(file)) != EOF) {
            if (c == '\n')         
                edge_num++;       
        }
        
        printf("Enter the degree of the vertex: ");
        scanf("%d", &degree);
    }
    

    rewind(file);

    edge* edge_list = CreateEdgeList(file, edge_num);

    fclose(file);

    
    
    printf("The %d degree vertices: ", degree);

    time_t begin = clock();
    VertexSearch(degree, edge_list, edge_num);
    time_t end = clock();
    
    puts("");
    printf("Time: \t%f\n", ((double)(end - begin))/CLOCKS_PER_SEC);

    free(edge_list);
    return 0;
}


edge* CreateEdgeList(FILE* file, long long edge_num)
{
    edge* edge_list = malloc(edge_num * sizeof(edge));
    for(long long i = 0; i < edge_num; i++)
        fscanf(file, "%d %d", &((edge_list+i)->begin), &((edge_list+i)->end));
    
    return edge_list;
}

void VertexSearch(int degree, edge* edge_list, long long edge_num)
{   
    long max_vertices = 0;
    for (long long i = 0; i < edge_num; i++)
    {
        if (edge_list[i].begin > max_vertices)
            max_vertices = edge_list[i].begin;
        if (edge_list[i].end > max_vertices)
            max_vertices = edge_list[i].end;
    }
    
    int *vertex_array = malloc((max_vertices+1) *sizeof(int));
    
    for (long i = 0; i < max_vertices+1; i++)
        vertex_array[i] = 0;

    for (long long i = 0; i < edge_num; i++)
    {
        vertex_array[edge_list[i].begin]++;
        vertex_array[edge_list[i].end]++;
    }

    int k = 0;
    for (long i = 0; i < max_vertices; i++)
    {   
        if (vertex_array[i] == degree)
        {
            printf("%d ", i);
            k = 1;
        }
    }
    if (k == 0)
        puts("No such vertices");
    free(vertex_array); 
}

