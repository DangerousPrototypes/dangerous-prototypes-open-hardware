setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port xsvf -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc2c64a/Verilog-CPLDIntro2Ledbutton/Verilog-CPLDIntro2Ledbutton.xsvf"
addDevice -p 1 -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc2c64a/Verilog-CPLDIntro2Ledbutton/CPLDIntro2Ledbutton.jed"
Program -p 1 -e -v 
setCable -port svf -file "E:/Work/dp/CPLD_Breakout/package/Tutorials/xc2c64a/Verilog-CPLDIntro2Ledbutton/Verilog-CPLDIntro2Ledbutton.svf"
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
