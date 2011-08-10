setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port xsvf -file "D:/Xilinx/Projects/XTideCPLD1_XC9572XL_3.3V_v1a/XTideCPLD1_XC9572XL_3.3V_v1a.xsvf"
addDevice -p 1 -file "D:/Xilinx/Projects/XTideCPLD1_XC9572XL_3.3V_v1a/Top.jed"
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
saveProjectFile -file "\auto_project.ipf"
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
