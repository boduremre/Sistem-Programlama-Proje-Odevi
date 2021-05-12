/* kilit.h
 * Kilit dosyası ile ilgili işlemleri yapan fonksiyon kütüphanesi   
 * BSM308 Proje / Tasarım Ödevi
 * Mayıs, 2021
*/
#ifndef _KILIT_H_
#define _KILIT_H_

#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"
#include "mrbdr.h"

/* @name  : Kilit
 * @desc  : .kilit dosyasından okunan key->val değerlerini tutan yapıdır.
 * @params: char *key; char *val;
 */
typedef struct
{
    char *key;
    char *val;
} Kilit;

// jrb ağacının içerğini ekrana yazan bir metot yazılmalı - Emre
void print_jrb();

// json okuma ve parse etme işlemleri yapılmalı - Ayşe Merve ve Emre
void fill_jrb_from_kilit_file(JRB kilit_encrypt, JRB kilit_decrypt);

//okunan metni kilit vasıtasıyla şifreleyen bir fonksiyon yazılmalı Sadık, Hüseyin, Emre, Ayşe Merve
void encrypt_file(IS is2, JRB kilitler, char *hedef_dosya_adi);

// şifreli metni kilit vasıtasıyla çözen bir fonksiyon yazılmalı Sadık, Hüseyin, Emre, Ayşe Merve
void decrypt_file(IS is, JRB kilitlerDec, char *hedef_dosya_adi);

#endif
