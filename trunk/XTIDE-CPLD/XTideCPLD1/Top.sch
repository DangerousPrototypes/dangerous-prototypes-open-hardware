<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
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
        <signal name="A18" />
        <signal name="A17" />
        <signal name="A16" />
        <signal name="A15" />
        <signal name="A14" />
        <signal name="A13" />
        <signal name="A19" />
        <signal name="A3" />
        <signal name="A0_ISA" />
        <signal name="A1_ISA" />
        <signal name="A2_ISA" />
        <signal name="S1" />
        <signal name="S2" />
        <signal name="S3" />
        <signal name="S4" />
        <signal name="S5" />
        <signal name="CS3FX" />
        <signal name="CS1FX" />
        <signal name="RESET" />
        <signal name="XLXN_273" />
        <signal name="XLXN_275" />
        <signal name="XLXN_277" />
        <signal name="XLXN_279" />
        <signal name="XLXN_281" />
        <signal name="XLXN_282" />
        <signal name="XLXN_285" />
        <signal name="SW1" />
        <signal name="SW2" />
        <signal name="SW3" />
        <signal name="SW4" />
        <signal name="SW5" />
        <signal name="SW6" />
        <signal name="SW7" />
        <signal name="SW8" />
        <signal name="XLXN_302" />
        <signal name="XLXN_303" />
        <signal name="XLXN_304" />
        <signal name="XLXN_305" />
        <signal name="XLXN_306" />
        <signal name="XLXN_307" />
        <signal name="XLXN_308" />
        <signal name="XLXN_309" />
        <signal name="XLXN_310" />
        <signal name="XLXN_311" />
        <signal name="XLXN_312" />
        <signal name="XLXN_313" />
        <signal name="XLXN_314" />
        <signal name="XLXN_315" />
        <signal name="XLXN_316" />
        <signal name="XLXN_317" />
        <signal name="XLXN_318" />
        <signal name="XLXN_319" />
        <signal name="XLXN_320" />
        <signal name="XLXN_321" />
        <signal name="XLXN_322" />
        <signal name="XLXN_323" />
        <signal name="ROMEN" />
        <signal name="XLXN_325" />
        <signal name="XLXN_326" />
        <signal name="XLXN_327" />
        <signal name="XLXN_328" />
        <signal name="XLXN_329" />
        <signal name="XLXN_330" />
        <signal name="XLXN_331" />
        <signal name="XLXN_332" />
        <signal name="XLXN_333" />
        <signal name="A2_IDE" />
        <signal name="IOR_IDE" />
        <signal name="IOW_IDE" />
        <signal name="A0_IDE" />
        <signal name="A1_IDE" />
        <signal name="XLXN_346" />
        <signal name="XLXN_347" />
        <signal name="XLXN_348" />
        <signal name="XLXN_349" />
        <signal name="XLXN_350" />
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
        <port polarity="Input" name="A18" />
        <port polarity="Input" name="A17" />
        <port polarity="Input" name="A16" />
        <port polarity="Input" name="A15" />
        <port polarity="Input" name="A14" />
        <port polarity="Input" name="A13" />
        <port polarity="Input" name="A19" />
        <port polarity="Input" name="A3" />
        <port polarity="Input" name="A0_ISA" />
        <port polarity="Input" name="A1_ISA" />
        <port polarity="Input" name="A2_ISA" />
        <port polarity="Output" name="S1" />
        <port polarity="Output" name="S2" />
        <port polarity="Output" name="S3" />
        <port polarity="Output" name="S4" />
        <port polarity="Output" name="S5" />
        <port polarity="Output" name="CS3FX" />
        <port polarity="Output" name="CS1FX" />
        <port polarity="Output" name="RESET" />
        <port polarity="Input" name="SW1" />
        <port polarity="Input" name="SW2" />
        <port polarity="Input" name="SW3" />
        <port polarity="Input" name="SW4" />
        <port polarity="Input" name="SW5" />
        <port polarity="Input" name="SW6" />
        <port polarity="Input" name="SW7" />
        <port polarity="Input" name="SW8" />
        <port polarity="Output" name="ROMEN" />
        <port polarity="Output" name="A2_IDE" />
        <port polarity="Output" name="IOR_IDE" />
        <port polarity="Output" name="IOW_IDE" />
        <port polarity="Output" name="A0_IDE" />
        <port polarity="Output" name="A1_IDE" />
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
            <timestamp>2010-9-15T10:36:20</timestamp>
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
        <blockdef name="ROM_DECODE">
            <timestamp>2010-9-15T10:29:43</timestamp>
            <rect width="256" x="64" y="-1120" height="1120" />
            <line x2="0" y1="-1088" y2="-1088" x1="64" />
            <line x2="0" y1="-992" y2="-992" x1="64" />
            <line x2="0" y1="-896" y2="-896" x1="64" />
            <line x2="0" y1="-800" y2="-800" x1="64" />
            <line x2="0" y1="-704" y2="-704" x1="64" />
            <line x2="0" y1="-608" y2="-608" x1="64" />
            <line x2="0" y1="-512" y2="-512" x1="64" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <line x2="384" y1="-1088" y2="-1088" x1="320" />
            <line x2="0" y1="-320" y2="-320" x1="64" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-128" y2="-128" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
        </blockdef>
        <block symbolname="ibuf" name="XLXI_130">
            <blockpin signalname="IOR_ISA" name="I" />
            <blockpin signalname="XLXN_349" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_100">
            <blockpin signalname="RESDRV" name="I" />
            <blockpin signalname="XLXN_285" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_97">
            <blockpin signalname="IOW_ISA" name="I" />
            <blockpin signalname="XLXN_350" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_144">
            <blockpin signalname="AEN" name="I" />
            <blockpin signalname="XLXN_318" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_12">
            <blockpin signalname="A5" name="I" />
            <blockpin signalname="XLXN_277" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_13">
            <blockpin signalname="A6" name="I" />
            <blockpin signalname="XLXN_316" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_14">
            <blockpin signalname="A7" name="I" />
            <blockpin signalname="XLXN_279" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_15">
            <blockpin signalname="A8" name="I" />
            <blockpin signalname="XLXN_317" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_11">
            <blockpin signalname="A4" name="I" />
            <blockpin signalname="XLXN_315" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_16">
            <blockpin signalname="A9" name="I" />
            <blockpin signalname="XLXN_281" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_23">
            <blockpin signalname="A19" name="I" />
            <blockpin signalname="XLXN_306" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_22">
            <blockpin signalname="A18" name="I" />
            <blockpin signalname="XLXN_307" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_21">
            <blockpin signalname="A17" name="I" />
            <blockpin signalname="XLXN_308" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_20">
            <blockpin signalname="A16" name="I" />
            <blockpin signalname="XLXN_309" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_19">
            <blockpin signalname="A15" name="I" />
            <blockpin signalname="XLXN_310" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_18">
            <blockpin signalname="A14" name="I" />
            <blockpin signalname="XLXN_311" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_17">
            <blockpin signalname="A13" name="I" />
            <blockpin signalname="XLXN_312" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_175">
            <blockpin signalname="A3" name="I" />
            <blockpin signalname="XLXN_275" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_188">
            <blockpin signalname="A2_ISA" name="I" />
            <blockpin signalname="XLXN_348" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_189">
            <blockpin signalname="A1_ISA" name="I" />
            <blockpin signalname="XLXN_347" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_190">
            <blockpin signalname="A0_ISA" name="I" />
            <blockpin signalname="XLXN_346" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_111">
            <blockpin signalname="XLXN_326" name="I" />
            <blockpin signalname="S1" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_112">
            <blockpin signalname="XLXN_327" name="I" />
            <blockpin signalname="S2" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_113">
            <blockpin signalname="XLXN_328" name="I" />
            <blockpin signalname="S3" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_114">
            <blockpin signalname="XLXN_329" name="I" />
            <blockpin signalname="S4" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_115">
            <blockpin signalname="XLXN_330" name="I" />
            <blockpin signalname="S5" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_116">
            <blockpin signalname="XLXN_331" name="I" />
            <blockpin signalname="CS3FX" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_117">
            <blockpin signalname="XLXN_332" name="I" />
            <blockpin signalname="CS1FX" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_146">
            <blockpin signalname="XLXN_333" name="I" />
            <blockpin signalname="RESET" name="O" />
        </block>
        <block symbolname="IDE_DECODE" name="XLXI_229">
            <blockpin signalname="XLXN_346" name="iA0_ISA" />
            <blockpin signalname="XLXN_347" name="iA1_ISA" />
            <blockpin signalname="XLXN_348" name="iA2_ISA" />
            <blockpin signalname="XLXN_275" name="iA3" />
            <blockpin signalname="XLXN_315" name="iA4" />
            <blockpin signalname="XLXN_277" name="iA5" />
            <blockpin signalname="XLXN_316" name="iA6" />
            <blockpin signalname="XLXN_279" name="iA7" />
            <blockpin signalname="XLXN_317" name="iA8" />
            <blockpin signalname="XLXN_281" name="iA9" />
            <blockpin signalname="XLXN_318" name="iAEN" />
            <blockpin signalname="XLXN_332" name="iCS1FX" />
            <blockpin signalname="XLXN_331" name="iCS3FX" />
            <blockpin signalname="XLXN_349" name="iIOR_ISA" />
            <blockpin signalname="XLXN_350" name="iIOW_ISA" />
            <blockpin signalname="XLXN_285" name="iRESDRV" />
            <blockpin signalname="XLXN_333" name="iRESDRVn" />
            <blockpin signalname="XLXN_326" name="iS1" />
            <blockpin signalname="XLXN_327" name="iS2" />
            <blockpin signalname="XLXN_328" name="iS3" />
            <blockpin signalname="XLXN_329" name="iS4" />
            <blockpin signalname="XLXN_330" name="iS5" />
            <blockpin signalname="XLXN_323" name="iSW1" />
            <blockpin signalname="XLXN_322" name="iSW2" />
            <blockpin signalname="XLXN_321" name="iSW3" />
            <blockpin signalname="XLXN_320" name="iSW4" />
        </block>
        <block symbolname="ibuf" name="XLXI_228">
            <blockpin signalname="SW1" name="I" />
            <blockpin signalname="XLXN_323" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_227">
            <blockpin signalname="SW2" name="I" />
            <blockpin signalname="XLXN_322" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_221">
            <blockpin signalname="SW3" name="I" />
            <blockpin signalname="XLXN_321" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_222">
            <blockpin signalname="SW4" name="I" />
            <blockpin signalname="XLXN_320" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_223">
            <blockpin signalname="SW5" name="I" />
            <blockpin signalname="XLXN_305" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_224">
            <blockpin signalname="SW6" name="I" />
            <blockpin signalname="XLXN_304" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_225">
            <blockpin signalname="SW7" name="I" />
            <blockpin signalname="XLXN_303" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_226">
            <blockpin signalname="SW8" name="I" />
            <blockpin signalname="XLXN_302" name="O" />
        </block>
        <block symbolname="ROM_DECODE" name="XLXI_257">
            <blockpin signalname="XLXN_312" name="iA13" />
            <blockpin signalname="XLXN_311" name="iA14" />
            <blockpin signalname="XLXN_310" name="iA15" />
            <blockpin signalname="XLXN_309" name="iA16" />
            <blockpin signalname="XLXN_308" name="iA17" />
            <blockpin signalname="XLXN_307" name="iA18" />
            <blockpin signalname="XLXN_306" name="iA19" />
            <blockpin signalname="XLXN_318" name="iAEN" />
            <blockpin signalname="XLXN_325" name="iROM_EN" />
            <blockpin signalname="XLXN_305" name="iSW5" />
            <blockpin signalname="XLXN_304" name="iSW6" />
            <blockpin signalname="XLXN_303" name="iSW7" />
            <blockpin signalname="XLXN_302" name="iSW8" />
        </block>
        <block symbolname="obuf" name="XLXI_220">
            <blockpin signalname="XLXN_325" name="I" />
            <blockpin signalname="ROMEN" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_118">
            <blockpin signalname="XLXN_347" name="I" />
            <blockpin signalname="A2_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_121">
            <blockpin signalname="XLXN_349" name="I" />
            <blockpin signalname="IOR_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_145">
            <blockpin signalname="XLXN_350" name="I" />
            <blockpin signalname="IOW_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_119">
            <blockpin signalname="XLXN_346" name="I" />
            <blockpin signalname="A0_IDE" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_120">
            <blockpin signalname="XLXN_348" name="I" />
            <blockpin signalname="A1_IDE" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="5440" height="3520">
        <instance x="320" y="624" name="XLXI_130" orien="R0" />
        <instance x="320" y="240" name="XLXI_100" orien="R0" />
        <branch name="RESDRV">
            <wire x2="320" y1="208" y2="208" x1="288" />
        </branch>
        <branch name="IOW_ISA">
            <wire x2="320" y1="496" y2="496" x1="288" />
        </branch>
        <instance x="320" y="528" name="XLXI_97" orien="R0" />
        <branch name="IOR_ISA">
            <wire x2="320" y1="592" y2="592" x1="288" />
        </branch>
        <instance x="320" y="144" name="XLXI_144" orien="R0" />
        <branch name="AEN">
            <wire x2="320" y1="112" y2="112" x1="288" />
        </branch>
        <iomarker fontsize="28" x="288" y="208" name="RESDRV" orien="R180" />
        <iomarker fontsize="28" x="288" y="496" name="IOW_ISA" orien="R180" />
        <iomarker fontsize="28" x="288" y="592" name="IOR_ISA" orien="R180" />
        <iomarker fontsize="28" x="288" y="112" name="AEN" orien="R180" />
        <instance x="320" y="1264" name="XLXI_12" orien="R0" />
        <instance x="320" y="1360" name="XLXI_13" orien="R0" />
        <instance x="320" y="1456" name="XLXI_14" orien="R0" />
        <instance x="320" y="1552" name="XLXI_15" orien="R0" />
        <branch name="A4">
            <wire x2="320" y1="1136" y2="1136" x1="288" />
        </branch>
        <branch name="A5">
            <wire x2="320" y1="1232" y2="1232" x1="288" />
        </branch>
        <branch name="A6">
            <wire x2="320" y1="1328" y2="1328" x1="288" />
        </branch>
        <branch name="A7">
            <wire x2="320" y1="1424" y2="1424" x1="288" />
        </branch>
        <branch name="A8">
            <wire x2="320" y1="1520" y2="1520" x1="288" />
        </branch>
        <branch name="A9">
            <wire x2="320" y1="1616" y2="1616" x1="288" />
        </branch>
        <instance x="320" y="1168" name="XLXI_11" orien="R0" />
        <instance x="320" y="1648" name="XLXI_16" orien="R0" />
        <instance x="336" y="2512" name="XLXI_23" orien="R0" />
        <instance x="336" y="2400" name="XLXI_22" orien="R0" />
        <instance x="336" y="2288" name="XLXI_21" orien="R0" />
        <instance x="336" y="2176" name="XLXI_20" orien="R0" />
        <instance x="336" y="2064" name="XLXI_19" orien="R0" />
        <instance x="336" y="1968" name="XLXI_18" orien="R0" />
        <instance x="336" y="1856" name="XLXI_17" orien="R0" />
        <branch name="A18">
            <wire x2="336" y1="2368" y2="2368" x1="304" />
        </branch>
        <branch name="A17">
            <wire x2="336" y1="2256" y2="2256" x1="304" />
        </branch>
        <branch name="A16">
            <wire x2="336" y1="2144" y2="2144" x1="304" />
        </branch>
        <branch name="A15">
            <wire x2="336" y1="2032" y2="2032" x1="304" />
        </branch>
        <branch name="A14">
            <wire x2="336" y1="1936" y2="1936" x1="304" />
        </branch>
        <branch name="A13">
            <wire x2="336" y1="1824" y2="1824" x1="304" />
        </branch>
        <branch name="A19">
            <wire x2="336" y1="2480" y2="2480" x1="304" />
        </branch>
        <instance x="320" y="1072" name="XLXI_175" orien="R0" />
        <branch name="A3">
            <wire x2="320" y1="1040" y2="1040" x1="288" />
        </branch>
        <instance x="320" y="976" name="XLXI_188" orien="R0" />
        <instance x="320" y="880" name="XLXI_189" orien="R0" />
        <branch name="A0_ISA">
            <wire x2="320" y1="752" y2="752" x1="288" />
        </branch>
        <branch name="A1_ISA">
            <wire x2="320" y1="848" y2="848" x1="288" />
        </branch>
        <branch name="A2_ISA">
            <wire x2="320" y1="944" y2="944" x1="288" />
        </branch>
        <iomarker fontsize="28" x="288" y="1232" name="A5" orien="R180" />
        <iomarker fontsize="28" x="288" y="1328" name="A6" orien="R180" />
        <iomarker fontsize="28" x="288" y="1424" name="A7" orien="R180" />
        <iomarker fontsize="28" x="288" y="1520" name="A8" orien="R180" />
        <iomarker fontsize="28" x="288" y="1136" name="A4" orien="R180" />
        <iomarker fontsize="28" x="288" y="1616" name="A9" orien="R180" />
        <iomarker fontsize="28" x="304" y="1824" name="A13" orien="R180" />
        <iomarker fontsize="28" x="304" y="1936" name="A14" orien="R180" />
        <iomarker fontsize="28" x="304" y="2032" name="A15" orien="R180" />
        <iomarker fontsize="28" x="304" y="2144" name="A16" orien="R180" />
        <iomarker fontsize="28" x="304" y="2256" name="A17" orien="R180" />
        <iomarker fontsize="28" x="304" y="2368" name="A18" orien="R180" />
        <iomarker fontsize="28" x="304" y="2480" name="A19" orien="R180" />
        <iomarker fontsize="28" x="288" y="1040" name="A3" orien="R180" />
        <iomarker fontsize="28" x="288" y="848" name="A1_ISA" orien="R180" />
        <iomarker fontsize="28" x="288" y="944" name="A2_ISA" orien="R180" />
        <instance x="320" y="784" name="XLXI_190" orien="R0" />
        <iomarker fontsize="28" x="288" y="752" name="A0_ISA" orien="R180" />
        <instance x="2720" y="176" name="XLXI_111" orien="R0" />
        <instance x="2720" y="272" name="XLXI_112" orien="R0" />
        <instance x="2720" y="384" name="XLXI_113" orien="R0" />
        <instance x="2720" y="496" name="XLXI_114" orien="R0" />
        <instance x="2720" y="608" name="XLXI_115" orien="R0" />
        <instance x="2720" y="736" name="XLXI_116" orien="R0" />
        <branch name="S1">
            <wire x2="2976" y1="144" y2="144" x1="2944" />
        </branch>
        <branch name="S2">
            <wire x2="2976" y1="240" y2="240" x1="2944" />
        </branch>
        <branch name="S3">
            <wire x2="2976" y1="352" y2="352" x1="2944" />
        </branch>
        <branch name="S4">
            <wire x2="2976" y1="464" y2="464" x1="2944" />
        </branch>
        <branch name="S5">
            <wire x2="2976" y1="576" y2="576" x1="2944" />
        </branch>
        <branch name="CS3FX">
            <wire x2="2976" y1="704" y2="704" x1="2944" />
        </branch>
        <branch name="CS1FX">
            <wire x2="2976" y1="832" y2="832" x1="2944" />
        </branch>
        <instance x="2720" y="864" name="XLXI_117" orien="R0" />
        <iomarker fontsize="28" x="2976" y="144" name="S1" orien="R0" />
        <iomarker fontsize="28" x="2976" y="240" name="S2" orien="R0" />
        <iomarker fontsize="28" x="2976" y="352" name="S3" orien="R0" />
        <iomarker fontsize="28" x="2976" y="464" name="S4" orien="R0" />
        <iomarker fontsize="28" x="2976" y="576" name="S5" orien="R0" />
        <iomarker fontsize="28" x="2976" y="704" name="CS3FX" orien="R0" />
        <iomarker fontsize="28" x="2976" y="832" name="CS1FX" orien="R0" />
        <instance x="2720" y="976" name="XLXI_146" orien="R0" />
        <branch name="RESET">
            <wire x2="2976" y1="944" y2="944" x1="2944" />
        </branch>
        <iomarker fontsize="28" x="2976" y="944" name="RESET" orien="R0" />
        <instance x="1472" y="1248" name="XLXI_229" orien="R0">
        </instance>
        <branch name="XLXN_275">
            <wire x2="1184" y1="1040" y2="1040" x1="544" />
            <wire x2="1472" y1="320" y2="320" x1="1184" />
            <wire x2="1184" y1="320" y2="1040" x1="1184" />
        </branch>
        <branch name="XLXN_277">
            <wire x2="1248" y1="1232" y2="1232" x1="544" />
            <wire x2="1472" y1="448" y2="448" x1="1248" />
            <wire x2="1248" y1="448" y2="1232" x1="1248" />
        </branch>
        <branch name="XLXN_279">
            <wire x2="1056" y1="1424" y2="1424" x1="544" />
            <wire x2="1472" y1="576" y2="576" x1="1056" />
            <wire x2="1056" y1="576" y2="1424" x1="1056" />
        </branch>
        <branch name="XLXN_281">
            <wire x2="992" y1="1616" y2="1616" x1="544" />
            <wire x2="1472" y1="704" y2="704" x1="992" />
            <wire x2="992" y1="704" y2="1616" x1="992" />
        </branch>
        <branch name="XLXN_285">
            <wire x2="608" y1="208" y2="208" x1="544" />
            <wire x2="608" y1="208" y2="960" x1="608" />
            <wire x2="1472" y1="960" y2="960" x1="608" />
        </branch>
        <instance x="336" y="2624" name="XLXI_228" orien="R0" />
        <instance x="336" y="2736" name="XLXI_227" orien="R0" />
        <instance x="336" y="2832" name="XLXI_221" orien="R0" />
        <instance x="336" y="2944" name="XLXI_222" orien="R0" />
        <instance x="336" y="3056" name="XLXI_223" orien="R0" />
        <instance x="336" y="3152" name="XLXI_224" orien="R0" />
        <instance x="336" y="3248" name="XLXI_225" orien="R0" />
        <instance x="336" y="3344" name="XLXI_226" orien="R0" />
        <branch name="SW1">
            <wire x2="336" y1="2592" y2="2592" x1="304" />
        </branch>
        <iomarker fontsize="28" x="304" y="2592" name="SW1" orien="R180" />
        <branch name="SW2">
            <wire x2="336" y1="2704" y2="2704" x1="304" />
        </branch>
        <iomarker fontsize="28" x="304" y="2704" name="SW2" orien="R180" />
        <branch name="SW3">
            <wire x2="336" y1="2800" y2="2800" x1="304" />
        </branch>
        <iomarker fontsize="28" x="304" y="2800" name="SW3" orien="R180" />
        <branch name="SW4">
            <wire x2="336" y1="2912" y2="2912" x1="304" />
        </branch>
        <iomarker fontsize="28" x="304" y="2912" name="SW4" orien="R180" />
        <branch name="SW5">
            <wire x2="336" y1="3024" y2="3024" x1="304" />
        </branch>
        <iomarker fontsize="28" x="304" y="3024" name="SW5" orien="R180" />
        <branch name="SW6">
            <wire x2="336" y1="3120" y2="3120" x1="304" />
        </branch>
        <iomarker fontsize="28" x="304" y="3120" name="SW6" orien="R180" />
        <branch name="SW7">
            <wire x2="336" y1="3216" y2="3216" x1="304" />
        </branch>
        <iomarker fontsize="28" x="304" y="3216" name="SW7" orien="R180" />
        <branch name="SW8">
            <wire x2="336" y1="3312" y2="3312" x1="304" />
        </branch>
        <iomarker fontsize="28" x="304" y="3312" name="SW8" orien="R180" />
        <instance x="1456" y="3344" name="XLXI_257" orien="R0">
        </instance>
        <branch name="XLXN_302">
            <wire x2="1456" y1="3312" y2="3312" x1="560" />
        </branch>
        <branch name="XLXN_303">
            <wire x2="1456" y1="3216" y2="3216" x1="560" />
        </branch>
        <branch name="XLXN_304">
            <wire x2="1456" y1="3120" y2="3120" x1="560" />
        </branch>
        <branch name="XLXN_305">
            <wire x2="1456" y1="3024" y2="3024" x1="560" />
        </branch>
        <branch name="XLXN_306">
            <wire x2="1088" y1="2480" y2="2480" x1="560" />
            <wire x2="1088" y1="2480" y2="2832" x1="1088" />
            <wire x2="1456" y1="2832" y2="2832" x1="1088" />
        </branch>
        <branch name="XLXN_307">
            <wire x2="1120" y1="2368" y2="2368" x1="560" />
            <wire x2="1120" y1="2368" y2="2736" x1="1120" />
            <wire x2="1456" y1="2736" y2="2736" x1="1120" />
        </branch>
        <branch name="XLXN_308">
            <wire x2="1152" y1="2256" y2="2256" x1="560" />
            <wire x2="1152" y1="2256" y2="2640" x1="1152" />
            <wire x2="1456" y1="2640" y2="2640" x1="1152" />
        </branch>
        <branch name="XLXN_309">
            <wire x2="1184" y1="2144" y2="2144" x1="560" />
            <wire x2="1184" y1="2144" y2="2544" x1="1184" />
            <wire x2="1456" y1="2544" y2="2544" x1="1184" />
        </branch>
        <branch name="XLXN_310">
            <wire x2="1216" y1="2032" y2="2032" x1="560" />
            <wire x2="1216" y1="2032" y2="2448" x1="1216" />
            <wire x2="1456" y1="2448" y2="2448" x1="1216" />
        </branch>
        <branch name="XLXN_311">
            <wire x2="1248" y1="1936" y2="1936" x1="560" />
            <wire x2="1248" y1="1936" y2="2352" x1="1248" />
            <wire x2="1456" y1="2352" y2="2352" x1="1248" />
        </branch>
        <branch name="XLXN_312">
            <wire x2="1280" y1="1824" y2="1824" x1="560" />
            <wire x2="1280" y1="1824" y2="2256" x1="1280" />
            <wire x2="1456" y1="2256" y2="2256" x1="1280" />
        </branch>
        <branch name="XLXN_315">
            <wire x2="1152" y1="1136" y2="1136" x1="544" />
            <wire x2="1472" y1="384" y2="384" x1="1152" />
            <wire x2="1152" y1="384" y2="1136" x1="1152" />
        </branch>
        <branch name="XLXN_316">
            <wire x2="928" y1="1328" y2="1328" x1="544" />
            <wire x2="928" y1="512" y2="1328" x1="928" />
            <wire x2="1472" y1="512" y2="512" x1="928" />
        </branch>
        <branch name="XLXN_317">
            <wire x2="896" y1="1520" y2="1520" x1="544" />
            <wire x2="896" y1="640" y2="1520" x1="896" />
            <wire x2="1472" y1="640" y2="640" x1="896" />
        </branch>
        <branch name="XLXN_318">
            <wire x2="704" y1="112" y2="112" x1="544" />
            <wire x2="704" y1="112" y2="2928" x1="704" />
            <wire x2="1456" y1="2928" y2="2928" x1="704" />
            <wire x2="1216" y1="112" y2="112" x1="704" />
            <wire x2="1216" y1="112" y2="768" x1="1216" />
            <wire x2="1472" y1="768" y2="768" x1="1216" />
        </branch>
        <branch name="XLXN_320">
            <wire x2="1024" y1="2912" y2="2912" x1="560" />
            <wire x2="1024" y1="1216" y2="2912" x1="1024" />
            <wire x2="1472" y1="1216" y2="1216" x1="1024" />
        </branch>
        <branch name="XLXN_321">
            <wire x2="944" y1="2800" y2="2800" x1="560" />
            <wire x2="944" y1="1152" y2="2800" x1="944" />
            <wire x2="1472" y1="1152" y2="1152" x1="944" />
        </branch>
        <branch name="XLXN_322">
            <wire x2="640" y1="2704" y2="2704" x1="560" />
            <wire x2="640" y1="1088" y2="2704" x1="640" />
            <wire x2="1472" y1="1088" y2="1088" x1="640" />
        </branch>
        <branch name="XLXN_323">
            <wire x2="576" y1="2592" y2="2592" x1="560" />
            <wire x2="576" y1="1024" y2="2592" x1="576" />
            <wire x2="1472" y1="1024" y2="1024" x1="576" />
        </branch>
        <branch name="ROMEN">
            <wire x2="2992" y1="2256" y2="2256" x1="2960" />
        </branch>
        <instance x="2736" y="2288" name="XLXI_220" orien="R0" />
        <iomarker fontsize="28" x="2992" y="2256" name="ROMEN" orien="R0" />
        <branch name="XLXN_325">
            <wire x2="2736" y1="2256" y2="2256" x1="1840" />
        </branch>
        <branch name="XLXN_326">
            <wire x2="2176" y1="320" y2="320" x1="1856" />
            <wire x2="2176" y1="144" y2="320" x1="2176" />
            <wire x2="2720" y1="144" y2="144" x1="2176" />
        </branch>
        <branch name="XLXN_327">
            <wire x2="2208" y1="384" y2="384" x1="1856" />
            <wire x2="2208" y1="240" y2="384" x1="2208" />
            <wire x2="2720" y1="240" y2="240" x1="2208" />
        </branch>
        <branch name="XLXN_328">
            <wire x2="2240" y1="448" y2="448" x1="1856" />
            <wire x2="2240" y1="352" y2="448" x1="2240" />
            <wire x2="2720" y1="352" y2="352" x1="2240" />
        </branch>
        <branch name="XLXN_329">
            <wire x2="2272" y1="512" y2="512" x1="1856" />
            <wire x2="2272" y1="464" y2="512" x1="2272" />
            <wire x2="2720" y1="464" y2="464" x1="2272" />
        </branch>
        <branch name="XLXN_330">
            <wire x2="2720" y1="576" y2="576" x1="1856" />
        </branch>
        <branch name="XLXN_331">
            <wire x2="2144" y1="192" y2="192" x1="1856" />
            <wire x2="2144" y1="192" y2="704" x1="2144" />
            <wire x2="2720" y1="704" y2="704" x1="2144" />
        </branch>
        <branch name="XLXN_332">
            <wire x2="2112" y1="128" y2="128" x1="1856" />
            <wire x2="2112" y1="128" y2="832" x1="2112" />
            <wire x2="2720" y1="832" y2="832" x1="2112" />
        </branch>
        <branch name="XLXN_333">
            <wire x2="2080" y1="256" y2="256" x1="1856" />
            <wire x2="2080" y1="256" y2="944" x1="2080" />
            <wire x2="2720" y1="944" y2="944" x1="2080" />
        </branch>
        <instance x="2752" y="1504" name="XLXI_118" orien="R0" />
        <instance x="2752" y="1824" name="XLXI_121" orien="R0" />
        <branch name="A2_IDE">
            <wire x2="3008" y1="1472" y2="1472" x1="2976" />
        </branch>
        <branch name="IOR_IDE">
            <wire x2="3008" y1="1792" y2="1792" x1="2976" />
        </branch>
        <branch name="IOW_IDE">
            <wire x2="3008" y1="1904" y2="1904" x1="2976" />
        </branch>
        <instance x="2752" y="1936" name="XLXI_145" orien="R0" />
        <instance x="2752" y="1408" name="XLXI_119" orien="R0" />
        <branch name="A0_IDE">
            <wire x2="3008" y1="1376" y2="1376" x1="2976" />
        </branch>
        <instance x="2752" y="1616" name="XLXI_120" orien="R0" />
        <branch name="A1_IDE">
            <wire x2="3008" y1="1584" y2="1584" x1="2976" />
        </branch>
        <iomarker fontsize="28" x="3008" y="1472" name="A2_IDE" orien="R0" />
        <iomarker fontsize="28" x="3008" y="1792" name="IOR_IDE" orien="R0" />
        <iomarker fontsize="28" x="3008" y="1904" name="IOW_IDE" orien="R0" />
        <iomarker fontsize="28" x="3008" y="1376" name="A0_IDE" orien="R0" />
        <iomarker fontsize="28" x="3008" y="1584" name="A1_IDE" orien="R0" />
        <branch name="XLXN_346">
            <wire x2="800" y1="752" y2="752" x1="544" />
            <wire x2="800" y1="752" y2="1376" x1="800" />
            <wire x2="2752" y1="1376" y2="1376" x1="800" />
            <wire x2="1088" y1="752" y2="752" x1="800" />
            <wire x2="1472" y1="128" y2="128" x1="1088" />
            <wire x2="1088" y1="128" y2="752" x1="1088" />
        </branch>
        <branch name="XLXN_347">
            <wire x2="768" y1="848" y2="848" x1="544" />
            <wire x2="768" y1="848" y2="1472" x1="768" />
            <wire x2="2752" y1="1472" y2="1472" x1="768" />
            <wire x2="1120" y1="848" y2="848" x1="768" />
            <wire x2="1472" y1="192" y2="192" x1="1120" />
            <wire x2="1120" y1="192" y2="848" x1="1120" />
        </branch>
        <branch name="XLXN_348">
            <wire x2="736" y1="944" y2="944" x1="544" />
            <wire x2="736" y1="944" y2="1584" x1="736" />
            <wire x2="2752" y1="1584" y2="1584" x1="736" />
            <wire x2="1024" y1="944" y2="944" x1="736" />
            <wire x2="1472" y1="256" y2="256" x1="1024" />
            <wire x2="1024" y1="256" y2="944" x1="1024" />
        </branch>
        <branch name="XLXN_349">
            <wire x2="864" y1="592" y2="592" x1="544" />
            <wire x2="944" y1="592" y2="592" x1="864" />
            <wire x2="944" y1="592" y2="832" x1="944" />
            <wire x2="1472" y1="832" y2="832" x1="944" />
            <wire x2="864" y1="592" y2="1792" x1="864" />
            <wire x2="2752" y1="1792" y2="1792" x1="864" />
        </branch>
        <branch name="XLXN_350">
            <wire x2="832" y1="496" y2="496" x1="544" />
            <wire x2="832" y1="496" y2="1904" x1="832" />
            <wire x2="2752" y1="1904" y2="1904" x1="832" />
            <wire x2="1280" y1="496" y2="496" x1="832" />
            <wire x2="1280" y1="496" y2="896" x1="1280" />
            <wire x2="1472" y1="896" y2="896" x1="1280" />
        </branch>
    </sheet>
</drawing>