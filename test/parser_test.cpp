#include "context.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <token/tokenizer.hpp>
#include <token/range/range.hpp>
#include <token/range/view.hpp>
#include <token/token.hpp>

#include <cst/parser.hpp>
#include <builder.hpp>

#include <puml/puml.hpp>

#include "diagram_matchers.hpp"

static puml::context make_ctx(const std::vector<std::string>& lines) {
  return puml::context{ "", lines };
}

TEST(ParserTest, SimpleState) {
  std::string str = "foo : asdasd";

  auto diagram = puml::parse(str);

  EXPECT_THAT(diagram, HasNoErrors());
  EXPECT_THAT(diagram, IsValid());
  EXPECT_THAT(diagram, HasStateWithName("foo"));
  EXPECT_THAT(diagram, HasStateCount(1));
}

TEST(ParserTest, ScopedState) {
  std::string str = R"a(
    state foo {
      state bar {}
    }

    foo: test
  )a";

  auto diagram = puml::parse(str);
}

TEST(ParserTest, InitTransition) {
  std::string str = "[*] -> qwe";

  auto diagram = puml::parse(str);

  EXPECT_THAT(diagram, HasNoErrors());
  EXPECT_THAT(diagram, IsValid());
  EXPECT_THAT(diagram, HasStateWithName("qwe"));
  EXPECT_THAT(diagram, HasStateCount(1));
  EXPECT_THAT(diagram, HasInitialTransitionTo("qwe"));
}

TEST(ParserTest, SimpleTransition) {
  std::string str = "asd -> qwe";

  auto diagram = puml::parse(str);

  EXPECT_THAT(diagram, HasNoErrors());
  EXPECT_THAT(diagram, IsValid());
  EXPECT_THAT(diagram, HasStateWithName("asd"));
  EXPECT_THAT(diagram, HasStateWithName("qwe"));
  EXPECT_THAT(diagram, HasStateCount(2));
  EXPECT_THAT(diagram, HasTransitionBetween("asd", "qwe"));
}

TEST(ParserTest, SimpleTransitionWithText) {
  std::string str = "asd -> qwe : text 123";

  auto diagram = puml::parse(str);

  EXPECT_THAT(diagram, HasNoErrors());
  EXPECT_THAT(diagram, IsValid());
  EXPECT_THAT(diagram, HasStateWithName("asd"));
  EXPECT_THAT(diagram, HasStateWithName("qwe"));
  EXPECT_THAT(diagram, HasStateCount(2));
  EXPECT_THAT(diagram, HasTransition("asd", "qwe", "text 123"));
}


TEST(ParserTest, ScopedStateWithTransitionInside) {
  std::string str = R"a(
[*] --> NotShooting

state NotShooting {
  [*] --> Idle
  Idle --> Configuring : EvConfig
  Configuring --> Idle : EvConfig
}

state Configuring {
  [*] --> NewValueSelection
  NewValueSelection --> NewValuePreview : EvNewValue
  NewValuePreview --> NewValueSelection : EvNewValueRejected
  NewValuePreview --> NewValueSelection : EvNewValueSaved

  state NewValuePreview {
     State1 -> State2
  }

}
  )a";

  auto diagram = puml::parse(str);
}
