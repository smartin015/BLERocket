#include "comms_base.h"
#include <stdio.h>

#define TYPE_IDX 0

void CommsBase::packMessage(const message::MessageT& msg, adv_packet_t& p) {
  p[0] = msg.oneof.type;
  p[1] = msg.source_user;
  switch (msg.oneof.type) {
    case message::UMessage_status:
      *((game::StatusT*) &p[2]) = *msg.oneof.Asstatus();
      break;
    case message::UMessage_ship:
      {
        auto s = msg.oneof.Asship();
        p[2] = s->action;
        p[3] = s->dest_user;
        p[4] = s->ship->owner;
        sprintf(&(p[5]), "%8s", s->ship->name.c_str());
        // TODO parts:[ShipPart];
      }
      break;
    case message::UMessage_part:
      {
        auto s = msg.oneof.Aspart();
        p[2] = s->action;
        p[3] = s->dest_user;
        p[4] = s->part->type;
        p[5] = s->part->quality;
        p[6] = s->part->creator;
      }
      break;
    default:
      ESP_LOGE(COMMS_TAG, "Could not pack message type %d", uint16_t(p[0]));
  }
}

const message::MessageT CommsBase::unpackMessage(const adv_packet_t& p) {
  message::MessageT result;
  result.source_user = p[1];
  switch ((message::UMessage) p[0]) {
    case message::UMessage_status:
      {
        result.oneof.Set<game::StatusT>(game::StatusT());
        auto s = result.oneof.Asstatus();
        *s = *((game::StatusT*) &p[2]);
      }
      break;
    case message::UMessage_ship:
      {
        result.oneof.Set<message::ShipT>(message::ShipT());
        auto s = result.oneof.Asship();
        s->action = (message::Type) p[2];
        s->dest_user = p[3];
        s->ship.reset(new game::ShipT());
        s->ship->owner = p[4];
        s->ship->name = &(p[5]);
      }
      break;
    case message::UMessage_part:
      {
        result.oneof.Set<message::PartT>(message::PartT());
        auto s = result.oneof.Aspart();
        s->action = (message::Type) p[2];
        s->dest_user = p[3];
        s->part.reset(new game::ShipPartT());
        s->part->type = (game::ShipPartType) p[4];
        s->part->quality = p[5];
        s->part->creator = p[6];
      }
      break;
    default:
      ESP_LOGE(COMMS_TAG, "Could not unpack message type %d", uint16_t(p[0]));
  }
  //message::GetMessage(packet)->UnPackTo(&result, NULL);
  return result;
}

void CommsBase::sendMessage(const message::MessageT& msg, const bool& retryUntilAck) {
  adv_packet_t p;
  packMessage(msg, p);
  sendBytes(p, retryUntilAck);
}

const message::MessageT CommsBase::receiveMessage() {
  int bytes_read = receiveToBuffer();
  if (bytes_read == 0) {
    return message::MessageT();
  }
  if (bytes_read == -1) {
    if (errno != EAGAIN) {
      ESP_LOGE(COMMS_TAG, "Recieve message %d: %s ", errno, strerror(errno));
    }
    return message::MessageT();
  }
  if (bytes_read > MAX_PACKET_SIZE) {
    ESP_LOGE(COMMS_TAG, "Message size exceeds max packet size");
  }

  auto result = unpackMessage(buffer);
  ESP_LOGI(COMMS_TAG, "Got %s message", message::EnumNameUMessage(result.oneof.type));

  // TODO ignore Ship / Part actions not meant for us (dest != user and dest != 0)

  return result;
}
