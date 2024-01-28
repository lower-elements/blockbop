#include "config.hpp"

#include <SDL.h>
#include <SDL2pp/RWops.hh>
#include <SDL2pp/SDL2pp.hh>
#include <al.h>
#include <alc.h>
#include <cassert>
#include <cstdint>
#include <cstdlib>

#if HAVE_ESPEAK_NG
#include <espeak-ng/espeak_ng.h>
#endif

#include <exception>
#include <fmt/core.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <initializer_list>
#include <memory>
#include <optional>
#include <sndfile.h>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
