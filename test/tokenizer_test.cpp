// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Tomasz Chłopek

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <token/range/range.hpp>
#include <token/result.hpp>
#include <token/token.hpp>
#include <token/tokenizer.hpp>

using namespace puml;
using namespace puml::lex;

static puml::context make_ctx(const std::vector<std::string>& lines) {
  return puml::context{ "", lines };
}

// ============================================================================
// Tokenizer Tests (moved from pumltest.cpp)
// ============================================================================

class TokenizerTest : public ::testing::Test {
};

TEST_F(TokenizerTest, EmptyInput) {
  std::vector<std::string> lines;
  auto r = tokenize(make_ctx(lines));
  EXPECT_EQ(r.get_range().size(), 0);
}

TEST_F(TokenizerTest, SingleIdentifier) {
  std::vector<std::string> lines{"foo"};
  auto r = tokenize(make_ctx(lines));
  EXPECT_EQ(r.get_range().size(), 1);
  auto it = r.get_range().begin();
  EXPECT_EQ(it->name(), "identifier");
  EXPECT_EQ(it->str(lines), "foo");
}

TEST_F(TokenizerTest, MixedTokens) {
  std::vector<std::string> lines{"foo -> bar . --> baz { } : textdata"};
  auto r = tokenize(make_ctx(lines));
  
  std::vector<std::string> expected_strs = {
    "foo", "->", "bar", ".", "-->", "baz", "{", "}", ": textdata"
  };
  std::vector<std::string> expected_names = {
    "identifier", "->", "identifier", ".", "-->", "identifier", "{", "}", "text"
  };
  
  EXPECT_EQ(r.get_range().size(), expected_strs.size());
  auto it = r.get_range().begin();
  for (size_t i = 0; i < expected_strs.size(); ++i, ++it) {
    EXPECT_EQ(it->str(lines), expected_strs[i]);
    EXPECT_EQ(it->name(), expected_names[i]);
  }
}

TEST_F(TokenizerTest, MultiLine) {
  std::vector<std::string> lines{"alpha", "beta"};
  auto r = tokenize(make_ctx(lines));
  EXPECT_EQ(r.get_range().size(), 2);
  auto it = r.get_range().begin();
  EXPECT_EQ(it->str(lines), "alpha");
  ++it;
  EXPECT_EQ(it->str(lines), "beta");
}
