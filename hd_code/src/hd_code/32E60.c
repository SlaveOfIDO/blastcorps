#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

// Proposed file name: comms.c
//
// This file is the "communications window" - the animated talking-head
// portrait that appears in a screen corner with a voice line and TV-static
// effects - plus the driving-skill monitor that decides when the advisor
// praises or criticizes the player. Skill samples ({speed ok, control ok,
// vehicle, time}) are recorded into a 50-entry ring buffer
// (D_8036C8D0, head/tail D_8036CB29/28, entries expire after 1000 frames);
// tallies of good/bad samples trigger "DOING REALLY WELL", "USING WRONG
// DIGGER" and "USING DIGGER INCORRECTLY" comms. The window plays 40x40
// RGBA16 face frames (id lists D_hd_code_802FBDD0..) streamed into the
// double buffer D_8036CB48, with radio-crackle static bursts via the NOISE
// combiner.

// <data>
u32 D_hd_code_802FAD50[32*32] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0A0C0E7D, 0x14171CEF, 0x14181CEF, 0x15181DF3, 0x15191DF3, 0x161A1EF3, 0x161A1FF3, 0x171B20F3, 0x191C21F3, 0x1A1E22F3, 0x1C2024F3, 0x1E2226F3, 0x212529F3, 0x24282CF3, 0x272B30F3, 0x2C3034F3, 0x303439F3, 0x363A3EF3, 0x3C3F44F3, 0x42464AF3, 0x494D51F3, 0x505458F3, 0x56595EF3, 0x555766F3, 0x5F6074F3, 0x696A81F3, 0x6D7079F3, 0x797C87F3, 0x7D7F8AF3, -0x7C78740D, -0x7874700D, 0x27282A46,
    0x0A0C0F81, 0x15191EFF, 0x16191EFF, 0x161A1FFF, 0x161A1FFF, 0x171B20FF, 0x181C21FF, 0x191D22FF, 0x1A1E23FF, 0x1C2025FF, 0x1E2227FF, 0x21252AFF, 0x24282DFF, 0x282C31FF, 0x2C3035FF, 0x31353AFF, 0x373B3FFF, 0x3D4146FF, 0x44484DFF, 0x4B4F54FF, 0x53575CFF, 0x5B5F64FF, 0x5F6368FF, 0x626475FF, 0x6C6C88FF, 0x757886FF, 0x7A7C8BFF, -0x76736A01, 0x7E7F90FF, -0x68655E01, -0x64605B01, 0x2B2C2E46,
    0x0A0C0E7D, 0x15191EFF, 0x161A1EFF, 0x161A1FFF, 0x171B1FFF, 0x171B20FF, 0x181C21FF, 0x191E22FF, 0x1B1F24FF, 0x1D2126FF, 0x1F2328FF, 0x22262BFF, 0x262A2FFF, 0x2A2E33FF, 0x2F3338FF, 0x34383DFF, 0x3A3F43FF, 0x41464AFF, 0x494D52FF, 0x51565AFF, 0x5A5E63FF, 0x63676CFF, 0x6B6F74FF, 0x717384FF, 0x787B86FF, -0x7B796601, -0x77756601, -0x72706201, -0x67645D01, -0x5D595301, -0x55524D01, 0x2F303146,
    0x0A0C0E7D, 0x202429FF, 0x2C3035FF, 0x12161BFF, 0x13171CFF, 0x1E252CFF, 0x272F38FF, 0x2A323BFF, 0x242B33FF, 0x222931FF, 0x212830FF, 0x1E242CFF, 0x1A2027FF, 0x191F25FF, 0x1C2229FF, 0x1D232AFF, 0x1E242BFF, 0x1B2127FF, 0x1B2127FF, 0x1F252CFF, 0x272D35FF, 0x2D343CFF, 0x363D46FF, 0x323942FF, 0x2E353DFF, 0x2A3139FF, 0x1C2228FF, 0x14181DFF, 0x11151AFF, 0x45494EFF, -0x47433F01, 0x30313242,
    0x0A0C0E79, 0x24282CFF, 0x565A5FFF, 0x373D44DD, 0x36404B8F, 0x38424E8C, 0x3B45518F, 0x38424E8F, 0x404B598F, 0x424E5B8F, 0x37414D8F, 0x38424E8C, 0x353F4A88, 0x333C4782, 0x353F4A82, 0x363F4B82, 0x3B455182, 0x3B444E82, 0x3E485285, 0x4A545F88, 0x646E7B8F, 0x68727E8F, 0x65707C8F, 0x646F7B8C, 0x69727E8C, 0x6C76818F, 0x5D66718F, 0x333A43B1, 0x10151AFF, 0x494E52FF, -0x39353001, 0x34353642,
    0x0A0C0E79, 0x23272CFF, 0x5B5F64FF, 0x3F4852B8, 0x333B4623, 0x2E363F23, 0x29303823, 0x2A313923, 0x30384223, 0x30384223, 0x323A4423, 0x282F3723, 0x2F384123, 0x30384123, 0x282F3823, 0x282E3623, 0x343B4423, 0x40485123, 0x49515B23, 0x4D555E23, 0x59626C23, 0x5A626D23, 0x5D656E23, 0x646B7323, 0x676E7623, 0x70788223, 0x62697223, 0x4D545E6A, 0x242A32FF, 0x4E5257FF, -0x2B272301, 0x3435363E,
    0x0A0B0E75, 0x23272CFF, 0x5F6469FF, 0x3C4550B8, 0x2E363F23, 0x262C3423, 0x282E3723, 0x2D343D23, 0x2B323B23, 0x2D343D23, 0x2B333B23, 0x2E363F23, 0x2F374123, 0x2E363F23, 0x2E364023, 0x31394323, 0x373F4923, 0x454E5823, 0x4A525C23, 0x4C545C23, 0x5C656F23, 0x5F677023, 0x656D7623, 0x6A727B23, 0x666E7723, 0x69717B23, 0x676F7823, 0x616A766A, 0x2B323BFF, 0x55595EFF, -0x1E1A1601, 0x3435363A,
    0x0A0B0E75, 0x24282DFF, 0x62676CFF, 0x44505DBB, 0x2D353F23, 0x343D4723, 0x2A313A23, 0x323A4423, 0x2F374123, 0x30394223, 0x2B323B23, 0x2D353E23, 0x353E4923, 0x31394323, 0x343E4823, 0x2D353E23, 0x363F4823, 0x424B5523, 0x515A6623, 0x5A646F23, 0x60687323, 0x60687223, 0x59606823, 0x62697323, 0x6B747F23, 0x646C7623, 0x60677123, 0x5F68746D, 0x353E47FF, 0x595D62FF, -0x120E0A01, 0x3738393A,
    0x0A0B0E75, 0x23272CFF, 0x656A6FFF, 0x3C4551BB, 0x2D343E23, 0x30384223, 0x2D353E23, 0x2B323B23, 0x2F374123, 0x30384223, 0x2A313A23, 0x29313923, 0x2E364023, 0x2F374023, 0x31394423, 0x31394323, 0x38414B23, 0x434C5723, 0x464E5823, 0x4D545E23, 0x5D667123, 0x59606923, 0x5D656E23, 0x575E6623, 0x59606923, 0x58606A23, 0x555D6723, 0x5059646D, 0x39434EFF, 0x606469FF, -0x8040101, 0x35363636,
    0x090B0D71, 0x24282DFF, 0x686D72FF, 0x414C58BE, 0x2A313A23, 0x30384223, 0x29303923, 0x2B333C23, 0x313A4423, 0x30384323, 0x2E363F23, 0x272E3623, 0x2E374123, 0x343D4823, 0x333C4723, 0x30384223, 0x30384123, 0x3E475123, 0x3E464F23, 0x4E576223, 0x525B6523, 0x545C6623, 0x59626C23, 0x4F576023, 0x49505923, 0x454D5623, 0x454D5823, 0x414A556D, 0x3A434FFF, 0x63676AFF, -0x1010001, 0x32333333,
    0x090B0D6D, 0x23272CFF, 0x6B7076FF, 0x3F4955BE, 0x323B4523, 0x2F374123, 0x2A323B23, 0x2A313A23, 0x31394323, 0x2E364023, 0x333C4723, 0x282F3823, 0x30394323, 0x343D4823, 0x353E4A23, 0x36404B23, 0x31394323, 0x39424D23, 0x343B4523, 0x363E4723, 0x3D465023, 0x39404923, 0x414A5423, 0x3B434D23, 0x333A4223, 0x333B4423, 0x2D343C23, 0x333C4671, 0x3A4450FF, 0x686B6EFF, 0x000000-1, 0x33333333,
    0x090B0D6D, 0x22262BFF, 0x6D7278FF, 0x414C58C2, 0x313A4423, 0x2F374123, 0x2C343D23, 0x2E364023, 0x272E3623, 0x30394323, 0x333C4723, 0x2C343E23, 0x2A313A23, 0x30384223, 0x36404B23, 0x36404C23, 0x31394423, 0x353E4A23, 0x333C4623, 0x2D353E23, 0x343D4823, 0x3C465323, 0x323A4423, 0x2E353E23, 0x2F374023, 0x333C4623, 0x2F374023, 0x3D475371, 0x3C4652FF, 0x686B6EFF, 0x000000-1, 0x2F2F2F2F,
    0x090A0C69, 0x22262BFF, 0x6E7379FF, 0x424C59C5, 0x29303923, 0x282F3723, 0x2F374123, 0x2C343E23, 0x31394423, 0x30384323, 0x2F384223, 0x2F384223, 0x353F4A23, 0x2F384223, 0x2F384223, 0x343D4823, 0x2E374123, 0x2F374123, 0x38424D23, 0x2E364023, 0x30384223, 0x30394223, 0x30394223, 0x31394223, 0x343D4723, 0x2C343C23, 0x333B4523, 0x3E485471, 0x3B4551FF, 0x686B6EFF, 0x000000-1, 0x2F2F2F2F,
    0x090A0C69, 0x202429FF, 0x6E7379FF, 0x3D4753C5, 0x272D3623, 0x262D3523, 0x2A323B23, 0x31394423, 0x2C343E23, 0x353E4923, 0x2E364023, 0x30384223, 0x38424D23, 0x323A4523, 0x2F374123, 0x29303923, 0x353E4923, 0x38414D23, 0x353E4923, 0x272D3523, 0x2B333C23, 0x2E363F23, 0x2A313A23, 0x2D353E23, 0x30384123, 0x353D4823, 0x323A4423, 0x3B455171, 0x3D4854FF, 0x6B6E71FF, 0x000000-1, 0x2B2B2B2B,
    0x080A0C66, 0x202429FF, 0x6E7278FF, 0x46525FC8, 0x282F3823, 0x2F384223, 0x2D353F23, 0x2F384223, 0x343D4823, 0x2E364023, 0x343E4923, 0x313A4523, 0x2E374123, 0x2F374123, 0x28303823, 0x2C343D23, 0x333C4723, 0x333C4723, 0x333C4623, 0x333B4623, 0x2F374123, 0x2E363F23, 0x36404B23, 0x2F374023, 0x323A4423, 0x31394223, 0x363E4923, 0x3E485474, 0x3F4A57FF, 0x6B6E71FF, 0x000000-1, 0x27272727,
    0x080A0B62, 0x1E2327FF, 0x6C7076FF, 0x444F5CC8, 0x2C333D23, 0x29313A23, 0x29313923, 0x262D3523, 0x2D353F23, 0x2A323B23, 0x2F384223, 0x2C333D23, 0x2E374123, 0x2F374123, 0x2D363F23, 0x333C4723, 0x2C333D23, 0x323B4523, 0x323B4523, 0x333C4623, 0x313A4423, 0x2B323B23, 0x2F374023, 0x2F374023, 0x2B333B23, 0x282E3623, 0x323A4423, 0x37414C74, 0x3C4753FF, 0x6F7275FF, 0x000000-1, 0x27272727,
    0x08090B5E, 0x1E2227FF, 0x696E73FF, 0x3E4854C8, 0x272F3723, 0x2E364023, 0x2D353E23, 0x2F384223, 0x2C343D23, 0x282F3823, 0x28303823, 0x29313A23, 0x31394423, 0x2F374123, 0x2D353E23, 0x2D363F23, 0x29313A23, 0x272E3623, 0x2D343E23, 0x282F3823, 0x2E364023, 0x2F364023, 0x343D4723, 0x333C4623, 0x31394323, 0x2F363F23, 0x333C4623, 0x31394377, 0x363F4BFF, 0x717578FF, -0x1010001, 0x23232323,
    0x08090B5E, 0x1C2125FF, 0x666A70FF, 0x404B57CC, 0x2B333C23, 0x323A4523, 0x30384323, 0x29303923, 0x30384223, 0x323B4523, 0x2E364023, 0x30394323, 0x2E374123, 0x2E374123, 0x29303923, 0x2F374123, 0x2A313A23, 0x2F384123, 0x333C4723, 0x313A4423, 0x2E363F23, 0x31394323, 0x30384123, 0x323A4423, 0x2B323B23, 0x30374123, 0x333C4623, 0x323A4477, 0x37404CFF, 0x71757AFF, -0x9050201, 0x1E1F1F1F,
    0x07090A5A, 0x1B1F24FF, 0x62676CFF, 0x434E5ACC, 0x2B333C23, 0x2C343D23, 0x2A323B23, 0x29303923, 0x2A313A23, 0x2E374023, 0x30384323, 0x282F3823, 0x29303823, 0x323B4523, 0x2B323B23, 0x30394323, 0x313A4423, 0x333C4723, 0x30384223, 0x2F374123, 0x2B323A23, 0x2D353E23, 0x30384123, 0x31394323, 0x282F3723, 0x2D343D23, 0x323A4323, 0x414C597E, 0x3B4552FF, 0x6C7176FF, -0x14100B01, 0x1D1D1E1F,
    0x07080A56, 0x1A1E23FF, 0x5E6368FF, 0x3F4955CC, 0x2B333C23, 0x2C343D23, 0x30394323, 0x333B4623, 0x2D353E23, 0x31394323, 0x343D4823, 0x2C343D23, 0x28303823, 0x313A4523, 0x2F374123, 0x323B4623, 0x323B4623, 0x363F4A23, 0x2F374123, 0x2A313A23, 0x30384223, 0x2C343C23, 0x2F374123, 0x353E4823, 0x353E4823, 0x2D343D23, 0x2B323B23, 0x3D47537E, 0x37414CFF, 0x6A6F74FF, -0x201C1801, 0x1818191B,
    0x07080A56, 0x191D22FF, 0x595E63FF, 0x3F4A56CC, 0x272E3623, 0x282F3723, 0x333B4623, 0x313A4423, 0x2A323B23, 0x2F374123, 0x272E3623, 0x313A4423, 0x2D343E23, 0x2C343D23, 0x29303823, 0x2B333C23, 0x2C333C23, 0x30384223, 0x333C4623, 0x323B4523, 0x2F374123, 0x282E3623, 0x333C4623, 0x333B4623, 0x353E4823, 0x30384123, 0x2B323A23, 0x3D475382, 0x38424DFF, 0x64686DFF, -0x2E2A2501, 0x1617171B,
    0x07080952, 0x191D21FF, 0x54585EFF, 0x3B4550CF, 0x2B323B23, 0x2B323B23, 0x333C4723, 0x353E4923, 0x2F374023, 0x333C4623, 0x272E3623, 0x323B4523, 0x2F374023, 0x323B4523, 0x2B323B23, 0x282F3823, 0x2D353E23, 0x323B4523, 0x2F374123, 0x2F374023, 0x353E4823, 0x333B4523, 0x38424D23, 0x353E4923, 0x252C3323, 0x30384223, 0x30384223, 0x3F495582, 0x37414CFF, 0x61656AFF, -0x3C383301, 0x12121317,
    0x0607094E, 0x171B20FF, 0x4F5358FF, 0x3F4852D3, 0x2B333C23, 0x252C3323, 0x2F374023, 0x39434E23, 0x333C4623, 0x30384123, 0x2D343D23, 0x2C343D23, 0x2F374123, 0x2E364023, 0x2F384123, 0x30384223, 0x30394223, 0x343D4723, 0x333C4623, 0x31394223, 0x31394223, 0x2C333C23, 0x323A4423, 0x31394223, 0x323B4523, 0x343D4723, 0x2E353E23, 0x3B455088, 0x2E3640FF, 0x5D6166FF, -0x4A464201, 0x0E0E0E13,
    0x0607084A, 0x171B20FF, 0x494E53FF, 0x373D44EA, 0x323B4688, 0x38424D85, 0x3D485585, 0x39434F85, 0x353E4A85, 0x38424E85, 0x37404C85, 0x3A445082, 0x333D487B, 0x353F4A7B, 0x39434F7B, 0x39434F7B, 0x3B46527B, 0x3A44507B, 0x3B45507B, 0x38414D82, 0x323B4685, 0x37414D85, 0x343D4885, 0x3C465285, 0x3C465385, 0x363F4A82, 0x2D353E82, 0x39424DB8, 0x1B2128FF, 0x585C61FF, -0x59555001, 0x0A0A0B0F,
    0x05070846, 0x161A1FFF, 0x32363BFF, 0x13171CFF, 0x161B21FF, 0x262E37FF, 0x313B46FF, 0x303A44FF, 0x2E3741FF, 0x272F38FF, 0x272F38FF, 0x262E37FF, 0x242B34FF, 0x222932FF, 0x272E38FF, 0x29313AFF, 0x262E37FF, 0x252D36FF, 0x242B34FF, 0x252D36FF, 0x2C343EFF, 0x2C353FFF, 0x2C353FFF, 0x2E3741FF, 0x2F3742FF, 0x29313AFF, 0x282F38FF, 0x191E24FF, 0x11151AFF, 0x53575CFF, -0x67635F01, 0x09090A0F,
    0x05060742, 0x15191EFF, 0x161A1FFF, 0x16191EFF, 0x161A1FFF, 0x161A1FFF, 0x171B20FF, 0x181C21FF, 0x191D22FF, 0x1A1F23FF, 0x1C2025FF, 0x1E2227FF, 0x21252AFF, 0x24282DFF, 0x272B30FF, 0x2B2F34FF, 0x303439FF, 0x35393EFF, 0x3A3E43FF, 0x404449FF, 0x474B50FF, 0x4D5256FF, 0x54585DFF, 0x5B5F64FF, 0x62666BFF, 0x696D72FF, 0x6F7378FF, 0x75797EFF, 0x7A7E83FF, -0x7F7B7601, -0x75716D01, 0x0606070B,
    0x04050533, 0x101317C4, 0x101317C4, 0x101417C4, 0x111417C4, 0x111418C4, 0x121518C4, 0x121519C4, 0x13161AC4, 0x14171BC4, 0x15181CC4, 0x171A1EC4, 0x191C20C4, 0x1B1E22C4, 0x1D2024C4, 0x202327C4, 0x24272AC4, 0x272A2EC4, 0x2B2E32C4, 0x303337C4, 0x35383BC4, 0x393D40C4, 0x3F4245C4, 0x44474AC4, 0x494C50C4, 0x4E5154C4, 0x525559C4, 0x595C5FC8, 0x5C6063C8, 0x606367C8, 0x636669C8, 0x03040407,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

Vtx D_hd_code_802FBD50[8] = {
  { { { 0x0000, 0x0000, 0xFFFB }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0xFFFB }, 0x0000, { 0x04E0, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0xFFFB }, 0x0000, { 0x04E0, 0x04E0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0xFFFB }, 0x0000, { 0x0000, 0x04E0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0xFFFB }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0xFFFB }, 0x0000, { 0x03E0, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0xFFFB }, 0x0000, { 0x03E0, 0x03E0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0xFFFB }, 0x0000, { 0x0000, 0x03E0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } }
};

u16 D_hd_code_802FBDD0[14] = {
  0x07EF, 0x07F0, 0x07F1, 0x07F2, 0x07F3, 0x07F4, 0x07F5,
  0x07F6, 0x07F7, 0x07F8, 0x07F9, 0x07FA, 0x07FB, 0x0000
};
u16 D_hd_code_802FBDEC[22] = {
  0x07D9, 0x07DA, 0x07DB, 0x07DC, 0x07DD, 0x07DE, 0x07DF,
  0x07E0, 0x07E1, 0x07E2, 0x07E3, 0x07E4, 0x07E5, 0x0787,
  0x0788, 0x078C, 0x078D, 0x078E, 0x078F, 0x0790, 0x0791,
  0x0000
};
u16 D_hd_code_802FBE18[22] = {
  0x055F, 0x0560, 0x0561, 0x0562, 0x0563, 0x0567, 0x065B,
  0x065C, 0x065D, 0x065E, 0x065F, 0x0660, 0x0661, 0x0662,
  0x076C, 0x076D, 0x076E, 0x076F, 0x0770, 0x0771, 0x07EC,
  0x0000
};
u16 D_hd_code_802FBE44[30] = {
  0x08AE, 0x08AF, 0x08B0, 0x08B1, 0x08B2, 0x08B3, 0x08B4,
  0x08B5, 0x08B6, 0x08B7, 0x08B8, 0x08B9, 0x08BA, 0x08BB,
  0x08BC, 0x08BD, 0x08BE, 0x08BE, 0x08BE, 0x08BE, 0x08BE,
  0x08BE, 0x08BE, 0x08BE, 0x08BE, 0x08BE, 0x08BE, 0x08BE,
  0x08BE, 0x08BE
};
u16 D_hd_code_802FBE80[40] = {
  0x08E1, 0x08E2, 0x08E3, 0x08E4, 0x08E5, 0x08E6, 0x08E7,
  0x08E8, 0x08E9, 0x08EA, 0x08EB, 0x08EC, 0x08ED, 0x08EE,
  0x08EF, 0x08F0, 0x08F1, 0x08F2, 0x08F3, 0x08F4, 0x08F3,
  0x08F2, 0x08F1, 0x08F0, 0x08EF, 0x08F0, 0x08F1, 0x08F2,
  0x08F3, 0x08F4, 0x08F4, 0x08F4, 0x08F4, 0x08F4, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
// </data>

// Per-frame update (arg0 = frame counter): expire old skill samples, record
// a new one when the vehicle code flagged it (D_8036CB2F, with metrics in
// D_8036CB2A/2C/2E), retally and run the praise/criticism checks; at frame
// 50 play the mission-start advisor clip; and in carrier levels fire the
// scripted one-shot comms from the level data (D_803BE6FC list) as the
// carrier passes each z threshold.
// Proposed name: UpdateCommsAdvisor
void func_hd_code_80277620(s32 arg0) {
    u8 sp2F;
    struct S_803BE6FC* sp28;
    s16 sp26;

    sp2F = 0;
    sp28 = D_803BE6FC;
    while ((sp2F == 0) && ((u8) D_8036CB28 != (u8) D_8036CB29)) {
        if ((arg0 - D_8036C8D0[D_8036CB28].unk8) >= 0x3E9) {
            D_8036CB28++;
            if (D_8036CB28 == 0x32) {
                D_8036CB28 = 0;
            }
        } else {
            sp2F = 1;
        }
    }

    if ((D_8036CB2F != 0) && (((u8) D_8036CB29 + 1) != (u8) D_8036CB28) && (((u8) D_8036CB29 != 0x31) || ((u8) D_8036CB28 != 0))) {
        D_8036C8D0[D_8036CB29].unk0 = func_hd_code_80277D34();
        D_8036C8D0[D_8036CB29].unk2 = func_hd_code_80277E08();
        D_8036C8D0[D_8036CB29].unk4 = D_8036CB2E;
        D_8036C8D0[D_8036CB29].unk8 = arg0;

        D_8036CB29++;
        if (D_8036CB29 == 0x32) {
            D_8036CB29 = 0;
        }
    }
    if (D_8036CB2F != 0) {
        func_hd_code_80277C20();
        func_hd_code_802778FC();
        func_hd_code_80277AE0();
        func_hd_code_80277B84();
    }
    if ((arg0 == 0x32) && (D_hd_code_803643D6 == 0)) {
        func_hd_code_80277EDC(2, 1, 2, func_hd_code_8026205C(1));
    }
    if (D_hd_code_803643DB != 0) {
        sp26 = (s16) ((s32) D_803EF6E4 >> 5);
        while ((u32)sp28 < (u32) D_803BE700) {
            if ((sp28->unk6 == 0) && (sp26 > sp28->unk0)) {
                func_hd_code_80277EDC((s32) sp28->unk2, (s32) sp28->unk3, (s32) sp28->unk4, (s32) sp28->unk5);
                sp28->unk6 = 1U;
            }
            sp28++;
        }
    }
    D_8036CB2F = 0;
}

// Praise check: per-vehicle thresholds of consecutive good samples trigger
// the "doing really well" comms and reset the ring
// Proposed name: CheckPraise
void func_hd_code_802778FC(void) {
  switch (D_hd_code_80364456) {                   /* irregular */
    case 5:
      if (((s32) D_8036CB31 >= 0x10) && ((s32) D_8036CB30 >= 0x10)) {
        func_hd_code_80277EDC(3, 1, 1, 0x63);
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("DOING REALLY WELL\n");
        return;
      }
      return;
    case 4:
      if (((s32) D_8036CB31 >= 0x29) && ((s32) D_8036CB30 >= 0x29)) {
        func_hd_code_80277EDC(4, 1, 1, func_hd_code_8026205C(4));
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("DOING REALLY WELL\n");
        return;
      }
      break;
    case 3:
      if (((s32) D_8036CB31 >= 0xB) && ((s32) D_8036CB30 >= 0xB)) {
        func_hd_code_80277EDC(0, 1, 3, 0xB2);
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("DOING REALLY WELL\n");
        return;
      }
      break;
    case 9:
      if (((s32) D_8036CB31 >= 0x1A) && ((s32) D_8036CB30 >= 0x1A)) {
        func_hd_code_80277EDC(4, 1, 1, func_hd_code_8026205C(4));
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("DOING REALLY WELL\n");
      }
      break;
  }
}

// "USING WRONG DIGGER" check: enough good speed samples but almost no good
// control samples
// Proposed name: CheckWrongVehicle
void func_hd_code_80277AE0(void) {
  switch(D_hd_code_80364456) {
    case 3:
    case 4:
    case 5:
    case 9:
      if (((s32) D_8036CB31 >= 6) && ((s32) D_8036CB30 < 2)) {
        func_hd_code_80277EDC(1, 1, 3, 0xB3);
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("USING WRONG DIGGER\n");
      }
      break;
  }
}

// "USING DIGGER INCORRECTLY" check: many bad speed samples with few good
// control samples
// Proposed name: CheckVehicleMisuse
void func_hd_code_80277B84(void) {
  switch(D_hd_code_80364456) {
    case 3:
    case 4:
    case 5:
      if (((s32) D_8036CB33 >= 0x1F) && ((s32) D_8036CB30 < 6)) {
        func_hd_code_80277EDC(2, 1, 2, 0x58);
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("USING DIGGER INCORRECTLY\n");
      }
      break;
  }
}

// Recompute the good/bad sample tallies (D_8036CB30..33) from the ring
// Proposed name: TallySkillSamples
void func_hd_code_80277C20(void) {
  u8 sp7 = D_8036CB28;

  D_8036CB30 = 0;
  D_8036CB31 = 0;
  D_8036CB32 = 0;
  D_8036CB33 = 0;

  while (sp7 != D_8036CB29) {
    if (D_8036C8D0[sp7].unk2 == 0) {
      D_8036CB30 += 1;
    } else {
      D_8036CB32 += 1;
    }
    if (D_8036C8D0[sp7].unk0 == 0) {
      D_8036CB31 += 1;
    } else {
      D_8036CB33 += 1;
    }
    sp7++;
    if (sp7 == 0x32) {
      sp7 = 0;
    }
  }
}

// Grade the current speed sample against the vehicle's threshold
// (0 = good, 1 = bad)
// Proposed name: GradeSpeedSample
s16 func_hd_code_80277D34(void) {
  switch (D_8036CB2E) {                           /* irregular */
    case 5:
      if (D_8036CB2A >= 0x191) {
        return 0;
      }
      return 1;
    case 4:
      if (D_8036CB2A >= 0x191) {
        return 0;
      }
      return 1;
    case 9:
      if (D_8036CB2A >= 0x64) {
        return 0;
      }
      return 1;
    case 3:
      if (D_8036CB2A >= 0x64) {
        return 0;
      }
      return 1;
  }
  return 1;
}

// Grade the current control/handling sample against the vehicle's threshold
// (0 = good, 1 = bad)
// Proposed name: GradeControlSample
s16 func_hd_code_80277E08(void) {
  switch (D_8036CB2E) {                           /* irregular */
    case 5:
      if (D_8036CB2C >= 0x51) {
        return 0;
      }
      return 1;
    case 4:
      if (D_8036CB2C >= 0x51) {
        return 0;
      }
      return 1;
    case 9:
      if (D_8036CB2C >= 0x64) {
        return 0;
      }
      return 1;
    case 3:
      if (D_8036CB2C >= 0x64) {
        return 0;
      }
      return 1;
  }
  return 1;
}

// Open the comms window: arg0 = face animation (0..4, selecting the frame
// id list, frame count and rate), arg1 = play mode (0 = loop forward,
// 1 = ping-pong), arg2 = number of loops, arg3 = voice clip to play.
// Positions the face + border quads top-left or bottom-right (always
// bottom-right outside demolition mode). Ignored if a window is already up.
// Proposed name: ShowCommsWindow
void func_hd_code_80277EDC(u8 arg0, u8 arg1, s32 arg2, s32 arg3) {
    u8 sp27;

    if (((D_hd_code_80364A90 & 0x200000000400220C)) && ((u8) D_8036CB34 == 0)) {
        if ((u8) arg3 != 0) {
            sndPlaySfx(D_hd_code_80367738, (s16) (u8) arg3, NULL);
        }
        D_8036CB34 = 1;
        D_8036CB35 = arg2;
        D_8036CB36 = 0;
        D_8036CB37 = 0;
        D_8036CB39 = 0;
        D_8036CB3A = 0;
        D_8036CB38 = (u8) arg1;
        D_8036CB44 = (u8) arg0;
        D_8036CB50 = 0;
        switch (arg0) {                        /* switch 1 */
        case 0:                                     /* switch 1 */
            sp27 = 0;
            D_8036CB3C = 0xD;
            D_8036CB40 = D_hd_code_802FBDD0;
            D_8036CB3B = 1;
            break;
        case 1:                                     /* switch 1 */
            sp27 = 1;
            D_8036CB3C = 0x15;
            D_8036CB40 = D_hd_code_802FBDEC;
            D_8036CB3B = 1;
            break;
        case 2:                                     /* switch 1 */
            sp27 = 0;
            D_8036CB3C = 0x15;
            D_8036CB40 = D_hd_code_802FBE18;
            D_8036CB3B = 2;
            break;
        case 3:                                     /* switch 1 */
            sp27 = 1;
            D_8036CB3C = 0x1E;
            D_8036CB40 = D_hd_code_802FBE44;
            D_8036CB3B = 1;
            break;
        case 4:                                     /* switch 1 */
            sp27 = 0;
            D_8036CB3C = 0x22;
            D_8036CB40 = D_hd_code_802FBE80;
            D_8036CB3B = 1;
            break;
        }
        if (D_hd_code_80364AA8 != 1) {
            sp27 = 1;
        }
        switch (sp27) {
        case 0:
            D_hd_code_802FBD50[0].v.ob[0] = 0x20;
            D_hd_code_802FBD50[0].v.ob[1] = 0x44;

            D_hd_code_802FBD50[1].v.ob[0] = 0x4E,
            D_hd_code_802FBD50[1].v.ob[1] = 0x44;

            D_hd_code_802FBD50[2].v.ob[0] = 0x4E,
            D_hd_code_802FBD50[2].v.ob[1] = 0x17;

            D_hd_code_802FBD50[3].v.ob[0] = 0x20,
            D_hd_code_802FBD50[3].v.ob[1] = 0x17;

            D_hd_code_802FBD50[4].v.ob[0] = 0x1A,
            D_hd_code_802FBD50[4].v.ob[1] = 0x49;

            D_hd_code_802FBD50[5].v.ob[0] = 0x54,
            D_hd_code_802FBD50[5].v.ob[1] = 0x49;

            D_hd_code_802FBD50[6].v.ob[0] = 0x54,
            D_hd_code_802FBD50[6].v.ob[1] = 0xD;

            D_hd_code_802FBD50[7].v.ob[0] = 0x1A,
            D_hd_code_802FBD50[7].v.ob[1] = 0xD;
            return;
        case 1:
            D_hd_code_802FBD50[0].v.ob[0] = 0xEE,
            D_hd_code_802FBD50[0].v.ob[1] = 0xDE;

            D_hd_code_802FBD50[1].v.ob[0] = 0x11C,
            D_hd_code_802FBD50[1].v.ob[1] = 0xDE;

            D_hd_code_802FBD50[2].v.ob[0] = 0x11C,
            D_hd_code_802FBD50[2].v.ob[1] = 0xB1;

            D_hd_code_802FBD50[3].v.ob[0] = 0xEE,
            D_hd_code_802FBD50[3].v.ob[1] = 0xB1;

            D_hd_code_802FBD50[4].v.ob[0] = 0xE8,
            D_hd_code_802FBD50[4].v.ob[1] = 0xE3;

            D_hd_code_802FBD50[5].v.ob[0] = 0x122,
            D_hd_code_802FBD50[5].v.ob[1] = 0xE3;

            D_hd_code_802FBD50[6].v.ob[0] = 0x122,
            D_hd_code_802FBD50[6].v.ob[1] = 0xA7;

            D_hd_code_802FBD50[7].v.ob[0] = 0xE8,
            D_hd_code_802FBD50[7].v.ob[1] = 0xA7;
            break;
        }
    }
}

// Close the comms window immediately
// Proposed name: HideCommsWindow
void func_hd_code_80278318(void) {
  D_8036CB34 = 0;
}

// decomped by inspectredc
// Draw the comms window: stream the current 40x40 face frame into the
// double buffer, advance the animation (forward or ping-pong, counting
// loops, closing when done), apply the TV-static effect - full static with
// a radio crackle (sfx 0x69) while tuning in, then random short bursts -
// and draw the face quad (2-cycle NOISE blend by the static alpha) plus the
// translucent 32x32 RGBA32 border frame.
// Proposed name: DrawCommsWindow
void func_hd_code_80278324(Gfx** arg0, s32* arg1, u8 arg2) {
    Gfx* entry;

    entry = *arg0;
    if (D_8036CB34 != 0) {
        func_hd_code_802A1040((u16) D_8036CB40->v.ob[D_8036CB39], D_8036CB48[arg2], 0);
        switch (D_8036CB38) {
            case 1:
                if (D_8036CB37 == 0) {
                    D_8036CB3A++;
                    if (D_8036CB3A == D_8036CB3B) {
                        D_8036CB3A = 0;
                        D_8036CB39++;
                        if ((D_8036CB39 + 1) == D_8036CB3C) {
                            D_8036CB37 = 1;
                            D_8036CB36++;
                        }
                    }
                } else {
                    D_8036CB3A++;
                    if (D_8036CB3A == D_8036CB3B) {
                        D_8036CB3A = 0;
                        D_8036CB39--;
                        if (!D_8036CB39) {
                            D_8036CB37 = 0;
                            D_8036CB36++;
                        }
                    }
                }
                break;
            case 0:
                D_8036CB3A++;
                if (D_8036CB3A == D_8036CB3B) {
                    D_8036CB3A = 0;
                    D_8036CB39++;
                    if (D_8036CB39 == D_8036CB3C) {
                        D_8036CB39 = 0;
                        D_8036CB36++;
                    }
                }
                break;
            default:
                break;
        }
        if (D_8036CB36 == D_8036CB35) {
            D_8036CB34 = 0;
        }
        if ((D_8036CB36 == 0) && (D_8036CB39 < 5)) {
            if (D_8036CB39 == 0) {
                sndPlaySfx(D_hd_code_80367738, 0x69, NULL);
            }
            D_8036CB51 = 0x50;
        } else if (D_8036CB50 != 0) {
            D_8036CB51 -= 0xF;
            D_8036CB50--;
        } else if (func_hd_code_8026A828(0, 0x14) == 0) {
            D_8036CB50 = 5;
            D_8036CB51 = 0x50;
            sndPlaySfx(D_hd_code_80367738, 0x69, NULL);
        } else {
            D_8036CB51 = 0;
        }

        gSPMatrix(entry++, &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_2CYCLE);
        gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
        gDPSetCombineLERP(entry++, NOISE, 0, PRIMITIVE_ALPHA, 0, 0, 0, 0, SHADE, TEXEL1, 0, SHADE, COMBINED, 0, 0, 0, SHADE);
        gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_8036CB51);
        gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(D_8036CB48[arg2]), G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 40, 0, G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(entry++, OS_PHYSICAL_TO_K0(D_hd_code_802FBD50), 8, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 2, 3, 0);
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
        gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(D_hd_code_802FAD50), G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Triangle(entry++, 4, 5, 6, 0);
        gSP1Triangle(entry++, 4, 6, 7, 0);
        gDPPipeSync(entry++);
    }
    *arg0 = entry;
}

