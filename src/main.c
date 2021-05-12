#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "kilit.h"
#include "jrb.h"


// ./kripto -e istiklal_marsi_2.txt sifrelenmis şeklinde yapının ayarlanması Sadık, Hüseyin
// ./kripto -d sifrelenmis cozumlenmis şeklinde yapının ayarlanması Ayşe Merve, Emre
// test işlemlerinin yapılması ve hataların tespiti Sadık, Hüseyin, Emre, Ayşe Merve
// test işlemleri sonucunda 

int main(int argc, char **argv)
{
  JRB kilit_encrypt, kilit_decrypt;
  
  // Kilit yapısı eklendi.
  Kilit *k;
  
  // field ile giriş metin dosyasına erişiliyor
  IS is2;
  is2 = new_inputstruct(argv[2]);
  if (is2 == NULL)
  {
    perror(argv[1]);
    exit(1);
  }

  if (!strcmp(argv[1], "-e"))
  {
    printf("%s =  encripted işlemi yapılıyor.\n", argv[1]);
    // burada dosya şifrelenecek
  }

  if (!strcmp(argv[1], "-d"))
  {
    printf("%s = decripted işlemi yapılıyor.\n", argv[1]);
    // burada giriş dosyasından şifre çözülecek
  }
  
  return 0;
}
