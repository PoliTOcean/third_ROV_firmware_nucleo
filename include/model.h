
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model.h
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

#ifndef MODEL_H
#define MODEL_H

#include "rtwtypes.h"

/* Constant parameters (default storage) */
typedef struct
{
    /* Expression: tBw
     * Referenced by: '<Root>/Gain2'
     */
    real_T Gain[48];

    /* Pooled Parameter (Expression: PWMs)
     * Referenced by:
     *   '<Root>/1-D Lookup Table'
     *   '<Root>/1-D Lookup Table1'
     *   '<Root>/1-D Lookup Table2'
     *   '<Root>/1-D Lookup Table3'
     *   '<Root>/1-D Lookup Table4'
     *   '<Root>/1-D Lookup Table5'
     *   '<Root>/1-D Lookup Table6'
     *   '<Root>/1-D Lookup Table7'
     */
    real_T pooled1[201];

    /* Pooled Parameter (Expression: ForceKgF)
     * Referenced by:
     *   '<Root>/1-D Lookup Table'
     *   '<Root>/1-D Lookup Table1'
     *   '<Root>/1-D Lookup Table2'
     *   '<Root>/1-D Lookup Table3'
     *   '<Root>/1-D Lookup Table4'
     *   '<Root>/1-D Lookup Table5'
     *   '<Root>/1-D Lookup Table6'
     *   '<Root>/1-D Lookup Table7'
     */
    real_T pooled2[201];
} ConstP_model_T;

/* External inputs (root inport signals with default storage) */
typedef struct
{
    real_T Input[6]; /* '<Root>/Input' */
} ExtU_model_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct
{
    real_T Output[8]; /* '<Root>/Output' */
} ExtY_model_T;

/* External inputs (root inport signals with default storage) */
extern ExtU_model_T model_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_model_T model_Y;

/* Constant parameters (default storage) */
extern const ConstP_model_T model_ConstP;

/* Model entry point functions */
extern void model_initialize(void);
extern void model_step(void);
extern void model_terminate(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'model'
 */
#endif /* RTW_HEADER_model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
