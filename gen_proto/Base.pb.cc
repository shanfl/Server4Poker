// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Base.proto
// Protobuf C++ Version: 5.26.0

#include "Base.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/io/zero_copy_stream_impl_lite.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace Ps {

inline constexpr Pong::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : t1_{::int64_t{0}},
        t2_{::int64_t{0}},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR Pong::Pong(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct PongDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PongDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~PongDefaultTypeInternal() {}
  union {
    Pong _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PongDefaultTypeInternal _Pong_default_instance_;

inline constexpr Ping::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : t1_{::int64_t{0}},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR Ping::Ping(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct PingDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PingDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~PingDefaultTypeInternal() {}
  union {
    Ping _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PingDefaultTypeInternal _Ping_default_instance_;

inline constexpr Hello::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : name_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        servertype_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR Hello::Hello(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct HelloDefaultTypeInternal {
  PROTOBUF_CONSTEXPR HelloDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~HelloDefaultTypeInternal() {}
  union {
    Hello _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 HelloDefaultTypeInternal _Hello_default_instance_;
}  // namespace Ps
namespace Ps {
PROTOBUF_CONSTINIT const uint32_t MSG_ID_internal_data_[] = {
    262144u, 0u, };
bool MSG_ID_IsValid(int value) {
  return 0 <= value && value <= 3;
}
static ::google::protobuf::internal::ExplicitlyConstructed<std::string>
    MSG_ID_strings[4] = {};

static const char MSG_ID_names[] = {
    "ID_0"
    "ID_HELLO"
    "ID_PING"
    "ID_PONG"
};

static const ::google::protobuf::internal::EnumEntry MSG_ID_entries[] =
    {
        {{&MSG_ID_names[0], 4}, 0},
        {{&MSG_ID_names[4], 8}, 1},
        {{&MSG_ID_names[12], 7}, 2},
        {{&MSG_ID_names[19], 7}, 3},
};

static const int MSG_ID_entries_by_number[] = {
    0,  // 0 -> ID_0
    1,  // 1 -> ID_HELLO
    2,  // 2 -> ID_PING
    3,  // 3 -> ID_PONG
};

const std::string& MSG_ID_Name(MSG_ID value) {
  static const bool kDummy =
      ::google::protobuf::internal::InitializeEnumStrings(
          MSG_ID_entries, MSG_ID_entries_by_number,
          4, MSG_ID_strings);
  (void)kDummy;

  int idx = ::google::protobuf::internal::LookUpEnumName(
      MSG_ID_entries, MSG_ID_entries_by_number, 4,
      value);
  return idx == -1 ? ::google::protobuf::internal::GetEmptyString()
                   : MSG_ID_strings[idx].get();
}

bool MSG_ID_Parse(absl::string_view name, MSG_ID* value) {
  int int_value;
  bool success = ::google::protobuf::internal::LookUpEnumValue(
      MSG_ID_entries, 4, name, &int_value);
  if (success) {
    *value = static_cast<MSG_ID>(int_value);
  }
  return success;
}
// ===================================================================

class Hello::_Internal {
 public:
};

Hello::Hello(::google::protobuf::Arena* arena)
    : ::google::protobuf::MessageLite(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:Ps.Hello)
}
inline PROTOBUF_NDEBUG_INLINE Hello::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : name_(arena, from.name_),
        _cached_size_{0} {}

Hello::Hello(
    ::google::protobuf::Arena* arena,
    const Hello& from)
    : ::google::protobuf::MessageLite(arena) {
  Hello* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<std::string>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  _impl_.servertype_ = from._impl_.servertype_;

  // @@protoc_insertion_point(copy_constructor:Ps.Hello)
}
inline PROTOBUF_NDEBUG_INLINE Hello::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : name_(arena),
        _cached_size_{0} {}

inline void Hello::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.servertype_ = {};
}
Hello::~Hello() {
  // @@protoc_insertion_point(destructor:Ps.Hello)
  _internal_metadata_.Delete<std::string>();
  SharedDtor();
}
inline void Hello::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.name_.Destroy();
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
Hello::GetClassData() const {
  struct ClassData_ {
    ::google::protobuf::MessageLite::ClassData header;
    char type_name[9];
  };

  PROTOBUF_CONSTINIT static const ClassData_ _data_ = {
      {
          nullptr,  // OnDemandRegisterArenaDtor
          PROTOBUF_FIELD_OFFSET(Hello, _impl_._cached_size_),
          true,
      },
      "Ps.Hello",
  };

  return &_data_.header;
}
PROTOBUF_NOINLINE void Hello::Clear() {
// @@protoc_insertion_point(message_clear_start:Ps.Hello)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.name_.ClearToEmpty();
  _impl_.servertype_ = 0;
  _internal_metadata_.Clear<std::string>();
}

const char* Hello::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 21, 2> Hello::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_Hello_default_instance_._instance,
    ::_pbi::TcParser::GenericFallbackLite,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::Ps::Hello>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string name = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(Hello, _impl_.name_)}},
    // int32 servertype = 1;
    {::_pbi::TcParser::FastV32S1,
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(Hello, _impl_.servertype_)}},
  }}, {{
    65535, 65535
  }}, {{
    // int32 servertype = 1;
    {PROTOBUF_FIELD_OFFSET(Hello, _impl_.servertype_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // string name = 2;
    {PROTOBUF_FIELD_OFFSET(Hello, _impl_.name_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\10\0\4\0\0\0\0\0"
    "Ps.Hello"
    "name"
  }},
};

::uint8_t* Hello::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Ps.Hello)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // int32 servertype = 1;
  if (this->_internal_servertype() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<1>(
            stream, this->_internal_servertype(), target);
  }

  // string name = 2;
  if (!this->_internal_name().empty()) {
    const std::string& _s = this->_internal_name();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "Ps.Hello.name");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(
        _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Ps.Hello)
  return target;
}

::size_t Hello::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Ps.Hello)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 2;
  if (!this->_internal_name().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_name());
  }

  // int32 servertype = 1;
  if (this->_internal_servertype() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_servertype());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size();
  }
  _impl_._cached_size_.Set(::_pbi::ToCachedSize(total_size));
  return total_size;
}

void Hello::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::_pbi::DownCast<const Hello*>(
      &from));
}

void Hello::MergeFrom(const Hello& from) {
  Hello* const _this = this;
  // @@protoc_insertion_point(class_specific_merge_from_start:Ps.Hello)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_name().empty()) {
    _this->_internal_set_name(from._internal_name());
  }
  if (from._internal_servertype() != 0) {
    _this->_impl_.servertype_ = from._impl_.servertype_;
  }
  _this->_internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
}

void Hello::CopyFrom(const Hello& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Ps.Hello)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool Hello::IsInitialized() const {
  return true;
}

void Hello::InternalSwap(Hello* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.name_, &other->_impl_.name_, arena);
        swap(_impl_.servertype_, other->_impl_.servertype_);
}

// ===================================================================

class Ping::_Internal {
 public:
};

Ping::Ping(::google::protobuf::Arena* arena)
    : ::google::protobuf::MessageLite(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:Ps.Ping)
}
Ping::Ping(
    ::google::protobuf::Arena* arena, const Ping& from)
    : Ping(arena) {
  MergeFrom(from);
}
inline PROTOBUF_NDEBUG_INLINE Ping::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void Ping::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.t1_ = {};
}
Ping::~Ping() {
  // @@protoc_insertion_point(destructor:Ps.Ping)
  _internal_metadata_.Delete<std::string>();
  SharedDtor();
}
inline void Ping::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
Ping::GetClassData() const {
  struct ClassData_ {
    ::google::protobuf::MessageLite::ClassData header;
    char type_name[8];
  };

  PROTOBUF_CONSTINIT static const ClassData_ _data_ = {
      {
          nullptr,  // OnDemandRegisterArenaDtor
          PROTOBUF_FIELD_OFFSET(Ping, _impl_._cached_size_),
          true,
      },
      "Ps.Ping",
  };

  return &_data_.header;
}
PROTOBUF_NOINLINE void Ping::Clear() {
// @@protoc_insertion_point(message_clear_start:Ps.Ping)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.t1_ = ::int64_t{0};
  _internal_metadata_.Clear<std::string>();
}

const char* Ping::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 0, 2> Ping::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_Ping_default_instance_._instance,
    ::_pbi::TcParser::GenericFallbackLite,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::Ps::Ping>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // int64 t1 = 1;
    {::_pbi::TcParser::FastV64S1,
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(Ping, _impl_.t1_)}},
  }}, {{
    65535, 65535
  }}, {{
    // int64 t1 = 1;
    {PROTOBUF_FIELD_OFFSET(Ping, _impl_.t1_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt64)},
  }},
  // no aux_entries
  {{
  }},
};

::uint8_t* Ping::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Ps.Ping)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // int64 t1 = 1;
  if (this->_internal_t1() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt64ToArrayWithField<1>(
            stream, this->_internal_t1(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(
        _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Ps.Ping)
  return target;
}

::size_t Ping::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Ps.Ping)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int64 t1 = 1;
  if (this->_internal_t1() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_t1());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size();
  }
  _impl_._cached_size_.Set(::_pbi::ToCachedSize(total_size));
  return total_size;
}

void Ping::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::_pbi::DownCast<const Ping*>(
      &from));
}

void Ping::MergeFrom(const Ping& from) {
  Ping* const _this = this;
  // @@protoc_insertion_point(class_specific_merge_from_start:Ps.Ping)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_t1() != 0) {
    _this->_impl_.t1_ = from._impl_.t1_;
  }
  _this->_internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
}

void Ping::CopyFrom(const Ping& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Ps.Ping)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool Ping::IsInitialized() const {
  return true;
}

void Ping::InternalSwap(Ping* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
        swap(_impl_.t1_, other->_impl_.t1_);
}

// ===================================================================

class Pong::_Internal {
 public:
};

Pong::Pong(::google::protobuf::Arena* arena)
    : ::google::protobuf::MessageLite(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:Ps.Pong)
}
Pong::Pong(
    ::google::protobuf::Arena* arena, const Pong& from)
    : Pong(arena) {
  MergeFrom(from);
}
inline PROTOBUF_NDEBUG_INLINE Pong::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void Pong::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, t1_),
           0,
           offsetof(Impl_, t2_) -
               offsetof(Impl_, t1_) +
               sizeof(Impl_::t2_));
}
Pong::~Pong() {
  // @@protoc_insertion_point(destructor:Ps.Pong)
  _internal_metadata_.Delete<std::string>();
  SharedDtor();
}
inline void Pong::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
Pong::GetClassData() const {
  struct ClassData_ {
    ::google::protobuf::MessageLite::ClassData header;
    char type_name[8];
  };

  PROTOBUF_CONSTINIT static const ClassData_ _data_ = {
      {
          nullptr,  // OnDemandRegisterArenaDtor
          PROTOBUF_FIELD_OFFSET(Pong, _impl_._cached_size_),
          true,
      },
      "Ps.Pong",
  };

  return &_data_.header;
}
PROTOBUF_NOINLINE void Pong::Clear() {
// @@protoc_insertion_point(message_clear_start:Ps.Pong)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.t1_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.t2_) -
      reinterpret_cast<char*>(&_impl_.t1_)) + sizeof(_impl_.t2_));
  _internal_metadata_.Clear<std::string>();
}

const char* Pong::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 0, 2> Pong::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_Pong_default_instance_._instance,
    ::_pbi::TcParser::GenericFallbackLite,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::Ps::Pong>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // int64 t2 = 2;
    {::_pbi::TcParser::FastV64S1,
     {16, 63, 0, PROTOBUF_FIELD_OFFSET(Pong, _impl_.t2_)}},
    // int64 t1 = 1;
    {::_pbi::TcParser::FastV64S1,
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(Pong, _impl_.t1_)}},
  }}, {{
    65535, 65535
  }}, {{
    // int64 t1 = 1;
    {PROTOBUF_FIELD_OFFSET(Pong, _impl_.t1_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt64)},
    // int64 t2 = 2;
    {PROTOBUF_FIELD_OFFSET(Pong, _impl_.t2_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt64)},
  }},
  // no aux_entries
  {{
  }},
};

::uint8_t* Pong::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Ps.Pong)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // int64 t1 = 1;
  if (this->_internal_t1() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt64ToArrayWithField<1>(
            stream, this->_internal_t1(), target);
  }

  // int64 t2 = 2;
  if (this->_internal_t2() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt64ToArrayWithField<2>(
            stream, this->_internal_t2(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(
        _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Ps.Pong)
  return target;
}

::size_t Pong::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Ps.Pong)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int64 t1 = 1;
  if (this->_internal_t1() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_t1());
  }

  // int64 t2 = 2;
  if (this->_internal_t2() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_t2());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size();
  }
  _impl_._cached_size_.Set(::_pbi::ToCachedSize(total_size));
  return total_size;
}

void Pong::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::_pbi::DownCast<const Pong*>(
      &from));
}

void Pong::MergeFrom(const Pong& from) {
  Pong* const _this = this;
  // @@protoc_insertion_point(class_specific_merge_from_start:Ps.Pong)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_t1() != 0) {
    _this->_impl_.t1_ = from._impl_.t1_;
  }
  if (from._internal_t2() != 0) {
    _this->_impl_.t2_ = from._impl_.t2_;
  }
  _this->_internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
}

void Pong::CopyFrom(const Pong& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Ps.Pong)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool Pong::IsInitialized() const {
  return true;
}

void Pong::InternalSwap(Pong* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Pong, _impl_.t2_)
      + sizeof(Pong::_impl_.t2_)
      - PROTOBUF_FIELD_OFFSET(Pong, _impl_.t1_)>(
          reinterpret_cast<char*>(&_impl_.t1_),
          reinterpret_cast<char*>(&other->_impl_.t1_));
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Ps
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
