/*
    $Id: labelobj.c 1797 2019-01-12 16:48:47Z soci $

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
#include "labelobj.h"
#include <string.h>
#include "values.h"
#include "error.h"
#include "unicode.h"
#include "file.h"

#include "strobj.h"
#include "typeobj.h"
#include "errorobj.h"

static Type obj;

Type *const LABEL_OBJ = &obj;

static MUST_CHECK Obj *create(Obj *v1, linepos_t epoint) {
    switch (v1->obj->type) {
    case T_NONE:
    case T_ERROR:
    case T_LABEL: return val_reference(v1);
    default: break;
    }
    return (Obj *)new_error_conv(v1, LABEL_OBJ, epoint);
}

static FAST_CALL void destroy(Obj *o1) {
    Label *v1 = (Label *)o1;
    const struct file_s *cfile = v1->file_list->file;
    if ((size_t)(v1->name.data - cfile->data) >= cfile->len) free((char *)v1->name.data);
    if (v1->name.data != v1->cfname.data) free((uint8_t *)v1->cfname.data);
    val_destroy(v1->value);
}

static FAST_CALL void garbage(Obj *o1, int i) {
    Label *v1 = (Label *)o1;
    Obj *v;
    const struct file_s *cfile;
    switch (i) {
    case -1:
        v1->value->refcount--;
        return;
    case 0:
        cfile = v1->file_list->file;
        if ((size_t)(v1->name.data - cfile->data) >= cfile->len) free((char *)v1->name.data);
        if (v1->name.data != v1->cfname.data) free((uint8_t *)v1->cfname.data);
        return;
    case 1:
        v = v1->value;
        if ((v->refcount & SIZE_MSB) != 0) {
            v->refcount -= SIZE_MSB - 1;
            v->obj->garbage(v, 1);
        } else v->refcount++;
        return;
    }
}

static FAST_CALL bool same(const Obj *o1, const Obj *o2) {
    const Label *v1 = (const Label *)o1, *v2 = (const Label *)o2;
    return o2->obj == LABEL_OBJ
        && v1->epoint.pos == v2->epoint.pos
        && v1->epoint.line == v2->epoint.line
        && v1->file_list == v2->file_list
        && v1->strength == v2->strength
        && str_cmp(&v1->name, &v2->name) == 0
        && str_cmp(&v1->cfname, &v2->cfname) == 0
        && (v1->value == v2->value || v1->value->obj->same(v1->value, v2->value));
}

static MUST_CHECK Obj *repr(Obj *o1, linepos_t epoint, size_t maxlen) {
    Label *v1 = (Label *)o1;
    size_t len, len2;
    uint8_t *s;
    Str *v;
    if (epoint == NULL) return NULL;
    switch (v1->name.data[0]) {
    case '+':
    case '-': len = 1; break;
    case '#':
    case '.': len = 0; break;
    default: len = v1->name.len;
    }
    len2 = len + 10;
    if (len2 > maxlen) return NULL;
    v = new_str2(len2);
    if (v == NULL) return NULL;
    v->chars = calcpos(v1->name.data, len);
    s = v->data;
    memcpy(s, "<label '", 8);
    s += 8;
    memcpy(s, v1->name.data, len);
    s[len] = '\'';
    s[len + 1] = '>';
    return &v->v;
}

static MUST_CHECK Obj *str(Obj *o1, linepos_t UNUSED(epoint), size_t maxlen) {
    Label *v1 = (Label *)o1;
    size_t len, chars;
    Str *v;
    switch (v1->name.data[0]) {
    case '+':
    case '-': len = 1; break;
    case '#':
    case '.': return NULL;
    default: len = v1->name.len;
    }
    chars = calcpos(v1->name.data, len);
    if (chars > maxlen) return NULL;
    v = new_str2(len);
    if (v == NULL) return NULL;
    v->chars = chars;
    memcpy(v->data, v1->name.data, len);
    return &v->v;
}

void labelobj_init(void) {
    new_type(&obj, T_LABEL, "label", sizeof(Label));
    obj.create = create;
    obj.destroy = destroy;
    obj.garbage = garbage;
    obj.same = same;
    obj.repr = repr;
    obj.str = str;
}
