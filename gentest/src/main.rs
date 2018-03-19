#![feature(i128_type)]
#![feature(i128)]
extern crate rand;
use std::cmp::PartialOrd;
use rand::ThreadRng;

trait LowHigh {
    fn low() -> Self;
    fn high() -> Self;
}

impl LowHigh for i128 {
    fn low() -> Self {
        std::i128::MIN
    }
    fn high() -> Self {
        std::i128::MAX
    }
}
impl LowHigh for i64 {
    fn low() -> Self {
        std::i64::MIN
    }
    fn high() -> Self {
        std::i64::MAX
    }
}
impl LowHigh for i32 {
    fn low() -> Self {
        std::i32::MIN
    }
    fn high() -> Self {
        std::i32::MAX
    }
}
impl LowHigh for u32 {
    fn low() -> Self {
        std::u32::MIN
    }
    fn high() -> Self {
        std::u32::MAX
    }
}

use rand::distributions::range::SampleRange;
fn uniform<T: SampleRange + PartialOrd + LowHigh>(rng: &mut rand::ThreadRng) -> T {
    use rand::distributions::{IndependentSample, Range};
    let between = Range::new(T::low(), T::high());
    between.ind_sample(rng)
}

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

fn write_file(text: String, base: &str, name: &str) -> std::io::Result<()> {
    use std::path::Path;
    use std::io::Write;
    let mut f = std::fs::File::create(Path::new(base).join(name))?;
    f.write_all(text.as_bytes())
}

fn write(input: Vec<String>, output: Vec<String>, path: &str) -> std::io::Result<()> {
    let input = input.join("\n");
    let output = output.join("\n");
    std::fs::create_dir_all(path)?;
    write_file(input, path, "input.txt")?;
    write_file(output, path, "output.txt")
}

fn conv_test(rng: &mut ThreadRng, in_base: u32, out_base: u32) -> (String, String) {
    let num = uniform::<i128>(rng);
    (
        format!("{} {} {}", in_base, out_base, format(num, in_base)),
        format(num, out_base),
    )
}

fn gen_conv_test(rng: &mut ThreadRng, count: usize, path: &str, in_base: u32, out_base: u32) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = conv_test(rng, in_base, out_base);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn and_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng);
    let rhs = uniform::<i128>(rng);
    (format!("10 {} & {}", lhs, rhs), (lhs & rhs).to_string())
}

fn gen_and_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = and_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn or_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng);
    let rhs = uniform::<i128>(rng);
    (format!("10 {} | {}", lhs, rhs), (lhs | rhs).to_string())
}

fn gen_or_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = or_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn xor_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng);
    let rhs = uniform::<i128>(rng);
    (format!("10 {} ^ {}", lhs, rhs), (lhs ^ rhs).to_string())
}

fn gen_xor_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = xor_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn not_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng);
    (format!("10 {} ~", lhs), (!lhs).to_string())
}

fn gen_not_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = not_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

// > 0 => shift left
// < 0 => shift right
fn shift_test(rng: &mut ThreadRng, direction: i32) -> (String, String) {
    assert!(direction != 0);
    let lhs = uniform::<i128>(rng);
    let rhs = uniform::<u32>(rng) % 128;
    let (op, res) = if direction > 0 {
        ("<<", lhs << rhs)
    } else {
        (">>", lhs >> rhs)
    };
    (format!("10 {} {} {}", lhs, op, rhs), res.to_string())
}

fn gen_shift_test(rng: &mut ThreadRng, count: usize, path: &str, direction: i32) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = shift_test(rng, direction);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn add_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng);
    let rhs = uniform::<i128>(rng);
    use std::i128;
    (
        format!("10 {} + {}", lhs, rhs),
        lhs.overflowing_add(rhs).0.to_string(),
    )
}

fn gen_add_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = add_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn substract_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng);
    let rhs = uniform::<i128>(rng);
    use std::i128;
    (
        format!("10 {} - {}", lhs, rhs),
        lhs.overflowing_sub(rhs).0.to_string(),
    )
}

fn gen_substract_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = substract_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn neg_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng);
    (format!("10 {} -", lhs), lhs.overflowing_neg().0.to_string())
}

fn gen_neg_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = neg_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

// > 0 => left
// < 0 => right
fn rotate_test(rng: &mut ThreadRng, direction: i32) -> (String, String) {
    assert!(direction != 0);
    let lhs = uniform::<i128>(rng);
    let rhs = uniform::<i32>(rng).abs() as u32;
    let (op, res) = if direction > 0 {
        ("rol", lhs.rotate_left(rhs))
    } else {
        ("ror", lhs.rotate_right(rhs))
    };
    (format!("10 {} {} {}", lhs, op, rhs), res.to_string())
}

fn gen_rotate_test(rng: &mut ThreadRng, count: usize, path: &str, direction: i32) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = rotate_test(rng, direction);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn mul_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng) as i128;
    let rhs = uniform::<i128>(rng) as i128;
    use std::i128;
    (
        format!("10 {} * {}", lhs, rhs),
        lhs.overflowing_mul(rhs).0.to_string(),
    )
}

fn gen_mul_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = mul_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn div_test(rng: &mut ThreadRng) -> (String, String) {
    let lhs = uniform::<i128>(rng);
    let rhs = uniform::<i128>(rng);
    let rhs = if rhs == 0 { uniform::<i128>(rng) } else { rhs };
    use std::i128;
    (format!("10 {} / {}", lhs, rhs), (lhs / rhs).to_string())
}

fn gen_div_test(rng: &mut ThreadRng, count: usize, path: &str) {
    let mut input = Vec::new();
    let mut output = Vec::new();
    for _ in 0..count {
        let (i, o) = div_test(rng);
        input.push(i);
        output.push(o);
    }
    write(input, output, path).unwrap();
}

fn main() {
    let mut rng = rand::thread_rng();
    let count = 500;
    gen_conv_test(&mut rng, count, "../tests/00_conv_10_10", 10, 10);
    gen_and_test(&mut rng, count, "../tests/01_and");
    gen_or_test(&mut rng, count, "../tests/02_or");
    gen_xor_test(&mut rng, count, "../tests/03_xor");
    gen_not_test(&mut rng, count, "../tests/04_not");
    gen_shift_test(&mut rng, count, "../tests/05_shl", 1);
    gen_shift_test(&mut rng, count, "../tests/06_shr", -1);
    gen_add_test(&mut rng, count, "../tests/07_add");
    gen_substract_test(&mut rng, count, "../tests/08_sub");
    gen_neg_test(&mut rng, count, "../tests/09_neg");
    gen_rotate_test(&mut rng, count, "../tests/10_rol", 1);
    gen_rotate_test(&mut rng, count, "../tests/11_ror", -1);
    gen_conv_test(&mut rng, count, "../tests/12_conv_16_16", 16, 16);
    gen_mul_test(&mut rng, count, "../tests/13_mul");
    gen_div_test(&mut rng, count, "../tests/14_div");
    gen_conv_test(&mut rng, count, "../tests/15_conv_2_2", 2, 2);
}
