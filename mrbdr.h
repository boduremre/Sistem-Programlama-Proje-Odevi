/* mrbdr.h
   Emre Bodur, Ayşe Merve Candaş, Hüseyin Eski, Sadık Sinai
   BSM308 Proje / Tasarım Ödevi
   Mayıs, 2021
*/
#ifndef _MRBDR_H_
#define _MRBDR_H_

/* @name  : remove_str_character
 * @desc  : Parametre olarak verilen metin değişkenin yine parametre olarak verilen silinecek_karakter değişkenini siler.
 * @params: char *metin, char silinecek_karakter
 * @return: void
 */
void metinden_karakter_sil(char *metin, char silinecek_karakter);

/* @name  : tirnak_isareti_say
 * @desc  : Parametre olarak verilen metin içerisinde " karakterini sayar.
 * @params: const char *metin, char karakter
 * @url   : https://stackoverflow.com/questions/23170096/how-to-count-single-or-double-quotes
 * @return: void
 */
int tirnak_isareti_say(const char *metin, char karakter);
#endif
