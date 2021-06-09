void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void select_pivot(int arr[], int low, int high) {
  srand(time(0));
  int random = low + rand() % (high - low);
  swap(&arr[random], &arr[high]);
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
  (high = (int)((sizeof(arr) / sizeof(arr[0]) - 1)));
  select_pivot(arr, 0, high);
  (pivot = arr[high]);
  (i = 0);
  (j = 0);
  // precheck
  // loopcond : (j <= high - 1)
  // loopstart
  while (j <= high - 1) {
    if (arr[j] < pivot) {
      swap(&arr[i], &arr[j]);
      i = i + 1;
    }
    j = j + 1;
  }
  swap(&arr[i], &arr[high]);
  // loopend
  // postcheck
  // post-condition
  assert((0 <= i <= high) && (arr[i - 1] < pivot) && (arr[i] == pivot) &&
         (arr[i + 1] > pivot));
}