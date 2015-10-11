#ifndef Plugin_Plugin_INCLUDED
#define Plugin_Plugin_INCLUDED

#if defined(_WIN32)// && defined(HYPHA_DLL)
#if defined(Plugin_EXPORTS)
#define Plugin_API __declspec(dllexport)
#else
#define Plugin_API __declspec(dllimport)
#endif
#endif

#if !defined(Plugin_API)
#if !defined(HYPHA_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
#define Plugin_API __attribute__ ((visibility ("default")))
#else
#define Plugin_API
#endif
#endif

#if defined(_MSC_VER)
#if !defined(HYPHA_NO_AUTOMATIC_LIBS) && !defined(Plugin_EXPORTS)
#pragma comment(lib, "HyphaPlugin" HYPHA_LIB_SUFFIX)
#endif
#endif


#endif // Plugin_Plugin_INCLUDED
