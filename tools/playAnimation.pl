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

# define usage message
my $usage = "\nUsage:\n\n\t./testAnimation.pl <shinyLed animation filename> <time in cycles of 8 ms between frames> <optional path to hidtool> <endless optional>\n\n";

# get user parameters
my $filename = shift || die "$usage\n";
my $cycles   = shift || die "$usage\n";
my $hidtool  = shift || "usbclient";
my $endless  = shift || 0;

# leeren Hash initialisieren
my %hash;
for ( my $i = 0; $i < 8; $i++ )
{
	for ( my $j = 0; $j < 8; $j++ )
	{
		$hash{$i."-".$j} = 0;
	}
}
# open input file
open FILE, "< $filename";

# Pipe zu usbclient herstellen
open OUT, "| $hidtool/hidtool interactive quiet" || die "Pipe konnte nicht geöffnet werden...\n";

	# Puffer für Pipe deaktivieren
	{
	my $tmp = select OUT;
	$| = 1;
	select $tmp;
	}

	# Datei einlesen
	my @lines = <FILE>;

	# Laufvariablen
	my $i = 0;
	my $data = "";
	my $cmdcnt = 0;

	# print function header
	print "Starte Animation...\n";
	print OUT "w 4 1\n"; # Frame löschen

	usleep(1000); # 1ms pause

	if ( $endless == 1 )
	{
		while (1)
		{
			playAnim();
		}
	} else {
		playAnim();
	}

	# close the function
	print "Ende\n";
	print OUT "q\n";

close OUT;

close FILE;

# done
exit 0;

sub playAnim
{

	# Animationsdatei zeilenweise durchgehen
	foreach my $line ( @lines )
	{
		chomp $line;
		# split the line into 3 parts
		my @tmp = split(" ", $line);
		my @commands;

		if ( $i == 0 )
		{
			print "Übertrage neues Frame...\n";
		}

		# Check for changed hash element.
		# Simple optimization progress to get a shorter function.
		if ( defined( $hash{$tmp[0]."-".$tmp[1]} ) && $hash{$tmp[0]."-".$tmp[1]} != $tmp[2] )
		{
			$cmdcnt++;
			push @commands, "w 2 $tmp[0] $tmp[1] $tmp[2]";
		}
		# save new hash value
		$hash{$tmp[0]."-".$tmp[1]} = $tmp[2];

		$data .= " ". sprintf("0x%02x", $tmp[2]);

		$i++;
		if ( $i == 64 ) # wenn 64 Bytes gelesen wurden die Daten ausgeben.
		{
=rem
			if ( ($cmdcnt * 4) >= 64 ) # Frame in einem Befehl übertragen
			{
=cut
				print "Schreibe 64 Bytes...\n";
				print OUT "w 1\n"; # Modus umschalte (1)
				usleep(1000);
				print OUT "w $data\n"; # 64 Bytes schreiben

=rem
			} else { # nur die änderungen übertragen
				print "Schreibe ". ($cmdcnt*4). " Bytes...\n";
				foreach my $cmd ( @commands )
				{
					print OUT $cmd. "\n"; # Ein Byte schreiben
				}
				
			}
=cut
			# Kurze Pause und aufräumen
			usleep(8000 * $cycles);
			$i = 0;
			$data = "";
			$cmdcnt = 0;
		}
	}

}

1;

