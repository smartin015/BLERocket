#ifdef STATE_SPIFFS

#include "state_spiffs.h"

void StateSPIFFS::init(std::string savePath, std::string metaPath) {
  this->savePath = savePath;
  this->metaPath = metaPath;
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    ESP_LOGE(STATE_TAG, "SPIFFS Mount Failed; cannot load state");
    return;
  }
}

std::vector<char> readFile(std::string path) {
  File file = SPIFFS.open(path.c_str());
  if(!file || file.isDirectory()){
    ESP_LOGE(STATE_TAG, "failed to open file %s for reading", path.c_str());
    return {};
  }
  std::vector<char> buffer(file.size());
  if (!file.readBytes(buffer.data(), file.size())) {
    ESP_LOGE(STATE_TAG, "Failed to read from path %s", path.c_str());
    return {};
  }
  file.close();
  ESP_LOGI(STATE_TAG, "Loaded from %s", path.c_str());
  return buffer;
}

Engine* StateSPIFFS::load() {
  std::vector<char> stateBuf = readFile(savePath);
  std::vector<char> metaBuf = readFile(metaPath);
  return new Engine(
    (stateBuf.size()) ? game::GetState(stateBuf.data()) : NULL,
    (metaBuf.size()) ? meta::GetData(metaBuf.data()) : NULL);
}

bool StateSPIFFS::save(const Engine* engine) {
  File file = SPIFFS.open(savePath.c_str(), FILE_WRITE);
  if(!file){
    ESP_LOGE(STATE_TAG, "failed to open file %s for writing", savePath.c_str());
    return false;
  }
  flatbuffers::FlatBufferBuilder fbb;
  fbb.Finish(game::State::Pack(fbb, engine->getState(), NULL));
  if(!file.write(fbb.GetBufferPointer(), fbb.GetSize())){
    ESP_LOGE(STATE_TAG, "failed to save game");
  } else {
    ESP_LOGI(STATE_TAG, "game saved");
  }
  file.close();
  return true;
}

#endif // STATE_SPIFFS
