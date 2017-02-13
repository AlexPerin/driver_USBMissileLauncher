#ifndef DEPEND
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/io.h>
#include <errno.h>
#include <linux/input.h>
#endif
#include "InputEvent.h"
#include "USBMissileLauncher.h"
#include "traitement.h"
#include "action.h"
#include "initialisation.h"

#define USB_TIMEOUT 1000 /* milliseconds */

missile_usb *control;

int main() {

	int commande = 1;
  int device_type = 1;

  init(&device_type);	
  
  //int i;
  
  //for(i=4;i>0;i--){

  action(&device_type,commande);
  
  //}

  missile_usb_destroy(control);  

  return 0;
}

//=============================================================================

/*
 * Local Variables:
 * mode: C
 * End:
 */

// structure à respecter : INIT / IF / DO
