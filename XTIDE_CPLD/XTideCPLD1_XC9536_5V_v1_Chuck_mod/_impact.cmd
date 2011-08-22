setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port xsvf -file "C:/Xilinx/Projects/XTideCPLD1_XC9536_5V_v1_Chuck_mod/XTideCPLD1_XC9536_5V_v1_Chuck_mod.xsvf"
addDevice -p 1 -file "C:/Xilinx/Projects/XTideCPLD1_XC9536_5V_v1_Chuck_mod/Top.jed"
Program -p 1 -e -v 
setMode -bs
setMode -bs
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
setMode -bs
saveProjectFile -file "C:\Xilinx\Projects\XTideCPLD1_XC9536_5V_v1\\auto_project.ipf"
setMode -bs
setMode -bs
deleteDevice -position 1
setMode -bs
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
