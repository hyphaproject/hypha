#ifndef Core_Core_INCLUDED
#define Core_Core_INCLUDED

#if defined(_WIN32)// && defined(HYPHA_DLL)
#if defined(Core_EXPORTS)
#define Core_API __declspec(dllexport)
#else
#define Core_API __declspec(dllimport)
#endif
#endif

#if !defined(Core_API)
#if !defined(HYPHA_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
#define Core_API __attribute__ ((visibility ("default")))
#else
#define Core_API
#endif
#endif

#if defined(_MSC_VER)
#if !defined(HYPHA_NO_AUTOMATIC_LIBS) && !defined(Utils_EXPORTS)
#pragma comment(lib, "HyphaCore" HYPHA_LIB_SUFFIX)
#endif
#endif


#endif // Core_Core_INCLUDED
