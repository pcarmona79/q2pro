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
/*
==============================================================================

jorg

==============================================================================
*/

#include "g_local.h"
#include "m_boss31.h"

extern void SP_monster_makron(edict_t *self);

static int  sound_pain1;
static int  sound_pain2;
static int  sound_pain3;
static int  sound_idle;
static int  sound_death;
static int  sound_search1;
static int  sound_search2;
static int  sound_search3;
static int  sound_attack1;
static int  sound_attack2;
static int  sound_firegun;
static int  sound_step_left;
static int  sound_step_right;

void BossExplode(edict_t *self);
void MakronToss(edict_t *self);

void jorg_search(edict_t *self)
{
    float r;

    r = random();

    if (r <= 0.3f)
        gi.sound(self, CHAN_VOICE, sound_search1, 1, ATTN_NORM, 0);
    else if (r <= 0.6f)
        gi.sound(self, CHAN_VOICE, sound_search2, 1, ATTN_NORM, 0);
    else
        gi.sound(self, CHAN_VOICE, sound_search3, 1, ATTN_NORM, 0);
}

static void jorg_dead(edict_t *self);
static void jorgBFG(edict_t *self);
static void jorg_firebullet(edict_t *self);
static void jorg_reattack1(edict_t *self);
static void jorg_attack1(edict_t *self);
static void jorg_idle(edict_t *self);
static void jorg_step_left(edict_t *self);
static void jorg_step_right(edict_t *self);

//
// stand
//

static const mframe_t jorg_frames_stand[] = {
    { ai_stand, 0, jorg_idle },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },      // 10
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },      // 20
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },      // 30
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 19, NULL },
    { ai_stand, 11, jorg_step_left },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 6, NULL },
    { ai_stand, 9, jorg_step_right },
    { ai_stand, 0, NULL },      // 40
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, 0, NULL },
    { ai_stand, -2, NULL },
    { ai_stand, -17, jorg_step_left },
    { ai_stand, 0, NULL },
    { ai_stand, -12, NULL },        // 50
    { ai_stand, -14, jorg_step_right }  // 51
};
const mmove_t jorg_move_stand = {FRAME_stand01, FRAME_stand51, jorg_frames_stand, NULL};

static void jorg_idle(edict_t *self)
{
    gi.sound(self, CHAN_VOICE, sound_idle, 1, ATTN_NORM, 0);
}

static void jorg_step_left(edict_t *self)
{
    gi.sound(self, CHAN_BODY, sound_step_left, 1, ATTN_NORM, 0);
}

static void jorg_step_right(edict_t *self)
{
    gi.sound(self, CHAN_BODY, sound_step_right, 1, ATTN_NORM, 0);
}

void jorg_stand(edict_t *self)
{
    self->monsterinfo.currentmove = &jorg_move_stand;
}

static const mframe_t jorg_frames_run[] = {
    { ai_run, 17, jorg_step_left },
    { ai_run, 0,  NULL },
    { ai_run, 0,  NULL },
    { ai_run, 0,  NULL },
    { ai_run, 12, NULL },
    { ai_run, 8,  NULL },
    { ai_run, 10, NULL },
    { ai_run, 33, jorg_step_right },
    { ai_run, 0,  NULL },
    { ai_run, 0,  NULL },
    { ai_run, 0,  NULL },
    { ai_run, 9,  NULL },
    { ai_run, 9,  NULL },
    { ai_run, 9,  NULL }
};
const mmove_t jorg_move_run = {FRAME_walk06, FRAME_walk19, jorg_frames_run, NULL};

//
// walk
//

static const mframe_t jorg_frames_start_walk[] = {
    { ai_walk,    5,  NULL },
    { ai_walk,    6,  NULL },
    { ai_walk,    7,  NULL },
    { ai_walk,    9,  NULL },
    { ai_walk,    15, NULL }
};
const mmove_t jorg_move_start_walk = {FRAME_walk01, FRAME_walk05, jorg_frames_start_walk, NULL};

static const mframe_t jorg_frames_walk[] = {
    { ai_walk, 17,    NULL },
    { ai_walk, 0, NULL },
    { ai_walk, 0, NULL },
    { ai_walk, 0, NULL },
    { ai_walk, 12,    NULL },
    { ai_walk, 8, NULL },
    { ai_walk, 10,    NULL },
    { ai_walk, 33,    NULL },
    { ai_walk, 0, NULL },
    { ai_walk, 0, NULL },
    { ai_walk, 0, NULL },
    { ai_walk, 9, NULL },
    { ai_walk, 9, NULL },
    { ai_walk, 9, NULL }
};
const mmove_t jorg_move_walk = {FRAME_walk06, FRAME_walk19, jorg_frames_walk, NULL};

static const mframe_t jorg_frames_end_walk[] = {
    { ai_walk,    11, NULL },
    { ai_walk,    0,  NULL },
    { ai_walk,    0,  NULL },
    { ai_walk,    0,  NULL },
    { ai_walk,    8,  NULL },
    { ai_walk,    -8, NULL }
};
const mmove_t jorg_move_end_walk = {FRAME_walk20, FRAME_walk25, jorg_frames_end_walk, NULL};

void jorg_walk(edict_t *self)
{
    self->monsterinfo.currentmove = &jorg_move_walk;
}

void jorg_run(edict_t *self)
{
    if (self->monsterinfo.aiflags & AI_STAND_GROUND)
        self->monsterinfo.currentmove = &jorg_move_stand;
    else
        self->monsterinfo.currentmove = &jorg_move_run;
}

static const mframe_t jorg_frames_pain3[] = {
    { ai_move,    -28,    NULL },
    { ai_move,    -6, NULL },
    { ai_move,    -3, jorg_step_left },
    { ai_move,    -9, NULL },
    { ai_move,    0,  jorg_step_right },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    -7, NULL },
    { ai_move,    1,  NULL },
    { ai_move,    -11,    NULL },
    { ai_move,    -4, NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    10, NULL },
    { ai_move,    11, NULL },
    { ai_move,    0,  NULL },
    { ai_move,    10, NULL },
    { ai_move,    3,  NULL },
    { ai_move,    10, NULL },
    { ai_move,    7,  jorg_step_left },
    { ai_move,    17, NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  jorg_step_right }
};
const mmove_t jorg_move_pain3 = {FRAME_pain301, FRAME_pain325, jorg_frames_pain3, jorg_run};

static const mframe_t jorg_frames_pain2[] = {
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL }
};
const mmove_t jorg_move_pain2 = {FRAME_pain201, FRAME_pain203, jorg_frames_pain2, jorg_run};

static const mframe_t jorg_frames_pain1[] = {
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL }
};
const mmove_t jorg_move_pain1 = {FRAME_pain101, FRAME_pain103, jorg_frames_pain1, jorg_run};

static const mframe_t jorg_frames_death1[] = {
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },       // 10
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },       // 20
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },       // 30
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },       // 40
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  MakronToss },
    { ai_move,    0,  BossExplode }     // 50
};
const mmove_t jorg_move_death = {FRAME_death01, FRAME_death50, jorg_frames_death1, jorg_dead};

static const mframe_t jorg_frames_attack2[] = {
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  jorgBFG },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL }
};
const mmove_t jorg_move_attack2 = {FRAME_attak201, FRAME_attak213, jorg_frames_attack2, jorg_run};

static const mframe_t jorg_frames_start_attack1[] = {
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL },
    { ai_charge,  0,  NULL }
};
const mmove_t jorg_move_start_attack1 = {FRAME_attak101, FRAME_attak108, jorg_frames_start_attack1, jorg_attack1};

static const mframe_t jorg_frames_attack1[] = {
    { ai_charge,  0,  jorg_firebullet },
    { ai_charge,  0,  jorg_firebullet },
    { ai_charge,  0,  jorg_firebullet },
    { ai_charge,  0,  jorg_firebullet },
    { ai_charge,  0,  jorg_firebullet },
    { ai_charge,  0,  jorg_firebullet }
};
const mmove_t jorg_move_attack1 = {FRAME_attak109, FRAME_attak114, jorg_frames_attack1, jorg_reattack1};

static const mframe_t jorg_frames_end_attack1[] = {
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL },
    { ai_move,    0,  NULL }
};
const mmove_t jorg_move_end_attack1 = {FRAME_attak115, FRAME_attak118, jorg_frames_end_attack1, jorg_run};

static void jorg_reattack1(edict_t *self)
{
    if (visible(self, self->enemy)) {
        if (random() < 0.9f)
            self->monsterinfo.currentmove = &jorg_move_attack1;
        else {
            self->s.sound = 0;
            self->monsterinfo.currentmove = &jorg_move_end_attack1;
        }
    } else {
        self->s.sound = 0;
        self->monsterinfo.currentmove = &jorg_move_end_attack1;
    }
}

static void jorg_attack1(edict_t *self)
{
    self->monsterinfo.currentmove = &jorg_move_attack1;
}

void jorg_pain(edict_t *self, edict_t *other, float kick, int damage)
{
    if (self->health < (self->max_health / 2))
        self->s.skinnum = 1;

    self->s.sound = 0;

    if (level.framenum < self->pain_debounce_framenum)
        return;

    // Lessen the chance of him going into his pain frames if he takes little damage
    if (damage <= 40)
        if (random() <= 0.6f)
            return;

    /*
    If he's entering his attack1 or using attack1, lessen the chance of him
    going into pain
    */

    if ((self->s.frame >= FRAME_attak101) && (self->s.frame <= FRAME_attak108))
        if (random() <= 0.005f)
            return;

    if ((self->s.frame >= FRAME_attak109) && (self->s.frame <= FRAME_attak114))
        if (random() <= 0.00005f)
            return;

    if ((self->s.frame >= FRAME_attak201) && (self->s.frame <= FRAME_attak208))
        if (random() <= 0.005f)
            return;

    self->pain_debounce_framenum = level.framenum + 3 * BASE_FRAMERATE;
    if (skill->value == 3)
        return;     // no pain anims in nightmare

    if (damage <= 50) {
        gi.sound(self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM, 0);
        self->monsterinfo.currentmove = &jorg_move_pain1;
    } else if (damage <= 100) {
        gi.sound(self, CHAN_VOICE, sound_pain2, 1, ATTN_NORM, 0);
        self->monsterinfo.currentmove = &jorg_move_pain2;
    } else {
        if (random() <= 0.3f) {
            gi.sound(self, CHAN_VOICE, sound_pain3, 1, ATTN_NORM, 0);
            self->monsterinfo.currentmove = &jorg_move_pain3;
        }
    }
}

static void jorgBFG(edict_t *self)
{
    vec3_t  forward, right;
    vec3_t  start;
    vec3_t  dir;
    vec3_t  vec;

    AngleVectors(self->s.angles, forward, right, NULL);
    G_ProjectSource(self->s.origin, monster_flash_offset[MZ2_JORG_BFG_1], forward, right, start);

    VectorCopy(self->enemy->s.origin, vec);
    vec[2] += self->enemy->viewheight;
    VectorSubtract(vec, start, dir);
    VectorNormalize(dir);
    gi.sound(self, CHAN_VOICE, sound_attack2, 1, ATTN_NORM, 0);
    monster_fire_bfg(self, start, dir, 50, 300, 100, 200, MZ2_JORG_BFG_1);
}

static void jorg_firebullet_right(edict_t *self)
{
    vec3_t  forward, right, target;
    vec3_t  start;

    AngleVectors(self->s.angles, forward, right, NULL);
    G_ProjectSource(self->s.origin, monster_flash_offset[MZ2_JORG_MACHINEGUN_R1], forward, right, start);

    VectorMA(self->enemy->s.origin, -0.2f, self->enemy->velocity, target);
    target[2] += self->enemy->viewheight;
    VectorSubtract(target, start, forward);
    VectorNormalize(forward);

    monster_fire_bullet(self, start, forward, 6, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, MZ2_JORG_MACHINEGUN_R1);
}

static void jorg_firebullet_left(edict_t *self)
{
    vec3_t  forward, right, target;
    vec3_t  start;

    AngleVectors(self->s.angles, forward, right, NULL);
    G_ProjectSource(self->s.origin, monster_flash_offset[MZ2_JORG_MACHINEGUN_L1], forward, right, start);

    VectorMA(self->enemy->s.origin, -0.2f, self->enemy->velocity, target);
    target[2] += self->enemy->viewheight;
    VectorSubtract(target, start, forward);
    VectorNormalize(forward);

    monster_fire_bullet(self, start, forward, 6, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, MZ2_JORG_MACHINEGUN_L1);
}

static void jorg_firebullet(edict_t *self)
{
    jorg_firebullet_left(self);
    jorg_firebullet_right(self);
}

void jorg_attack(edict_t *self)
{
    if (random() <= 0.75f) {
        gi.sound(self, CHAN_VOICE, sound_attack1, 1, ATTN_NORM, 0);
        self->s.sound = gi.soundindex("boss3/w_loop.wav");
        self->monsterinfo.currentmove = &jorg_move_start_attack1;
    } else {
        gi.sound(self, CHAN_VOICE, sound_attack2, 1, ATTN_NORM, 0);
        self->monsterinfo.currentmove = &jorg_move_attack2;
    }
}

static void jorg_dead(edict_t *self)
{
}

void jorg_die(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
    gi.sound(self, CHAN_VOICE, sound_death, 1, ATTN_NORM, 0);
    self->deadflag = DEAD_DEAD;
    self->takedamage = DAMAGE_NO;
    self->s.sound = 0;
    self->count = 0;
    self->monsterinfo.currentmove = &jorg_move_death;
}

bool Jorg_CheckAttack(edict_t *self)
{
    vec3_t  spot1, spot2;
    vec3_t  temp;
    float   chance;
    trace_t tr;
    int         enemy_range;
    float       enemy_yaw;

    if (self->enemy->health > 0) {
        // see if any entities are in the way of the shot
        VectorCopy(self->s.origin, spot1);
        spot1[2] += self->viewheight;
        VectorCopy(self->enemy->s.origin, spot2);
        spot2[2] += self->enemy->viewheight;

        tr = gi.trace(spot1, NULL, NULL, spot2, self, CONTENTS_SOLID | CONTENTS_MONSTER | CONTENTS_SLIME | CONTENTS_LAVA);

        // do we have a clear shot?
        if (tr.ent != self->enemy)
            return false;
    }

    enemy_range = range(self, self->enemy);
    VectorSubtract(self->enemy->s.origin, self->s.origin, temp);
    enemy_yaw = vectoyaw(temp);

    self->ideal_yaw = enemy_yaw;

    // melee attack
    if (enemy_range == RANGE_MELEE) {
        if (self->monsterinfo.melee)
            self->monsterinfo.attack_state = AS_MELEE;
        else
            self->monsterinfo.attack_state = AS_MISSILE;
        return true;
    }

// missile attack
    if (!self->monsterinfo.attack)
        return false;

    if (level.framenum < self->monsterinfo.attack_finished)
        return false;

    if (enemy_range == RANGE_FAR)
        return false;

    if (self->monsterinfo.aiflags & AI_STAND_GROUND) {
        chance = 0.4f;
    } else if (enemy_range == RANGE_MELEE) {
        chance = 0.8f;
    } else if (enemy_range == RANGE_NEAR) {
        chance = 0.4f;
    } else if (enemy_range == RANGE_MID) {
        chance = 0.2f;
    } else {
        return false;
    }

    if (random() < chance) {
        self->monsterinfo.attack_state = AS_MISSILE;
        self->monsterinfo.attack_finished = level.framenum + 2 * random() * BASE_FRAMERATE;
        return true;
    }

    if (self->flags & FL_FLY) {
        if (random() < 0.3f)
            self->monsterinfo.attack_state = AS_SLIDING;
        else
            self->monsterinfo.attack_state = AS_STRAIGHT;
    }

    return false;
}

void MakronPrecache(void);

static void jorg_precache(void)
{
    sound_pain1 = gi.soundindex("boss3/bs3pain1.wav");
    sound_pain2 = gi.soundindex("boss3/bs3pain2.wav");
    sound_pain3 = gi.soundindex("boss3/bs3pain3.wav");
    sound_death = gi.soundindex("boss3/bs3deth1.wav");
    sound_attack1 = gi.soundindex("boss3/bs3atck1.wav");
    sound_attack2 = gi.soundindex("boss3/bs3atck2.wav");
    sound_search1 = gi.soundindex("boss3/bs3srch1.wav");
    sound_search2 = gi.soundindex("boss3/bs3srch2.wav");
    sound_search3 = gi.soundindex("boss3/bs3srch3.wav");
    sound_idle = gi.soundindex("boss3/bs3idle1.wav");
    sound_step_left = gi.soundindex("boss3/step1.wav");
    sound_step_right = gi.soundindex("boss3/step2.wav");
    sound_firegun = gi.soundindex("boss3/xfire.wav");

    MakronPrecache();
}

/*QUAKED monster_jorg (1 .5 0) (-80 -80 0) (90 90 140) Ambush Trigger_Spawn Sight
*/
void SP_monster_jorg(edict_t *self)
{
    if (deathmatch->value) {
        G_FreeEdict(self);
        return;
    }

    G_AddPrecache(jorg_precache);

    self->movetype = MOVETYPE_STEP;
    self->solid = SOLID_BBOX;
    self->s.modelindex = gi.modelindex("models/monsters/boss3/jorg/tris.md2");
    self->s.modelindex2 = gi.modelindex("models/monsters/boss3/rider/tris.md2");
    VectorSet(self->mins, -80, -80, 0);
    VectorSet(self->maxs, 80, 80, 140);

    self->health = 3000;
    self->gib_health = -2000;
    self->mass = 1000;

    self->pain = jorg_pain;
    self->die = jorg_die;
    self->monsterinfo.stand = jorg_stand;
    self->monsterinfo.walk = jorg_walk;
    self->monsterinfo.run = jorg_run;
    self->monsterinfo.dodge = NULL;
    self->monsterinfo.attack = jorg_attack;
    self->monsterinfo.search = jorg_search;
    self->monsterinfo.melee = NULL;
    self->monsterinfo.sight = NULL;
    self->monsterinfo.checkattack = Jorg_CheckAttack;
    gi.linkentity(self);

    self->monsterinfo.currentmove = &jorg_move_stand;
    self->monsterinfo.scale = MODEL_SCALE;

    walkmonster_start(self);
}
