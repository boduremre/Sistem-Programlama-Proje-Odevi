// Fields ile ilgili örnek

#include "fields.h"

int main()
{
  IS is;

  // Yeni bir dosya okuyucusu tanımla
  is = new_inputstruct(NULL);  // NULL --> stdin

  get_line(is);

  printf("Kelime sayısı: %d\n", is->NF);

  if(is->NF > 2)
    printf("İkinci kelime: %s\n", is->fields[1]);
  else
    printf("İkinci kelime yok\n");
  
  // Çıkmadan önce bellekte kullanılan yerlerin geri bırakılması
  jettison_inputstruct(is);
}
