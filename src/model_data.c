
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model_data.c
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

/* Constant parameters (default storage) */
const ConstP_model_T model_ConstP = {
    /* Expression: tBw
     * Referenced by: '<Root>/Gain2'
     */
    {0.33299667313036063, 0.37393307874758769, 0.37411010805618666,
     0.33317370243895972, 0.036960629992566246, 0.03719100454601746,
     -0.037106306603676947, -0.037045327934906641, 1.0950664274301052,
     -1.0886807026437848, -0.38795964624355667, 0.38157392145723612,
     0.061208141578512218, -0.061346831213904988, 0.061105829455647465,
     -0.060967139820254646, -5.7367847451639253E-17, -2.6224140046993138E-17,
     1.1064283170214573E-16, 1.1785277614917433E-16, 0.2623166854207124,
     0.23936151405332984, 0.26059528123896658, 0.23772651928699146,
     -2.4633073358870661E-16, -1.43982048506075E-16, 1.8735013540549517E-16,
     2.0990154059319366E-16, 1.8570431304160009, -1.8612509470238192,
     1.8539390004747502, -1.8497311838669304, 5.7782554782614959E-16,
     -9.893344823930228E-17, -5.3697823097775821E-16, 4.809791887688819E-17,
     -1.1213783371531021, -1.1283678563718882, 1.1257981372474815,
     1.1239480562775086, 3.2157555671353864, -3.1880622846013362,
     -3.2157555671353832, 3.1880622846013331, 1.3392065234540951E-15,
     1.97758476261356E-16, -6.6266436782314031E-16, 1.1796119636642288E-16},

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
    {1100.0, 1104.0, 1108.0, 1112.0, 1116.0, 1120.0, 1124.0, 1128.0, 1132.0,
     1136.0, 1140.0, 1144.0, 1148.0, 1152.0, 1156.0, 1160.0, 1164.0, 1168.0,
     1172.0, 1176.0, 1180.0, 1184.0, 1188.0, 1192.0, 1196.0, 1200.0, 1204.0,
     1208.0, 1212.0, 1216.0, 1220.0, 1224.0, 1228.0, 1232.0, 1236.0, 1240.0,
     1244.0, 1248.0, 1252.0, 1256.0, 1260.0, 1264.0, 1268.0, 1272.0, 1276.0,
     1280.0, 1284.0, 1288.0, 1292.0, 1296.0, 1300.0, 1304.0, 1308.0, 1312.0,
     1316.0, 1320.0, 1324.0, 1328.0, 1332.0, 1336.0, 1340.0, 1344.0, 1348.0,
     1352.0, 1356.0, 1360.0, 1364.0, 1368.0, 1372.0, 1376.0, 1380.0, 1384.0,
     1388.0, 1392.0, 1396.0, 1400.0, 1404.0, 1408.0, 1412.0, 1416.0, 1420.0,
     1424.0, 1428.0, 1432.0, 1436.0, 1440.0, 1444.0, 1448.0, 1452.0, 1456.0,
     1460.0, 1464.0, 1468.0, 1472.0, 1476.0, 1480.0, 1484.0, 1488.0, 1492.0,
     1496.0, 1500.0, 1504.0, 1508.0, 1512.0, 1516.0, 1520.0, 1524.0, 1528.0,
     1532.0, 1536.0, 1540.0, 1544.0, 1548.0, 1552.0, 1556.0, 1560.0, 1564.0,
     1568.0, 1572.0, 1576.0, 1580.0, 1584.0, 1588.0, 1592.0, 1596.0, 1600.0,
     1604.0, 1608.0, 1612.0, 1616.0, 1620.0, 1624.0, 1628.0, 1632.0, 1636.0,
     1640.0, 1644.0, 1648.0, 1652.0, 1656.0, 1660.0, 1664.0, 1668.0, 1672.0,
     1676.0, 1680.0, 1684.0, 1688.0, 1692.0, 1696.0, 1700.0, 1704.0, 1708.0,
     1712.0, 1716.0, 1720.0, 1724.0, 1728.0, 1732.0, 1736.0, 1740.0, 1744.0,
     1748.0, 1752.0, 1756.0, 1760.0, 1764.0, 1768.0, 1772.0, 1776.0, 1780.0,
     1784.0, 1788.0, 1792.0, 1796.0, 1800.0, 1804.0, 1808.0, 1812.0, 1816.0,
     1820.0, 1824.0, 1828.0, 1832.0, 1836.0, 1840.0, 1844.0, 1848.0, 1852.0,
     1856.0, 1860.0, 1864.0, 1868.0, 1872.0, 1876.0, 1880.0, 1884.0, 1888.0,
     1892.0, 1896.0, 1900.0},

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
    {-2.3095392666666661, -2.30424736, -2.29517552, -2.28156776, -2.2226008,
     -2.18177752, -2.1636338399999997, -2.1318824, -2.1092028000000003,
     -2.05477176, -2.041164, -1.9867329599999999, -1.9549815199999998, -1.927766,
     -1.8914786399999999, -1.8370476, -1.80983208, -1.7916884, -1.75540104,
     -1.7145777599999998, -1.68282632, -1.6510748800000001, -1.6193234399999998,
     -1.59210792, -1.5558205600000001, -1.53767688, -1.50138952,
     -1.4696380800000002, -1.44242256, -1.41067112, -1.360776,
     -1.3290245600000001, -1.31995272, -1.28820128, -1.25644984, -1.22016248,
     -1.18841104, -1.1657314399999998, -1.13851592, -1.09769264, -1.07501304,
     -1.05686936, -1.0160460800000002, -0.98883056, -0.97068688,
     -0.9298635999999999, -0.907184, -0.87996847999999994, -0.85275295999999989,
     -0.82553744000000007, -0.79832192, -0.78017824, -0.75296272, -0.72121128,
     -0.69853168, -0.67131615999999994, -0.65317247999999994,
     -0.63049287999999992, -0.6123492, -0.58059776, -0.55338224, -0.53070264,
     -0.5125589599999999, -0.48534344, -0.46719976, -0.44452016,
     -0.42184056000000003, -0.39916096, -0.38101727999999996, -0.35380176,
     -0.33565807999999997, -0.31297847999999995, -0.2948348, -0.27669112,
     -0.24947560000000002, -0.23586784, -0.21318823999999997, -0.19958048,
     -0.1814368, -0.16329311999999999, -0.15422128000000002, -0.1360776,
     -0.11793392, -0.09979024, -0.08618248, -0.07257472, -0.063502880000000012,
     -0.05443104, -0.0453592, -0.031751440000000006, -0.009, -0.008, -0.007,
     -0.006, -0.005, -0.004, -0.003, -0.002, -0.001, -0.0, 0.001, 0.002, 0.003,
     0.004, 0.005, 0.006, 0.007, 0.008, 0.009, 0.0091, 0.0092,
     0.040823279999999997, 0.054431040000000007, 0.06803880000000001,
     0.077110640000000008, 0.0907184, 0.10886208000000001, 0.12700576, 0.14514944,
     0.16329311999999999, 0.18143679999999998, 0.20411639999999998, 0.22226008,
     0.24493968000000002, 0.26308336, 0.29029888, 0.31297847999999995,
     0.33565807999999997, 0.36287359999999996, 0.3855532, 0.41276872000000003,
     0.44452016, 0.46719976, 0.49441528, 0.5216308, 0.54884632, 0.58059776,
     0.60781328, 0.63956472, 0.68492392, 0.7030676, 0.7257472,
     0.76203455999999992, 0.79832192, 0.82553744000000007, 0.85275295999999989,
     0.88904032, 0.92079175999999985, 0.9480072799999999, 0.9707, 0.9752,
     1.04779752, 1.07501304, 1.1113004, 1.1657314399999998, 1.18387512,
     1.20655472, 1.23830616, 1.27459352, 1.31088088, 1.3562400799999998,
     1.41067112, 1.4288148, 1.4787099199999998, 1.5240691199999998, 1.54674872,
     1.57850016, 1.62385936, 1.6556108, 1.69189816, 1.72818552, 1.77354472,
     1.80076024, 1.84611944, 1.8778708800000001, 1.9141582400000003,
     1.9912688800000002, 1.9958048000000002, 2.05930768, 2.09105912,
     2.1228105600000005, 2.16816976, 2.2135289600000005, 2.2724959200000003,
     2.30424736, 2.3632143200000004, 2.40857352, 2.45393272, 2.4811482400000004,
     2.5537229600000004, 2.5809384800000004, 2.61722584, 2.6489772800000004,
     2.68526464, 2.73515976, 2.77144712, 2.8213422400000003, 2.87577328,
     2.8939169600000003, 2.9165965600000003, 2.9256684}};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
