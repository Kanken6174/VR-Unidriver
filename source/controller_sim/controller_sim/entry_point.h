/**
* @author Valve corporation
* @brief defines the HMD_DLL_EXPORT/IMPORT types which serve as entry points for the DLL
* @version 0.1
* @date 16/12/2021
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