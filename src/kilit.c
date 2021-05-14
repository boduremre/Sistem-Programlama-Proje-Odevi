/* kilit.c
 * Kilit dosyası ile ilgili işlemleri yapan fonksiyon kütüphanesi  
 * BSM308 Proje / Tasarım Ödevi
 * Mayıs, 2021
*/
#include "kilit.h"

/* @name  : print_jrb
 * @desc  : Parametre olarak verilen JRB ağacının içeriğini ekrana yazdırır (Traverse eder).
 * @params: JRB j
 * @return: void
 */
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

// BU FONKSİYONDA HATA VAR ARKADAŞLAR KONTROL EDİP DÜZENLER MİSİNİZ?
/* @name  : fill_jrb_from_kilit_file
 * @desc  : Bu fonksiyon kilit dosyasını okur(parse eder) ve parametre olarak verilen ağaçları doldurur.
 * @params: JRB kilit_encrypt, JRB kilit_decrypt
 * @return: void
 */
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
        if (strchr(is->text1, '{') == NULL && strchr(is->text1, '}') == NULL)
        {
            p = malloc(sizeof(Kilit)); // bellekten alan ayrılıyor.
            
            // Bu fonksiyon içerisinde ayırma işlemlerinin strtok kullanılarak yapılması gerektiğini düşünüyorum.
            // 
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

/* @name  : encrypt_file
 * @desc  : Giriş metnini kilit dosyasından okunarak doldurulan jrb ağacına göre şifreler ve hedef dosyaya yazar.
 * @params: IS is, JRB kilit_decrypt, char *hedef_dosya_adi
 * @return: void
 */
void encrypt_file(IS is, JRB kilit_encrypt, char *hedef_dosya_adi)
{
    JRB rnode;
    Kilit *k1;

    FILE *fptr;
    fptr = fopen(hedef_dosya_adi, "w");
    if (fptr == NULL)
    {
        printf("Dosya oluşturulamadı!");
        exit(1);
    }

    /* Read each line with get_line().  Print out each word. */
    while (get_line(is) >= 0)
    {
        for (int i = 0; i < is->NF; i++)
        {
            if (is->fields[i] != NULL)
            {
                rnode = jrb_find_str(kilit_encrypt, is->fields[i]);
                //printf("%d: %s\n", is->line, is->fields[i]);
                if (rnode != NULL)
                {
                    k1 = (Kilit *)rnode->val.v;
                    fprintf(fptr, "%s ", k1->val);
                    //printf("%s için bir şifre %s \n", is->fields[i], k1->val);
                }
                else
                {
                    fprintf(fptr, "%s ", is->fields[i]);
                }
            }
        }
    }

    fclose(fptr);
}

/* @name  : decrypt_file
 * @desc  : Şifreli giriş metnini kilit dosyasından okunarak doldurulan jrb ağacına göre çözümler ve hedef dosyaya yazar.
 * @params: IS is, JRB kilit_decrypt, char *hedef_dosya_adi
 * @return: void
 */
void decrypt_file(IS is, JRB kilit_decrypt, char *hedef_dosya_adi)
{
    JRB jrb_decripted, jrb_tmp;
    Kilit *kilit_decripted;

    FILE *fptr;
    fptr = fopen(hedef_dosya_adi, "w");
    if (fptr == NULL)
    {
        printf("Dosya oluşturulamadı!");
        exit(1);
    }

    // /* Read each line with get_line().  Print out each word. */
    while (get_line(is) >= 0)
    {
        for (int i = 0; i < is->NF; i++)
        {
            if (is->fields[i] != NULL)
            {
                jrb_decripted = jrb_find_str(kilit_decrypt, is->fields[i]);

                if (jrb_decripted != NULL)
                {
                    kilit_decripted = (Kilit *)jrb_decripted->val.v;
                    fprintf(fptr, "%s ", kilit_decripted->key);
                    // printf("%s şifresi için bulunan kelime %s \n", is->fields[i], k1->key);
                }
                else
                {
                    fprintf(fptr, "%s ", is->fields[i]);
                }
            }
        }
    }

    fclose(fptr);
}

