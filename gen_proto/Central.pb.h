// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Central.proto
// Protobuf C++ Version: 5.26.0

#ifndef GOOGLE_PROTOBUF_INCLUDED_Central_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_Central_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION != 5026000
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/generated_enum_util.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_Central_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_Central_2eproto {
  static const ::uint32_t offsets[];
};
namespace Ps {
class CentralHeartBeat;
struct CentralHeartBeatDefaultTypeInternal;
extern CentralHeartBeatDefaultTypeInternal _CentralHeartBeat_default_instance_;
class RegisterToCentral;
struct RegisterToCentralDefaultTypeInternal;
extern RegisterToCentralDefaultTypeInternal _RegisterToCentral_default_instance_;
}  // namespace Ps
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace Ps {
enum MsgID : int {
  MsgID_Central_0 = 0,
  ID_RegisterToCentral = 3000,
  ID_CentralHeartBeat = 3001,
  MsgID_INT_MIN_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::min(),
  MsgID_INT_MAX_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::max(),
};

bool MsgID_IsValid(int value);
extern const uint32_t MsgID_internal_data_[];
constexpr MsgID MsgID_MIN = static_cast<MsgID>(0);
constexpr MsgID MsgID_MAX = static_cast<MsgID>(3001);
constexpr int MsgID_ARRAYSIZE = 3001 + 1;
const std::string& MsgID_Name(MsgID value);
template <typename T>
const std::string& MsgID_Name(T value) {
  static_assert(std::is_same<T, MsgID>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to MsgID_Name().");
  return MsgID_Name(static_cast<MsgID>(value));
}
bool MsgID_Parse(absl::string_view name, MsgID* value);

// ===================================================================


// -------------------------------------------------------------------

class RegisterToCentral final : public ::google::protobuf::MessageLite
/* @@protoc_insertion_point(class_definition:Ps.RegisterToCentral) */ {
 public:
  inline RegisterToCentral() : RegisterToCentral(nullptr) {}
  ~RegisterToCentral() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR RegisterToCentral(
      ::google::protobuf::internal::ConstantInitialized);

  inline RegisterToCentral(const RegisterToCentral& from) : RegisterToCentral(nullptr, from) {}
  inline RegisterToCentral(RegisterToCentral&& from) noexcept
      : RegisterToCentral(nullptr, std::move(from)) {}
  inline RegisterToCentral& operator=(const RegisterToCentral& from) {
    CopyFrom(from);
    return *this;
  }
  inline RegisterToCentral& operator=(RegisterToCentral&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const std::string& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString);
  }
  inline std::string* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<std::string>();
  }

  static const RegisterToCentral& default_instance() {
    return *internal_default_instance();
  }
  static inline const RegisterToCentral* internal_default_instance() {
    return reinterpret_cast<const RegisterToCentral*>(
        &_RegisterToCentral_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(RegisterToCentral& a, RegisterToCentral& b) { a.Swap(&b); }
  inline void Swap(RegisterToCentral* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RegisterToCentral* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  RegisterToCentral* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::MessageLite::DefaultConstruct<RegisterToCentral>(arena);
  }
  void CheckTypeAndMergeFrom(
      const ::google::protobuf::MessageLite& from) final;
  void CopyFrom(const RegisterToCentral& from);
  void MergeFrom(const RegisterToCentral& from);
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(RegisterToCentral* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "Ps.RegisterToCentral"; }

 protected:
  explicit RegisterToCentral(::google::protobuf::Arena* arena);
  RegisterToCentral(::google::protobuf::Arena* arena, const RegisterToCentral& from);
  RegisterToCentral(::google::protobuf::Arena* arena, RegisterToCentral&& from) noexcept
      : RegisterToCentral(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kServernameFieldNumber = 1,
    kServertypeFieldNumber = 2,
    kServerindexFieldNumber = 3,
  };
  // string servername = 1;
  void clear_servername() ;
  const std::string& servername() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_servername(Arg_&& arg, Args_... args);
  std::string* mutable_servername();
  PROTOBUF_NODISCARD std::string* release_servername();
  void set_allocated_servername(std::string* value);

  private:
  const std::string& _internal_servername() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_servername(
      const std::string& value);
  std::string* _internal_mutable_servername();

  public:
  // int32 servertype = 2;
  void clear_servertype() ;
  ::int32_t servertype() const;
  void set_servertype(::int32_t value);

  private:
  ::int32_t _internal_servertype() const;
  void _internal_set_servertype(::int32_t value);

  public:
  // int32 serverindex = 3;
  void clear_serverindex() ;
  ::int32_t serverindex() const;
  void set_serverindex(::int32_t value);

  private:
  ::int32_t _internal_serverindex() const;
  void _internal_set_serverindex(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:Ps.RegisterToCentral)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 0,
      39, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::internal::ArenaStringPtr servername_;
    ::int32_t servertype_;
    ::int32_t serverindex_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Central_2eproto;
};
// -------------------------------------------------------------------

class CentralHeartBeat final : public ::google::protobuf::MessageLite
/* @@protoc_insertion_point(class_definition:Ps.CentralHeartBeat) */ {
 public:
  inline CentralHeartBeat() : CentralHeartBeat(nullptr) {}
  ~CentralHeartBeat() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR CentralHeartBeat(
      ::google::protobuf::internal::ConstantInitialized);

  inline CentralHeartBeat(const CentralHeartBeat& from) : CentralHeartBeat(nullptr, from) {}
  inline CentralHeartBeat(CentralHeartBeat&& from) noexcept
      : CentralHeartBeat(nullptr, std::move(from)) {}
  inline CentralHeartBeat& operator=(const CentralHeartBeat& from) {
    CopyFrom(from);
    return *this;
  }
  inline CentralHeartBeat& operator=(CentralHeartBeat&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const std::string& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString);
  }
  inline std::string* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<std::string>();
  }

  static const CentralHeartBeat& default_instance() {
    return *internal_default_instance();
  }
  static inline const CentralHeartBeat* internal_default_instance() {
    return reinterpret_cast<const CentralHeartBeat*>(
        &_CentralHeartBeat_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(CentralHeartBeat& a, CentralHeartBeat& b) { a.Swap(&b); }
  inline void Swap(CentralHeartBeat* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(CentralHeartBeat* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CentralHeartBeat* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::MessageLite::DefaultConstruct<CentralHeartBeat>(arena);
  }
  void CheckTypeAndMergeFrom(
      const ::google::protobuf::MessageLite& from) final;
  void CopyFrom(const CentralHeartBeat& from);
  void MergeFrom(const CentralHeartBeat& from);
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(CentralHeartBeat* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "Ps.CentralHeartBeat"; }

 protected:
  explicit CentralHeartBeat(::google::protobuf::Arena* arena);
  CentralHeartBeat(::google::protobuf::Arena* arena, const CentralHeartBeat& from);
  CentralHeartBeat(::google::protobuf::Arena* arena, CentralHeartBeat&& from) noexcept
      : CentralHeartBeat(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kNatsclientsFieldNumber = 1,
  };
  // repeated .Ps.RegisterToCentral natsclients = 1;
  int natsclients_size() const;
  private:
  int _internal_natsclients_size() const;

  public:
  void clear_natsclients() ;
  ::Ps::RegisterToCentral* mutable_natsclients(int index);
  ::google::protobuf::RepeatedPtrField<::Ps::RegisterToCentral>* mutable_natsclients();

  private:
  const ::google::protobuf::RepeatedPtrField<::Ps::RegisterToCentral>& _internal_natsclients() const;
  ::google::protobuf::RepeatedPtrField<::Ps::RegisterToCentral>* _internal_mutable_natsclients();
  public:
  const ::Ps::RegisterToCentral& natsclients(int index) const;
  ::Ps::RegisterToCentral* add_natsclients();
  const ::google::protobuf::RepeatedPtrField<::Ps::RegisterToCentral>& natsclients() const;
  // @@protoc_insertion_point(class_scope:Ps.CentralHeartBeat)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 1,
      0, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::RepeatedPtrField< ::Ps::RegisterToCentral > natsclients_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Central_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// RegisterToCentral

// string servername = 1;
inline void RegisterToCentral::clear_servername() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.servername_.ClearToEmpty();
}
inline const std::string& RegisterToCentral::servername() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Ps.RegisterToCentral.servername)
  return _internal_servername();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void RegisterToCentral::set_servername(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.servername_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Ps.RegisterToCentral.servername)
}
inline std::string* RegisterToCentral::mutable_servername() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_servername();
  // @@protoc_insertion_point(field_mutable:Ps.RegisterToCentral.servername)
  return _s;
}
inline const std::string& RegisterToCentral::_internal_servername() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.servername_.Get();
}
inline void RegisterToCentral::_internal_set_servername(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.servername_.Set(value, GetArena());
}
inline std::string* RegisterToCentral::_internal_mutable_servername() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.servername_.Mutable( GetArena());
}
inline std::string* RegisterToCentral::release_servername() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Ps.RegisterToCentral.servername)
  return _impl_.servername_.Release();
}
inline void RegisterToCentral::set_allocated_servername(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.servername_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.servername_.IsDefault()) {
          _impl_.servername_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Ps.RegisterToCentral.servername)
}

// int32 servertype = 2;
inline void RegisterToCentral::clear_servertype() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.servertype_ = 0;
}
inline ::int32_t RegisterToCentral::servertype() const {
  // @@protoc_insertion_point(field_get:Ps.RegisterToCentral.servertype)
  return _internal_servertype();
}
inline void RegisterToCentral::set_servertype(::int32_t value) {
  _internal_set_servertype(value);
  // @@protoc_insertion_point(field_set:Ps.RegisterToCentral.servertype)
}
inline ::int32_t RegisterToCentral::_internal_servertype() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.servertype_;
}
inline void RegisterToCentral::_internal_set_servertype(::int32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.servertype_ = value;
}

// int32 serverindex = 3;
inline void RegisterToCentral::clear_serverindex() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.serverindex_ = 0;
}
inline ::int32_t RegisterToCentral::serverindex() const {
  // @@protoc_insertion_point(field_get:Ps.RegisterToCentral.serverindex)
  return _internal_serverindex();
}
inline void RegisterToCentral::set_serverindex(::int32_t value) {
  _internal_set_serverindex(value);
  // @@protoc_insertion_point(field_set:Ps.RegisterToCentral.serverindex)
}
inline ::int32_t RegisterToCentral::_internal_serverindex() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.serverindex_;
}
inline void RegisterToCentral::_internal_set_serverindex(::int32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.serverindex_ = value;
}

// -------------------------------------------------------------------

// CentralHeartBeat

// repeated .Ps.RegisterToCentral natsclients = 1;
inline int CentralHeartBeat::_internal_natsclients_size() const {
  return _internal_natsclients().size();
}
inline int CentralHeartBeat::natsclients_size() const {
  return _internal_natsclients_size();
}
inline void CentralHeartBeat::clear_natsclients() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.natsclients_.Clear();
}
inline ::Ps::RegisterToCentral* CentralHeartBeat::mutable_natsclients(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:Ps.CentralHeartBeat.natsclients)
  return _internal_mutable_natsclients()->Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::Ps::RegisterToCentral>* CentralHeartBeat::mutable_natsclients()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:Ps.CentralHeartBeat.natsclients)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _internal_mutable_natsclients();
}
inline const ::Ps::RegisterToCentral& CentralHeartBeat::natsclients(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Ps.CentralHeartBeat.natsclients)
  return _internal_natsclients().Get(index);
}
inline ::Ps::RegisterToCentral* CentralHeartBeat::add_natsclients() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::Ps::RegisterToCentral* _add = _internal_mutable_natsclients()->Add();
  // @@protoc_insertion_point(field_add:Ps.CentralHeartBeat.natsclients)
  return _add;
}
inline const ::google::protobuf::RepeatedPtrField<::Ps::RegisterToCentral>& CentralHeartBeat::natsclients() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:Ps.CentralHeartBeat.natsclients)
  return _internal_natsclients();
}
inline const ::google::protobuf::RepeatedPtrField<::Ps::RegisterToCentral>&
CentralHeartBeat::_internal_natsclients() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.natsclients_;
}
inline ::google::protobuf::RepeatedPtrField<::Ps::RegisterToCentral>*
CentralHeartBeat::_internal_mutable_natsclients() {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return &_impl_.natsclients_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace Ps


namespace google {
namespace protobuf {

template <>
struct is_proto_enum<::Ps::MsgID> : std::true_type {};

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_Central_2eproto_2epb_2eh
