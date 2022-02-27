

fn main()
{
    let v1 =[1,2,3];

    let mut arr_iter = v1.into_iter();
    assert_eq!(arr_iter.next(),Some(1));
    for val in v1{
        println!("{}",val);
    }
}
