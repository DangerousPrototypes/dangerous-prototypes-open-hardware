<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="LED" />
        <signal name="XLXN_12" />
        <port polarity="Output" name="LED" />
        <blockdef name="obuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="32" y1="-64" y2="-64" x1="96" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="64" />
        </blockdef>
        <block symbolname="obuf" name="XLXI_2">
            <blockpin signalname="XLXN_12" name="I" />
            <blockpin signalname="LED" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_3">
            <blockpin signalname="XLXN_12" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="LED">
            <wire x2="1952" y1="800" y2="800" x1="1936" />
        </branch>
        <instance x="1712" y="832" name="XLXI_2" orien="R0" />
        <iomarker fontsize="28" x="1952" y="800" name="LED" orien="R0" />
        <branch name="XLXN_12">
            <wire x2="1712" y1="768" y2="800" x1="1712" />
        </branch>
        <instance x="1648" y="768" name="XLXI_3" orien="R0" />
    </sheet>
</drawing>