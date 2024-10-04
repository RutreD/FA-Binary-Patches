#pragma once
#include <cstdint>
#include <type_traits>

#define SHARED extern "C"

#define GPtr(addr, type) (*(type *)addr)

#define WDecl(addr, type) ((type) * (uintptr_t *)addr)
#define CSTR(NAME) extern const char NAME[]

#define VALIDATE_SIZE(struc, size)                                             \
  static_assert(sizeof(struc) == size, "Invalid structure size of " #struc);

#define g_CSimDriver GPtr(0x10C4F50, CSimDriver *)
#define g_SWldSessionInfo GPtr(0x10C4F58, SWldSessionInfo *)
#define g_CWldSession GPtr(0x10A6470, CWldSession *)
#define g_Sim GPtr(0x10A63F0, Sim *)
#define g_EntityCategoryTypeInfo GPtr(0x10C6E70, EntityCategoryTypeInfo *)
#define g_CAiBrainTypeInfo GPtr(0x10C6FA0, CAiBrainTypeInfo *)
#define g_CUIManager GPtr(0x10A6450, CUIManager *)
#define g_EngineStats GPtr(0x10A67B8, EngineStats *)
#define g_WRenViewport GPtr(0x10C7C28, WRenViewport *)
#define g_ConsoleLuaState GPtr(0x10A6478, LuaState *)
#define g_Device GPtr(0x0F8E284, Device *)

extern int ui_ProgressBarColor asm("0x0F57BB8");
extern float ui_SelectTolerance asm("0x0F57A90");
extern float ui_ExtractSnapTolerance asm("0x0F57A94");
extern bool ui_DisableCursorFixing asm("0x10A6464");
extern bool ui_RenderIcons asm("0x0F57B27");
extern bool range_RenderSelected asm("0x10A640A");
extern bool range_RenderHighlighted asm("0x10A640B");
extern bool range_RenderBuild asm("0x10A6414");
extern bool d3d_WindowsCursor asm("0x10A636E");
extern bool debugSelect asm("0x10A645E");

CSTR(s_FACTORY) asm("0xE19824");
CSTR(s_EXPERIMENTAL) asm("0xE204B8");
// "%s\n  expected %d args, but got %d"
CSTR(s_ExpectedButGot) asm("0xE0A220");
// "%s\n  expected between %d and %d args, but got %d"
CSTR(s_ExpectedBetweenButGot) asm("0xE0A270");
CSTR(s_Global) asm("0xE00D90");      // "<global>"
CSTR(s_CMauiBitmap) asm("0xE37438"); // "CMauiBitmap"
// "UserUnit"
CSTR(s_UserUnit) asm("0xE4D090");
// "Expected a game object. (Did you call with '.' instead of ':'?)"
CSTR(s_ExpectedAGameObject) asm("0xE09860");
// "Game object has been destroyed"
CSTR(s_GameObjectHasBeenDestroyed) asm("0xE098A0");
// "Incorrect type of game object.  (Did you call with '.' instead of ':'?)"
CSTR(s_IncorrectTypeOfGameObject) asm("0xE098C0");
CSTR(s_UnknownColor) asm("0x00E07D14"); // "Unknown color: %s"
CSTR(s_c_object) asm("0xE016DC");       // "_c_object"
extern const int g_ExeVersion1 asm("0x876666");
extern const int g_ExeVersion2 asm("0x87612d");
extern const int g_ExeVersion3 asm("0x4d3d40");

void AbortF(wchar_t *fmt, ...) asm("0x9C4940");
int LogF(const char *fmt, ...) asm("0x937CB0");
int WarningF(const char *fmt, ...) asm("0x937D30");
int SpewF(const char *fmt, ...) asm("0x937C30");
int ConsoleLogF(const char *fmt, ...) asm("0x41C990");
int FileWrite(int fileIndex, const char *str,
              int strlen) asm("0xA9B4E6"); // index 3 is log.
bool CopyToClipboard(const wchar_t *str) asm("0x4F2730");
void *shi_new(size_t size) asm("0xA825B9");

extern "C" {
void *realloc(void *ptr, size_t new_size) asm("0x957B00");
void *malloc(size_t size) asm("0x958B20");
void free(void *ptr) asm("0x958C40");
size_t msize(void *memblock) asm("0x957EA0");
void *calloc(size_t num, size_t size) asm("0x957AB0");
void *memset(void *dest, int ch, size_t count) asm("0xA89110");
void *memcpy(void *dest, const void *src, size_t count) asm("0xA89190");
size_t strlen(const char *str) asm("0xA94450");
int strcmp(const char *str1, const char *str2) asm("0xAA549E");
int sprintf_s(char *Buffer, size_t BufferCount, const char *Format,
              ...) asm("0xA82F32");
float sqrtf(float) asm("0x452FC0");
}
#define GetModuleHandleA                                                       \
  WDecl(0xC0F378, __stdcall void *(*)(const char *lpLibFileName))
#define GetProcAddress                                                         \
  WDecl(0xC0F48C, __stdcall void *(*)(void *hModule, const char *lpProcName))
#define GetCurrentProcess WDecl(0xC0F58C, __stdcall void *(*)())

#define QueryPerformanceCounter WDecl(0xC0F470, __stdcall bool (*)(int64_t *))
#define QueryPerformanceFrequency WDecl(0xC0F46C, __stdcall bool (*)(int64_t *))

#define DebugLog(_s) LogF("%s", (_s))

template <typename T> struct basic_string;
using string = basic_string<char>;
using wstring = basic_string<wchar_t>;

wstring *__cdecl wstring_copy_ctor(wstring *ws, const char *s) asm("0x938720");
string *__thiscall InitString(string *this_, const char *str) asm("0x405550");
string *__thiscall AssignString(string *this_, const char *str,
                                size_t size) asm("0x4059E0");

int __thiscall wstring_dtor(wstring *ws) asm("0x00431390");
void __thiscall string_dtor(string *ws) asm("0x00402370");

#define SSO_bytes 0x10ul
template <typename T> struct basic_string {
  static constexpr uint32_t sso_size = SSO_bytes / sizeof(T);
  uint32_t ptr; // ?
  union {
    T str[sso_size]; // data
    T *_data;        // pointer to data
  };
  uint32_t strLen;
  uint32_t capacity; // capacity?

  basic_string() {
    ptr = 0;
    str[0] = T(0);
    strLen = 0;
    capacity = sso_size - 1;
  }

  basic_string(const char *s) {
    if constexpr (std::is_same_v<char, T>)
      InitString(this, s);
    else if constexpr (std::is_same_v<wchar_t, T>)
      wstring_copy_ctor(this, s);
    else
      static_assert(false, "Unknown type T.");
  }

  inline const T *data() { return capacity < sso_size ? &str : _data; }

  inline void clear() {
    if (capacity >= sso_size) {
      free(data());
    }
    ptr = 0;
    str[0] = T(0);
    strLen = 0;
    capacity = sso_size - 1;
  }

  ~basic_string() { clear(); }
};

VALIDATE_SIZE(string, 0x1C)
static_assert(string::sso_size == 0x10);
VALIDATE_SIZE(wstring, 0x1C)
static_assert(wstring::sso_size == 0x8);

template <typename T> struct Result {
  T *object = nullptr;
  const char *reason = nullptr;

  constexpr static Result<T> Fail(const char *reason) {
    return {nullptr, reason};
  }
  constexpr static Result<T> Success(void *data) {
    return {(T *)data, nullptr};
  }

  inline bool IsFail() { return reason != nullptr; }
};