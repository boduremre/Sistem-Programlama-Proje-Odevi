/* kilit.h
   Emre Bodur, Ayşe Merve Candaş, Hüseyin Eski, Sadık Sinai
   BSM308 Proje / Tasarım Ödevi
   Mayıs, 2021
*/

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

/* @name  : kilit_dosyasindan_jrb_doldur
 * @desc  : Bu fonksiyon kilit dosyasını okur(parse eder) ve parametre olarak verilen ağaçları doldurur.
 * @params: JRB kilit_sifrelenmis, JRB kilit_cozumlenmis
 * @return: void
 */
void kilit_dosyasindan_jrb_doldur(JRB kilit_sifrelenmis, JRB kilit_cozumlenmis);

void encrypt_file(IS is2, JRB kilitler, char *hedef_dosya_adi);

/* @name  : dosyanin_sifresini_coz
 * @desc  : Şifreli giriş metnini kilit dosyasından okunarak doldurulan jrb ağacına göre çözümler ve hedef dosyaya yazar.
 * @params: IS is, JRB kilit_cozumlenmis, char *hedef_dosya_adi
 * @return: void
 */
void dosyanin_sifresini_coz(IS is, JRB kilitlerDec, char *hedef_dosya_adi);

#endif
