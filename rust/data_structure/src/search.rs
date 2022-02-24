//use rand;
use std::cmp::Ordering;

// binary_search
pub fn binary_search<T:Ord>(item:&T,arr:&[T])->Option<usize>{
    let mut left =0;
    let mut right = arr.len();

    while left < right {
        let mid =left+(right-left)/2;
        
        match item.cmp(&arr[mid]) {
            Ordering::Less => right = mid,
            Ordering::Equal => return Some(mid),
            Ordering::Greater=>left = mid+1,
        }
    }
    None
}

//binary_search_rec
pub fn binary_search_rec<T:Ord>(
    list_of_item:&[T],
    target:&T,
    left:&usize,
    right:&usize,
    ) -> Option<usize>
{
    if left>= right{
        return  None;
    }

    let mid:usize = left +(right-left)/2;
    match target.cmp(&list_of_item[mid]) {
        Ordering::Less => binary_search_rec(list_of_item, target, left, &mid),
        Ordering::Equal=> Some(mid),
        Ordering::Greater => binary_search_rec(list_of_item, target, &(mid+1), right)
    }
}




