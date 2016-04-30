/*
    $Id$

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
#ifndef _MISC_H_
#define _MISC_H_
#include "inttypes.h"

enum output_mode_e {
    OUTPUT_CBM, OUTPUT_RAW, OUTPUT_NONLINEAR, OUTPUT_FLAT, OUTPUT_XEX,
    OUTPUT_APPLE, OUTPUT_IHEX, OUTPUT_SREC
};

enum label_mode_e {
    LABEL_64TASS, LABEL_VICE, LABEL_DUMP
};

struct file_s;

struct arguments_s {
    unsigned warning:1;
    unsigned caret:1;
    unsigned quiet:1;
    unsigned toascii:1;
    unsigned monitor:1;
    unsigned source:1;
    unsigned longbranch:1;
    unsigned longaddr:1;
    unsigned tasmcomp:1;
    unsigned shadow_check:1;
    unsigned verbose:1;
    uint8_t caseinsensitive;
    const char *output;
    const struct cpu_s *cpumode;
    const char *label;
    const char *list;
    const char *make;
    const char *error;
    enum output_mode_e output_mode;
    uint8_t tab_size;
    enum label_mode_e label_mode;
};

#define ignore() while(pline[lpoint.pos]==0x20 || pline[lpoint.pos]==0x09) lpoint.pos++
#define here() pline[lpoint.pos]

extern void tfree(void);
extern void tinit(void);
extern int testarg(int,char **,struct file_s *);
extern struct arguments_s arguments;
extern int str_hash(const str_t *);
extern int str_cmp(const str_t *, const str_t *);
extern void str_cfcpy(str_t *, const str_t *);
extern void str_cpy(str_t *, const str_t *);
extern linecpos_t calcpos(const uint8_t *, size_t, int);

#endif
