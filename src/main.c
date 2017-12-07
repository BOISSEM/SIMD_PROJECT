#include <stdlib.h>
#include <stdint.h>

#include "test_mouvement.h"
#include "test_mouvement_SSE2.h"
#include "test_morpho.h"
#include "test_morpho_SSE2.h"
#include "bench_morpho.h"
#include "bench_morpho_SSE2.h"

#include "test_car3.h"
#include "test_car3_SSE2.h"

#include "test_ROC.h"
#include "bench_mouvement.h"
#include "bench_mouvement_SSE2.h"

int main()
{
    // f_test_mouvement();
    // f_test_mouvement_SSE2();

    // f_test_morpho();
    // f_test_morpho_SSE2();

    f_test_mouvement_car3(198);
    f_test_mouvement_car3_SSE2();

    // f_bench_morpho(1);
    // f_bench_morpho_SSE2(1);

    // f_test_roc_car3();

    //f_bench_mouvement();
    //f_bench_mouvement_SSE2();

    return 0;
}
