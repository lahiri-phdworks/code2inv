void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int main() {
  // variable declarations
  int i;
  int j;
  int pivot;
  int high;

  int arr[] = {2, 3, 90, 78, 1, 0, 67, 14, 9, 6, 7, 18, 10, 15, 11};
  // pre-conditions
  // scanf("%d", &i);
  // scanf("%d", &j);
  // scanf("%d", &pivot);
  (high = (int)(sizeof(arr) / sizeof(arr[0])));
  (pivot = arr[high - 1]);
  (i = -1);
  (j = 0);
  // precheck
  // loopcond : (j <= high - 2)
  // loopstart
  while (j <= high - 2) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
    j++;
  }
  swap(&arr[i + 1], &arr[high - 1]);
  // loopend
  // postcheck
  // post-condition
  assert((arr[i + 1] == pivot) && (arr[i] < pivot) && (arr[i + 2] > pivot));
}