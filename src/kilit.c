/* kilit.c
 * Kilit dosyası ile ilgili işlemleri yapan fonksiyon kütüphanesi  
 * BSM308 Proje / Tasarım Ödevi
 * Mayıs, 2021
*/
#include "kilit.h"

void print_jrb(JRB j)
{
    JRB tmp;
    Kilit *kilit;

    jrb_traverse(tmp, j)
    {
        kilit = (Kilit *)tmp->val.v;
        printf("Key=%s Val=%s\n", kilit->key, kilit->val);
    }
}
void encrypt_file(IS is2, JRB kilitler, char *hedef_dosya_adi);
void decrypt_file(IS is, JRB kilitlerDec, char *hedef_dosya_adi);

void fill_jrb_from_kilit_file(JRB kilit_encrypt, JRB kilit_decrypt)
{
    IS is;
    Kilit *p;

    //kilit dosyası okunuyor.
    is = new_inputstruct(".kilit");
    if (is == NULL)
    {
        perror("Huffman kilit dosyası bulunamadı!");
        exit(1);
    }

    /* Read each line with get_line(). */
    while (get_line(is) >= 0)
    {

        // ilk ve son satır değilse
        // ilk satır daima { başlar ve son satır daima } ile biter.
        if (strchr(is->fields[0], '{') == NULL && strchr(is->fields[0], '}') == NULL)
        {

            p = malloc(sizeof(Kilit));

            if (strchr(is->fields[0], ':') != NULL)
            {
                remove_str_character(is->fields[0], ':');
            }
            else
            {
                printf("KILIT DOSYASI HATALI!\n");
                printf("Hatalı Satır Numarası: %d, \nHatalı Satır: %sHata: ':' karakteri yok!\n", is->line, is->text1);
                exit(1);
            }

            if (strchr(is->fields[0], '"') != NULL)
                remove_str_character(is->fields[0], '"');

            if (strchr(is->fields[1], '"') != NULL)
                remove_str_character(is->fields[1], '"');

            if (strchr(is->fields[1], ',') != NULL)
                remove_str_character(is->fields[1], ',');

            p->key = (char *)malloc(sizeof(char) * (strlen(is->fields[0]) + 1));
            strcpy(p->key, is->fields[0]);

            p->val = (char *)malloc(sizeof(char) * (strlen(is->fields[1]) + 1));
            strcpy(p->val, is->fields[1]);

            (void)jrb_insert_str(kilit_encrypt, p->key, new_jval_v((void *)p));
            (void)jrb_insert_str(kilit_decrypt, p->val, new_jval_v((void *)p));
        }
    }
}