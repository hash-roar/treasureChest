
//reverse string
pub fn reverse(text: &str)->String {
    text.chars().rev().collect()
}

//knuth_morris_pratt
pub fn knuth_morris_pratt(st:String,pat:String) -> Vec<usize>{
    if st.is_empty()||pat.is_empty() {
        return vec![]; 
    }

    let string = st.into_bytes();
    let pattern = pat.into_bytes();

    let mut next = vec![0];
    for i in 1..pattern.len() {
        let mut j = next[i-1];
        while j>0 && pattern[j]!=pattern[i] {
            j = next[j-1];
        }
        next.push(if pattern[j]==pattern[i]{j+1}else{j});
    }

    let mut ret = vec![];
    let mut j=0;

    for (i,&c) in string.iter().enumerate(){
        while j>0 && c !=pattern[j] {
            j=next[j-1];
        }
        if c==pattern[j]{
            j+=1;
        }

        if j==pattern.len() {
            ret.push(i+1-j);
            j = next[j-1];
        }
    }
    ret
}

//
