//
// Created by Nathan on 14/05/2021.
//

#include "random.h"
#include "math_functions.h"
//#include <math.h>

float fn[128], wn[128];
long kn[128];
long jsr = 42;


/******************************************************************************/

long shr3_seeded (){

    long value;
    value = &jsr;

    jsr = ( jsr ^ ( jsr <<   13 ) );
    jsr = ( jsr ^ ( jsr >>   17 ) );
    jsr = ( jsr ^ ( jsr <<    5 ) );

    value = value + jsr;

    return value;
}

/******************************************************************************/

void r4_nor_setup (){

    double dn = 3.442619855899;
    int i;
    const double m1 = 2147483648.0;
    double q;
    double tn = 3.442619855899;
    const double vn = 9.91256303526217E-03;

    q = vn / exp ( - 0.5 * dn * dn );

    kn[0] = ( long ) ( ( dn / q ) * m1 );
    kn[1] = 0;

    wn[0] = ( float ) ( q / m1 );
    wn[127] = ( float ) ( dn / m1 );

    fn[0] = 1.0;
    fn[127] = ( float ) ( exp ( - 0.5 * dn * dn ) );

    for ( i = 126; 1 <= i; i-- )
    {
        dn = sqrt ( - 2.0 * log ( vn / dn + exp ( - 0.5 * dn * dn ) ) );
        kn[i+1] = ( long ) ( ( dn / tn ) * m1 );
        tn = dn;
        fn[i] = ( float ) ( exp ( - 0.5 * dn * dn ) );
        wn[i] = ( float ) ( dn / m1 );
    }


    return;
}

/******************************************************************************/

float r4_uni (){
    long jsr_input;
    float value;

    jsr_input = jsr;

    jsr = ( jsr ^ ( jsr <<   13 ) );
    jsr = ( jsr ^ ( jsr >>   17 ) );
    jsr = ( jsr ^ ( jsr <<    5 ) );

    value = fmod ( 0.5 + ( float ) ( jsr_input + jsr ) / 65536.0 / 65536.0, 1.0 );

    return value;
}

/******************************************************************************/

float r4_nor (){

    int hz;
    long iz;
    const float r = 3.442620;
    float value;
    float x;
    float y;

    hz = ( int ) shr3_seeded ( jsr );
    iz = ( hz & 127 );

    if ( fabs ( hz ) < kn[iz] )
    {
        value = ( float ) ( hz ) * wn[iz];
    } else {
        for ( ; ; )
        {
            if ( iz == 0 )
            {
                for ( ; ; )
                {
                    x = - 0.2904764 * log ( r4_uni ( jsr ) );
                    y = - log ( r4_uni ( jsr ) );
                    if ( x * x <= y + y )
                    {
                        break;
                    }
                }

                if ( hz <= 0 )
                {
                    value = - r - x;
                }
                else
                {
                    value = + r + x;
                }
                break;
            }

            x = ( float ) ( hz ) * wn[iz];

            if ( fn[iz] + r4_uni ( jsr ) * ( fn[iz-1] - fn[iz] ) < exp ( - 0.5 * x * x )){
                value = x;
                break;
            }

            hz = ( int ) shr3_seeded ( jsr );
            iz = ( hz & 127 );

            if ( fabs ( hz ) < kn[iz] )
            {
                value = ( float ) ( hz ) * wn[iz];
                break;
            }
        }
    }

    return value;
}

/**************************/

double random_double(int maximum){
    float output = r4_nor();
    return modd(maximum*output,maximum);
}

double prepare_random(){
    r4_nor_setup();
    shr3_seeded();
}
