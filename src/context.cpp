#include "context.hpp"

namespace puml {

context::context(
  const std::filesystem::path& filepath,
  const std::vector<std::string>& lines
) : m_filepath{ filepath }
  , m_lines{ lines }
{}

const std::vector<std::string>& context::get_text() const {
  return m_lines;
}

const std::string& context::get_line(std::size_t lineno) const {
  return m_lines[lineno];
}

}
