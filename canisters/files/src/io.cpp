#include "io.h"
#include "utils.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

#include "ic_api.h"

void write_read(IC_API &ic_api) {
  std::string filename = "internal_data_file";

  // Open an ofstream
  std::ofstream of_stream;
  std::string msg;
  std::ios_base::openmode mode = std::ios::binary | std::ios::trunc;
  if (!open_ofstream(filename, mode, of_stream, msg)) {
    ic_api.to_wire(CandidTypeVariant{
        "Err", CandidTypeVariant{"Other", CandidTypeText{std::string(__func__) +
                                                         ": " + msg}}});
    return;
  }

  // Write a header
  std::string header = "_data_";
  of_stream.write(header.c_str(), header.size());

  // Write some data
  std::vector<std::string> data{"Hello ", "from the ", "internal data file!"};
  // Write the length of the string
  for (const auto &str : data) {
    // Write the length of the string
    size_t length = str.size();
    of_stream.write(reinterpret_cast<const char *>(&length), sizeof(length));
    // Write the string itself
    of_stream.write(str.c_str(), str.size());
  }

  of_stream.close();

  // -------------------------------------------------------------------
  // Read it back from the file, to check it all worked

  // Open an ifstream
  std::ifstream if_stream;
  if (!open_ifstream(filename, std::ios::binary, if_stream, msg)) {
    ic_api.to_wire(CandidTypeVariant{
        "Err", CandidTypeVariant{"Other", CandidTypeText{std::string(__func__) +
                                                         ": " + msg}}});
    return;
  }

  // Read the header
  header.clear();
  header.resize(6);
  if_stream.read(&header[0], 6);

  // Read the data
  data.clear();
  while (if_stream) {
    size_t length;
    // Read the length of the string
    if_stream.read(reinterpret_cast<char *>(&length), sizeof(length));
    if (!if_stream) break;

    // Read the string itself
    std::string str(length, '\0');
    if_stream.read(&str[0], length);
    if (!if_stream) break;

    data.push_back(str);
  }

  if_stream.close();

  // print it to the dfx canister console
  std::cout << "Content read back from file " << filename << ": " << std::endl;
  std::cout << "Header  : " << header << std::endl;
  std::cout << "Data    : ";
  for (const auto &str : data) {
    std::cout << str;
  }
  std::cout << std::endl;

  // Return the content over the wire
  CandidTypeRecord r_out;
  r_out.append("header", CandidTypeText{header});
  r_out.append("data", CandidTypeVecText{data});
  ic_api.to_wire(CandidTypeVariant{"Ok", CandidTypeRecord{r_out}});
}

void write_read_during_query() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  write_read(ic_api);
}

void write_read_during_update() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  write_read(ic_api);
}
