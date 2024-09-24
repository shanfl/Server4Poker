// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Core.proto
// Protobuf C++ Version: 5.26.0

#include "Core.pb.h"

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

inline constexpr ProtoMsgWrapper::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : cookie_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        msg_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        id_{0},
        zipped_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR ProtoMsgWrapper::ProtoMsgWrapper(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct ProtoMsgWrapperDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ProtoMsgWrapperDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ProtoMsgWrapperDefaultTypeInternal() {}
  union {
    ProtoMsgWrapper _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ProtoMsgWrapperDefaultTypeInternal _ProtoMsgWrapper_default_instance_;
}  // namespace Ps
namespace Ps {
// ===================================================================

class ProtoMsgWrapper::_Internal {
 public:
};

ProtoMsgWrapper::ProtoMsgWrapper(::google::protobuf::Arena* arena)
    : ::google::protobuf::MessageLite(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:Ps.ProtoMsgWrapper)
}
inline PROTOBUF_NDEBUG_INLINE ProtoMsgWrapper::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : cookie_(arena, from.cookie_),
        msg_(arena, from.msg_),
        _cached_size_{0} {}

ProtoMsgWrapper::ProtoMsgWrapper(
    ::google::protobuf::Arena* arena,
    const ProtoMsgWrapper& from)
    : ::google::protobuf::MessageLite(arena) {
  ProtoMsgWrapper* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<std::string>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, id_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, id_),
           offsetof(Impl_, zipped_) -
               offsetof(Impl_, id_) +
               sizeof(Impl_::zipped_));

  // @@protoc_insertion_point(copy_constructor:Ps.ProtoMsgWrapper)
}
inline PROTOBUF_NDEBUG_INLINE ProtoMsgWrapper::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : cookie_(arena),
        msg_(arena),
        _cached_size_{0} {}

inline void ProtoMsgWrapper::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, id_),
           0,
           offsetof(Impl_, zipped_) -
               offsetof(Impl_, id_) +
               sizeof(Impl_::zipped_));
}
ProtoMsgWrapper::~ProtoMsgWrapper() {
  // @@protoc_insertion_point(destructor:Ps.ProtoMsgWrapper)
  _internal_metadata_.Delete<std::string>();
  SharedDtor();
}
inline void ProtoMsgWrapper::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.cookie_.Destroy();
  _impl_.msg_.Destroy();
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
ProtoMsgWrapper::GetClassData() const {
  struct ClassData_ {
    ::google::protobuf::MessageLite::ClassData header;
    char type_name[19];
  };

  PROTOBUF_CONSTINIT static const ClassData_ _data_ = {
      {
          nullptr,  // OnDemandRegisterArenaDtor
          PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_._cached_size_),
          true,
      },
      "Ps.ProtoMsgWrapper",
  };

  return &_data_.header;
}
PROTOBUF_NOINLINE void ProtoMsgWrapper::Clear() {
// @@protoc_insertion_point(message_clear_start:Ps.ProtoMsgWrapper)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.cookie_.ClearToEmpty();
  _impl_.msg_.ClearToEmpty();
  ::memset(&_impl_.id_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.zipped_) -
      reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.zipped_));
  _internal_metadata_.Clear<std::string>();
}

const char* ProtoMsgWrapper::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 4, 0, 36, 2> ProtoMsgWrapper::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    4, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967280,  // skipmap
    offsetof(decltype(_table_), field_entries),
    4,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_ProtoMsgWrapper_default_instance_._instance,
    ::_pbi::TcParser::GenericFallbackLite,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::Ps::ProtoMsgWrapper>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string msg = 4;
    {::_pbi::TcParser::FastUS1,
     {34, 63, 0, PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.msg_)}},
    // int32 id = 1;
    {::_pbi::TcParser::FastV32S1,
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.id_)}},
    // int32 zipped = 2;
    {::_pbi::TcParser::FastV32S1,
     {16, 63, 0, PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.zipped_)}},
    // string cookie = 3;
    {::_pbi::TcParser::FastUS1,
     {26, 63, 0, PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.cookie_)}},
  }}, {{
    65535, 65535
  }}, {{
    // int32 id = 1;
    {PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.id_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // int32 zipped = 2;
    {PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.zipped_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // string cookie = 3;
    {PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.cookie_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string msg = 4;
    {PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.msg_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\22\0\0\6\3\0\0\0"
    "Ps.ProtoMsgWrapper"
    "cookie"
    "msg"
  }},
};

::uint8_t* ProtoMsgWrapper::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Ps.ProtoMsgWrapper)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // int32 id = 1;
  if (this->_internal_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<1>(
            stream, this->_internal_id(), target);
  }

  // int32 zipped = 2;
  if (this->_internal_zipped() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<2>(
            stream, this->_internal_zipped(), target);
  }

  // string cookie = 3;
  if (!this->_internal_cookie().empty()) {
    const std::string& _s = this->_internal_cookie();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "Ps.ProtoMsgWrapper.cookie");
    target = stream->WriteStringMaybeAliased(3, _s, target);
  }

  // string msg = 4;
  if (!this->_internal_msg().empty()) {
    const std::string& _s = this->_internal_msg();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "Ps.ProtoMsgWrapper.msg");
    target = stream->WriteStringMaybeAliased(4, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(
        _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Ps.ProtoMsgWrapper)
  return target;
}

::size_t ProtoMsgWrapper::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Ps.ProtoMsgWrapper)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string cookie = 3;
  if (!this->_internal_cookie().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_cookie());
  }

  // string msg = 4;
  if (!this->_internal_msg().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_msg());
  }

  // int32 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_id());
  }

  // int32 zipped = 2;
  if (this->_internal_zipped() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_zipped());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size();
  }
  _impl_._cached_size_.Set(::_pbi::ToCachedSize(total_size));
  return total_size;
}

void ProtoMsgWrapper::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::_pbi::DownCast<const ProtoMsgWrapper*>(
      &from));
}

void ProtoMsgWrapper::MergeFrom(const ProtoMsgWrapper& from) {
  ProtoMsgWrapper* const _this = this;
  // @@protoc_insertion_point(class_specific_merge_from_start:Ps.ProtoMsgWrapper)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_cookie().empty()) {
    _this->_internal_set_cookie(from._internal_cookie());
  }
  if (!from._internal_msg().empty()) {
    _this->_internal_set_msg(from._internal_msg());
  }
  if (from._internal_id() != 0) {
    _this->_impl_.id_ = from._impl_.id_;
  }
  if (from._internal_zipped() != 0) {
    _this->_impl_.zipped_ = from._impl_.zipped_;
  }
  _this->_internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
}

void ProtoMsgWrapper::CopyFrom(const ProtoMsgWrapper& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Ps.ProtoMsgWrapper)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool ProtoMsgWrapper::IsInitialized() const {
  return true;
}

void ProtoMsgWrapper::InternalSwap(ProtoMsgWrapper* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.cookie_, &other->_impl_.cookie_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.msg_, &other->_impl_.msg_, arena);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.zipped_)
      + sizeof(ProtoMsgWrapper::_impl_.zipped_)
      - PROTOBUF_FIELD_OFFSET(ProtoMsgWrapper, _impl_.id_)>(
          reinterpret_cast<char*>(&_impl_.id_),
          reinterpret_cast<char*>(&other->_impl_.id_));
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Ps
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
