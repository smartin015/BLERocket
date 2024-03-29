// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_GAME_GAME_H_
#define FLATBUFFERS_GENERATED_GAME_GAME_H_

#include "flatbuffers/flatbuffers.h"

#include "nav_generated.h"

namespace game {

struct ShipPart;
struct ShipPartT;

struct Ship;
struct ShipT;

struct Phase;
struct PhaseT;

struct Status;
struct StatusT;

struct State;
struct StateT;

enum ShipPartType {
  ShipPartType_unknown = 0,
  ShipPartType_hull = 1,
  ShipPartType_thruster = 2,
  ShipPartType_cargo = 3,
  ShipPartType_sensors = 4,
  ShipPartType_MIN = ShipPartType_unknown,
  ShipPartType_MAX = ShipPartType_sensors
};

inline const ShipPartType (&EnumValuesShipPartType())[5] {
  static const ShipPartType values[] = {
    ShipPartType_unknown,
    ShipPartType_hull,
    ShipPartType_thruster,
    ShipPartType_cargo,
    ShipPartType_sensors
  };
  return values;
}

inline const char * const *EnumNamesShipPartType() {
  static const char * const names[] = {
    "unknown",
    "hull",
    "thruster",
    "cargo",
    "sensors",
    nullptr
  };
  return names;
}

inline const char *EnumNameShipPartType(ShipPartType e) {
  if (e < ShipPartType_unknown || e > ShipPartType_sensors) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesShipPartType()[index];
}

struct ShipPartT : public flatbuffers::NativeTable {
  typedef ShipPart TableType;
  ShipPartType type;
  uint8_t quality;
  uint8_t creator;
  ShipPartT()
      : type(ShipPartType_unknown),
        quality(0),
        creator(0) {
  }
};

struct ShipPart FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ShipPartT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_QUALITY = 6,
    VT_CREATOR = 8
  };
  ShipPartType type() const {
    return static_cast<ShipPartType>(GetField<int8_t>(VT_TYPE, 0));
  }
  uint8_t quality() const {
    return GetField<uint8_t>(VT_QUALITY, 0);
  }
  uint8_t creator() const {
    return GetField<uint8_t>(VT_CREATOR, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           VerifyField<uint8_t>(verifier, VT_QUALITY) &&
           VerifyField<uint8_t>(verifier, VT_CREATOR) &&
           verifier.EndTable();
  }
  ShipPartT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ShipPartT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<ShipPart> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ShipPartT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ShipPartBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(ShipPartType type) {
    fbb_.AddElement<int8_t>(ShipPart::VT_TYPE, static_cast<int8_t>(type), 0);
  }
  void add_quality(uint8_t quality) {
    fbb_.AddElement<uint8_t>(ShipPart::VT_QUALITY, quality, 0);
  }
  void add_creator(uint8_t creator) {
    fbb_.AddElement<uint8_t>(ShipPart::VT_CREATOR, creator, 0);
  }
  explicit ShipPartBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShipPartBuilder &operator=(const ShipPartBuilder &);
  flatbuffers::Offset<ShipPart> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ShipPart>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShipPart> CreateShipPart(
    flatbuffers::FlatBufferBuilder &_fbb,
    ShipPartType type = ShipPartType_unknown,
    uint8_t quality = 0,
    uint8_t creator = 0) {
  ShipPartBuilder builder_(_fbb);
  builder_.add_creator(creator);
  builder_.add_quality(quality);
  builder_.add_type(type);
  return builder_.Finish();
}

flatbuffers::Offset<ShipPart> CreateShipPart(flatbuffers::FlatBufferBuilder &_fbb, const ShipPartT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct ShipT : public flatbuffers::NativeTable {
  typedef Ship TableType;
  std::string name;
  std::vector<std::unique_ptr<ShipPartT>> parts;
  uint8_t owner;
  ShipT()
      : owner(0) {
  }
};

struct Ship FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ShipT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_PARTS = 6,
    VT_OWNER = 8
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::Vector<flatbuffers::Offset<ShipPart>> *parts() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<ShipPart>> *>(VT_PARTS);
  }
  uint8_t owner() const {
    return GetField<uint8_t>(VT_OWNER, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_PARTS) &&
           verifier.VerifyVector(parts()) &&
           verifier.VerifyVectorOfTables(parts()) &&
           VerifyField<uint8_t>(verifier, VT_OWNER) &&
           verifier.EndTable();
  }
  ShipT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ShipT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Ship> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ShipT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ShipBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Ship::VT_NAME, name);
  }
  void add_parts(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ShipPart>>> parts) {
    fbb_.AddOffset(Ship::VT_PARTS, parts);
  }
  void add_owner(uint8_t owner) {
    fbb_.AddElement<uint8_t>(Ship::VT_OWNER, owner, 0);
  }
  explicit ShipBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShipBuilder &operator=(const ShipBuilder &);
  flatbuffers::Offset<Ship> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Ship>(end);
    return o;
  }
};

inline flatbuffers::Offset<Ship> CreateShip(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ShipPart>>> parts = 0,
    uint8_t owner = 0) {
  ShipBuilder builder_(_fbb);
  builder_.add_parts(parts);
  builder_.add_name(name);
  builder_.add_owner(owner);
  return builder_.Finish();
}

inline flatbuffers::Offset<Ship> CreateShipDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const std::vector<flatbuffers::Offset<ShipPart>> *parts = nullptr,
    uint8_t owner = 0) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto parts__ = parts ? _fbb.CreateVector<flatbuffers::Offset<ShipPart>>(*parts) : 0;
  return game::CreateShip(
      _fbb,
      name__,
      parts__,
      owner);
}

flatbuffers::Offset<Ship> CreateShip(flatbuffers::FlatBufferBuilder &_fbb, const ShipT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct PhaseT : public flatbuffers::NativeTable {
  typedef Phase TableType;
  uint8_t id;
  uint8_t txn;
  PhaseT()
      : id(0),
        txn(0) {
  }
};

struct Phase FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PhaseT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ID = 4,
    VT_TXN = 6
  };
  uint8_t id() const {
    return GetField<uint8_t>(VT_ID, 0);
  }
  uint8_t txn() const {
    return GetField<uint8_t>(VT_TXN, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_ID) &&
           VerifyField<uint8_t>(verifier, VT_TXN) &&
           verifier.EndTable();
  }
  PhaseT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(PhaseT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Phase> Pack(flatbuffers::FlatBufferBuilder &_fbb, const PhaseT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct PhaseBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(uint8_t id) {
    fbb_.AddElement<uint8_t>(Phase::VT_ID, id, 0);
  }
  void add_txn(uint8_t txn) {
    fbb_.AddElement<uint8_t>(Phase::VT_TXN, txn, 0);
  }
  explicit PhaseBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PhaseBuilder &operator=(const PhaseBuilder &);
  flatbuffers::Offset<Phase> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Phase>(end);
    return o;
  }
};

inline flatbuffers::Offset<Phase> CreatePhase(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t id = 0,
    uint8_t txn = 0) {
  PhaseBuilder builder_(_fbb);
  builder_.add_txn(txn);
  builder_.add_id(id);
  return builder_.Finish();
}

flatbuffers::Offset<Phase> CreatePhase(flatbuffers::FlatBufferBuilder &_fbb, const PhaseT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct StatusT : public flatbuffers::NativeTable {
  typedef Status TableType;
  uint8_t firmwareVersion;
  uint8_t user;
  uint8_t phase_id;
  uint8_t phase_txn;
  uint64_t score;
  StatusT()
      : firmwareVersion(0),
        user(0),
        phase_id(0),
        phase_txn(0),
        score(0) {
  }
};

struct Status FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef StatusT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_FIRMWAREVERSION = 4,
    VT_USER = 6,
    VT_PHASE_ID = 8,
    VT_PHASE_TXN = 10,
    VT_SCORE = 12
  };
  uint8_t firmwareVersion() const {
    return GetField<uint8_t>(VT_FIRMWAREVERSION, 0);
  }
  uint8_t user() const {
    return GetField<uint8_t>(VT_USER, 0);
  }
  uint8_t phase_id() const {
    return GetField<uint8_t>(VT_PHASE_ID, 0);
  }
  uint8_t phase_txn() const {
    return GetField<uint8_t>(VT_PHASE_TXN, 0);
  }
  uint64_t score() const {
    return GetField<uint64_t>(VT_SCORE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_FIRMWAREVERSION) &&
           VerifyField<uint8_t>(verifier, VT_USER) &&
           VerifyField<uint8_t>(verifier, VT_PHASE_ID) &&
           VerifyField<uint8_t>(verifier, VT_PHASE_TXN) &&
           VerifyField<uint64_t>(verifier, VT_SCORE) &&
           verifier.EndTable();
  }
  StatusT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(StatusT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Status> Pack(flatbuffers::FlatBufferBuilder &_fbb, const StatusT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct StatusBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_firmwareVersion(uint8_t firmwareVersion) {
    fbb_.AddElement<uint8_t>(Status::VT_FIRMWAREVERSION, firmwareVersion, 0);
  }
  void add_user(uint8_t user) {
    fbb_.AddElement<uint8_t>(Status::VT_USER, user, 0);
  }
  void add_phase_id(uint8_t phase_id) {
    fbb_.AddElement<uint8_t>(Status::VT_PHASE_ID, phase_id, 0);
  }
  void add_phase_txn(uint8_t phase_txn) {
    fbb_.AddElement<uint8_t>(Status::VT_PHASE_TXN, phase_txn, 0);
  }
  void add_score(uint64_t score) {
    fbb_.AddElement<uint64_t>(Status::VT_SCORE, score, 0);
  }
  explicit StatusBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  StatusBuilder &operator=(const StatusBuilder &);
  flatbuffers::Offset<Status> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Status>(end);
    return o;
  }
};

inline flatbuffers::Offset<Status> CreateStatus(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t firmwareVersion = 0,
    uint8_t user = 0,
    uint8_t phase_id = 0,
    uint8_t phase_txn = 0,
    uint64_t score = 0) {
  StatusBuilder builder_(_fbb);
  builder_.add_score(score);
  builder_.add_phase_txn(phase_txn);
  builder_.add_phase_id(phase_id);
  builder_.add_user(user);
  builder_.add_firmwareVersion(firmwareVersion);
  return builder_.Finish();
}

flatbuffers::Offset<Status> CreateStatus(flatbuffers::FlatBufferBuilder &_fbb, const StatusT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct StateT : public flatbuffers::NativeTable {
  typedef State TableType;
  nav::Page page;
  std::vector<std::unique_ptr<ShipPartT>> parts;
  std::vector<std::unique_ptr<ShipT>> ships;
  uint8_t selectedShip;
  uint8_t selectedUser;
  uint8_t charIdx;
  std::unique_ptr<StatusT> status;
  StateT()
      : page(nav::Page_main),
        selectedShip(0),
        selectedUser(0),
        charIdx(0) {
  }
};

struct State FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef StateT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PAGE = 4,
    VT_PARTS = 6,
    VT_SHIPS = 8,
    VT_SELECTEDSHIP = 10,
    VT_SELECTEDUSER = 12,
    VT_CHARIDX = 14,
    VT_STATUS = 16
  };
  nav::Page page() const {
    return static_cast<nav::Page>(GetField<int8_t>(VT_PAGE, 0));
  }
  const flatbuffers::Vector<flatbuffers::Offset<ShipPart>> *parts() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<ShipPart>> *>(VT_PARTS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Ship>> *ships() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Ship>> *>(VT_SHIPS);
  }
  uint8_t selectedShip() const {
    return GetField<uint8_t>(VT_SELECTEDSHIP, 0);
  }
  uint8_t selectedUser() const {
    return GetField<uint8_t>(VT_SELECTEDUSER, 0);
  }
  uint8_t charIdx() const {
    return GetField<uint8_t>(VT_CHARIDX, 0);
  }
  const Status *status() const {
    return GetPointer<const Status *>(VT_STATUS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_PAGE) &&
           VerifyOffset(verifier, VT_PARTS) &&
           verifier.VerifyVector(parts()) &&
           verifier.VerifyVectorOfTables(parts()) &&
           VerifyOffset(verifier, VT_SHIPS) &&
           verifier.VerifyVector(ships()) &&
           verifier.VerifyVectorOfTables(ships()) &&
           VerifyField<uint8_t>(verifier, VT_SELECTEDSHIP) &&
           VerifyField<uint8_t>(verifier, VT_SELECTEDUSER) &&
           VerifyField<uint8_t>(verifier, VT_CHARIDX) &&
           VerifyOffset(verifier, VT_STATUS) &&
           verifier.VerifyTable(status()) &&
           verifier.EndTable();
  }
  StateT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(StateT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<State> Pack(flatbuffers::FlatBufferBuilder &_fbb, const StateT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct StateBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_page(nav::Page page) {
    fbb_.AddElement<int8_t>(State::VT_PAGE, static_cast<int8_t>(page), 0);
  }
  void add_parts(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ShipPart>>> parts) {
    fbb_.AddOffset(State::VT_PARTS, parts);
  }
  void add_ships(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Ship>>> ships) {
    fbb_.AddOffset(State::VT_SHIPS, ships);
  }
  void add_selectedShip(uint8_t selectedShip) {
    fbb_.AddElement<uint8_t>(State::VT_SELECTEDSHIP, selectedShip, 0);
  }
  void add_selectedUser(uint8_t selectedUser) {
    fbb_.AddElement<uint8_t>(State::VT_SELECTEDUSER, selectedUser, 0);
  }
  void add_charIdx(uint8_t charIdx) {
    fbb_.AddElement<uint8_t>(State::VT_CHARIDX, charIdx, 0);
  }
  void add_status(flatbuffers::Offset<Status> status) {
    fbb_.AddOffset(State::VT_STATUS, status);
  }
  explicit StateBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  StateBuilder &operator=(const StateBuilder &);
  flatbuffers::Offset<State> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<State>(end);
    return o;
  }
};

inline flatbuffers::Offset<State> CreateState(
    flatbuffers::FlatBufferBuilder &_fbb,
    nav::Page page = nav::Page_main,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ShipPart>>> parts = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Ship>>> ships = 0,
    uint8_t selectedShip = 0,
    uint8_t selectedUser = 0,
    uint8_t charIdx = 0,
    flatbuffers::Offset<Status> status = 0) {
  StateBuilder builder_(_fbb);
  builder_.add_status(status);
  builder_.add_ships(ships);
  builder_.add_parts(parts);
  builder_.add_charIdx(charIdx);
  builder_.add_selectedUser(selectedUser);
  builder_.add_selectedShip(selectedShip);
  builder_.add_page(page);
  return builder_.Finish();
}

inline flatbuffers::Offset<State> CreateStateDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    nav::Page page = nav::Page_main,
    const std::vector<flatbuffers::Offset<ShipPart>> *parts = nullptr,
    const std::vector<flatbuffers::Offset<Ship>> *ships = nullptr,
    uint8_t selectedShip = 0,
    uint8_t selectedUser = 0,
    uint8_t charIdx = 0,
    flatbuffers::Offset<Status> status = 0) {
  auto parts__ = parts ? _fbb.CreateVector<flatbuffers::Offset<ShipPart>>(*parts) : 0;
  auto ships__ = ships ? _fbb.CreateVector<flatbuffers::Offset<Ship>>(*ships) : 0;
  return game::CreateState(
      _fbb,
      page,
      parts__,
      ships__,
      selectedShip,
      selectedUser,
      charIdx,
      status);
}

flatbuffers::Offset<State> CreateState(flatbuffers::FlatBufferBuilder &_fbb, const StateT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ShipPartT *ShipPart::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new ShipPartT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void ShipPart::UnPackTo(ShipPartT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = type(); _o->type = _e; };
  { auto _e = quality(); _o->quality = _e; };
  { auto _e = creator(); _o->creator = _e; };
}

inline flatbuffers::Offset<ShipPart> ShipPart::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ShipPartT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateShipPart(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<ShipPart> CreateShipPart(flatbuffers::FlatBufferBuilder &_fbb, const ShipPartT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ShipPartT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _type = _o->type;
  auto _quality = _o->quality;
  auto _creator = _o->creator;
  return game::CreateShipPart(
      _fbb,
      _type,
      _quality,
      _creator);
}

inline ShipT *Ship::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new ShipT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Ship::UnPackTo(ShipT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = name(); if (_e) _o->name = _e->str(); };
  { auto _e = parts(); if (_e) { _o->parts.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->parts[_i] = std::unique_ptr<ShipPartT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = owner(); _o->owner = _e; };
}

inline flatbuffers::Offset<Ship> Ship::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ShipT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateShip(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Ship> CreateShip(flatbuffers::FlatBufferBuilder &_fbb, const ShipT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ShipT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  auto _parts = _o->parts.size() ? _fbb.CreateVector<flatbuffers::Offset<ShipPart>> (_o->parts.size(), [](size_t i, _VectorArgs *__va) { return CreateShipPart(*__va->__fbb, __va->__o->parts[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _owner = _o->owner;
  return game::CreateShip(
      _fbb,
      _name,
      _parts,
      _owner);
}

inline PhaseT *Phase::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new PhaseT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Phase::UnPackTo(PhaseT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = id(); _o->id = _e; };
  { auto _e = txn(); _o->txn = _e; };
}

inline flatbuffers::Offset<Phase> Phase::Pack(flatbuffers::FlatBufferBuilder &_fbb, const PhaseT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreatePhase(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Phase> CreatePhase(flatbuffers::FlatBufferBuilder &_fbb, const PhaseT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const PhaseT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _id = _o->id;
  auto _txn = _o->txn;
  return game::CreatePhase(
      _fbb,
      _id,
      _txn);
}

inline StatusT *Status::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new StatusT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Status::UnPackTo(StatusT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = firmwareVersion(); _o->firmwareVersion = _e; };
  { auto _e = user(); _o->user = _e; };
  { auto _e = phase_id(); _o->phase_id = _e; };
  { auto _e = phase_txn(); _o->phase_txn = _e; };
  { auto _e = score(); _o->score = _e; };
}

inline flatbuffers::Offset<Status> Status::Pack(flatbuffers::FlatBufferBuilder &_fbb, const StatusT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateStatus(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Status> CreateStatus(flatbuffers::FlatBufferBuilder &_fbb, const StatusT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const StatusT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _firmwareVersion = _o->firmwareVersion;
  auto _user = _o->user;
  auto _phase_id = _o->phase_id;
  auto _phase_txn = _o->phase_txn;
  auto _score = _o->score;
  return game::CreateStatus(
      _fbb,
      _firmwareVersion,
      _user,
      _phase_id,
      _phase_txn,
      _score);
}

inline StateT *State::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new StateT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void State::UnPackTo(StateT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = page(); _o->page = _e; };
  { auto _e = parts(); if (_e) { _o->parts.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->parts[_i] = std::unique_ptr<ShipPartT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = ships(); if (_e) { _o->ships.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->ships[_i] = std::unique_ptr<ShipT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = selectedShip(); _o->selectedShip = _e; };
  { auto _e = selectedUser(); _o->selectedUser = _e; };
  { auto _e = charIdx(); _o->charIdx = _e; };
  { auto _e = status(); if (_e) _o->status = std::unique_ptr<StatusT>(_e->UnPack(_resolver)); };
}

inline flatbuffers::Offset<State> State::Pack(flatbuffers::FlatBufferBuilder &_fbb, const StateT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateState(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<State> CreateState(flatbuffers::FlatBufferBuilder &_fbb, const StateT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const StateT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _page = _o->page;
  auto _parts = _o->parts.size() ? _fbb.CreateVector<flatbuffers::Offset<ShipPart>> (_o->parts.size(), [](size_t i, _VectorArgs *__va) { return CreateShipPart(*__va->__fbb, __va->__o->parts[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _ships = _o->ships.size() ? _fbb.CreateVector<flatbuffers::Offset<Ship>> (_o->ships.size(), [](size_t i, _VectorArgs *__va) { return CreateShip(*__va->__fbb, __va->__o->ships[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _selectedShip = _o->selectedShip;
  auto _selectedUser = _o->selectedUser;
  auto _charIdx = _o->charIdx;
  auto _status = _o->status ? CreateStatus(_fbb, _o->status.get(), _rehasher) : 0;
  return game::CreateState(
      _fbb,
      _page,
      _parts,
      _ships,
      _selectedShip,
      _selectedUser,
      _charIdx,
      _status);
}

inline const game::State *GetState(const void *buf) {
  return flatbuffers::GetRoot<game::State>(buf);
}

inline const game::State *GetSizePrefixedState(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<game::State>(buf);
}

inline bool VerifyStateBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<game::State>(nullptr);
}

inline bool VerifySizePrefixedStateBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<game::State>(nullptr);
}

inline void FinishStateBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<game::State> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedStateBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<game::State> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<StateT> UnPackState(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<StateT>(GetState(buf)->UnPack(res));
}

}  // namespace game

#endif  // FLATBUFFERS_GENERATED_GAME_GAME_H_
