/*

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/
#ifndef _NUMOBJ_H
#define _NUMOBJ_H
struct oper_s;
typedef struct oper_s *oper_t;

extern obj_t NUM_OBJ;

extern void numobj_init(void);
extern int calc2_num_num(oper_t, uval_t, uint8_t, uval_t, uint8_t);
extern int calc1_num(oper_t, uval_t, uint8_t);
#endif