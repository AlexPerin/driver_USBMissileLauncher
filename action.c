#include "traitement.h"
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

#define USB_TIMEOUT 1000 /* milliseconds */

missile_usb *control;
  
  //---------------------------------------------------------------------------

void action(int *device_type, int p_commande){

  unsigned int set_fire = 0, set_left = 0, set_right = 0;
  unsigned int set_up = 0, set_down = 0, set_stop = 0;
  
  fprintf(stderr,"1\n");
  
  int delay = 10; // butée = 3.5 s

  //---------------------------------------------------------------------------

	if (p_commande == 0) {
		delay = 3000; 
		set_left=1;
		set_down=1;
		set_stop = 1;
	}
  set_right = 1;
  //set_fire = 1;
  //set_up = 1; 
  set_left = 1;
  //set_down = 1;
  //set_stop = 1;  

  char msg = 0x00;

  switch (*device_type) {
    
  case DEVICE_TYPE_MISSILE_LAUNCHER:
  
    if (set_left)
      msg |= MISSILE_LAUNCHER_CMD_LEFT; //masque de la commande en hexa
    
    if (set_right)
      msg |= MISSILE_LAUNCHER_CMD_RIGHT;
    
    if (set_up)
      msg |= MISSILE_LAUNCHER_CMD_UP;
    
    if (set_down)
      msg |= MISSILE_LAUNCHER_CMD_DOWN;
    
    if (set_fire)
      msg |= MISSILE_LAUNCHER_CMD_FIRE;

    missile_do(control, msg, *device_type);
    
    if (set_stop) {
      usleep(delay * 1000);
      missile_do(control, MISSILE_LAUNCHER_CMD_STOP, *device_type);
    }

    break;
    
  default:
    printf("Device Type (%d) not implemented, please do it!\n",
	   *device_type);
    //return -1;
    
  }
}
