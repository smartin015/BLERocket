#ifdef STATE_SPIFFS

#include "state_spiffs.h"

void StateSPIFFS::init(std::string savePath, std::string metaPath) {
  this->savePath = savePath;
  this->metaPath = metaPath;
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    std::cerr << "SPIFFS Mount Failed" << std::endl;
    return;
  }
}

std::vector<char> readFile(std::string path) {
  File file = SPIFFS.open(path.c_str());
  if(!file || file.isDirectory()){
    std::cerr << "failed to open file for reading" << std::endl;
    return {};
  }
  std::vector<char> buffer(file.size());
  if (!file.readBytes(buffer.data(), file.size())) {
    std::cerr << "Failed to read from path " << path << std::endl;
    return {};
  }
  file.close();
  std::cout << "Loaded from " << path << std::endl;
  return buffer;
}

Engine* StateSPIFFS::load() {
  std::vector<char> stateBuf = readFile(savePath);
  std::vector<char> metaBuf = readFile(metaPath);
  return new Engine(
    (stateBuf.size()) ? game::GetState(stateBuf.data()) : NULL,
    (metaBuf.size()) ? meta::GetData(metaBuf.data()) : NULL);
}

bool StateSPIFFS::save(const Engine& engine) {
  File file = SPIFFS.open(savePath.c_str(), FILE_WRITE);
  if(!file){
    std::cerr << "failed to open file " << savePath << " for writing" << std::endl;
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
