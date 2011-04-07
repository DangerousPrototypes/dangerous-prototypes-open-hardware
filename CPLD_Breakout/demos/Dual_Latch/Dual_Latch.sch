<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xbr" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1(7:0)" />
        <signal name="XLXN_2(7:0)" />
        <signal name="XLXN_3(7:0)" />
        <signal name="XLXN_5(7:0)" />
        <signal name="XLXN_6(7:0)" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="Addr" />
        <signal name="Write" />
        <signal name="XLXN_13(7:0)" />
        <port polarity="Input" name="XLXN_1(7:0)" />
        <port polarity="Output" name="XLXN_2(7:0)" />
        <port polarity="Output" name="XLXN_3(7:0)" />
        <port polarity="Input" name="Addr" />
        <port polarity="Input" name="Write" />
        <blockdef name="ld8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <rect width="64" x="320" y="-268" height="24" />
            <rect width="64" x="0" y="-268" height="24" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="ibuf8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="96" x="128" y="-44" height="24" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <blockdef name="and2b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="and2b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
        </blockdef>
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <blockdef name="obuf8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <rect width="64" x="0" y="-44" height="24" />
            <rect width="96" x="128" y="-44" height="24" />
        </blockdef>
        <block symbolname="ibuf8" name="XLXI_9">
            <blockpin signalname="XLXN_1(7:0)" name="I(7:0)" />
            <blockpin signalname="XLXN_13(7:0)" name="O(7:0)" />
        </block>
        <block symbolname="ld8" name="XLXI_3">
            <blockpin signalname="XLXN_13(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_7" name="G" />
            <blockpin signalname="XLXN_5(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="ld8" name="XLXI_4">
            <blockpin signalname="XLXN_13(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_8" name="G" />
            <blockpin signalname="XLXN_6(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="and2b2" name="XLXI_12">
            <blockpin signalname="XLXN_9" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_13">
            <blockpin signalname="XLXN_9" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_14">
            <blockpin signalname="Write" name="I" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_15">
            <blockpin signalname="Addr" name="I" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="obuf8" name="XLXI_16">
            <blockpin signalname="XLXN_5(7:0)" name="I(7:0)" />
            <blockpin signalname="XLXN_2(7:0)" name="O(7:0)" />
        </block>
        <block symbolname="obuf8" name="XLXI_17">
            <blockpin signalname="XLXN_6(7:0)" name="I(7:0)" />
            <blockpin signalname="XLXN_3(7:0)" name="O(7:0)" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="2688" height="1900">
        <attr value="CM" name="LengthUnitName" />
        <attr value="4" name="GridsPerUnit" />
        <instance x="512" y="1056" name="XLXI_9" orien="R0" />
        <branch name="XLXN_1(7:0)">
            <wire x2="512" y1="1024" y2="1024" x1="480" />
        </branch>
        <instance x="1344" y="928" name="XLXI_3" orien="R0" />
        <instance x="1344" y="1328" name="XLXI_4" orien="R0" />
        <branch name="XLXN_2(7:0)">
            <wire x2="2096" y1="672" y2="672" x1="2064" />
        </branch>
        <branch name="XLXN_3(7:0)">
            <wire x2="2112" y1="1072" y2="1072" x1="2080" />
        </branch>
        <branch name="XLXN_5(7:0)">
            <wire x2="1777" y1="672" y2="672" x1="1728" />
            <wire x2="1840" y1="672" y2="672" x1="1777" />
        </branch>
        <branch name="XLXN_6(7:0)">
            <wire x2="1744" y1="1072" y2="1072" x1="1728" />
            <wire x2="1856" y1="1072" y2="1072" x1="1744" />
        </branch>
        <instance x="880" y="896" name="XLXI_12" orien="R0" />
        <instance x="880" y="1296" name="XLXI_13" orien="R0" />
        <branch name="XLXN_7">
            <wire x2="1344" y1="800" y2="800" x1="1136" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="1344" y1="1200" y2="1200" x1="1136" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="816" y1="1232" y2="1232" x1="736" />
            <wire x2="880" y1="1232" y2="1232" x1="816" />
            <wire x2="816" y1="832" y2="1232" x1="816" />
            <wire x2="880" y1="832" y2="832" x1="816" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="784" y1="768" y2="768" x1="736" />
            <wire x2="784" y1="768" y2="1168" x1="784" />
            <wire x2="880" y1="1168" y2="1168" x1="784" />
            <wire x2="880" y1="768" y2="768" x1="784" />
        </branch>
        <instance x="512" y="1264" name="XLXI_14" orien="R0" />
        <instance x="512" y="800" name="XLXI_15" orien="R0" />
        <branch name="Addr">
            <wire x2="512" y1="768" y2="768" x1="480" />
        </branch>
        <branch name="Write">
            <wire x2="512" y1="1232" y2="1232" x1="480" />
        </branch>
        <branch name="XLXN_13(7:0)">
            <wire x2="1280" y1="1024" y2="1024" x1="736" />
            <wire x2="1280" y1="1024" y2="1072" x1="1280" />
            <wire x2="1344" y1="1072" y2="1072" x1="1280" />
            <wire x2="1280" y1="672" y2="1024" x1="1280" />
            <wire x2="1344" y1="672" y2="672" x1="1280" />
        </branch>
        <instance x="1840" y="704" name="XLXI_16" orien="R0" />
        <instance x="1856" y="1104" name="XLXI_17" orien="R0" />
        <iomarker fontsize="28" x="480" y="1024" name="XLXN_1(7:0)" orien="R180" />
        <iomarker fontsize="28" x="2096" y="672" name="XLXN_2(7:0)" orien="R0" />
        <iomarker fontsize="28" x="2112" y="1072" name="XLXN_3(7:0)" orien="R0" />
        <iomarker fontsize="28" x="480" y="768" name="Addr" orien="R180" />
        <iomarker fontsize="28" x="480" y="1232" name="Write" orien="R180" />
    </sheet>
</drawing>