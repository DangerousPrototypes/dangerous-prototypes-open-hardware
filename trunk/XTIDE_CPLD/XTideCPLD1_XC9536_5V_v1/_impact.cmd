setPreference -pref StartupClock:AUTO_CORRECTION
setPreference -pref AutoSignature:FALSE
setPreference -pref KeepSVF:FALSE
setPreference -pref ConcurrentMode:FALSE
setPreference -pref UseHighz:FALSE
setPreference -pref svfUseTime:FALSE
setPreference -pref SpiByteSwap:AUTO_CORRECTION
setPreference -pref AutoInfer:TRUE
setPreference -pref SvfPlayDisplayComments:FALSE
setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port xsvf -file "D:/Xilinx/Projects/XTideCPLD1_XC9536_5V_v1/XTideCPLD1_XC9536_5V_v1.xsvf"
addDevice -p 1 -file "D:/Xilinx/Projects/XTideCPLD1_XC9536_5V_v1/Top.jed"
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
