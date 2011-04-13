<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="LED" />
        <signal name="BUTTON" />
        <signal name="XLXN_8" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <port polarity="Output" name="LED" />
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
        <block symbolname="ibuf" name="XLXI_1">
            <blockpin signalname="BUTTON" name="I" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_2">
            <blockpin signalname="XLXN_10" name="I" />
            <blockpin signalname="LED" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="LED">
            <wire x2="1952" y1="800" y2="800" x1="1936" />
        </branch>
        <instance x="1712" y="832" name="XLXI_2" orien="R0" />
        <iomarker fontsize="28" x="1952" y="800" name="LED" orien="R0" />
        <branch name="BUTTON">
            <wire x2="1456" y1="800" y2="800" x1="1440" />
            <wire x2="1472" y1="800" y2="800" x1="1456" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="1712" y1="800" y2="800" x1="1696" />
        </branch>
        <instance x="1472" y="832" name="XLXI_1" orien="R0" />
        <iomarker fontsize="28" x="1440" y="800" name="BUTTON" orien="R180" />
    </sheet>
</drawing>