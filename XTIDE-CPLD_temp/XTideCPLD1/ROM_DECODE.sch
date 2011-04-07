<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_36(7:0)" />
        <signal name="XLXN_113" />
        <signal name="XLXN_144" />
        <signal name="iAEN" />
        <signal name="XLXN_135(7:0)" />
        <signal name="XLXN_136" />
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
        <signal name="XLXN_139" />
        <signal name="XLXN_140" />
        <signal name="iSW8" />
        <signal name="iROM_EN" />
        <port polarity="Input" name="iAEN" />
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
        <port polarity="Output" name="iROM_EN" />
        <blockdef name="comp8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-384" height="320" />
            <line x2="320" y1="-224" y2="-224" x1="384" />
            <rect width="64" x="0" y="-332" height="24" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <rect width="64" x="0" y="-140" height="24" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
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
        <block symbolname="comp8" name="XLXI_1">
            <blockpin signalname="XLXN_36(7:0)" name="A(7:0)" />
            <blockpin signalname="XLXN_135(7:0)" name="B(7:0)" />
            <blockpin signalname="XLXN_113" name="EQ" />
        </block>
        <block symbolname="gnd" name="XLXI_35">
            <blockpin signalname="XLXN_139" name="G" />
        </block>
        <block symbolname="vcc" name="XLXI_126">
            <blockpin signalname="XLXN_136" name="P" />
        </block>
        <block symbolname="or2" name="XLXI_123">
            <blockpin signalname="iAEN" name="I0" />
            <blockpin signalname="XLXN_113" name="I1" />
            <blockpin signalname="iROM_EN" name="O" />
        </block>
        <block symbolname="gnd" name="XLXI_127">
            <blockpin signalname="XLXN_140" name="G" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="2688" height="1900">
        <attr value="CM" name="LengthUnitName" />
        <attr value="4" name="GridsPerUnit" />
        <branch name="XLXN_36(7:0)">
            <wire x2="903" y1="164" y2="180" x1="903" />
            <wire x2="903" y1="180" y2="244" x1="903" />
            <wire x2="903" y1="244" y2="308" x1="903" />
            <wire x2="903" y1="308" y2="372" x1="903" />
            <wire x2="903" y1="372" y2="436" x1="903" />
            <wire x2="903" y1="436" y2="500" x1="903" />
            <wire x2="903" y1="500" y2="564" x1="903" />
            <wire x2="903" y1="564" y2="628" x1="903" />
            <wire x2="903" y1="628" y2="852" x1="903" />
            <wire x2="1143" y1="852" y2="852" x1="903" />
        </branch>
        <instance x="1143" y="1172" name="XLXI_1" orien="R0" />
        <instance x="679" y="836" name="XLXI_35" orien="R0" />
        <bustap x2="775" y1="564" y2="564" x1="903" />
        <bustap x2="775" y1="628" y2="628" x1="903" />
        <branch name="XLXN_113">
            <wire x2="1639" y1="948" y2="948" x1="1527" />
        </branch>
        <branch name="iAEN">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="1271" y="1316" type="branch" />
            <wire x2="1271" y1="1316" y2="1316" x1="1223" />
            <wire x2="1575" y1="1316" y2="1316" x1="1271" />
            <wire x2="1639" y1="1012" y2="1012" x1="1575" />
            <wire x2="1575" y1="1012" y2="1316" x1="1575" />
        </branch>
        <bustap x2="823" y1="1092" y2="1092" x1="919" />
        <bustap x2="823" y1="1156" y2="1156" x1="919" />
        <bustap x2="823" y1="1220" y2="1220" x1="919" />
        <bustap x2="823" y1="1284" y2="1284" x1="919" />
        <bustap x2="823" y1="1348" y2="1348" x1="919" />
        <bustap x2="823" y1="1412" y2="1412" x1="919" />
        <bustap x2="823" y1="1476" y2="1476" x1="919" />
        <bustap x2="823" y1="1540" y2="1540" x1="919" />
        <branch name="XLXN_135(7:0)">
            <wire x2="1143" y1="1044" y2="1044" x1="919" />
            <wire x2="919" y1="1044" y2="1092" x1="919" />
            <wire x2="919" y1="1092" y2="1156" x1="919" />
            <wire x2="919" y1="1156" y2="1220" x1="919" />
            <wire x2="919" y1="1220" y2="1284" x1="919" />
            <wire x2="919" y1="1284" y2="1348" x1="919" />
            <wire x2="919" y1="1348" y2="1412" x1="919" />
            <wire x2="919" y1="1412" y2="1476" x1="919" />
            <wire x2="919" y1="1476" y2="1540" x1="919" />
            <wire x2="919" y1="1540" y2="1572" x1="919" />
        </branch>
        <instance x="679" y="1076" name="XLXI_126" orien="R0" />
        <branch name="XLXN_136">
            <wire x2="743" y1="1076" y2="1092" x1="743" />
            <wire x2="823" y1="1092" y2="1092" x1="743" />
            <wire x2="743" y1="1092" y2="1156" x1="743" />
            <wire x2="823" y1="1156" y2="1156" x1="743" />
        </branch>
        <bustap x2="807" y1="500" y2="500" x1="903" />
        <bustap x2="807" y1="436" y2="436" x1="903" />
        <bustap x2="807" y1="372" y2="372" x1="903" />
        <bustap x2="807" y1="308" y2="308" x1="903" />
        <bustap x2="807" y1="244" y2="244" x1="903" />
        <bustap x2="807" y1="180" y2="180" x1="903" />
        <branch name="iA19">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="743" y="180" type="branch" />
            <wire x2="743" y1="180" y2="180" x1="695" />
            <wire x2="807" y1="180" y2="180" x1="743" />
        </branch>
        <branch name="iA18">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="743" y="244" type="branch" />
            <wire x2="743" y1="244" y2="244" x1="695" />
            <wire x2="807" y1="244" y2="244" x1="743" />
        </branch>
        <branch name="iA17">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="743" y="308" type="branch" />
            <wire x2="743" y1="308" y2="308" x1="695" />
            <wire x2="807" y1="308" y2="308" x1="743" />
        </branch>
        <branch name="iA16">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="743" y="372" type="branch" />
            <wire x2="743" y1="372" y2="372" x1="695" />
            <wire x2="807" y1="372" y2="372" x1="743" />
        </branch>
        <branch name="iA15">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="743" y="436" type="branch" />
            <wire x2="743" y1="436" y2="436" x1="695" />
            <wire x2="807" y1="436" y2="436" x1="743" />
        </branch>
        <branch name="iA14">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="743" y="500" type="branch" />
            <wire x2="743" y1="500" y2="500" x1="695" />
            <wire x2="807" y1="500" y2="500" x1="743" />
        </branch>
        <branch name="iSW5">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="759" y="1220" type="branch" />
            <wire x2="759" y1="1220" y2="1220" x1="711" />
            <wire x2="823" y1="1220" y2="1220" x1="759" />
        </branch>
        <branch name="iSW6">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="759" y="1284" type="branch" />
            <wire x2="759" y1="1284" y2="1284" x1="711" />
            <wire x2="823" y1="1284" y2="1284" x1="759" />
        </branch>
        <branch name="iSW7">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="759" y="1348" type="branch" />
            <wire x2="759" y1="1348" y2="1348" x1="711" />
            <wire x2="823" y1="1348" y2="1348" x1="759" />
        </branch>
        <instance x="1639" y="1076" name="XLXI_123" orien="R0" />
        <branch name="iA13">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="743" y="564" type="branch" />
            <wire x2="743" y1="564" y2="564" x1="695" />
            <wire x2="775" y1="564" y2="564" x1="743" />
        </branch>
        <branch name="XLXN_139">
            <wire x2="775" y1="628" y2="628" x1="743" />
            <wire x2="743" y1="628" y2="708" x1="743" />
        </branch>
        <branch name="XLXN_140">
            <wire x2="823" y1="1476" y2="1476" x1="743" />
            <wire x2="743" y1="1476" y2="1540" x1="743" />
            <wire x2="743" y1="1540" y2="1572" x1="743" />
            <wire x2="823" y1="1540" y2="1540" x1="743" />
        </branch>
        <branch name="iSW8">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="759" y="1412" type="branch" />
            <wire x2="759" y1="1412" y2="1412" x1="711" />
            <wire x2="823" y1="1412" y2="1412" x1="759" />
        </branch>
        <branch name="iROM_EN">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="1975" y="980" type="branch" />
            <wire x2="1975" y1="980" y2="980" x1="1895" />
            <wire x2="2135" y1="980" y2="980" x1="1975" />
        </branch>
        <instance x="679" y="1700" name="XLXI_127" orien="R0" />
        <iomarker fontsize="28" x="695" y="180" name="iA19" orien="R180" />
        <iomarker fontsize="28" x="695" y="244" name="iA18" orien="R180" />
        <iomarker fontsize="28" x="695" y="308" name="iA17" orien="R180" />
        <iomarker fontsize="28" x="695" y="372" name="iA16" orien="R180" />
        <iomarker fontsize="28" x="695" y="436" name="iA15" orien="R180" />
        <iomarker fontsize="28" x="695" y="500" name="iA14" orien="R180" />
        <iomarker fontsize="28" x="695" y="564" name="iA13" orien="R180" />
        <iomarker fontsize="28" x="711" y="1220" name="iSW5" orien="R180" />
        <iomarker fontsize="28" x="711" y="1284" name="iSW6" orien="R180" />
        <iomarker fontsize="28" x="711" y="1348" name="iSW7" orien="R180" />
        <iomarker fontsize="28" x="711" y="1412" name="iSW8" orien="R180" />
        <iomarker fontsize="28" x="1223" y="1316" name="iAEN" orien="R180" />
        <iomarker fontsize="28" x="2135" y="980" name="iROM_EN" orien="R0" />
    </sheet>
</drawing>