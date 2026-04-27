#include <PR/os_internal.h>
#include <PR/rcp.h>
#include "piint.h"

void __osDevMgrMain(void* args) {
  OSIoMesg *mb;
  OSMesg em;
  OSMesg dummy;
  s32 ret;
  OSDevMgr *dm;

  mb = NULL;
  ret = 0;
  dm = (OSDevMgr *)args;
  while(1) {
    osRecvMesg(dm->cmdQueue, (OSMesg)&mb, OS_MESG_BLOCK);
    switch (mb->hdr.type) {                              /* irregular */
      case 11:
        osRecvMesg(dm->acsQueue, &dummy, 1);
        ret = dm->dma(OS_READ, mb->devAddr, mb->dramAddr, mb->size);
        break;
      case 12:
        osRecvMesg(dm->acsQueue, &dummy, 1);
        ret = dm->dma(OS_WRITE, mb->devAddr, mb->dramAddr, mb->size);
        break;
      case OS_MESG_TYPE_LOOPBACK:
        osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
        ret = -1;
        break;
      default:
        ret = -1;
        break;
    }
    if (ret == 0) {
      osRecvMesg(dm->evtQueue, &em, 1);
      osSendMesg(mb->hdr.retQueue, mb, 0);
      osSendMesg(dm->acsQueue, NULL, 0);
    }
  }
}
