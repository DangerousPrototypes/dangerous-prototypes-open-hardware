#ifndef DP_LCD_FT232_H
#define DP_LCD_FT232_H

#ifndef DLL_EXPORT
#define DLL_EXPORT(type) extern "C" __declspec(dllexport) type __stdcall
#endif

#define OK  1

typedef unsigned char  LCDS_BYTE;
typedef unsigned short LCDS_WORD;
typedef unsigned char  LCDS_BOOL;

#endif
