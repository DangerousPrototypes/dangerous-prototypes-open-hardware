<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="iA9,iA8,iA7,iA6,iA5,iA4,XLXN_61,XLXN_61" />
        <signal name="XLXN_61" />
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_111" />
        <signal name="XLXN_112" />
        <signal name="XLXN_113" />
        <signal name="iAEN" />
        <signal name="iA2_ISA" />
        <signal name="iA1_ISA" />
        <signal name="iS1" />
        <signal name="iA3" />
        <signal name="iS5" />
        <signal name="iS2" />
        <signal name="iS4" />
        <signal name="iS3" />
        <signal name="iCS3FX" />
        <signal name="iCS1FX" />
        <signal name="iIOW_ISA" />
        <signal name="iIOR_ISA" />
        <signal name="iA0_ISA" />
        <signal name="iRESDRV" />
        <signal name="iRESDRVn" />
        <signal name="XLXN_136,iSW1,iSW2,iSW3,iSW4,XLXN_137,XLXN_137,XLXN_137" />
        <signal name="XLXN_136" />
        <signal name="XLXN_137" />
        <signal name="iA9" />
        <signal name="iA8" />
        <signal name="iA7" />
        <signal name="iA6" />
        <signal name="iA5" />
        <signal name="iA4" />
        <signal name="iSW1" />
        <signal name="iSW2" />
        <signal name="iSW3" />
        <signal name="iSW4" />
        <signal name="XLXN_138" />
        <port polarity="Input" name="iAEN" />
        <port polarity="Input" name="iA2_ISA" />
        <port polarity="Input" name="iA1_ISA" />
        <port polarity="Output" name="iS1" />
        <port polarity="Input" name="iA3" />
        <port polarity="Output" name="iS5" />
        <port polarity="Output" name="iS2" />
        <port polarity="Output" name="iS4" />
        <port polarity="Output" name="iS3" />
        <port polarity="Output" name="iCS3FX" />
        <port polarity="Output" name="iCS1FX" />
        <port polarity="Input" name="iIOW_ISA" />
        <port polarity="Input" name="iIOR_ISA" />
        <port polarity="Input" name="iA0_ISA" />
        <port polarity="Input" name="iRESDRV" />
        <port polarity="Output" name="iRESDRVn" />
        <port polarity="Input" name="iA9" />
        <port polarity="Input" name="iA8" />
        <port polarity="Input" name="iA7" />
        <port polarity="Input" name="iA6" />
        <port polarity="Input" name="iA5" />
        <port polarity="Input" name="iA4" />
        <port polarity="Input" name="iSW1" />
        <port polarity="Input" name="iSW2" />
        <port polarity="Input" name="iSW3" />
        <port polarity="Input" name="iSW4" />
        <blockdef name="nor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
        </blockdef>
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-96" x1="64" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="64" y1="-64" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="or3b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="28" y1="-64" y2="-64" x1="0" />
            <circle r="10" cx="38" cy="-62" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="60" cy="-128" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-128" y2="-128" x1="40" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="32" y1="-64" y2="-64" x1="96" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="64" />
        </blockdef>
        <blockdef name="comp8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-384" height="320" />
            <line x2="320" y1="-224" y2="-224" x1="384" />
            <rect width="64" x="0" y="-332" height="24" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <rect width="64" x="0" y="-140" height="24" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="d3_8e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-320" y2="-320" x1="384" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <rect width="256" x="64" y="-640" height="576" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <block symbolname="gnd" name="XLXI_35">
            <blockpin signalname="XLXN_61" name="G" />
        </block>
        <block symbolname="or2" name="XLXI_5">
            <blockpin signalname="XLXN_2" name="I0" />
            <blockpin signalname="iS1" name="I1" />
            <blockpin signalname="iCS3FX" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_6">
            <blockpin signalname="iS1" name="I0" />
            <blockpin signalname="iA3" name="I1" />
            <blockpin signalname="iCS1FX" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_7">
            <blockpin signalname="XLXN_1" name="I" />
            <blockpin signalname="iS5" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_8">
            <blockpin signalname="XLXN_138" name="I" />
            <blockpin signalname="iS3" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_10">
            <blockpin signalname="iA3" name="I" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_123">
            <blockpin signalname="iAEN" name="I0" />
            <blockpin signalname="XLXN_113" name="I1" />
            <blockpin signalname="iS1" name="O" />
        </block>
        <block symbolname="or3b2" name="XLXI_124">
            <blockpin signalname="iS1" name="I0" />
            <blockpin signalname="iA0_ISA" name="I1" />
            <blockpin signalname="XLXN_112" name="I2" />
            <blockpin signalname="XLXN_111" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_4">
            <blockpin signalname="iA1_ISA" name="I0" />
            <blockpin signalname="iA2_ISA" name="I1" />
            <blockpin signalname="XLXN_112" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="iRESDRV" name="I" />
            <blockpin signalname="iRESDRVn" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_126">
            <blockpin signalname="XLXN_136" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_127">
            <blockpin signalname="XLXN_137" name="G" />
        </block>
        <block symbolname="comp8" name="XLXI_128">
            <blockpin signalname="iA9,iA8,iA7,iA6,iA5,iA4,XLXN_61,XLXN_61" name="A(7:0)" />
            <blockpin signalname="XLXN_136,iSW1,iSW2,iSW3,iSW4,XLXN_137,XLXN_137,XLXN_137" name="B(7:0)" />
            <blockpin signalname="XLXN_113" name="EQ" />
        </block>
        <block symbolname="d3_8e" name="XLXI_129">
            <blockpin signalname="iIOW_ISA" name="A0" />
            <blockpin signalname="iIOR_ISA" name="A1" />
            <blockpin signalname="iA3" name="A2" />
            <blockpin signalname="XLXN_111" name="E" />
            <blockpin name="D0" />
            <blockpin signalname="XLXN_1" name="D1" />
            <blockpin signalname="iS2" name="D2" />
            <blockpin name="D3" />
            <blockpin name="D4" />
            <blockpin signalname="iS4" name="D5" />
            <blockpin signalname="XLXN_138" name="D6" />
            <blockpin name="D7" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3801" height="2688">
        <attr value="CM" name="LengthUnitName" />
        <attr value="4" name="GridsPerUnit" />
        <branch name="iA9,iA8,iA7,iA6,iA5,iA4,XLXN_61,XLXN_61">
            <wire x2="368" y1="352" y2="368" x1="368" />
            <wire x2="368" y1="368" y2="432" x1="368" />
            <wire x2="368" y1="432" y2="496" x1="368" />
            <wire x2="368" y1="496" y2="560" x1="368" />
            <wire x2="368" y1="560" y2="624" x1="368" />
            <wire x2="368" y1="624" y2="688" x1="368" />
            <wire x2="368" y1="688" y2="752" x1="368" />
            <wire x2="368" y1="752" y2="816" x1="368" />
            <wire x2="368" y1="816" y2="1040" x1="368" />
            <wire x2="464" y1="1040" y2="1040" x1="368" />
            <wire x2="608" y1="1040" y2="1040" x1="464" />
        </branch>
        <branch name="XLXN_61">
            <wire x2="240" y1="752" y2="752" x1="208" />
            <wire x2="208" y1="752" y2="816" x1="208" />
            <wire x2="208" y1="816" y2="896" x1="208" />
            <wire x2="240" y1="816" y2="816" x1="208" />
        </branch>
        <instance x="144" y="1024" name="XLXI_35" orien="R0" />
        <bustap x2="240" y1="752" y2="752" x1="368" />
        <bustap x2="240" y1="816" y2="816" x1="368" />
        <instance x="2288" y="1008" name="XLXI_5" orien="R0" />
        <instance x="2288" y="1312" name="XLXI_6" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="3184" y1="1440" y2="1440" x1="3152" />
        </branch>
        <instance x="3184" y="1472" name="XLXI_7" orien="R0" />
        <branch name="XLXN_2">
            <wire x2="2288" y1="944" y2="944" x1="2256" />
        </branch>
        <instance x="2032" y="976" name="XLXI_10" orien="R0" />
        <instance x="1104" y="1264" name="XLXI_123" orien="R0" />
        <instance x="2496" y="1952" name="XLXI_124" orien="R0" />
        <branch name="XLXN_111">
            <wire x2="2768" y1="1824" y2="1824" x1="2752" />
        </branch>
        <branch name="XLXN_112">
            <wire x2="2496" y1="1760" y2="1760" x1="1744" />
        </branch>
        <instance x="1488" y="1856" name="XLXI_4" orien="R0" />
        <branch name="XLXN_113">
            <wire x2="1104" y1="1136" y2="1136" x1="992" />
        </branch>
        <branch name="iAEN">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="732" y="1496" type="branch" />
            <wire x2="736" y1="1504" y2="1504" x1="688" />
            <wire x2="1040" y1="1504" y2="1504" x1="736" />
            <wire x2="1104" y1="1200" y2="1200" x1="1040" />
            <wire x2="1040" y1="1200" y2="1504" x1="1040" />
        </branch>
        <branch name="iA2_ISA">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="1324" y="1720" type="branch" />
            <wire x2="1328" y1="1728" y2="1728" x1="1264" />
            <wire x2="1488" y1="1728" y2="1728" x1="1328" />
        </branch>
        <branch name="iA1_ISA">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="1324" y="1784" type="branch" />
            <wire x2="1328" y1="1792" y2="1792" x1="1264" />
            <wire x2="1488" y1="1792" y2="1792" x1="1328" />
        </branch>
        <branch name="iS1">
            <wire x2="1424" y1="1168" y2="1168" x1="1360" />
            <wire x2="1936" y1="1168" y2="1168" x1="1424" />
            <wire x2="1936" y1="1168" y2="1248" x1="1936" />
            <wire x2="1936" y1="1248" y2="1888" x1="1936" />
            <wire x2="2496" y1="1888" y2="1888" x1="1936" />
            <wire x2="2288" y1="1248" y2="1248" x1="1936" />
            <wire x2="1424" y1="608" y2="1168" x1="1424" />
            <wire x2="1712" y1="608" y2="608" x1="1424" />
            <wire x2="2288" y1="880" y2="880" x1="1936" />
            <wire x2="1936" y1="880" y2="1168" x1="1936" />
        </branch>
        <branch name="iA3">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="1676" y="936" type="branch" />
            <wire x2="1680" y1="944" y2="944" x1="1632" />
            <wire x2="2016" y1="944" y2="944" x1="1680" />
            <wire x2="2016" y1="944" y2="1184" x1="2016" />
            <wire x2="2288" y1="1184" y2="1184" x1="2016" />
            <wire x2="2032" y1="944" y2="944" x1="2016" />
        </branch>
        <branch name="iS5">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="3484" y="1432" type="branch" />
            <wire x2="3488" y1="1440" y2="1440" x1="3408" />
            <wire x2="3616" y1="1440" y2="1440" x1="3488" />
        </branch>
        <branch name="iS2">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="3484" y="1496" type="branch" />
            <wire x2="3488" y1="1504" y2="1504" x1="3152" />
            <wire x2="3616" y1="1504" y2="1504" x1="3488" />
        </branch>
        <branch name="iS4">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="3468" y="1688" type="branch" />
            <wire x2="3472" y1="1696" y2="1696" x1="3152" />
            <wire x2="3616" y1="1696" y2="1696" x1="3472" />
        </branch>
        <branch name="iS3">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="3468" y="1752" type="branch" />
            <wire x2="3616" y1="1760" y2="1760" x1="3408" />
        </branch>
        <branch name="iCS3FX">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="2668" y="904" type="branch" />
            <wire x2="2672" y1="912" y2="912" x1="2544" />
            <wire x2="2768" y1="912" y2="912" x1="2672" />
        </branch>
        <branch name="iCS1FX">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="2652" y="1208" type="branch" />
            <wire x2="2656" y1="1216" y2="1216" x1="2544" />
            <wire x2="2768" y1="1216" y2="1216" x1="2656" />
        </branch>
        <branch name="iIOW_ISA">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="2636" y="1368" type="branch" />
            <wire x2="2640" y1="1376" y2="1376" x1="2512" />
            <wire x2="2768" y1="1376" y2="1376" x1="2640" />
        </branch>
        <branch name="iIOR_ISA">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="2636" y="1432" type="branch" />
            <wire x2="2640" y1="1440" y2="1440" x1="2512" />
            <wire x2="2768" y1="1440" y2="1440" x1="2640" />
        </branch>
        <branch name="iA3">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="2604" y="1496" type="branch" />
            <wire x2="2608" y1="1504" y2="1504" x1="2512" />
            <wire x2="2768" y1="1504" y2="1504" x1="2608" />
        </branch>
        <branch name="iA0_ISA">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="2284" y="1816" type="branch" />
            <wire x2="2288" y1="1824" y2="1824" x1="2224" />
            <wire x2="2496" y1="1824" y2="1824" x1="2288" />
        </branch>
        <instance x="2896" y="2384" name="XLXI_9" orien="R0" />
        <branch name="iRESDRV">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="2780" y="2344" type="branch" />
            <wire x2="2784" y1="2352" y2="2352" x1="2752" />
            <wire x2="2896" y1="2352" y2="2352" x1="2784" />
        </branch>
        <branch name="iRESDRVn">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="3180" y="2344" type="branch" />
            <wire x2="3184" y1="2352" y2="2352" x1="3120" />
            <wire x2="3296" y1="2352" y2="2352" x1="3184" />
        </branch>
        <bustap x2="288" y1="1280" y2="1280" x1="384" />
        <bustap x2="288" y1="1344" y2="1344" x1="384" />
        <bustap x2="288" y1="1408" y2="1408" x1="384" />
        <bustap x2="288" y1="1472" y2="1472" x1="384" />
        <bustap x2="288" y1="1536" y2="1536" x1="384" />
        <bustap x2="288" y1="1600" y2="1600" x1="384" />
        <bustap x2="288" y1="1664" y2="1664" x1="384" />
        <bustap x2="288" y1="1728" y2="1728" x1="384" />
        <branch name="XLXN_136,iSW1,iSW2,iSW3,iSW4,XLXN_137,XLXN_137,XLXN_137">
            <wire x2="384" y1="1232" y2="1280" x1="384" />
            <wire x2="384" y1="1280" y2="1344" x1="384" />
            <wire x2="384" y1="1344" y2="1408" x1="384" />
            <wire x2="384" y1="1408" y2="1472" x1="384" />
            <wire x2="384" y1="1472" y2="1536" x1="384" />
            <wire x2="384" y1="1536" y2="1600" x1="384" />
            <wire x2="384" y1="1600" y2="1664" x1="384" />
            <wire x2="384" y1="1664" y2="1728" x1="384" />
            <wire x2="384" y1="1728" y2="1760" x1="384" />
            <wire x2="432" y1="1232" y2="1232" x1="384" />
            <wire x2="480" y1="1232" y2="1232" x1="432" />
            <wire x2="496" y1="1232" y2="1232" x1="480" />
            <wire x2="608" y1="1232" y2="1232" x1="496" />
        </branch>
        <instance x="144" y="1264" name="XLXI_126" orien="R0" />
        <branch name="XLXN_136">
            <wire x2="208" y1="1264" y2="1280" x1="208" />
            <wire x2="288" y1="1280" y2="1280" x1="208" />
        </branch>
        <instance x="144" y="1888" name="XLXI_127" orien="R0" />
        <branch name="XLXN_137">
            <wire x2="288" y1="1600" y2="1600" x1="208" />
            <wire x2="208" y1="1600" y2="1664" x1="208" />
            <wire x2="288" y1="1664" y2="1664" x1="208" />
            <wire x2="208" y1="1664" y2="1728" x1="208" />
            <wire x2="208" y1="1728" y2="1760" x1="208" />
            <wire x2="288" y1="1728" y2="1728" x1="208" />
        </branch>
        <bustap x2="272" y1="688" y2="688" x1="368" />
        <bustap x2="272" y1="624" y2="624" x1="368" />
        <bustap x2="272" y1="560" y2="560" x1="368" />
        <bustap x2="272" y1="496" y2="496" x1="368" />
        <bustap x2="272" y1="432" y2="432" x1="368" />
        <bustap x2="272" y1="368" y2="368" x1="368" />
        <branch name="iA9">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="204" y="360" type="branch" />
            <wire x2="208" y1="368" y2="368" x1="160" />
            <wire x2="272" y1="368" y2="368" x1="208" />
        </branch>
        <branch name="iA8">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="204" y="424" type="branch" />
            <wire x2="208" y1="432" y2="432" x1="160" />
            <wire x2="272" y1="432" y2="432" x1="208" />
        </branch>
        <branch name="iA7">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="204" y="488" type="branch" />
            <wire x2="208" y1="496" y2="496" x1="160" />
            <wire x2="272" y1="496" y2="496" x1="208" />
        </branch>
        <branch name="iA6">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="204" y="552" type="branch" />
            <wire x2="208" y1="560" y2="560" x1="160" />
            <wire x2="272" y1="560" y2="560" x1="208" />
        </branch>
        <branch name="iA5">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="204" y="616" type="branch" />
            <wire x2="208" y1="624" y2="624" x1="160" />
            <wire x2="272" y1="624" y2="624" x1="208" />
        </branch>
        <branch name="iA4">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="204" y="680" type="branch" />
            <wire x2="208" y1="688" y2="688" x1="160" />
            <wire x2="272" y1="688" y2="688" x1="208" />
        </branch>
        <branch name="iSW1">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="220" y="1336" type="branch" />
            <wire x2="224" y1="1344" y2="1344" x1="176" />
            <wire x2="288" y1="1344" y2="1344" x1="224" />
        </branch>
        <branch name="iSW2">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="220" y="1400" type="branch" />
            <wire x2="224" y1="1408" y2="1408" x1="176" />
            <wire x2="288" y1="1408" y2="1408" x1="224" />
        </branch>
        <branch name="iSW3">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="220" y="1464" type="branch" />
            <wire x2="224" y1="1472" y2="1472" x1="176" />
            <wire x2="288" y1="1472" y2="1472" x1="224" />
        </branch>
        <branch name="iSW4">
            <attrtext style="alignment:SOFT-LEFT" attrname="Name" x="220" y="1528" type="branch" />
            <wire x2="224" y1="1536" y2="1536" x1="176" />
            <wire x2="288" y1="1536" y2="1536" x1="224" />
        </branch>
        <iomarker fontsize="28" x="160" y="368" name="iA9" orien="R180" />
        <iomarker fontsize="28" x="160" y="432" name="iA8" orien="R180" />
        <iomarker fontsize="28" x="160" y="496" name="iA7" orien="R180" />
        <iomarker fontsize="28" x="160" y="560" name="iA6" orien="R180" />
        <iomarker fontsize="28" x="160" y="624" name="iA5" orien="R180" />
        <iomarker fontsize="28" x="160" y="688" name="iA4" orien="R180" />
        <iomarker fontsize="28" x="176" y="1344" name="iSW1" orien="R180" />
        <iomarker fontsize="28" x="176" y="1408" name="iSW2" orien="R180" />
        <iomarker fontsize="28" x="176" y="1472" name="iSW3" orien="R180" />
        <iomarker fontsize="28" x="176" y="1536" name="iSW4" orien="R180" />
        <iomarker fontsize="28" x="1264" y="1728" name="iA2_ISA" orien="R180" />
        <iomarker fontsize="28" x="1264" y="1792" name="iA1_ISA" orien="R180" />
        <iomarker fontsize="28" x="2224" y="1824" name="iA0_ISA" orien="R180" />
        <iomarker fontsize="28" x="2512" y="1440" name="iIOR_ISA" orien="R180" />
        <iomarker fontsize="28" x="2512" y="1376" name="iIOW_ISA" orien="R180" />
        <iomarker fontsize="28" x="3616" y="1760" name="iS3" orien="R0" />
        <iomarker fontsize="28" x="3616" y="1696" name="iS4" orien="R0" />
        <iomarker fontsize="28" x="3616" y="1504" name="iS2" orien="R0" />
        <iomarker fontsize="28" x="1632" y="944" name="iA3" orien="R180" />
        <iomarker fontsize="28" x="2768" y="912" name="iCS3FX" orien="R0" />
        <iomarker fontsize="28" x="2768" y="1216" name="iCS1FX" orien="R0" />
        <iomarker fontsize="28" x="2752" y="2352" name="iRESDRV" orien="R180" />
        <iomarker fontsize="28" x="3296" y="2352" name="iRESDRVn" orien="R0" />
        <iomarker fontsize="28" x="3616" y="1440" name="iS5" orien="R0" />
        <iomarker fontsize="28" x="1712" y="608" name="iS1" orien="R0" />
        <iomarker fontsize="28" x="688" y="1504" name="iAEN" orien="R180" />
        <instance x="608" y="1360" name="XLXI_128" orien="R0" />
        <instance x="2768" y="1952" name="XLXI_129" orien="R0" />
        <branch name="XLXN_138">
            <wire x2="3184" y1="1760" y2="1760" x1="3152" />
        </branch>
        <instance x="3184" y="1792" name="XLXI_8" orien="R0" />
    </sheet>
</drawing>