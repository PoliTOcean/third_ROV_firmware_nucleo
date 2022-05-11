
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model.c
 *
 * Code generated for Simulink model 'model'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon May  9 01:14:03 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->ST10/Super10
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "model.h"
#include "model_private.h"

/* External inputs (root inport signals with default storage) */
ExtU_model_T model_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_model_T model_Y;

/* Real-time model */
real_T lookup(real_T u0, const real_T bp0[], const real_T table[],
              uint32_T maxIndex)
{
    real_T frac;
    real_T yL_0d0;
    uint32_T iLeft;

    /* Column-major Lookup 1-D
       Search method: 'binary'
       Use previous index: 'off'
       Interpolation method: 'Linear point-slope'
       Extrapolation method: 'Linear'
       Use last breakpoint for index at or above upper limit: 'off'
       Remove protection against out-of-range input in generated code: 'off'
     */
    /* Prelookup - Index and Fraction
       Index Search method: 'binary'
       Extrapolation method: 'Linear'
       Use previous index: 'off'
       Use last breakpoint for index at or above upper limit: 'off'
       Remove protection against out-of-range input in generated code: 'off'
     */
    if (u0 <= bp0[0UL])
    {
        iLeft = 0UL;
        frac = (u0 - bp0[0UL]) / (bp0[1UL] - bp0[0UL]);
    }
    else if (u0 < bp0[maxIndex])
    {
        uint32_T bpIdx;
        uint32_T iRght;

        /* Binary Search */
        bpIdx = maxIndex >> 1UL;
        iLeft = 0UL;
        iRght = maxIndex;
        while (iRght - iLeft > 1UL)
        {
            if (u0 < bp0[bpIdx])
                iRght = bpIdx;
            else
                iLeft = bpIdx;

            bpIdx = (iRght + iLeft) >> 1UL;
        }

        frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1UL] - bp0[iLeft]);
    }
    else
    {
        iLeft = maxIndex - 1UL;
        frac = (u0 - bp0[maxIndex - 1UL]) / (bp0[maxIndex] - bp0[maxIndex - 1UL]);
    }

    /* Column-major Interpolation 1-D
       Interpolation method: 'Linear point-slope'
       Use last breakpoint for index at or above upper limit: 'off'
       Overflow mode: 'portable wrapping'
     */
    yL_0d0 = table[iLeft];
    return (table[iLeft + 1UL] - yL_0d0) * frac + yL_0d0;
}

void model_step(void)
{
    real_T saturation[8];
    real_T tmp[8];
    int16_T i;
    int16_T i_0;
    for (i = 0; i < 8; i++)
    {
        real_T u0;

        /* Gain: '<Root>/Gain2' incorporates:
         *  Inport: '<Root>/Input'
         */
        tmp[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++)
            tmp[i] += model_ConstP.Gain[(i_0 << 3) + i] * model_U.Input[i_0];

        /* End of Gain: '<Root>/Gain2' */

        /* Saturate: '<Root>/Saturation' */
        u0 = tmp[i];
        if (u0 > 28.69100601486)
            saturation[i] = 28.69100601486;
        else if (u0 < -22.648843249456661)
            saturation[i] = -22.648843249456661;
        else
            saturation[i] = u0;

        /* End of Saturate: '<Root>/Saturation' */

        /* Outport: '<Root>/Output' incorporates:
         *  Lookup_n-D: '<Root>/1-D Lookup Table'
         */
        model_Y.Output[i] = lookup(saturation[i], model_ConstP.pooled2,
                                   model_ConstP.pooled1, 200UL);
    }
}

/* Model initialize function */
void model_initialize(void)
{
    /* (no initialization code required) */
    for (int i = 0; i < 8; i++)
        model_Y.Output[i++] = 1500;
}

/* Model terminate function */
void model_terminate(void)
{
    /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
