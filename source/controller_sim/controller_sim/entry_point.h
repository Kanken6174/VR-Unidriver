/**
* Définitions du point d'entrée, steamVR attend à ce que
* la fonction ayant le type de retour HMD_DLL_EXPORT soit
* la fonction HmdDriverFactory, qui sert donc de point d'entrée
*/

#if defined(_WIN32)
#define HMD_DLL_EXPORT extern "C" __declspec( dllexport )
#define HMD_DLL_IMPORT extern "C" __declspec( dllimport )
#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)	//cas apple / linux
#define HMD_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#define HMD_DLL_IMPORT extern "C" 
#else
#error "Unsupported Platform."
#endif

#define FUNCTION_POINTER void*