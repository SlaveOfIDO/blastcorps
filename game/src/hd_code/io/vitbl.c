#include <PR/os.h>
#include <PR/rcp.h>
#include "viint.h"

OSViMode osViModeTable[] = {
    {
        OS_VI_NTSC_LPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                             // width
            BURST(57, 34, 5, 62),                   // burst
            VSYNC(525),                             // vSync
            HSYNC(3093, 0),                         // hSync
            LEAP(3093, 3093),                       // leap
            HSTART(108, 748),                       // hStart
            SCALE(2, 0),                            // xScale
            VCURRENT(0),                            // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(640),         // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(640),         // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                                  // width
            BURST(57, 34, 5, 62),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3093, 0),                                              // hSync
            LEAP(3093, 3093),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(2, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(640),         // origin
                SCALE(1, 0.25),      // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(640),         // origin
                SCALE(1, 0.75),      // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                                // width
            BURST(57, 34, 5, 62),                                      // burst
            VSYNC(525),                                                // vSync
            HSYNC(3093, 0),                                            // hSync
            LEAP(3093, 3093),                                          // leap
            HSTART(108, 748),                                          // hStart
            SCALE(2, 0),                                               // xScale
            VCURRENT(0),                                               // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(640),         // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(640),         // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                          // width
            BURST(57, 34, 5, 62),                                // burst
            VSYNC(524),                                          // vSync
            HSYNC(3093, 0),                                      // hSync
            LEAP(3093, 3093),                                    // leap
            HSTART(108, 748),                                    // hStart
            SCALE(2, 0),                                         // xScale
            VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(640),         // origin
                SCALE(1, 0.25),      // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(640),         // origin
                SCALE(1, 0.75),      // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                             // width
            BURST(57, 34, 5, 62),                   // burst
            VSYNC(525),                             // vSync
            HSYNC(3093, 0),                         // hSync
            LEAP(3093, 3093),                       // leap
            HSTART(108, 748),                       // hStart
            SCALE(2, 0),                            // xScale
            VCURRENT(0),                            // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                                  // width
            BURST(57, 34, 5, 62),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3093, 0),                                              // hSync
            LEAP(3093, 3093),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(2, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0.25),      // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(1280),        // origin
                SCALE(1, 0.75),      // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LAN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                     // width
            BURST(57, 34, 5, 62),           // burst
            VSYNC(525),                     // vSync
            HSYNC(3093, 0),                 // hSync
            LEAP(3093, 3093),               // leap
            HSTART(108, 748),               // hStart
            SCALE(2, 0),                    // xScale
            VCURRENT(0),                    // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LAF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                          // width
            BURST(57, 34, 5, 62),                                // burst
            VSYNC(524),                                          // vSync
            HSYNC(3093, 0),                                      // hSync
            LEAP(3093, 3093),                                    // leap
            HSTART(108, 748),                                    // hStart
            SCALE(2, 0),                                         // xScale
            VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0.25),      // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(1280),        // origin
                SCALE(1, 0.75),      // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(1280),                                                 // width
            BURST(57, 34, 5, 62),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3093, 0),                                              // hSync
            LEAP(3093, 3093),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(1, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(2560),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(640),                                                  // width
            BURST(57, 34, 5, 62),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3093, 0),                                              // hSync
            LEAP(3093, 3093),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(1, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(2560),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(1280),                                         // width
            BURST(57, 34, 5, 62),                                // burst
            VSYNC(524),                                          // vSync
            HSYNC(3093, 0),                                      // hSync
            LEAP(3093, 3093),                                    // leap
            HSTART(108, 748),                                    // hStart
            SCALE(1, 0),                                         // xScale
            VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(2560),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(640),                                          // width
            BURST(57, 34, 5, 62),                                // burst
            VSYNC(524),                                          // vSync
            HSYNC(3093, 0),                                      // hSync
            LEAP(3093, 3093),                                    // leap
            HSTART(108, 748),                                    // hStart
            SCALE(1, 0),                                         // xScale
            VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(2560),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(1280),                                                 // width
            BURST(57, 34, 5, 62),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3093, 0),                                              // hSync
            LEAP(3093, 3093),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(1, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(2560),        // origin
                SCALE(1, 0),         // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(5120),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(640),                                                  // width
            BURST(57, 34, 5, 62),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3093, 0),                                              // hSync
            LEAP(3093, 3093),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(1, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(2560),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(35, 509),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(5120),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                             // width
            BURST(57, 30, 5, 70),                   // burst
            VSYNC(525),                             // vSync
            HSYNC(3089, 4),                         // hSync
            LEAP(3097, 3098),                       // leap
            HSTART(108, 748),                       // hStart
            SCALE(2, 0),                            // xScale
            VCURRENT(0),                            // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(640),         // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(640),         // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                                  // width
            BURST(57, 30, 5, 70),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3088, 0),                                              // hSync
            LEAP(3100, 3100),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(2, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(640),         // origin
                SCALE(1, 0.25),      // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(640),         // origin
                SCALE(1, 0.75),      // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                                // width
            BURST(57, 30, 5, 70),                                      // burst
            VSYNC(525),                                                // vSync
            HSYNC(3089, 4),                                            // hSync
            LEAP(3097, 3098),                                          // leap
            HSTART(108, 748),                                          // hStart
            SCALE(2, 0),                                               // xScale
            VCURRENT(0),                                               // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(640),         // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(640),         // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                          // width
            BURST(57, 30, 5, 70),                                // burst
            VSYNC(524),                                          // vSync
            HSYNC(3088, 0),                                      // hSync
            LEAP(3100, 3100),                                    // leap
            HSTART(108, 748),                                    // hStart
            SCALE(2, 0),                                         // xScale
            VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(640),         // origin
                SCALE(1, 0.25),      // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(640),         // origin
                SCALE(1, 0.75),      // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                             // width
            BURST(57, 30, 5, 70),                   // burst
            VSYNC(525),                             // vSync
            HSYNC(3089, 4),                         // hSync
            LEAP(3097, 3098),                       // leap
            HSTART(108, 748),                       // hStart
            SCALE(2, 0),                            // xScale
            VCURRENT(0),                            // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                                  // width
            BURST(57, 30, 5, 70),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3088, 0),                                              // hSync
            LEAP(3100, 3100),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(2, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0.25),      // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(1280),        // origin
                SCALE(1, 0.75),      // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LAN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                     // width
            BURST(57, 30, 5, 70),           // burst
            VSYNC(525),                     // vSync
            HSYNC(3089, 4),                 // hSync
            LEAP(3097, 3098),               // leap
            HSTART(108, 748),               // hStart
            SCALE(2, 0),                    // xScale
            VCURRENT(0),                    // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LAF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(320),                                          // width
            BURST(57, 30, 5, 70),                                // burst
            VSYNC(524),                                          // vSync
            HSYNC(3088, 0),                                      // hSync
            LEAP(3100, 3100),                                    // leap
            HSTART(108, 748),                                    // hStart
            SCALE(2, 0),                                         // xScale
            VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0.25),      // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(1280),        // origin
                SCALE(1, 0.75),      // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(1280),                                                 // width
            BURST(57, 30, 5, 70),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3088, 0),                                              // hSync
            LEAP(3100, 3100),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(1, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(2560),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(640),                                                  // width
            BURST(57, 30, 5, 70),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3088, 0),                                              // hSync
            LEAP(3100, 3100),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(1, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(2560),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(1280),                                         // width
            BURST(57, 30, 5, 70),                                // burst
            VSYNC(524),                                          // vSync
            HSYNC(3088, 0),                                      // hSync
            LEAP(3100, 3100),                                    // leap
            HSTART(108, 748),                                    // hStart
            SCALE(1, 0),                                         // xScale
            VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(1280),        // origin
                SCALE(1, 0),         // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(2560),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(640),                                          // width
            BURST(57, 30, 5, 70),                                // burst
            VSYNC(524),                                          // vSync
            HSYNC(3088, 0),                                      // hSync
            LEAP(3100, 3100),                                    // leap
            HSTART(108, 748),                                    // hStart
            SCALE(1, 0),                                         // xScale
            VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { //[0]
                ORIGIN(1280),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { //[1]
                ORIGIN(2560),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(1280),                                                 // width
            BURST(57, 30, 5, 70),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3088, 0),                                              // hSync
            LEAP(3100, 3100),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(1, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(2560),        // origin
                SCALE(1, 0),         // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(5120),        // origin
                SCALE(1, 0),         // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            WIDTH(640),                                                  // width
            BURST(57, 30, 5, 70),                                        // burst
            VSYNC(524),                                                  // vSync
            HSYNC(3088, 0),                                              // hSync
            LEAP(3100, 3100),                                            // leap
            HSTART(108, 748),                                            // hStart
            SCALE(1, 0),                                                 // xScale
            VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                ORIGIN(2560),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(35, 509),     // vStart
                BURST(2, 2, 11, 0),  // vBurst
                VINTR(2),            // vIntr
            },
            { // [1]
                ORIGIN(5120),        // origin
                SCALE(0.5, 0.5),     // yScale
                HSTART(37, 511),     // vStart
                BURST(4, 2, 14, 0),  // vBurst
                VINTR(2),            // vIntr
            }
        }
    },

};
