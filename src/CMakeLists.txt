add_executable(periscvcope memory.cc instructions.cc main.cc)

target_include_directories(periscvcope PUBLIC ${CMAKE_SOURCE_DIR}/include )

if (MSVC)
  target_compile_options(periscvcope PRIVATE /W4 /WX)
else()
  target_compile_options(periscvcope PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
