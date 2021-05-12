/* Copyright (C) 2021 Emre Bodur */

#ifndef _KILIT_H_
#define _KILIT_H_

#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"
#include "mrbdr.h"

typedef struct
{
    char *key;
    char *val;
} Kilit;

void print_jrb();
void fill_jrb_from_kilit_file(JRB kilit_encrypt, JRB kilit_decrypt);
void encrypt_file(IS is2, JRB kilitler, char *hedef_dosya_adi);
void decrypt_file(IS is, JRB kilitlerDec, char *hedef_dosya_adi);

#endif