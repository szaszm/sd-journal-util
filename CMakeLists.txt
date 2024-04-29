cmake_minimum_required(VERSION 3.12.4)
project(sd_journal_cat VERSION 0.0.1)

include(FindPkgConfig)
pkg_search_module(LIBSYSTEMD REQUIRED libsystemd)

find_package(fmt REQUIRED)

add_executable(sd_journal_cat main.cpp)
target_compile_features(sd_journal_cat PUBLIC cxx_std_17)
target_link_libraries(sd_journal_cat PRIVATE fmt::fmt ${LIBSYSTEMD_LIBRARIES})
target_compile_options(sd_journal_cat PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Wall -Wextra -Wpedantic -Walloca -Wcast-qual -Wconversion -Wdate-time>
	$<$<CXX_COMPILER_ID:GNU>:
		-Wformat-overflow -Wnull-dereference -Wimplicit-fallthrough=5 -Wmissing-include-dirs
		-Wswitch-enum -Wstrict-aliasing=1 -Wduplicated-branches -Wduplicated-cond -Wshadow -Wundef -Wcast-align=strict -Wlogical-op -Wmissing-declarations -Wredundant-decls>
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
		-Wabstract-vbase-init -Wanon-enum-enum-conversion -Wassign-enum -Watomic-implicit-seq-cst
		-Wbad-function-cast -Wbitfield-constant-conversion -Wc++11-narrowing -Wcast-align -Wchar-subscripts
		-Wcomma -Wctad-maybe-unsupported -Wdeprecated -Wduplicate-enum -Wfor-loop-analysis -Wformat-type-confusion
		-Wfour-char-constants -Wframe-address -Wgnu -Wheader-hygiene -Widiomatic-parentheses -Wint-in-bool-context
		-Wmicrosoft -Wmost>)
set_property(TARGET sd_journal_cat PROPERTY CXX_EXTENSIONS OFF)
