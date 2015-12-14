##############################################################################
## Filename:          C:\hlocal\SE\p3\Practica3SE\Practica3SE/drivers/teclado_v1_00_a/data/teclado_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Wed Nov 25 12:56:12 2015 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "teclado" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
