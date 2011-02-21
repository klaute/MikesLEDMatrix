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

system("../usbclient/hidtool write 5");

for (my $i = 0; $i < 8; $i++)
{
	for (my $j = 0; $j < 8; $j++)
	{
		for (my $k = 0; $k < 8; $k++)
		{
			#system("clear");
			out($i,$j,$k);
			sleep 1;
		}
		out($i,$j,255, 1); # Zeile bleibt an
	}
}
exit 0;

sub out
{
	my $i = shift;
	my $j = shift;
	my $k = shift;
	my $l = shift;
	my $v = 2**$k;
	if ( $l )
	{
		print "$i $j $k\n";
		system("../usbclient/hidtool write 2 $i $j $k");
	} else {
		print "$i $j 2^$k = $v\n";
		system("../usbclient/hidtool write 2 $i $j $v");
	}
	system("../usbclient/hidtool write 1");
	print `../usbclient/hidtool read| tail -n4`;
	#system("sleep 1");
	#system("./hidtool write 2 $i $j 0");
}
