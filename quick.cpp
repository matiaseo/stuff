#include <stdio.h>
#include <vector>
#include <chrono>

#define now() std::chrono::system_clock::now().time_since_epoch().count()

using std::vector;
using std::memcpy;

std::vector<int> firstSort(std::vector<int> list) {
  if(list.size() <= 1) return list;
  vector<int> smaller;
  vector<int> larger;
  auto iterator = list.begin();
  int pivot = *iterator;
  while(++iterator != list.end()) {
    if(*iterator > pivot) larger.push_back(*iterator);
    if(*iterator <= pivot) smaller.push_back(*iterator);
  }
  auto sortedSmaller = firstSort(smaller);
  const auto sortedLarger = firstSort(larger);
  sortedSmaller.push_back(pivot);
  sortedSmaller.insert(sortedSmaller.end(), sortedLarger.begin(), sortedLarger.end());
  return sortedSmaller;
}

template<typename T>
void rSort(T* arr, int size) {
  if(size <= 1) return;
  T* dupped = new T[size];
  //memcpy(dupped, arr, size * sizeof(T));
  std::copy(arr, arr + size, dupped);
  int j=0,k=size;
  const int pivot = *dupped;
  for(int i=1;i<size;i++) {
    if(dupped[i] < pivot) arr[j++] = dupped[i];
    else arr[--k] = dupped[i];
  }
  delete[] dupped;
  rSort(arr, j);
  arr[j++] = pivot;
  rSort(arr+j, size-k);
}

template<typename T>
vector<T> betterSort(vector<T> list) {
  T copy[list.size()];
  std::copy(list.begin(), list.end(), copy);
  rSort(copy, list.size());
  return vector<T>(copy, copy+list.size());
}

//std::vector<int> sort(vector<int> list) {
//  if(list.size() <= 1) return list;
//  int smaller[list.size()-1];
//  int larger[list.size()-1];
//  int * array = list.data();
//  int pivot = *array;
//  int j=0, k=0;
//  for(int i = 1; i < list.size();) {
//    const int & value = array[i++];
//    if(value > pivot) larger[j++] = value;
//    else smaller[k++] = value;
//  }
//  const auto & sortedSmaller = sort(vector<int>(smaller,smaller+k));
//  const auto & sortedLarger = sort(vector<int>(larger,larger+j));
//  int result[list.size()];
//  int i = 0;
//  for(;i < sortedSmaller.size();i++) result[i] = sortedSmaller[i];
//  result[i++] = pivot;
//  for(int j=0;i < list.size();i++,j++) result[i] = sortedLarger[j];
//  return vector<int>(result, result + i);
//}

std::vector<int> sort(vector<int> list) {
  if(list.size() <= 1) return list;
  int temp[list.size()-1];
  int * array = list.data();
  int pivot = *array;
  int j=0, k=list.size()-1;
  while (k > j) {
    const int & value = *(++array);
    temp[value > pivot? --k : j++] = value;
  }
  const auto & sortedSmaller = sort(vector<int>(temp,temp+k));
  const auto & sortedLarger = sort(vector<int>(temp+k,temp+list.size()-1));
  int result[list.size()];
  //int i = 0;
  //for(;i < sortedSmaller.size();i++) result[i] = sortedSmaller[i];
  std::copy(sortedSmaller.begin(), sortedSmaller.end(), result);
  result[sortedSmaller.size()] = pivot;
  std::copy(sortedLarger.begin(), sortedLarger.end(), &result[sortedSmaller.size()+1]);
  //for(int j=0;i < list.size();i++,j++) result[i] = sortedLarger[j];
  return vector<int>(result, result + list.size());
}

int getRandom(int seed) {
  int value = seed ^ seed << 13;
  value ^= value >> 17;
  value ^= value << 5;
  return value & 0x7f;
}

int main() {
  auto before = now();
  vector<int> numbers = {5,3,2,56,7,3,24,1,3,4,533,67,765,3,2,4,3,456,546,664,546,456,456,456,645,456,45,453,345,435,3,65,7,8,89,6,88,654,32,456,7,969,76,54,3,25,675,8};
  for(int i = 0; i++ < 45511;) numbers.insert(numbers.end(), { i & 0x7f, i >> 3 & 0x3f, getRandom(i) });
  printf("\nnumbers=%lu\n", numbers.size());
  auto after = now();
  //for(const int & num : numbers) printf("%4d", num);
  printf("\n%lld\n", after - before);

  before = now();
  const auto sortedBetter = betterSort(numbers);
  after = now();
  //for(const int & num : sortedBetter) printf("%4d", num);
  printf("\nbetterSort=%lld\n", after - before);

  before = now();
  const auto sortedFirst = firstSort(numbers);
  after = now();
  //for(const int & num : sortedFirst) printf("%4d", num);
  printf("\nfirstSort=%lld\n", after - before);

  before = now();
  const auto sorted = sort(numbers);
  after = now();
  //for(const int & num : sorted) printf("%4d", num);
  printf("\ntryharding=%lld\n", after - before);

  for(int i=0;i<numbers.size();i++) {
    if(sorted[i] != sortedBetter[i]) {
      printf("\ns=%d != sB=%d\n", sorted[i], sortedBetter[i]);
      return 1;
    }
    if(sortedFirst[i] != sortedBetter[i]) {
      printf("\nsF=%d != sB=%d\n", sortedFirst[i], sortedBetter[i]);
      return 1;
    }
    //printf("%d ", sortedBetter[i]);
  }
  printf("\nAll ok\n");
  return 0;
}
