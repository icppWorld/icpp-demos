#include "utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

#include "ic_api.h"

bool open_ifstream(const std::string &filename,
                   const std::ios_base::openmode &mode,
                   std::ifstream &if_stream, std::string &msg) {
  if_stream.open(filename.c_str(), mode);
  if (!if_stream.is_open()) {
    msg = "ERROR: failed to open ifstream for file " + filename;
    return false;
  }
  return true;
}

bool open_ofstream(const std::string &filename,
                   const std::ios_base::openmode &mode,
                   std::ofstream &of_stream, std::string &msg) {
  of_stream.open(filename.c_str(), mode);
  if (!of_stream.is_open()) {
    msg = "ERROR: failed to open ofstream for file " + filename;
    return false;
  }
  return true;
}

std::ofstream open_ofstream_or_trap(std::string filename,
                                    std::ios_base::openmode mode) {
  std::ofstream of_stream;
  of_stream.open(filename.c_str(), mode);
  if (!of_stream.is_open()) {
    std::string msg = std::string(__func__) +
                      ": failed to open ofstream for file " + filename;
    IC_API::trap(msg);
  }
  return of_stream;
}

std::ifstream open_ifstream_or_trap(std::string filename,
                                    std::ios_base::openmode mode) {
  std::ifstream if_stream;
  if_stream.open(filename.c_str(), mode);
  if (!if_stream.is_open()) {
    std::string msg = std::string(__func__) +
                      ": failed to open ifstream for file " + filename;
    IC_API::trap(msg);
  }
  return if_stream;
}
