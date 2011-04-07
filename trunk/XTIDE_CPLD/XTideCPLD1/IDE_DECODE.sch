<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_36(7:0)" />
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
        <signal name="XLXN_135(7:0)" />
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
        <block symbolname="comp8" name="XLXI_1">
            <blockpin signalname="XLXN_36(7:0)" name="A(7:0)" />
            <blockpin signalname="XLXN_135(7:0)" name="B(7:0)" />
            <blockpin signalname="XLXN_113" name="EQ" />
        </block>
        <block symbolname="gnd" name="XLXI_35">
            <blockpin signalname="XLXN_61" name="G" />
        </block>
        <block symbolname="d3_8e" name="XLXI_3">
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
            <blockpin name="D6" />
            <blockpin name="D7" />
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
            <blockpin name="I" />
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
    </netlist>
    <sheet sheetnum="1" width="3801" height="2688">
        <attr value="CM" name="LengthUnitName" />
        <attr value="4" name="GridsPerUnit" />
        <branch name="XLXN_36(7:0)">
            <wire x2="364" y1="344" y2="360" x1="364" />
            <wire x2="364" y1="360" y2="424" x1="364" />
            <wire x2="364" y1="424" y2="456" x1="364" />
            <wire x2="364" y1="456" y2="488" x1="364" />
            <wire x2="364" y1="488" y2="552" x1="364" />
            <wire x2="364" y1="552" y2="616" x1="364" />
            <wire x2="364" y1="616" y2="648" x1="364" />
            <wire x2="364" y1="648" y2="680" x1="364" />
            <wire x2="364" y1="680" y2="744" x1="364" />
            <wire x2="364" y1="744" y2="808" x1="364" />
            <wire x2="364" y1="808" y2="1032" x1="364" />
            <wire x2="604" y1="1032" y2="1032" x1="364" />
        </branch>
        <instance x="604" y="1352" name="XLXI_1" orien="R0" />
        <branch name="XLXN_61">
            <wire x2="236" y1="744" y2="744" x1="204" />
            <wire x2="204" y1="744" y2="808" x1="204" />
            <wire x2="204" y1="808" y2="888" x1="204" />
            <wire x2="236" y1="808" y2="808" x1="204" />
        </branch>
        <instance x="140" y="1016" name="XLXI_35" orien="R0" />
        <bustap x2="236" y1="744" y2="744" x1="364" />
        <bustap x2="236" y1="808" y2="808" x1="364" />
        <instance x="2764" y="1944" name="XLXI_3" orien="R0" />
        <instance x="2284" y="1000" name="XLXI_5" orien="R0" />
        <instance x="2284" y="1304" name="XLXI_6" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="3180" y1="1432" y2="1432" x1="3148" />
        </branch>
        <instance x="3180" y="1464" name="XLXI_7" orien="R0" />
        <instance x="3164" y="1784" name="XLXI_8" orien="R0" />
        <branch name="XLXN_2">
            <wire x2="2284" y1="936" y2="936" x1="2252" />
        </branch>
        <instance x="2028" y="968" name="XLXI_10" orien="R0" />
        <instance x="1100" y="1256" name="XLXI_123" orien="R0" />
        <instance x="2492" y="1944" name="XLXI_124" orien="R0" />
        <branch name="XLXN_111">
            <wire x2="2764" y1="1816" y2="1816" x1="2748" />
        </branch>
        <branch name="XLXN_112">
            <wire x2="2492" y1="1752" y2="1752" x1="1740" />
        </branch>
        <instance x="1484" y="1848" name="XLXI_4" orien="R0" />
        <branch name="XLXN_113">
            <wire x2="1100" y1="1128" y2="1128" x1="988" />
        </branch>
        <branch name="iAEN">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="732" y="1496" type="branch" />
            <wire x2="732" y1="1496" y2="1496" x1="684" />
            <wire x2="1036" y1="1496" y2="1496" x1="732" />
            <wire x2="1100" y1="1192" y2="1192" x1="1036" />
            <wire x2="1036" y1="1192" y2="1496" x1="1036" />
        </branch>
        <branch name="iA2_ISA">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="1324" y="1720" type="branch" />
            <wire x2="1324" y1="1720" y2="1720" x1="1260" />
            <wire x2="1484" y1="1720" y2="1720" x1="1324" />
        </branch>
        <branch name="iA1_ISA">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="1324" y="1784" type="branch" />
            <wire x2="1324" y1="1784" y2="1784" x1="1260" />
            <wire x2="1484" y1="1784" y2="1784" x1="1324" />
        </branch>
        <branch name="iS1">
            <wire x2="1420" y1="1160" y2="1160" x1="1356" />
            <wire x2="1932" y1="1160" y2="1160" x1="1420" />
            <wire x2="1932" y1="1160" y2="1240" x1="1932" />
            <wire x2="1932" y1="1240" y2="1880" x1="1932" />
            <wire x2="2492" y1="1880" y2="1880" x1="1932" />
            <wire x2="2284" y1="1240" y2="1240" x1="1932" />
            <wire x2="1420" y1="600" y2="1160" x1="1420" />
            <wire x2="1708" y1="600" y2="600" x1="1420" />
            <wire x2="2284" y1="872" y2="872" x1="1932" />
            <wire x2="1932" y1="872" y2="1160" x1="1932" />
        </branch>
        <branch name="iA3">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="1676" y="936" type="branch" />
            <wire x2="1676" y1="936" y2="936" x1="1628" />
            <wire x2="2012" y1="936" y2="936" x1="1676" />
            <wire x2="2012" y1="936" y2="1176" x1="2012" />
            <wire x2="2284" y1="1176" y2="1176" x1="2012" />
            <wire x2="2028" y1="936" y2="936" x1="2012" />
        </branch>
        <branch name="iS5">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="3484" y="1432" type="branch" />
            <wire x2="3484" y1="1432" y2="1432" x1="3404" />
            <wire x2="3612" y1="1432" y2="1432" x1="3484" />
        </branch>
        <branch name="iS2">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="3484" y="1496" type="branch" />
            <wire x2="3484" y1="1496" y2="1496" x1="3148" />
            <wire x2="3612" y1="1496" y2="1496" x1="3484" />
        </branch>
        <branch name="iS4">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="3468" y="1688" type="branch" />
            <wire x2="3468" y1="1688" y2="1688" x1="3148" />
            <wire x2="3612" y1="1688" y2="1688" x1="3468" />
        </branch>
        <branch name="iS3">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="3468" y="1752" type="branch" />
            <wire x2="3468" y1="1752" y2="1752" x1="3388" />
            <wire x2="3612" y1="1752" y2="1752" x1="3468" />
        </branch>
        <branch name="iCS3FX">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2668" y="904" type="branch" />
            <wire x2="2668" y1="904" y2="904" x1="2540" />
            <wire x2="2764" y1="904" y2="904" x1="2668" />
        </branch>
        <branch name="iCS1FX">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2652" y="1208" type="branch" />
            <wire x2="2652" y1="1208" y2="1208" x1="2540" />
            <wire x2="2764" y1="1208" y2="1208" x1="2652" />
        </branch>
        <branch name="iIOW_ISA">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2636" y="1368" type="branch" />
            <wire x2="2636" y1="1368" y2="1368" x1="2508" />
            <wire x2="2764" y1="1368" y2="1368" x1="2636" />
        </branch>
        <branch name="iIOR_ISA">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2636" y="1432" type="branch" />
            <wire x2="2636" y1="1432" y2="1432" x1="2508" />
            <wire x2="2764" y1="1432" y2="1432" x1="2636" />
        </branch>
        <branch name="iA3">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2604" y="1496" type="branch" />
            <wire x2="2604" y1="1496" y2="1496" x1="2508" />
            <wire x2="2764" y1="1496" y2="1496" x1="2604" />
        </branch>
        <branch name="iA0_ISA">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2284" y="1816" type="branch" />
            <wire x2="2284" y1="1816" y2="1816" x1="2220" />
            <wire x2="2492" y1="1816" y2="1816" x1="2284" />
        </branch>
        <instance x="2892" y="2376" name="XLXI_9" orien="R0" />
        <branch name="iRESDRV">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2780" y="2344" type="branch" />
            <wire x2="2780" y1="2344" y2="2344" x1="2748" />
            <wire x2="2892" y1="2344" y2="2344" x1="2780" />
        </branch>
        <branch name="iRESDRVn">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="3180" y="2344" type="branch" />
            <wire x2="3180" y1="2344" y2="2344" x1="3116" />
            <wire x2="3292" y1="2344" y2="2344" x1="3180" />
        </branch>
        <bustap x2="284" y1="1272" y2="1272" x1="380" />
        <bustap x2="284" y1="1336" y2="1336" x1="380" />
        <bustap x2="284" y1="1400" y2="1400" x1="380" />
        <bustap x2="284" y1="1464" y2="1464" x1="380" />
        <bustap x2="284" y1="1528" y2="1528" x1="380" />
        <bustap x2="284" y1="1592" y2="1592" x1="380" />
        <bustap x2="284" y1="1656" y2="1656" x1="380" />
        <bustap x2="284" y1="1720" y2="1720" x1="380" />
        <branch name="XLXN_135(7:0)">
            <wire x2="604" y1="1224" y2="1224" x1="380" />
            <wire x2="380" y1="1224" y2="1272" x1="380" />
            <wire x2="380" y1="1272" y2="1336" x1="380" />
            <wire x2="380" y1="1336" y2="1384" x1="380" />
            <wire x2="380" y1="1384" y2="1400" x1="380" />
            <wire x2="380" y1="1400" y2="1464" x1="380" />
            <wire x2="380" y1="1464" y2="1480" x1="380" />
            <wire x2="380" y1="1480" y2="1528" x1="380" />
            <wire x2="380" y1="1528" y2="1560" x1="380" />
            <wire x2="380" y1="1560" y2="1592" x1="380" />
            <wire x2="380" y1="1592" y2="1624" x1="380" />
            <wire x2="380" y1="1624" y2="1656" x1="380" />
            <wire x2="380" y1="1656" y2="1688" x1="380" />
            <wire x2="380" y1="1688" y2="1720" x1="380" />
            <wire x2="380" y1="1720" y2="1752" x1="380" />
        </branch>
        <instance x="140" y="1256" name="XLXI_126" orien="R0" />
        <branch name="XLXN_136">
            <wire x2="204" y1="1256" y2="1272" x1="204" />
            <wire x2="284" y1="1272" y2="1272" x1="204" />
        </branch>
        <instance x="140" y="1880" name="XLXI_127" orien="R0" />
        <branch name="XLXN_137">
            <wire x2="284" y1="1592" y2="1592" x1="204" />
            <wire x2="204" y1="1592" y2="1656" x1="204" />
            <wire x2="284" y1="1656" y2="1656" x1="204" />
            <wire x2="204" y1="1656" y2="1720" x1="204" />
            <wire x2="204" y1="1720" y2="1752" x1="204" />
            <wire x2="284" y1="1720" y2="1720" x1="204" />
        </branch>
        <bustap x2="268" y1="680" y2="680" x1="364" />
        <bustap x2="268" y1="616" y2="616" x1="364" />
        <bustap x2="268" y1="552" y2="552" x1="364" />
        <bustap x2="268" y1="488" y2="488" x1="364" />
        <bustap x2="268" y1="424" y2="424" x1="364" />
        <bustap x2="268" y1="360" y2="360" x1="364" />
        <branch name="iA9">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="204" y="360" type="branch" />
            <wire x2="204" y1="360" y2="360" x1="156" />
            <wire x2="268" y1="360" y2="360" x1="204" />
        </branch>
        <branch name="iA8">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="204" y="424" type="branch" />
            <wire x2="204" y1="424" y2="424" x1="156" />
            <wire x2="268" y1="424" y2="424" x1="204" />
        </branch>
        <branch name="iA7">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="204" y="488" type="branch" />
            <wire x2="204" y1="488" y2="488" x1="156" />
            <wire x2="268" y1="488" y2="488" x1="204" />
        </branch>
        <branch name="iA6">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="204" y="552" type="branch" />
            <wire x2="204" y1="552" y2="552" x1="156" />
            <wire x2="268" y1="552" y2="552" x1="204" />
        </branch>
        <branch name="iA5">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="204" y="616" type="branch" />
            <wire x2="204" y1="616" y2="616" x1="156" />
            <wire x2="268" y1="616" y2="616" x1="204" />
        </branch>
        <branch name="iA4">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="204" y="680" type="branch" />
            <wire x2="204" y1="680" y2="680" x1="156" />
            <wire x2="268" y1="680" y2="680" x1="204" />
        </branch>
        <branch name="iSW1">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="220" y="1336" type="branch" />
            <wire x2="220" y1="1336" y2="1336" x1="172" />
            <wire x2="284" y1="1336" y2="1336" x1="220" />
        </branch>
        <branch name="iSW2">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="220" y="1400" type="branch" />
            <wire x2="220" y1="1400" y2="1400" x1="172" />
            <wire x2="284" y1="1400" y2="1400" x1="220" />
        </branch>
        <branch name="iSW3">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="220" y="1464" type="branch" />
            <wire x2="220" y1="1464" y2="1464" x1="172" />
            <wire x2="284" y1="1464" y2="1464" x1="220" />
        </branch>
        <branch name="iSW4">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="220" y="1528" type="branch" />
            <wire x2="220" y1="1528" y2="1528" x1="172" />
            <wire x2="284" y1="1528" y2="1528" x1="220" />
        </branch>
        <iomarker fontsize="28" x="156" y="360" name="iA9" orien="R180" />
        <iomarker fontsize="28" x="156" y="424" name="iA8" orien="R180" />
        <iomarker fontsize="28" x="156" y="488" name="iA7" orien="R180" />
        <iomarker fontsize="28" x="156" y="552" name="iA6" orien="R180" />
        <iomarker fontsize="28" x="156" y="616" name="iA5" orien="R180" />
        <iomarker fontsize="28" x="156" y="680" name="iA4" orien="R180" />
        <iomarker fontsize="28" x="172" y="1336" name="iSW1" orien="R180" />
        <iomarker fontsize="28" x="172" y="1400" name="iSW2" orien="R180" />
        <iomarker fontsize="28" x="172" y="1464" name="iSW3" orien="R180" />
        <iomarker fontsize="28" x="172" y="1528" name="iSW4" orien="R180" />
        <iomarker fontsize="28" x="1260" y="1720" name="iA2_ISA" orien="R180" />
        <iomarker fontsize="28" x="1260" y="1784" name="iA1_ISA" orien="R180" />
        <iomarker fontsize="28" x="2220" y="1816" name="iA0_ISA" orien="R180" />
        <iomarker fontsize="28" x="2508" y="1432" name="iIOR_ISA" orien="R180" />
        <iomarker fontsize="28" x="2508" y="1368" name="iIOW_ISA" orien="R180" />
        <iomarker fontsize="28" x="3612" y="1752" name="iS3" orien="R0" />
        <iomarker fontsize="28" x="3612" y="1688" name="iS4" orien="R0" />
        <iomarker fontsize="28" x="3612" y="1496" name="iS2" orien="R0" />
        <iomarker fontsize="28" x="1628" y="936" name="iA3" orien="R180" />
        <iomarker fontsize="28" x="2764" y="904" name="iCS3FX" orien="R0" />
        <iomarker fontsize="28" x="2764" y="1208" name="iCS1FX" orien="R0" />
        <iomarker fontsize="28" x="2748" y="2344" name="iRESDRV" orien="R180" />
        <iomarker fontsize="28" x="3292" y="2344" name="iRESDRVn" orien="R0" />
        <iomarker fontsize="28" x="3612" y="1432" name="iS5" orien="R0" />
        <iomarker fontsize="28" x="1708" y="600" name="iS1" orien="R0" />
        <iomarker fontsize="28" x="684" y="1496" name="iAEN" orien="R180" />
    </sheet>
</drawing>