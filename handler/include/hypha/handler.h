#ifndef Handler_Handler_INCLUDED
#define Handler_Handler_INCLUDED

#if defined(_WIN32)// && defined(HYPHA_DLL)
#if defined(Handler_EXPORTS)
#define Handler_API __declspec(dllexport)
#else
#define Handler_API __declspec(dllimport)
#endif
#endif

#if !defined(Handler_API)
#if !defined(HYPHA_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
#define Handler_API __attribute__ ((visibility ("default")))
#else
#define Handler_API
#endif
#endif

#if defined(_MSC_VER)
#if !defined(HYPHA_NO_AUTOMATIC_LIBS) && !defined(Handler_EXPORTS)
#pragma comment(lib, "HyphaHandler" HYPHA_LIB_SUFFIX)
#endif
#endif


#endif // Handler_Handler_INCLUDED
