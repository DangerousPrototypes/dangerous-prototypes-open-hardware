<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="iA19" />
        <signal name="iA18" />
        <signal name="iA17" />
        <signal name="iA16" />
        <signal name="iA15" />
        <signal name="iA14" />
        <signal name="iSW5" />
        <signal name="iSW6" />
        <signal name="iSW7" />
        <signal name="iA13" />
        <signal name="iSW8" />
        <signal name="iROM_CS" />
        <signal name="XLXN_222" />
        <signal name="XLXN_229" />
        <signal name="XLXN_231" />
        <signal name="iROM_EN" />
        <port polarity="Input" name="iA19" />
        <port polarity="Input" name="iA18" />
        <port polarity="Input" name="iA17" />
        <port polarity="Input" name="iA16" />
        <port polarity="Input" name="iA15" />
        <port polarity="Input" name="iA14" />
        <port polarity="Input" name="iSW5" />
        <port polarity="Input" name="iSW6" />
        <port polarity="Input" name="iSW7" />
        <port polarity="Input" name="iA13" />
        <port polarity="Input" name="iSW8" />
        <port polarity="Output" name="iROM_CS" />
        <port polarity="Input" name="iROM_EN" />
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
        <block symbolname="x74_521" name="XLXI_132">
            <blockpin signalname="iROM_EN" name="G" />
            <blockpin signalname="iA19" name="P0" />
            <blockpin signalname="iA18" name="P1" />
            <blockpin signalname="iA17" name="P2" />
            <blockpin signalname="iA16" name="P3" />
            <blockpin signalname="iA15" name="P4" />
            <blockpin signalname="iA14" name="P5" />
            <blockpin signalname="iA13" name="P6" />
            <blockpin signalname="XLXN_229" name="P7" />
            <blockpin signalname="XLXN_222" name="Q0" />
            <blockpin signalname="XLXN_222" name="Q1" />
            <blockpin signalname="iSW5" name="Q2" />
            <blockpin signalname="iSW6" name="Q3" />
            <blockpin signalname="iSW7" name="Q4" />
            <blockpin signalname="iSW8" name="Q5" />
            <blockpin signalname="XLXN_231" name="Q6" />
            <blockpin signalname="XLXN_231" name="Q7" />
            <blockpin signalname="iROM_CS" name="PEQ" />
        </block>
        <block symbolname="gnd" name="XLXI_133">
            <blockpin signalname="XLXN_229" name="G" />
        </block>
        <block symbolname="gnd" name="XLXI_134">
            <blockpin signalname="XLXN_231" name="G" />
        </block>
        <block symbolname="vcc" name="XLXI_135">
            <blockpin signalname="XLXN_222" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="2688" height="1900">
        <attr value="CM" name="LengthUnitName" />
        <attr value="4" name="GridsPerUnit" />
        <branch name="iA19">
            <wire x2="1424" y1="304" y2="304" x1="944" />
        </branch>
        <branch name="iA18">
            <wire x2="1424" y1="432" y2="432" x1="944" />
        </branch>
        <branch name="iA17">
            <wire x2="1424" y1="560" y2="560" x1="944" />
        </branch>
        <branch name="iA16">
            <wire x2="1424" y1="688" y2="688" x1="944" />
        </branch>
        <branch name="iA15">
            <wire x2="1424" y1="816" y2="816" x1="944" />
        </branch>
        <branch name="iA14">
            <wire x2="1424" y1="944" y2="944" x1="944" />
        </branch>
        <branch name="iSW5">
            <wire x2="1424" y1="624" y2="624" x1="752" />
        </branch>
        <branch name="iSW6">
            <wire x2="1424" y1="752" y2="752" x1="752" />
        </branch>
        <branch name="iSW7">
            <wire x2="1424" y1="880" y2="880" x1="752" />
        </branch>
        <branch name="iA13">
            <wire x2="1424" y1="1072" y2="1072" x1="944" />
        </branch>
        <branch name="iSW8">
            <wire x2="1424" y1="1008" y2="1008" x1="752" />
        </branch>
        <branch name="iROM_CS">
            <wire x2="1824" y1="816" y2="816" x1="1808" />
            <wire x2="1920" y1="816" y2="816" x1="1824" />
        </branch>
        <branch name="XLXN_222">
            <wire x2="656" y1="320" y2="368" x1="656" />
            <wire x2="1424" y1="368" y2="368" x1="656" />
            <wire x2="656" y1="368" y2="496" x1="656" />
            <wire x2="1424" y1="496" y2="496" x1="656" />
        </branch>
        <instance x="1424" y="1456" name="XLXI_132" orien="R0" />
        <instance x="800" y="1424" name="XLXI_133" orien="R0" />
        <instance x="592" y="1424" name="XLXI_134" orien="R0" />
        <instance x="592" y="320" name="XLXI_135" orien="R0" />
        <branch name="XLXN_229">
            <wire x2="1424" y1="1200" y2="1200" x1="864" />
            <wire x2="864" y1="1200" y2="1296" x1="864" />
        </branch>
        <branch name="XLXN_231">
            <wire x2="1424" y1="1136" y2="1136" x1="656" />
            <wire x2="656" y1="1136" y2="1264" x1="656" />
            <wire x2="1424" y1="1264" y2="1264" x1="656" />
            <wire x2="656" y1="1264" y2="1296" x1="656" />
        </branch>
        <branch name="iROM_EN">
            <wire x2="1152" y1="1712" y2="1712" x1="800" />
            <wire x2="1152" y1="1328" y2="1712" x1="1152" />
            <wire x2="1424" y1="1328" y2="1328" x1="1152" />
        </branch>
        <iomarker fontsize="28" x="944" y="304" name="iA19" orien="R180" />
        <iomarker fontsize="28" x="944" y="432" name="iA18" orien="R180" />
        <iomarker fontsize="28" x="944" y="560" name="iA17" orien="R180" />
        <iomarker fontsize="28" x="944" y="816" name="iA15" orien="R180" />
        <iomarker fontsize="28" x="944" y="688" name="iA16" orien="R180" />
        <iomarker fontsize="28" x="944" y="944" name="iA14" orien="R180" />
        <iomarker fontsize="28" x="944" y="1072" name="iA13" orien="R180" />
        <iomarker fontsize="28" x="752" y="1008" name="iSW8" orien="R180" />
        <iomarker fontsize="28" x="752" y="880" name="iSW7" orien="R180" />
        <iomarker fontsize="28" x="752" y="752" name="iSW6" orien="R180" />
        <iomarker fontsize="28" x="752" y="624" name="iSW5" orien="R180" />
        <iomarker fontsize="28" x="800" y="1712" name="iROM_EN" orien="R180" />
        <iomarker fontsize="28" x="1920" y="816" name="iROM_CS" orien="R0" />
    </sheet>
</drawing>