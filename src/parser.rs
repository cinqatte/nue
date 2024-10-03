
use crate::token::Token;
use crate::token_type::TokenType;
use crate::lexer::Lexer;
use crate::ast::{Program, Statement, Expression};

pub struct Parser {
  lexer: Lexer,
  current_token: Token,
  peek_token: Token
}

impl Parser {
  pub fn new(mut lexer: Lexer) -> Self {
    let current_token = lexer.get_token();
    let peek_token = lexer.get_token();

    Self {
      lexer,
      current_token,
      peek_token
    }
  }

  fn next_token(&mut self) {
    self.current_token = std::mem::replace(&mut self.peek_token, self.lexer.get_token());
  }

  pub fn parse_program(&mut self) -> Program {
    let mut statements = Vec::new();
    while self.current_token.token_type != TokenType::TokenEof {
      if let Some(stmt) = self.parse_statement() {
        statements.push(stmt);
      }
      self.next_token();
    }
    Program { statements }
  }

  fn parse_statement(&mut self) -> Option<Statement> {
    match self.current_token.token_type {
      TokenType::TokenId | TokenType::TokenValueInt | TokenType::TokenValueFloat | TokenType::TokenValueString => {
        Some(Statement::ExpressionStatement(self.parse_expression()))
      }
      _ => None,
    }
  }

  fn parse_expression(&mut self) -> Expression {
    match self.current_token.token_type {
      TokenType::Ident => Expression::Identifier(self.current_token.literal.clone()),
      TokenType::Int => Expression::IntegerLiteral(self.current_token.literal.parse().unwrap()),
      TokenType::Float => Expression::FloatLiteral(self.current_token.literal.parse().unwrap()),
      TokenType::String => Expression::StringLiteral(self.current_token.literal.clone()),
      // ... (other expressions)
      _ => unimplemented!(),
    }
  }

}