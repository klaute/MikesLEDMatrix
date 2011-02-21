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

# define usage message
my $usage = "\nUsage:\n\n\t./animation2function.pl <shinyLed animation filename> <function name> <time in cycles of 8 ms between frames>\n\n";

# get user parameters
my $filename = shift || die "$usage\n";
my $fname    = shift || die "$usage\n";
my $cycles   = shift || die "$usage\n";

my %hash;

# Hash initialisieren
for ( my $i = 0; $i < 8; $i++ )
{
	for ( my $j = 0; $j < 8; $j++ )
	{
		$hash{$i."-".$j} = 0;
	}
}

# open input file
open FILE, "< $filename";

	my @lines = <FILE>;
	my $i = 0;
	# print function header
	print "void animation_$fname(void)\n{\n\tuint8_t dur = $cycles;\n\tcube_clear();\n";
	foreach my $line ( @lines )
	{
		chomp $line;
		# split the line into 3 parts
		my @tmp = split(" ", $line);
	
		if ( $i == 64 ) # every 64 lines equal one frame, so the function should break a few cycles.
		{
			print "	cube_show_loop(dur);\n";
			$i = 0;
		}
		# Check for changed hash element.
		# Simple optimization progress to get a shorter function.
		if ( defined( $hash{$tmp[0]."-".$tmp[1]} ) && $hash{$tmp[0]."-".$tmp[1]} != $tmp[2] )
		{
			print sprintf("	cube[%d][%d] = 0x%02x;\n",$tmp[0],$tmp[1],$tmp[2]);
		}
		# save new hash value
		$hash{$tmp[0]."-".$tmp[1]} = $tmp[2];

		$i++;
	}

	# close the function
	print "}\n";

close FILE;

# done

