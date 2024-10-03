#![allow(dead_code)]

#[derive(Clone, Debug)]
enum Type {
  Eof,

  BoolLiteral,
  CharLiteral,
  IntLiteral,
  FloatLiteral,
  StringLiteral,

  Add,
  Sub,
  Mul,
  Div,
  Mod,

  Assign,

  Or,
  Not,
  And,

  LessThan,
  GreaterThan,
  NotEqual,
  LessThanEqual,
  GreaterThanEqual,

  BitOr,
  BitNot,
  BitAnd,
  BitXor,
  BitLeftShift,
  BitRightShift,

  LeftParenthesis,
  RightParenthesis,
  LeftBracket,
  RightBracket,
  LeftBrace,
  RightBrace,

  Period,
  Comma,
  Colon,
  Semi,

  Var,
  Let,
  Const,

  Void,
  Bool,
  Char,
  Int,
  Float,
  String,
  Any,

  Enum,
  Struct,
  Fun,

  If,
  Elif,
  Else,
  Switch,
  Case,
  Default,

  For,
  While,
  Do,

  Continue,
  Break,
  Return,

  Identifier,

  Error
}

#[derive(Clone, Debug)]
enum Value {
  Bool(bool),
  Char(char),
  Int(i64),
  Float(f64),
  String(String)
}

#[derive(Clone, Debug)]
pub struct Token {
  typ: Type,
  val: Value
}

impl Token {
  fn new(typ: Type, val: Value) -> Self {
    Self {
      typ,
      val
    }
  }

  fn get_type(self) -> Type {
    self.typ
  }

  fn get_value(self) -> Value {
    self.val
  }
}

use lazy_static::lazy_static;
use std::collections::hash_map::HashMap;

lazy_static! {
  static ref KEYWORD_MAP: HashMap<&'static str, Type> = {
    let mut map = HashMap::new();
    map.insert("void", Type::Void);
    map.insert("bool", Type::Bool);
    map.insert("char", Type::Char);
    map.insert("int", Type::Int);
    map.insert("float", Type::Float);
    map.insert("string", Type::String);
    map.insert("any", Type::Any);

    map.insert("enum", Type::Enum);
    map.insert("struct", Type::Struct);
    map.insert("fun", Type::Fun);

    map.insert("if", Type::If);
    map.insert("elif", Type::Elif);
    map.insert("else", Type::Else);
    map.insert("switch", Type::Switch);
    map.insert("case", Type::Case);
    map.insert("default", Type::Default);

    map.insert("for", Type::For);
    map.insert("while", Type::While);
    map.insert("do", Type::Do);

    map.insert("continue", Type::Continue);
    map.insert("break", Type::Break);
    map.insert("return", Type::Return);
    map
  };

  static ref OPERATOR_MAP: HashMap<&'static str, Type> = {
    let mut map = HashMap::new();
    map.insert("+", Type::Add);
    map.insert("-", Type::Sub);
    map.insert("*", Type::Sub);
    map.insert("/", Type::Div);
    map.insert("%", Type::Mod);

    map.insert("=", Type::Assign);

    map.insert("||", Type::Or);
    map.insert("!", Type::Not);
    map.insert("&&", Type::And);

    map.insert("<", Type::LessThan);
    map.insert(">", Type::GreaterThan);
    map.insert("!=", Type::NotEqual);
    map.insert("<=", Type::LessThanEqual);
    map.insert(">=", Type::GreaterThanEqual);

    map.insert("|", Type::BitOr);
    map.insert("~", Type::BitNot);
    map.insert("&", Type::BitAnd);
    map.insert("^", Type::BitXor);
    map.insert("<<", Type::BitLeftShift);
    map.insert(">>", Type::BitRightShift);
    map
  };
  static ref DELIMITER_MAP: HashMap<&'static str, Type> = {
    let mut map = HashMap::new();
    map.insert("(", Type::LeftParenthesis);
    map.insert(")", Type::RightParenthesis);
    map.insert("[", Type::LeftBracket);
    map.insert("]", Type::RightBracket);
    map.insert("{", Type::LeftBrace);
    map.insert("}", Type::RightBrace);

    map.insert(".", Type::Period);
    map.insert(",", Type::Comma);
    map.insert(":", Type::Colon);
    map.insert("'", Type::Semi);
    map
  };

  static ref OPERATORS: &'static str = "+-*/%=|!&<>^~";
  static ref DELIMITERS: &'static str = "()[]{}.,:;";
}

#[derive(Clone, Debug)]
pub struct Lexer {
  code: String,
  path: String,
  current: char,
  index: i32,
  line: i32,
  column: i32
}

impl Lexer {
  pub fn new(code: String, path: String) -> Self {
    let current = code.chars().next().unwrap_or('\0');

    Self {
      code,
      path,
      current,
      index: 0,
      line: 1,
      column: 1
    }
  }

  fn advance(&mut self) {
    if self.current != '\0' && self.index < self.code.len() as i32 {
      if self.current == '\n' {
        self.line += 1;
        self.column = 0;
      } else {
        self.column += 1;
      }

      self.index += 1;
      self.current = self.code.chars().nth(self.index as usize).unwrap_or('\0');
    } else {
      self.current = '\0'
    }
  }

  fn skip_whitespace(&mut self) {
    while self.current.is_whitespace() {
      self.advance()
    }
  }

  fn set_error(&mut self) {
    self.current = '\0'
  }

  pub fn is_eof(&self) -> bool {
    self.current == '\0' || self.index >= self.code.len() as i32
  }

  pub fn get_token(&mut self) -> Token {
    if self.current.is_whitespace() {
      self.skip_whitespace()
    }

    if self.current != '\0' && self.index < self.code.len() as i32 {
      if self.current.is_digit(10) {
        return self.get_token_number();
      }

      if self.current.is_alphabetic() {
        return self.get_token_identifier();
      }

      if OPERATORS.contains(self.current) {
        return self.get_token_operator();
      }

      if DELIMITERS.contains(self.current) {
        return self.get_token_delimiter();
      }

      if self.current == '\'' {
        return self.get_token_char();
      }

      if self.current == '"' {
        return self.get_token_string();
      }

      let ch = self.current;
      self.set_error();
      Token::new(Type::Error, Value::String(format!("{}:{}:{}: unknown character '{}'", self.path, self.line, self.column, ch)));
    }

    Token::new(Type::Eof, Value::Char('\0'))
  }

  fn get_token_number(&mut self) -> Token {
    let start = self.index;

    while self.current.is_digit(10) {
      self.advance();
    }

    if self.current == '.' {
      self.advance();

      while self.current.is_digit(10) {
        self.advance();
      }
    }

    if self.current == 'e' || self.current == 'E' {
      self.advance();

      if self.current == '+' || self.current == '-' {
        self.advance();
      }

      while self.current.is_digit(10) {
        self.advance();
      }
    }

    let number = &self.code[start as usize..self.index as usize].to_string();

    return if number.contains('.') || number.contains('e') || number.contains('E') {
      match number.parse::<f64>() {
        Ok(val) => {
          if val.fract() == 0.0 {
            return Token::new(Type::FloatLiteral, Value::Int(val as i64));
          }
          Token::new(Type::FloatLiteral, Value::Float(val))
        },
        Err(_) => {
          self.set_error();
          Token::new(Type::Error, Value::String(format!("{}:{}:{}: invalid float literal '{}'", self.path, self.line, self.column, number)))
        }
      }
    } else {
      match number.parse::<i64>() {
        Ok(val) => Token::new(Type::IntLiteral, Value::Int(val)),
        Err(_) => {
          self.set_error();
          Token::new(Type::Error, Value::String(format!("{}:{}:{}: invalid int literal '{}'", self.path, self.line, self.column, number)))
        }
      }
    }
  }

  fn get_token_identifier(&mut self) -> Token {
    let start = self.index;

    while self.current.is_alphabetic() || self.current == '_' {
      self.advance();
    }

    let identifier = &self.code[start as usize..self.index as usize];

    return match identifier {
      "true" => Token::new(Type::BoolLiteral, Value::Bool(true)),
      "false" => Token::new(Type::BoolLiteral, Value::Bool(false)),
      &_ => {
        let typ = KEYWORD_MAP.get(identifier).cloned().unwrap_or(Type::Identifier);
        Token::new(typ, Value::String(identifier.to_string()))
      }
    }
  }

  fn get_token_operator(&mut self) -> Token {
    let mut operator = self.current.to_string();
    self.advance();

    if !self.is_eof() {
      let next_operator = self.current;
      let potential_operator = format!("{}{}", operator, next_operator);

      if OPERATOR_MAP.contains_key(potential_operator.as_str()) {
        operator = potential_operator;
        self.advance();
      }
    }

    let typ = OPERATOR_MAP.get(operator.as_str()).cloned().unwrap();
    Token::new(typ, Value::String(operator))
  }

  fn get_token_delimiter(&mut self) -> Token {
    let delimiter = self.current.to_string();
    self.advance();
    let typ = DELIMITER_MAP.get(delimiter.as_str()).cloned().unwrap();
    Token::new(typ, Value::String(delimiter))
  }

  fn get_token_char(&mut self) -> Token {
    self.advance();

    let ch = if self.current == '\\' {
      self.advance();
      self.process_escape_char()
    } else {
      let ch = self.current;
      self.advance();
      ch
    };

    if self.current != '\'' {
      self.set_error();
      Token::new(Type::Error, Value::String(format!("{}:{}:{}: unterminated char literal", self.path, self.line, self.column)))
    } else {
      self.advance();
      Token::new(Type::CharLiteral, Value::Char(ch))
    }
  }

  fn get_token_string(&mut self) -> Token {
    self.advance();
    let mut string = String::new();
    let mut index_start = 0;

    while self.current != '"' && index_start < 256 && !self.is_eof() {
      let ch = if self.current == '\\' {
        self.advance();
        self.process_escape_char()
      } else {
        self.current
      };

      string.push(ch);
      self.advance();
      index_start += 1;
    }

    if index_start >= 256 || self.is_eof() {
      self.set_error();
      if index_start >= 256 {
        Token::new(Type::Error, Value::String(format!("{}:{}:{}: string length exceed 255 characters", self.path, self.line, self.column)))
      } else {
        Token::new(Type::Error, Value::String(format!("{}:{}:{}: unterminated string literal", self.path, self.line, self.column)))
      }

    } else {
      self.advance();
      Token::new(Type::StringLiteral, Value::String(string))
    }
  }

  fn process_escape_char(&mut self) -> char {
    match self.current {
      'n' => '\n',
      't' => '\t',
      'r' => '\r',
      '0' => '\0',
      '\\' => '\\',
      '\'' => '\'',
      '"' => '"',
      'x' => self.process_hex_escape(2),
      'u' => self.process_hex_escape(4),
      _ => self.current,
    }
  }

  fn process_hex_escape(&mut self, len: usize) -> char {
    let start = self.index;
    for _ in 0..len {
      self.advance();
    }
    let hex = &self.code[start as usize..self.index as usize];
    u32::from_str_radix(hex, 16).unwrap_or(0) as u8 as char
  }
}

