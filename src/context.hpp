#pragma once

#include <filesystem>
#include <vector>
#include <string>

namespace puml {

class context {
public:
  context(
    const std::filesystem::path& filepath,
    const std::vector<std::string>& lines);

  const std::vector<std::string>& get_text() const;
  const std::string& get_line(std::size_t lineno) const;

private:
  std::filesystem::path m_filepath;
  std::vector<std::string> m_lines;
};

}
