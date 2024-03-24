// Madison Manankil
// cop 3502
// Bonus Assignment
//  March 23, 2024
//It takes a while so pls be patient when running :) <3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int extraMemAllocated;

// Allocates mem + tracks allocated size
void *Alloc(size_t sz) {
  extraMemAllocated += sz;
  size_t *mem = malloc(sizeof(size_t) + sz);
  *mem = sz;
  printf("Extra memory allocated, size: %ld\n", sz);
  return &mem[1];
}

// Deallocates mem + updates tracking of alloc size
void DeAlloc(void *ptr) {
  size_t *pSize = (size_t *)ptr - 1;
  extraMemAllocated -= *pSize;
  printf("Extra memory deallocated, size: %ld\n", *pSize);
  free((size_t *)ptr - 1);
}

// Returnssize of mem with Alloc
size_t Size(void *ptr) { return ((size_t *)ptr)[-1]; }

// insert
//  Sorts an array using heap sort
void heapSort(int numbers[], int len) {
  // Build the heap in ara
  for (int i = len / 2 - 1; i >= 0; i--) {
    int largest = i; // Initialize largest as root
    int heapified = 0;  // false

    while (!heapified && largest * 2 + 1 <= len) {
      int j = 2 * largest + 1; // largest
      if (j < len - 1 && numbers[j] < numbers[j + 1])
        j++;
      if (numbers[largest] < numbers[j]) {
        int swap = numbers[largest];
        numbers[largest] = numbers[j];
        numbers[j] = swap;
        largest = j;
      } else {
        heapified = 1;
      }
    }
  }

  // One by one extract nimber
  for (int i = len - 1; i > 0; i--) {
    int temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;

    int largest = 0;
    int heapified = 0; // false

    while (!heapified && largest * 2 + 1 < i) {
      int j = 2 * largest + 1;              // left child
      if (j < i - 1 && numbers[j] < numbers[j + 1]) // right child can be larger
        j++;
      if (numbers[largest] < numbers[j]) {
        temp = numbers[largest];
        numbers[largest] = numbers[j];
        numbers[j] = temp;
        largest = j;
      } else {
        heapified = 1; // true
      }
    }
  }
}
// insert

// This will merges two subber arrays of dataset[]
void merge(int dataset[], int left, int middle, int right) {
  int i, j, k;
  int n1 = middle - left + 1;
  int n2 = right - middle;

  // Tempor
  int L[n1], R[n2];

  // Copy data to temp arrays (L[] and R[])!
  for (i = 0; i < n1; i++)
    L[i] = dataset[left + i];
  for (j = 0; j < n2; j++)
    R[j] = dataset[middle + 1 + j];

  // Merge the temp arrays back into data
  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      dataset[k] = L[i];
      i++;
    } else {
      dataset[k] = R[j];
      j++;
    }
    k++;
  }

  // this will copy the remaining elements of L[]
  // ig uess if there are any
  while (i < n1) {
    dataset[k] = L[i];
    i++;
    k++;
  }

  // this willl copy the remaining elements of R[]
  // if anyif there are any
  while (j < n2) {
    dataset[k] = R[j];
    j++;
    k++;
  }
}

// IMPORTANT NEEDED FOR merge sort
void mergeSort(int dataset[], int left, int right) {
  if (left < right) {
    // Find the middle of everything and then  t divide the array into two
    int middle = left + (right - left) / 2;

    // Sort first and second halves
    mergeSort(dataset, left, middle);
    mergeSort(dataset, middle + 1, right);
    merge(dataset, left, middle, right);
  }
}

// Sorts an array using insertion sort algorithm
void insertionSort(int dataset[], int len) {
  int i, key, j;
  for (i = 1; i < len; i++) {
    key = dataset[i];
    j = i - 1;

    // Move elements of dataset
    // when they are greater than key, to one position ahead of their current
    // position
    while (j >= 0 && dataset[j] > key) {
      dataset[j + 1] = dataset[j];
      j = j - 1;
    }
    dataset[j + 1] = key;
  }
}

// insert Sorts an array using bubble sort algorithm
void bubbleSort(int dataset[], int len) {
  int i, j;
  for (i = 0; i < len - 1; i++)
    // Last i elements are already in place
    for (j = 0; j < len - i - 1; j++)
      if (dataset[j] > dataset[j + 1]) {
        // Swap if the element found is bigger
        // than the next element
        int swap = dataset[j];
        dataset[j] = dataset[j + 1];
        dataset[j + 1] = swap;
      }
}

// Sorts an array using selection sort algorithm
void selectionSort(int dataset[], int len) {
  int i, j, min_idx;

  // One by one move unsorted subar
  for (i = 0; i < len - 1; i++) {
    // looks for the minimum element in unsorted array
    min_idx = i;
    for (j = i + 1; j < len; j++)
      if (dataset[j] < dataset[min_idx])
        min_idx = j;

    // Swap the minimum element with nymebr 1 element
    int swap = dataset[min_idx];
    dataset[min_idx] = dataset[i];
    dataset[i] = swap;
  }
}
// end
int parseData(char *inputFileName, int **ppDataset) {
  FILE *fileStream = fopen(inputFileName, "r");
  int size = 0;
  *ppDataset = NULL;

  if (fileStream) {
    fscanf(fileStream, "%d\n", &size);
    *ppDataset = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
      fscanf(fileStream, "%d", &(*ppDataset)[i]);
    }
    fclose(fileStream);
  }

  return size;
}

void printArray(int dataset[], int size) {
  int i, threshold = size - 100;
  printf("\tData:\n\t");
  for (i = 0; i < 100; ++i) {
    printf("%d ", dataset[i]);
  }
  printf("\n\t");

  for (i = threshold; i < size; ++i) {
    printf("%d ", dataset[i]);
  }
  printf("\n\n");
}

int main(void) {
  clock_t startTime, endTime;
  int i;
  double cpuTimeUsed;
  char *files[] = {"input1.txt", "input2.txt", "input3.txt"};

  for (i = 0; i < 3; ++i) {
    int *originalData, *copyData;
    int dataSize = parseData(files[i], &originalData);

    if (dataSize <= 0)
      continue;

    copyData = (int *)malloc(sizeof(int) * dataSize);

    printf("---------------------------\n");
    printf("Dataset Size : %d\n", dataSize);
    printf("---------------------------\n");

    printf("Selection Sort:\n");
    memcpy(copyData, originalData, dataSize * sizeof(int));
    extraMemAllocated = 0;
    startTime = clock();
    selectionSort(copyData, dataSize);
    endTime = clock();
    cpuTimeUsed = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpuTimeUsed);
    printf("\textra memory allocated\t: %d\n", extraMemAllocated);
    printArray(copyData, dataSize);

    printf("Insertion Sort:\n");
    memcpy(copyData, originalData, dataSize * sizeof(int));
    extraMemAllocated = 0;
    startTime = clock();
    insertionSort(copyData, dataSize);
    endTime = clock();
    cpuTimeUsed = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpuTimeUsed);
    printf("\textra memory allocated\t: %d\n", extraMemAllocated);
    printArray(copyData, dataSize);

    printf("Bubble Sort:\n");
    memcpy(copyData, originalData, dataSize * sizeof(int));
    extraMemAllocated = 0;
    startTime = clock();
    bubbleSort(copyData, dataSize);
    endTime = clock();
    cpuTimeUsed = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpuTimeUsed);
    printf("\textra memory allocated\t: %d\n", extraMemAllocated);
    printArray(copyData, dataSize);

    printf("Merge Sort:\n");
    memcpy(copyData, originalData, dataSize * sizeof(int));
    extraMemAllocated = 0;
    startTime = clock();
    mergeSort(copyData, 0, dataSize - 1);
    endTime = clock();
    cpuTimeUsed = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpuTimeUsed);
    printf("\textra memory allocated\t: %d\n", extraMemAllocated);
    printArray(copyData, dataSize);

    free(copyData);
    free(originalData);
  }
  return 0;
}