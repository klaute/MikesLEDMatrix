#!/usr/bin/perl -w
=rem
 (C) Copyright 2010 Kai Lauterbach klaute at web.de

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
=cut

use strict;
use Time::HiRes qw(usleep);

my $hidtool = shift || "usbclient";
my $wait = shift || 1000;

open OUT, "| $hidtool/hidtool interactive quiet" || die "Pipe konnte nicht geöffnet werden...\n";

	# Puffer für Pipe deaktivieren
	{
	my $tmp = select OUT;
	$| = 1;
	select $tmp;
	}

	# print function header
	print OUT "w 4 1\n"; # Frame löschen
	usleep(1000);

    for ( my $t = 0; $t < 3; $t++ )
    {
	for ( my $i = 30; $i < 41; $i++ )
	{
		print OUT "w 4 $i\n"; # einen ring zeichnen
		usleep($wait);
	}

	for ( my $i = 50; $i < 61; $i++ )
	{
		print OUT "w 4 $i\n"; # einen ring zeichnen
		usleep($wait);
	}
    }

	print OUT "w 4 1\n"; # Frame löschen
	usleep(1000);

    for ( my $t = 0; $t < 3; $t++ )
    {
	for ( my $i = 30; $i < 41; $i++ )
	{
		print OUT "w 4 $i\n"; # einen ring zeichnen
		usleep($wait);
	}

	for ( my $i = 60; $i > 49; $i-- )
	{
		print OUT "w 4 $i\n"; # einen ring zeichnen
		usleep($wait);
	}
    }

	print OUT "w 4 1\n"; # Frame löschen
	usleep(1000);

    for ( my $t = 0; $t < 3; $t++ )
    {
	for ( my $i = 30; $i < 41; $i++ )
	{
		print OUT "w 4 $i\n"; # einen ring zeichnen
		usleep($wait);
		print OUT "w 4 ". ($i+20). "\n"; # einen ring zeichnen
	}
	for ( my $i = 60; $i > 49; $i-- )
	{
		print OUT "w 4 ". ($i-20). "\n"; # einen ring zeichnen
		usleep($wait);
		print OUT "w 4 $i\n"; # einen ring zeichnen
	}
    }

	print OUT "q\n";

close OUT;


