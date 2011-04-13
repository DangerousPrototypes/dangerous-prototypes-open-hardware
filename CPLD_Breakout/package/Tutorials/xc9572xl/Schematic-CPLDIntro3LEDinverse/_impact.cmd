setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port xsvf -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc9572xl/Schematic-CPLDIntro3LEDinverse/sch-CPLDIntro3LEDinverse.xsvf"
addDevice -p 1 -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc9572xl/Schematic-CPLDIntro3LEDinverse/CPLDIntro3LEDinverse.jed"
Program -p 1 -e -v 
setCable -port svf -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc9572xl/Schematic-CPLDIntro3LEDinverse/schCPLDIntro3LEDinverse.svf"
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
deleteDevice -position 1
