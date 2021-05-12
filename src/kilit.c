/* kilit.c
 * Kilit dosyası ile ilgili işlemleri yapan fonksiyon kütüphanesi  
 * BSM308 Proje / Tasarım Ödevi
 * Mayıs, 2021
*/
#include "kilit.h"

void print_jrb();
void fill_jrb_from_kilit_file(JRB kilit_encrypt, JRB kilit_decrypt);
void encrypt_file(IS is2, JRB kilitler, char *hedef_dosya_adi);
void decrypt_file(IS is, JRB kilitlerDec, char *hedef_dosya_adi);