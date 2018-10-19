#ifndef _LIBDUNGEON_EXPORT_H
#define _LIBDUNGEON_EXPORT_H

#ifdef LIBDUNGEON_EXPORTS
	#define LIBDUNGEON_API __declspec(dllexport)
#else
	#ifdef LIBDUNGEON_STATIC
		#define LIBDUNGEON_API
	#else
		#define LIBDUNGEON_API __declspec(dllimport)
	#endif
#endif

#endif // _LIBDUNGEON_EXPORT_H