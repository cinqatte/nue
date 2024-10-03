#![allow(dead_code)]

mod lexer;

// use std::fs;
// use std::env;
// use std::error::Error;
// use std::process;
// use std::path::Path;

use crate::lexer::{Lexer};

fn main() {
  // let arguments: Vec<String> = env::args().collect();
  //
  // if arguments.len() != 2 {
  //   eprintln!("usage: nune <filename>");
  //   process::exit(1);
  // }
  //
  // let filename = &arguments[1];
  //
  // if filename.len() < 6 {
  //   eprintln!("filename '{}' is too short", filename);
  //   process::exit(1);
  // }
  //
  // if Path::new(filename).extension().map_or(false, |extension| extension == "nune") == false {
  //   eprintln!("filename '{}' is an invalid nune file", filename);
  //   process::exit(1);
  // }
  //
  // let code = match fs::read_to_string(filename) {
  //   Ok(content) => {
  //     if content.is_empty() {
  //       eprintln!("error reading file '{}': file is empty", filename);
  //       process::exit(1);
  //     }
  //
  //     content
  //   },
  //   Err(error) => {
  //     eprintln!("error reading file '{}': {:?}", filename, error.to_string());
  //     process::exit(1);
  //   }
  // };


  let test_code = String::from("'A' '\n' \"\x73\" 44b44");
  let test_path = "test.nue";
  let mut lexer = Lexer::new(test_code, test_path.to_string());


  while !lexer.is_eof() {
    let mut token = lexer.get_token();
    println!("{:?}", token);
  }
}



