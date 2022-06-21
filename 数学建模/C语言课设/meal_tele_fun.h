//meal_tele_func.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_info.h"
 
void admin(Info guest[]);
int read(Info guest[]);
void interface();
void meal_regi(Info guest[],int guest_number);
void meal_canc(Info guest[]);
void meal_inqu(Info guest[]);
void meal_chan(Info guest[]);
int exp();
