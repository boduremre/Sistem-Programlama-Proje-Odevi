/* Copyright (C) 2021 Emre Bodur */

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

void kilit_dosyasindan_jrb_doldur(JRB kilit_sifrelenmis, JRB kilit_cozumlenmis);
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

            if (strchr(my_is->text1, '\"') == NULL || getNumPipe(my_is->text1, '\"') < 4)
            {
                printf("KILIT DOSYASI HATALI!\n");
                printf("Hatalı Satır Numarası: %d, \nHatalı Satır: %sHata: '\"' karakteri yok!\n", my_is->line, my_is->text1);
                exit(1);
            }

            parcalanmis_text = strtok(my_is->text1, ":");
            while (parcalanmis_text != NULL)
            {
                remove_str_character(parcalanmis_text, ' ');  // boşluk karakteri siliniyor
                remove_str_character(parcalanmis_text, '\n'); // satır karakteri siliniyor
                remove_str_character(parcalanmis_text, '"');  // çift tırnak karakteri siliniyor

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
                        remove_str_character(parcalanmis_text, ','); // val sonundaki virgüller siliniyor.
                        kilit->val = (char *)malloc(sizeof(char) * (strlen(parcalanmis_text) + 1));
                        strcpy(kilit->val, parcalanmis_text);
                        //printf("%d. k->key=%s, k->val=%s\n", i, k->key, k->val);
                    }

                    a++;
                }

                parcalanmis_text = strtok(NULL, ":");
            }

            //printf("%d. k->key=%s, k->val=%s\n", i, k->key, k->val);
            (void)jrb_insert_str(kilit_encrypt, kilit->key, new_jval_v((void *)kilit));
            (void)jrb_insert_str(kilit_decrypt, kilit->val, new_jval_v((void *)kilit));
        }
    }
}

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
