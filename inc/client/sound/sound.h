/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once

#define CHAN_FOOTSTEP   8

void S_Init(void);
void S_Shutdown(void);

// if origin is NULL, the sound will be dynamically sourced from the entity
void S_StartSound(const vec3_t origin, int entnum, int entchannel,
                  qhandle_t sfx, float fvol, float attenuation, float timeofs);
void S_ParseStartSound(void);
void S_StartLocalSound(const char *s);
void S_StartLocalSoundOnce(const char *s);

void S_FreeAllSounds(void);
void S_StopAllSounds(void);
void S_Update(void);

void S_Activate(void);

void S_BeginRegistration(void);
qhandle_t S_RegisterSound(const char *sample);
void S_EndRegistration(void);

#define MAX_RAW_SAMPLES     8192

void S_RawSamples(int samples, int rate, int width, int channels, const void *data);
int S_GetSampleRate(void);
bool S_SupportsFloat(void);
void S_PauseRawSamples(bool paused);

#if USE_AVCODEC
void OGG_Play(void);
void OGG_Stop(void);
void OGG_Update(void);
void OGG_LoadTrackList(void);
void OGG_Init(void);
void OGG_Shutdown(void);
#else
#define OGG_Play()          (void)0
#define OGG_Stop()          (void)0
#define OGG_Update()        (void)0
#define OGG_LoadTrackList() (void)0
#define OGG_Init()          (void)0
#define OGG_Shutdown()      (void)0
#endif

extern vec3_t   listener_origin;
extern vec3_t   listener_forward;
extern vec3_t   listener_right;
extern vec3_t   listener_up;
extern int      listener_entnum;
