//
// Copyright 2021 Mustafa Serdar Sanli
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//



#ifndef LIBREPR_HPP_
#define LIBREPR_HPP_
#include <string.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <type_traits>
#include <cstdint>
#include <optional>


namespace librepr::_internal_v3 {


enum class DwarfTag : uint16_t
{
    None = 0,
    ArrayType = 1,
    ClassType = 2,
    EntryPoint = 3,
    EnumerationType = 4,
    FormalParameter = 5,
    ImportedDeclaration = 8,
    Label = 10,
    LexicalBlock = 11,
    Member = 13,
    PointerType = 15,
    ReferenceType = 16,
    CompileUnit = 17,
    StringType = 18,
    StructureType = 19,
    SubroutineType = 21,
    Typedef = 22,
    UnionType = 23,
    UnspecifiedParameters = 24,
    Variant = 25,
    CommonBlock = 26,
    CommonInclusion = 27,
    Inheritance = 28,
    InlinedSubroutine = 29,
    Module = 30,
    PtrToMemberType = 31,
    SetType = 32,
    SubrangeType = 33,
    WithStmt = 34,
    AccessDeclaration = 35,
    BaseType = 36,
    CatchBlock = 37,
    ConstType = 38,
    Constant = 39,
    Enumerator = 40,
    FileType = 41,
    Friend = 42,
    Namelist = 43,
    NamelistItem = 44,
    PackedType = 45,
    Subprogram = 46,
    TemplateTypeParameter = 47,
    TemplateValueParameter = 48,
    ThrownType = 49,
    TryBlock = 50,
    VariantPart = 51,
    Variable = 52,
    VolatileType = 53,
    DwarfProcedure = 54,
    RestrictType = 55,
    InterfaceType = 56,
    Namespace = 57,
    ImportedModule = 58,
    UnspecifiedType = 59,
    PartialUnit = 60,
    ImportedUnit = 61,
    Condition = 63,
    SharedType = 64,
    TypeUnit = 65,
    RvalueReferenceType = 66,
    TemplateAlias = 67,
    LoUser = 16512,
    HiUser = 65535,
};

inline
std::ostream& operator<<(std::ostream &out, DwarfTag v)
{
    switch (v)
    {
    case DwarfTag::None: out << "None"; return out;
    case DwarfTag::ArrayType: out << "ArrayType"; return out;
    case DwarfTag::ClassType: out << "ClassType"; return out;
    case DwarfTag::EntryPoint: out << "EntryPoint"; return out;
    case DwarfTag::EnumerationType: out << "EnumerationType"; return out;
    case DwarfTag::FormalParameter: out << "FormalParameter"; return out;
    case DwarfTag::ImportedDeclaration: out << "ImportedDeclaration"; return out;
    case DwarfTag::Label: out << "Label"; return out;
    case DwarfTag::LexicalBlock: out << "LexicalBlock"; return out;
    case DwarfTag::Member: out << "Member"; return out;
    case DwarfTag::PointerType: out << "PointerType"; return out;
    case DwarfTag::ReferenceType: out << "ReferenceType"; return out;
    case DwarfTag::CompileUnit: out << "CompileUnit"; return out;
    case DwarfTag::StringType: out << "StringType"; return out;
    case DwarfTag::StructureType: out << "StructureType"; return out;
    case DwarfTag::SubroutineType: out << "SubroutineType"; return out;
    case DwarfTag::Typedef: out << "Typedef"; return out;
    case DwarfTag::UnionType: out << "UnionType"; return out;
    case DwarfTag::UnspecifiedParameters: out << "UnspecifiedParameters"; return out;
    case DwarfTag::Variant: out << "Variant"; return out;
    case DwarfTag::CommonBlock: out << "CommonBlock"; return out;
    case DwarfTag::CommonInclusion: out << "CommonInclusion"; return out;
    case DwarfTag::Inheritance: out << "Inheritance"; return out;
    case DwarfTag::InlinedSubroutine: out << "InlinedSubroutine"; return out;
    case DwarfTag::Module: out << "Module"; return out;
    case DwarfTag::PtrToMemberType: out << "PtrToMemberType"; return out;
    case DwarfTag::SetType: out << "SetType"; return out;
    case DwarfTag::SubrangeType: out << "SubrangeType"; return out;
    case DwarfTag::WithStmt: out << "WithStmt"; return out;
    case DwarfTag::AccessDeclaration: out << "AccessDeclaration"; return out;
    case DwarfTag::BaseType: out << "BaseType"; return out;
    case DwarfTag::CatchBlock: out << "CatchBlock"; return out;
    case DwarfTag::ConstType: out << "ConstType"; return out;
    case DwarfTag::Constant: out << "Constant"; return out;
    case DwarfTag::Enumerator: out << "Enumerator"; return out;
    case DwarfTag::FileType: out << "FileType"; return out;
    case DwarfTag::Friend: out << "Friend"; return out;
    case DwarfTag::Namelist: out << "Namelist"; return out;
    case DwarfTag::NamelistItem: out << "NamelistItem"; return out;
    case DwarfTag::PackedType: out << "PackedType"; return out;
    case DwarfTag::Subprogram: out << "Subprogram"; return out;
    case DwarfTag::TemplateTypeParameter: out << "TemplateTypeParameter"; return out;
    case DwarfTag::TemplateValueParameter: out << "TemplateValueParameter"; return out;
    case DwarfTag::ThrownType: out << "ThrownType"; return out;
    case DwarfTag::TryBlock: out << "TryBlock"; return out;
    case DwarfTag::VariantPart: out << "VariantPart"; return out;
    case DwarfTag::Variable: out << "Variable"; return out;
    case DwarfTag::VolatileType: out << "VolatileType"; return out;
    case DwarfTag::DwarfProcedure: out << "DwarfProcedure"; return out;
    case DwarfTag::RestrictType: out << "RestrictType"; return out;
    case DwarfTag::InterfaceType: out << "InterfaceType"; return out;
    case DwarfTag::Namespace: out << "Namespace"; return out;
    case DwarfTag::ImportedModule: out << "ImportedModule"; return out;
    case DwarfTag::UnspecifiedType: out << "UnspecifiedType"; return out;
    case DwarfTag::PartialUnit: out << "PartialUnit"; return out;
    case DwarfTag::ImportedUnit: out << "ImportedUnit"; return out;
    case DwarfTag::Condition: out << "Condition"; return out;
    case DwarfTag::SharedType: out << "SharedType"; return out;
    case DwarfTag::TypeUnit: out << "TypeUnit"; return out;
    case DwarfTag::RvalueReferenceType: out << "RvalueReferenceType"; return out;
    case DwarfTag::TemplateAlias: out << "TemplateAlias"; return out;
    case DwarfTag::LoUser: out << "LoUser"; return out;
    case DwarfTag::HiUser: out << "HiUser"; return out;
    default: out << "Unknown(" << static_cast<uint16_t>(v) << ")"; return out;
    }
}

enum class DwarfAttr : uint16_t
{
    None = 0,
    Sibling = 1,
    Location = 2,
    Name = 3,
    Ordering = 9,
    ByteSize = 11,
    BitOffset = 12,
    BitSize = 13,
    StmtList = 16,
    LowPc = 17,
    HighPc = 18,
    Language = 19,
    Discr = 21,
    DiscrValue = 22,
    Visibility = 23,
    Import = 24,
    StringLength = 25,
    CommonReference = 26,
    CompDir = 27,
    ConstValue = 28,
    ContainingType = 29,
    DefaultValue = 30,
    Inline = 32,
    IsOptional = 33,
    LowerBound = 34,
    Producer = 37,
    Prototyped = 39,
    ReturnAddr = 42,
    StartScope = 44,
    BitStride = 46,
    UpperBound = 47,
    AbstractOrigin = 49,
    Accessibility = 50,
    AddressClass = 51,
    Artificial = 52,
    BaseTypes = 53,
    CallingConvention = 54,
    Count = 55,
    DataMemberLocation = 56,
    DeclColumn = 57,
    DeclFile = 58,
    DeclLine = 59,
    Declaration = 60,
    DiscrList = 61,
    Encoding = 62,
    External = 63,
    FrameBase = 64,
    Friend = 65,
    IdentifierCase = 66,
    MacroInfo = 67,
    NamelistItem = 68,
    Priority = 69,
    Segment = 70,
    Specification = 71,
    StaticLink = 72,
    Type = 73,
    UseLocation = 74,
    VariableParameter = 75,
    Virtuality = 76,
    VtableElemLocation = 77,
    Allocated = 78,
    Associated = 79,
    DataLocation = 80,
    ByteStride = 81,
    EntryPc = 82,
    Use_UTF8 = 83,
    Extension = 84,
    Ranges = 85,
    Trampoline = 86,
    CallColumn = 87,
    CallFile = 88,
    CallLine = 89,
    Description = 90,
    BinaryScale = 91,
    DecimalScale = 92,
    Small = 93,
    DecimalSign = 94,
    DigitCount = 95,
    PictureString = 96,
    Mutable = 97,
    ThreadsScaled = 98,
    Explicit = 99,
    ObjectPointer = 100,
    Endianity = 101,
    Elemental = 102,
    Pure = 103,
    Recursive = 104,
    Signature = 105,
    MainSubprogram = 106,
    DataBitOffset = 107,
    ConstExpr = 108,
    EnumClass = 109,
    LinkageName = 110,
    StringLengthBitSize = 111,
    StringLengthByteSize = 112,
    Rank = 113,
    StrOffsetsBase = 114,
    AddrBase = 115,
    RnglistsBase = 116,
    DwoName = 118,
    Reference = 119,
    RvalueReference = 120,
    Macros = 121,
    CallAllCalls = 122,
    CallAllSourceCalls = 123,
    CallAllTailCalls = 124,
    CallReturnPc = 125,
    CallValue = 126,
    CallOrigin = 127,
    CallParameter = 128,
    CallPc = 129,
    CallTailCall = 130,
    CallTarget = 131,
    CallTargetClobbered = 132,
    CallDataLocation = 133,
    CallDataValue = 134,
    Noreturn = 135,
    Alignment = 136,
    ExportSymbols = 137,
    Deleted = 138,
    Defaulted = 139,
    LoclistsBase = 140,
    LoUser = 8192,
    HiUser = 16383,
};

inline
std::ostream& operator<<(std::ostream &out, DwarfAttr v)
{
    switch (v)
    {
    case DwarfAttr::None: out << "None"; return out;
    case DwarfAttr::Sibling: out << "Sibling"; return out;
    case DwarfAttr::Location: out << "Location"; return out;
    case DwarfAttr::Name: out << "Name"; return out;
    case DwarfAttr::Ordering: out << "Ordering"; return out;
    case DwarfAttr::ByteSize: out << "ByteSize"; return out;
    case DwarfAttr::BitOffset: out << "BitOffset"; return out;
    case DwarfAttr::BitSize: out << "BitSize"; return out;
    case DwarfAttr::StmtList: out << "StmtList"; return out;
    case DwarfAttr::LowPc: out << "LowPc"; return out;
    case DwarfAttr::HighPc: out << "HighPc"; return out;
    case DwarfAttr::Language: out << "Language"; return out;
    case DwarfAttr::Discr: out << "Discr"; return out;
    case DwarfAttr::DiscrValue: out << "DiscrValue"; return out;
    case DwarfAttr::Visibility: out << "Visibility"; return out;
    case DwarfAttr::Import: out << "Import"; return out;
    case DwarfAttr::StringLength: out << "StringLength"; return out;
    case DwarfAttr::CommonReference: out << "CommonReference"; return out;
    case DwarfAttr::CompDir: out << "CompDir"; return out;
    case DwarfAttr::ConstValue: out << "ConstValue"; return out;
    case DwarfAttr::ContainingType: out << "ContainingType"; return out;
    case DwarfAttr::DefaultValue: out << "DefaultValue"; return out;
    case DwarfAttr::Inline: out << "Inline"; return out;
    case DwarfAttr::IsOptional: out << "IsOptional"; return out;
    case DwarfAttr::LowerBound: out << "LowerBound"; return out;
    case DwarfAttr::Producer: out << "Producer"; return out;
    case DwarfAttr::Prototyped: out << "Prototyped"; return out;
    case DwarfAttr::ReturnAddr: out << "ReturnAddr"; return out;
    case DwarfAttr::StartScope: out << "StartScope"; return out;
    case DwarfAttr::BitStride: out << "BitStride"; return out;
    case DwarfAttr::UpperBound: out << "UpperBound"; return out;
    case DwarfAttr::AbstractOrigin: out << "AbstractOrigin"; return out;
    case DwarfAttr::Accessibility: out << "Accessibility"; return out;
    case DwarfAttr::AddressClass: out << "AddressClass"; return out;
    case DwarfAttr::Artificial: out << "Artificial"; return out;
    case DwarfAttr::BaseTypes: out << "BaseTypes"; return out;
    case DwarfAttr::CallingConvention: out << "CallingConvention"; return out;
    case DwarfAttr::Count: out << "Count"; return out;
    case DwarfAttr::DataMemberLocation: out << "DataMemberLocation"; return out;
    case DwarfAttr::DeclColumn: out << "DeclColumn"; return out;
    case DwarfAttr::DeclFile: out << "DeclFile"; return out;
    case DwarfAttr::DeclLine: out << "DeclLine"; return out;
    case DwarfAttr::Declaration: out << "Declaration"; return out;
    case DwarfAttr::DiscrList: out << "DiscrList"; return out;
    case DwarfAttr::Encoding: out << "Encoding"; return out;
    case DwarfAttr::External: out << "External"; return out;
    case DwarfAttr::FrameBase: out << "FrameBase"; return out;
    case DwarfAttr::Friend: out << "Friend"; return out;
    case DwarfAttr::IdentifierCase: out << "IdentifierCase"; return out;
    case DwarfAttr::MacroInfo: out << "MacroInfo"; return out;
    case DwarfAttr::NamelistItem: out << "NamelistItem"; return out;
    case DwarfAttr::Priority: out << "Priority"; return out;
    case DwarfAttr::Segment: out << "Segment"; return out;
    case DwarfAttr::Specification: out << "Specification"; return out;
    case DwarfAttr::StaticLink: out << "StaticLink"; return out;
    case DwarfAttr::Type: out << "Type"; return out;
    case DwarfAttr::UseLocation: out << "UseLocation"; return out;
    case DwarfAttr::VariableParameter: out << "VariableParameter"; return out;
    case DwarfAttr::Virtuality: out << "Virtuality"; return out;
    case DwarfAttr::VtableElemLocation: out << "VtableElemLocation"; return out;
    case DwarfAttr::Allocated: out << "Allocated"; return out;
    case DwarfAttr::Associated: out << "Associated"; return out;
    case DwarfAttr::DataLocation: out << "DataLocation"; return out;
    case DwarfAttr::ByteStride: out << "ByteStride"; return out;
    case DwarfAttr::EntryPc: out << "EntryPc"; return out;
    case DwarfAttr::Use_UTF8: out << "Use_UTF8"; return out;
    case DwarfAttr::Extension: out << "Extension"; return out;
    case DwarfAttr::Ranges: out << "Ranges"; return out;
    case DwarfAttr::Trampoline: out << "Trampoline"; return out;
    case DwarfAttr::CallColumn: out << "CallColumn"; return out;
    case DwarfAttr::CallFile: out << "CallFile"; return out;
    case DwarfAttr::CallLine: out << "CallLine"; return out;
    case DwarfAttr::Description: out << "Description"; return out;
    case DwarfAttr::BinaryScale: out << "BinaryScale"; return out;
    case DwarfAttr::DecimalScale: out << "DecimalScale"; return out;
    case DwarfAttr::Small: out << "Small"; return out;
    case DwarfAttr::DecimalSign: out << "DecimalSign"; return out;
    case DwarfAttr::DigitCount: out << "DigitCount"; return out;
    case DwarfAttr::PictureString: out << "PictureString"; return out;
    case DwarfAttr::Mutable: out << "Mutable"; return out;
    case DwarfAttr::ThreadsScaled: out << "ThreadsScaled"; return out;
    case DwarfAttr::Explicit: out << "Explicit"; return out;
    case DwarfAttr::ObjectPointer: out << "ObjectPointer"; return out;
    case DwarfAttr::Endianity: out << "Endianity"; return out;
    case DwarfAttr::Elemental: out << "Elemental"; return out;
    case DwarfAttr::Pure: out << "Pure"; return out;
    case DwarfAttr::Recursive: out << "Recursive"; return out;
    case DwarfAttr::Signature: out << "Signature"; return out;
    case DwarfAttr::MainSubprogram: out << "MainSubprogram"; return out;
    case DwarfAttr::DataBitOffset: out << "DataBitOffset"; return out;
    case DwarfAttr::ConstExpr: out << "ConstExpr"; return out;
    case DwarfAttr::EnumClass: out << "EnumClass"; return out;
    case DwarfAttr::LinkageName: out << "LinkageName"; return out;
    case DwarfAttr::StringLengthBitSize: out << "StringLengthBitSize"; return out;
    case DwarfAttr::StringLengthByteSize: out << "StringLengthByteSize"; return out;
    case DwarfAttr::Rank: out << "Rank"; return out;
    case DwarfAttr::StrOffsetsBase: out << "StrOffsetsBase"; return out;
    case DwarfAttr::AddrBase: out << "AddrBase"; return out;
    case DwarfAttr::RnglistsBase: out << "RnglistsBase"; return out;
    case DwarfAttr::DwoName: out << "DwoName"; return out;
    case DwarfAttr::Reference: out << "Reference"; return out;
    case DwarfAttr::RvalueReference: out << "RvalueReference"; return out;
    case DwarfAttr::Macros: out << "Macros"; return out;
    case DwarfAttr::CallAllCalls: out << "CallAllCalls"; return out;
    case DwarfAttr::CallAllSourceCalls: out << "CallAllSourceCalls"; return out;
    case DwarfAttr::CallAllTailCalls: out << "CallAllTailCalls"; return out;
    case DwarfAttr::CallReturnPc: out << "CallReturnPc"; return out;
    case DwarfAttr::CallValue: out << "CallValue"; return out;
    case DwarfAttr::CallOrigin: out << "CallOrigin"; return out;
    case DwarfAttr::CallParameter: out << "CallParameter"; return out;
    case DwarfAttr::CallPc: out << "CallPc"; return out;
    case DwarfAttr::CallTailCall: out << "CallTailCall"; return out;
    case DwarfAttr::CallTarget: out << "CallTarget"; return out;
    case DwarfAttr::CallTargetClobbered: out << "CallTargetClobbered"; return out;
    case DwarfAttr::CallDataLocation: out << "CallDataLocation"; return out;
    case DwarfAttr::CallDataValue: out << "CallDataValue"; return out;
    case DwarfAttr::Noreturn: out << "Noreturn"; return out;
    case DwarfAttr::Alignment: out << "Alignment"; return out;
    case DwarfAttr::ExportSymbols: out << "ExportSymbols"; return out;
    case DwarfAttr::Deleted: out << "Deleted"; return out;
    case DwarfAttr::Defaulted: out << "Defaulted"; return out;
    case DwarfAttr::LoclistsBase: out << "LoclistsBase"; return out;
    case DwarfAttr::LoUser: out << "LoUser"; return out;
    case DwarfAttr::HiUser: out << "HiUser"; return out;
    default: out << "Unknown(" << static_cast<uint16_t>(v) << ")"; return out;
    }
}

enum class DwarfForm : uint16_t
{
    None = 0,
    Addr = 1,
    Block2 = 3,
    Block4 = 4,
    Data2 = 5,
    Data4 = 6,
    Data8 = 7,
    String = 8,
    Block = 9,
    Block1 = 10,
    Data1 = 11,
    Flag = 12,
    Sdata = 13,
    Strp = 14,
    Udata = 15,
    RefAddr = 16,
    Ref1 = 17,
    Ref2 = 18,
    Ref4 = 19,
    Ref8 = 20,
    RefUdata = 21,
    Indirect = 22,
    SecOffset = 23,
    Exprloc = 24,
    FlagPresent = 25,
    Strx = 26,
    Addrx = 27,
    RefSup4 = 28,
    StrpSup = 29,
    Data16 = 30,
    LineStrp = 31,
    RefSig8 = 32,
    ImplicitConst = 33,
    Loclistx = 34,
    Rnglistx = 35,
    RefSup8 = 36,
    Strx1 = 37,
    Strx2 = 38,
    Strx3 = 39,
    Strx4 = 40,
    Addrx1 = 41,
    Addrx2 = 42,
    Addrx3 = 43,
    Addrx4 = 44,
};

inline
std::ostream& operator<<(std::ostream &out, DwarfForm v)
{
    switch (v)
    {
    case DwarfForm::None: out << "None"; return out;
    case DwarfForm::Addr: out << "Addr"; return out;
    case DwarfForm::Block2: out << "Block2"; return out;
    case DwarfForm::Block4: out << "Block4"; return out;
    case DwarfForm::Data2: out << "Data2"; return out;
    case DwarfForm::Data4: out << "Data4"; return out;
    case DwarfForm::Data8: out << "Data8"; return out;
    case DwarfForm::String: out << "String"; return out;
    case DwarfForm::Block: out << "Block"; return out;
    case DwarfForm::Block1: out << "Block1"; return out;
    case DwarfForm::Data1: out << "Data1"; return out;
    case DwarfForm::Flag: out << "Flag"; return out;
    case DwarfForm::Sdata: out << "Sdata"; return out;
    case DwarfForm::Strp: out << "Strp"; return out;
    case DwarfForm::Udata: out << "Udata"; return out;
    case DwarfForm::RefAddr: out << "RefAddr"; return out;
    case DwarfForm::Ref1: out << "Ref1"; return out;
    case DwarfForm::Ref2: out << "Ref2"; return out;
    case DwarfForm::Ref4: out << "Ref4"; return out;
    case DwarfForm::Ref8: out << "Ref8"; return out;
    case DwarfForm::RefUdata: out << "RefUdata"; return out;
    case DwarfForm::Indirect: out << "Indirect"; return out;
    case DwarfForm::SecOffset: out << "SecOffset"; return out;
    case DwarfForm::Exprloc: out << "Exprloc"; return out;
    case DwarfForm::FlagPresent: out << "FlagPresent"; return out;
    case DwarfForm::Strx: out << "Strx"; return out;
    case DwarfForm::Addrx: out << "Addrx"; return out;
    case DwarfForm::RefSup4: out << "RefSup4"; return out;
    case DwarfForm::StrpSup: out << "StrpSup"; return out;
    case DwarfForm::Data16: out << "Data16"; return out;
    case DwarfForm::LineStrp: out << "LineStrp"; return out;
    case DwarfForm::RefSig8: out << "RefSig8"; return out;
    case DwarfForm::ImplicitConst: out << "ImplicitConst"; return out;
    case DwarfForm::Loclistx: out << "Loclistx"; return out;
    case DwarfForm::Rnglistx: out << "Rnglistx"; return out;
    case DwarfForm::RefSup8: out << "RefSup8"; return out;
    case DwarfForm::Strx1: out << "Strx1"; return out;
    case DwarfForm::Strx2: out << "Strx2"; return out;
    case DwarfForm::Strx3: out << "Strx3"; return out;
    case DwarfForm::Strx4: out << "Strx4"; return out;
    case DwarfForm::Addrx1: out << "Addrx1"; return out;
    case DwarfForm::Addrx2: out << "Addrx2"; return out;
    case DwarfForm::Addrx3: out << "Addrx3"; return out;
    case DwarfForm::Addrx4: out << "Addrx4"; return out;
    default: out << "Unknown(" << static_cast<uint16_t>(v) << ")"; return out;
    }
}

using Buffer = std::basic_string_view<uint8_t>;

// DWARF processing lib
struct DebugDataLoader;

struct Reader
{
    Reader(const uint8_t *data)
        : _it(data)
    {
    }

    static int64_t DecodeLEB128Unsigned(const uint8_t *it, const uint8_t **it_out = nullptr)
    {
        const uint8_t *begin = it;
        while (*it & 0b1000'0000)
        {
            ++it;
        }
        if (it_out)
        {
            *it_out = it + 1;
        }

        uint64_t result = 0;

        while (true)
        {
            result <<= 7;
            result |= (*it & 0x7f);
            if (it == begin) break;
            --it;
        }
        return result;
    }

    static int64_t DecodeLEB128Signed(const uint8_t *it, const uint8_t **it_out = nullptr)
    {
        const uint8_t *begin = it;
        while (*it & 0b1000'0000)
        {
            ++it;
        }
        if (it_out)
        {
            *it_out = it + 1;
        }

        uint64_t result = 0;
        if (*it & 0b0100'0000)
        {
            result = -1;
        }

        while (true)
        {
            result <<= 7;
            result |= (*it & 0x7f);
            if (it == begin) break;
            --it;
        }
        return result;
    }


    uint64_t u8() { uint8_t res = *_it; _it += 1; return res; }
    uint64_t u16() { uint16_t res = *(uint16_t*)_it; _it += 2; return res; }
    uint64_t u32() { uint32_t res = *(uint32_t*)_it; _it += 4; return res; }
    uint64_t u64() { uint64_t res = *(uint64_t*)_it; _it += 8; return res; }

    uint64_t leb128() { return DecodeLEB128Unsigned(_it, &_it); }
    uint64_t leb128s() { return DecodeLEB128Signed(_it, &_it); }

    void skip(size_t len) { _it += len; }
    Buffer buffer(size_t len) { Buffer res(_it, len); _it += len; return res; }

    const char* str() { const char *res = (const char*)_it; _it += strlen(res) + 1; return res; }

    const uint8_t *_it;
};

struct AttrNameAndForm
{
    DwarfAttr name;
    DwarfForm form;
    int64_t implicit_const; // TODO rarely used, inefficient to keep inline
};

struct AbbrevEntry
{
    DwarfTag tag;
    uint8_t has_children;
    uint16_t num_attrs;
    AttrNameAndForm attrs[0];

    size_t findAttrIdxByName(DwarfAttr name) const
    {
        for (uint16_t i = 0; i < num_attrs; ++i)
        {
            if (attrs[i].name == name)
            {
                return i;
            }
        }
        return -1;
    }
};

struct DwarfCompilationUnit
{
    void parse_debug_abbrev(Reader it)
    {
        {
            _abbrev_offsets.push_back(0);
            _abbrev_data_unpacked.resize(sizeof(AbbrevEntry));
            AbbrevEntry *entry = reinterpret_cast<AbbrevEntry*>(_abbrev_data_unpacked.data());
            entry->tag = DwarfTag::None;
            entry->has_children = 0;
            entry->num_attrs = 0;
        }

        while (true) {
            uint64_t abbrev_code = it.leb128();
            if (abbrev_code == 0) break;

            if (abbrev_code != _abbrev_offsets.size()) throw std::runtime_error("Unexpected abbrev code");

            uint32_t entry_offset = _abbrev_data_unpacked.size();
            _abbrev_offsets.push_back(entry_offset);
            _abbrev_data_unpacked.resize(_abbrev_data_unpacked.size() + sizeof(AbbrevEntry));
            AbbrevEntry *entry = reinterpret_cast<AbbrevEntry*>(_abbrev_data_unpacked.data() + entry_offset);

            entry->tag = static_cast<DwarfTag>(it.leb128());
            entry->has_children = (it.u8() == 1); // DW_CHILDREN_yes
            entry->num_attrs = 0;

            while (true) {
                DwarfAttr attr_name = static_cast<DwarfAttr>(it.leb128());
                DwarfForm attr_form = static_cast<DwarfForm>(it.leb128());
                int64_t implicit_const_val = 0;

                if (attr_name == DwarfAttr::None && attr_form == DwarfForm::None) {
                    break;
                }

                if (attr_form == DwarfForm::ImplicitConst)
                {
                    implicit_const_val = it.leb128s();
                }

                _abbrev_data_unpacked.resize(_abbrev_data_unpacked.size() + sizeof(AttrNameAndForm));
                entry = reinterpret_cast<AbbrevEntry*>(_abbrev_data_unpacked.data() + entry_offset);
                entry->attrs[entry->num_attrs].name = attr_name;
                entry->attrs[entry->num_attrs].form = attr_form;
                entry->attrs[entry->num_attrs].implicit_const = implicit_const_val;
                entry->num_attrs++;
            }

            static uint16_t max_num = 0;
            if (entry->num_attrs > max_num) max_num = entry->num_attrs;
        }
    }

    const AbbrevEntry& get_abbrev(uint32_t abbrev_code)
    {
        return *reinterpret_cast<AbbrevEntry*>(_abbrev_data_unpacked.data() + _abbrev_offsets[abbrev_code]);
    }

    size_t _size;
    size_t _offset;
    size_t _root_die_offset;
    std::vector<char> _abbrev_data_unpacked;
    std::vector<uint32_t> _abbrev_offsets;
};

struct RawDwarfData
{
    Buffer debug_info;
    Buffer debug_abbrev;
    Buffer debug_str;

    RawDwarfData() = default;

    RawDwarfData(RawDwarfData &&ot)
        : debug_info(ot.debug_info)
        , debug_abbrev(ot.debug_abbrev)
        , debug_str(ot.debug_str)
    {
        // TODO steal destructor
    }


    RawDwarfData& operator=(RawDwarfData &&ot)
    {
        debug_info = ot.debug_info;
        debug_abbrev = ot.debug_abbrev;
        debug_str = ot.debug_str;
        return *this;
    }

    static RawDwarfData LoadELF(const char *path)
    {
        int fd __attribute__((__cleanup__(CleanupFD))) = open(path, O_RDONLY);
        if (fd == -1)
        {
            throw std::runtime_error("open failed");
        }

        struct stat sb;
        if (fstat(fd, &sb) == -1)
        {
            throw std::runtime_error("fstat failed");
        }

        void *_file_data = mmap(nullptr, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (_file_data == MAP_FAILED)
        {
            throw std::runtime_error("mmap failed");
        }

        uint8_t *file_begin = (uint8_t*)_file_data;

        Elf64_Ehdr *elf = reinterpret_cast<Elf64_Ehdr*>(_file_data);
        if (*(uint32_t*)elf != 0x464C457f)
        {
            throw std::runtime_error("Not an ELF file");
        }

        if (elf->e_ident[4] != ELFCLASS64)
        {
            throw std::runtime_error("Not 64 bits");
        }
        if (elf->e_ident[5] != ELFDATA2LSB)
        {
            throw std::runtime_error("Not little endian");
        }

        if (elf->e_type != ET_EXEC && elf->e_type != ET_DYN)
        {
            throw std::runtime_error("Not an executable file");
        }
        if (elf->e_machine != EM_X86_64)
        {
            throw std::runtime_error("Not AMD64");
        }

        Elf64_Shdr *sec_shstr = reinterpret_cast<Elf64_Shdr*>(file_begin + elf->e_shoff + elf->e_shentsize * elf->e_shstrndx);
        uint8_t *shstr = file_begin + sec_shstr->sh_offset;

        Buffer debug_info, debug_abbrev, debug_str;
        const char *debug_link = nullptr;
        for (int i = 0; i < elf->e_shnum; ++i)
        {
            Elf64_Shdr *shdr = reinterpret_cast<Elf64_Shdr*>(file_begin + elf->e_shoff + elf->e_shentsize * i);
            const char *sname = reinterpret_cast<const char*>(shstr + shdr->sh_name);

            if (strcmp(sname, ".debug_info") == 0)
            {
                debug_info = Buffer(file_begin + shdr->sh_offset, shdr->sh_size);
            }
            else if (strcmp(sname, ".debug_abbrev") == 0)
            {
                debug_abbrev = Buffer(file_begin + shdr->sh_offset, shdr->sh_size);
            }
            else if (strcmp(sname, ".debug_str") == 0)
            {
                debug_str = Buffer(file_begin + shdr->sh_offset, shdr->sh_size);
            }
            else if (strcmp(sname, ".gnu_debuglink") == 0)
            {
                debug_link = reinterpret_cast<const char*>(file_begin + shdr->sh_offset);
            }
        }

        if (!debug_info.empty() && !debug_abbrev.empty() && !debug_str.empty())
        {
            return RawDwarfData(debug_info, debug_abbrev, debug_str);
        }

        if (debug_link)
        {
            char buf[1024];
            ssize_t len;
            if (strcmp(path, "/proc/self/exe") == 0)
            {
                len = readlink("/proc/self/exe", buf, 1024);
                if (len == -1 || len == 1024) throw std::runtime_error("readlink");
                buf[len] = 0;
            }
            else
            {
                strcpy(buf, path);
                len = strlen(buf);
            }

            while (true)
            {
                --len;
                if (buf[len] == '/')
                {
                    break;
                }
                buf[len] = 0;
            }

            strcat(buf, debug_link); // TODO unsafe
            return RawDwarfData::LoadELF(buf); // TODO this doesn't work when debug_link file is not in the same dir
        }

        throw std::runtime_error("No debug info found");
    }

private:

    static void CleanupFD(int *fd)
    {
        if (*fd != -1)
        {
            close(*fd);
            *fd = -1;
        }
    }

    RawDwarfData(Buffer debug_info_, Buffer debug_abbrev_, Buffer debug_str_)
        : debug_info(debug_info_)
        , debug_abbrev(debug_abbrev_)
        , debug_str(debug_str_)
    {
        // TODO cleanup mmap..
    }
};

struct DIEAccessor
{
    DebugDataLoader *_loader;
    DwarfCompilationUnit *_cu;
    const AbbrevEntry *_abbrev;
    const uint8_t *_nextDieBegin;
    const uint8_t *_rangeEnd;
    const uint8_t *_attrData[26]; // TODO make this a small_vector
    uint64_t _offset;

    void operator++();

    operator bool() const
    {
        return _abbrev != nullptr;
    }

    DwarfTag tag()
    {
        return _abbrev->tag;
    }

    bool has_children()
    {
        return _abbrev->has_children;
    }


    RawDwarfData& getRawDwarfData();

    std::optional<std::string_view> getCStringView(DwarfAttr attr)
    {
        RawDwarfData &rdd = getRawDwarfData();

        size_t idx = _abbrev->findAttrIdxByName(attr);
        if (idx == (size_t)-1)
        {
            return std::nullopt;
        }

        switch (_abbrev->attrs[idx].form)
        {
        case DwarfForm::Strp:   return (const char*)rdd.debug_str.data() + *(const uint32_t*)(_attrData[idx]);
        case DwarfForm::String: return (const char*)_attrData[idx];
        default: return std::nullopt;
        }
    }

    std::optional<Buffer> getBuffer(DwarfAttr attr)
    {
        size_t idx = _abbrev->findAttrIdxByName(attr);
        if (idx == (size_t)-1)
        {
            return std::nullopt;
        }

        switch (_abbrev->attrs[idx].form)
        {
        case DwarfForm::Block1:
        {
            uint64_t size = *(const uint8_t*)(_attrData[idx]);
            return Buffer(_attrData[idx] + 1, size);
        }
        case DwarfForm::Exprloc:
        {
            Reader it(_attrData[idx]);
            uint64_t len = it.leb128();
            return it.buffer(len);
        }
        default: return std::nullopt;
        }
    }

    std::optional<uint64_t> getOffset(DwarfAttr attr)
    {
        size_t idx = _abbrev->findAttrIdxByName(attr);
        if (idx == (size_t)-1)
        {
            return std::nullopt;
        }

        switch (_abbrev->attrs[idx].form)
        {
        case DwarfForm::SecOffset: return *(const uint32_t*)(_attrData[idx]);
        case DwarfForm::Ref4: return *(const uint32_t*)(_attrData[idx]);
        case DwarfForm::Addr: return *(const uint64_t*)(_attrData[idx]);
        case DwarfForm::Exprloc:
        {
            Reader it(_attrData[idx]);
            if (it.leb128() == 9 && it.u8() == 3) // When exprloc program is a single `DW_OP_addr`
            {
                return it.u64();
            }
            return std::nullopt;
        }
        default: return std::nullopt;
        }
    }

    std::optional<uint64_t> getUnsigned(DwarfAttr attr)
    {
        size_t idx = _abbrev->findAttrIdxByName(attr);
        if (idx == (size_t)-1)
        {
            return std::nullopt;
        }

        switch (_abbrev->attrs[idx].form)
        {
        case DwarfForm::Data1: return *(const uint8_t* )(_attrData[idx]);
        case DwarfForm::Data2: return *(const uint16_t*)(_attrData[idx]);
        case DwarfForm::Data4: return *(const uint32_t*)(_attrData[idx]);
        case DwarfForm::Data8: return *(const uint64_t*)(_attrData[idx]);
        case DwarfForm::Udata: return Reader::DecodeLEB128Unsigned(_attrData[idx]);
        case DwarfForm::Sdata: return Reader::DecodeLEB128Signed(_attrData[idx]);
        case DwarfForm::ImplicitConst: return _abbrev->attrs[idx].implicit_const;
        default: return std::nullopt;
        }
    }

    std::optional<int64_t> getSigned(DwarfAttr attr)
    {
        size_t idx = _abbrev->findAttrIdxByName(attr);
        if (idx == (size_t)-1)
        {
            return std::nullopt;
        }

        switch (_abbrev->attrs[idx].form)
        {
        case DwarfForm::Data1: return (uint64_t)*(const uint8_t* )(_attrData[idx]);
        case DwarfForm::Data2: return (uint64_t)*(const uint16_t*)(_attrData[idx]);
        case DwarfForm::Data4: return (uint64_t)*(const uint32_t*)(_attrData[idx]);
        case DwarfForm::Data8: return (uint64_t)*(const uint64_t*)(_attrData[idx]);
        case DwarfForm::Sdata: return Reader::DecodeLEB128Signed(_attrData[idx]);
        default: return std::nullopt;
        }
    }
};

struct DebugDataLoader
{
    void loadFile(const char *path)
    {
        try
        {
            loadFileImpl(path);
        }
        catch (const std::runtime_error &err)
        {
            std::cerr << err.what() << "\n";
            std::cerr << "librepr: Error loading file: " << path << ". Values will not be pretty printed.\n";
            _compilation_units.clear();
        }
    }

    size_t num_compilation_units()
    {
        return _compilation_units.size();
    }

    DIEAccessor loadDie(DwarfCompilationUnit *cu, const uint8_t *die)
    {
        Reader it(die);

        uint64_t die_abbrev_code = it.leb128();

        const auto &abbrev = cu->get_abbrev(die_abbrev_code);
        if (abbrev.tag == DwarfTag::None) {
            DIEAccessor curDie;
            curDie._offset = die - rdd.debug_info.data();
            curDie._loader = this;
            curDie._cu = cu;
            curDie._rangeEnd = rdd.debug_info.data() + cu->_offset + cu->_size;
            curDie._abbrev = &abbrev;
            curDie._nextDieBegin = it._it;
            return curDie;
        }

        DIEAccessor curDie;
        curDie._offset = die - rdd.debug_info.data();
        curDie._loader = this;
        curDie._cu = cu;
        curDie._rangeEnd = rdd.debug_info.data() + cu->_offset + cu->_size;
        curDie._abbrev = &abbrev;
        if (abbrev.num_attrs > 26) throw std::runtime_error("TODO larger than small_vector size");

        auto skipLEB128 = [](const uint8_t *it) -> const uint8_t* {
            while (true) {
                uint8_t byte = *it; ++it;
                if ((byte & 0x80) == 0)
                    break;
            }
            return it;
        };

        for (int i = 0; i < abbrev.num_attrs; ++i)
        {
            curDie._attrData[i] = it._it;
            switch (abbrev.attrs[i].form)
            {
            case DwarfForm::FlagPresent:                                 break; // maybe use bool?
            case DwarfForm::Strp:          it._it += 4;                  break;
            case DwarfForm::LineStrp:      it._it += 4;                  break;
            case DwarfForm::Data1:         it._it += 1;                  break;
            case DwarfForm::Data2:         it._it += 2;                  break;
            case DwarfForm::Data4:         it._it += 4;                  break;
            case DwarfForm::Data8:         it._it += 8;                  break;
            case DwarfForm::Sdata:         it._it = skipLEB128(it._it);  break;
            case DwarfForm::Udata:         it._it = skipLEB128(it._it);  break;
            case DwarfForm::Addrx:         it._it = skipLEB128(it._it);  break;
            case DwarfForm::Rnglistx:      it._it = skipLEB128(it._it);  break;
            case DwarfForm::Loclistx:      it._it = skipLEB128(it._it);  break;
            case DwarfForm::SecOffset:     it._it += 4;                  break;
            case DwarfForm::Addr:          it._it += 8;                  break;
            case DwarfForm::Ref4:          it._it += 4;                  break;
            case DwarfForm::String:        it._it += strlen((const char*)it._it) + 1; break;
            case DwarfForm::Block1:        it._it += 1 + it._it[0];      break;
            case DwarfForm::Strx1:         it._it += 1;                  break;
            case DwarfForm::Strx2:         it._it += 2;                  break;
            case DwarfForm::Exprloc:
            {
                uint64_t len = it.leb128();
                it.skip(len);
                break;
            }
            case DwarfForm::ImplicitConst: break;
            default:
            {
                std::stringstream ss;
                ss << "Unknown form " << static_cast<uint16_t>(abbrev.attrs[i].form);
                throw std::runtime_error(ss.str());
            }
            }
        }

        curDie._nextDieBegin = it._it;

        return curDie;
    }

    DIEAccessor loadCompilationUnitRootDie(size_t cu_idx)
    {
        return loadCompilationUnitDie(cu_idx, _compilation_units[cu_idx]._root_die_offset);
    }

    DIEAccessor loadCompilationUnitDie(size_t cu_idx, uint64_t cu_die_offset)
    {
        auto &cu = _compilation_units[cu_idx];
        return loadDie(&cu, rdd.debug_info.data() + cu._offset + cu_die_offset);
    }

    void *_file_data;
    RawDwarfData rdd;
    std::vector<DwarfCompilationUnit> _compilation_units;

private:
    void loadFileImpl(const char *path)
    {
        rdd = RawDwarfData::LoadELF(path);

        Reader it(rdd.debug_info.data());

        for (int i = 0; ; ++i)
        {
            uint64_t unit_offset = (it._it - rdd.debug_info.data());
            if (unit_offset >= rdd.debug_info.size()) break;

            uint64_t unit_len = it.u32();
            if (unit_len == 0xFFFFFFFFu)
            {
                throw std::runtime_error("64 bit dwarf format"); // Below sizes must differ too..
            }

            uint16_t dwarf_ver = it.u16();
            switch (dwarf_ver)
            {
            case 4:
            {
                uint64_t debug_abbrev_offset = it.u32();
                uint64_t address_size = it.u8();
                if (address_size != 8)
                {
                    throw std::runtime_error("Not 8-byte addressing");
                }

                it._it = rdd.debug_info.data() + unit_offset + 4 + unit_len;


                auto &cu = _compilation_units.emplace_back();
                cu._offset = unit_offset;
                cu._size = 4 + unit_len;
                cu._root_die_offset = 11;
                cu.parse_debug_abbrev(Reader(rdd.debug_abbrev.data() + debug_abbrev_offset));
                break;
            }
            case 5:
            {
                uint64_t unit_type = it.u8();
                if (unit_type != 1)
                {
                    throw std::runtime_error("Unknown unit type");
                }

                uint64_t address_size = it.u8();
                if (address_size != 8)
                {
                    throw std::runtime_error("Not 8-byte addressing");
                }

                uint64_t debug_abbrev_offset = it.u32();

                it._it = rdd.debug_info.data() + unit_offset + 4 + unit_len;


                auto &cu = _compilation_units.emplace_back();
                cu._offset = unit_offset;
                cu._size = 4 + unit_len;
                cu._root_die_offset = 12;
                cu.parse_debug_abbrev(Reader(rdd.debug_abbrev.data() + debug_abbrev_offset));
                break;
            }
            default:
                throw std::runtime_error("Unsupported dwarf version");
            }
        }
    }
};

inline void DIEAccessor::operator++()
{
    if (_nextDieBegin >= _rangeEnd)
    {
        _abbrev = nullptr; // Mark end
        _nextDieBegin = nullptr;
        _rangeEnd = nullptr;
        return;
    }
    *this = this->_loader->loadDie(this->_cu, this->_nextDieBegin);
}

inline RawDwarfData& DIEAccessor::getRawDwarfData()
{
    return _loader->rdd;
}


using StringifyFunc = void(*)(std::ostream &out, void *type_info, const void *obj);
struct StringifyFuncAndTypeInfo
{
    StringifyFunc func;
    void *type_info;
};

struct DwarfStringify2
{
    template <typename UnderlyingT>
    struct EnumClassTypeInfo
    {
        const char *enum_name;
        std::unordered_map<UnderlyingT, const char*> valueToNameMap;
    };

    struct StructTypeInfo
    {
        struct MemberInfo
        {
            const char *name;
            size_t offset;
            StringifyFuncAndTypeInfo stringifier;
        };
        std::vector<MemberInfo> members;
    };

    template <typename UnderlyingT>
    static void EnumClass(std::ostream &out, void *type_info_, const void *val_)
    {
        const EnumClassTypeInfo<UnderlyingT> *type_info = reinterpret_cast<const EnumClassTypeInfo<UnderlyingT>*>(type_info_);

        UnderlyingT val = *(const UnderlyingT*)val_;

        constexpr bool IsSigned = std::is_signed_v<UnderlyingT>;

        auto it = type_info->valueToNameMap.find(static_cast<UnderlyingT>(val));
        if (it != type_info->valueToNameMap.end())
        {
            out << type_info->enum_name << "::" << it->second;
            return;
        }

        if constexpr (IsSigned)
        {
            if (val == (-9223372036854775807-1))
            {
                out << "static_cast<" << type_info->enum_name << ">(-9223372036854775807-1)";
            }
            else
            {
                out << "static_cast<" << type_info->enum_name << ">(" << (int64_t)val << ")";
            }
        }
        else
        {
            if (val > 9223372036854775807)
            {
                out << "static_cast<" << type_info->enum_name << ">(" << (uint64_t)val << "ull)";
            }
            else
            {
                out << "static_cast<" << type_info->enum_name << ">(" << (uint64_t)val << ")";
            }
        }
    }

    static void Struct(std::ostream &out, void *type_info_, const void *val_)
    {
        const StructTypeInfo *type_info = reinterpret_cast<const StructTypeInfo*>(type_info_);

        (void)val_;
        out << "{";
        bool need_comma = false;
        for (const auto &m : type_info->members)
        {
            if (need_comma) out << ", ";
            out << "." << m.name << "=";

            m.stringifier.func(out, m.stringifier.type_info, (const void*)((const char *)val_ + m.offset));

            need_comma = true;
        }
        out << "}";
    }
};

// Manages mapping of dwarf type refs to their relevant stringify functions and data
struct LibReprGlobalCache
{
    using DwarfLocation = std::pair<uint32_t, uint32_t>; // cu_idx, cu_die_offset

    std::map<DwarfLocation, StringifyFuncAndTypeInfo> stringifiers;

    template <typename UnderlyingT>
    StringifyFuncAndTypeInfo loadEnumStringify(DIEAccessor die)
    {
        constexpr bool IsSigned = std::is_signed_v<UnderlyingT>;

        auto type_info = std::make_unique<DwarfStringify2::EnumClassTypeInfo<UnderlyingT>>();

        type_info->enum_name = die.getCStringView(DwarfAttr::Name).value().data();
        if (die.has_children())
        {
            ++die;
            for (; die.tag() != DwarfTag::None; ++die)
            {
                if (die.tag() != DwarfTag::Enumerator) throw std::runtime_error("Invalid dwarf");

                UnderlyingT value;
                if constexpr (IsSigned)
                {
                    value = die.getSigned(DwarfAttr::ConstValue).value();
                }
                else
                {
                    value = die.getUnsigned(DwarfAttr::ConstValue).value();
                }

                type_info->valueToNameMap[value] = die.getCStringView(DwarfAttr::Name).value().data();
            }
        }

        StringifyFuncAndTypeInfo res;
        res.func = DwarfStringify2::EnumClass<UnderlyingT>;
        res.type_info = static_cast<void*>(type_info.release());
        return res;
    }

    void loadStructStringifyAppendMembers(DwarfStringify2::StructTypeInfo &type_info, DebugDataLoader &loader, size_t cu_idx, DIEAccessor die, size_t offset_base)
    {
        int depth = 0;
        if (die.has_children())
        {
            ++depth;
            ++die;
            for (; ; ++die)
            {
                if (depth == 1 && die.tag() == DwarfTag::Inheritance)
                {
                    DIEAccessor baseClassDie = loader.loadCompilationUnitDie(cu_idx, die.getOffset(DwarfAttr::Type).value());
                    loadStructStringifyAppendMembers(type_info, loader, cu_idx, baseClassDie, offset_base + die.getUnsigned(DwarfAttr::DataMemberLocation).value());
                }
                else if (depth == 1 && die.tag() == DwarfTag::Member)
                {
                    auto &member = type_info.members.emplace_back();
                    member.name = die.getCStringView(DwarfAttr::Name)->data();
                    member.offset = offset_base + die.getUnsigned(DwarfAttr::DataMemberLocation).value();
                    member.stringifier = loadStringify(loader, cu_idx, die.getOffset(DwarfAttr::Type).value());
                }

                if (die.has_children())
                {
                    ++depth;
                }
                else if (die.tag() == DwarfTag::None)
                {
                    --depth;
                    if (depth == 0)
                    {
                        break;
                    }
                }
            }
        }
    }

    StringifyFuncAndTypeInfo loadStructStringify(DebugDataLoader &loader, size_t cu_idx, DIEAccessor die)
    {
        auto type_info = std::make_unique<DwarfStringify2::StructTypeInfo>();
        loadStructStringifyAppendMembers(*type_info, loader, cu_idx, die, 0);

        StringifyFuncAndTypeInfo res;
        res.func = DwarfStringify2::Struct;
        res.type_info = static_cast<void*>(type_info.release());
        return res;
    }

    StringifyFuncAndTypeInfo loadBaseStringify(DIEAccessor die)
    {
        StringifyFuncAndTypeInfo res = {};

        uint64_t encoding = die.getUnsigned(DwarfAttr::Encoding).value();
        uint64_t byteSize = die.getUnsigned(DwarfAttr::ByteSize).value();

        switch (encoding)
        {
        case 4: // float
            if (byteSize == 4)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const float*)val;       }; return res; }
            if (byteSize == 8)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const double*)val;      }; return res; }
            if (byteSize == 16) { res.func = [](std::ostream &out, void *, const void *val) { out << *(const long double*)val; }; return res; }
            break;
        case 5: // signed
        case 6: // signed char
            if (byteSize == 1)  { res.func = [](std::ostream &out, void *, const void *val) { out << static_cast<int32_t>(*(const int8_t*)val); }; return res; }
            if (byteSize == 2)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const int16_t*)val;      }; return res; }
            if (byteSize == 4)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const int32_t*)val;      }; return res; }
            if (byteSize == 8)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const int64_t*)val;      }; return res; }
            break;
        case 7: // unsigned
        case 8: // unsigned char
            if (byteSize == 1)  { res.func = [](std::ostream &out, void *, const void *val) { out << static_cast<uint32_t>(*(const uint8_t*)val); }; return res; }
            if (byteSize == 2)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const uint16_t*)val;      }; return res; }
            if (byteSize == 4)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const uint32_t*)val;      }; return res; }
            if (byteSize == 8)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const uint64_t*)val;      }; return res; }
            break;
        case 16: // DW_ATE_UTF
            if (byteSize == 1)  { res.func = [](std::ostream &out, void *, const void *val) { out << static_cast<uint32_t>(*(const uint8_t*)val); }; return res; }
            if (byteSize == 2)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const uint16_t*)val;      }; return res; }
            if (byteSize == 4)  { res.func = [](std::ostream &out, void *, const void *val) { out << *(const uint32_t*)val;      }; return res; }
            break;
        }

        std::cerr << "encoding=" << encoding << ", byteSize=" << byteSize << " type=" << die.getCStringView(DwarfAttr::Name).value() << "\n";

        res.func = [](std::ostream &out, void *, const void *)
        {
            out << "???";
        };
        res.type_info = nullptr;
        return res;
    }

    StringifyFuncAndTypeInfo loadStringify(DebugDataLoader &loader, size_t cu_idx, uint64_t typeDieOffset)
    {
        DwarfLocation loc(cu_idx, typeDieOffset);
        if (auto it = stringifiers.find(loc); it != stringifiers.end()) {
            return it->second;
        }

        DIEAccessor acc = loader.loadCompilationUnitDie(cu_idx, typeDieOffset);
        std::optional<StringifyFuncAndTypeInfo> res;
        switch (acc.tag())
        {
        case DwarfTag::EnumerationType:
        {
            // GCC has encoding/byteSize in enum type, but clang only has them on linked primitive
            DIEAccessor primitiveDie = loader.loadCompilationUnitDie(cu_idx, acc.getOffset(DwarfAttr::Type).value());

            // TODO extract this typedef following logic to a function
            while (primitiveDie.tag() == DwarfTag::Typedef)
            {
                primitiveDie = loader.loadCompilationUnitDie(cu_idx, primitiveDie.getOffset(DwarfAttr::Type).value());
            }

            uint64_t encoding = primitiveDie.getUnsigned(DwarfAttr::Encoding).value();
            uint64_t byteSize = primitiveDie.getUnsigned(DwarfAttr::ByteSize).value();

            // GCC uses encoding=5,7, clang uses 6,8
            bool signed_ = (encoding == 5 || encoding == 6);
            bool unsigned_ = (encoding == 7 || encoding == 8);
            if (signed_   && byteSize == 1) { res = loadEnumStringify<int8_t  >(acc); break; }
            if (signed_   && byteSize == 2) { res = loadEnumStringify<int16_t >(acc); break; }
            if (signed_   && byteSize == 4) { res = loadEnumStringify<int32_t >(acc); break; }
            if (signed_   && byteSize == 8) { res = loadEnumStringify<int64_t >(acc); break; }
            if (unsigned_ && byteSize == 1) { res = loadEnumStringify<uint8_t >(acc); break; }
            if (unsigned_ && byteSize == 2) { res = loadEnumStringify<uint16_t>(acc); break; }
            if (unsigned_ && byteSize == 4) { res = loadEnumStringify<uint32_t>(acc); break; }
            if (unsigned_ && byteSize == 8) { res = loadEnumStringify<uint64_t>(acc); break; }
            break;
        }
        case DwarfTag::StructureType:
        case DwarfTag::ClassType:
        {
            res = loadStructStringify(loader, cu_idx, acc);
            break;
        }
        case DwarfTag::BaseType:
        {
            res = loadBaseStringify(acc);
            break;
        }
        case DwarfTag::Typedef:
        {
            res = loadStringify(loader, cu_idx, acc.getOffset(DwarfAttr::Type).value());
            break;
        }
        case DwarfTag::PointerType:
        {
            // TODO function ptrs?
            // TODO maybe make char* etc to print the string etc
            res.emplace();
            res->func = [](std::ostream &out, void *, const void *val)
            {
                uint64_t addr = *(const uint64_t*)val;
                if (addr == 0)
                {
                    out << "nullptr";
                }
                else
                {
                    std::stringstream ss;
                    ss << "0x" << std::hex << std::setw(16) << std::setfill('0') << addr;
                    out << ss.str();
                }
            };
            res->type_info = nullptr;
            break;
        }
        default:
            break;
        }

        if (!res) {
            std::cerr << "Can't stringify type at 0x" << std::hex << typeDieOffset << std::dec << " " << acc.tag() << "\n";
            res.emplace();
            res->func = [](std::ostream &out, void *, const void *)
            {
                out << "???";
            };
            res->type_info = nullptr;
        }

        stringifiers[loc] = *res;
        return *res;
    }

    uint64_t findGlobalOffset(DebugDataLoader &loader)
    {
        // Find a position of a well known global variable and compare it to its debug data
        // Use that offset for any global variables later, to make this work with PIE.
        static volatile bool librepr_global_offset_marker__;
        uint64_t dwarfLocation = -1;
        uint64_t realLocation = reinterpret_cast<uint64_t>(&librepr_global_offset_marker__);

        for (size_t i = 0; i < loader.num_compilation_units(); ++i)
        {
            for (DIEAccessor acc = loader.loadCompilationUnitRootDie(i); acc; ++acc)
            {
                if (acc.tag() == DwarfTag::Variable)
                {
                    if (acc.getCStringView(DwarfAttr::Name) == "librepr_global_offset_marker__")
                    {
                        dwarfLocation = acc.getOffset(DwarfAttr::Location).value();
                        return realLocation - dwarfLocation;
                    }
                }
            }
        }

        // TODO fallback, not fail
        throw std::runtime_error("Unable to find librepr_global_offset_marker__, did you enable debug data?");
    }

    void run(DebugDataLoader &loader)
    {
        uint64_t globalOffset = findGlobalOffset(loader);

        for (size_t i = 0; i < loader.num_compilation_units(); ++i)
        {
            std::optional<DIEAccessor> ttypeDie, fnVarDie;
            auto check = [&]()
            {
                if (ttypeDie && fnVarDie)
                {
                    uint64_t typeDieOffset = ttypeDie->getOffset(DwarfAttr::Type).value();

                    uint64_t dwarfOffset = fnVarDie->getOffset(DwarfAttr::Location).value();
                    StringifyFuncAndTypeInfo *fnti = (StringifyFuncAndTypeInfo*)(globalOffset + dwarfOffset);
                    *fnti = loadStringify(loader, i, typeDieOffset);

                    ttypeDie.reset();
                    fnVarDie.reset();
                }
            };

            for (DIEAccessor acc = loader.loadCompilationUnitRootDie(i); acc; ++acc)
            {
                switch (acc.tag())
                {
                case DwarfTag::Subprogram:
                    ttypeDie.reset();
                    fnVarDie.reset();
                    break;
                case DwarfTag::TemplateTypeParameter:
                    if (acc.getCStringView(DwarfAttr::Name) == "librepr_T__")
                    {
                        ttypeDie = acc;
                        check();
                    }
                    break;
                case DwarfTag::Variable:
                {
                    if (acc.getCStringView(DwarfAttr::Name) == "librepr_stringify_fnti__")
                    {
                        fnVarDie = acc;
                        check();
                    }
                    break;
                }
                default:
                    break;
                }
            }
        }
    }

    static
    void InitializeAll(std::ostream &out, void *type_info, const void *obj)
    {
        StringifyFuncAndTypeInfo *fnti = reinterpret_cast<StringifyFuncAndTypeInfo*>(type_info);

        static std::mutex gMut;
        static std::shared_ptr<DebugDataLoader> gLoader;
        static std::shared_ptr<LibReprGlobalCache> gCache;

        std::lock_guard<std::mutex> guard(gMut);
        if (!gLoader)
        {
            gLoader = std::make_shared<DebugDataLoader>();
            gLoader->loadFile("/proc/self/exe");
            gCache = std::make_shared<LibReprGlobalCache>();
            gCache->run(*gLoader);
        }

        if (fnti->func == InitializeAll)
        {
            // TODO implement fallback printers?
            fnti->func = [](std::ostream &out, void *, const void *)
            {
                out << "???";
            };
            fnti->type_info = nullptr;
        }

        fnti->func(out, fnti->type_info, obj);
    }
};



} // namespace librepr::_internal_v3




namespace librepr {



template <typename librepr_T__>
inline
std::string repr(const librepr_T__ &val)
{
    using namespace _internal_v3;

    static StringifyFuncAndTypeInfo librepr_stringify_fnti__ = {
        LibReprGlobalCache::InitializeAll,
        reinterpret_cast<void*>(&librepr_stringify_fnti__)
    };

    std::stringstream ss;
    librepr_stringify_fnti__.func(ss, librepr_stringify_fnti__.type_info, reinterpret_cast<const void*>(&val));
    return ss.str();
}


} // namespace librepr


#endif // LIBREPR_HPP_
