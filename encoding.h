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
#ifndef _ENCODING_H_
#define _ENCODING_H_
#include "libtree.h"
#include "inttypes.h"

struct encoding_s;

struct trans_s {
    uint32_t start;
    unsigned end : 24;
    unsigned offset : 8;
    struct avltree_node node;
};

struct escape_s {
    size_t len;
    uint8_t code;
};


extern struct encoding_s *new_encoding(const str_t *);
extern struct trans_s *new_trans(struct trans_s *, struct encoding_s *);
extern uint16_t find_trans(uint32_t, struct encoding_s *);
extern struct escape_s *new_escape(const uint8_t *, const uint8_t *, uint8_t, struct encoding_s *);
extern uint32_t find_escape(const uint8_t *, const uint8_t *, struct encoding_s *);
extern void init_encoding(int);
extern void destroy_encoding(void);
#endif
