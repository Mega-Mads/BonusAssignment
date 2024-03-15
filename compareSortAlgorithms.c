//Madison Manankil
//cop 3502
//Bonus Assignment
//INSTRUCTIONS: You need to implement parseData, selectionSort, insertionSort, bubbleSort, mergeSort and heapSort functions. 
//Each sorting function will count the number of extra memory allocated using the global variable extraMemoryAllocated.

//Please prepare a report in pdf format containing the url of your git repository and screenshot of your output.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int extraMemoryAllocated;

void *Alloc(size_t sz);
void DeAlloc(void *ptr);
size_t Size(void *ptr);
void selectionSort(int *pData, int n);
void insertionSort(int *pData, int n);
void bubbleSort(int *pData, int n);
void mergeSort(int *pData, int l, int r);
void merge(int *pData, int l, int m, int r);
void heapSort(int arr[], int n);
int parseData(char *inputFileName, int **ppData);
void printArray(int pData[], int dataSz);

void *Alloc(size_t sz) {
  extraMemoryAllocated += sz;
  size_t *ret = malloc(sizeof(size_t) + sz);
  *ret = sz;
  printf("Extra memory allocated, size: %ld\n", sz);
  return &ret[1];
}

void DeAlloc(void *ptr) {
  size_t *pSz = (size_t *)ptr - 1;
  extraMemoryAllocated -= *pSz;
  printf("Extra memory deallocated, size: %ld\n", *pSz);
  free((size_t *)ptr - 1);
}

size_t Size(void *ptr) { return ((size_t *)ptr)[-1]; }
//INSERT HERE
// heapSort: Sorts an array arr[] of size n. 
void heapSort(int arr[], int n) {
  int *indices = (int *)Alloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    indices[i] = i;
  }


  for (int i = 1; i < n; i++) {
    if (arr[indices[i]] < arr[indices[(i - 1) / 2]]) {
      int j = i;
      while (arr[indices[j]] < arr[indices[(j - 1) / 2]]) {
        int temp = indices[j];
        indices[j] = indices[(j - 1) / 2];
        indices[(j - 1) / 2] = temp;
        j = (j - 1) / 2;
      }
    }
  }

  DeAlloc(indices);
}
//merge
void merge(int *pData, int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int *L = (int *)Alloc(n1 * sizeof(int));
  int *R = (int *)Alloc(n2 * sizeof(int));

  for (i = 0; i < n1; i++)
    L[i] = pData[l + i];
  for (j = 0; j < n2; j++)
    R[j] = pData[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      pData[k] = L[i++];
    } else {
      pData[k] = R[j++];
    }
    k++;
  }

  while (i < n1) {
    pData[k++] = L[i++];
  }

  while (j < n2) {
    pData[k++] = R[j++];
  }

  DeAlloc(L);
  DeAlloc(R);
}
//insert
// mergeSort will divide the array into halfs THAN sorts each half and
// puts them back together
void mergeSort(int *pData, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(pData, l, m);
    mergeSort(pData, m + 1, r);
    merge(pData, l, m, r);
  }
}
//insert
// insertionSort this will build the sorted array one at a time 
//This compares each new thing with the previously sorted thing and inserting it into the
// correct part.
void insertionSort(int *pData, int n) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = pData[i];
    j = i - 1;

    while (j >= 0 && pData[j] > key) {
      pData[j + 1] = pData[j];
      j = j - 1;
    }
    pData[j + 1] = key;
  }
}


//insert
// bubbleSort this will repeate the steps through the list and comparessss each pair of
// items and switchy them if wrong order. Then pass through 
// list is repeated until the list is sort.
void bubbleSort(int *pData, int n) {
  int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
      if (pData[j] > pData[j + 1]) {
        int temp = pData[j];
        pData[j] = pData[j + 1];
        pData[j + 1] = temp;
      }
}



//insert

// selectionSort
//will sep the input list into two parts 
//1, the sublist of items already sorted
// 2. the sublist of items remaining to be sorted that occupy the rest of the list. 
void selectionSort(int *pData, int n) {
  int i, j, min_idx;
  for (i = 0; i < n - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < n; j++)
      if (pData[j] < pData[min_idx])
        min_idx = j;
    int temp = pData[min_idx];
    pData[min_idx] = pData[i];
    pData[i] = temp;
  }
}


//INSERT

// parseData
//THis will  read ints from a file and stores them in an array. 
//Then the size of array is spotted first and memory  THEN is allocated accordingly.
int parseData(char *inputFileName, int **ppData) {
  FILE *inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  *ppData = NULL;

  if (inFile) {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (int *)Alloc(sizeof(int) * dataSz);
    for (int i = 0; i < dataSz; i++) {
      fscanf(inFile, "%d", (*ppData) + i);
    }
    fclose(inFile);
  }

  return dataSz;
}

void printArray(int pData[], int dataSz) {
  int i, sz = dataSz > 100 ? 100 : dataSz; // Adjust to handle smaller arrays
  printf("\tData (First 100 elements, if applicable):\n\t");
  for (i = 0; i < sz; ++i) {
    printf("%d ", pData[i]);
  }
  if (dataSz > 100) {
    printf("\n\t...skipping...\n\t");
    for (i = dataSz - 100; i < dataSz; ++i) {
      printf("%d ", pData[i]);
    }
  }
  printf("\n\n");
}

int main(void) {
  clock_t start, end;
  double cpu_time_used;
  char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
  int fileCount = sizeof(fileNames) / sizeof(char *);

  for (int i = 0; i < fileCount; ++i) {
    int *pDataSrc = NULL, *pDataCopy = NULL;
    int dataSz = parseData(fileNames[i], &pDataSrc);

    if (dataSz <= 0) {
      printf("Error reading data from %s or file is empty.\n", fileNames[i]);
      continue;
    }

    pDataCopy = (int *)Alloc(sizeof(int) * dataSz);

    printf("---------------------------\n");
    printf("Dataset Size: %d\n", dataSz);
    printf("---------------------------\n");

    // Repeat this pattern for each sort function
    printf("Selection Sort:\n");
    memcpy(pDataCopy, pDataSrc, sizeof(int) * dataSz);
    extraMemoryAllocated = 0;
    start = clock();
    selectionSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.2lf seconds\n", cpu_time_used);
    printf("\textra memory allocated\t: %d bytes\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    

    DeAlloc(pDataCopy);
    DeAlloc(pDataSrc);
  }
  return 0;
}