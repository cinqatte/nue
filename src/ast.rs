
pub enum Node {
  Program(Program),
  Statement(Statement),
  Expression(Expression)
}

pub struct Program {
  pub statements: Vec<Statement>
}

pub enum Statement {
  ExpressionStatement(Expression)
}

pub enum Expression {
  Identifier(String),
  IntegerLiteral(i64),
  FloatLiteral(f64),
  StringLiteral(String),
  InfixExpression {
    left: Box<Expression>,
    operator: String,
    right: Box<Expression>
  }
}