setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port svf -file "E:/Work/dp-svn/trunk/BusBlasterv2/bitstreams/BBv2-KTlink-v1.0.svf"
addDevice -p 1 -file "E:/Work/dp-svn/trunk/BusBlasterv2/bitstreams/KTlink/BBv2KTLINK.jed"
setCable -port svf -file "E:/Work/dp-svn/trunk/BusBlasterv2/bitstreams/BBv2-KTlink-v1.0.svf"
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
