setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port svf -file "E:/Work/dp/Bus_Blaster/buffer_logic/selftest/selftest.svf"
addDevice -p 1 -file "E:/Work/dp/Bus_Blaster/buffer_logic/selftest/selftest.jed"
saveArchive -file "selftest.iaf" -dir "E:\Work\dp\Bus_Blaster\buffer_logic\selftest"
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
