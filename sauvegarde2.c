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

#define USB_TIMEOUT 1000 /* milliseconds */

int debug_level = 0;
missile_usb *control;

  //---------------------------------------------------------------------------
  
void init(int *device_type){

	char *device = NULL;

  unsigned int set_event = 0;

  if (missile_usb_initialise() != 0) {
    fprintf(stderr, "missile_usb_initalise failed: %s\n", strerror(errno));
    //return -1;
  }
  
  control = missile_usb_create(debug_level, USB_TIMEOUT);
  if (control == NULL) {
    fprintf(stderr, "missile_usb_create() failed\n");
    //return -1;
  }
  
  if (missile_usb_finddevice(control, 0, *device_type) != 0) {
    fprintf(stderr, "USBMissileLauncher device not found\n");
    //return -1;
  }

  if (debug_level)
    fprintf(stderr, "Now we're ready.  Move the thing around, and FIRE!\n");

  //---------------------------------------------------------------------------

  int fd;
  struct input_event ev[64];
  int events;

  if (set_event) {

    if (device == NULL) { //
      fprintf(stderr, "No device given\n"); 
      //return 0;
    }
    
    if (IEOpen(device, &fd) < 0) {
      fprintf(stderr, "IEOpen(%s, fd) failed\n", device); //-------------------// 
      //return -1;
    }

    while (1) {

      if (IERead(fd, ev, &events) < 0) {
	fprintf(stderr, "IERead() failed\n");
	//return -1;
      }

      usleep(200000);
	
    }
} 

}
  
  //---------------------------------------------------------------------------

void action(int *device_type, int commande){

  int delay = 3000;

  unsigned int set_fire = 0, set_left = 0, set_right = 0;
  unsigned int set_up = 0, set_down = 0, set_stop = 0;
  
  fprintf(stderr,"1\n");

  //---------------------------------------------------------------------------

  //set_right = 1;
  //set_fire = 1;
  set_up = 1; 
  set_left = 1;
  //set_down = 1;
  set_stop = 1;  

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

//=============================================================================

int main() {

	char commande = 0;

  int device_type = 1;

  init(&device_type);	
  
  int i;
  
  for(i=4;i>0;i--){

  action(&device_type,commande);
  
  }

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
