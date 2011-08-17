<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="iAEN" />
        <signal name="iS1" />
        <signal name="iA3" />
        <signal name="iS5" />
        <signal name="iS4" />
        <signal name="iS3" />
        <signal name="iCS3FX" />
        <signal name="iCS1FX" />
        <signal name="iIOW_ISA" />
        <signal name="iIOR_ISA" />
        <signal name="iA0_ISA" />
        <signal name="iA9" />
        <signal name="iA7" />
        <signal name="iA6" />
        <signal name="iA5" />
        <signal name="iA4" />
        <signal name="iSW1" />
        <signal name="iSW2" />
        <signal name="iSW3" />
        <signal name="iSW4" />
        <signal name="XLXN_138" />
        <signal name="iA8" />
        <signal name="XLXN_222" />
        <signal name="XLXN_226" />
        <signal name="XLXN_227" />
        <signal name="iRESDRV" />
        <signal name="iRESDRVn" />
        <signal name="iS2" />
        <signal name="XLXN_231" />
        <signal name="iA2_ISA" />
        <signal name="iA1_ISA" />
        <port polarity="Input" name="iAEN" />
        <port polarity="Output" name="iS1" />
        <port polarity="Input" name="iA3" />
        <port polarity="Output" name="iS5" />
        <port polarity="Output" name="iS4" />
        <port polarity="Output" name="iS3" />
        <port polarity="Output" name="iCS3FX" />
        <port polarity="Output" name="iCS1FX" />
        <port polarity="Input" name="iIOW_ISA" />
        <port polarity="Input" name="iIOR_ISA" />
        <port polarity="Input" name="iA0_ISA" />
        <port polarity="Input" name="iA9" />
        <port polarity="Input" name="iA7" />
        <port polarity="Input" name="iA6" />
        <port polarity="Input" name="iA5" />
        <port polarity="Input" name="iA4" />
        <port polarity="Input" name="iSW1" />
        <port polarity="Input" name="iSW2" />
        <port polarity="Input" name="iSW3" />
        <port polarity="Input" name="iSW4" />
        <port polarity="Input" name="iA8" />
        <port polarity="Input" name="iRESDRV" />
        <port polarity="Output" name="iRESDRVn" />
        <port polarity="Output" name="iS2" />
        <port polarity="Input" name="iA2_ISA" />
        <port polarity="Input" name="iA1_ISA" />
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
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="32" y1="-64" y2="-64" x1="96" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="64" />
        </blockdef>
        <blockdef name="x74_521">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <circle r="12" cx="332" cy="-640" />
            <line x2="344" y1="-640" y2="-640" x1="384" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-704" y2="-704" x1="0" />
            <line x2="64" y1="-832" y2="-832" x1="0" />
            <line x2="64" y1="-960" y2="-960" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-384" y2="-384" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-640" y2="-640" x1="0" />
            <line x2="64" y1="-768" y2="-768" x1="0" />
            <line x2="64" y1="-896" y2="-896" x1="0" />
            <line x2="64" y1="-1024" y2="-1024" x1="0" />
            <line x2="64" y1="-1152" y2="-1152" x1="0" />
            <line x2="64" y1="-1088" y2="-1088" x1="0" />
            <rect width="256" x="64" y="-1216" height="1152" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="x74_138">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-640" height="576" />
            <circle r="12" cx="332" cy="-128" />
            <line x2="344" y1="-128" y2="-128" x1="384" />
            <circle r="12" cx="332" cy="-192" />
            <line x2="344" y1="-192" y2="-192" x1="384" />
            <circle r="12" cx="332" cy="-256" />
            <line x2="344" y1="-256" y2="-256" x1="384" />
            <circle r="12" cx="332" cy="-320" />
            <line x2="344" y1="-320" y2="-320" x1="384" />
            <circle r="12" cx="332" cy="-384" />
            <line x2="344" y1="-384" y2="-384" x1="384" />
            <circle r="12" cx="332" cy="-448" />
            <line x2="344" y1="-448" y2="-448" x1="384" />
            <circle r="12" cx="332" cy="-512" />
            <line x2="344" y1="-512" y2="-512" x1="384" />
            <circle r="12" cx="332" cy="-576" />
            <line x2="344" y1="-576" y2="-576" x1="384" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <circle r="12" cx="52" cy="-256" />
            <line x2="40" y1="-256" y2="-256" x1="0" />
            <circle r="12" cx="52" cy="-192" />
            <line x2="40" y1="-192" y2="-192" x1="0" />
        </blockdef>
        <block symbolname="gnd" name="XLXI_35">
            <blockpin signalname="XLXN_226" name="G" />
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
        <block symbolname="inv" name="XLXI_10">
            <blockpin signalname="iA3" name="I" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_126">
            <blockpin signalname="XLXN_222" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_127">
            <blockpin signalname="XLXN_227" name="G" />
        </block>
        <block symbolname="inv" name="XLXI_8">
            <blockpin signalname="XLXN_138" name="I" />
            <blockpin signalname="iS3" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="iRESDRV" name="I" />
            <blockpin signalname="iRESDRVn" name="O" />
        </block>
        <block symbolname="x74_521" name="XLXI_135">
            <blockpin signalname="iAEN" name="G" />
            <blockpin signalname="iA9" name="P0" />
            <blockpin signalname="iA8" name="P1" />
            <blockpin signalname="iA7" name="P2" />
            <blockpin signalname="iA6" name="P3" />
            <blockpin signalname="iA5" name="P4" />
            <blockpin signalname="iA4" name="P5" />
            <blockpin signalname="XLXN_226" name="P6" />
            <blockpin signalname="XLXN_226" name="P7" />
            <blockpin signalname="XLXN_222" name="Q0" />
            <blockpin signalname="iSW1" name="Q1" />
            <blockpin signalname="iSW2" name="Q2" />
            <blockpin signalname="iSW3" name="Q3" />
            <blockpin signalname="iSW4" name="Q4" />
            <blockpin signalname="XLXN_227" name="Q5" />
            <blockpin signalname="XLXN_227" name="Q6" />
            <blockpin signalname="XLXN_227" name="Q7" />
            <blockpin signalname="iS1" name="PEQ" />
        </block>
        <block symbolname="x74_138" name="XLXI_136">
            <blockpin signalname="iIOW_ISA" name="A" />
            <blockpin signalname="iIOR_ISA" name="B" />
            <blockpin signalname="iA3" name="C" />
            <blockpin signalname="XLXN_231" name="G1" />
            <blockpin signalname="iS1" name="G2A" />
            <blockpin signalname="iA0_ISA" name="G2B" />
            <blockpin name="Y0" />
            <blockpin signalname="XLXN_1" name="Y1" />
            <blockpin signalname="iS2" name="Y2" />
            <blockpin name="Y3" />
            <blockpin name="Y4" />
            <blockpin signalname="iS4" name="Y5" />
            <blockpin signalname="XLXN_138" name="Y6" />
            <blockpin name="Y7" />
        </block>
        <block symbolname="nor2" name="XLXI_4">
            <blockpin signalname="iA1_ISA" name="I0" />
            <blockpin signalname="iA2_ISA" name="I1" />
            <blockpin signalname="XLXN_231" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3801" height="2688">
        <attr value="CM" name="LengthUnitName" />
        <attr value="4" name="GridsPerUnit" />
        <instance x="2288" y="736" name="XLXI_5" orien="R0" />
        <instance x="2288" y="1040" name="XLXI_6" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="3184" y1="1168" y2="1168" x1="3152" />
        </branch>
        <instance x="3184" y="1200" name="XLXI_7" orien="R0" />
        <branch name="XLXN_2">
            <wire x2="2288" y1="672" y2="672" x1="2256" />
        </branch>
        <instance x="2032" y="704" name="XLXI_10" orien="R0" />
        <branch name="iS1">
            <wire x2="1680" y1="896" y2="896" x1="1344" />
            <wire x2="1936" y1="896" y2="896" x1="1680" />
            <wire x2="1936" y1="896" y2="976" x1="1936" />
            <wire x2="2288" y1="976" y2="976" x1="1936" />
            <wire x2="1936" y1="976" y2="1424" x1="1936" />
            <wire x2="2768" y1="1424" y2="1424" x1="1936" />
            <wire x2="1888" y1="336" y2="336" x1="1680" />
            <wire x2="1680" y1="336" y2="896" x1="1680" />
            <wire x2="2288" y1="608" y2="608" x1="1936" />
            <wire x2="1936" y1="608" y2="896" x1="1936" />
        </branch>
        <branch name="iS5">
            <wire x2="3616" y1="1168" y2="1168" x1="3408" />
        </branch>
        <branch name="iS4">
            <wire x2="3616" y1="1424" y2="1424" x1="3152" />
        </branch>
        <branch name="iS3">
            <wire x2="3616" y1="1488" y2="1488" x1="3408" />
        </branch>
        <branch name="iCS3FX">
            <wire x2="2768" y1="640" y2="640" x1="2544" />
        </branch>
        <branch name="iCS1FX">
            <wire x2="2768" y1="944" y2="944" x1="2544" />
        </branch>
        <branch name="iIOW_ISA">
            <wire x2="2768" y1="1104" y2="1104" x1="2512" />
        </branch>
        <branch name="iIOR_ISA">
            <wire x2="2768" y1="1168" y2="1168" x1="2512" />
        </branch>
        <branch name="iA0_ISA">
            <wire x2="2768" y1="1488" y2="1488" x1="2080" />
        </branch>
        <branch name="iA6">
            <wire x2="960" y1="768" y2="768" x1="464" />
        </branch>
        <branch name="iA5">
            <wire x2="960" y1="896" y2="896" x1="464" />
        </branch>
        <branch name="iA4">
            <wire x2="960" y1="1024" y2="1024" x1="464" />
        </branch>
        <branch name="iSW1">
            <wire x2="960" y1="576" y2="576" x1="288" />
        </branch>
        <branch name="iSW2">
            <wire x2="960" y1="704" y2="704" x1="288" />
        </branch>
        <branch name="iSW3">
            <wire x2="960" y1="832" y2="832" x1="288" />
        </branch>
        <branch name="iSW4">
            <wire x2="960" y1="960" y2="960" x1="288" />
        </branch>
        <branch name="XLXN_138">
            <wire x2="3184" y1="1488" y2="1488" x1="3152" />
        </branch>
        <instance x="3184" y="1520" name="XLXI_8" orien="R0" />
        <iomarker fontsize="28" x="2512" y="1168" name="iIOR_ISA" orien="R180" />
        <iomarker fontsize="28" x="2512" y="1104" name="iIOW_ISA" orien="R180" />
        <iomarker fontsize="28" x="3616" y="1488" name="iS3" orien="R0" />
        <iomarker fontsize="28" x="3616" y="1424" name="iS4" orien="R0" />
        <iomarker fontsize="28" x="3616" y="1232" name="iS2" orien="R0" />
        <iomarker fontsize="28" x="2768" y="640" name="iCS3FX" orien="R0" />
        <iomarker fontsize="28" x="2768" y="944" name="iCS1FX" orien="R0" />
        <iomarker fontsize="28" x="3616" y="1168" name="iS5" orien="R0" />
        <iomarker fontsize="28" x="1824" y="672" name="iA3" orien="R180" />
        <iomarker fontsize="28" x="1888" y="336" name="iS1" orien="R0" />
        <branch name="iA9">
            <wire x2="960" y1="384" y2="384" x1="464" />
        </branch>
        <branch name="iA8">
            <wire x2="960" y1="512" y2="512" x1="464" />
        </branch>
        <branch name="iA7">
            <wire x2="960" y1="640" y2="640" x1="464" />
        </branch>
        <branch name="XLXN_222">
            <wire x2="192" y1="400" y2="448" x1="192" />
            <wire x2="960" y1="448" y2="448" x1="192" />
        </branch>
        <branch name="iA3">
            <wire x2="2016" y1="672" y2="672" x1="1824" />
            <wire x2="2016" y1="672" y2="912" x1="2016" />
            <wire x2="2288" y1="912" y2="912" x1="2016" />
            <wire x2="2016" y1="912" y2="1232" x1="2016" />
            <wire x2="2768" y1="1232" y2="1232" x1="2016" />
            <wire x2="2032" y1="672" y2="672" x1="2016" />
        </branch>
        <instance x="2688" y="2384" name="XLXI_9" orien="R0" />
        <branch name="iRESDRV">
            <wire x2="2688" y1="2352" y2="2352" x1="2544" />
        </branch>
        <branch name="iRESDRVn">
            <wire x2="3088" y1="2352" y2="2352" x1="2912" />
        </branch>
        <iomarker fontsize="28" x="2544" y="2352" name="iRESDRV" orien="R180" />
        <iomarker fontsize="28" x="352" y="1792" name="iAEN" orien="R180" />
        <branch name="iAEN">
            <wire x2="704" y1="1792" y2="1792" x1="352" />
            <wire x2="960" y1="1408" y2="1408" x1="704" />
            <wire x2="704" y1="1408" y2="1792" x1="704" />
        </branch>
        <instance x="960" y="1536" name="XLXI_135" orien="R0" />
        <branch name="XLXN_226">
            <wire x2="960" y1="1152" y2="1152" x1="400" />
            <wire x2="400" y1="1152" y2="1280" x1="400" />
            <wire x2="960" y1="1280" y2="1280" x1="400" />
            <wire x2="400" y1="1280" y2="1376" x1="400" />
        </branch>
        <branch name="iS2">
            <wire x2="3616" y1="1232" y2="1232" x1="3152" />
        </branch>
        <instance x="336" y="1504" name="XLXI_35" orien="R0" />
        <branch name="XLXN_227">
            <wire x2="192" y1="1088" y2="1216" x1="192" />
            <wire x2="960" y1="1216" y2="1216" x1="192" />
            <wire x2="192" y1="1216" y2="1344" x1="192" />
            <wire x2="960" y1="1344" y2="1344" x1="192" />
            <wire x2="192" y1="1344" y2="1376" x1="192" />
            <wire x2="960" y1="1088" y2="1088" x1="192" />
        </branch>
        <instance x="128" y="1504" name="XLXI_127" orien="R0" />
        <iomarker fontsize="28" x="464" y="1024" name="iA4" orien="R180" />
        <iomarker fontsize="28" x="288" y="960" name="iSW4" orien="R180" />
        <iomarker fontsize="28" x="464" y="896" name="iA5" orien="R180" />
        <iomarker fontsize="28" x="288" y="832" name="iSW3" orien="R180" />
        <iomarker fontsize="28" x="464" y="768" name="iA6" orien="R180" />
        <iomarker fontsize="28" x="288" y="704" name="iSW2" orien="R180" />
        <iomarker fontsize="28" x="288" y="576" name="iSW1" orien="R180" />
        <iomarker fontsize="28" x="464" y="640" name="iA7" orien="R180" />
        <iomarker fontsize="28" x="464" y="512" name="iA8" orien="R180" />
        <iomarker fontsize="28" x="464" y="384" name="iA9" orien="R180" />
        <instance x="128" y="400" name="XLXI_126" orien="R0" />
        <instance x="2768" y="1680" name="XLXI_136" orien="R0" />
        <branch name="XLXN_231">
            <wire x2="2592" y1="1584" y2="1584" x1="2416" />
            <wire x2="2592" y1="1552" y2="1584" x1="2592" />
            <wire x2="2768" y1="1552" y2="1552" x1="2592" />
        </branch>
        <iomarker fontsize="28" x="2080" y="1488" name="iA0_ISA" orien="R180" />
        <branch name="iA2_ISA">
            <wire x2="2160" y1="1552" y2="1552" x1="2080" />
        </branch>
        <branch name="iA1_ISA">
            <wire x2="2160" y1="1616" y2="1616" x1="2080" />
        </branch>
        <instance x="2160" y="1680" name="XLXI_4" orien="R0" />
        <iomarker fontsize="28" x="2080" y="1616" name="iA1_ISA" orien="R180" />
        <iomarker fontsize="28" x="2080" y="1552" name="iA2_ISA" orien="R180" />
        <iomarker fontsize="28" x="3088" y="2352" name="iRESDRVn" orien="R0" />
    </sheet>
</drawing>