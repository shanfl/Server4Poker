// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BaseMsg.proto

#include "BaseMsg.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace Base {
class BaseMsgDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BaseMsg> _instance;
} _BaseMsg_default_instance_;
class TimerEventDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<TimerEvent> _instance;
} _TimerEvent_default_instance_;
}  // namespace Base
static void InitDefaultsscc_info_BaseMsg_BaseMsg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Base::_BaseMsg_default_instance_;
    new (ptr) ::Base::BaseMsg();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BaseMsg_BaseMsg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BaseMsg_BaseMsg_2eproto}, {}};

static void InitDefaultsscc_info_TimerEvent_BaseMsg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Base::_TimerEvent_default_instance_;
    new (ptr) ::Base::TimerEvent();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_TimerEvent_BaseMsg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_TimerEvent_BaseMsg_2eproto}, {}};

namespace Base {
bool ServerType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

static ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<std::string> ServerType_strings[4] = {};

static const char ServerType_names[] =
  "ST_CLIENT"
  "ST_GAME"
  "ST_GATE"
  "ST_NONE";

static const ::PROTOBUF_NAMESPACE_ID::internal::EnumEntry ServerType_entries[] = {
  { {ServerType_names + 0, 9}, 1 },
  { {ServerType_names + 9, 7}, 3 },
  { {ServerType_names + 16, 7}, 2 },
  { {ServerType_names + 23, 7}, 0 },
};

static const int ServerType_entries_by_number[] = {
  3, // 0 -> ST_NONE
  0, // 1 -> ST_CLIENT
  2, // 2 -> ST_GATE
  1, // 3 -> ST_GAME
};

const std::string& ServerType_Name(
    ServerType value) {
  static const bool dummy =
      ::PROTOBUF_NAMESPACE_ID::internal::InitializeEnumStrings(
          ServerType_entries,
          ServerType_entries_by_number,
          4, ServerType_strings);
  (void) dummy;
  int idx = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumName(
      ServerType_entries,
      ServerType_entries_by_number,
      4, value);
  return idx == -1 ? ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString() :
                     ServerType_strings[idx].get();
}
bool ServerType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ServerType* value) {
  int int_value;
  bool success = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumValue(
      ServerType_entries, 4, name, &int_value);
  if (success) {
    *value = static_cast<ServerType>(int_value);
  }
  return success;
}
bool TimerOpcode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

static ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<std::string> TimerOpcode_strings[5] = {};

static const char TimerOpcode_names[] =
  "TM_ADD"
  "TM_DEL"
  "TM_DEL_ALL"
  "TM_NONE"
  "TM_TICK";

static const ::PROTOBUF_NAMESPACE_ID::internal::EnumEntry TimerOpcode_entries[] = {
  { {TimerOpcode_names + 0, 6}, 1 },
  { {TimerOpcode_names + 6, 6}, 2 },
  { {TimerOpcode_names + 12, 10}, 3 },
  { {TimerOpcode_names + 22, 7}, 0 },
  { {TimerOpcode_names + 29, 7}, 4 },
};

static const int TimerOpcode_entries_by_number[] = {
  3, // 0 -> TM_NONE
  0, // 1 -> TM_ADD
  1, // 2 -> TM_DEL
  2, // 3 -> TM_DEL_ALL
  4, // 4 -> TM_TICK
};

const std::string& TimerOpcode_Name(
    TimerOpcode value) {
  static const bool dummy =
      ::PROTOBUF_NAMESPACE_ID::internal::InitializeEnumStrings(
          TimerOpcode_entries,
          TimerOpcode_entries_by_number,
          5, TimerOpcode_strings);
  (void) dummy;
  int idx = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumName(
      TimerOpcode_entries,
      TimerOpcode_entries_by_number,
      5, value);
  return idx == -1 ? ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString() :
                     TimerOpcode_strings[idx].get();
}
bool TimerOpcode_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, TimerOpcode* value) {
  int int_value;
  bool success = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumValue(
      TimerOpcode_entries, 5, name, &int_value);
  if (success) {
    *value = static_cast<TimerOpcode>(int_value);
  }
  return success;
}

// ===================================================================

class BaseMsg::_Internal {
 public:
};

BaseMsg::BaseMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Base.BaseMsg)
}
BaseMsg::BaseMsg(const BaseMsg& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite() {
  _internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
  msg_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_msg().empty()) {
    msg_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_msg(), 
      GetArena());
  }
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&verison_) -
    reinterpret_cast<char*>(&id_)) + sizeof(verison_));
  // @@protoc_insertion_point(copy_constructor:Base.BaseMsg)
}

void BaseMsg::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BaseMsg_BaseMsg_2eproto.base);
  msg_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
      reinterpret_cast<char*>(&id_) - reinterpret_cast<char*>(this)),
      0, static_cast<size_t>(reinterpret_cast<char*>(&verison_) -
      reinterpret_cast<char*>(&id_)) + sizeof(verison_));
}

BaseMsg::~BaseMsg() {
  // @@protoc_insertion_point(destructor:Base.BaseMsg)
  SharedDtor();
  _internal_metadata_.Delete<std::string>();
}

void BaseMsg::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  msg_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void BaseMsg::ArenaDtor(void* object) {
  BaseMsg* _this = reinterpret_cast< BaseMsg* >(object);
  (void)_this;
}
void BaseMsg::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void BaseMsg::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const BaseMsg& BaseMsg::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BaseMsg_BaseMsg_2eproto.base);
  return *internal_default_instance();
}


void BaseMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:Base.BaseMsg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  msg_.ClearToEmpty();
  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&verison_) -
      reinterpret_cast<char*>(&id_)) + sizeof(verison_));
  _internal_metadata_.Clear<std::string>();
}

const char* BaseMsg::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 verison = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          verison_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int64 id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string msg = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_msg();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, nullptr));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<std::string>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* BaseMsg::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Base.BaseMsg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 verison = 1;
  if (this->verison() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_verison(), target);
  }

  // int64 id = 2;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(2, this->_internal_id(), target);
  }

  // string msg = 3;
  if (this->msg().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_msg().data(), static_cast<int>(this->_internal_msg().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Base.BaseMsg.msg");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_msg(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(_internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Base.BaseMsg)
  return target;
}

size_t BaseMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Base.BaseMsg)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string msg = 3;
  if (this->msg().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_msg());
  }

  // int64 id = 2;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_id());
  }

  // int32 verison = 1;
  if (this->verison() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_verison());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).size();
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void BaseMsg::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const BaseMsg*>(
      &from));
}

void BaseMsg::MergeFrom(const BaseMsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Base.BaseMsg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.msg().size() > 0) {
    _internal_set_msg(from._internal_msg());
  }
  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.verison() != 0) {
    _internal_set_verison(from._internal_verison());
  }
}

void BaseMsg::CopyFrom(const BaseMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Base.BaseMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BaseMsg::IsInitialized() const {
  return true;
}

void BaseMsg::InternalSwap(BaseMsg* other) {
  using std::swap;
  _internal_metadata_.Swap<std::string>(&other->_internal_metadata_);
  msg_.Swap(&other->msg_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(BaseMsg, verison_)
      + sizeof(BaseMsg::verison_)
      - PROTOBUF_FIELD_OFFSET(BaseMsg, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

std::string BaseMsg::GetTypeName() const {
  return "Base.BaseMsg";
}


// ===================================================================

class TimerEvent::_Internal {
 public:
};

TimerEvent::TimerEvent(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Base.TimerEvent)
}
TimerEvent::TimerEvent(const TimerEvent& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite() {
  _internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
  ::memcpy(&code_, &from.code_,
    static_cast<size_t>(reinterpret_cast<char*>(&repeat_) -
    reinterpret_cast<char*>(&code_)) + sizeof(repeat_));
  // @@protoc_insertion_point(copy_constructor:Base.TimerEvent)
}

void TimerEvent::SharedCtor() {
  ::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
      reinterpret_cast<char*>(&code_) - reinterpret_cast<char*>(this)),
      0, static_cast<size_t>(reinterpret_cast<char*>(&repeat_) -
      reinterpret_cast<char*>(&code_)) + sizeof(repeat_));
}

TimerEvent::~TimerEvent() {
  // @@protoc_insertion_point(destructor:Base.TimerEvent)
  SharedDtor();
  _internal_metadata_.Delete<std::string>();
}

void TimerEvent::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void TimerEvent::ArenaDtor(void* object) {
  TimerEvent* _this = reinterpret_cast< TimerEvent* >(object);
  (void)_this;
}
void TimerEvent::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void TimerEvent::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const TimerEvent& TimerEvent::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_TimerEvent_BaseMsg_2eproto.base);
  return *internal_default_instance();
}


void TimerEvent::Clear() {
// @@protoc_insertion_point(message_clear_start:Base.TimerEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&code_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&repeat_) -
      reinterpret_cast<char*>(&code_)) + sizeof(repeat_));
  _internal_metadata_.Clear<std::string>();
}

const char* TimerEvent::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .Base.TimerOpcode code = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_code(static_cast<::Base::TimerOpcode>(val));
        } else goto handle_unusual;
        continue;
      // int32 id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 delay = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          delay_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 repeat = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          repeat_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<std::string>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* TimerEvent::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Base.TimerEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .Base.TimerOpcode code = 1;
  if (this->code() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_code(), target);
  }

  // int32 id = 2;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_id(), target);
  }

  // int32 delay = 3;
  if (this->delay() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_delay(), target);
  }

  // int32 repeat = 4;
  if (this->repeat() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_repeat(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(_internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Base.TimerEvent)
  return target;
}

size_t TimerEvent::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Base.TimerEvent)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .Base.TimerOpcode code = 1;
  if (this->code() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_code());
  }

  // int32 id = 2;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_id());
  }

  // int32 delay = 3;
  if (this->delay() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_delay());
  }

  // int32 repeat = 4;
  if (this->repeat() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_repeat());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).size();
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void TimerEvent::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const TimerEvent*>(
      &from));
}

void TimerEvent::MergeFrom(const TimerEvent& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Base.TimerEvent)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.code() != 0) {
    _internal_set_code(from._internal_code());
  }
  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.delay() != 0) {
    _internal_set_delay(from._internal_delay());
  }
  if (from.repeat() != 0) {
    _internal_set_repeat(from._internal_repeat());
  }
}

void TimerEvent::CopyFrom(const TimerEvent& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Base.TimerEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TimerEvent::IsInitialized() const {
  return true;
}

void TimerEvent::InternalSwap(TimerEvent* other) {
  using std::swap;
  _internal_metadata_.Swap<std::string>(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(TimerEvent, repeat_)
      + sizeof(TimerEvent::repeat_)
      - PROTOBUF_FIELD_OFFSET(TimerEvent, code_)>(
          reinterpret_cast<char*>(&code_),
          reinterpret_cast<char*>(&other->code_));
}

std::string TimerEvent::GetTypeName() const {
  return "Base.TimerEvent";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Base
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Base::BaseMsg* Arena::CreateMaybeMessage< ::Base::BaseMsg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Base::BaseMsg >(arena);
}
template<> PROTOBUF_NOINLINE ::Base::TimerEvent* Arena::CreateMaybeMessage< ::Base::TimerEvent >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Base::TimerEvent >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
