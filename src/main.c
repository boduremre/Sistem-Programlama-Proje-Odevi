#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"

// Kilit Struct Tanımlanmalı Hüseyin
struct Kilit{};

// JRB Eklenmeli Sadık
// json okuma ve parse etme işlemleri yapılmalı - Ayşe Merve ve Emre
// ./kripto -e istiklal_marsi_2.txt sifrelenmis şeklinde yapının ayarlanması Sadık, Hüseyin
// ./kripto -d sifrelenmis cozumlenmis şeklinde yapının ayarlanması Ayşe Merve, Emre
// test işlemlerinin yapılması ve hataların tespiti Sadık, Hüseyin, Emre, Ayşe Merve
// test işlemleri sonucunda 

// okunan metni kilit vasıtasıyla şifreleyen bir fonksiyon yazılmalı Sadık, Hüseyin, Emre, Ayşe Merve
void encrypt_file(IS is2, JRB kilitler, char *hedef_dosya_adi);

// şifreli metni kilit vasıtasıyla çözen bir fonksiyon yazılmalı Sadık, Hüseyin, Emre, Ayşe Merve
void decrypt_file(IS is, JRB kilitlerDec, char *hedef_dosya_adi);

int main(int argc, char **argv)
{
  IS is;
  int i;

  /* Open the file as an inputstruct.  Error check. */
  is = new_inputstruct(NULL);
  if (is == NULL)
  {
    perror(argv[1]);
    exit(1);
  }

  /* Read each line with get_line().  Print out each word. */
  while (get_line(is) >= 0)
  {
    for (i = 0; i < is->NF; i++)
    {
      printf("%d: %s\n", is->line, is->fields[i]);
    }
  }

  jettison_inputstruct(is);
  return 0;
}
