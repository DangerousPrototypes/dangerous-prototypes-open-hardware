setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port xsvf -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc9572xl/VHDL-CPLDIntro3LEDinverse/VHDL-CPLDIntro3LEDinverse.xsvf"
addDevice -p 1 -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc9572xl/VHDL-CPLDIntro3LEDinverse/light_LED_PB.jed"
Program -p 1 -e -v 
setCable -port svf -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc9572xl/VHDL-CPLDIntro1LEDon/VHDL-CPLDIntro3LEDinverse.svf"
setCable -port svf -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc9572xl/VHDL-CPLDIntro3LEDinverse/VHDL-CPLDIntro3LEDinverse.svf"
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
saveProjectFile -file "E:\Work\dp\CPLD_Breakout\package\Tutorials\xc9572xl\VHDL-CPLDIntro1LEDon\\auto_project.ipf"
deleteDevice -position 1
