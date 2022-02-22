use std::cmp::Ord;

pub fn is_sorted<T:PartialOrd>(arr:&[T])->bool{
    let size = arr.len();
    if size == 0{
        return  true;
    }
    for i in 1..(size-1){
        if arr[i-1]>arr[i]{
            return false;
        }
    }
    true
}

// bubble_sort
pub fn bubble_sort<T:PartialOrd>(arr :&mut[T]){
    if arr.len()<=1{
        return;
    }
    let size = arr.len();
    for i in 0..(size-1){
        let mut swapped = false;

        for j in 1..(size-i){
            if arr[j-1]>arr[j]{
                arr.swap(j-1,j);
                swapped = true;
            }
        }

        if !swapped{
            break;
        }
    }
}

//bucket_sort
pub fn bucket_sort(arr:&[usize]) -> Vec<usize>{
    if arr.is_empty(){
        return vec![];
    }
    let max= *arr.iter().max().unwrap();
    let len= arr.len();
    let mut buckets = vec![vec![];len+1];
    for v in arr {
        buckets[len * *v / max].push(*v);
    }

    for bucket in buckets.iter_mut() {
        bubble_sort(bucket);
    }

    let mut result = vec![];
    for bucket in buckets{
        for v in bucket{
            result.push(v)
        }
    }

    result
}
//cocktail_shaker_sort
pub fn cocktail_shaker_sort<T:Ord>(arr :&mut[T]){
    let len = arr.len();
    if len == 0{
        return ; 
    }

    loop {
        let mut swapped = false ;

        for i in 0..(len-1).clamp(0, len){
            if arr[i] > arr[i+1]{
                arr.swap(1, i+1);
                swapped = true;
            }
        }

        if !swapped{
            break;
        }

        swapped = false;

        for i in (0..(len-1).clamp(0, len)).rev(){
            if arr[i] > arr[i+1]{
                arr.swap(i,i+1);
                swapped = true;
            }
        }

        if !swapped {
            break;
        }
    }

}

//comb_sort
pub fn comb_sort<T:Ord>(arr:&mut [T]){
    let mut gap = arr.len();
    if gap == 0 {
        return;
    }
    let shrink = 1.3 ;
    let mut sorted = false;

    while !sorted {
        gap = (gap as f32 /shrink).floor() as usize;
        if gap <=1{
            gap=1;
            sorted = true
        }
        for i in 0..arr.len()-gap{
            let j=i+gap;
            if arr[i]>arr[j]{
                arr.swap(i, j);
                sorted = false;
            }
        }
    }
}
//counting_sort
pub fn counting_sort(arr:&mut[u32],maxval :usize){
    let mut occurences: Vec<usize> = vec![0;maxval+1];

    for &data in arr.iter(){
        occurences[data as usize] +=1;
    }
    let mut i =0;
    for(data,&number) in occurences.iter().enumerate(){
        for _ in 0..number{
            arr[i]= data as u32;
            i +=1;
        }
    }

}


//heap_sort
pub fn heap_sort<T:PartialOrd>(arr:&mut[T]) {
    let size = arr.len();
    for i in (0..size/2).rev(){
        heapify(arr, i, size);
    }

    for i in (1..size).rev(){
        arr.swap(0, i);

        heapify(arr,0, i);
    }
}
pub fn heapify<T:PartialOrd>(arr:&mut[T],root: usize,end: usize){
    let mut largest = root;

    let left_child = 2*root+1;
    if left_child < end&& arr[left_child]>arr[largest]{
        largest = left_child;
    }
    let right_child = left_child+1;
    if right_child <end && arr[right_child]>arr[largest]{
        largest = right_child;
    }

    if largest!=root{
        arr.swap(root, largest);
        heapify(arr, largest, end);
    }
}

//insert_sort
pub fn insert_sort<T:PartialOrd>(arr: &mut[T]){
    for i in 1..arr.len() {
        let mut j = i;
        while j>0 && arr[j-1] >arr[i] {
            arr.swap(j-1, j);
                j-=1;
        }
    }
}
pub fn insert_binary_search_sort<T:Ord>(arr:&mut[T]){
    for i in 1..arr.len() {
        let pos = arr[..i].binary_search(&arr[i]).unwrap_or_else(|pos| pos);
        let mut j = i;
        while j > pos {
            arr.swap(j-1, j);
            j-=1;
        }
    }
}


//merge_sort
pub fn merge_sort<T>(arr:&mut [T])
where
    T:PartialOrd + Clone + Default,
{
    if arr.len() >1{
        merge_sort_range(arr, 0, arr.len()-1);
    }
}

fn merge_sort_range<T>(arr:&mut [T],lo :usize,hi :usize)
    where T:PartialOrd + Clone + Default,
{
    if lo < hi{
        let mid = lo+((hi-lo)/2);
        merge_sort_range(arr, lo,mid);
        merge_sort_range(arr, mid+1,hi);
        merge_two_array(arr, lo, mid, hi);
    }
}
fn merge_two_array<T>(arr:&mut [T],lo :usize,mid:usize,hi :usize)
    where T:PartialOrd + Clone + Default,
{
    let mut arr1 = arr[lo..=mid].to_vec();
    let mut arr2 = arr[mid+1 ..=hi].to_vec();
    let (mut i,mut j)=(0,0);
    while i <arr1.len() && j <arr2.len() {
        if arr1[i] < arr2[j]{
            arr1[i+j+lo] =std::mem::take(&mut arr1[i]);
            i+=1;
        }else {
            arr1[i+j+lo] =std::mem::take(&mut arr2[j]);
            j+=1;
        }
    }
}


//odd_even_sort
pub fn odd_even_sort<T:Ord>(arr:&mut [T]){
    let len = arr.len();
    if len == 0{
        return;
    }
    let mut sorted = false;

    while !sorted {
        sorted =true;
        for i in (1..len-1).step_by(2){
            if arr[i]> arr[i+1]{
                arr.swap(i, i+1);
                sorted =false;
            }
        }

        for i in (0..len-1).step_by(2){
            if arr[i]> arr[i+1]{
                arr.swap(i, i+1);
                sorted =false;
            }
        }
    }
}

//quick_sort
pub fn quick_sort<T:PartialOrd>(arr:&mut [T]){
    if arr.len()>1 {
        quick_sort_range(arr, 0, arr.len()-1);
    }
}

fn quick_sort_range<T:PartialOrd>(arr:&mut [T],lo :usize,hi :usize){
    if lo <hi{
        let pos = partition(arr, lo, hi);
        if pos!=0 {
            quick_sort_range(arr, lo,pos-1);
        }
        quick_sort_range(arr, pos+1, hi);
    }
}

fn partition<T:PartialOrd>(arr:&mut [T],lo :usize,hi :usize)-> usize{
    let pivot = lo;
    let (mut left,mut right) = (lo,hi);

    while left < right{
        while left < right && arr[right]>=arr[pivot] {
            right -=1;
        }
        while left<right && arr[right]<=arr[pivot] {
            left+=1;
        }

        if left !=right {
            arr.swap(left,right)
        }
    }
    arr.swap(pivot,left);
    left
}

//fn partition_random<T: PartialOrd>(arr: &mut [T], lo: usize, hi: usize) -> usize {
    //// 在 Cargo.toml 的依赖中添加 rand 库
    //use rand::Rng;
    //let mut rng = rand::thread_rng();
    //let pivot = rng.gen_range(lo..=hi);

    //// 交换 lo 和 pivot 位置上的元素，从而间接使得 pivot = lo
    //// 因此后序操作和 partition() 函数一致
    //arr.swap(lo, pivot);

    //let pivot = lo;
    //let (mut left, mut right) = (lo, hi);
    //while left < right {
        //// 找到右边第一个不大于等于 arr[pivot] 的元素
        //while left < right && arr[right] >= arr[pivot] {
            //right -= 1;
        //}

        //// 找到左边第一个不小于等于 arr[pivot] 的元素
        //while left < right && arr[left] <= arr[pivot] {
            //left += 1;
        //}
        
        //// 交换前面找到的两个元素
        //if left != right {
            //arr.swap(left, right);
        //}
    //}

    //arr.swap(pivot, left);

    //// 返回正确的分割位置
    //left
//}


//select_sort
pub fn select_sort<T:PartialOrd>(arr:&mut [T]){
    if arr.len()<=1 {
        return;
    }
    let size  =arr.len();
    for i in 0..(size-1){
        let mut min_index = i;
        for j in (i+1)..size {
            if arr[j]<arr[min_index] {
                min_index = j;
            }
        }
        if min_index!=i{
            arr.swap(i,min_index);
        }
    }
}

//shell_sort
pub fn shell_sort<T:Ord + Copy>(values :&mut Vec<T>){

}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_empty_vec() {
        let mut empty_vec: Vec<String> = vec![];
        bubble_sort(&mut empty_vec);
        assert_eq!(empty_vec, Vec::<String>::new());
    }

    #[test]
    fn test_number_vec() {
        let mut vec = vec![7, 49, 73, 58, 30, 72, 44, 78, 23, 9];
        bubble_sort(&mut vec);
        assert_eq!(vec, vec![7, 9, 23, 30, 44, 49, 58, 72, 73, 78]);
    }

    #[test]
    fn test_string_vec() {
        let mut vec = vec![
            String::from("Bob"),
            String::from("David"),
            String::from("Carol"),
            String::from("Alice"),
        ];
        bubble_sort(&mut vec);
        assert_eq!(
            vec,
            vec![
            String::from("Alice"),
            String::from("Bob"),
            String::from("Carol"),
            String::from("David"),
            ]
            );
    }

    #[test]
    fn empty() {
        let arr: [usize; 0] = [];
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res));
    }

    #[test]
    fn one_element() {
        let arr: [usize; 1] = [4];
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res));
    }

    #[test]
    fn already_sorted() {
        let arr: [usize; 3] = [10, 9, 105];
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res));
    }

    #[test]
    fn basic() {
        let arr: [usize; 4] = [35, 53, 1, 0];
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res));
    }

    #[test]
    fn odd_number_of_elements() {
        let arr: Vec<usize> = vec![1, 21, 5, 11, 58];
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res));
    }

    #[test]
    fn repeated_elements() {
        let arr: Vec<usize> = vec![542, 542, 542, 542];
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res));
    }

     #[test]
    fn cocktail_shaker_sort_basic() {
        let mut arr = vec![5, 2, 1, 3, 4, 6];
        cocktail_shaker_sort(&mut arr);
        assert_eq!(arr, vec![1, 2, 3, 4, 5, 6]);
    }

    #[test]
    fn cocktail_shaker_sort_empty() {
        let mut arr = Vec::<i32>::new();
        cocktail_shaker_sort(&mut arr);
        assert_eq!(arr, vec![]);
    }

    #[test]
    fn cocktail_shaker_sort_one_element() {
        let mut arr = vec![1];
        cocktail_shaker_sort(&mut arr);
        assert_eq!(arr, vec![1]);
    }

    #[test]
    fn cocktail_shaker_sort_pre_sorted() {
        let mut arr = vec![1, 2, 3, 4, 5, 6];
        cocktail_shaker_sort(&mut arr);
        assert_eq!(arr, vec![1, 2, 3, 4, 5, 6]);
    }
    
    #[test]
    fn comb_sortdescending() { 
        //descending
        let mut ve1 = vec![6, 5, 4, 3, 2, 1];
        comb_sort(&mut ve1);
        for i in 0..ve1.len() - 1 {
            assert!(ve1[i] <= ve1[i + 1]);
        }
    }

    #[test]
    fn comb_sortascending() { 
        //pre-sorted
        let mut ve2 = vec![1, 2, 3, 4, 5, 6];
        comb_sort(&mut ve2);
        for i in 0..ve2.len() - 1 {
            assert!(ve2[i] <= ve2[i + 1]);
        }
    }
    
    #[test]
    fn heap_test_empty_vec() {
        let mut empty_vec: Vec<String> = vec![];
        heap_sort(&mut empty_vec);
        assert_eq!(empty_vec, Vec::<String>::new());
    }

    #[test]
    fn heap_test_number_vec() {
        let mut vec = vec![7, 49, 73, 58, 30, 72, 44, 78, 23, 9];
        heap_sort(&mut vec);
        assert_eq!(vec, vec![7, 9, 23, 30, 44, 49, 58, 72, 73, 78]);
    }

    #[test]
    fn heap_test_string_vec() {
        let mut vec = vec![
            String::from("Bob"),
            String::from("David"),
            String::from("Carol"),
            String::from("Alice"),
        ];
        heap_sort(&mut vec);
        assert_eq!(
            vec,
            vec![
                String::from("Alice"),
                String::from("Bob"),
                String::from("Carol"),
                String::from("David"),
            ]
        );
    }



        #[test]
        fn inser_test_empty_vec() {
            let mut empty_vec: Vec<String> = vec![];
            insert_sort(&mut empty_vec);
            assert_eq!(empty_vec, Vec::<String>::new());
        }
    
}
