
//{{BLOCK(walker)

//======================================================================
//
//	walker, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 2 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 64 + 2048 = 2624
//
//	Time-stamp: 2025-12-20, 16:49:45
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_WALKER_H
#define GRIT_WALKER_H

#define walkerTilesLen 64
extern const unsigned int walkerTiles[16];

#define walkerMapLen 2048
extern const unsigned short walkerMap[1024];

#define walkerPalLen 512
extern const unsigned short walkerPal[256];

#endif // GRIT_WALKER_H

//}}BLOCK(walker)
