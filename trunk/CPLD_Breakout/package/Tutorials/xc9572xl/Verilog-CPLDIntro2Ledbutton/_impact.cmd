setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port xsvf -file "E:/Work/dp-svn/trunk/CPLD-breakout/demos/xc9572xl/Verilog-CPLDIntro2Ledbutton/CPLDIntro2Ledbutton.xsvf"
addDevice -p 1 -file "E:/Work/dp-svn/trunk/CPLD-breakout/demos/xc9572xl/Verilog-CPLDIntro2Ledbutton/CPLDIntro2Ledbutton.jed"
Program -p 1 -e -v 
saveArchive -file "CPLDIntro2Ledbutton.iaf" -dir "E:\Work\dp-svn\trunk\CPLD-breakout\demos\xc9572xl\Verilog-CPLDIntro2Ledbutton"
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
