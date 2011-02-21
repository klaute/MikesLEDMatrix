<map version="0.8.1">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1285505067034" MODIFIED="1285505067034" TEXT="LEDMatrix">
<node CREATED="1285505067034" MODIFIED="1285505067034" POSITION="right" TEXT="Hardware">
<node CREATED="1285505067034" MODIFIED="1285505067034" TEXT="Matrix">
<node CREATED="1285505067034" MODIFIED="1285505067034" TEXT="441 LED&apos;s (blau, ultrahell, 3mm)"/>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="441 LED Halterungen"/>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="ca. 100 Meter Kupferlitze"/>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="ca. 5 Meter Silberdraht"/>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="aufgeteilt in 8x8x8 Bl&#xf6;cke">
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="3 der 8 Bl&#xf6;cke sind nicht voll belegt"/>
</node>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="Anordnung in 21x21 Reihen"/>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="es leuchtet maximal ein Block zur selben Zeit komplett"/>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="auf Edelstahlplatte montiert">
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="die Edelstahlplatte ist in Mike&apos;s Rahmen des MP3Player montiert"/>
</node>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="ca. 3 Wochen a 5 Wochentage a 3 Stunden L&#xf6;tzeit"/>
</node>
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="Steuerplatine">
<node CREATED="1285505067035" MODIFIED="1285505067035" TEXT="Technische Daten">
<node CREATED="1285505067035" ID="Freemind_Link_1044005588" MODIFIED="1285505067035" TEXT="ATmega32">
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="32KB Flash">
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="davon 4KB als Bootloader genutzt"/>
</node>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="2KB SRAM"/>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="4x 8Bit Ports in Verwendung">
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="damit alle des &#xb5;C"/>
</node>
<node CREATED="1285505067036" ID="Freemind_Link_836289472" MODIFIED="1285505067036" TEXT="max. 16MHz Takt">
<node CREATED="1285505111440" ID="_" MODIFIED="1285505122456" TEXT="16MHz Quarz verbaut">
<node CREATED="1285505140396" ID="Freemind_Link_923818415" MODIFIED="1285505154538" TEXT="bringt Probleme mit V-USB Modul bei Nvidia Chips&#xe4;tzen"/>
</node>
<node CREATED="1285505123631" ID="Freemind_Link_1515974900" MODIFIED="1285505138639" TEXT="12MHz Quarz zu Testen"/>
</node>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="16 Bit Microkontroller"/>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="Havard Architektur"/>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="RISC"/>
</node>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="D-Latches">
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="8x 74HC573"/>
</node>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="8x N-MOSFET"/>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="diverse passive Bauteile"/>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="USB 1.1 Anschluss unter Verwendung&#xa;von INT2-Pin und Software USB-Stack">
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="elektrische Verbindung mit Z-Dioden wie in V-USB Beispiel"/>
</node>
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="ISP Schnittstelle">
<node CREATED="1285505067036" MODIFIED="1285505067036" TEXT="Programmierung des &#xb5;C ohne diesen aus&#xa;dem Socker nehmen zu m&#xfc;ssen."/>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="Pinbelegung kompatibel mit USB Proggi vom&#xa;Minimexle Projekt der HHN"/>
</node>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="9 Steckverbinder (8-Polig)">
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="8 f&#xfc;r die LED-Bl&#xf6;cke"/>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="einer f&#xfc;r die Massen"/>
</node>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="5V Versorgungsspannung">
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="Durch Spannungsregler von 12-18V auf 5V herunter geregelt"/>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="die LED&apos;s werden hierdurch mit versorgt"/>
</node>
</node>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="m&#xf6;gliche Erweiterungen">
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="Steuerung der 8 MOSFET&apos;s per PWM um die LED&apos;s dimmen zu k&#xf6;nnen"/>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="externen USB-Chip verwenden um die Datenrate zu erh&#xf6;hen"/>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="&#xe4;tzen der Platine"/>
</node>
</node>
</node>
<node CREATED="1285505067037" MODIFIED="1285505067037" POSITION="left" TEXT="Software">
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="Flashspeicher">
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="USBaspLoader">
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="im Bootloader"/>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="ca. 1,2 KB gro&#xdf;"/>
<node CREATED="1285505067037" MODIFIED="1285505067037" TEXT="zum flashen der eigentlichen Firmware"/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="schreibgesch&#xfc;tzt durch Fuses im AVR"/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="Startet wenn auf der Steuerplatine ein Jumpergesetzt ist,&#xa;nach Bet&#xe4;tigung des Reset-Buttons."/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="wird als USBASP USB device erkannt">
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="Treiber f&#xfc;r Windows vorhanden"/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="unter Linux per avrusb unterst&#xfc;tzt">
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="f&#xfc;r Zugriff als user m&#xfc;ssen udev Rechte angepasst werden"/>
</node>
</node>
</node>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="eigentliche Firmware">
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="V-USB">
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="Software USB (v1.1) Stack">
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="es gibt Probleme bei der Konnektivit&#xe4;t mancher Rechner"/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="unabh&#xe4;ngig vom Betriebssystem"/>
</node>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH"/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary"/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="hier als hid-data Device konfiguriert">
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="maximale Datenblock-Gr&#xf6;&#xdf;e 64Byte">
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="vorher 128 Byte"/>
</node>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="Kommunikation &#xfc;ber USB Controll Messages">
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="zum senden USBRQ_HID_SET_REPORT"/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="zum empfangen USBRQ_HID_GET_REPORT"/>
</node>
</node>
</node>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="basiert auf ledCube"/>
<node CREATED="1285505067038" MODIFIED="1285505067038" TEXT="erweiterte Animationen"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="interner Equalizer"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="interne Animationen"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="anzeigen von Einzelframes"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="ca. 15 KB gro&#xdf;"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="translations und rotations Funktionalit&#xe4;t entfernt"/>
</node>
</node>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="Kommandozeile">
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="USBClient">
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="verwendet die libUSB"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="fr&#xfc;her hidtool aus den V-USB examples"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="Anpassungen des originalen&#xa;hid-data Client">
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="interaktive Kommandozeile"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="optimierte Senderoutine">
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="es wird nur die Anzahl der Bytes gesendet,&#xa;die &#xfc;bergeben wurde"/>
</node>
</node>
</node>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="Perl">
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="frame2function.pl">
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="Konvertierung von &quot;.led&quot;-Dateien in C-Funktionen"/>
</node>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="64rnd.pl"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="testAllBits.pl">
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="es werden alle LED&apos;s nacheinander und&#xa;blockweise an und ab geschaltet"/>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="jede getestete LED-Reihe bleibt aktiviert"/>
</node>
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="playAnimation.pl">
<node CREATED="1285505067039" MODIFIED="1285505067039" TEXT="&#xfc;bertr&#xe4;gt per usbclient &quot;.led&quot;-Dateien Frameweise an den &#xb5;c"/>
</node>
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="testEqualizer.pl"/>
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="animation2function.pl">
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="Konvertierung von &quot;.led&quot;-Dateien in C-Funktionen"/>
</node>
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="alle Scripte verwenden den USBClient"/>
</node>
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="Bash">
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="randomFrame.sh"/>
</node>
</node>
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="X11">
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="basierend auf QT">
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="shinyLED">
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="zum erzeugen von &quot;.led&quot;-Dateien"/>
</node>
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="shinyPlayer">
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="MP3-Player der per Touchscreen bedient wird"/>
</node>
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="verwenden alle Teile des USBClients und die libUSB"/>
</node>
</node>
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="Windows">
<node CREATED="1285505067040" MODIFIED="1285505067040" TEXT="originaler hidtool Client"/>
</node>
<node CREATED="1285505067041" MODIFIED="1285505067041" TEXT="meist genutzte Lizenz und Copyright">
<node CREATED="1285505067041" MODIFIED="1285505067041" TEXT="License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary"/>
<node CREATED="1285505067041" MODIFIED="1285505067041" TEXT="Copyright: (c) 2009 by klaute (klaute@gmail.com)"/>
</node>
</node>
</node>
</map>
