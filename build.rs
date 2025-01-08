fn main() {
    println!("cargo:rustc-link-search=native=/home/philae/git/eth/git/sdsl-lite-fm");
    println!("cargo:rustc-link-lib=sdsl");
    println!("cargo:rustc-link-lib=stdc++");
    println!("cargo:rustc-link-lib=divsufsort");
    println!("cargo:rustc-link-lib=divsufsort64");
    println!("cargo:rustc-link-lib=static=sdslfm");
}
