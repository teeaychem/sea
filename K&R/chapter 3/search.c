#include <stdio.h>

int binsearch(int x, int v[], int n);
int altBinsearch(int x, int v[], int n);


int main()
{
  const int dataSize = 6;
  int data[dataSize] = {1,3,5,7,9,11};
  int searchFor = 7;
  int location = altBinsearch(searchFor, data, dataSize);
  printf("%d was found at location %d\n", searchFor, location);

}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;

  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else /* found match */
      return mid;
  }
  return -1; /* no match */
}

/* alt to binsearch (above) */
int altBinsearch(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;

  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else
      low = mid + 1;

    if (v[mid] == x)/* found match */
      return mid;
  }
  return -1; /* no match */
}
