cmake_minimum_required(VERSION 3.25)

project(LCG)
project(LCG
  VERSION 0.0.2
  DESCRIPTION "LCG 64/128 with all features"
  LANGUAGES CXX
)

add_compile_definitions(funq=auto)

add_executable(lcg main.cpp lcg64.cpp lcg128.cpp)
target_compile_features(lcg PUBLIC cxx_std_23)
