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
    ESP_LOGE(FS_TAG, "No save at file %s; starting new game.", path.c_str());
    return {};
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<char> buffer(size);
  if (!file.read(buffer.data(), size)) {
    ESP_LOGE(FS_TAG, "Failed to read from path %s", path.c_str());
    return {};
  }

  ESP_LOGI(FS_TAG, "Loaded from %s", path.c_str());
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
    ESP_LOGE(FS_TAG, "Could not open file %s to save state", savePath.c_str());
    return false;
  }

  flatbuffers::FlatBufferBuilder fbb;
  fbb.Finish(game::State::Pack(fbb, engine->getState(), NULL));
  file.write((const char*) fbb.GetBufferPointer(), fbb.GetSize());
  file.close();
  ESP_LOGI(FS_TAG, "Saved game state");
}

#endif // STATE_FS
