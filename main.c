#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void swap(int* v1,int* v2){
    int placeholder = *v1;
    *v1 = *v2;
    *v2 = placeholder;
}


void heapify(int data[],int size,int parent){
    
    int highest = parent;
    int child1 = 2* parent + 1;
    int child2 = 2* parent + 2;
    
    
    if(child1 < size && data[child1] > data[highest])
        highest = child1;
    if(child2 < size && data[child2] > data[highest])
        highest = child2;
    
    if(highest != parent){
        swap(&data[parent], &data[highest]);
        heapify(data, size, highest);
    }
}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n){
    
    for (int x = n/2-1; x >= 0; x--)
        heapify(arr, n, x);
    
    for (int y = n - 1; y >= 0; y--) {
        swap(&arr[0], &arr[y]);
        heapify(arr, y, 0);
    }
}

void merge(int data[],int b, int m, int e){
    
    int x, y, z = b;
    
    int s1 = m - b + 1;
    int s2 = e - m;
    
    int *ds1 = (int*) malloc(s1*sizeof(int));
    int *ds2 = (int*) malloc(s2*sizeof(int));
    
    extraMemoryAllocated += ((s1 + s2)*sizeof(int));

    
    
    
    for (x = 0; x < s1; x++)
        ds1[x] = data[b + x];
    for (y = 0; y < s2; y++)
        ds2[y] = data[m + 1+ y];
    
    x = 0;
    y = 0;
    
    while (x < s1 && y < s2)
    {
        if (ds1[x] <= ds2[y])
        {
            data[z] = ds1[x];
            x++;
        } else {
            data[z] = ds2[y];
            y++;
        }
        z++;
    }

    
    while (x < s1)
    {
        data[z] = ds1[x];
        x++;
        z++;
    }

    
    while (y < s2)
    {
        data[z] = ds2[y];
        y++;
        z++;
    }
    
    free(ds1);
    free(ds2);

}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if(l < r){
        
        int midPoint = (l+r)/2;
        
        mergeSort(pData, l, midPoint);
        mergeSort(pData, midPoint+1, r);
        
        
        merge(pData, l, midPoint, r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
    int i, n, *data;
    *ppData = NULL;
    
    if (inFile)
    {
        fscanf(inFile,"%d\n",&dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i=0;i<dataSz;++i)
        {
            fscanf(inFile, "%d ",&n);
            data = *ppData + i;
            *data = n;
        }

        fclose(inFile);
    }
    
    return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    if(dataSz < 100){
        for (i=0;i<dataSz;++i)
        {
            printf("%d ",pData[i]);
        }
        printf("\n\n");
        return;
    }
        
        
        for (i=0;i<100;++i)
        {
            printf("%d ",pData[i]);
        }
        printf("\n\t");
        
        for (i=sz;i<dataSz;++i)
        {
            printf("%d ",pData[i]);
        }
        printf("\n\n");
    
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
    
    for (i=0;i<4;++i)
    {
        int *pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);
        
        if (dataSz <= 0)
            continue;
        
        pDataCopy = (int *)malloc(sizeof(int)*dataSz);
    
        printf("---------------------------\n");
        printf("Dataset Size : %d\n",dataSz);
        printf("---------------------------\n");
        
        printf("Heap Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        heapSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        free(pDataCopy);
        free(pDataSrc);
    }
    
}
