# Blastcorps VRAM layout

BlastCorps consists of three overlays:
- init
- hd_code
- hd_front_end

init is loaded while booting. It is just responsible for loading hd_code. hd_code loads hd_front_end on demand.

## VRAM Layout

The developers reserved the following VRAM address spaces for each overlay:

| overlay        | from       | to         | occupied space |
|----------------|------------|------------|----------------|
| `hd_front_end` | 0x801E7000 | 0x8021ED00 | 0x37D00        |
| `init`         | 0x8021ED00 | 0x802447C0 | 0x25AC0        |
| `hd_code`      | 0x802447C0 | 0x80400000 | 0x1BB840       |




