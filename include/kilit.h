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

/* @name  : print_jrb
 * @desc  : Parametre olarak verilen JRB ağacının içeriğini ekrana yazdırır (Traverse eder).
 * @params: JRB j
 * @return: void
 */
void print_jrb();

/* @name  : fill_jrb_from_kilit_file
 * @desc  : Bu fonksiyon kilit dosyasını okur(parse eder) ve parametre olarak verilen ağaçları doldurur.
 * @params: JRB kilit_encrypt, JRB kilit_decrypt
 * @return: void
 */
void fill_jrb_from_kilit_file(JRB kilit_encrypt, JRB kilit_decrypt);

/* @name  : encrypt_file
 * @desc  : Giriş metnini kilit dosyasından okunarak doldurulan jrb ağacına göre şifreler ve hedef dosyaya yazar.
 * @params: IS is, JRB kilit_decrypt, char *hedef_dosya_adi
 * @return: void
 */
void encrypt_file(IS is2, JRB kilitler, char *hedef_dosya_adi);

/* @name  : decrypt_file
 * @desc  : Şifreli giriş metnini kilit dosyasından okunarak doldurulan jrb ağacına göre çözümler ve hedef dosyaya yazar.
 * @params: IS is, JRB kilit_decrypt, char *hedef_dosya_adi
 * @return: void
 */
void decrypt_file(IS is, JRB kilitlerDec, char *hedef_dosya_adi);

#endif
