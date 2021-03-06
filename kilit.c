/* kilit.c
   Emre Bodur, Ayşe Merve Candaş, Hüseyin Eski, Sadık Sinai
   BSM308 Proje / Tasarım Ödevi
   Mayıs, 2021
*/
#include "kilit.h"

/* @name  : jrb_ekrana_yazdir
 * @desc  : Parametre olarak verilen JRB ağacını ekrana yazar (traverse eder).
 * @params: JRB jrb_agaci
 * @return: void
 */
void jrb_ekrana_yazdir(JRB jrb_agaci)
{
    JRB jrb_gecici;
    Kilit *kilit;

    jrb_traverse(jrb_gecici, jrb_agaci)
    {
        kilit = (Kilit *)jrb_gecici->val.v;
        printf("Key=%s Val=%s\n", kilit->key, kilit->val);
    }
}

/* @name  : kilit_dosyasindan_jrb_doldur
 * @desc  : Bu fonksiyon kilit dosyasını okur(parse eder) ve parametre olarak verilen ağaçları doldurur.
 * @params: JRB kilit_sifrelenmis, JRB kilit_cozumlenmis
 * @return: void
 */
void kilit_dosyasindan_jrb_doldur(JRB kilit_sifrelenmis, JRB kilit_cozumlenmis)
{
    IS my_is;
    Kilit *kilit;
    char *parcalanmis_text;
    int a = 0;

    //kilit dosyası okunuyor.
    my_is = new_inputstruct(".kilit");
    if (my_is == NULL)
    {
        perror("Huffman kilit dosyası bulunamadı!");
        printf("Program sonlandirildi!\n");
        exit(1);
    }

    /* Read each line with get_line(). */
    while (get_line(my_is) >= 0)
    {
        // ilk ve son satır değilse
        // ilk satır daima { başlar ve son satır daima } ile biter.
        if (strchr(my_is->text1, '{') == NULL && strchr(my_is->text1, '}') == NULL)
        {
            // kilit için bellekten alan ayrılıyor.
            kilit = malloc(sizeof(Kilit));

            // okunan satırda : işaretinin varlığı kontrol ediliyor.
            if (strchr(my_is->text1, ':') == NULL)
            {
                printf("KILIT DOSYASI HATALI!\n");
                printf("Hatalı Satır Numarası: %d, \nHatalı Satır: %sHata: ':' karakteri yok!\n", my_is->line, my_is->text1);
                exit(1);
            }

            if (strchr(my_is->text1, '\"') == NULL || tirnak_isareti_say(my_is->text1, '\"') < 4)
            {
                printf("KILIT DOSYASI HATALI!\n");
                printf("Hatalı Satır Numarası: %d, \nHatalı Satır: %sHata: '\"' karakteri yok!\n", my_is->line, my_is->text1);
                exit(1);
            }

            parcalanmis_text = strtok(my_is->text1, ":");
            while (parcalanmis_text != NULL)
            {
                metinden_karakter_sil(parcalanmis_text, ' ');  // boşluk karakteri siliniyor
                metinden_karakter_sil(parcalanmis_text, '\n'); // satır karakteri siliniyor
                metinden_karakter_sil(parcalanmis_text, '"');  // çift tırnak karakteri siliniyor

                if (parcalanmis_text != NULL)
                {
                    if (a % 2 == 0)
                    {
                        kilit->key = (char *)malloc(sizeof(char) * (strlen(parcalanmis_text) + 1));
                        strcpy(kilit->key, parcalanmis_text);
                        //printf("%d. k->key=%s\n", i, k->key);
                    }
                    else
                    {
                        metinden_karakter_sil(parcalanmis_text, ','); // val sonundaki virgüller siliniyor.
                        kilit->val = (char *)malloc(sizeof(char) * (strlen(parcalanmis_text) + 1));
                        strcpy(kilit->val, parcalanmis_text);
                        //printf("%d. k->key=%s, k->val=%s\n", i, k->key, k->val);
                    }

                    a++;
                }

                parcalanmis_text = strtok(NULL, ":");
            }

            //printf("%d. k->key=%s, k->val=%s\n", i, k->key, k->val);
            (void)jrb_insert_str(kilit_sifrelenmis, kilit->key, new_jval_v((void *)kilit));
            (void)jrb_insert_str(kilit_cozumlenmis, kilit->val, new_jval_v((void *)kilit));
        }
    }
}

/* @name  : dosyanin_sifresini_coz
 * @desc  : Giriş metnini kilit dosyasından okunarak doldurulan jrb ağacına göre şifreler ve hedef dosyaya yazar.
 * @params: IS is, JRB kilit_sifrelenmis, char *hedef_dosya_adi
 * @return: void
 */
void dosyayi_sifrele(IS my_is, JRB kilit_sifrelenmis, char *hedef_dosya_adi)
{
    JRB jrb_gecici;
    Kilit *kilit_sifrelendi;

    FILE *fptr;
    fptr = fopen(hedef_dosya_adi, "w");
    if (fptr == NULL)
    {
        printf("Dosya oluşturulamadı!");
        exit(1);
    }

    /* Read each line with get_line().  Print out each word. */
    while (get_line(my_is) >= 0)
    {
        for (int i = 0; i < my_is->NF; i++)
        {
            if (my_is->fields[i] != NULL)
            {
                jrb_gecici = jrb_find_str(kilit_sifrelenmis, my_is->fields[i]);
                //printf("%d: %s\n", my_is->line, my_is->fields[i]);
                if (jrb_gecici != NULL)
                {
                    kilit_sifrelendi = (Kilit *)jrb_gecici->val.v;
                    fprintf(fptr, "%s ", kilit_sifrelendi->val);
                    //printf("%s için bir şifre %s \n", my_is->fields[i], kilit_sifrelendi->val);
                }
                else
                {
                    fprintf(fptr, "%s ", my_is->fields[i]);
                }
            }
        }
    }

    fclose(fptr);
}

/* @name  : dosyanin_sifresini_coz
 * @desc  : Şifreli giriş metnini kilit dosyasından okunarak doldurulan jrb ağacına göre çözümler ve hedef dosyaya yazar.
 * @params: IS is, JRB kilit_cozumlenmis, char *hedef_dosya_adi
 * @return: void
 */
void dosyanin_sifresini_coz(IS my_is, JRB kilit_cozumlenmis, char *hedef_dosya_adi)
{
    JRB jrb_cozumlendi;
    Kilit *kilit_cozumlendi;

    FILE *fptr;
    fptr = fopen(hedef_dosya_adi, "w");
    if (fptr == NULL)
    {
        printf("Dosya oluşturulamadı!");
        exit(1);
    }

    // hedef_dosya_adi parametresi ile gelen dosyanın her satırı get_line () ile okunuyor.
    // Her kelime çözümleniyor
    while (get_line(my_is) >= 0)
    {
        for (int i = 0; i < my_is->NF; i++)
        {
            if (my_is->fields[i] != NULL) // okunan null değilse
            {
                jrb_cozumlendi = jrb_find_str(kilit_cozumlenmis, my_is->fields[i]);

                if (jrb_cozumlendi != NULL)
                {
                    kilit_cozumlendi = (Kilit *)jrb_cozumlendi->val.v;
                    fprintf(fptr, "%s ", kilit_cozumlendi->key);
                    // printf("%s şifresi için bulunan kelime %s \n", is->fields[i], k1->key);
                }
                else
                {
                    fprintf(fptr, "%s ", my_is->fields[i]);
                }
            }
        }
    }

    fclose(fptr);
}
