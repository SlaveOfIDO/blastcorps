#ifndef GAME_STATES_H
#define GAME_STATES_H

#define STATE_NINTENDO_INTRO       (1ULL << 4)  // 0x10
#define STATE_RARE_INTRO           (1ULL << 5)  // 0x20
#define STATE_PRELEVEL_STATS       (1ULL << 7)  // 0x80
#define STATE_IN_LEVEL             (1ULL << 11) // 0x800
#define STATE_WORLD_VIEW           (1ULL << 14) // 0x4000
#define STATE_ENTER_NAME           (1ULL << 18) // 0x40000
#define STATE_PROMOTION_SCREEN     (1ULL << 30) // 0x40000000
#define STATE_VEHICLE_SELECTION    (1ULL << 29) // 0x20000000
#define STATE_POSTLEVEL_STATS      (1ULL << 27) // 0x8000000
#define STATE_LEVELS_COMPLETED     (1ULL << 47) // 0x800000000000
#define STATE_TUTORIAL             (1ULL << 44) // 0x100000000000
#define STATE_ATTRACT_TEAM_MEMBERS (1ULL << 48) // 0x1000000000000

#endif
