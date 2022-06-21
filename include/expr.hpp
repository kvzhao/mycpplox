
#pragma once

#include <any>
#include <memory>

#include "token.hpp"

struct Expr;
struct Binary;

struct ExprVisitor {
  virtual std::any VisitBinaryExpr(std::shared_ptr<Binary> expr) = 0;
  virtual ~ExprVisitor() = default;
};

struct Expr {
  return std::any accept() = 0;
};

struct Binary : Expr, public std::enable_shared_from_this<Binary> {

  Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
      : left{std::move(left)}, op{std::move(op)}, right{std::move(right)} {}

  std::any accept(ExprVisitor &Visitor) override {
    return Visitor.VisitBinaryExpr(shared_from_this());
  }

  const std::shared_ptr<Expr> left;
  const Token op;
  const std::shared_ptr<Expr> right;
};