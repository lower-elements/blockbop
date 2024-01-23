#ifndef BBENGINE_UTIL_HPP
#define BBENGINE_UTIL_HPP

#include <cstddef>
#include <string>

void setSDLLogPriority();

/**
 * Find the next UTF-8 character in a std::string
 */
std::size_t nextUTF8Character(const std::string &utf8_str,
                              std::size_t current_position);
/**
 * find the previous UTF-8 character in a std::string
 */
std::size_t prevUTF8Character(const std::string &utf8_str,
                              std::size_t current_position);

#endif
