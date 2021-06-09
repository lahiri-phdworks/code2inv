int main() {
  // variable declarations
  int low;
  int high;
  int mid;
  int item;
  int SIZE;
  int arr[] = {5,   6,   11,  18,  23,  28,  29,  30,  35,  33,  88,
               89,  90,  95,  105, 115, 125, 162, 189, 196, 225, 345,
               382, 412, 430, 445, 500, 505, 519, 569, 725, 885, 1025};
  // pre-conditions
  // scanf("%d", &low);
  // scanf("%d", &high);
  // scanf("%d", &item);
  // scanf("%d", &mid);
  (low = 0);
  (mid = 0);
  (item = 0);
  (high = (int)(sizeof(arr) / sizeof(arr[0])));
  (SIZE = (int)(sizeof(arr) / sizeof(arr[0])));
  // precheck
  // loopcond : (low < high)
  // loopstart
  while ((low < high)) {
    // loop body
    mid = (low + high) / 2;
    if ((item < arr[mid])) {
      high = mid;
    } else if ((arr[mid] < item)) {
      low = mid + 1;
    } else {
      break;
    }
  }
  // loopend
  // postcheck
  // post-condition
  // printf("%d", arr[mid]);
  assert((0 <= low <= mid <= high) &&
         (((0 <= mid) && (mid < low) && (arr[mid] != item)) ||
          ((high <= mid) && (mid <= SIZE) && (arr[mid] != item)) ||
          (arr[mid] == item)));
}