#![feature(i128_type)]
extern crate rand;

fn format(mut i: i128, base: u32) -> String {
    assert!(base > 1 && base <= 16);
    if i == 0 {
        return "0".to_owned();
    }
    let digit = [
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    ];
    let mut res = String::new();
    let is_negative = i < 0;
    if is_negative {
        i = -i;
    }
    while i > 0 {
        res.push(digit[(i % base as i128) as usize]);
        i /= base as i128;
    }
    if is_negative {
        res.push('-');
    }
    res.chars().rev().collect()
}

fn write_all(text: String, base: &str, name: &str) -> std::io::Result<()> {
    use std::path::Path;
    use std::io::Write;
    let mut f = std::fs::File::create(Path::new(base).join(name))?;
    f.write_all(text.as_bytes())
}

fn write(input: Vec<String>, output: Vec<String>, path: &str) -> std::io::Result<()> {
    let input = input.join("\n");
    let output = output.join("\n");
    std::fs::create_dir_all(path)?;
    write_all(input, path, "input.txt")?;
    write_all(output, path, "output.txt")
}

fn conv_test(in_base: u32, out_base: u32) -> (String, String) {
    let num = rand::random::<i128>();
    (
        format!("{} {} {}", in_base, out_base, format(num, in_base)),
        format(num, out_base),
    )
}

fn gen_conv_test(count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = conv_test(10, 10);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn and_test() -> (String, String) {
    let lhs = rand::random::<i128>();
    let rhs = rand::random::<i128>();
    (format!("10 {} & {}", lhs, rhs), (lhs & rhs).to_string())
}

fn gen_and_test(count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = and_test();
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn or_test() -> (String, String) {
    let lhs = rand::random::<i128>();
    let rhs = rand::random::<i128>();
    (format!("10 {} | {}", lhs, rhs), (lhs | rhs).to_string())
}

fn gen_or_test(count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = or_test();
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn xor_test() -> (String, String) {
    let lhs = rand::random::<i128>();
    let rhs = rand::random::<i128>();
    (format!("10 {} ^ {}", lhs, rhs), (lhs ^ rhs).to_string())
}

fn gen_xor_test(count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = xor_test();
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn not_test() -> (String, String) {
    let lhs = rand::random::<i128>();
    (format!("10 {} ~", lhs), (!lhs).to_string())
}

fn gen_not_test(count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = not_test();
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn main() {
    gen_conv_test(50, "../tests/00_conv_10_10");
    gen_and_test(50, "../tests/01_and");
    gen_or_test(50, "../tests/02_or");
    gen_xor_test(50, "../tests/03_xor");
    gen_not_test(50, "../tests/04_not");
}
