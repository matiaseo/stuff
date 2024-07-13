//template<typename T>
//void rSort(T* arr, int size) {
//  if(size <= 1) return;
//  T* dupped = new T[size];
//  //memcpy(dupped, arr, size * sizeof(T));
//  std::copy(arr, arr + size, dupped);
//  int j=0,k=size;
//  const int pivot = *dupped;
//  for(int i=1;i<size;i++) {
//    if(dupped[i] < pivot) arr[j++] = dupped[i];
//    else arr[--k] = dupped[i];
//  }
//  delete[] dupped;
//  rSort(arr, j);
//  arr[j++] = pivot;
//  rSort(arr+j, size-k);
//}
//
//template<typename T>
//vector<T> betterSort(vector<T> list) {
//  T copy[list.size()];
//  std::copy(list.begin(), list.end(), copy);
//  rSort(copy, list.size());
//  return vector<T>(copy, copy+list.size());
//}

#![allow(non_snake_case)]

fn rSort(list:&mut Vec<i32>, start:usize, end:usize) {
  if end-start <= 1 { return }
  let mut sm = start;
  let mut lg = end;
  let pivot = list[start];
  {
    let dupped:Vec<_> = list[start+1..end].iter().cloned().collect();
    for value in dupped.iter() {
      if *value < pivot {
        list[{let pre=sm;sm+=1;pre}] = *value
      } else {
        list[{lg-=1;lg}] = *value
      }
    }
  }
  rSort(list, start, sm);
  list[sm] = pivot;
  rSort(list, lg, end);
}

fn betterSort(list:&Vec<i32>) -> Vec<i32> {
  let mut copy = list.clone();
  rSort(&mut copy, 0, list.len());
  return copy;
}

fn firstSort(list:&Vec<i32>) -> Vec<i32> {
  if list.len() <= 1 { return list.clone(); }
  let mut smaller = vec![];
  let mut larger = vec![];
  let pivot = list[0];
  for i in 1..list.len() {
    //println!("list={},pivot={},smaller={},larger={}, value={}", list.len(), pivot, smaller.len(), larger.len(), list[i]);
    if list[i] > pivot { larger.push(list[i]) }
    else { smaller.push(list[i]) }
  }
  //println!("list={},pivot={},smaller={},larger={}", list.len(), pivot, smaller.len(), larger.len());
  smaller = firstSort(&smaller);
  smaller.push(pivot);
  larger = firstSort(&larger);
  smaller.append(&mut larger);
  return smaller;
}

fn getRandom(seed:i32) -> i32 {
  let mut value = seed ^ seed << 13;
  value ^= value >> 17;
  value ^= value << 5;
  return value & 0x7ff;
}

fn main() {
  let mut before = std::time::Instant::now();
  let randomCount = 1051100;
  let mut numbers = vec![5,3,2,56,7,3,24,1,3,4,533,67,765,3,2,4,3,456,546,664,546,45,453,345,435,3,65,7,8,89,6,88,654,32,456,7,969,76,54,3,25,675,8];
  numbers.reserve(randomCount);
  for i in 0..randomCount as i32 {
    numbers.push(getRandom(i));
  }
  println!("numbers={}", numbers.len());
  let mut after = std::time::Instant::now();
  //for(const int & num : numbers) print!("%4d", num);
  println!("{:?}", after.duration_since(before));

  before = std::time::Instant::now();
  let sortedBetter = betterSort(&numbers);
  after = std::time::Instant::now();
  //for(const int & num : sortedBetter) print!("%4d", num);
  println!("betterSort={:?}", after.duration_since(before));

  before = std::time::Instant::now();
  let sortedFirst = firstSort(&numbers);
  after = std::time::Instant::now();
  //for(const int & num : sortedFirst) print!("%4d", num);
  println!("firstSort={:?}", after.duration_since(before));

  before = std::time::Instant::now();
  numbers.sort();
  after = std::time::Instant::now();
  //for(const int & num : sorted) print!("%4d", num);
  println!("built-in={:?}", after.duration_since(before));

  for i in 0..numbers.len() {
    if sortedFirst[i] != numbers[i] {
      println!("sF={} != sB={}", sortedFirst[i], numbers[i]);
      std::process::exit(1);
    }
    //print!("{} ", sortedBetter[i]);
  }
  println!("first ok");
  for i in 0..numbers.len() {
    if numbers[i] != sortedBetter[i] {
      println!("s={} != sB={}", numbers[i], sortedBetter[i]);
      std::process::exit(1);
    }
    //print!("{} ", sortedBetter[i]);
  }
  println!("All ok");
}

