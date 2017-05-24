#include <stdio.h>

typedef struct rational {
  int bottom;
    int top;
} rational;

  rational reduce(rational tmp) {
    int t;
    int a = tmp.top;
    int b = tmp.bottom;
    while(b!=0) {
      t=b;
      b=a%b;
	a=t;
    }
    tmp.top = tmp.top/t;
    tmp.bottom = tmp.bottom/t;
    return tmp;
  }

rational addq(rational a, rational b) {
  rational tmp1;
  rational tmp2;
  
  tmp1.top = a.top*b.bottom;
  tmp1.bottom = a.bottom*b.bottom;
  tmp2.top = b.top*a.bottom;
  tmp1.top = tmp1.top + tmp2.top;
  
  return tmp1;
}
rational subq(rational a, rational b) {
  rational tmp1;
  rational tmp2;
  
  tmp1.top = a.top*b.bottom;
  tmp1.bottom = a.bottom*b.bottom;
  tmp2.top = b.top*a.bottom;
  tmp1.top = tmp1.top - tmp2.top;
  return tmp1;
}
rational mulq(rational a, rational b) {
  rational tmp;
  tmp.top = a.top*b.top;
  tmp.bottom = a.bottom*b.bottom;
  return tmp;
}
rational divq(rational a, rational b) {
  rational tmp;
  tmp.top = a.top*b.bottom;
  tmp.bottom = a.bottom*b.top;
  return tmp;
}
  
  int main() {
    rational rata;
    rational ratb;
    rational ratc;
    
    // rata.top = 25;
    //rata.bottom = 100;
    //ratb.top = 9;
    //ratb.bottom = 63;

    printf("enter numerator for rational number 1:");
    scanf("%d", &rata.top);
    printf("enter denominator for rational number 1:");
    scanf("%d", &rata.bottom);
    printf("enter numerator for rational number 2:");
    scanf("%d", &ratb.top);
    printf("enter denominator for rational number 2:");
    scanf("%d", &ratb.bottom);
    

    rata = reduce(rata);
    ratb = reduce(ratb);
    ratc = reduce(addq(rata,ratb));
    
    printf("Rational number 1:%d/%d\n",rata.top, rata.bottom);
    printf("Rational number 2:%d/%d\n",ratb.top, ratb.bottom);
    printf("addq:%d/%d\n",ratc.top, ratc.bottom);
    ratc = reduce(subq(rata,ratb));
    printf("subq:%d/%d\n",ratc.top, ratc.bottom);
    ratc = reduce(mulq(rata,ratb));
    printf("mulq:%d/%d\n",ratc.top, ratc.bottom);
    ratc = reduce(divq(rata,ratb));
    printf("divq:%d/%d\n",ratc.top, ratc.bottom);
    

    
  }
