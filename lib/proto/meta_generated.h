// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_META_META_H_
#define FLATBUFFERS_GENERATED_META_META_H_

#include "flatbuffers/flatbuffers.h"

namespace meta {

struct User;
struct UserT;

struct Scenario;
struct ScenarioT;

struct Choice;
struct ChoiceT;

struct Data;
struct DataT;

enum Alignment {
  Alignment_neutral = 0,
  Alignment_good = 1,
  Alignment_evil = 2,
  Alignment_MIN = Alignment_neutral,
  Alignment_MAX = Alignment_evil
};

inline const Alignment (&EnumValuesAlignment())[3] {
  static const Alignment values[] = {
    Alignment_neutral,
    Alignment_good,
    Alignment_evil
  };
  return values;
}

inline const char * const *EnumNamesAlignment() {
  static const char * const names[] = {
    "neutral",
    "good",
    "evil",
    nullptr
  };
  return names;
}

inline const char *EnumNameAlignment(Alignment e) {
  if (e < Alignment_neutral || e > Alignment_evil) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesAlignment()[index];
}

struct UserT : public flatbuffers::NativeTable {
  typedef User TableType;
  std::string firstname;
  std::string lastname;
  std::string username;
  std::string site;
  UserT() {
  }
};

struct User FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UserT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_FIRSTNAME = 4,
    VT_LASTNAME = 6,
    VT_USERNAME = 8,
    VT_SITE = 10
  };
  const flatbuffers::String *firstname() const {
    return GetPointer<const flatbuffers::String *>(VT_FIRSTNAME);
  }
  const flatbuffers::String *lastname() const {
    return GetPointer<const flatbuffers::String *>(VT_LASTNAME);
  }
  const flatbuffers::String *username() const {
    return GetPointer<const flatbuffers::String *>(VT_USERNAME);
  }
  const flatbuffers::String *site() const {
    return GetPointer<const flatbuffers::String *>(VT_SITE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_FIRSTNAME) &&
           verifier.VerifyString(firstname()) &&
           VerifyOffset(verifier, VT_LASTNAME) &&
           verifier.VerifyString(lastname()) &&
           VerifyOffset(verifier, VT_USERNAME) &&
           verifier.VerifyString(username()) &&
           VerifyOffset(verifier, VT_SITE) &&
           verifier.VerifyString(site()) &&
           verifier.EndTable();
  }
  UserT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(UserT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<User> Pack(flatbuffers::FlatBufferBuilder &_fbb, const UserT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct UserBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_firstname(flatbuffers::Offset<flatbuffers::String> firstname) {
    fbb_.AddOffset(User::VT_FIRSTNAME, firstname);
  }
  void add_lastname(flatbuffers::Offset<flatbuffers::String> lastname) {
    fbb_.AddOffset(User::VT_LASTNAME, lastname);
  }
  void add_username(flatbuffers::Offset<flatbuffers::String> username) {
    fbb_.AddOffset(User::VT_USERNAME, username);
  }
  void add_site(flatbuffers::Offset<flatbuffers::String> site) {
    fbb_.AddOffset(User::VT_SITE, site);
  }
  explicit UserBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UserBuilder &operator=(const UserBuilder &);
  flatbuffers::Offset<User> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<User>(end);
    return o;
  }
};

inline flatbuffers::Offset<User> CreateUser(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> firstname = 0,
    flatbuffers::Offset<flatbuffers::String> lastname = 0,
    flatbuffers::Offset<flatbuffers::String> username = 0,
    flatbuffers::Offset<flatbuffers::String> site = 0) {
  UserBuilder builder_(_fbb);
  builder_.add_site(site);
  builder_.add_username(username);
  builder_.add_lastname(lastname);
  builder_.add_firstname(firstname);
  return builder_.Finish();
}

inline flatbuffers::Offset<User> CreateUserDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *firstname = nullptr,
    const char *lastname = nullptr,
    const char *username = nullptr,
    const char *site = nullptr) {
  auto firstname__ = firstname ? _fbb.CreateString(firstname) : 0;
  auto lastname__ = lastname ? _fbb.CreateString(lastname) : 0;
  auto username__ = username ? _fbb.CreateString(username) : 0;
  auto site__ = site ? _fbb.CreateString(site) : 0;
  return meta::CreateUser(
      _fbb,
      firstname__,
      lastname__,
      username__,
      site__);
}

flatbuffers::Offset<User> CreateUser(flatbuffers::FlatBufferBuilder &_fbb, const UserT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct ScenarioT : public flatbuffers::NativeTable {
  typedef Scenario TableType;
  std::string desc;
  std::vector<std::unique_ptr<ChoiceT>> choices;
  ScenarioT() {
  }
};

struct Scenario FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ScenarioT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_DESC = 4,
    VT_CHOICES = 6
  };
  const flatbuffers::String *desc() const {
    return GetPointer<const flatbuffers::String *>(VT_DESC);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Choice>> *choices() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Choice>> *>(VT_CHOICES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_DESC) &&
           verifier.VerifyString(desc()) &&
           VerifyOffset(verifier, VT_CHOICES) &&
           verifier.VerifyVector(choices()) &&
           verifier.VerifyVectorOfTables(choices()) &&
           verifier.EndTable();
  }
  ScenarioT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ScenarioT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Scenario> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ScenarioT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ScenarioBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_desc(flatbuffers::Offset<flatbuffers::String> desc) {
    fbb_.AddOffset(Scenario::VT_DESC, desc);
  }
  void add_choices(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Choice>>> choices) {
    fbb_.AddOffset(Scenario::VT_CHOICES, choices);
  }
  explicit ScenarioBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ScenarioBuilder &operator=(const ScenarioBuilder &);
  flatbuffers::Offset<Scenario> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Scenario>(end);
    return o;
  }
};

inline flatbuffers::Offset<Scenario> CreateScenario(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> desc = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Choice>>> choices = 0) {
  ScenarioBuilder builder_(_fbb);
  builder_.add_choices(choices);
  builder_.add_desc(desc);
  return builder_.Finish();
}

inline flatbuffers::Offset<Scenario> CreateScenarioDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *desc = nullptr,
    const std::vector<flatbuffers::Offset<Choice>> *choices = nullptr) {
  auto desc__ = desc ? _fbb.CreateString(desc) : 0;
  auto choices__ = choices ? _fbb.CreateVector<flatbuffers::Offset<Choice>>(*choices) : 0;
  return meta::CreateScenario(
      _fbb,
      desc__,
      choices__);
}

flatbuffers::Offset<Scenario> CreateScenario(flatbuffers::FlatBufferBuilder &_fbb, const ScenarioT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct ChoiceT : public flatbuffers::NativeTable {
  typedef Choice TableType;
  std::string action;
  Alignment alignment;
  uint8_t risk;
  std::string success;
  std::string failure;
  ChoiceT()
      : alignment(Alignment_neutral),
        risk(0) {
  }
};

struct Choice FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ChoiceT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ACTION = 4,
    VT_ALIGNMENT = 6,
    VT_RISK = 8,
    VT_SUCCESS = 10,
    VT_FAILURE = 12
  };
  const flatbuffers::String *action() const {
    return GetPointer<const flatbuffers::String *>(VT_ACTION);
  }
  Alignment alignment() const {
    return static_cast<Alignment>(GetField<int8_t>(VT_ALIGNMENT, 0));
  }
  uint8_t risk() const {
    return GetField<uint8_t>(VT_RISK, 0);
  }
  const flatbuffers::String *success() const {
    return GetPointer<const flatbuffers::String *>(VT_SUCCESS);
  }
  const flatbuffers::String *failure() const {
    return GetPointer<const flatbuffers::String *>(VT_FAILURE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ACTION) &&
           verifier.VerifyString(action()) &&
           VerifyField<int8_t>(verifier, VT_ALIGNMENT) &&
           VerifyField<uint8_t>(verifier, VT_RISK) &&
           VerifyOffset(verifier, VT_SUCCESS) &&
           verifier.VerifyString(success()) &&
           VerifyOffset(verifier, VT_FAILURE) &&
           verifier.VerifyString(failure()) &&
           verifier.EndTable();
  }
  ChoiceT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ChoiceT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Choice> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ChoiceT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ChoiceBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_action(flatbuffers::Offset<flatbuffers::String> action) {
    fbb_.AddOffset(Choice::VT_ACTION, action);
  }
  void add_alignment(Alignment alignment) {
    fbb_.AddElement<int8_t>(Choice::VT_ALIGNMENT, static_cast<int8_t>(alignment), 0);
  }
  void add_risk(uint8_t risk) {
    fbb_.AddElement<uint8_t>(Choice::VT_RISK, risk, 0);
  }
  void add_success(flatbuffers::Offset<flatbuffers::String> success) {
    fbb_.AddOffset(Choice::VT_SUCCESS, success);
  }
  void add_failure(flatbuffers::Offset<flatbuffers::String> failure) {
    fbb_.AddOffset(Choice::VT_FAILURE, failure);
  }
  explicit ChoiceBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ChoiceBuilder &operator=(const ChoiceBuilder &);
  flatbuffers::Offset<Choice> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Choice>(end);
    return o;
  }
};

inline flatbuffers::Offset<Choice> CreateChoice(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> action = 0,
    Alignment alignment = Alignment_neutral,
    uint8_t risk = 0,
    flatbuffers::Offset<flatbuffers::String> success = 0,
    flatbuffers::Offset<flatbuffers::String> failure = 0) {
  ChoiceBuilder builder_(_fbb);
  builder_.add_failure(failure);
  builder_.add_success(success);
  builder_.add_action(action);
  builder_.add_risk(risk);
  builder_.add_alignment(alignment);
  return builder_.Finish();
}

inline flatbuffers::Offset<Choice> CreateChoiceDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *action = nullptr,
    Alignment alignment = Alignment_neutral,
    uint8_t risk = 0,
    const char *success = nullptr,
    const char *failure = nullptr) {
  auto action__ = action ? _fbb.CreateString(action) : 0;
  auto success__ = success ? _fbb.CreateString(success) : 0;
  auto failure__ = failure ? _fbb.CreateString(failure) : 0;
  return meta::CreateChoice(
      _fbb,
      action__,
      alignment,
      risk,
      success__,
      failure__);
}

flatbuffers::Offset<Choice> CreateChoice(flatbuffers::FlatBufferBuilder &_fbb, const ChoiceT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct DataT : public flatbuffers::NativeTable {
  typedef Data TableType;
  std::vector<std::unique_ptr<UserT>> users;
  std::vector<std::unique_ptr<ScenarioT>> scenarios;
  DataT() {
  }
};

struct Data FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef DataT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_USERS = 4,
    VT_SCENARIOS = 6
  };
  const flatbuffers::Vector<flatbuffers::Offset<User>> *users() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<User>> *>(VT_USERS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Scenario>> *scenarios() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Scenario>> *>(VT_SCENARIOS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_USERS) &&
           verifier.VerifyVector(users()) &&
           verifier.VerifyVectorOfTables(users()) &&
           VerifyOffset(verifier, VT_SCENARIOS) &&
           verifier.VerifyVector(scenarios()) &&
           verifier.VerifyVectorOfTables(scenarios()) &&
           verifier.EndTable();
  }
  DataT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(DataT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Data> Pack(flatbuffers::FlatBufferBuilder &_fbb, const DataT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct DataBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_users(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<User>>> users) {
    fbb_.AddOffset(Data::VT_USERS, users);
  }
  void add_scenarios(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Scenario>>> scenarios) {
    fbb_.AddOffset(Data::VT_SCENARIOS, scenarios);
  }
  explicit DataBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  DataBuilder &operator=(const DataBuilder &);
  flatbuffers::Offset<Data> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Data>(end);
    return o;
  }
};

inline flatbuffers::Offset<Data> CreateData(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<User>>> users = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Scenario>>> scenarios = 0) {
  DataBuilder builder_(_fbb);
  builder_.add_scenarios(scenarios);
  builder_.add_users(users);
  return builder_.Finish();
}

inline flatbuffers::Offset<Data> CreateDataDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<User>> *users = nullptr,
    const std::vector<flatbuffers::Offset<Scenario>> *scenarios = nullptr) {
  auto users__ = users ? _fbb.CreateVector<flatbuffers::Offset<User>>(*users) : 0;
  auto scenarios__ = scenarios ? _fbb.CreateVector<flatbuffers::Offset<Scenario>>(*scenarios) : 0;
  return meta::CreateData(
      _fbb,
      users__,
      scenarios__);
}

flatbuffers::Offset<Data> CreateData(flatbuffers::FlatBufferBuilder &_fbb, const DataT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline UserT *User::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new UserT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void User::UnPackTo(UserT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = firstname(); if (_e) _o->firstname = _e->str(); };
  { auto _e = lastname(); if (_e) _o->lastname = _e->str(); };
  { auto _e = username(); if (_e) _o->username = _e->str(); };
  { auto _e = site(); if (_e) _o->site = _e->str(); };
}

inline flatbuffers::Offset<User> User::Pack(flatbuffers::FlatBufferBuilder &_fbb, const UserT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateUser(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<User> CreateUser(flatbuffers::FlatBufferBuilder &_fbb, const UserT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const UserT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _firstname = _o->firstname.empty() ? 0 : _fbb.CreateString(_o->firstname);
  auto _lastname = _o->lastname.empty() ? 0 : _fbb.CreateString(_o->lastname);
  auto _username = _o->username.empty() ? 0 : _fbb.CreateString(_o->username);
  auto _site = _o->site.empty() ? 0 : _fbb.CreateString(_o->site);
  return meta::CreateUser(
      _fbb,
      _firstname,
      _lastname,
      _username,
      _site);
}

inline ScenarioT *Scenario::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new ScenarioT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Scenario::UnPackTo(ScenarioT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = desc(); if (_e) _o->desc = _e->str(); };
  { auto _e = choices(); if (_e) { _o->choices.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->choices[_i] = std::unique_ptr<ChoiceT>(_e->Get(_i)->UnPack(_resolver)); } } };
}

inline flatbuffers::Offset<Scenario> Scenario::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ScenarioT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateScenario(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Scenario> CreateScenario(flatbuffers::FlatBufferBuilder &_fbb, const ScenarioT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ScenarioT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _desc = _o->desc.empty() ? 0 : _fbb.CreateString(_o->desc);
  auto _choices = _o->choices.size() ? _fbb.CreateVector<flatbuffers::Offset<Choice>> (_o->choices.size(), [](size_t i, _VectorArgs *__va) { return CreateChoice(*__va->__fbb, __va->__o->choices[i].get(), __va->__rehasher); }, &_va ) : 0;
  return meta::CreateScenario(
      _fbb,
      _desc,
      _choices);
}

inline ChoiceT *Choice::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new ChoiceT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Choice::UnPackTo(ChoiceT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = action(); if (_e) _o->action = _e->str(); };
  { auto _e = alignment(); _o->alignment = _e; };
  { auto _e = risk(); _o->risk = _e; };
  { auto _e = success(); if (_e) _o->success = _e->str(); };
  { auto _e = failure(); if (_e) _o->failure = _e->str(); };
}

inline flatbuffers::Offset<Choice> Choice::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ChoiceT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateChoice(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Choice> CreateChoice(flatbuffers::FlatBufferBuilder &_fbb, const ChoiceT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ChoiceT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _action = _o->action.empty() ? 0 : _fbb.CreateString(_o->action);
  auto _alignment = _o->alignment;
  auto _risk = _o->risk;
  auto _success = _o->success.empty() ? 0 : _fbb.CreateString(_o->success);
  auto _failure = _o->failure.empty() ? 0 : _fbb.CreateString(_o->failure);
  return meta::CreateChoice(
      _fbb,
      _action,
      _alignment,
      _risk,
      _success,
      _failure);
}

inline DataT *Data::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new DataT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Data::UnPackTo(DataT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = users(); if (_e) { _o->users.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->users[_i] = std::unique_ptr<UserT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = scenarios(); if (_e) { _o->scenarios.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->scenarios[_i] = std::unique_ptr<ScenarioT>(_e->Get(_i)->UnPack(_resolver)); } } };
}

inline flatbuffers::Offset<Data> Data::Pack(flatbuffers::FlatBufferBuilder &_fbb, const DataT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateData(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Data> CreateData(flatbuffers::FlatBufferBuilder &_fbb, const DataT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const DataT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _users = _o->users.size() ? _fbb.CreateVector<flatbuffers::Offset<User>> (_o->users.size(), [](size_t i, _VectorArgs *__va) { return CreateUser(*__va->__fbb, __va->__o->users[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _scenarios = _o->scenarios.size() ? _fbb.CreateVector<flatbuffers::Offset<Scenario>> (_o->scenarios.size(), [](size_t i, _VectorArgs *__va) { return CreateScenario(*__va->__fbb, __va->__o->scenarios[i].get(), __va->__rehasher); }, &_va ) : 0;
  return meta::CreateData(
      _fbb,
      _users,
      _scenarios);
}

inline const meta::Data *GetData(const void *buf) {
  return flatbuffers::GetRoot<meta::Data>(buf);
}

inline const meta::Data *GetSizePrefixedData(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<meta::Data>(buf);
}

inline bool VerifyDataBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<meta::Data>(nullptr);
}

inline bool VerifySizePrefixedDataBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<meta::Data>(nullptr);
}

inline void FinishDataBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<meta::Data> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedDataBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<meta::Data> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<DataT> UnPackData(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<DataT>(GetData(buf)->UnPack(res));
}

}  // namespace meta

#endif  // FLATBUFFERS_GENERATED_META_META_H_
