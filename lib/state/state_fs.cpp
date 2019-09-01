#ifdef STATE_FS

#include <fstream>
#include <iostream>
#include "state_fs.h"
#include "game_generated.h"

StateFS::StateFS(std::string path) {
  this->path = path;
}

Engine StateFS::load() {
  std::ifstream file(path, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    std::cerr << "No save at file " << path << "; starting new game." << std::endl;
    return Engine();
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<char> buffer(size);
  if (!file.read(buffer.data(), size)) {
    std::cerr << "Failed to read from path " << path << std::endl;
    return Engine();
  }

  auto engine = Engine(game::GetState(buffer.data()));
  std::cout << "Loaded game state from " << path << std::endl;
  return engine;
}

bool StateFS::save(const Engine& engine) {
  flatbuffers::FlatBufferBuilder fbb;

  std::ofstream file(path, std::ofstream::binary);
  if (!file.is_open()) {
    std::cerr << "Could not open file " << path << " to save state." << std::endl;
    return false;
  }

  fbb.Finish(game::State::Pack(fbb, engine.getState(), NULL));
  file.write((const char*) fbb.GetBufferPointer(), fbb.GetSize());
  file.close();
  std::cout << "Saved game state." << std::endl;
}

#endif // STATE_FS
