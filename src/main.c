#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "kilit.h"
#include "jrb.h"

// test işlemlerinin yapılması ve hataların tespiti Sadık, Hüseyin, Emre, Ayşe Merve
// test işlemleri sonucunda

int main(int argc, char **argv)
{
  JRB kilit_encrypt, kilit_decrypt;

  // Kilit yapısı eklendi.
  Kilit *k;
  // field
  IS is;

  // giriş ve çıkış metinleri kontrol ediliyor.
  if (argv[2] == NULL)
  {
    printf("Giriş metni adı belirtilmedi!\n");
  }
  else if (argv[3] == NULL)
  {
    printf("Çıkış metni adı belirtilmedi!\n");
  }
  else
  {
    //jrb oluşturuluyor.
    kilit_encrypt = make_jrb();
    kilit_decrypt = make_jrb();

    // bu fonksiyon ile kilit dosyası okunarak jrb ağaçları dolduruluyor.
    // kilit.c içerisinde gövde tanımlanmalı
    fill_jrb_from_kilit_file(kilit_encrypt, kilit_decrypt);

    // giriş metni için fields ayarlanıyor.
    is = new_inputstruct(argv[2]);
    if (is == NULL)
    {
      perror(argv[2]);
      exit(1);
    }

    // girilen parametrenin ne olduğuna göre şifreleme mi çözmemi işlemi yapılacağına karar veriliyor.
    if (!strcmp(argv[1], "-e"))
    {
      printf("%s =  encripted işlemi yapıldı.\n", argv[1]);
      encrypt_file(is, kilit_encrypt, argv[3]);
    }
    else if (!strcmp(argv[1], "-d")) // -d işlemi çözme işlemi yapar
    {
      printf("%s = decripted işlemi yapıldı.\n", argv[1]);
      decrypt_file(is, kilit_decrypt, argv[3]);
    }
    else // eğer -e ve -d dışında bir parametre girildi ise uyarı veriliyor.
    {
      printf("Geçersiz parametre girildi. Şifrelemek için -e, Şifreyi Çözmek icin -d giriniz.\n");
    }
  }

  /* işi biten değişkenler bellekten siliniyor */
  jettison_inputstruct(is);

  return 0;
}
