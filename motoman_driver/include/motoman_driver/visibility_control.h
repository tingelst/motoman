#ifndef MOTOMAN_DRIVER__VISIBILITY_CONTROL_H_
#define MOTOMAN_DRIVER__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MOTOMAN_DRIVER_EXPORT __attribute__ ((dllexport))
    #define MOTOMAN_DRIVER_IMPORT __attribute__ ((dllimport))
  #else
    #define MOTOMAN_DRIVER_EXPORT __declspec(dllexport)
    #define MOTOMAN_DRIVER_IMPORT __declspec(dllimport)
  #endif
  #ifdef MOTOMAN_DRIVER_BUILDING_LIBRARY
    #define MOTOMAN_DRIVER_PUBLIC MOTOMAN_DRIVER_EXPORT
  #else
    #define MOTOMAN_DRIVER_PUBLIC MOTOMAN_DRIVER_IMPORT
  #endif
  #define MOTOMAN_DRIVER_PUBLIC_TYPE MOTOMAN_DRIVER_PUBLIC
  #define MOTOMAN_DRIVER_LOCAL
#else
  #define MOTOMAN_DRIVER_EXPORT __attribute__ ((visibility("default")))
  #define MOTOMAN_DRIVER_IMPORT
  #if __GNUC__ >= 4
    #define MOTOMAN_DRIVER_PUBLIC __attribute__ ((visibility("default")))
    #define MOTOMAN_DRIVER_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MOTOMAN_DRIVER_PUBLIC
    #define MOTOMAN_DRIVER_LOCAL
  #endif
  #define MOTOMAN_DRIVER_PUBLIC_TYPE
#endif

#endif  // MOTOMAN_DRIVER__VISIBILITY_CONTROL_H_
