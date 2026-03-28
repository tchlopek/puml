#pragma once

#if defined(PUML_STATIC_BUILD)
#  define PUML_API
#  define PUML_API_LOCAL
#else
#  if defined(PUML_SHARED_BUILD)
#    if defined(_MSC_VER) || defined(__MINGW32__)
#      define PUML_API __declspec(dllexport)
#      define PUML_API_LOCAL
#    elif defined(__GNUC__) || defined(__clang__)
#      define PUML_API __attribute__ ((visibility ("default")))
#      define PUML_API_LOCAL  __attribute__ ((visibility ("hidden")))
#    endif
#  else
#    if defined(_MSC_VER) || defined(__MINGW32__)
#      define PUML_API __declspec(dllimport)
#    elif defined(__GNUC__) || defined(__clang__)
#      define PUML_API __attribute__ ((visibility ("default")))
#      define PUML_API_LOCAL  __attribute__ ((visibility ("hidden")))
#    endif
#  endif
#endif

#if !defined(PUML_API)
#  define PUML_API
#endif

#if !defined(PUML_API_LOCAL)
#  define PUML_API_LOCAL
#endif
