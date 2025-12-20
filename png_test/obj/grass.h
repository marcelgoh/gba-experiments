
//{{BLOCK(grass)

//======================================================================
//
//	grass, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 6 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 192 + 2048 = 2752
//
//	Time-stamp: 2025-12-14, 09:59:36
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GRASS_H
#define GRIT_GRASS_H

#define grassTilesLen 192
extern const unsigned int grassTiles[48];

#define grassMapLen 2048
extern const unsigned short grassMap[1024];

#define grassPalLen 512
extern const unsigned short grassPal[256];

#endif // GRIT_GRASS_H

//}}BLOCK(grass)
