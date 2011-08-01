/*
  This programm is part of MikesLEDMatrix by Kai Lauterbach.

  gefa <Generate Flash Animation>
  use a simple compression for saving animation in the atmega Flash

  written by Mike Gareiss

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <QtCore/QCoreApplication>
#include <QList>

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include <iostream>
#include <inttypes.h>
#include <math.h>

using namespace std;

struct Frame
{
    //irgenwie bekomm ich das uint8_t nicht in QList
    //deswegen der umweg ueber die struktur

    // 8 ebenen mit 8 reihen
    // spalten sind die bits in reihen

    uint8_t ebene[8][8];
};

QList<Frame*> frames;
Frame* currentFrame;
QList<uint8_t*> maske_aenderungen;
QList<uint8_t*> aenderungen;

void clearFrame(Frame* f)
{
    for(int x = 0; x < 8; x++)
       {
        for(int y = 0; y < 8; y++)
            f->ebene[x][y] = 0;
       }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc < 2)
    {
        qDebug("Kein File angegeben!");
        qDebug("playAnimation <Led-File>");
        return -1;
    }

    QString ledfilename = a.arguments().at(1);
    QFileInfo ledfileInfo(ledfilename);
    if(!ledfileInfo.exists())
    {
        qDebug() << QString("Konnte File '%1' nicht finden").arg(ledfilename);
        return -1;
    }

    QFile f(ledfilename);

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("Fehler beim oeffne");
        return -1;
    }

    qDebug("File open");

    //Frames aus dem File in die Liste frames einlesen
    Frame* frame;
    QTextStream out(&f);
    int e, r, s;
    frames.clear();
    do
    {
       frame = new Frame;
        clearFrame(frame);
        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 8; y++)
            {
                out >> e;
                out >> r;
                out >> s;
                frame->ebene[e][r] = s;
            }
        }
        frames.append(frame);
    }
    while(!out.atEnd());
    frames.pop_back();

    //Die Listen für die Maske und den Änderungen auf null setzen
    maske_aenderungen.clear();
    aenderungen.clear();

    uint8_t* byteMaske;
    uint8_t* byteAenderung;

    frame = frames.at(0);
    /*
      Ein Frame besteht aus 64 Bytes. Eine Maske besteht aus 8 Bytes das sind 64 bits.
      Ein Bit der Maske steht für ein Byte des Frames. Ist das Byte != 0 dann wird das Byte
      in die Liste der Änderungen geschoben und das entsprechende Bit in der Maske gesetzt.
      Abschliessend werden die 8 Bytes der Maske in die Liste der Maske geschoben.
    */
    for(int x = 0; x < 8; x++)
    {
        byteMaske = new uint8_t;
        *byteMaske = 0;

        for(int y = 0; y < 8; y++)
        {
            if(frame->ebene[x][y] != 0)
            {
                *byteMaske = *byteMaske + pow(2,y);
                byteAenderung = new uint8_t;
                *byteAenderung = (uint8_t)(frame->ebene[x][y]);
                aenderungen.append(byteAenderung);
            }
        }

        maske_aenderungen.append(byteMaske);
    }

    /*
      Selbes Prinzip nur dass ein Byte des Frames mit dem Byte des vorangegangenen Frame
      verglichen wird.
    */
    for(int i = 1; i < frames.size(); i++)
    {
        currentFrame = frames.at(i);
        frame = frames.at(i-1);

        for(int x = 0; x < 8; x++)
        {
            byteMaske = new uint8_t;
            *byteMaske = 0;

            for(int y = 0; y < 8; y++)
            {
                if(currentFrame->ebene[x][y] != frame->ebene[x][y])
                {
                    *byteMaske = *byteMaske + pow(2,y);
                    byteAenderung = new uint8_t;
                    *byteAenderung = currentFrame->ebene[x][y];
                    aenderungen.append(byteAenderung);
                }
            }

            maske_aenderungen.append(byteMaske);
        }
    }

    int rest = aenderungen.size() % 8;
    for (int i = 0; i < rest; i++)
    {
        byteAenderung = new uint8_t;
        *byteAenderung = 0;
        aenderungen.append(byteAenderung);
    }
    cout << "\n\n";
    cout << "const uchar frames<NUM> = " << frames.size() << "\n";

    cout << "const uchar maske<NUM>[] PROGMEM = { \n";
    for(int i = 0; i<maske_aenderungen.size(); i++)
    {
        cout << (int)(*maske_aenderungen.at(i)) << ",";
        if (i % 16 == 0)
            cout << "\n";
    }
    cout << "};\n";

    cout << "const uchar aendrung<NUM>[] PROGMEM = { \n";
    for(int i = 0; i<aenderungen.size(); i++)
    {
        cout << (int)(*aenderungen.at(i)) << ",";
        if (i % 16 == 0)
            cout << "\n";
    }
    cout << "};\n\n";
    cout << "Diesen Code in animation.h kopieren\n";
    cout << "<NUM> muss noch als fortlaufende Nummer ersetzt werden\n";
    cout << "In der main.c muss noch in der While Schleife Code eingefügt werden\n";
    cout << "\n case 36 : ;\n";
    cout << "        playAnimation = true;\n";
    cout << "        playAnimationen(maske7, aendrung7,frames7);\n";


    return 0; //a.exec();
}
