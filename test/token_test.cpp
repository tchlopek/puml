#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "token/token.hpp"
#include "token/identifier.hpp"
#include "token/kw_arrow_single.hpp"
#include "token/kw_arrow_double.hpp"
#include "token/l_brace.hpp"
#include "token/r_brace.hpp"
#include "token/text.hpp"

using namespace puml;

// Test fixture class for token tests
class TokenTest : public ::testing::Test {
protected:
  // Create test text content for str() testing
  std::vector<std::string> text_content = {
    "line0_content",
    "line1_content",
    "line2_content"
  };
};

// ============================================================================
// Construction Tests
// ============================================================================

TEST_F(TokenTest, ConstructIdentifier) {
  identifier id(0, 0, 4);
  token t(id);
  EXPECT_TRUE(t.is<identifier>());
}

TEST_F(TokenTest, ConstructText) {
  text txt(1, 5, 12);
  token t(txt);
  EXPECT_TRUE(t.is<text>());
}

TEST_F(TokenTest, ConstructKwArrowSingle) {
  kw_arrow_single arrow(0, 2, 4);
  token t(arrow);
  EXPECT_TRUE(t.is<kw_arrow_single>());
}

TEST_F(TokenTest, ConstructKwArrowDouble) {
  kw_arrow_double arrow(0, 5, 8);
  token t(arrow);
  EXPECT_TRUE(t.is<kw_arrow_double>());
}

TEST_F(TokenTest, ConstructLBrace) {
  l_brace brace(2, 0, 1);
  token t(brace);
  EXPECT_TRUE(t.is<l_brace>());
}

TEST_F(TokenTest, ConstructRBrace) {
  r_brace brace(2, 10, 11);
  token t(brace);
  EXPECT_TRUE(t.is<r_brace>());
}

TEST_F(TokenTest, ConstructWithTemporaryCopies) {
  token t(identifier(1, 3, 7));
  EXPECT_TRUE(t.is<identifier>());
}

// ============================================================================
// Type Checking Tests (is() method)
// ============================================================================

TEST_F(TokenTest, IsSingleType) {
  token t(identifier(0, 0, 4));
  EXPECT_TRUE(t.is<identifier>());
  EXPECT_FALSE(t.is<text>());
  EXPECT_FALSE(t.is<l_brace>());
}

TEST_F(TokenTest, IsMultipleTypes) {
  token t(identifier(0, 0, 4));
  EXPECT_TRUE((t.is<identifier, text>()));
  EXPECT_TRUE((t.is<text, identifier>()));
  EXPECT_TRUE((t.is<identifier, text, l_brace>()));
  EXPECT_FALSE((t.is<text, l_brace>()));
  EXPECT_FALSE((t.is<l_brace, r_brace>()));
}

TEST_F(TokenTest, IsAllVariantTypes) {
  // Test that is<> works with all variant member types
  token t1(kw_arrow_double(0, 0, 2));
  EXPECT_TRUE(t1.is<kw_arrow_double>());

  token t2(kw_arrow_single(0, 2, 4));
  EXPECT_TRUE(t2.is<kw_arrow_single>());

  token t3(l_brace(0, 5, 6));
  EXPECT_TRUE(t3.is<l_brace>());

  token t4(r_brace(0, 6, 7));
  EXPECT_TRUE(t4.is<r_brace>());

  token t5(text(1, 0, 5));
  EXPECT_TRUE(t5.is<text>());

  token t6(identifier(1, 6, 11));
  EXPECT_TRUE(t6.is<identifier>());
}

// ============================================================================
// Map Tests (map() method)
// ============================================================================

TEST_F(TokenTest, MapReturnsCorrectType) {
  token t(identifier(0, 0, 4));
  
  // Map should return a size_t pair (start, end)
  auto result = t.map([](const auto& tkn) {
    return tkn.span();
  });
  
  EXPECT_EQ(result.first, 0);
  EXPECT_EQ(result.second, 4);
}

TEST_F(TokenTest, MapPreservesTokenData) {
  token t(text(2, 5, 10));
  
  auto [line, start, end_pos] = t.map([](const auto& tkn) {
    const auto [s, e] = tkn.span();
    return std::make_tuple(tkn.line(), s, e);
  });

  EXPECT_EQ(line, 2);
  EXPECT_EQ(start, 5);
  EXPECT_EQ(end_pos, 10);
}

TEST_F(TokenTest, MapWithDifferentTokenTypes) {
  // Verify map works consistently across different token types
  std::vector<token> tokens = {
    token(identifier(0, 0, 2)),
    token(text(1, 3, 6)),
    token(l_brace(2, 7, 8))
  };

  for (const auto& t : tokens) {
    auto [start, end_pos] = t.map([](const auto& tkn) {
      return tkn.span();
    });
    EXPECT_GE(end_pos, start);  // Ensure end >= start
  }
}

TEST_F(TokenTest, MapLambdaCapture) {
  token t(identifier(0, 5, 9));
  int captured_value = 42;

  auto result = t.map([captured_value](const auto& tkn) {
    auto [start, end_pos] = tkn.span();
    return start + captured_value;
  });

  EXPECT_EQ(result, 47);  // 5 + 42
}

// ============================================================================
// String Extraction Tests (str() method)
// ============================================================================

TEST_F(TokenTest, StrExtractsCorrectSubstring) {
  // Set up content: "line0_content"
  //                  01234567890123
  token t(identifier(0, 0, 6));
  EXPECT_EQ(t.str(text_content), "line0_");
}

TEST_F(TokenTest, StrFromMiddleOfLine) {
  // Extract "content" from "line0_content" starting at position 6
  token t(text(0, 6, 13));
  EXPECT_EQ(t.str(text_content), "content");
}

TEST_F(TokenTest, StrFromDifferentLines) {
  // Test extraction from different lines
  token t1(identifier(0, 0, 5));
  EXPECT_EQ(t1.str(text_content), "line0");

  token t2(text(1, 0, 5));
  EXPECT_EQ(t2.str(text_content), "line1");

  token t3(l_brace(2, 0, 1));  // Single character at position 0
  EXPECT_EQ(t3.str(text_content), "l");
}

TEST_F(TokenTest, StrSingleCharacter) {
  // Extract single character
  token t(l_brace(0, 0, 1));
  EXPECT_EQ(t.str(text_content), "l");
}

TEST_F(TokenTest, StrFullLine) {
  // Extract entire line
  token t(text(1, 0, 13));
  EXPECT_EQ(t.str(text_content), "line1_content");
}

// ============================================================================
// Name Tests (name() method)
// ============================================================================

TEST_F(TokenTest, NameIdentifier) {
  token t(identifier(0, 0, 2));
  EXPECT_EQ(t.name(), "identifier");
}

TEST_F(TokenTest, NameKeywordArrowSingle) {
  token t(kw_arrow_single(0, 0, 2));
  EXPECT_EQ(t.name(), "->");
}

TEST_F(TokenTest, NameKeywordArrowDouble) {
  token t(kw_arrow_double(0, 0, 3));
  EXPECT_EQ(t.name(), "-->");
}

TEST_F(TokenTest, NameLBrace) {
  token t(l_brace(0, 0, 1));
  EXPECT_EQ(t.name(), "{");
}

TEST_F(TokenTest, NameRBrace) {
  token t(r_brace(0, 0, 1));
  EXPECT_EQ(t.name(), "}");
}

TEST_F(TokenTest, NameText) {
  token t(text(0, 0, 5));
  EXPECT_EQ(t.name(), "text");
}

TEST_F(TokenTest, NameAllTokenTypes) {
  // Verify all token types have expected names
  std::vector<std::pair<token, std::string>> name_tests = {
    {token(identifier(0, 0, 1)), "identifier"},
    {token(kw_arrow_single(0, 0, 1)), "->"},
    {token(kw_arrow_double(0, 0, 1)), "-->"},
    {token(l_brace(0, 0, 1)), "{"},
    {token(r_brace(0, 0, 1)), "}"},
    {token(text(0, 0, 1)), "text"}
  };

  for (const auto& [t, expected_name] : name_tests) {
    EXPECT_EQ(t.name(), expected_name);
  }
}

// ============================================================================
// Integration Tests
// ============================================================================

TEST_F(TokenTest, CompleteTokenWorkflow) {
  // Create a token, check type, extract string, and get name
  std::vector<std::string> lines = {"hello world"};
  
  token t(identifier(0, 0, 5));
  
  EXPECT_TRUE(t.is<identifier>());
  EXPECT_EQ(t.str(lines), "hello");
  EXPECT_EQ(t.name(), "identifier");
}

TEST_F(TokenTest, DifferentTokensSameData) {
  // Create different token types with same position data
  std::vector<std::string> lines = {"content"};
  
  token t1(identifier(0, 0, 7));
  token t2(text(0, 0, 7));
  
  // Both extract the same substring
  EXPECT_EQ(t1.str(lines), "content");
  EXPECT_EQ(t2.str(lines), "content");
  
  // But have different names and types
  EXPECT_NE(t1.name(), t2.name());
  EXPECT_TRUE(t1.is<identifier>());
  EXPECT_TRUE(t2.is<text>());
}

TEST_F(TokenTest, TokenSequence) {
  // Test a sequence of tokens
  std::vector<std::string> lines = {"func { body }"};
  
  std::vector<token> tokens = {
    token(identifier(0, 0, 4)),      // "func"
    token(l_brace(0, 5, 6)),         // "{"
    token(identifier(0, 7, 11)),     // "body"
    token(r_brace(0, 12, 13))        // "}"
  };

  EXPECT_EQ(tokens[0].str(lines), "func");
  EXPECT_EQ(tokens[1].str(lines), "{");
  EXPECT_EQ(tokens[2].str(lines), "body");
  EXPECT_EQ(tokens[3].str(lines), "}");

  EXPECT_TRUE(tokens[0].is<identifier>());
  EXPECT_TRUE(tokens[1].is<l_brace>());
  EXPECT_TRUE(tokens[2].is<identifier>());
  EXPECT_TRUE(tokens[3].is<r_brace>());
}

TEST_F(TokenTest, IsAcceptsAnyNumberOfTypes) {
  token t(identifier(0, 0, 1));
  
  // Test with 1 type
  EXPECT_TRUE(t.is<identifier>());
  
  // Test with 2 types
  EXPECT_TRUE((t.is<identifier, text>()));
  
  // Test with 3 types
  EXPECT_TRUE((t.is<identifier, text, l_brace>()));
  
  // Test with 4 types
  EXPECT_TRUE((t.is<identifier, text, l_brace, r_brace>()));
  
  // Test with all variant types
  EXPECT_TRUE((t.is<
    kw_arrow_double,
    kw_arrow_single,
    l_brace,
    r_brace,
    text,
    identifier
  >()));
}

// ============================================================================
// Edge Cases and Special Scenarios
// ============================================================================

TEST_F(TokenTest, ZeroLengthToken) {
  token t(identifier(0, 5, 5));  // Zero-length span (start == end)
  auto [start, end_pos] = t.map([](const auto& tkn) {
    return tkn.span();
  });
  EXPECT_EQ(start, 5);
  EXPECT_EQ(end_pos, 5);
}

TEST_F(TokenTest, LargePositionValues) {
  // Test with large position values
  token t(text(1000, 5000, 5010));
  auto [start, end_pos] = t.map([](const auto& tkn) {
    return tkn.span();
  });
  EXPECT_EQ(start, 5000);
  EXPECT_EQ(end_pos, 5010);
}

TEST_F(TokenTest, MapTypeConversion) {
  token t(identifier(0, 1, 3));
  
  // Map to a different return type
  double result = t.map([](const auto& tkn) -> double {
    auto [start, end_pos] = tkn.span();
    return start * 1.5 + (end_pos - start);
  });
  
  EXPECT_DOUBLE_EQ(result, 3.5);  // 1 * 1.5 + (3 - 1) = 1.5 + 2 = 3.5
}

TEST_F(TokenTest, MapMutableLambda) {
  token t(text(0, 0, 5));
  int counter = 0;
  
  t.map([&counter](const auto& tkn) {
    counter++;
    // Lambda should execute exactly once
  });
  
  EXPECT_EQ(counter, 1);
}
