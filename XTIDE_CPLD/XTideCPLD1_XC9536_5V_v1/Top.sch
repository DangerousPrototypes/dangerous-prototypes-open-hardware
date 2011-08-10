<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="iS5" />
        <signal name="iA0_ISA" />
        <signal name="iA1_ISA" />
        <signal name="iA2_ISA" />
        <signal name="iIOR_ISA" />
        <signal name="iIOW_ISA" />
        <signal name="iA3" />
        <signal name="iA5" />
        <signal name="iA7" />
        <signal name="iA9" />
        <signal name="iA4" />
        <signal name="iA6" />
        <signal name="iA8" />
        <signal name="iSW4" />
        <signal name="iS1" />
        <signal name="iS2" />
        <signal name="iS3" />
        <signal name="iS4" />
        <signal name="iCS3FX" />
        <signal name="iCS1FX" />
        <signal name="iRESDRVn" />
        <signal name="iSW3" />
        <signal name="iSW2" />
        <signal name="iSW1" />
        <signal name="iAEN" />
        <signal name="iRESDRV" />
        <signal name="RESDRV" />
        <signal name="IOW_ISA" />
        <signal name="IOR_ISA" />
        <signal name="AEN" />
        <signal name="A4" />
        <signal name="A5" />
        <signal name="A6" />
        <signal name="A7" />
        <signal name="A8" />
        <signal name="A9" />
        <signal name="A3" />
        <signal name="A0_ISA" />
        <signal name="A1_ISA" />
        <signal name="A2_ISA" />
        <signal name="ADDR_IO_A8" />
        <signal name="ADDR_IO_A7" />
        <signal name="ADDR_IO_A6" />
        <signal name="ADDR_IO_A5" />
        <signal name="A2_IDE" />
        <signal name="A0_IDE" />
        <signal name="A1_IDE" />
        <signal name="IOR_IDE" />
        <signal name="IOW_IDE" />
        <signal name="S1" />
        <signal name="S2" />
        <signal name="S3" />
        <signal name="S4" />
        <signal name="S5" />
        <signal name="CS3FX" />
        <signal name="CS1FX" />
        <signal name="RESET" />
        <port polarity="Input" name="RESDRV" />
        <port polarity="Input" name="IOW_ISA" />
        <port polarity="Input" name="IOR_ISA" />
        <port polarity="Input" name="AEN" />
        <port polarity="Input" name="A4" />
        <port polarity="Input" name="A5" />
        <port polarity="Input" name="A6" />
        <port polarity="Input" name="A7" />
        <port polarity="Input" name="A8" />
        <port polarity="Input" name="A9" />
        <port polarity="Input" name="A3" />
        <port polarity="Input" name="A0_ISA" />
        <port polarity="Input" name="A1_ISA" />
        <port polarity="Input" name="A2_ISA" />
        <port polarity="Input" name="ADDR_IO_A8" />
        <port polarity="Input" name="ADDR_IO_A7" />
        <port polarity="Input" name="ADDR_IO_A6" />
        <port polarity="Input" name="ADDR_IO_A5" />
        <port polarity="Output" name="A2_IDE" />
        <port polarity="Output" name="A0_IDE" />
        <port polarity="Output" name="A1_IDE" />
        <port polarity="Output" name="IOR_IDE" />
        <port polarity="Output" name="IOW_IDE" />
        <port polarity="Output" name="S1" />
        <port polarity="Output" name="S2" />
        <port polarity="Output" name="S3" />
        <port polarity="Output" name="S4" />
        <port polarity="Output" name="S5" />
        <port polarity="Output" name="CS3FX" />
        <port polarity="Output" name="CS1FX" />
        <port polarity="Output" name="RESET" />
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <blockdef name="obuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
        </blockdef>
        <blockdef name="IDE_DECODE">
            <timestamp>2011-4-19T2:34:32</timestamp>
            <rect width="256" x="64" y="-1152" height="1152" />
            <line x2="0" y1="-1120" y2="-1120" x1="64" />
            <line x2="0" y1="-1056" y2="-1056" x1="64" />
            <line x2="0" y1="-992" y2="-992" x1="64" />
            <line x2="0" y1="-928" y2="-928" x1="64" />
            <line x2="0" y1="-864" y2="-864" x1="64" />
            <line x2="0" y1="-800" y2="-800" x1="64" />
            <line x2="0" y1="-736" y2="-736" x1="64" />
            <line x2="0" y1="-672" y2="-672" x1="64" />
            <line x2="0" y1="-608" y2="-608" x1="64" />
            <line x2="0" y1="-544" y2="-544" x1="64" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <line x2="384" y1="-1120" y2="-1120" x1="320" />
            <line x2="384" y1="-1056" y2="-1056" x1="320" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="384" y1="-992" y2="-992" x1="320" />
            <line x2="384" y1="-928" y2="-928" x1="320" />
            <line x2="384" y1="-864" y2="-864" x1="320" />
            <line x2="384" y1="-800" y2="-800" x1="320" />
            <line x2="384" y1="-736" y2="-736" x1="320" />
            <line x2="384" y1="-672" y2="-672" x1="320" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
        </blockdef>
        <block symbolname="ibuf" name="XLXI_190">
            <blockpin signalname="A0_ISA" name="I" />
            <blockpin signalname="iA0_ISA" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_189">
            <blockpin signalname="A1_ISA" name="I" />
            <blockpin signalname="iA1_ISA" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_188">
            <blockpin signalname="A2_ISA" name="I" />
            <blockpin signalname="iA2_ISA" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_175">
            <blockpin signalname="A3" name="I" />
            <blockpin signalname="iA3" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_11">
            <blockpin signalname="A4" name="I" />
            <blockpin signalname="iA4" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_144">
            <blockpin signalname="AEN" name="I" />
            <blockpin signalname="iAEN" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_100">
            <blockpin signalname="RESDRV" name="I" />
            <blockpin signalname="iRESDRV" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_97">
            <blockpin signalname="IOW_ISA" name="I" />
            <blockpin signalname="iIOW_ISA" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_130">
            <blockpin signalname="IOR_ISA" name="I" />
            <blockpin signalname="iIOR_ISA" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_12">
            <blockpin signalname="A5" name="I" />
            <blockpin signalname="iA5" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_13">
            <blockpin signalname="A6" name="I" />
            <blockpin signalname="iA6" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_14">
            <blockpin signalname="A7" name="I" />
            <blockpin signalname="iA7" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_15">
            <blockpin signalname="A8" name="I" />
            <blockpin signalname="iA8" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_16">
            <blockpin signalname="A9" name="I" />
            <blockpin signalname="iA9" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_228">
            <blockpin signalname="ADDR_IO_A8" name="I" />
            <blockpin signalname="iSW1" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_227">
            <blockpin signalname="ADDR_IO_A7" name="I" />
            <blockpin signalname="iSW2" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_221">
            <blockpin signalname="ADDR_IO_A6" name="I" />
            <blockpin signalname="iSW3" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_222">
            <blockpin signalname="ADDR_IO_A5" name="I" />
            <blockpin signalname="iSW4" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_120">
            <blockpin signalname="iA2_ISA" name="I" />
            <blockpin signalname="A1_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_118">
            <blockpin signalname="iA1_ISA" name="I" />
            <blockpin signalname="A2_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_119">
            <blockpin signalname="iA0_ISA" name="I" />
            <blockpin signalname="A0_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_145">
            <blockpin signalname="iIOW_ISA" name="I" />
            <blockpin signalname="IOW_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_121">
            <blockpin signalname="iIOR_ISA" name="I" />
            <blockpin signalname="IOR_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_115">
            <blockpin signalname="iS5" name="I" />
            <blockpin signalname="S5" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_114">
            <blockpin signalname="iS4" name="I" />
            <blockpin signalname="S4" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_113">
            <blockpin signalname="iS3" name="I" />
            <blockpin signalname="S3" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_112">
            <blockpin signalname="iS2" name="I" />
            <blockpin signalname="S2" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_111">
            <blockpin signalname="iS1" name="I" />
            <blockpin signalname="S1" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_116">
            <blockpin signalname="iCS3FX" name="I" />
            <blockpin signalname="CS3FX" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_117">
            <blockpin signalname="iCS1FX" name="I" />
            <blockpin signalname="CS1FX" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_146">
            <blockpin signalname="iRESDRVn" name="I" />
            <blockpin signalname="RESET" name="O" />
        </block>
        <block symbolname="IDE_DECODE" name="XLXI_229">
            <blockpin signalname="iA0_ISA" name="iA0_ISA" />
            <blockpin signalname="iA1_ISA" name="iA1_ISA" />
            <blockpin signalname="iA2_ISA" name="iA2_ISA" />
            <blockpin signalname="iA3" name="iA3" />
            <blockpin signalname="iA4" name="iA4" />
            <blockpin signalname="iA5" name="iA5" />
            <blockpin signalname="iA6" name="iA6" />
            <blockpin signalname="iA7" name="iA7" />
            <blockpin signalname="iA8" name="iA8" />
            <blockpin signalname="iA9" name="iA9" />
            <blockpin signalname="iAEN" name="iAEN" />
            <blockpin signalname="iCS1FX" name="iCS1FX" />
            <blockpin signalname="iCS3FX" name="iCS3FX" />
            <blockpin signalname="iIOR_ISA" name="iIOR_ISA" />
            <blockpin signalname="iIOW_ISA" name="iIOW_ISA" />
            <blockpin signalname="iRESDRV" name="iRESDRV" />
            <blockpin signalname="iRESDRVn" name="iRESDRVn" />
            <blockpin signalname="iS1" name="iS1" />
            <blockpin signalname="iS2" name="iS2" />
            <blockpin signalname="iS3" name="iS3" />
            <blockpin signalname="iS4" name="iS4" />
            <blockpin signalname="iS5" name="iS5" />
            <blockpin signalname="iSW1" name="iSW1" />
            <blockpin signalname="iSW2" name="iSW2" />
            <blockpin signalname="iSW3" name="iSW3" />
            <blockpin signalname="iSW4" name="iSW4" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="5440" height="3520">
        <branch name="iA3">
            <wire x2="2336" y1="1184" y2="1184" x1="1904" />
            <wire x2="2352" y1="1184" y2="1184" x1="2336" />
        </branch>
        <branch name="iA5">
            <wire x2="2336" y1="1312" y2="1312" x1="1904" />
            <wire x2="2352" y1="1312" y2="1312" x1="2336" />
        </branch>
        <branch name="iA7">
            <wire x2="2336" y1="1440" y2="1440" x1="1904" />
            <wire x2="2352" y1="1440" y2="1440" x1="2336" />
        </branch>
        <branch name="iA9">
            <wire x2="2336" y1="1568" y2="1568" x1="1904" />
            <wire x2="2352" y1="1568" y2="1568" x1="2336" />
        </branch>
        <branch name="iA4">
            <wire x2="2336" y1="1248" y2="1248" x1="1904" />
            <wire x2="2352" y1="1248" y2="1248" x1="2336" />
        </branch>
        <branch name="iA6">
            <wire x2="2336" y1="1376" y2="1376" x1="1904" />
            <wire x2="2352" y1="1376" y2="1376" x1="2336" />
        </branch>
        <branch name="iA8">
            <wire x2="2336" y1="1504" y2="1504" x1="1904" />
            <wire x2="2352" y1="1504" y2="1504" x1="2336" />
        </branch>
        <branch name="iSW4">
            <wire x2="2336" y1="2080" y2="2080" x1="1904" />
            <wire x2="2352" y1="2080" y2="2080" x1="2336" />
        </branch>
        <branch name="iS1">
            <wire x2="2752" y1="1184" y2="1184" x1="2736" />
            <wire x2="2976" y1="1184" y2="1184" x1="2752" />
        </branch>
        <branch name="iS2">
            <wire x2="2752" y1="1248" y2="1248" x1="2736" />
            <wire x2="2976" y1="1248" y2="1248" x1="2752" />
        </branch>
        <branch name="iS3">
            <wire x2="2752" y1="1312" y2="1312" x1="2736" />
            <wire x2="2976" y1="1312" y2="1312" x1="2752" />
        </branch>
        <branch name="iS4">
            <wire x2="2752" y1="1376" y2="1376" x1="2736" />
            <wire x2="2976" y1="1376" y2="1376" x1="2752" />
        </branch>
        <branch name="iCS3FX">
            <wire x2="2752" y1="1056" y2="1056" x1="2736" />
            <wire x2="2976" y1="1056" y2="1056" x1="2752" />
        </branch>
        <branch name="iCS1FX">
            <wire x2="2752" y1="992" y2="992" x1="2736" />
            <wire x2="2976" y1="992" y2="992" x1="2752" />
        </branch>
        <branch name="iRESDRVn">
            <wire x2="2752" y1="1120" y2="1120" x1="2736" />
            <wire x2="2976" y1="1120" y2="1120" x1="2752" />
        </branch>
        <branch name="iSW3">
            <wire x2="2336" y1="2016" y2="2016" x1="1904" />
            <wire x2="2352" y1="2016" y2="2016" x1="2336" />
        </branch>
        <branch name="iSW2">
            <wire x2="2336" y1="1952" y2="1952" x1="1904" />
            <wire x2="2352" y1="1952" y2="1952" x1="2336" />
        </branch>
        <branch name="iSW1">
            <wire x2="2336" y1="1888" y2="1888" x1="1904" />
            <wire x2="2352" y1="1888" y2="1888" x1="2336" />
        </branch>
        <branch name="iAEN">
            <wire x2="2336" y1="1632" y2="1632" x1="1904" />
            <wire x2="2352" y1="1632" y2="1632" x1="2336" />
        </branch>
        <branch name="iRESDRV">
            <wire x2="2336" y1="1824" y2="1824" x1="1904" />
            <wire x2="2352" y1="1824" y2="1824" x1="2336" />
        </branch>
        <branch name="iS5">
            <wire x2="2752" y1="1440" y2="1440" x1="2736" />
            <wire x2="2976" y1="1440" y2="1440" x1="2752" />
        </branch>
        <branch name="RESDRV">
            <wire x2="1680" y1="1824" y2="1824" x1="1648" />
        </branch>
        <branch name="IOW_ISA">
            <wire x2="1680" y1="1760" y2="1760" x1="1648" />
        </branch>
        <branch name="IOR_ISA">
            <wire x2="1680" y1="1696" y2="1696" x1="1648" />
        </branch>
        <branch name="AEN">
            <wire x2="1680" y1="1632" y2="1632" x1="1648" />
        </branch>
        <branch name="A4">
            <wire x2="1680" y1="1248" y2="1248" x1="1648" />
        </branch>
        <branch name="A5">
            <wire x2="1680" y1="1312" y2="1312" x1="1648" />
        </branch>
        <branch name="A6">
            <wire x2="1680" y1="1376" y2="1376" x1="1648" />
        </branch>
        <branch name="A7">
            <wire x2="1680" y1="1440" y2="1440" x1="1648" />
        </branch>
        <branch name="A8">
            <wire x2="1680" y1="1504" y2="1504" x1="1648" />
        </branch>
        <branch name="A9">
            <wire x2="1680" y1="1568" y2="1568" x1="1648" />
        </branch>
        <branch name="A3">
            <wire x2="1680" y1="1184" y2="1184" x1="1648" />
        </branch>
        <branch name="A0_ISA">
            <wire x2="1680" y1="992" y2="992" x1="1648" />
        </branch>
        <branch name="A1_ISA">
            <wire x2="1680" y1="1056" y2="1056" x1="1648" />
        </branch>
        <branch name="A2_ISA">
            <wire x2="1680" y1="1120" y2="1120" x1="1648" />
        </branch>
        <instance x="1680" y="1024" name="XLXI_190" orien="R0" />
        <instance x="1680" y="1088" name="XLXI_189" orien="R0" />
        <instance x="1680" y="1152" name="XLXI_188" orien="R0" />
        <instance x="1680" y="1216" name="XLXI_175" orien="R0" />
        <instance x="1680" y="1280" name="XLXI_11" orien="R0" />
        <instance x="1680" y="1664" name="XLXI_144" orien="R0" />
        <instance x="1680" y="1856" name="XLXI_100" orien="R0" />
        <instance x="1680" y="1792" name="XLXI_97" orien="R0" />
        <instance x="1680" y="1728" name="XLXI_130" orien="R0" />
        <instance x="1680" y="1344" name="XLXI_12" orien="R0" />
        <instance x="1680" y="1408" name="XLXI_13" orien="R0" />
        <instance x="1680" y="1472" name="XLXI_14" orien="R0" />
        <instance x="1680" y="1536" name="XLXI_15" orien="R0" />
        <instance x="1680" y="1600" name="XLXI_16" orien="R0" />
        <instance x="1680" y="1920" name="XLXI_228" orien="R0" />
        <branch name="ADDR_IO_A8">
            <wire x2="1680" y1="1888" y2="1888" x1="1648" />
        </branch>
        <instance x="1680" y="1984" name="XLXI_227" orien="R0" />
        <branch name="ADDR_IO_A7">
            <wire x2="1680" y1="1952" y2="1952" x1="1648" />
        </branch>
        <instance x="1680" y="2048" name="XLXI_221" orien="R0" />
        <branch name="ADDR_IO_A6">
            <wire x2="1680" y1="2016" y2="2016" x1="1648" />
        </branch>
        <instance x="1680" y="2112" name="XLXI_222" orien="R0" />
        <branch name="ADDR_IO_A5">
            <wire x2="1680" y1="2080" y2="2080" x1="1648" />
        </branch>
        <branch name="A2_IDE">
            <wire x2="3232" y1="2448" y2="2448" x1="3200" />
        </branch>
        <branch name="A0_IDE">
            <wire x2="3232" y1="2384" y2="2384" x1="3200" />
        </branch>
        <instance x="2976" y="2544" name="XLXI_120" orien="R0" />
        <branch name="A1_IDE">
            <wire x2="3232" y1="2512" y2="2512" x1="3200" />
        </branch>
        <branch name="IOR_IDE">
            <wire x2="3232" y1="2256" y2="2256" x1="3200" />
        </branch>
        <branch name="IOW_IDE">
            <wire x2="3232" y1="2320" y2="2320" x1="3200" />
        </branch>
        <instance x="2976" y="2480" name="XLXI_118" orien="R0" />
        <instance x="2976" y="2416" name="XLXI_119" orien="R0" />
        <instance x="2976" y="2352" name="XLXI_145" orien="R0" />
        <instance x="2976" y="2288" name="XLXI_121" orien="R0" />
        <instance x="2976" y="1472" name="XLXI_115" orien="R0" />
        <branch name="S1">
            <wire x2="3232" y1="1184" y2="1184" x1="3200" />
        </branch>
        <branch name="S2">
            <wire x2="3232" y1="1248" y2="1248" x1="3200" />
        </branch>
        <branch name="S3">
            <wire x2="3232" y1="1312" y2="1312" x1="3200" />
        </branch>
        <branch name="S4">
            <wire x2="3232" y1="1376" y2="1376" x1="3200" />
        </branch>
        <branch name="S5">
            <wire x2="3232" y1="1440" y2="1440" x1="3200" />
        </branch>
        <branch name="CS3FX">
            <wire x2="3232" y1="1056" y2="1056" x1="3200" />
        </branch>
        <branch name="CS1FX">
            <wire x2="3232" y1="992" y2="992" x1="3200" />
        </branch>
        <branch name="RESET">
            <wire x2="3232" y1="1120" y2="1120" x1="3200" />
        </branch>
        <instance x="2976" y="1408" name="XLXI_114" orien="R0" />
        <instance x="2976" y="1344" name="XLXI_113" orien="R0" />
        <instance x="2976" y="1280" name="XLXI_112" orien="R0" />
        <instance x="2976" y="1216" name="XLXI_111" orien="R0" />
        <instance x="2976" y="1088" name="XLXI_116" orien="R0" />
        <instance x="2976" y="1024" name="XLXI_117" orien="R0" />
        <instance x="2976" y="1152" name="XLXI_146" orien="R0" />
        <branch name="iA2_ISA">
            <wire x2="2032" y1="1120" y2="1120" x1="1904" />
            <wire x2="2352" y1="1120" y2="1120" x1="2032" />
            <wire x2="2032" y1="1120" y2="2512" x1="2032" />
            <wire x2="2976" y1="2512" y2="2512" x1="2032" />
        </branch>
        <branch name="iA1_ISA">
            <wire x2="2096" y1="1056" y2="1056" x1="1904" />
            <wire x2="2352" y1="1056" y2="1056" x1="2096" />
            <wire x2="2096" y1="1056" y2="2448" x1="2096" />
            <wire x2="2976" y1="2448" y2="2448" x1="2096" />
        </branch>
        <branch name="iA0_ISA">
            <wire x2="2160" y1="992" y2="992" x1="1904" />
            <wire x2="2352" y1="992" y2="992" x1="2160" />
            <wire x2="2160" y1="992" y2="2384" x1="2160" />
            <wire x2="2976" y1="2384" y2="2384" x1="2160" />
        </branch>
        <branch name="iIOW_ISA">
            <wire x2="2224" y1="1760" y2="1760" x1="1904" />
            <wire x2="2352" y1="1760" y2="1760" x1="2224" />
            <wire x2="2224" y1="1760" y2="2320" x1="2224" />
            <wire x2="2976" y1="2320" y2="2320" x1="2224" />
        </branch>
        <branch name="iIOR_ISA">
            <wire x2="2288" y1="1696" y2="1696" x1="1904" />
            <wire x2="2352" y1="1696" y2="1696" x1="2288" />
            <wire x2="2288" y1="1696" y2="2256" x1="2288" />
            <wire x2="2976" y1="2256" y2="2256" x1="2288" />
        </branch>
        <iomarker fontsize="28" x="1648" y="992" name="A0_ISA" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1056" name="A1_ISA" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1120" name="A2_ISA" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1184" name="A3" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1248" name="A4" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1632" name="AEN" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1824" name="RESDRV" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1760" name="IOW_ISA" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1696" name="IOR_ISA" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1312" name="A5" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1376" name="A6" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1440" name="A7" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1504" name="A8" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1568" name="A9" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1888" name="ADDR_IO_A8" orien="R180" />
        <iomarker fontsize="28" x="1648" y="1952" name="ADDR_IO_A7" orien="R180" />
        <iomarker fontsize="28" x="1648" y="2016" name="ADDR_IO_A6" orien="R180" />
        <iomarker fontsize="28" x="1648" y="2080" name="ADDR_IO_A5" orien="R180" />
        <iomarker fontsize="28" x="3232" y="2512" name="A1_IDE" orien="R0" />
        <iomarker fontsize="28" x="3232" y="2448" name="A2_IDE" orien="R0" />
        <iomarker fontsize="28" x="3232" y="2384" name="A0_IDE" orien="R0" />
        <iomarker fontsize="28" x="3232" y="2320" name="IOW_IDE" orien="R0" />
        <iomarker fontsize="28" x="3232" y="2256" name="IOR_IDE" orien="R0" />
        <iomarker fontsize="28" x="3232" y="1440" name="S5" orien="R0" />
        <iomarker fontsize="28" x="3232" y="1376" name="S4" orien="R0" />
        <iomarker fontsize="28" x="3232" y="1312" name="S3" orien="R0" />
        <iomarker fontsize="28" x="3232" y="1248" name="S2" orien="R0" />
        <iomarker fontsize="28" x="3232" y="1184" name="S1" orien="R0" />
        <iomarker fontsize="28" x="3232" y="1056" name="CS3FX" orien="R0" />
        <iomarker fontsize="28" x="3232" y="992" name="CS1FX" orien="R0" />
        <iomarker fontsize="28" x="3232" y="1120" name="RESET" orien="R0" />
        <instance x="2352" y="2112" name="XLXI_229" orien="R0">
        </instance>
    </sheet>
</drawing>