#ifndef HD_CODE_STATS_PERM_H
#define HD_CODE_STATS_PERM_H

struct LevelStats {
    /* 0x00 */ u32 money; /// destruction damage done in level; displayed as money :)
    /* 0x04 */ s32 timeCode; /// time in level; in tenths of seconds. 1313 is 1:13.3 (1 min, 13 seconds, 300ms)
    /* 0x08 */ u8 buildingsDestroyed; /// how many buildings were destroyed in the level
    /* 0x09 */ u8 civiliansRescued; /// how many civilians were found in the level
    /* 0x0A */ u8 coin; // TODO: what is this? the medal?
    /* 0x0B */ u8 bdn; // TODO: what is this?
    /* 0x0C */ u16 rdusFound; /// how many rdus got activated in the level
    /* 0x0E */ u16 padE;
};

extern struct LevelStats g_statsOld;
extern struct LevelStats g_statsNew;
extern struct LevelStats g_statsRes;
extern struct LevelStats g_statsRes2;

void statsCopyTo(struct LevelStats* src, struct LevelStats* dst);

#endif