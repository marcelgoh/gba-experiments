
//{{BLOCK(ahoy)

//======================================================================
//
//	ahoy, 512x512@4, 
//	+ palette 256 entries, not compressed
//	+ 276 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 8832 + 8192 = 17536
//
//	Time-stamp: 2025-12-13, 16:44:44
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_AHOY_H
#define GRIT_AHOY_H

#define ahoyTilesLen 8832
extern const unsigned int ahoyTiles[2208];

#define ahoyMapLen 8192
extern const unsigned short ahoyMap[4096];

#define ahoyPalLen 512
extern const unsigned short ahoyPal[256];

#endif // GRIT_AHOY_H

//}}BLOCK(ahoy)
