#ifndef Utils_Utils_INCLUDED
#define Utils_Utils_INCLUDED

#if defined(_WIN32)// && defined(HYPHA_DLL)
#if defined(Utils_EXPORTS)
#define Utils_API __declspec(dllexport)
#else
#define Utils_API __declspec(dllimport)
#endif
#endif

#if !defined(Utils_API)
#if !defined(HYPHA_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
#define Utils_API __attribute__ ((visibility ("default")))
#else
#define Utils_API
#endif
#endif

#if defined(_MSC_VER)
#if !defined(HYPHA_NO_AUTOMATIC_LIBS) && !defined(Utils_EXPORTS)
#pragma comment(lib, "HyphaUtils" HYPHA_LIB_SUFFIX)
#endif
#endif


#endif // Utils_Utils_INCLUDED
