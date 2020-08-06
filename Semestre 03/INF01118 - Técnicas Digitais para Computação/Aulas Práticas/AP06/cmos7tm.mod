.MODEL MODN NMOS LEVEL=7 
* ----------------------------------------------------------------------
************************* SIMULATION PARAMETERS ************************
* ----------------------------------------------------------------------
* format    : PSPICE
* model     : MOS BSIM3v3
* process   : CU[BEQWAVP]
* revision  : B; 
* extracted : CUE 41667; 1998-08; ese(487)
* doc#      : 9933011 REV_B
* ----------------------------------------------------------------------
*                        TYPICAL MEAN CONDITION
* ----------------------------------------------------------------------
*
*        *** Flags ***
+MOBMOD =1.000e+00 CAPMOD =2.000e+00 
+NOIMOD =1.000e+00 

*        *** Threshold voltage related model parameters ***
+K1     =1.057e+00 
+K2     =-1.23e-01 K3     =6.535e+00 K3B    =-2.02e+00 
+NCH    =9.114e+16 VTH0   =8.481e-01 
+VOFF   =-1.16e-01 DVT0   =3.561e+00 DVT1   =8.652e-01 
+DVT2   =-2.50e-01 KETA   =-4.48e-02 
+PSCBE1 =3.616e+08 PSCBE2 =1.020e-05 
+DVT0W  =-2.98e+00 DVT1W  =1.306e+06 DVT2W  =-9.24e-03 
*        *** Mobility related model parameters ***
+UA     =1.000e-12 UB     =1.709e-18 UC     =-3.60e-11 
+U0     =4.269e+02 
*        *** Subthreshold related parameters ***
+DSUB   =5.000e-01 ETA0   =1.008e-02 ETAB   =-1.72e-02 
+NFACTOR=6.529e-01 
*        *** Saturation related parameters ***
+EM     =4.100e+07 PCLM   =9.549e-01 
+PDIBLC1=2.750e-02 PDIBLC2=1.069e-03 DROUT  =3.510e-01 
+A0     =9.550e-01 A1     =0.000e+00 A2     =1.000e+00 
+PVAG   =0.000e+00 VSAT   =8.665e+04 AGS    =1.785e-01 
+B0     =2.652e-07 B1     =0.000e+00 DELTA  =1.000e-02 
+PDIBLCB=2.306e-01 
*        *** Geometry modulation related parameters ***
+W0     =3.151e-08 DLC    =1.449e-07 
+DWC    =-8.94e-09 DWB    =0.000e+00 DWG    =0.000e+00 
+LL     =0.000e+00 LW     =0.000e+00 LWL    =0.000e+00 
+LLN    =1.000e+00 LWN    =1.000e+00 WL     =0.000e+00 
+WW     =0.000e+00 WWL    =0.000e+00 WLN    =1.000e+00 
+WWN    =1.000e+00 
*        *** Temperature effect parameters ***
+AT     =3.300e+04 UTE    =-1.90e+00 
+KT1    =-4.20e-01 KT2    =2.200e-02 KT1L   =0.000e+00 
+UA1    =0.000e+00 UB1    =0.000e+00 UC1    =0.000e+00 
+PRT    =0.000e+00 
*        *** Overlap capacitance related and dynamic model parameters   ***
+CGDO   =3.400e-10 CGSO   =3.400e-10 CGBO   =1.300e-10 
+CGDL   =0.000e+00 CGSL   =0.000e+00 CKAPPA =6.000e-01 
+CF     =0.000e+00 ELM    =5.000e+00 
+XPART  =1.000e+00 CLC    =1.000e-15 CLE    =6.000e-01 
*        *** Parasitic resistance and capacitance related model parameters ***
+RDSW   =1.687e+03 
+CDSC   =0.000e+00 CDSCB  =0.000e+00 CDSCD  =0.000e+00 
+PRWB   =0.000e+00 PRWG   =0.000e+00 CIT    =2.234e-04 
*        *** Process and parameters extraction related model parameters ***
+TOX    =1.270e-08 NGATE  =0.000e+00 
+NLX    =1.000e-10 
*        *** Substrate current related model parameters ***
+ALPHA0 =0.000e+00 BETA0  =3.000e+01 
*        *** Noise effect related model parameters ***
+AF     =1.343e+00 KF     =6.896e-27 EF     =1.000e+00 
+NOIA   =1.000e+20 NOIB   =5.000e+04 NOIC   =-1.40e-12 
*        *** Common extrinsic model parameters ***
+LINT   =1.449e-07 WINT   =-8.94e-09 XJ     =3.000e-07 
+RSH    =3.000e+01 JS     =2.000e-05 
+CJ     =3.800e-04 CJSW   =4.300e-10 
+MJ     =4.400e-01 MJSW   =2.500e-01 
+PB     =8.400e-01 
+PBSW   =9.400e-01 
* ----------------------------------------------------------------------
.SUBCKT ND A C PARAMS: AREA=1e-12 PERI=4e-6
* ----------------------------------------------------------------------
************************* SIMULATION PARAMETERS ************************
* ----------------------------------------------------------------------
* format    : PSPICE
* model     : DIODE
* process   : CU[BEQWAVP]
* revision  : B; 
* extracted : CUE 41667; 1998-08; ese(487)
* doc#      : 9933011 REV_B
* ----------------------------------------------------------------------
*                        TYPICAL MEAN CONDITION
* ----------------------------------------------------------------------
* TERMINALS: A=anode=P-region C=cathode=N-region
* VARIABLES: M (mulitiplier), AREA [m^2], PERI [m].
* NOTE: The role of a protection DIODE is to conduct ESD current to VDD 
* (or from VSS). This forward bias is NOT modelled, only leakage current 
* and capacitance during normal operation. Any inductive load etc that 
* will give forward bias, must be limited by other components to within 
* Operating Conditions, otherwise parasitic bipolar action can occur.
*
D1 A C NDINSUBA {AREA}
D2 A C NDINSUBS {PERI}
.ENDS ND
*
.MODEL NDINSUBA D 
+IS     =2.000e-05 N      =1.000e+00 
+CJO    =3.800e-04 M      =4.400e-01 VJ     =8.400e-01 
+TT     =0.000e+00 FC     =0.500e+00 
+EG     =1.110e+00 XTI    =3.000e+00 
+AF     =1.000e+00 KF     =0.000e+00
.MODEL NDINSUBS D
+IS     =0.000e+00 N      =1.000e+00 
+CJO    =4.300e-10 M      =2.500e-01 VJ     =8.400e-01 
+TT     =0.000e+00 FC     =0.500e+00  
+EG     =1.110e+00 XTI    =3.000e+00 
+AF     =1.000e+00 KF     =0.000e+00
* ----------------------------------------------------------------------
.MODEL MODP PMOS LEVEL=7 
* ----------------------------------------------------------------------
************************* SIMULATION PARAMETERS ************************
* ----------------------------------------------------------------------
* format    : PSPICE
* model     : MOS BSIM3v3
* process   : CU[BEQWAVP]
* revision  : B; 
* extracted : CUE 41667; 1998-08; ese(487)
* doc#      : 9933011 REV_B
* ----------------------------------------------------------------------
*                        TYPICAL MEAN CONDITION
* ----------------------------------------------------------------------
*
*        *** Flags ***
+MOBMOD =1.000e+00 CAPMOD =2.000e+00 
+NOIMOD =1.000e+00 

*        *** Threshold voltage related model parameters ***
+K1     =5.626e-01 
+K2     =-1.66e-02 K3     =1.485e+01 K3B    =-1.40e+00 
+NCH    =5.948e+16 VTH0   =-7.85e-01 
+VOFF   =-1.12e-01 DVT0   =2.066e+00 DVT1   =5.015e-01 
+DVT2   =-3.99e-02 KETA   =-7.67e-03 
+PSCBE1 =5.000e+08 PSCBE2 =1.000e-10 
+DVT0W  =0.000e+00 DVT1W  =0.000e+00 DVT2W  =0.000e+00 
*        *** Mobility related model parameters ***
+UA     =6.770e-11 UB     =1.040e-18 UC     =-1.16e-10 
+U0     =1.115e+02 
*        *** Subthreshold related parameters ***
+DSUB   =4.379e-01 ETA0   =4.843e-02 ETAB   =-3.50e-05 
+NFACTOR=2.220e-01 
*        *** Saturation related parameters ***
+EM     =4.100e+07 PCLM   =1.459e+00 
+PDIBLC1=5.872e-03 PDIBLC2=3.394e-04 DROUT  =7.861e-02 
+A0     =7.522e-01 A1     =0.000e+00 A2     =1.000e+00 
+PVAG   =0.000e+00 VSAT   =9.496e+04 AGS    =1.746e-01 
+B0     =3.421e-07 B1     =0.000e+00 DELTA  =1.000e-02 
+PDIBLCB=-3.18e-01 
*        *** Geometry modulation related parameters ***
+W0     =7.289e-07 DLC    =9.927e-08 
+DWC    =3.878e-08 DWB    =0.000e+00 DWG    =0.000e+00 
+LL     =0.000e+00 LW     =0.000e+00 LWL    =0.000e+00 
+LLN    =1.000e+00 LWN    =1.000e+00 WL     =0.000e+00 
+WW     =0.000e+00 WWL    =0.000e+00 WLN    =1.000e+00 
+WWN    =1.000e+00 
*        *** Temperature effect parameters ***
+AT     =3.300e+04 UTE    =-1.40e+00 
+KT1    =-5.70e-01 KT2    =2.200e-02 KT1L   =0.000e+00 
+UA1    =0.000e+00 UB1    =0.000e+00 UC1    =0.000e+00 
+PRT    =0.000e+00 
*        *** Overlap capacitance related and dynamic model parameters   ***
+CGDO   =3.400e-10 CGSO   =3.400e-10 CGBO   =1.300e-10 
+CGDL   =0.000e+00 CGSL   =0.000e+00 CKAPPA =6.000e-01 
+CF     =0.000e+00 ELM    =5.000e+00 
+XPART  =1.000e+00 CLC    =1.000e-15 CLE    =6.000e-01 
*        *** Parasitic resistance and capacitance related model parameters ***
+RDSW   =3.796e+03 
+CDSC   =0.000e+00 CDSCB  =0.000e+00 CDSCD  =2.171e-04 
+PRWB   =0.000e+00 PRWG   =0.000e+00 CIT    =3.231e-04 
*        *** Process and parameters extraction related model parameters ***
+TOX    =1.270e-08 NGATE  =0.000e+00 
+NLX    =2.784e-07 
*        *** Substrate current related model parameters ***
+ALPHA0 =0.000e+00 BETA0  =3.000e+01 
*        *** Noise effect related model parameters ***
+AF     =1.368e+00 KF     =7.623e-29 EF     =1.000e+00 
+NOIA   =1.000e+20 NOIB   =5.000e+04 NOIC   =-1.40e-12 
*        *** Common extrinsic model parameters ***
+LINT   =9.927e-08 WINT   =3.878e-08 XJ     =3.000e-07 
+RSH    =6.000e+01 JS     =2.000e-05 
+CJ     =6.000e-04 CJSW   =3.300e-10 
+MJ     =4.400e-01 MJSW   =2.400e-01 
+PB     =8.400e-01 
+PBSW   =9.400e-01 
* ----------------------------------------------------------------------
.SUBCKT PD A C PARAMS: AREA=1e-12 PERI=4e-6
* ----------------------------------------------------------------------
************************* SIMULATION PARAMETERS ************************
* ----------------------------------------------------------------------
* format    : PSPICE
* model     : DIODE
* process   : CU[BEQWAVP]
* revision  : B; 
* extracted : CUE 41667; 1998-08; ese(487)
* doc#      : 9933011 REV_B
* ----------------------------------------------------------------------
*                        TYPICAL MEAN CONDITION
* ----------------------------------------------------------------------
* TERMINALS: A=anode=P-region C=cathode=N-region
* VARIABLES: M (mulitiplier), AREA [m^2], PERI [m].
* NOTE: The role of a protection DIODE is to conduct ESD current to VDD 
* (or from VSS). This forward bias is NOT modelled, only leakage current 
* and capacitance during normal operation. Any inductive load etc that 
* will give forward bias, must be limited by other components to within 
* Operating Conditions, otherwise parasitic bipolar action can occur.
*
D1 A C PDINSUBA {AREA}
D2 A C PDINSUBS {PERI}
.ENDS PD
*
.MODEL PDINSUBA D 
+IS     =2.000e-05 N      =1.000e+00 
+CJO    =6.000e-04 M      =4.400e-01 VJ     =8.400e-01 
+TT     =0.000e+00 FC     =0.500e+00 
+EG     =1.110e+00 XTI    =3.000e+00 
+AF     =1.000e+00 KF     =0.000e+00
.MODEL PDINSUBS D
+IS     =0.000e+00 N      =1.000e+00 
+CJO    =3.300e-10 M      =2.400e-01 VJ     =8.400e-01 
+TT     =0.000e+00 FC     =0.500e+00  
+EG     =1.110e+00 XTI    =3.000e+00 
+AF     =1.000e+00 KF     =0.000e+00
* ----------------------------------------------------------------------
.SUBCKT MODNH D G S B PARAMS: W=1e-6 L=1e-6 AD=0 AS=0 PD=0 PS=0 NRD=0 NRS=0
* VARIABLES: W,L,AD,AS,PD,PS,NRD,NRS = standard MOSFET parameters
*
M1 D1 G S B MODNHINSUB W={W} L={L} AD={AD} AS={AS} PD={PD} PS={PS} NRD={NRD} NRS={NRS}
RD D1 D {2.874e+03*2.800e-06/(W)} TC=6.600e-03 
.ENDS MODNH
.MODEL MODNHINSUB NMOS LEVEL=7 
* ----------------------------------------------------------------------
************************* SIMULATION PARAMETERS ************************
* ----------------------------------------------------------------------
* format    : PSPICE
* model     : MOS BSIM3v3
* process   : CU[BEQWAVP]
* revision  : B.1; 
* extracted : CUE 41667; 1998-08; ese(487)
* doc#      : 9933011 REV_B
* ----------------------------------------------------------------------
*                        TYPICAL MEAN CONDITION
* ----------------------------------------------------------------------
*
*        *** Flags ***
+MOBMOD =1.000e+00 CAPMOD =2.000e+00 
+NLEV   =0         NOIMOD =1.000e+00 

*        *** Threshold voltage related model parameters ***
+K1     =1.064e+00 
+K2     =-1.30e-01 K3     =6.535e+00 K3B    =-2.02e+00 
+NCH    =8.762e+16 VTH0   =8.375e-01 
+VOFF   =-1.16e-01 DVT0   =3.561e+00 DVT1   =8.652e-01 
+DVT2   =-2.50e-01 KETA   =-4.48e-02 
+PSCBE1 =3.616e+08 PSCBE2 =1.020e-09 
+DVT0W  =-2.98e+00 DVT1W  =1.306e+06 DVT2W  =-9.24e-03 
*        *** Mobility related model parameters ***
+UA     =1.000e-12 UB     =5.807e-18 UC     =-3.60e-11 
+U0     =3.853e+02 
*        *** Subthreshold related parameters ***
+DSUB   =5.000e-01 ETA0   =1.008e-02 ETAB   =-1.72e-02 
+NFACTOR=6.311e-01 
*        *** Saturation related parameters ***
+EM     =4.100e+07 PCLM   =2.500e+00 
+PDIBLC1=2.750e-02 PDIBLC2=7.929e-03 DROUT  =3.510e-01 
+A0     =9.550e-01 A1     =0.000e+00 A2     =1.000e+00 
+PVAG   =0.000e+00 VSAT   =1.252e+05 AGS    =1.785e-01 
+B0     =2.652e-07 B1     =0.000e+00 DELTA  =1.000e-02 
+PDIBLCB=2.306e-01 
*        *** Geometry modulation related parameters ***
+W0     =3.151e-08 DLC    =5.000e-07 
+DWC    =-8.94e-09 DWB    =0.000e+00 DWG    =0.000e+00 
+LL     =0.000e+00 LW     =0.000e+00 LWL    =0.000e+00 
+LLN    =1.000e+00 LWN    =1.000e+00 WL     =0.000e+00 
+WW     =0.000e+00 WWL    =0.000e+00 WLN    =1.000e+00 
+WWN    =1.000e+00 
*        *** Temperature effect parameters ***
+AT     =3.300e+04 UTE    =-1.90e+00 
+KT1    =-4.20e-01 KT2    =2.200e-02 KT1L   =0.000e+00 
+UA1    =0.000e+00 UB1    =0.000e+00 UC1    =0.000e+00 
+PRT    =0.000e+00 
*        *** Overlap capacitance related and dynamic model parameters   ***
+CGDO   =3.400e-10 CGSO   =3.400e-10 CGBO   =1.300e-10 
+CGDL   =0.000e+00 CGSL   =0.000e+00 CKAPPA =6.000e-01 
+CF     =0.000e+00 ELM    =5.000e+00 
+XPART  =1.000e+00 CLC    =1.000e-15 CLE    =6.000e-01 
*        *** Parasitic resistance and capacitance related model parameters ***
+RDSW   =1.687e+03 
+CDSC   =0.000e+00 CDSCB  =0.000e+00 CDSCD  =0.000e+00 
+PRWB   =0.000e+00 PRWG   =0.000e+00 CIT    =2.234e-04 
*        *** Process and parameters extraction related model parameters ***
+TOX    =1.270e-08 NGATE  =0.000e+00 
+NLX    =1.000e-10 
*        *** Substrate current related model parameters ***
+ALPHA0 =0.000e+00 BETA0  =3.000e+01 
*        *** Noise effect related model parameters ***
+AF     =1.343e+00 KF     =6.896e-27 EF     =1.000e+00 
+NOIA   =1.000e+20 NOIB   =5.000e+04 NOIC   =-1.40e-12 
*        *** Common extrinsic model parameters ***
+LINT   =5.000e-07 WINT   =-8.94e-09 XJ     =3.000e-07 
+RSH    =3.000e+01 JS     =2.000e-05 
+CJ     =3.800e-04 CJSW   =4.300e-10 
+MJ     =4.400e-01 MJSW   =2.500e-01 
+PB     =8.400e-01 TT     =0.000e+00 
+PBSW   =9.400e-01 
* ----------------------------------------------------------------------
.SUBCKT MODNH6 D G S B PARAMS: W=1e-6 L=1e-6 AD=0 AS=0 PD=0 PS=0 NRD=0 NRS=0
* VARIABLES: W,L,AD,AS,PD,PS,NRD,NRS = standard MOSFET parameters
*
M1 D1 G S B MODNH6INSUB W={W} L={L} AD={AD} AS={AS} PD={PD} PS={PS} NRD={NRD} NRS={NRS}
RD D1 D {5.023e+03*6.000e-06/(W)} TC=6.600e-03 
.ENDS MODNH6
.MODEL MODNH6INSUB NMOS LEVEL=7 
* ----------------------------------------------------------------------
************************* SIMULATION PARAMETERS ************************
* ----------------------------------------------------------------------
* format    : PSPICE
* model     : MOS BSIM3v3
* process   : CU[BEQWAVP]
* revision  : B.1; 
* extracted : CUE 41667; 1998-08; ese(487)
* doc#      : 9933011 REV_B
* ----------------------------------------------------------------------
*                        TYPICAL MEAN CONDITION
* ----------------------------------------------------------------------
*
*        *** Flags ***
+MOBMOD =1.000e+00 CAPMOD =2.000e+00 
+NLEV   =0         NOIMOD =1.000e+00 

*        *** Threshold voltage related model parameters ***
+K1     =8.316e-01 
+K2     =-7.27e-02 K3     =6.535e+00 K3B    =-2.02e+00 
+NCH    =7.932e+16 VTH0   =8.588e-01 
+VOFF   =-1.16e-01 DVT0   =3.561e+00 DVT1   =8.652e-01 
+DVT2   =-2.50e-01 KETA   =-4.48e-02 
+PSCBE1 =3.616e+08 PSCBE2 =1.020e-09 
+DVT0W  =-2.98e+00 DVT1W  =1.306e+06 DVT2W  =-9.24e-03 
*        *** Mobility related model parameters ***
+UA     =1.000e-12 UB     =2.937e-18 UC     =-3.60e-11 
+U0     =4.952e+02 
*        *** Subthreshold related parameters ***
+DSUB   =5.000e-01 ETA0   =1.008e-02 ETAB   =-1.72e-02 
+NFACTOR=5.000e-01 
*        *** Saturation related parameters ***
+EM     =4.100e+07 PCLM   =2.500e+00 
+PDIBLC1=2.750e-02 PDIBLC2=6.407e-03 DROUT  =3.510e-01 
+A0     =9.550e-01 A1     =0.000e+00 A2     =1.000e+00 
+PVAG   =0.000e+00 VSAT   =8.561e+04 AGS    =1.785e-01 
+B0     =2.652e-07 B1     =0.000e+00 DELTA  =1.000e-02 
+PDIBLCB=2.306e-01 
*        *** Geometry modulation related parameters ***
+W0     =3.151e-08 DLC    =5.000e-07 
+DWC    =-8.94e-09 DWB    =0.000e+00 DWG    =0.000e+00 
+LL     =0.000e+00 LW     =0.000e+00 LWL    =0.000e+00 
+LLN    =1.000e+00 LWN    =1.000e+00 WL     =0.000e+00 
+WW     =0.000e+00 WWL    =0.000e+00 WLN    =1.000e+00 
+WWN    =1.000e+00 
*        *** Temperature effect parameters ***
+AT     =3.300e+04 UTE    =-1.90e+00 
+KT1    =-4.20e-01 KT2    =2.200e-02 KT1L   =0.000e+00 
+UA1    =0.000e+00 UB1    =0.000e+00 UC1    =0.000e+00 
+PRT    =0.000e+00 
*        *** Overlap capacitance related and dynamic model parameters   ***
+CGDO   =3.400e-10 CGSO   =3.400e-10 CGBO   =1.300e-10 
+CGDL   =0.000e+00 CGSL   =0.000e+00 CKAPPA =6.000e-01 
+CF     =0.000e+00 ELM    =5.000e+00 
+XPART  =1.000e+00 CLC    =1.000e-15 CLE    =6.000e-01 
*        *** Parasitic resistance and capacitance related model parameters ***
+RDSW   =1.687e+03 
+CDSC   =0.000e+00 CDSCB  =0.000e+00 CDSCD  =0.000e+00 
+PRWB   =0.000e+00 PRWG   =0.000e+00 CIT    =2.234e-04 
*        *** Process and parameters extraction related model parameters ***
+TOX    =1.270e-08 NGATE  =0.000e+00 
+NLX    =1.000e-10 
*        *** Substrate current related model parameters ***
+ALPHA0 =0.000e+00 BETA0  =3.000e+01 
*        *** Noise effect related model parameters ***
+AF     =1.000e+00 KF     =6.896e-27 EF     =1.000e+00 
+NOIA   =1.000e+20 NOIB   =5.000e+04 NOIC   =-1.40e-12 
*        *** Common extrinsic model parameters ***
+LINT   =5.000e-07 WINT   =-8.94e-09 XJ     =3.000e-07 
+RSH    =3.000e+01 JS     =2.000e-05 
+CJ     =3.800e-04 CJSW   =4.300e-10 
+MJ     =4.400e-01 MJSW   =2.500e-01 
+PB     =8.400e-01 TT     =0.000e+00 
+PBSW   =9.400e-01 
* ----------------------------------------------------------------------
