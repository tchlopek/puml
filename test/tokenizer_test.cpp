#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "token/range/range.hpp"
#include "token/token.hpp"
#include "token/tokenizer.hpp"

using namespace tkn;

// ============================================================================
// Tokenizer Tests (moved from pumltest.cpp)
// ============================================================================

class TokenizerTest : public ::testing::Test {
};

TEST_F(TokenizerTest, EmptyInput) {
  std::vector<std::string> lines;
  auto r = tokenize(lines);
  EXPECT_EQ(r.size(), 0);
}

TEST_F(TokenizerTest, SingleIdentifier) {
  std::vector<std::string> lines{"foo"};
  auto r = tokenize(lines);
  EXPECT_EQ(r.size(), 1);
  auto it = r.begin();
  EXPECT_EQ(it->name(), "identifier");
  EXPECT_EQ(it->str(lines), "foo");
}

TEST_F(TokenizerTest, MixedTokens) {
  std::vector<std::string> lines{"foo -> bar --> baz { } : textdata"};
  auto r = tokenize(lines);
  
  std::vector<std::string> expected_strs = {
    "foo", "->", "bar", "-->", "baz", "{", "}", ": textdata"
  };
  std::vector<std::string> expected_names = {
    "identifier", "->", "identifier", "-->", "identifier", "{", "}", "text"
  };
  
  EXPECT_EQ(r.size(), expected_strs.size());
  auto it = r.begin();
  for (size_t i = 0; i < expected_strs.size(); ++i, ++it) {
    EXPECT_EQ(it->str(lines), expected_strs[i]);
    EXPECT_EQ(it->name(), expected_names[i]);
  }
}

TEST_F(TokenizerTest, MultiLine) {
  std::vector<std::string> lines{"alpha", "beta"};
  auto r = tokenize(lines);
  EXPECT_EQ(r.size(), 2);
  auto it = r.begin();
  EXPECT_EQ(it->str(lines), "alpha");
  ++it;
  EXPECT_EQ(it->str(lines), "beta");
}
