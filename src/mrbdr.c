/* mrbdr.c
 * Çeşitli işlemleri yapmak için fonksiyon kütüphanesi   
 * BSM308 Proje / Tasarım Ödevi
 * Mayıs, 2021
*/
#include "mrbdr.h"

/* @name  : remove_str_character
 * @desc  : Text içerisinde belirtilen karakteri siler.
 * @params: char *s, char delimeter
 * @return: void
 */
void remove_str_character(char *s, char delimeter)
{
    const char *d = s;
    do
    {
        while (*d == delimeter)
        {
            ++d;
        }
    } while (*s++ = *d++);
}