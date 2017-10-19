//===--- STM8.h - Declare STM8 target feature support -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares STM8 TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_STM8_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_STM8_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY STM8TargetInfo : public TargetInfo {
  static const char *const GCCRegNames[];

public:
  STM8TargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
      TLSSupported = false;
      PointerWidth = 16;
      PointerAlign = 8;
      IntWidth = 16;
      IntAlign = 8;
      LongWidth = 32;
      LongAlign = 8;
      LongLongWidth = 64;
      LongLongAlign = 8;
      SuitableAlign = 8;
      DefaultAlignForAttributeAligned = 8;
      HalfWidth = 16;
      HalfAlign = 8;
      FloatWidth = 32;
      FloatAlign = 8;
      DoubleWidth = 32;
      DoubleAlign = 8;
      DoubleFormat = &llvm::APFloat::IEEEsingle();
      LongDoubleWidth = 32;
      LongDoubleAlign = 8;
      LongDoubleFormat = &llvm::APFloat::IEEEsingle();
      SizeType = UnsignedInt;
      PtrDiffType = SignedInt;
      IntPtrType = SignedInt;
      Char16Type = UnsignedInt;
      WIntType = SignedInt;
      Char32Type = UnsignedLong;
      SigAtomicType = SignedChar;
      resetDataLayout("E-p:16:8-i8:8-i16:8-i32:8-i64:8-f32:8-f64:8-n8-a:8");
  }
  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<Builtin::Info> getTargetBuiltins() const override {
    // FIXME: Implement.
    return None;
  }

  bool hasFeature(StringRef Feature) const override {
    return Feature == "stm8";
  }

  ArrayRef<const char *> getGCCRegNames() const override;

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    // No aliases.
    return None;
  }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override {
    // FIXME: implement
    switch (*Name) {
    case 'K': // the constant 1
    case 'L': // constant -1^20 .. 1^19
    case 'M': // constant 1-4:
      return true;
    }
    // No target constraints for now.
    return false;
  }

  const char *getClobbers() const override {
    // FIXME: Is this really right?
    return "";
  }

  BuiltinVaListKind getBuiltinVaListKind() const override {
    // FIXME: implement
    return TargetInfo::CharPtrBuiltinVaList;
  }
};

} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_STM8_H
