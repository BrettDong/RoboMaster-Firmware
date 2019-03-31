/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file remote_ctrl.h
 *  @version 1.0
 *  @date June 2017
 *
 *  @brief remote control message handle
 *
 *  @copyright 2017 DJI RoboMaster. All rights reserved.
 *
 */
 
#ifndef __REMOTE_CTRL_H__
#define __REMOTE_CTRL_H__

#include "stm32f4xx_hal.h"
#include "shoot_task.h"
#include "infantry_info.h"

enum
{
  RC_UP = 1,
  RC_MI = 3,
  RC_DN = 2,
};
enum
{
	WH_UP_THRESHOLD = -300,
	WH_NEG_MI_THRESHOLD = -100,
	WH_POS_MI_THRESHOLD = 100,
	WH_DN_THRESHOLD = 300,
};
enum hero_signal_index
{
	UP,
	DOWN,
	TOBOTTOM,
	TOTOP
};

typedef enum
{
	OFF=0,
	BOTTOM_STAY=1,
	NON_BOTTOM_STAY=-1,
	CONTIN_UP=2,
	CONTIN_DOWN=-2,
	ONCE_UP=3,
	ONCE_DOWN=-3
}hero_frame_status;

typedef struct
{
	int8_t output;
	int8_t signal[4];
	hero_frame_status status;
}hero_frame;

/* control operation definition */
//      shoot relevant      remote control operation
#define RC_SINGLE_SHOOT    ((glb_sw.last_sw1 == RC_MI) && (rc.sw1 == RC_DN))
//#define RC_SINGLE_SHOOT    ((glb_sw.last_wh<WH_POS_MI_THRESHOLD) && (glb_sw.last_wh>WH_NEG_MI_THRESHOLD) && (rc.ch7 > WH_UP_THRESHOLD))
#define RC_CONTINUE_SHOOT  (rc.sw1 == RC_DN)
//#define RC_CONTINUE_SHOOT  ((glb_sw.last_wh<WH_POS_MI_THRESHOLD) && (glb_sw.last_wh>WH_NEG_MI_THRESHOLD) && (rc.ch7 < WH_DN_THRESHOLD))
#define RC_CTRL_FRIC_WHEEL ((glb_sw.last_sw1 == RC_MI) && (rc.sw1 == RC_UP))

typedef struct
{
  uint8_t last_sw1;
  uint8_t last_sw2;
  uint32_t stable_time_sw1;
  uint32_t stable_time_sw2;
	uint8_t last_wh;
	uint32_t stable_time_wh;
} sw_record_t;


typedef struct
{
  float vx;
  float vy;
  float vw;
  
  float pit_v;
  float yaw_v;
	/*Horizontal speed for Hero*/
	int16_t vz;
} rc_ctrl_t;


#define DBUS_MAX_LEN 50
#define DBUS_BUFLEN  18

extern uint8_t     dbus_buf[];
extern rc_info_t   rc;
extern rc_ctrl_t   rm;
extern sw_record_t glb_sw;

void rc_callback_handler(rc_info_t *rc, uint8_t *buff);

void remote_ctrl_chassis_hook(void);
void remote_ctrl_gimbal_hook(void);
void remote_ctrl_shoot_hook(void);
void remote_ctrl_hero_frame(void);


#endif

