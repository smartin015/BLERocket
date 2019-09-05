#ifdef STATE_FS

#include <fstream>
#include <iostream>
#include "state_fs.h"
#include "game_generated.h"

StateFS::StateFS(std::string savePath, std::string metaPath) {
  this->savePath = savePath;
  this->metaPath = metaPath;
}

std::vector<char> readFile(std::string path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    std::cerr << "No save at file " << path << "; starting new game." << std::endl;
    return {};
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<char> buffer(size);
  if (!file.read(buffer.data(), size)) {
    std::cerr << "Failed to read from path " << path << std::endl;
    return {};
  }

  std::cout << "Loaded from " << path << std::endl;
  return buffer;
}

Engine* StateFS::load() {
  std::vector<char> stateBuf = readFile(savePath);
  std::vector<char> metaBuf = readFile(metaPath);
  return new Engine(
    (stateBuf.size()) ? game::GetState(stateBuf.data()) : NULL,
    (metaBuf.size()) ? meta::GetData(metaBuf.data()) : NULL);;
}

bool StateFS::save(const Engine* engine) {
  std::ofstream file(savePath, std::ofstream::binary);
  if (!file.is_open()) {
    std::cerr << "Could not open file " << savePath << " to save state." << std::endl;
    return false;
  }

  flatbuffers::FlatBufferBuilder fbb;
  fbb.Finish(game::State::Pack(fbb, engine->getState(), NULL));
  file.write((const char*) fbb.GetBufferPointer(), fbb.GetSize());
  file.close();
  std::cout << "Saved game state." << std::endl;
}

#endif // STATE_FS
