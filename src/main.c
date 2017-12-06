#include <stdlib.h>
#include <stdint.h>

#include "test_mouvement.h"
#include "test_mouvement_SSE2.h"
#include "test_morpho.h"
#include "test_car3.h"
#include "test_car3_SSE2.h"
#include "test_ROC.h"

int main()
{
    // f_test_mouvement();

    //f_test_mouvement_SSE2();

    // f_test_morpho();

    //f_test_mouvement_car3();

    f_test_mouvement_car3_SSE2();

    f_test_roc_car3();

    return 0;
}
