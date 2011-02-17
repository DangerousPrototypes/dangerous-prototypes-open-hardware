<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xbr" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_3" />
        <signal name="XLXN_5" />
        <signal name="LED" />
        <signal name="LED_INV" />
        <signal name="BUTTON" />
        <port polarity="Output" name="LED" />
        <port polarity="Output" name="LED_INV" />
        <port polarity="Input" name="BUTTON" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="pullup">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-108" y2="-128" x1="64" />
            <line x2="64" y1="-104" y2="-108" x1="80" />
            <line x2="80" y1="-88" y2="-104" x1="48" />
            <line x2="48" y1="-72" y2="-88" x1="80" />
            <line x2="80" y1="-56" y2="-72" x1="48" />
            <line x2="48" y1="-48" y2="-56" x1="64" />
            <line x2="64" y1="-32" y2="-48" x1="64" />
            <line x2="64" y1="-56" y2="-48" x1="48" />
            <line x2="48" y1="-72" y2="-56" x1="80" />
            <line x2="80" y1="-88" y2="-72" x1="48" />
            <line x2="48" y1="-104" y2="-88" x1="80" />
            <line x2="80" y1="-108" y2="-104" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-128" y2="-128" x1="96" />
        </blockdef>
        <block symbolname="ibuf" name="XLXI_1">
            <blockpin signalname="BUTTON" name="I" />
            <blockpin signalname="XLXN_5" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_2">
            <blockpin signalname="XLXN_5" name="I" />
            <blockpin signalname="LED" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_3">
            <blockpin signalname="XLXN_3" name="I" />
            <blockpin signalname="LED_INV" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="XLXN_5" name="I" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="pullup" name="XLXI_6">
            <blockpin signalname="BUTTON" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_3">
            <wire x2="1712" y1="928" y2="928" x1="1696" />
        </branch>
        <branch name="LED">
            <wire x2="1952" y1="800" y2="800" x1="1936" />
        </branch>
        <branch name="LED_INV">
            <wire x2="1952" y1="928" y2="928" x1="1936" />
        </branch>
        <instance x="1168" y="896" name="XLXI_1" orien="R0" />
        <instance x="1472" y="960" name="XLXI_5" orien="R0" />
        <instance x="1712" y="960" name="XLXI_3" orien="R0" />
        <iomarker fontsize="28" x="1952" y="928" name="LED_INV" orien="R0" />
        <instance x="1712" y="832" name="XLXI_2" orien="R0" />
        <branch name="XLXN_5">
            <wire x2="1440" y1="864" y2="864" x1="1392" />
            <wire x2="1440" y1="864" y2="928" x1="1440" />
            <wire x2="1472" y1="928" y2="928" x1="1440" />
            <wire x2="1712" y1="800" y2="800" x1="1440" />
            <wire x2="1440" y1="800" y2="864" x1="1440" />
        </branch>
        <iomarker fontsize="28" x="1952" y="800" name="LED" orien="R0" />
        <branch name="BUTTON">
            <wire x2="1120" y1="864" y2="864" x1="1072" />
            <wire x2="1168" y1="864" y2="864" x1="1120" />
            <wire x2="1120" y1="832" y2="864" x1="1120" />
        </branch>
        <iomarker fontsize="28" x="1072" y="864" name="BUTTON" orien="R180" />
        <instance x="1056" y="832" name="XLXI_6" orien="R0" />
    </sheet>
</drawing>