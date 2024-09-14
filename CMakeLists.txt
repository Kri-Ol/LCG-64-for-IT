cmake_minimum_required(VERSION 3.25)

project(LCG)
project(LCG
  VERSION 0.0.1
  DESCRIPTION "LCG with all features"
  LANGUAGES CXX
)

add_executable(lcg main.cpp lcg.cpp)
target_compile_features(lcg PUBLIC cxx_std_20)
