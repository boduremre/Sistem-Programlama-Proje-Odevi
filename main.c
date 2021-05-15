/* main.c
   Emre Bodur
   BSM308 Proje / Tasarım Ödevi
   Mayıs, 2021
*/
#include <stdio.h>
#include "kilit.h"
#include "mrbdr.h"

int main(int argc, char **argv)
{
  JRB kilit_encrypt, kilit_decrypt;
  IS is;
  int i, nsize;
  char *lines;

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
    //jrb'ye ekleme
    kilit_encrypt = make_jrb();
    kilit_decrypt = make_jrb();

    fill_jrb_from_kilit_file(kilit_encrypt, kilit_decrypt);

    is = new_inputstruct(argv[2]);
    if (is == NULL)
    {
      perror(argv[2]);
      exit(1);
    }

    if (!strcmp(argv[1], "-e"))
    {
      printf("%s =  Kripto kilidine göre kriptonlandi ve okunabilir kripto metni üretildi!\n\n", argv[1]);
      encrypt_file(is, kilit_encrypt, argv[3]);
    }
    else if (!strcmp(argv[1], "-d"))
    {
      printf("%s = Kripto kilidine göre çözümlendi ve okunabilir çıkış metni üretildi!\n\n", argv[1]);
      decrypt_file(is, kilit_decrypt, argv[3]);
    }
    else
    {
      printf("Geçersiz parametre girildi! Metni/Dosyayı kriptolamak için -e, çözümlemek icin -d giriniz.\n");
    }
  }

  /* Free up the memory allocated with new_inputstruct, and close the open file.  */
  jettison_inputstruct(is);
  return 0;
}
