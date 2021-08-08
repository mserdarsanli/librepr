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


namespace librepr::_internal_v1 {



enum class DwarfTag : uint16_t {
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

enum class DwarfAttr : uint16_t {
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
    LoUser = 8192,
    HiUser = 16383,
};

enum class DwarfForm : uint16_t {
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

    const char* str() { const char *res = (const char*)_it; _it += strlen(res) + 1; return res; }

    const uint8_t *_it;
};

struct AttrNameAndForm
{
    DwarfAttr name;
    DwarfForm form;
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
static_assert(sizeof(AbbrevEntry) == 6);

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

                if (attr_name == DwarfAttr::None && attr_form == DwarfForm::None) {
                    break;
                }

                if (attr_form == DwarfForm::ImplicitConst)
                {
                    it.leb128s(); // Skip implicit cont valu from dwarf5
                }

                _abbrev_data_unpacked.resize(_abbrev_data_unpacked.size() + sizeof(AttrNameAndForm));
                entry = reinterpret_cast<AbbrevEntry*>(_abbrev_data_unpacked.data() + entry_offset);
                entry->attrs[entry->num_attrs].name = attr_name;
                entry->attrs[entry->num_attrs].form = attr_form;
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

        if (elf->e_type != ET_EXEC)
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
            return RawDwarfData::LoadELF(buf); // TODO prevent recursion
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
    const uint8_t *_attrData[27]; // TODO make this a small_vector

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

    std::optional<uint64_t> getOffset(DwarfAttr attr)
    {
        size_t idx = _abbrev->findAttrIdxByName(attr);
        if (idx == (size_t)-1)
        {
            return std::nullopt;
        }

        switch (_abbrev->attrs[idx].form)
        {
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
            curDie._loader = this;
            curDie._cu = cu;
            curDie._rangeEnd = rdd.debug_info.data() + cu->_offset + cu->_size;
            curDie._abbrev = &abbrev;
            curDie._nextDieBegin = it._it;
            return curDie;
        }

        DIEAccessor curDie;
        curDie._loader = this;
        curDie._cu = cu;
        curDie._rangeEnd = rdd.debug_info.data() + cu->_offset + cu->_size;
        curDie._abbrev = &abbrev;
        if (abbrev.num_attrs > 27) throw std::runtime_error("TODO larger than small_vector size");

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

struct EnumClassPayload;

template <typename UnderlyingT>
struct EnumClassPayloadWith
{
    void (**stringify_fn_ptr)(const EnumClassPayload *, std::ostream &, const void *);
    void (*no_debugdata_fn)(const EnumClassPayload *, std::ostream &, const void *);
    const char *enum_name;
    std::unordered_map<UnderlyingT, const char*> valueToNameMap;
};

constexpr size_t MaxEnumClassPayloadSize = std::max(std::initializer_list<size_t>{
    sizeof(EnumClassPayloadWith<int8_t>),
    sizeof(EnumClassPayloadWith<uint8_t>),
    sizeof(EnumClassPayloadWith<int16_t>),
    sizeof(EnumClassPayloadWith<uint16_t>),
    sizeof(EnumClassPayloadWith<int32_t>),
    sizeof(EnumClassPayloadWith<uint32_t>),
    sizeof(EnumClassPayloadWith<int64_t>),
    sizeof(EnumClassPayloadWith<uint64_t>)
});

struct EnumClassPayload
{
    void (**stringify_fn_ptr)(const EnumClassPayload *, std::ostream &, const void *);
    void (*no_debugdata_fn)(const EnumClassPayload *, std::ostream &, const void *);

    union {
        max_align_t align;
        char buf[MaxEnumClassPayloadSize - 16];
    };
};
static_assert(sizeof(EnumClassPayload) == MaxEnumClassPayloadSize);


struct DwarfStringify
{
    template <typename UnderlyingT>
    static void EnumClass(const EnumClassPayload *payload_, std::ostream &out, const void *val_)
    {
        const EnumClassPayloadWith<UnderlyingT> *payload = reinterpret_cast<const EnumClassPayloadWith<UnderlyingT>*>(payload_);

        UnderlyingT val = *(const UnderlyingT*)val_;

        constexpr bool IsSigned = std::is_signed_v<UnderlyingT>;

        auto it = payload->valueToNameMap.find(static_cast<UnderlyingT>(val));
        if (it != payload->valueToNameMap.end())
        {
            out << payload->enum_name << "::" << it->second;
            return;
        }

        if constexpr (IsSigned)
        {
            if (val == (-9223372036854775807-1))
            {
                out << "static_cast<" << payload->enum_name << ">(-9223372036854775807-1)";
            }
            else
            {
                out << "static_cast<" << payload->enum_name << ">(" << (int64_t)val << ")";
            }
        }
        else
        {
            if (val > 9223372036854775807)
            {
                out << "static_cast<" << payload->enum_name << ">(" << (uint64_t)val << "ull)";
            }
            else
            {
                out << "static_cast<" << payload->enum_name << ">(" << (uint64_t)val << ")";
            }
        }
    }

    template <typename UnderlyingT>
    static void EnumClassNoDebugData(const EnumClassPayload *, std::ostream &out, const void *val_)
    {
        UnderlyingT val = *(const UnderlyingT*)val_;

        constexpr bool IsSigned = std::is_signed_v<UnderlyingT>;

        if constexpr (IsSigned)
        {
            out << static_cast<int64_t>(val);
        }
        else
        {
            out << static_cast<uint64_t>(val);
        }
    }
};

struct TypeRef
{
    uint64_t cu_idx;
    uint64_t offset;
};

template <typename UnderlyingT>
inline void ExtractEnumClassTypeInfo(EnumClassPayloadWith<UnderlyingT> *payload, DIEAccessor &die)
{
    *payload->stringify_fn_ptr = DwarfStringify::EnumClass<UnderlyingT>;
    new (&payload->valueToNameMap) std::unordered_map<UnderlyingT, const char*>;

    constexpr bool IsSigned = std::is_signed_v<UnderlyingT>;

    payload->enum_name = die.getCStringView(DwarfAttr::Name).value().data();

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

            payload->valueToNameMap[value] = die.getCStringView(DwarfAttr::Name).value().data();
        }
    }
}

struct LibRepr
{
    static void Initialize(const EnumClassPayload *payload, std::ostream &out, const void *val)
    {
        static std::mutex gMut;
        static std::shared_ptr<DebugDataLoader> gLoader;

        std::lock_guard<std::mutex> guard(gMut);
        if (!gLoader)
        {
            gLoader = std::make_shared<DebugDataLoader>();
            gLoader->loadFile("/proc/self/exe");
        }

        bool found = false;

        for (size_t i = 0; i < gLoader->num_compilation_units(); ++i)
        {
            DIEAccessor acc = gLoader->loadCompilationUnitRootDie(i);

            TypeRef lastTypeRef;
            void (**stringify_fn_ptr)(const EnumClassPayload*, std::ostream &, const void*);
            EnumClassPayload *payload_ptr;

            auto clear = [&]()
            {
                lastTypeRef.cu_idx = -1;
                lastTypeRef.offset = -1;
                stringify_fn_ptr = nullptr;
                payload_ptr = nullptr;
            };

            auto check = [&]()
            {
                if (lastTypeRef.cu_idx != (uint64_t)-1 && stringify_fn_ptr && payload_ptr)
                {

                    // Extract type info and stuff..
                    {
                        DIEAccessor die = gLoader->loadCompilationUnitDie(lastTypeRef.cu_idx, lastTypeRef.offset);

                        if (die.tag() != DwarfTag::EnumerationType) throw std::runtime_error("Invalid dwarf");
                        // TODO check DW_AT_enum_class

                        // GCC has encoding/byteSize in enum type, but clang only has them on linked primitive
                        DIEAccessor primitiveDie = gLoader->loadCompilationUnitDie(lastTypeRef.cu_idx, die.getOffset(DwarfAttr::Type).value());
                        uint64_t encoding = primitiveDie.getUnsigned(DwarfAttr::Encoding).value();
                        uint64_t byteSize = primitiveDie.getUnsigned(DwarfAttr::ByteSize).value();

                        // GCC uses encoding=5,7, clang uses 6,8
                        bool signed_ = (encoding == 5 || encoding == 6);
                        bool unsigned_ = (encoding == 7 || encoding == 8);
                        if (signed_   && byteSize == 1) { ExtractEnumClassTypeInfo((EnumClassPayloadWith<int8_t>*)payload_ptr, die); goto done; }
                        if (signed_   && byteSize == 2) { ExtractEnumClassTypeInfo((EnumClassPayloadWith<int16_t>*)payload_ptr, die); goto done; }
                        if (signed_   && byteSize == 4) { ExtractEnumClassTypeInfo((EnumClassPayloadWith<int32_t>*)payload_ptr, die); goto done; }
                        if (signed_   && byteSize == 8) { ExtractEnumClassTypeInfo((EnumClassPayloadWith<int64_t>*)payload_ptr, die); goto done; }
                        if (unsigned_ && byteSize == 1) { ExtractEnumClassTypeInfo((EnumClassPayloadWith<uint8_t>*)payload_ptr, die); goto done; }
                        if (unsigned_ && byteSize == 2) { ExtractEnumClassTypeInfo((EnumClassPayloadWith<uint16_t>*)payload_ptr, die); goto done; }
                        if (unsigned_ && byteSize == 4) { ExtractEnumClassTypeInfo((EnumClassPayloadWith<uint32_t>*)payload_ptr, die); goto done; }
                        if (unsigned_ && byteSize == 8) { ExtractEnumClassTypeInfo((EnumClassPayloadWith<uint64_t>*)payload_ptr, die); goto done; }

                        throw std::runtime_error("Not found encoding/byteSize");
                        done:
                            ;
                    }

                    clear();
                }
            };

            clear();
            while (acc) {
                if (acc.tag() == DwarfTag::TemplateTypeParameter && acc.getCStringView(DwarfAttr::Name) == "librepr_T__")
                {
                    lastTypeRef = {i, acc.getOffset(DwarfAttr::Type).value()};
                    check();
                }
                if (acc.tag() == DwarfTag::Variable && acc.getCStringView(DwarfAttr::Name) == "librepr_stringify_fn__")
                {
                    uint64_t loc = acc.getOffset(DwarfAttr::Location).value();
                    stringify_fn_ptr = (void (**)(const EnumClassPayload*, std::ostream &, const void*))loc;
                    check();
                }
                if (acc.tag() == DwarfTag::Variable && acc.getCStringView(DwarfAttr::Name) == "librepr_stringify_fn_payload__")
                {
                    uint64_t loc = acc.getOffset(DwarfAttr::Location).value();
                    payload_ptr = (EnumClassPayload*)loc;
                    if (payload_ptr == payload)
                    {
                        found = true;
                    }
                    check();
                }

                ++acc;
            }
        }

        if (!found)
        {
            // No debug data..
            (*payload->stringify_fn_ptr) = payload->no_debugdata_fn;
        }

        // Recall repr after initialization
        (*payload->stringify_fn_ptr)(payload, out, val);
    }
};


} // namespace librepr::_internal_v1




namespace librepr {


template <typename librepr_T__>
inline std::string repr(const librepr_T__ &val)
{
    using namespace _internal_v1;

    static void (*librepr_stringify_fn__)(const EnumClassPayload *, std::ostream &, const void *) = LibRepr::Initialize;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    static EnumClassPayload librepr_stringify_fn_payload__ = { &librepr_stringify_fn__, DwarfStringify::EnumClassNoDebugData<std::underlying_type_t<librepr_T__>> };
#pragma GCC diagnostic pop

    std::stringstream ss;
    librepr_stringify_fn__(&librepr_stringify_fn_payload__, ss, (const void*)&val);
    return ss.str();
}


} // namespace librepr


#endif // LIBREPR_HPP_
