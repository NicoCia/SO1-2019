#include "stepA.h"
#include "stepB.h"
#include "stepC.h"
#include "stepD.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    stepA();
    stepB();
    stepD(argv[1],atoi(argv[2]));
    return 0;

}
    //StepA();
    /*printf("\n");
    StepB();
    printf("\n");
    StepC(2,6);
    return 0;
}


