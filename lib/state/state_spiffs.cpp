#ifdef STATE_SPIFFS

#include "state_spiffs.h"

StateSPIFFS::StateSPIFFS(std::string path) {
  this->path = path;
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    std::cerr << "SPIFFS Mount Failed" << std::endl;
    return;
  }
}

Engine StateSPIFFS::load() {
  File file = SPIFFS.open(path.c_str());
  if(!file || file.isDirectory()){
    std::cerr << "failed to open file for reading" << std::endl;
    return Engine();
  }
  std::vector<char> buffer(file.size());
  if (!file.readBytes(buffer.data(), file.size())) {
    std::cerr << "Failed to read from path " << path << std::endl;
    return Engine();
  }
  file.close();
  auto engine = Engine(game::GetState(buffer.data()));
  std::cout << "Loaded game state from " << path << std::endl;
  return engine;
}

bool StateSPIFFS::save(const Engine& engine) {
  File file = SPIFFS.open(path.c_str(), FILE_WRITE);
  if(!file){
    std::cerr << "failed to open file " << path << " for writing" << std::endl;
    return false;
  }
  flatbuffers::FlatBufferBuilder fbb;
  fbb.Finish(game::State::Pack(fbb, engine.getState(), NULL));
  if(!file.write(fbb.GetBufferPointer(), fbb.GetSize())){
    std::cerr << "failed to save game" << std::endl;
  } else {
    std::cout << "game saved" << std::endl;
  }
  file.close();
  return true;
}

#endif // STATE_SPIFFS
